#!/bin/bash
#ZYAM.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, version2, Weight, MupT, Fine)
#JetYieldComp.C(multMinhi, multMaxhi, multMinlow, multMaxlow, rapMin, rapMax, TrkptMin, TrkptMax, isfine, versionhi, versionlow, Weight, MupT)
#CompJRatio.C(Fine, Weight, MupT)

#multMin=("0" "40" "100" "200" "300")
#multMax=("40" "100" "200" "300" "1500")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")

#root -l -b -q 'ZYAM.C+(0, 50, 12, 15, -2.4, 2.4, 0, 3, "v28", true, "3p5", true)'
#root -l 'ZYAM.C+(90, 300, 10, 12, -2.4, 2.4, 0, 3, "v46", true, "3p5", false)'
#root -l -b -q 'JetYieldRatio.C+(0, 50, 0, 45, -2.4, 2.4, 0, 3, false, "v28", "v27", true, "3p5")'
#root -l 'JetYieldRatio.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, false, "v46", "v39", true, "3p5")'
root -l 'JetYieldRatio.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, false, "v47", "v41", true, "3p5")'
#root -l -b -q 'CompJRatio.C+(false, true, "3p5")'
