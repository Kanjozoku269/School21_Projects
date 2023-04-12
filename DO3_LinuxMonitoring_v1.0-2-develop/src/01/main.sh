#!/bin/bash

if [ $# -ne 1 ] || [ $# -gt 1 ]; then
	echo "Use 1 argument"
elif [[ $1 =~ ^[+-]?[0-9]+([.][0-9]+)?$ ]]; then
	echo "Only string format with word"
else
	echo $1
fi