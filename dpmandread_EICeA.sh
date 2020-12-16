#!/bin/bash
#./dpmandread.sh ep_HERA5_1 0 1E4 2000
cd /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/
A=$(($2/79))
B=$(($2%79)) #use modulo to have more files
NUM=$(($2+$4))
mkdir -p /sphenix/user/xwang97/DPMJET/$1/$A/$B
cp $1.inp /sphenix/user/xwang97/DPMJET/$1/${1}_${2}.inp
cd /sphenix/user/xwang97/DPMJET/$1/$A/

if [ ! -f nuclear.bin ]
then
echo "copying nuclear.bin"
cp /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/nuclear.bin .
fi

echo $(pwd)
echo $(ls)
output=$((21 + $B))
echo output $output round $A queue $2

TAB=$'\t'
sed -i "s/^OUTPUT.*/OUTPUT           ${output}/" /sphenix/user/xwang97/DPMJET/${1}/${1}_${2}.inp
sed -i "s/^FSEED.*/FSEED           $((($NUM/8000)%20-5))           $((10-($NUM/400)%20))           $((($NUM/20)%20-3))           $((13-$NUM%20))/" /sphenix/user/xwang97/DPMJET/$1/${1}_${2}.inp
sed -i "s/^START.*/START          ${3}           0.0/" /sphenix/user/xwang97/DPMJET/${1}/${1}_${2}.inp
#cat /sphenix/user/xwang97/DPMJET/$1/${1}_${2}.inp

/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/dpmjet3.0-5F-new < /sphenix/user/xwang97/DPMJET/${1}/${1}_${2}.inp > /sphenix/user/xwang97/DPMJET/$1/log${1}_${2}.txt
#/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/dpmjet3.0-5F-new < /sphenix/user/xwang97/DPMJET/${1}/${1}_${2}.inp
echo "now convert to root"
root -q '/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/BuildIt.C("'fort.${output}'","'$B'")' > /sphenix/user/xwang97/DPMJET/$1/fort_${1}_${2}_${3}_log.txt
mv /sphenix/user/xwang97/DPMJET/$1/$A/$B/fort.root /sphenix/user/xwang97/DPMJET/$1/fort_${1}_${2}_${3}.root
echo "now remove old output"
#folder $B contains single fort.root file that's only identifiable through path
#folder $A contains nuclear.bin and fort.21-99 for every 79 jobs
rm -rf /sphenix/user/xwang97/DPMJET/$1/$A/$B
rm /sphenix/user/xwang97/DPMJET/$1/$A/fort.${output}
sed -n '1,/^ \*\*   phone: + 1 - 630 - 252 - 7615; e-mail: mrenna@hep.anl.gov              \*\*.*/p' /sphenix/user/xwang97/DPMJET/$1/log${1}_${2}.txt > /sphenix/user/xwang97/DPMJET/$1/log${1}_${2}_short.txt
sed -n '/^ HISTAT:              statistics - intranuclear cascade.*/,$p' /sphenix/user/xwang97/DPMJET/$1/log${1}_${2}.txt >> /sphenix/user/xwang97/DPMJET/$1/log${1}_${2}_short.txt
rm /sphenix/user/xwang97/DPMJET/$1/log${1}_${2}.txt
echo "now read it"
cd /sphenix/u/xwang97/DPMFILE
root -b -q -l 'read_condor.cxx("'/sphenix/user/xwang97/DPMJET/$1/fort_${1}_${2}_${3}.root'", 0, false, "fullcut", 1., 20.,2000.)'
echo "finished"
