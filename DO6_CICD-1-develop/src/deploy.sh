#!/bin/bash

sshpass -p '1' scp src/cat/s21_cat dan@172.24.116.8:/usr/local/bin/
sshpass -p '1' scp src/grep/s21_grep dan@172.24.116.8:/usr/local/bin/

echo $(md5sum src/cat/s21_cat | awk '{print $1}') > diffcat.log
echo $(md5sum src/grep/s21_grep | awk '{print $1}') > diffgrep.log

echo $(sshpass -p '1' ssh dan@172.24.116.8 md5sum /usr/local/bin/s21_cat | awk '{print $1}') > diffremotecat.log
echo $(sshpass -p '1' ssh dan@172.24.116.8 md5sum /usr/local/bin/s21_grep | awk '{print $1}') > diffremotegrep.log

diff -q diffcat.log diffremotecat.log > report.log
diff -q diffgrep.log diffremotegrep.log >> report.log

rm diffcat.log diffgrep.log diffremotecat.log diffremotegrep.log

if [[ $(cat report.log | wc -l) -ne 0 ]]; then 
	echo "FILES IS DIFF"
	exit 1
fi

