/bin/bash

echo -e "\nDate: $(date)\nAccount name: $USER"

echo "PC domain name: $(hostname -f)"

echo -e "\nProcessor:\n $(lscpu | grep "Model name")\n $(lscpu | grep Architecture)\n Clock frequency - $(cat /proc/cpuinfo | grep "cpu MHz" | sed s/[^0-9]//g | sed '2, $d') MHz"

echo -e " Number of cores - $(cat /proc/cpuinfo | grep "cpu cores" | wc -l)\n Number of threads per core - $(lscpu | grep Thread | wc -l)\n"

echo "Random access memory:"

echo " Total - $(cat /proc/meminfo | grep "MemTotal:" | sed s/[^0-9]//g) kB"

echo " Available - $(cat /proc/meminfo | grep "MemAvailable:" | sed s/[^0-9]//g) kB"

echo -e "\nHard disk:\n Total - $(df -h / | sed '2!D' | awk '{printf $2}')\n Available - $(df -h / | sed '2!D' | awk '{printf $4}')"

echo " Mounted to the root directory /- $(df -h / | sed '2!D' | awk '{printf $2}')"

echo -e " SWAP total - $(free -h | grep -E 'Swap' | awk '{print $2}')\n SWAP available - $(free -h | grep -E 'Swap' | awk '{print $4}')"

echo -e "\nNetwork interfaces:\n Number of network interfaces - $(ls /sys/class/net | cat -n | tail -1 | awk '{print $1}')"


number=1
printf "| %-2s | %-25s | %-17s | %-10s | %-15s |\n" "#" "Name of network interface" "MAC adress" "IP adress" "Speed conection"
for var in $(ls /sys/class/net)
do
MAC=$(ifconfig $var | grep -E 'ether' | awk '{print $2}') 
IP=$(ifconfig $var | grep -E 'inet ' | awk '{print $2}')
if [ $var != "lo" ] && [ ${#IP} != 0 ];
then
speed=$(speedtest --secure | grep -E '^Download' | awk '{print $2, $3}')
else
speed=' '
fi
printf "| %-2s | %-25s | %-17s | %-10s | %-15s |\n" "$number" "$var" "$MAC" "$IP" "$speed"  
number=$[$number + 1]
done
