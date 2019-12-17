nohup radiusd -X >> /root/freeradius-server-3.0.17/log/radius-$(date '+%Y-%m-%d').log &
echo "RADIUS is started."
