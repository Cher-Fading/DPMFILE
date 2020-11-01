#!/bin/bash
cd /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/
A=$(($2/79))
B=$(($2%79)) #use modulo to have more files
mkdir -p /sphenix/user/xwang97/DPMJET/$1/$A/$B
cp $1.inp /sphenix/user/xwang97/DPMJET/$1/$A/$1_$2.inp
cd /sphenix/user/xwang97/DPMJET/$1/$A/

if [ "$B" -eq "0" ]
then
echo "copying nuclear.bin"
cp /sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/nuclear.bin .
fi

echo $(pwd)
echo $(ls)
output=$((21 + $B))
echo output $output round $A queue $2

if [ "$((13-$2%20))" -eq "4" ] || [ "$((10-($2/400)%20))" -eq "7" ]
then
echo "problematic random seed, exiting"
exit 1
fi

TAB=$'\t'
sed -i "s/^OUTPUT.*/OUTPUT           ${output}/" /sphenix/user/xwang97/DPMJET/$1/$A/$1_$2.inp
sed -i "s/^FSEED.*/FSEED           $((($2/8000)%20-5))           $((10-($2/400)%20))           $((($2/20)%20-3))           $((13-$2%20))/" /sphenix/user/xwang97/DPMJET/$1/$A/$1_$2.inp
sed -i "s/^START.*/START          ${3}           0.0/" /sphenix/user/xwang97/DPMJET/$1/$A/$1_$2.inp
cat /sphenix/user/xwang97/DPMJET/$1/$A/$1_$2.inp

/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/dpmjet3.0-5F-new < /sphenix/user/xwang97/DPMJET/$1/$A/$1_$2.inp > /sphenix/user/xwang97/DPMJET/$1/$A/log$1_$2.txt
echo "now convert to root"
root -q '/sphenix/user/xwang97/DPMJET/dpmjet3-32BIT/BuildIt.C("'fort.${output}'","'$B'")'
mv /sphenix/user/xwang97/DPMJET/$1/$A/$B/fort.root /sphenix/user/xwang97/DPMJET/$1/fort_$1_$2_$3.root
echo "now remove old output"
rm -rf /sphenix/user/xwang97/DPMJET/$1/$A/
