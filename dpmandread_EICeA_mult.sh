#!/bin/bash
#./dpmcondor_mult.sh ep_HERA4 40000 1E4 2000 1 20 400 0
cd /sphenix/u/xwang97/DPMFILE
C=$(($2/$4))
D=$(($8/$4))
echo $C'+'$D
cp /sphenix/u/xwang97/DPMFILE/read_condor.cxx /sphenix/u/xwang97/DPMFILE/read_condor${1}.cxx
sed -i "s/^void read_condor/void read_condor${1}/" /sphenix/u/xwang97/DPMFILE/read_condor${1}.cxx
cp /sphenix/u/xwang97/DPMFILE/dpmandread_EICeA.sh /sphenix/u/xwang97/DPMFILE/dpmandread_${1}.sh
sed -i "s@^root -b -q -l.*@root -b -q -l \'read_condor${1}.cxx(\"\'/sphenix/user/xwang97/DPMJET/\${1}/fort_\${1}_\${2}_\${3}\.root\'\", 0, false, \"fullcut\", ${5}, ${6},${7})'@" /sphenix/u/xwang97/DPMFILE/dpmandread_${1}.sh
chmod +x /sphenix/u/xwang97/DPMFILE/dpmandread_${1}.sh
#use a different condorjob for each batch of $400 simulations
for ((i = $(($D+1)); i <= $(($C+$D)); i++)); do
echo $i
    #rm -rf /sphenix/user/xwang97/DPMJET/${1}_${i}
    cp /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/${1}.inp /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/${1}_${i}.inp
    cp /sphenix/u/xwang97/DPMFILE/dpmreadCondor.condor /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
sed -i "s@^Executable.*@Executable   = /sphenix/u/xwang97/DPMFILE/dpmandread_${1}\.\sh@" /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
    sed -i "s/^Queue.*/Queue ${4}/" /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
    VAL=$((${4}*${i}))
    sed -i "s/^Arguments.*/Arguments       = ${1}_${i} \$(Process) ${3} ${VAL}/" /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
    #cat /sphenix/u/xwang97/DPMFILE/readCondor${1}_${i}.condor
    condor_submit /sphenix/u/xwang97/DPMFILE/dpmreadCondor${1}_${i}.condor
done
