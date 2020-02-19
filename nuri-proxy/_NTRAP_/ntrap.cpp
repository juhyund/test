/**
* Author : Hyunoh Shin
* Created : 2019. 11. 25
* Security Issue Notification Trap listener
*
*/

#include "ntrap.h"
#include "log.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>


int main()
{
	struct instance ins;
	int ret;
	
	log_stderr_open(LOG_INFO);
	log_info("_NTRAP_ is started.");
	log_info("ntrap config file  = %s", NTRAP_CONFIG_FILE);
	if ( ! (ret=setConfig(&ins)) )
	{
		log_error("Read Config file FAILD !!");
		return ret;
	}
	SecTrapListener(ins.listen_trap_host, ins.listen_trap_port, ins.backend_trap_host, ins.backend_trap_port);



	return 0;
}



void SecTrapListener(const char* lip, const char* lport, const char* bip, const char* bport) 
{
	int s, r, recvlen;
	struct sockaddr_in fepAddr, locAddr, cliAddr;
	socklen_t cliaddrlen = sizeof(cliAddr);
	unsigned char recvbuf[1024];

	// Backend Server (Fep Server)	
	memset(&fepAddr, 0, sizeof(fepAddr));
	fepAddr.sin_family = AF_INET;
	fepAddr.sin_addr.s_addr = inet_addr(bip);
	fepAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	fepAddr.sin_port = htons(atoi(bport));

	// Listen Server
	memset(&locAddr, 0, sizeof(locAddr));
	locAddr.sin_family = AF_INET;
	locAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	locAddr.sin_port = htons(10000);


	s = socket ( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

	if( (r = bind(s, (const struct sockaddr*)&locAddr, sizeof(locAddr))) < 0 )
	{
		log_error(" r = %d" ,r );
	}

	while(true)
	{
		recvlen = recvfrom( s, recvbuf, 1024, 0, (sockaddr*)&cliAddr, &cliaddrlen );
		log_info("RECEIVE Trap Packet [%d] ", recvlen);
		for(int i=0; i < recvlen; i++) printf("%02X ", (unsigned int)recvbuf[i]);
		//trapParser(recvbuf, recvlen);
		log_info("RECEIVE Trap Packet End");
	}


	return;
}

void trapParser(void* args)
{
	// parser code

	return;
}

void hexconvert(char *text, unsigned char bytes[] )
{
    int i;
    int temp;

    for( i = 0; i < 4; ++i ) 
	{
        sscanf( text + 2 * i, "%2x", &temp );
        bytes[i] = temp;
    }
}


int udpSocketCreate()
{
	int s/*socket*/;

	assert(-1 != (s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)));
	log_info("Socket has been created. [Socket Discriptor = %d]", s);
	
	return s;
}

void updSocketClose(int s)
{
	close(s);
	log_info("Socket has been closed. [Socket Discriptor = %d]", s);

}
