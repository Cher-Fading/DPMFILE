#!/bin/bash
#$1 jobname $2 event number $3 number of batches $4 label
cd /sphenix/user/xwang97/DPMJET/
#use a different condorjob for each batch of $400 simulations
for ((i = 1; i <= $3; i++)); do
    hadd $1_$i/$1_$i_$2_result$4.root $1_$i/$1_$i_*_result$4.root
    #cat /sphenix/u/xwang97/DPMFILE/dpmCondor$1$i.condor
    #condor_submit /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor
done
hadd $1_$2_result$4.root $1_$i/$1_$i_$2_result$4.root