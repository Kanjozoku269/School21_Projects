#!/bin/bash

chmod +x check_sys_info.sh
./check_sys_info.sh

while true; do
    read -r -p "Do you wish to write logs? (Y/N): " answer
    case $answer in
        [Yy]* ) chmod +x write_info_to_file.sh; ./write_info_to_file.sh; break;;
        [^Yy]* ) exit;;
        * ) echo "Please answer Y or N.";;
    esac
done
