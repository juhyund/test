/**
* Author : Hyunoh Shin
* Created : 2019. 2. 18
* Udp communication with Radius Server to send and receive packets. 
* The received packets are sent to the Radius Client via dtls communication. (from nproxy) 
*
*/

#include "udpComm.h"
#include "log.h"
#include "../ptls/include/ptls.h"

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


void udpProxyComm(int s, const char* ip, const char* port, unsigned char* buf, int buf_len, unsigned char** rdbuf, int *rbuf_len) 
{
	socklen_t slen;
	struct sockaddr_in servAddr, locAddr, fromAddr;

	int sentSize = 0;
	const char eof = 0x1A;
	unsigned char rbuf[PTLS_SSL_MAX_CONTENT_LEN];
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(port));

	memset(&locAddr, 0, sizeof(locAddr));
	locAddr.sin_family = AF_INET;
	locAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	locAddr.sin_port = htons(9898);

	slen = sizeof(servAddr);

	log_info("Backend Server = %s:%s", ip, port);
	// assert(-1 != bind(s, (const struct sockaddr*)&locAddr, sizeof(locAddr)));
	int r = bind(s, (const struct sockaddr*)&locAddr, sizeof(locAddr));


	//Send msg to Backend Server
	sendto(s, buf, buf_len, 0, (const struct sockaddr*)&servAddr, slen);
	log_info("radius server <- proxy :: %i Bytes data sent.", buf_len);
	printf("\n SEND PACKET[%i] \n", buf_len);
	for(int i=0; i < buf_len; i++) printf("%02X ", (unsigned int)buf[i]);
	printf(" \n\n\n ");


	*rbuf_len = recvfrom(s, rbuf, sizeof(rbuf), 0, NULL, &slen);
	log_info("radius server -> proxy :: %i Byte data received.", *rbuf_len);

	printf("\n RECIEVE PACKET[%i] \n", *rbuf_len);
	for(int i=0; i < *rbuf_len; i++) printf("%02X ", (unsigned int)rbuf[i]);
	printf(" \n\n\n ");

	//Copy received buff
	*rdbuf = (unsigned char *)malloc(*rbuf_len);
	memcpy(*rdbuf, rbuf, *rbuf_len);

}

void hexconvert(char *text, unsigned char bytes[] )
{
    int i;
    int temp;

    for( i = 0; i < 4; ++i ) {
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
