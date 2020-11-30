#!/bin/bash

#$1 jobname $2 event number $3 batch mode $4 number of batches

if [ $3 == "true" ]; then
ls /sphenix/user/xwang97/DPMJET/${1}_1/fort*${2}.root >"/sphenix/user/xwang97/DPMJET/${1}_1/${1}_1_${2}_files.txt"
        < "/sphenix/user/xwang97/DPMJET/${1}_1/${1}_1_${2}_files.txt" wc -l >/sphenix/user/xwang97/DPMJET/${1}_${2}batch_nof.txt
    for ((i = 2; i <= $4; i++)); do
        ls /sphenix/user/xwang97/DPMJET/${1}_${i}/fort*${2}.root >"/sphenix/user/xwang97/DPMJET/${1}_${i}/${1}_${i}_${2}_files.txt"
        < "/sphenix/user/xwang97/DPMJET/${1}_${i}/${1}_${i}_${2}_files.txt" wc -l >>/sphenix/user/xwang97/DPMJET/${1}_${2}batch_nof.txt
    done
else
    ls /sphenix/user/xwang97/DPMJET/${1}/fort*${2}.root >"/sphenix/user/xwang97/DPMJET/${1}/${1}_${2}_files.txt"
    wc -l "/sphenix/user/xwang97/DPMJET/${1}/${1}_files.txt" >/sphenix/user/xwang97/DPMJET/${1}_${2}_nof.txt
fi
