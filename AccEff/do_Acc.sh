#!/bin/bash
#Acc.C(Generation, MupT, isRW, ifile)
#DrawAcc.C(Generation, MupT, isRW)
#RWCompAcc.C(Generation, MupT)

#for((i=1; i<26; i++))
#do
#	root -l -b -q 'Acc.C+(1, "3p5", true, '$i')'
#	root -l -b -q 'Acc.C+(1, "3p5", false, '$i')'
#done
root -l -b -q 'DrawAcc.C+(1, "3p5", true)'
root -l -b -q 'DrawAcc.C+(1, "3p5", false)'
#root -l -b -q 'RWCompAcc.C+(1, "3p5")'
