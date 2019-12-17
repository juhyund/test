

#Killing RADIUS
p_radius=$(ps -ef | grep radiusd |wc -l)
if [ $p_radius == 1 ]; then
	 echo "RADIUS is not running."
else 
	pkill -f radiusd
	p_radius=$(ps -ef | grep radiusd |wc -l)
	sleep .3 
	if [ $p_radius -gt  1 ]; then
		echo "Failed to kill RADIUS" 
	else
		echo "RADIUS is killed."
	fi
fi
