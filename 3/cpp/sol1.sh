#!/bin/bash


grep 'mul([0-9]\+,[0-9]\+)' -o $1 > tmp.txt
sed -n -e "s/mul(\([0-9]\+\),\([0-9]\+\))/\1 \2/gp" tmp.txt | ./adder

