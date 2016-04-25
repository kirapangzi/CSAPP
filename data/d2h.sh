#!/bin/sh
# Convert list of decimal numbers into hex

for i in $*
do
	printf "%d\t= 0x%x\n" $i $i
done

