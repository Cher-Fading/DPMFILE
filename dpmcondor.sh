#!/bin/bash
cd ~/dpmjet3-32BIT/CondorResult
mkdir -p $1
mkdir -p $1/$2
cd ..
cp $1.inp CondorResult/$1/$2/
output=$((50 + $2))
echo output$output
TAB=$'\t'
sed -i "s/^OUTPUT.*/OUTPUT           ${output}/" CondorResult/$1/$2/$1.inp
sed -i "s/^FSEED.*/FSEED           $(($output-50))           $((100-$output))           $(($output-30))           $((130-$output))/" CondorResult/$1/$2/$1.inp
./dpmjet3.0-5F-new < CondorResult/$1/$2/$1.inp > CondorResult/$1/$2/log$1_$2.txt
mv fort.${output} CondorResult/$1/$2/
root -q 'BuildIt.C("'CondorResult/$1/$2/fort.${output}'","'CondorResult/$1/$2/'")'
mv CondorResult/$1/$2/fort.root CondorResult/$1/fort_$1_$2.root
