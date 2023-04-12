#!/bin/bash

source colorium_portable.sh

setup_color=($blue)
setup_back_color=($back_white)

foldername=($top5_NAME_folders)
foldersize=($top5_SIZE_folders)
filename=($top10_NAME_files)
filesize=($top10_SIZE_files)
filetype=($top10_TYPE_files)
exename=($top10_EXECUTABLE_NAME_files)
exesize=($top10_EXECUTABLE_SIZE_files)

echo -e $setup_color$setup_back_color"Total number of folders (including all nested ones) = $allfolders"$reset_color

#Top 5 folders with the highest weight in descending order (path and size)
echo -e  $setup_color$setup_back_color"TOP 5 folders with highest weight in descending order (path and size) :"$reset_color

i=1
while [ "$i" -lt "6" ]; do
echo -e "$setup_color$setup_back_color$i - ${foldername[i]} ${foldersize[i]}"$reset_color
i=$(( $i+1 ))
done

echo -e $setup_color$setup_back_color"Total number of files = $allfiles"$reset_color

echo -e $setup_color$setup_back_color"Number of  :"$reset_color

echo -e $setup_color$setup_back_color"Configuration files (with the .conf extension) = $all_CONF_files"$reset_color
echo -e $setup_color$setup_back_color"Text files = $all_TXT_files"$reset_color
echo -e $setup_color$setup_back_color"Executable files = $all_EXECUTABLE_files"$reset_color
echo -e $setup_color$setup_back_color"Log files (with the extension .log) = $all_LOG_files"$reset_color
echo -e $setup_color$setup_back_color"Archive files = $all_ARCHIVE_files"$reset_color
echo -e $setup_color$setup_back_color"Symbolic links = $all_LINK_files"$reset_color

echo -e $setup_color$setup_back_color"TOP 10 files of maximum size arranged in descending order (path, size and type) :"$reset_color

j=1
while [ "$j" -lt "11" ]; do
filetype=$(file ${filename[j]} | awk '{print $3}')
echo -e $setup_color$setup_back_color"$j - ${filename[j]} ${filesize[j]} $filetype"$reset_color
j=$(( $j+1 ))
done

echo -e $setup_color$setup_back_color"TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file) :"$reset_color

k=1
while [ "$k" -lt "11" ]; do
exemd5hash=$(md5sum ${exename[k]} | awk '{print $1}' )
echo -e $setup_color$setup_back_color"$k - ${exename[k]}, ${exesize[k]}, $exemd5hash"
k=$(( $k+1 ))
done

elapsedtime=$(python3 -c "print(($finish-$start)/1000000000)")
echo -e $setup_color$setup_back_color"Script execution time (in seconds) = $elapsedtime sec."$reset_color
