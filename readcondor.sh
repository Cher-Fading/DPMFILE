#!/bin/bash

#$1 jobname $2 job batch $3 job number $4 batch mode (true) single job mode $5 event number
if [ $4 == "true" ]; then
input="/sphenix/user/xwang97/DPMJET/$1_$2/$1_$2_files.txt"
else
input = "/sphenix/user/xwang97/DPMJET/$1/$1_files.txt"

#indexline=$1
linenumber=0
while IFS= read -r line; do
	if [ $3 -eq $linenumber ]; then
		if [ "$4" == "true" ]; then
			filename=/sphenix/user/xwang97/DPMJET/$1_$2/fort_$1_$2_$3_$5.root
		else

			filename=/sphenix/user/xwang97/DPMJET/$1/fort_$1_$3_$5.root
		fi
echo $filename
		root -b -q -l 'read_condor.cxx("'$filename'")'
		sleep 2
	fi
	linenumber=$((linenumber + 1))
done <"$input"