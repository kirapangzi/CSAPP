#!/bin/sh
# Convert list of hexadecimal numbers into decimal

for i in $*
do
	value=$(echo "ibase=16; $i" |bc)
	printf "0x%x\t= %d\n" $value $value
done
