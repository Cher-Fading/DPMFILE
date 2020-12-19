#!/bin/bash
#$1 jobname $2 event number $3 number of batches $4 label
cd /sphenix/user/xwang97/DPMJET/
#use a different condorjob for each batch of $400 simulations
touch ${1}_${2}_nofevt.txt
tot=0
for ((i = 1; i <= $3; i++)); do
    #Shadd -f $1_${i}_${2}_result$4.root $1_${i}/$1_${i}_*_${2}_*_result$4.root
    num=0
passednum=0
    for entry in $1_${i}/$1_${i}_*_${2}_*_result$4.root
do
#echo $entry
name=${entry##*/}
#echo $name
passednew=${name%"_result$4.root"*}
#echo $passednew
passednew=${passednew##*_}
#echo $passednew
newnum=${name%"_${2}_${passednew}_result$4.root"*}
#echo $newnum
newnum=${newnum##*_}
#echo $newnum
	num=$((num+newnum))
passednum=$((passednum+passednew))
#exit
#echo $num
done
tot=$((tot+num))
passed=$((passed+passednum))
echo "${1} ${i} total:$num"
echo "${1} ${i} total:$num" >> /sphenix/user/xwang97/DPMJET/${1}_${2}_nofevt.txt
echo "${1} ${i} passed:$passednum"
echo "${1} ${i} passed:$passednum" >> /sphenix/user/xwang97/DPMJET/${1}_${2}_nofevt.txt
    #cat /sphenix/u/xwang97/DPMFILE/dpmCondor$1$i.condor
    #condor_submit /sphenix/u/xwang97/DPMFILE/readCondor$1_$i.condor
done
#hadd -f ${1}_${2}_batch_${3}_result$4.root ${1}_*_${2}_result$4.root
echo "${1} total:$tot"
echo "${1} passed:$passed"
echo "${1} total:$tot">>${1}_${2}_nofevt.txt
echo "${1} passed:$passed">>${1}_${2}_nofevt.txt
cd /sphenix/u/xwang97/DPMFILE/
root -b -q -l 'draw.cpp("'$1'", true, '$3', "'$2'", "'$4'",'$5','$6','$7','$8','$9')'
