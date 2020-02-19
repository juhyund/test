#pragma once

#define BUFSIZE 4096


void udpProxyComm(int s/*socket*/, const char* ip, const char* port, unsigned char* buf, int buf_len, unsigned char** rbuf, int* rbuf_len);
int udpSocketCreate();
void updSocketClose(int s/*socket*/);
void hexconvert(char *text, unsigned char bytes[] );
