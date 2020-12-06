#!/bin/bash
#$1 jobname $2 event number $3 number of batches $4 label
cd /sphenix/user/xwang97/DPMJET/
#use a different condorjob for each batch of $400 simulations
touch ${1}_${2}_nofevt.txt
tot=0
for ((i = 1; i <= $3; i++)); do
    #hadd -f $1_${i}_$2_result$4.root $1_${i}/$1_${i}_*_result$4.root
    num=0
    for entry in $1_${i}/$1_${i}_*_result$4.root
do
#echo $entry
newnum=${entry##*/}
#echo $newnum
newnum=${newnum%'_resultfullcut.root'*}
newnum=${newnum##*_}
#echo $newnum
	num=$((num+newnum))
#echo $num
done
echo "${1} ${i} :$num"
tot=$((tot+num))
echo "${1} ${i} :$num" >> /sphenix/user/xwang97/DPMJET/${1}_${2}_nofevt.txt
    #cat /sphenix/u/xwang97/DPMFILE/dpmCondor$1$i.condor
    #condor_submit /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor
done
#hadd -f $1_batch_$3_$2_result$4.root $1_*_$2_result$4.root
echo "${1} :$tot"
cd /sphenix/u/xwang97/DPMFILE/
#root -b -q -l 'draw.cpp("'$1'", true, 40, "'$2'", "'$4'")'
