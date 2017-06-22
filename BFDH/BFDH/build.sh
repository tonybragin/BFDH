#!/bin/sh

clang -o gen gen.c
clang -o BFDH bfdh.c
./gen 10 10
./BFDH 10 data
clear
echo "\nDATA:\n"
cat data
echo "\n\nSCHEDULE:\n"
cat schedule
read
