#!/bin/bash

#$1 jobname $2 job batch $3 batch mode (true) single job mode $4 event number
if [ $3 == "true" ]; then
ls /sphenix/user/xwang97/DPMJET/$1_$2/fort*$4.root > "/sphenix/user/xwang97/DPMJET/$1_$2/$1_$2_files.txt"
else
ls /sphenix/user/xwang97/DPMJET/$1/fort*$4.root > "/sphenix/user/xwang97/DPMJET/$1/$1_files.txt"
fi
