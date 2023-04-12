#!/bin/bash

#TIMEZONE
timezone=$(timedatectl | grep "Time zone" | awk '{print$3}'; date +%:::z )

#DATE
date=$(date | awk '{print$2,$3,$4,$5}')

#UPTIME
uptime=$(uptime -p)

#UPTIME IN SECONDS
uptime_sec=$(cat /proc/uptime | awk '{print $1}')

#IP
ip=$(ifconfig enp0s3 | grep netmask | awk '{print $2}')

#MASK
mask=$(ifconfig enp0s3 | grep netmask | awk '{print $4}')

#GATEWAY
gateway=$(ip r | grep default | awk '{print $3}')

#RAM IN GB
ram_total=$(free | grep Mem | awk '{kbyte =$2 /1024/1024; printf("%.3f GB", kbyte)}')
ram_used=$(free | grep Mem | awk '{kbyte =$3 /1024/1024; printf("%.3f GB", kbyte)}')
ram_free=$(free | grep Mem | awk '{kbyte =$4 /1024/1024; printf("%.3f GB", kbyte)}')

#SPACE ROOT IN MB
space_root=$(df /root | grep dev | awk '{kb = $2 /1024; printf("%.2f MB\n", kb)}')
space_root_used=$(df /root | grep dev | awk '{kb = $3 /1024; printf("%.2f MB\n", kb)}')
space_root_free=$(df /root | grep dev | awk '{kb = $4 /1024; printf("%.2f MB\n", kb)}')

