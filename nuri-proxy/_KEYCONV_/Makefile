#############################################################
#															#
#				nuri-proxy(keyconv) Makefile				#
#										@author: hyun5		#
#############################################################

CC=g++
TARGET=_KEYCONV_
OBJECT=keyconv.o log.o

LDFLAGS ?= -L/root/nuri-proxy/ptls/lib
LOCAL_LDFLAGS = -lm -lptls -lcis_cc -lcis_ce
LOCAL_CFLAGS = -I/root/nuri-proxy/ptls/include

PROJECTBIN = /root/nuri-proxy/bin

all: $(TARGET)

clean: 
	rm $(OBJECT)

$(TARGET) : $(OBJECT)
	$(CC) -o $(TARGET) $(OBJECT) $(LOCAL_LDFLAGS) $(LDFLAGS)
	mv $(TARGET) $(PROJECTBIN)

keyconv.o : keyconv.cpp
	$(CC) -c -g -o keyconv.o keyconv.cpp $(LOCAL_CFLAGS)

log.o : log.cpp
	$(CC) -c -g -o log.o log.cpp
