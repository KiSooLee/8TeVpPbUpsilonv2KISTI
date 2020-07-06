#!/bin/bash
#LMsub.C(multMinhi, multMaxhi, multMinlow, multMaxlow, rapMin, rapMax, TrkptMin, TrkptMax, maxF, bkgN, versionhi, versionlow, Weight, MupT)

#multMin=("0" "40" "100" "200" "300")
#multMax=("40" "100" "200" "300" "1500")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")

#root -l -b -q 'LMsub.C+(110, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, true, "v19", "v28", true, "3p5")'
root -l -b -q 'LMsub.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v37", "v42", "v46", "v39", true, "3p5")'
#root -l -b -q 'CompSub.C+(false, true, "3p5")'
#root -l -b -q 'Compv2.C+(false, true, "3p5")'
