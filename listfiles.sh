#!/bin/bash

#$1 jobname $2 job batch $3 job number $4 batch mode (true) single job mode $5 event number
if [ $4 == "true" ]; then
input="/sphenix/user/xwang97/DPMJET/$1_$2/$1_$2_files.txt"
else
input = "/sphenix/user/xwang97/DPMJET/$1/$1_files.txt"