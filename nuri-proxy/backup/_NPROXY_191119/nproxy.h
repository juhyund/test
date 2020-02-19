#ifndef _NPROXY_H_
#define _NPROxY_H_


#define NPROXY_VERSION "1"
#define DEFAULT_SESSION_TIMEOUT 60
#define NPROXY_CONFIG_FILE "/root/nuri-proxy/nproxy.conf"
#define DELIM "="

#include <time.h>
#include "../ptls/include/ptls.h"

struct instance 
{
	char *listen_host;
	char *listen_port;
	char *backend_host;
	char *backend_port;
	char *cert_file;
	char *private_key_file;
	char *ca_file;
	int daemonize;
	int session_timeout;          /* in seconds */
};

struct ptlsArgs
{
	ptls_session_ctx *sctx;
	struct instance *ins;
	int sd;	/*socket discriptor*/
	time_t create_time;
	time_t comm_time;
	struct ptlsArgs *next; /*next thread*/
};


#endif
