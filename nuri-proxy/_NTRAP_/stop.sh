

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
