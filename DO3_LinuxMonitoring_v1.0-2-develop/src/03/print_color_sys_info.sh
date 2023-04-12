#!/bin/bash

source check_sys_info.sh
source colorium.sh

echo -e $color_key$color_backkey"HOSTNAME"$reset_color = $color_val$color_valback$HOSTNAME$reset_color
echo -e $color_key$color_backkey"TIMEZONE"$reset_color = $color_val$color_valback$timezone$reset_color
echo -e $color_key$color_backkey"USER"$reset_color = $color_val$color_valback$USER$reset_color
echo -e $color_key$color_backkey"OSTYPE"$reset_color = $color_val$color_valback$OSTYPE$reset_color
echo -e $color_key$color_backkey"DATE"$reset_color = $color_val$color_valback$date$reset_color
echo -e $color_key$color_backkey"UPTIME"$reset_color = $color_val$color_valback$uptime$reset_color
echo -e $color_key$color_backkey"UPTIME_SEC"$reset_color = $color_val$color_valback$uptime_sec$reset_color
echo -e $color_key$color_backkey"IP"$reset_color = $color_val$color_valback$ip$reset_color
echo -e $color_key$color_backkey"MASK"$reset_color = $color_val$color_valback$mask$reset_color
echo -e $color_key$color_backkey"GATEWAY"$reset_color = $color_val$color_valback$gateway$reset_color
echo -e $color_key$color_backkey"RAM_TOTAL"$reset_color = $color_val$color_valback$ram_total$reset_color
echo -e $color_key$color_backkey"RAM_USED"$reset_color = $color_val$color_valback$ram_used$reset_color
echo -e $color_key$color_backkey"RAM_FREE"$reset_color = $color_val$color_valback$ram_free$reset_color
echo -e $color_key$color_backkey"SPACE_ROOT"$reset_color = $color_val$color_valback$space_root$reset_color
echo -e $color_key$color_backkey"SPACE_ROOT_USED"$reset_color = $color_val$color_valback$space_root_used$reset_color
echo -e $color_key$color_backkey"SPACE_ROOT_FREE"$reset_color = $color_val$color_valback$space_root_free$reset_color
