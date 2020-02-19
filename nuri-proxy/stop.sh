

#Killing _NPROXY_ 
p_nproxy=$(ps -ef | grep _NPROXY_ |wc -l)
if [ $p_nproxy == 1 ]; then
	 echo "_NPROXY_ is not running."
else 
	pkill -f _NPROXY_
	p_nproxy=$(ps -ef | grep _NPROXY_ |wc -l)
	sleep .3 
	if [ $p_nproxy -gt  1 ]; then
		echo "Failed to kill _NPROXY_" 
	else
		echo "_NPROXY_ is killed."
	fi
fi


#Killing _NTRAP_ 
p_ntrap=$(ps -ef | grep _NTRAP_ |wc -l)
if [ $p_ntrap == 1 ]; then
     echo "_NTRAP_ is not running."
else 
    pkill -f _NTRAP_
    p_ntrap=$(ps -ef | grep _NTRAP_ |wc -l)
    sleep .3 
    if [ $p_ntrap -gt  1 ]; then
        echo "Failed to kill _NTRAP_" 
    else
        echo "_NTRAP_ is killed."
    fi  
fi 
