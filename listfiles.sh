#!/bin/bash

#$1 jobname $2 job batch $3 job number $4 batch mode (true) single job mode $5 event number
for ((i=1;i<=40;i++)); do
if [ $4 == "true" ]; then
ls /sphenix/user/xwang97/DPMJET/$1_$2/fort*.root > "/sphenix/user/xwang97/DPMJET/$1_$2/$1_$2_files.txt"
else
ls /sphenix/user/xwang97/DPMJET/$1/fort*.root > "/sphenix/user/xwang97/DPMJET/$1/$1_files.txt"
fi
done