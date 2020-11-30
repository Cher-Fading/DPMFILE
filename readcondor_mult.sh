#!/bin/bash
#./readcondor_mult.sh ep_HERA4 1E4 40
#$1 jobname $2 event number $3 number of batches
cd /sphenix/u/xwang97/DPMFILE
input="/sphenix/user/xwang97/DPMJET/$1_$2batch_nof.txt"
#use a different condorjob for each batch of $400 simulations
for ((i = 1; i <= $3; i++)); do
    linenumber=1
    while IFS= read -r line; do
        if [ $i -eq $linenumber ]; then
            num=$line
        fi
        linenumber=$((linenumber + 1))
    done <"$input"

    cp /sphenix/u/xwang97/DPMFILE/readcondor.sh /sphenix/u/xwang97/DPMFILE/readcondor$1_$i.sh
    #cat /sphenix/u/xwang97/DPMFILE/dpmcondor$1$i.sh
    chmod +x /sphenix/u/xwang97/DPMFILE/readcondor$1_$i.sh
    cp /sphenix/u/xwang97/DPMFILE/readCondor.condor /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor
    sed -i "s@^Executable.*@Executable   = /sphenix/u/xwang97/DPMFILE/readcondor${1}_${i}\.\sh@" /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor
    sed -i "s/^Queue.*/Queue ${num}/" /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor
    sed -i "s/^Arguments.*/Arguments       = ${1}_${i} \$(Process) ${2}/" /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor
    #cat /sphenix/u/xwang97/DPMFILE/dpmCondor$1$i.condor

    #condor_submit /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor
done
