/**
* Author: Hyunoh Shin
* Created : 2019. 2. 14
* Read the configuration file for nproxy.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nproxy.h"
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
		char *conffile = NPROXY_CONFIG_FILE;

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

                        if ( strncasecmp(temp, "ListenAddr", strlen("ListenAddr")) == 0 ) {
								cfline = strrchr(temp, '=')+1;
								ins->listen_host = (char*)malloc(strlen(cfline));
								memcpy(ins->listen_host,cfline,strlen(cfline-1));	
                        }

                        if ( strncasecmp(temp, "ListenPort", strlen("ListenPort")) == 0 ) {
                                 cfline = strrchr(temp, '=')+1;
                                 ins->listen_port = (char*)malloc(strlen(cfline));
                                 memcpy(ins->listen_port,cfline,strlen(cfline-1)); 
                        }

                        if ( strncasecmp(temp, "BackendAddr", strlen("BackendAddr")) == 0 ) {
                                 cfline = strrchr(temp, '=')+1;
                                 ins->backend_host = (char*)malloc(strlen(cfline));
                                 memcpy(ins->backend_host,cfline,strlen(cfline-1)); 
                        }

                        if ( strncasecmp(temp, "BackendPort", strlen("BackendPort")) == 0 ) {
                                 cfline = strrchr(temp, '=')+1;
                                 ins->backend_port = (char*)malloc(strlen(cfline));
                                 memcpy(ins->backend_port,cfline,strlen(cfline-1));
                        }

                        if ( strncasecmp(temp, "CertificateFile", strlen("CertificateFile")) == 0 ) {
                                 cfline = strrchr(temp, '=')+1;
                                 ins->cert_file = (char*)malloc(strlen(cfline));
                                 memcpy(ins->cert_file,cfline,strlen(cfline-1));
                        }
                        if ( strncasecmp(temp, "CertificateKeyFile", strlen("CertificateKeyFile")) == 0 ) {
                                 cfline = strrchr(temp, '=')+1;
                                 ins->private_key_file = (char*)malloc(strlen(cfline));
                                 memcpy(ins->private_key_file,cfline,strlen(cfline-1));
                        }
						if ( strncasecmp(temp, "CACertificateFile", strlen("CACertificateFile")) == 0 ) {
                                  cfline = strrchr(temp, '=')+1;
                                  ins->ca_file = (char*)malloc(strlen(cfline));
                                  memcpy(ins->ca_file,cfline,strlen(cfline-1));
                         }
						if ( strncasecmp(temp, "MaxSessionTime", strlen("MaxSessionTime")) == 0 ) {
                                   cfline = strrchr(temp, '=')+1;
                                   ins->session_timeout = atoi(cfline);
                          }
                }
        } else return -1;
        
		log_info("Listen host = %s", ins->listen_host);
		log_info("Listen port = %s", ins->listen_port);
		log_info("Backend host = %s" , ins->backend_host);
		log_info("Backend port = %s", ins->backend_port);
		log_info("CACertificate file =%s", ins->ca_file);
		log_info("Certificate file = %s", ins->cert_file);
		log_info("CertificateKeyFile =%s", ins->private_key_file);
		log_info("Max session time =%i", ins->session_timeout);

		fclose(fp);

        return 1;
}
