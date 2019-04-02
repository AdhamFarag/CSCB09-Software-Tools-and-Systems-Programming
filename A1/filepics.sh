#!/bin/sh
export PATH=$PATH:/courses/courses/cscb09w19/bin
user_path=$1
if [ $# -eq 0 ]
then
echo 'NO DIRECTORY WAS GIVEN TRY AGAIN'>&2
exit 128
elif [ $# -gt 1 ]
then
echo 'CANNOT ACCEPT MORE THAN ONE DIRECTORY'>&2
exit 128
elif [ ! -d $user_path ]
then
echo 'THE DIRECTORY YOU ENTERED IS INVALID'>&2
exit 128
fi
for pics in "$user_path"/*
do
file $pics | grep -q JPEG
if [ $? -eq 0 ]
then
image=$(exiftime -tg "$pics")
does_img_exist=$?
if [ $does_img_exist -ne 0 ]
then
echo $pics' THE IMAGE IS NOT A VALID IMAGE'>&2
else
Date=$(echo "$image"| cut -d ' ' -f 3)
year=$(echo "$Date"| cut -d ':' -f 1)
month=$(echo "$Date"| cut -d':' -f 2)
pic_name=$(echo "$pics"| cut -d '/' -f 2)
mkdir -p "$user_path"/"$year"/"$month"
if [ -d "$user_path"/"$year"/"$month" -a $does_img_exist -eq 0 ]
then
mv -f "$pics" "$user_path"/"$year"/"$month"/"$pic_name"
else
echo $pics' IS NOT A VALID IMAGE'>&2
fi
fi
fi
done
exit 0
