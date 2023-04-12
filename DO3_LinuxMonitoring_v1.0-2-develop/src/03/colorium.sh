#!/bin/bash

white=\\033[97m
back_white=\\033[107m

red=\\033[91m
back_red=\\033[101m

green=\\033[92m
back_green=\\033[102m

blue=\\033[94m
back_blue=\\033[104m

purple=\\033[95m
back_purple=\\033[105m

black=\\033[30m
back_black=\\033[40m

reset_color=\\033[0m
#########################################
case $key_background_color in
	"1")
	color_backkey=$back_white;;
	"2")
	color_backkey=$back_red;;
	"3")
	color_backkey=$back_green;;
	"4")
	color_backkey=$back_blue;;
	"5")
	color_backkey=$back_purple;;
	"6")
	color_backkey=$back_black;;
esac
##########################################
case $key_font_color in
	"1")
	color_key=$white;;
	"2")
	color_key=$red;;
	"3")
	color_key=$green;;
	"4")
	color_key=$blue;;
	"5")
	color_key=$purple;;
	"6")
	color_key=$black;;
esac
###################################
case $value_background_color in
	"1")
	color_valback=$back_white;;
	"2")
        color_valback=$back_red;;
	"3")
        color_valback=$back_green;;
	"4")
        color_valback=$back_blue;;
	"5")
        color_valback=$back_purple;;
	"6")
        color_valback=$back_black;;
esac
#######################################
case $value_font_color in
        "1")
        color_val=$white;;
        "2")
        color_val=$red;;
        "3")
        color_val=$green;;
        "4")
        color_val=$blue;;
        "5")
        color_val=$purple;;
        "6")
        color_val=$black;;
esac
