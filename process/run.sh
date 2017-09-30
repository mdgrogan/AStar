#!/bin/bash
for i in `seq 1 100`;
do
    ./main 10000 $1 $2
done
mv H2.txt H2_$1$2.txt
