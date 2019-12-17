#############################################################
#															#
#				nuri-proxy(nproxy) Makefile					#
#										@author: hyun5		#
#############################################################

CC=gcc
TARGET=nproxy
OBJECT=nproxy.o log.o config.o udpComm.o

LDFLAGS ?= -L/root/nuri-proxy/ptls/lib
LOCAL_LDFLAGS = -lm -lptls -lcis_cc -lpthread
LOCAL_CFLAGS = -I/root/nuri-proxy/ptls/include

$(TARGET) : $(OBJECT)
	$(CC) -o $(TARGET) $(OBJECT) $(LOCAL_LDFLAGS) $(LDFLAGS)

nproxy.o : nproxy.c
	$(CC) -c -o nproxy.o nproxy.c $(LOCAL_CFLAGS)

log.o : log.c
	$(CC) -c -o log.o log.c

config.o : config.c
	$(CC) -c -p config.c config.c

udpComm.o : udpComm.c
	$(CC) -c -o udpComm.o udpComm.c

clean:
	rm $(OBJECT) $(TARGET)
