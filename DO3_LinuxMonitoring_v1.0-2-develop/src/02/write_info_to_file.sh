#!/bin/bash


source <(grep -E '^\w+=' check_sys_info.sh)

filename=$(date +"%d-%m-%y-%H-%M-%S").status

touch "$filename"

echo HOSTNAME = $HOSTNAME >> $filename 
echo TIMEZONE = $timezone >> $filename
echo USER = $USER >> $filename
echo OS = $OSTYPE >> $filename
echo DATE = $date >> $filename
echo UPTIME = $uptime >> $filename
echo UPTIME_SEC = $uptime_sec >> $filename
echo IP = $ip >> $filename
echo MASK = $mask >> $filename
echo GATEWAY = $gateway >> $filename
echo RAM_TOTAL = $ram_total >> $filename
echo RAM_USED = $ram_used >> $filename
echo RAM_FREE = $ram_free >> $filename
echo SPACE_ROOT = $space_root >> $filename
echo SPACE_ROOT_USED = $space_root_used >> $filename
echo SPACE_ROOT_FREE = $space_root_free >> $filename


