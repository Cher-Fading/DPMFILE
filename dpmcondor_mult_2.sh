#!/bin/bash

#./dpmcondor_mult.sh ep_HERA4 4000 1E4 200
cd /sphenix/u/xwang97/DPMFILE
C=$(($2/$4))
echo $C
#use a different condorjob for each batch of $400 simulations
for ((i=21;i<=(20+C);i++))
do
VAL=$(($i*$4))
mkdir -p /sphenix/user/xwang97/DPMJET/$1_$i/
cp /sphenix/u/xwang97/DPMFILE/dpmcondor.sh /sphenix/u/xwang97/DPMFILE/dpmcondor$1_$i.sh
sed -i "s/^NUM.*/NUM=\$((\$2+${VAL}))/" /sphenix/u/xwang97/DPMFILE/dpmcondor$1_$i.sh
#cat /sphenix/u/xwang97/DPMFILE/dpmcondor$1$i.sh
chmod +x /sphenix/u/xwang97/DPMFILE/dpmcondor$1_$i.sh
cp /sphenix/u/xwang97/DPMFILE/dpmCondor.condor /sphenix/u/xwang97/DPMFILE/dpmCondor$1_$i.condor
sed -i "s@^Executable.*@Executable   = /sphenix/u/xwang97/DPMFILE/dpmcondor${1}_${i}\.\sh@" /sphenix/u/xwang97/DPMFILE/dpmCondor$1_$i.condor
sed -i "s/^Queue.*/Queue ${4}/" /sphenix/u/xwang97/DPMFILE/dpmCondor$1_$i.condor
sed -i "s/^Arguments.*/Arguments       = ${1}_${i} \$(Process) ${3}/" /sphenix/u/xwang97/DPMFILE/dpmCondor$1_$i.condor
#cat /sphenix/u/xwang97/DPMFILE/dpmCondor$1$i.condor

cp /gpfs/mnt/gpfs02/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/$1.inp /gpfs/mnt/gpfs02/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/$1_$i.inp
condor_submit /sphenix/u/xwang97/DPMFILE/dpmCondor$1_$i.condor
done
