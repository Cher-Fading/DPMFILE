#!/bin/bash

#$1 jobname $2 event number $3 batch mode $4 number of batches

if [ $4 == "true" ]; then
    for ((i = 1; i <= 40; i++)); do
        ls /sphenix/user/xwang97/DPMJET/$1_$i/fort*$3.root >"/sphenix/user/xwang97/DPMJET/$1_$i/$1_$i_files.txt"
        -l wc -l "/sphenix/user/xwang97/DPMJET/$1_$i/$1_$i_files.txt" >>/sphenix/user/xwang97/DPMJET/$1_$3batch_nof.txt
    done
else
    ls /sphenix/user/xwang97/DPMJET/$1/fort*$3.root >"/sphenix/user/xwang97/DPMJET/$1/$1_files.txt"
    -l wc -l "/sphenix/user/xwang97/DPMJET/$1/$1_files.txt" >>/sphenix/user/xwang97/DPMJET/$1_$3nof.txt
fi
