#!/bin/bash

#$1 jobname $2 event number $3 batch mode $4 number of batches

if [ $3 == "true" ]; then
ls /sphenix/user/xwang97/DPMJET/$1_1/fort*$2.root >"/sphenix/user/xwang97/DPMJET/$1_1/$1_1_$2_files.txt"
        < "/sphenix/user/xwang97/DPMJET/$1_1/$1_1_$2_files.txt" wc -l >/sphenix/user/xwang97/DPMJET/$1_$2batch_nof.txt
    for ((i = 2; i <= $4; i++)); do
        ls /sphenix/user/xwang97/DPMJET/$1_$i/fort*$2.root >"/sphenix/user/xwang97/DPMJET/$1_$i/$1_$i_$2_files.txt"
        < "/sphenix/user/xwang97/DPMJET/$1_$i/$1_$i_$2_files.txt" wc -l >>/sphenix/user/xwang97/DPMJET/$1_$2batch_nof.txt
    done
else
    ls /sphenix/user/xwang97/DPMJET/$1/fort*$2.root >"/sphenix/user/xwang97/DPMJET/$1/$1_$2_files.txt"
    wc -l "/sphenix/user/xwang97/DPMJET/$1/$1_files.txt" >/sphenix/user/xwang97/DPMJET/$1_$2_nof.txt
fi
