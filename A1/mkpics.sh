#!/bin/sh
counter=0
if [ $# -eq 0 ]
then
echo 'INPUT VALID PARAMETERS'>&2
exit 128
elif [ $# -gt 0 ]
then
col_num=$1
colomn_value=`expr $1 + 10`
if [ $? -ne 0 ]
then
echo 'COLOMN NUMBER SHOULD BE INTEGER'>&2
exit 128
fi
if [ $# -lt 2 ]
then
echo 'INVALID ARGUMENTS NUMBER'>&2
exit 128
fi
num_of_pics=`expr $# - 1`
add_extra_tr=0
echo '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">' 
echo '<html>'
echo '<head>'
echo '<title>Pictures</title>'
echo '</head>'
echo '<body>'
echo '<h1>Pictures</h1>'
fi
if [ $col_num -eq 0 ]
then
echo '</body>'
echo '</html>'
exit 0
elif [ $col_num -gt 0 ]
then
echo '<table>'
shift
for pics in "$@"
do
file $pics | grep -q JPEG
if [ $? -eq 0 ]
then
if [ $counter -eq 0 ]
then
echo '<tr>'
add_extra_tr=`expr $add_extra_tr + 1`
fi
echo  '<td><img src='"\""$pics"\""' height=100></td>'
counter=`expr $counter + 1`
if [ $counter -eq $col_num ]
then
echo '</tr>'
add_extra_tr=`expr $add_extra_tr - 1`
counter=0
fi
fi
done
fi
if [ $add_extra_tr -ne 0 ]
then 
echo '</tr>'
fi
echo '</table>'
echo '</body>'
echo '</html>'
