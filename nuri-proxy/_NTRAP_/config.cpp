/**
* Author: Hyunoh Shin
* Created : 2019. 2. 14
* Read the configuration file for nproxy.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ntrap.h"
#include "config.h"
#include "log.h"


int isBlank(char ch) 
{
    return ( (ch==0x20) || (ch=='\t') || (ch=='\r') || (ch=='\n') );
}

char *trim( char *s ) 
{
    char *f=s, *e=0, *c=s;

    /* Remove Back Space */
    e=s +(strlen(s)) -1;
    while( isBlank(*e) && s<=e) e--;
    *(e+1)=0;

    /* Remove Front Space */
    while( isBlank(*f) && f<=e) f++;

    /* Spaceless Partial Copy */
    if (s!=f) {
        while(f<=e) *(c++) = *(f++);
        *c=0;
    }

    return s;
}

int setConfig(struct instance *ins)
{
        char readBuff[512];
        char *temp;
		const char *conffile = NTRAP_CONFIG_FILE;

        FILE *fp = NULL;
		fp = fopen (conffile, "r");

        if ( fp ){
                while ( !feof(fp) ) {
                        memset(readBuff, 0, 512);
						char* cfline;
                        if ( fgets(readBuff, 512, fp) == NULL ) {
                                continue;
                        }

                        temp = trim(readBuff);

                        if ( *temp == '#' ) {
                                continue;
                        }

                        if ( strncasecmp(temp, "ListenTrapAddr", strlen("ListenTrapAddr")) == 0 ) {
								cfline = strrchr(temp, '=')+1;
								ins->listen_trap_host = (char*)malloc(strlen(cfline));
								memcpy(ins->listen_trap_host,cfline,strlen(cfline-1));	
                        }

                        if ( strncasecmp(temp, "ListenTrapPort", strlen("ListenTrapPort")) == 0 ) {
                                 cfline = strrchr(temp, '=')+1;
                                 ins->listen_trap_port = (char*)malloc(strlen(cfline));
                                 memcpy(ins->listen_trap_port,cfline,strlen(cfline-1)); 
                        }

                        if ( strncasecmp(temp, "BackendTrapAddr", strlen("BackendTrapAddr")) == 0 ) {
                                 cfline = strrchr(temp, '=')+1;
                                 ins->backend_trap_host = (char*)malloc(strlen(cfline));
                                 memcpy(ins->backend_trap_host,cfline,strlen(cfline-1)); 
                        }

                        if ( strncasecmp(temp, "BackendTrapPort", strlen("BackendTrapPort")) == 0 ) {
                                 cfline = strrchr(temp, '=')+1;
                                 ins->backend_trap_port = (char*)malloc(strlen(cfline));
                                 memcpy(ins->backend_trap_port,cfline,strlen(cfline-1));
                        }
                }
        } else return -1;
        
		log_info("Listen trap host = %s", ins->listen_trap_host);
		log_info("Listen trap port = %s", ins->listen_trap_port);
		log_info("Backend trap host = %s" , ins->backend_trap_host);
		log_info("Backend trap port = %s", ins->backend_trap_port);

		fclose(fp);

        return 1;
}
