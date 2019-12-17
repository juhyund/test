#############################################################
#															#
#				nuri-proxy(nproxy) Makefile					#
#										@author: hyun5		#
#############################################################

CC=g++
TARGET=nproxy
OBJECT=nproxy.o log.o config.o udpComm.o

LDFLAGS ?= -L/root/nuri-proxy/ptls/lib
LOCAL_LDFLAGS = -lm -lptls -lcis_cc -lpthread
LOCAL_CFLAGS = -I/root/nuri-proxy/ptls/include

$(TARGET) : $(OBJECT)
	$(CC) -o $(TARGET) $(OBJECT) $(LOCAL_LDFLAGS) $(LDFLAGS)

nproxy.o : nproxy.cpp
	$(CC) -c -g -o nproxy.o nproxy.cpp $(LOCAL_CFLAGS)

log.o : log.cpp
	$(CC) -c -g -o log.o log.cpp

config.o : config.cpp
	$(CC) -c -g -p config.cpp config.cpp

udpComm.o : udpComm.cpp
	$(CC) -c -g -o udpComm.o udpComm.cpp

clean:
	rm $(OBJECT) $(TARGET)
