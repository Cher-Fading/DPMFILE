#!/bin/bash
#./dpmcondor_mult.sh ep_HERA4 40000 1E4 2000
cd /sphenix/u/xwang97/DPMFILE
C=$(($2/$4))
echo $C
#use a different condorjob for each batch of $400 simulations
for ((i = 1; i <= $C; i++)); do
    #rm -rf /sphenix/user/xwang97/DPMJET/${1}_${i}
    cp /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/${1}.inp /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/${1}_${i}.inp
    cp /sphenix/u/xwang97/DPMFILE/dpmreadCondor.condor /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
sed -i "s@^Executable.*@Executable   = /sphenix/u/xwang97/DPMFILE/dpmandread_EIC\.\sh@" /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
    sed -i "s/^Queue.*/Queue ${4}/" /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
    VAL=$((${4}*${i}))
    sed -i "s/^Arguments.*/Arguments       = ${1}_${i} \$(Process) ${3} ${VAL}/" /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
    #cat /sphenix/u/xwang97/DPMFILE/readCondor${1}_${i}.condor
    condor_submit /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
done

