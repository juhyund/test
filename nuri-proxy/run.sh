#!/bin/sh

export LD_LIBRARY_PATH=/root/nuri-proxy/ptls/lib

LOGDIR=/root/nuri-proxy/log

nohup /root/nuri-proxy/bin/_NPROXY_ >> $LOGDIR/nproxy.log 2>&1&
echo "run _NPROXY_"
sleep .3
nohup /root/nuri-proxy/bin/_NTRAP_ >> $LOGDIR/ntrap.log 2>&1&
echo "run _NTRAP_"

sleep .5
