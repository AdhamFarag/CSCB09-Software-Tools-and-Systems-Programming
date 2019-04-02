#!/bin/sh
col=$1
dir=$2
tr=0
counter=0
if [ ! -d $dir ]
then
echo "THE DIRCTORY YOU ENTERED IS NOT VALID">&2
exit 128
fi
if [ $# -ne 2 ]
then
echo "INVALID NUMBER OF PARAMETERS">&2
exit 128
fi
if echo "$col" | grep -q "[a-zA-Z]";
then
echo "INVALID VALUE ENTERED">&2
exit 128
fi
echo  '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">'
echo  '<html>'
echo  '<head>'
echo  '<title>Pictures</title>'
echo  '</head>'
echo  '<body>'
echo  '<h1>Pictures</h1>'
if [ $col -eq 0 ]
then
echo '</body>'
echo '</html>'
else
for years in $dir/*
do
counter=0
echo '<h2>'$years'</h2>'
echo '<table>'
for months in $years/*
do
for img in $months/*
do
if [ $counter -eq 0 ]
then
echo '<tr>'
tr=`expr $tr + 1`
fi
echo '<td><img src='"\""$img"\""' height=100></td>'
counter=`expr $counter + 1`
if [ $counter -eq $col ]
then
echo '</tr>'
tr=`expr $tr - 1`
counter=0
fi
done
if [ $tr -ne 0 ]
then
echo '</tr>'
fi
echo '</table>'
done
done
echo '</body>'
echo '</html>'
fi
