#!/bin/bash

cd src/cat/
make style
cd ../grep/
make style

if [[ $(cat ../style.log | wc -l) -eq 0 ]]; then
	echo "style is ok!"
	exit 0
else
	cat ../style.log
	rm ../style.lo*
	exit 1
fi	