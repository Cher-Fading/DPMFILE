#!/bin/bash
#./readcondor_mult.sh ep_HERA4 1E4 40
#$1 jobname $2 event number $3 number of batches
cd /sphenix/u/xwang97/DPMFILE
#use a different condorjob for each batch of $400 simulations
for ((i = 1; i <= $3; i++)); do
    if [ $3 > 1 ]; then
        ls /sphenix/user/xwang97/DPMJET/${1}_${i}/fort*${2}.root >"/sphenix/user/xwang97/DPMJET/${1}_${i}/${1}_${i}_${2}_files.txt"
shopt -s nullglob
numfiles=(/sphenix/user/xwang97/DPMJET/${1}_${i}/fort*${2}.root)
num=${#numfiles[@]}
       # num=$(find | wc -l "/sphenix/user/xwang97/DPMJET/${1}_${i}/fort*${2}.root" | wc -l)
        echo $num
        if [ $i == 1 ]; then
            echo $num >"/sphenix/user/xwang97/DPMJET/${1}_${2}batch_nof.txt"
        else
            echo $num >>"/sphenix/user/xwang97/DPMJET/${1}_${2}batch_nof.txt"
        fi
    else
        ls /sphenix/user/xwang97/DPMJET/${1}/fort*${2}.root >"/sphenix/user/xwang97/DPMJET/${1}/${1}_${2}_files.txt"
        shopt -s nullglob
numfiles=(/sphenix/user/xwang97/DPMJET/${1}/fort*${2}.root)
num=${#numfiles[@]}
        echo $num
        echo $num >"/sphenix/user/xwang97/DPMJET/${1}_${2}batch_nof.txt"
    fi
    cp /sphenix/u/xwang97/DPMFILE/readCondor.condor /sphenix/u/xwang97/DPMFILE/readCondor${1}_${i}.condor
    sed -i "s/^Queue.*/Queue ${num}/" /sphenix/u/xwang97/DPMFILE/readCondor${1}_${i}.condor
    sed -i "s/^Arguments.*/Arguments       = ${1}_${i} \$(Process) ${2}/" /sphenix/u/xwang97/DPMFILE/readCondor${1}_${i}.condor
    #cat /sphenix/u/xwang97/DPMFILE/readCondor${1}_${i}.condor
    condor_submit /sphenix/u/xwang97/DPMFILE/readCondor${1}_${i}.condor
done
