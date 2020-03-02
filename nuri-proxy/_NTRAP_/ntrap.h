#ifndef _NTRAP_H_
#define _NTRAP_H_


#define NTRAP_VERSION "1"
#define DEFAULT_SESSION_TIMEOUT 60
#define NTRAP_CONFIG_FILE "/root/nuri-proxy/nproxy.conf"
#define DELIM "="

#include <time.h>
#include "../ptls/include/ptls.h"

/*UDP Trap Listnter*/
void SecTrapListener(const char* lip, const char* lport, const char* bip, const char* bport);

/*Trap Parser*/
void trapParser(void* args);

struct instance 
{
	char *listen_trap_host;
	char *listen_trap_port;
	char *backend_trap_host;
	char *backend_trap_port;
};

struct trapifno
{
	unsigned char buff[1024];
	int buflen;
};


#endif
