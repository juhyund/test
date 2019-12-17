#!/bin/sh

export LD_LIBRARY_PATH=./lib
#export LD_LIBRARY_PATH=/usr/local/nuri-ssl/lib


# DTLS off
#/usr/local/nuri-ssl/bin/kepco -d 0 -c /usr/local/nuri-ssl/etc -r /usr/local/nuri-ssl/bin -s off -k on

# DTLS on
#./kepco -d 5 -c ../etc -r ./ -n 0

# DTLS on with non cipherd config file
#./kepco -d 0 -c ../etc -r ./data -s on -n 0
#./kepco -d 0 -c ./ -r ./data -s on -n 0 -k 0
./kepco_nondecpkey -d 0 -c ./ -r ./data -s on -n 0 -k 0

# DTLS off with non cipherd config file
#./kepco -d 0 -c ../etc -r ../bin -s off -n 0
