#!/bin/bash

#./dpmcondor_mult.sh ep_HERA4 4000 1E4 200
cd /sphenix/u/xwang97/DPMFILE
C=40
#use a different condorjob for each batch of $400 simulations
for ((i=1;i<=C;i++))
do

cp /sphenix/u/xwang97/DPMFILE/readcondor.sh /sphenix/u/xwang97/DPMFILE/readcondor$1_$i.sh
#cat /sphenix/u/xwang97/DPMFILE/dpmcondor$1$i.sh
chmod +x /sphenix/u/xwang97/DPMFILE/readcondor$1_$i.sh
cp /sphenix/u/xwang97/DPMFILE/readCondor.condor /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor
sed -i "s@^Executable.*@Executable   = /sphenix/u/xwang97/DPMFILE/readcondor${1}_${i}\.\sh@" /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor

sed -i "s/^Queue.*/Queue ${num}/" /sphenix/u/xwang97/DPMFILE/dpmCondor$1_$i.condor
sed -i "s/^Arguments.*/Arguments       = ${1}_${i} \$(Process) ${3}/" /sphenix/u/xwang97/DPMFILE/dpmCondor$1_$i.condor
#cat /sphenix/u/xwang97/DPMFILE/dpmCondor$1$i.condor

cp /gpfs/mnt/gpfs02/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/$1.inp /gpfs/mnt/gpfs02/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/$1_$i.inp
condor_submit /sphenix/u/xwang97/DPMFILE/dpmCondor$1_$i.condor
done
