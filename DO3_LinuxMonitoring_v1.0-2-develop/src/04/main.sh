#!/bin/bash

source color.conf

function print {
				export key_background_color=$column1_background
                                export key_font_color=$column1_font_color
                                export value_background_color=$column2_background
                                export value_font_color=$column2_font_color
                                chmod +x check_sys_info.sh
                                chmod +x colorium.sh
                                chmod +x print_color_sys_info.sh
                                ./print_color_sys_info.sh
}
############# CHECK FIRST PARAMETR
if [[ -z ${column1_background// } ]]; then
	column1_background=default
else
	if [[ "$column1_background" != [1-6] ]]; then
        	echo "first parametr range is "1-6""
		error=1
	else
		firstisdigit=1
	fi
fi
############# CHECK SECOND PARAMETR AND EQUALIZE WHEN 1 && 2 IS DIGIT
if [[ -z ${column1_font_color// } ]]; then
	 column1_font_color=default
else
	if [[ "$column1_font_color" != [1-6] ]]; then
        	echo "second parametr range is "1-6""
		error=1
        else
		if [ "$firstisdigit" = 1 ]; then
			if [ "$column1_background" -eq "$column1_font_color" ]; then
				echo "1 color in 1 column =/ you dont see info "
				error=1
			fi
		fi
	fi
fi
############# CHECK THIRD PARAMETR
if [[ -z ${column2_background// } ]]; then
	column2_background=default
else
	if [[ "$column2_background" != [1-6] ]]; then
		echo "third parametr range is "1-6""
		error=1
	else
		thirdisdigit=1
	fi
fi
############# CHECK FOURTH PARAMETR
if [[ -z ${column2_font_color// } ]]; then
	column2_font_color=default
else
	if [[ "$column2_font_color" != [1-6] ]]; then
        	echo "fourth parametr range is "1-6""
		error=1
	else
		if [ "$thirdisdigit" = 1 ]; then
			if [ "$column2_background" -eq "$column2_font_color" ]; then
		                echo "1 color in 2 column =/ you dont see info "
				error=1
	                fi
		fi
	fi
fi

if [[ $error -eq 0 ]]; then
	print
else
	exit 1
fi
