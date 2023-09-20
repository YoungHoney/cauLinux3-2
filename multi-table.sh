#!/bin/sh

if [ -z $1 ] || [ -z $2 ]
then
	echo "Invalid Input"
	exit 1

fi

if [ $1 -lt 0 ] || [ $2 -lt 0 ]
then
	echo "Input must be greater than 0"
	exit 1
fi

row=$1
col=$2

for i in $(seq 1 $row)
do
	for j in $(seq 1 $col)
	do
		result=`expr $i \* $j`
		echo -n  "$i*$j=$result \t"
	done
	echo ""
done
#20191155 gwak young hun
exit 0
