#Check _NPROXY_ 
p_radius=$(ps -ef | grep radiusd | wc -l)
if [ $p_radius == 1 ]; then
	echo "RADIUS is not running."
else 
	echo "RADIUS is running."
	ps -ef | grep radiusd
fi
