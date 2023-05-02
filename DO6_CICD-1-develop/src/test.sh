#!/bin/bash

cd src/cat/
make testfunc
cd ../grep/
make testfunc

if [[ $(cat ../testfunc_cat.log | tail -3 | grep SUCCESS | awk '{print $2}' | cut -c1-3) != 526 ]]; then
	cat ../testfunc_cat.log
	rm ../testfunc_cat.log
	exit 1
elif [[ $(cat ../testfunc_grep.log | tail -3 | grep SUCCESS | awk '{print $2}' | cut -c1-3) != 787  ]];then
	cat ../testfunc_grep.log
	rm ../testfunc_grep.log
	exit 1
else 
	rm ../testfunc_cat.log
	rm ../testfunc_grep.log
	echo "test is ok"	
fi	