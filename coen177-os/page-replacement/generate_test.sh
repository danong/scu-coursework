#!/bin/bash

## Testing script for COEN 177 Lab Assignment 3
## For use with programs that use callng format as follows:
## ./replacement_alg size
## e.g. ./lru 10
##
## Call script using following format:
## /path/to/dir/test_one lru

## Place numbers.txt in same directory as the script 
## Also make sure that lru_faults.txt & lfu_faults.txt are
## also in the script file directory.
##
## While you may test your own page request files, I recommend using my
## provided test files and result files to verify your program
bigFILE=numbers.txt				#page request file

## do not create the following files; they will be created in the script
countFILE=counts.txt			#dummy file to log program output

## Change scriptDIR to path of directory with test files
## **** IF script is located w/in program directory, use ./ ****
scriptDIR=./

## generate count of fault results
for size in 10 50 100 150 200 250 300 350 400 450 500; do
	cat $scriptDIR$bigFILE | ./"$1" $size | grep -o -E [0-9]+ >> "$scriptDIR$countFILE"
done


exit 0
