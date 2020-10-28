#!/bin/bash
cd ~/dpmjet3-32BIT/
mkdir -p sphenix/user/xwang97/DPMJET/$1
mkdir -p sphenix/user/xwang97/DPMJET/$1/$2
cd ..
cp $1.inp sphenix/user/xwang97/DPMJET/$1/$2/
output=$((50 + $2))
echo output$output
TAB=$'\t'
sed -i "s/^OUTPUT.*/OUTPUT           ${output}/" sphenix/user/xwang97/DPMJET/$1/$2/$1.inp
sed -i "s/^FSEED.*/FSEED           $(($2-5))           $((10-$output))           $(($output-3))           $((13-$output))/" CondorResult/$1/$2/$1.inp
./dpmjet3.0-5F-new < sphenix/user/xwang97/DPMJET/$1/$2/$1.inp > sphenix/user/xwang97/DPMJET/$1/$2/log$1_$2.txt
mv fort.${output} sphenix/user/xwang97/DPMJET/$1/$2/
root -q 'BuildIt.C("'sphenix/user/xwang97/DPMJET/$1/$2/fort.${output}'","'sphenix/user/xwang97/DPMJET/$1/$2/'")'
mv sphenix/user/xwang97/DPMJET/$1/$2/fort.root sphenix/user/xwang97/DPMJET/$1/fort_$1_$2.root
