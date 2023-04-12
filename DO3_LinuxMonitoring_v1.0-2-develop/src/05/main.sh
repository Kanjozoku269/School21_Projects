#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Error arg"
	exit 1
	elif [[ "${1: -1}" != "/" ]]; then
        	echo "Wrong path!"
        	exit 1
		else 
			export start=$(date +%S%N)
			#Total number of folders, including nested
			export allfolders=$(find "$1" -type d | wc -l)

			#Top 5 folders with the highest weight in descending order (path and size)
			export top5_NAME_folders=$(du -h "$1" | sort -rh | head -6 | awk '{print $2}')
			export top5_SIZE_folders=$(du -h "$1" | sort -rh | head -6 | awk '{print $1}')


			#Total number of files
			export  allfiles=$(find "$1" -type f | wc -l)

			#The number of configuration files (with the .conf extension), text files, executable files, logs (files with the .log extension), archives, symbolic links
			export all_CONF_files=$(find "$1" -type f -name \*.conf | wc -l)

			export all_TXT_files=$(find "$1" -type f -name \*.txt | wc -l)

			export all_EXECUTABLE_files=$(find "$1" -type f -executable | wc -l)

			export all_LOG_files=$(find "$1" -type f -name \*.log | wc -l)

			export all_ARCHIVE_files=$(find "$1" -type f -name \*.zip | wc -l)

			export all_LINK_files=$(find "$1" -type l | wc -l)
			#Top 10 files with the highest weight in descending order (path, size and type)
			export top10_NAME_files=$(find "$1" -type f -exec du -h {} + | sort -rh | head -11 | awk '{print $2}')
			#export top10_TYPE_files=$(find "$1" -type f -exec du -h {} + | sort -rh | head -11 | awk -F '.' '{print $8}')
			export top10_SIZE_files=$(find "$1" -type f -exec du -h {} + | sort -rh | head -11 | awk '{print $1}')
			#Top 10 executable files with the highest weight
			export top10_EXECUTABLE_NAME_files=$(find "$1" -type f -executable -exec du -h {} + | sort -rh | head -11 | awk '{print $2}')
			export top10_EXECUTABLE_SIZE_files=$(find "$1" -type f -executable -exec du -h {} + | sort -rh | head -11 | awk '{print $1}')
			#Script execution time
			export finish=$(date +%S%N)

			chmod +x printmonitoringinfo.sh
			./printmonitoringinfo.sh

fi
