#!/bin/bash

#$1 jobname $2 job number $3 event number
input="/sphenix/user/xwang97/DPMJET/${1}/${1}_${3}_files.txt"

#indexline=$1
linenumber=0
while IFS= read -r line; do
    if [ $2 -eq $linenumber ]; then
        echo $line
        root -b -q -l 'read_condor.cxx("'$line'")'
        sleep 2
    fi
    linenumber=$((linenumber + 1))
done <"$input"
