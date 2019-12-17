#ifndef	_MYCONFIG_H_
#define	_MYCONFIG_H_

/*
* Read configuration file
* author hyun5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "/usr/local/etc/raddb/config.conf"
#define MAXBUF 1024 
#define DELIM "="

struct config
{
   char kepfepcert[MAXBUF];
   char kepemucert[MAXBUF];
};

/*get Configuration file*/
struct config get_config(char *filename);

#endif

