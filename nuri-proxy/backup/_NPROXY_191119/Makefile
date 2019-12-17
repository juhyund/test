#############################################################
#															#
#				nuri-proxy(nproxy) Makefile					#
#										@author: hyun5		#
#############################################################

CC=g++
TARGET=_NPROXY_
OBJECT=nproxy.o log.o config.o udpComm.o

LDFLAGS ?= -L/root/nuri-proxy/ptls/lib
LOCAL_LDFLAGS = -lm -lptls -lcis_cc -lpthread -lcis_ce
LOCAL_CFLAGS = -I/root/nuri-proxy/ptls/include

PROJECTBIN = /root/nuri-proxy/bin

$(TARGET) : $(OBJECT)
	$(CC) -o $(TARGET) $(OBJECT) $(LOCAL_LDFLAGS) $(LDFLAGS)
	mv $(TARGET) $(PROJECTBIN)

nproxy.o : nproxy.cpp
	$(CC) -c -g -o nproxy.o nproxy.cpp $(LOCAL_CFLAGS)

log.o : log.cpp
	$(CC) -c -g -o log.o log.cpp

config.o : config.cpp
	$(CC) -c -g -p config.cpp config.cpp

udpComm.o : udpComm.cpp
	$(CC) -c -g -o udpComm.o udpComm.cpp

clean:
	rm $(OBJECT)
