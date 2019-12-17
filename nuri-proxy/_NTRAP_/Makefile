#############################################################
#															#
#				nuri-proxy(ntrap) Makefile					#
#										@author: hyun5		#
#############################################################

CC=g++
TARGET=_NTRAP_
OBJECT=ntrap.o log.o config.o

LOCAL_LDFLAGS = -lm -lpthread

PROJECTBIN = /root/nuri-proxy/bin

all: $(TARGET)

clean:
	rm $(OBJECT)

$(TARGET) : $(OBJECT)
	$(CC) -o $(TARGET) $(OBJECT) $(LOCAL_LDFLAGS)
	mv $(TARGET) $(PROJECTBIN)

ntrap.o : ntrap.cpp
	$(CC) -c -g -o ntrap.o ntrap.cpp

log.o : log.cpp
	$(CC) -c -g -o log.o log.cpp

config.o : config.cpp
	$(CC) -c -g -p config.cpp config.cpp
