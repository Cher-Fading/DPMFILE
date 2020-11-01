#!/bin/bash
#insert input pattern here
input=$(($2*20+9))

cd /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/
A=$(($input/79))
B=$(($input%79)) #use modulo to have more files
mkdir -p /sphenix/user/xwang97/DPMJET/$1/$A/$input
cp $1.inp /sphenix/user/xwang97/DPMJET/$1/$A/$1_$input.inp
cd /sphenix/user/xwang97/DPMJET/$1/$A/
if [ "$B" -eq "0" ]
then
echo "copying nuclear.bin"
cp /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/nuclear.bin .
fi
echo $(pwd)
echo $(ls)
output=$((21 + $B))
echo output $output round $A queue $input
TAB=$'\t'
sed -i "s/^OUTPUT.*/OUTPUT           ${output}/" /sphenix/user/xwang97/DPMJET/$1/$A/$1_$input.inp
sed -i "s/^FSEED.*/FSEED           $((($input/8000)%20-5))           $((10-($input/400)%20))           $((($input/20)%20-3))           $((13-$input%20))/" /sphenix/user/xwang97/DPMJET/$1/$A/$1_$input.inp
sed -i "s/^START.*/START          ${3}           0.0/" /sphenix/user/xwang97/DPMJET/$1/$A/$1_$input.inp
cat /sphenix/user/xwang97/DPMJET/$1/$A/$1_$input.inp
/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/dpmjet3.0-5F-new < /sphenix/user/xwang97/DPMJET/$1/$A/$1_$input.inp > /sphenix/user/xwang97/DPMJET/$1/$A/log$1_$input.txt
echo "now convert to root"
root -q '/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/BuildIt.C("'fort.${output}'","'$B'")'
mv /sphenix/user/xwang97/DPMJET/$1/$A/$B/fort.root /sphenix/user/xwang97/DPMJET/$1/fort_$1_$input_$3.root
echo "now remove old output"
rm /sphenix/user/xwang97/DPMJET/$1/$A/fort.${output} 
