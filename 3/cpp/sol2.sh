#!/bin/bash


grep -e 'mul([0-9]\+,[0-9]\+)' -e "don't()" -e "do()" -o $1 > tmp.txt
sed -e "s/mul(\([0-9]\+\),\([0-9]\+\))/\1 \2/gp" tmp.txt > out
cat out | ./adder

