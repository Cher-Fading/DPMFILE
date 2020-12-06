#!/bin/bash
#./dpmcondor_mult.sh ep_HERA4 40000 1E4 2000
cd /sphenix/u/xwang97/DPMFILE
C=$(($2/$4))
echo $C
#use a different condorjob for each batch of $400 simulations
for ((i = 1; i <= $C; i++)); do
    cp /sphenix/u/xwang97/DPMFILE/readCondor.condor /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
    sed -i "s/^Queue.*/Queue ${4}/" /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
    sed -i "s/^Arguments.*/Arguments       = ${1}_${i} \$(Process) ${3} ${VAL}/" /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
    #cat /sphenix/u/xwang97/DPMFILE/readCondor${1}_${i}.condor
    condor_submit /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
done

