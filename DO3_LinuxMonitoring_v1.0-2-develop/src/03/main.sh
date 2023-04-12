#!/bin/bash

chmod +x check_sys_info.sh
chmod +x colorium.sh
chmod +x print_color_sys_info.sh

if [ $# -ne 4 ]; then
	echo "invalid parametr"
	elif [[ "$1" != [1-6] ]] || [[ "$2" != [1-6] ]] || [[ "$3" != [1-6] ]] || [[ "$4" != [1-6] ]]; then
		echo "invalid range parametr"
		elif [ "$1" -eq "$2" ] || [ "$3" -eq "$4" ]; then
			echo "repick back and font colours"
			else
				export key_background_color=$1
				export key_font_color=$2
				export value_background_color=$3
				export value_font_color=$4
				./print_color_sys_info.sh
fi

