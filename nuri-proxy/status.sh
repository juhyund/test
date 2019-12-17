#Check _NPROXY_ 
p_nproxy=$(ps -ef | grep _NPROXY_ | wc -l)
if [ $p_nproxy == 1 ]; then
	echo "_NPROXY_ is not running."
else 
	echo "_NPROXY_ is running."
	ps -ef | grep _NPROXY_
fi

#Check _NTRAP_ 
p_ntrap=$(ps -ef | grep _NTRAP_ |wc -l)
if [ $p_ntrap == 1 ]; then
     echo "_NTRAP_ is not running."
else 
	echo "_NPROXY is running."
	ps -ef | grep _NTRAP_
fi 
