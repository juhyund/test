/**
* Author : Hyunoh Shin
* Created : 2019. 2. 13
* DTLS Proxy for Radius Server and Radius Client 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "nproxy.h"
#include "ptls.h"
#include "log.h"
#include "config.h"
#include "udpComm.h"

int nproxy_server_init(struct instance *ins);
int nproxy_ptls_run(struct instance *ins);
int thread_create(ptls_session_ctx *ctx, struct instance *ins);
void *svr_thread_func(void* data);


int main()
{
	struct instance ins;

	log_stderr_open(LOG_INFO);

	log_info(" ................ [START] NURI PROXY  ................ ");
	nproxy_server_init(&ins);
	nproxy_ptls_run(&ins);

	log_info(" ................ [END] NURI PROXY  ................ ");
	return 0;
}

int nproxy_server_init(struct instance *ins)
{
	int ret = 0;

	// Setting Configuration
	log_info("proxy server initialization ");
	log_info("nproxy config file  = %s", NPROXY_CONFIG_FILE);
	if ( ! (ret=setConfig(ins)) )
	{
		log_error("Read Config file FAILD !!");
		return ret;
	}

}

int nproxy_ptls_run(struct instance *ins)
{
	ptls_ctx *ctx = NULL;
	char buf[32768] = { 0 };
	int len = 32768;
	int ret = 0;

	//1. ptls server init
	log_info("ptls server initialization");
	ctx = ptls_ctx_malloc();
	if(!ctx)
	{
		log_error("ptls_ctx_malloc fail ! !");
		return PTLS_ERR_FATAL;
	}
	ret = ptls_server_init(ctx,PTLS_SSL_TRANSPORT_DATAGRAM, //DTLS
			ins->private_key_file, NULL, // Private Key file & key file Password
			ins->cert_file, // Certficate file
			ins->ca_file); // CA & CRL config file
	if( ret != 0 ) 
	{
    	log_info("proxy server init - %04X\n", -ret);
		goto exit;
	}

	//2. ptls server bind
	ret = ptls_server_bind(ctx, ins->listen_host, ins->listen_port);
	if( ret != 0 ) 
	{
	
    	log_info("proxy server bind - %04X\n", -ret);
		goto exit;
	}

reset:
	while(1)
	{
		log_info("Waiting for DTLS communication...... ");
		//3. ptls_session_ctx malloc
		ptls_session_ctx *sctx = ptls_session_ctx_malloc();
		if(!sctx) {
			log_error("ptls_session_ctx_malloc fail\n");
			goto exit;
		}
		else log_info("ptls_session_ctx_malloc success");
retry:
		//4. ptls server accept
		if (0 != (ret = ptls_server_accept(sctx, ctx)))
		{
			if (0x7890 == -ret) // Penta Library internal error handling
			{
				goto retry;
			}
		}
	
		log_debug("ptls_server_accept - %d",ret);
		if (ret == PTLS_ERR_SSL_HELLO_VERIFY_REQUIRED) goto retry;
		if (ret != 0) ret = ptls_server_session_close_notify(sctx);
	
		log_info("Cipher-Suite : %s", ptls_get_session_ciphersuite(sctx));
		// Hand shake end
        if( ( ret = thread_create( sctx , ins) ) != 0 )
        {
            log_info( "thread_create failed %d", ret );
            goto reset;
        }
        log_info( "thread_create success %d", ret );
      }

exit:
    log_info("proxy server init done - %04X", -ret);
    ret = ptls_server_final(ctx);

    ptls_ctx_free(ctx);

	return ret;
}

int thread_create(ptls_session_ctx *sctx, struct instance *ins)
{
    int ret = 0;
    pthread_t	thread;
	struct ptlsArgs	*pargs;

	pargs = (struct ptlsArgs*)malloc(sizeof(struct ptlsArgs));
	pargs->sctx = sctx;
	pargs->ins = ins;
    if( ( ret = pthread_create( &thread, NULL, svr_thread_func,
                                pargs ) ) != 0 )
    {
        log_info("pthread_create%d", ret);
        return( ret );
    }

    return( 0 );
}

void *svr_thread_func(void* args)
{
	int ret = 0;
	struct ptlsArgs *pargs = (struct ptlsArgs *)args;
    ptls_session_ctx* sctx = pargs->sctx;
	struct instance *ins = pargs->ins;

#if WIN32
    pthread_t ptid = pthread_self();
    long int thread_id = (long int) &ptid;
#else
    long int thread_id = (long int) pthread_self();
#endif
	char buf[PTLS_SSL_MAX_CONTENT_LEN] = { 0 };
	char *rbuf;
    int buf_len = sizeof(buf);
    int len = 0;
	int rbuf_len, s/*socket*/;
	time_t stime, ctime;

	s = udpSocketCreate();
    log_info("[thread_id : %u] Thread start ", thread_id, ret);

    while(1) 
	{
		// 1. ptls server read
        ret = ptls_server_read(sctx, buf, buf_len);
		//If the message length is less than 100, print it out; otherwise, only log is left.
        if (ret > 0 )
            log_info("ptls_server_read[%d] : <<pass>> ", ret );
        else
		{
			switch (ret)
			{
				case PTLS_ERR_FATAL:
					log_error("PTLS FATAL ERROR ! ! ");
					break;
				case PTLS_ERR_SSL_TIMEOUT:
					log_error("The operation timed out.");
					break;
				case PTLS_ERR_SSL_HELLO_VERIFY_REQUIRED:
					log_error("DTLS client must retry for hello verification.");
					break;
				case PTLS_ERR_SSL_WANT_READ:
					log_error("No data of requested type currently available on underlying transport.");
					break;
				case PTLS_ERR_SSL_WANT_WRITE:
					log_error("Connection requires a write call.");
					break;
				case PTLS_ERR_SSL_BAD_INPUT_DATA:
					log_error("Bad input parameters to function.");
					break;
			}
			
		}
		if(ret <=0) break;

		//2. upd Communicate to backend server(client) , Send Msgs
		udpProxyComm(s, ins->backend_host, ins->backend_port, buf, ret, &rbuf, &rbuf_len);

		//3. ptls server write
		ret = ptls_server_write(sctx, rbuf, rbuf_len);
        log_info("ptls_server_write[%d] : <<pass>>\n", ret);
        if (ret <= 0)
            break;
    }
    ret = ptls_server_session_close_notify(sctx);
    log_info("[thread_id : %u] ptls_server_session_close_notify %d", thread_id, ret);
	updSocketClose(s);

    ptls_session_ctx_free(sctx);
    log_info("[thread_id : %u] ptls_session_ctx_free %d", thread_id, ret);

    log_info("[thread_id : %u] Thread terminated \n", thread_id, ret);
    return NULL;

}
