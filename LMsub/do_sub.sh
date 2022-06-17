#!/bin/bash
#LMsub.C(multMinhi, multMaxhi, multMinlow, multMaxlow, rapMin, rapMax, TrkptMin, TrkptMax, maxF, bkgN, AwayN, isfine, versionhi, versionlow, isAccRW, isEffRW, isTnP, SigSys, BkgSys, MupT)
#LMsub_Par.C(multMinhi, multMaxhi, multMinlow, multMaxlow, rapMin, rapMax, TrkptMin, TrkptMax, maxF, bkgN, AwayN, isfine, versionhi, versionlow, MupT, FreePar)
#LMsub_Jvar(multMinhi, multMaxhi, multMinlow, multMaxlow, rapMin, rapMax, TrkptMin, TrkptMax, maxF, AwayN, isfine, versionhi, versionlow, MupT)

#multMin=("0" "40" "100" "200" "300")
#multMax=("40" "100" "200" "300" "1500")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")

#root -l 'LMsub_Samev2.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v83", "v85", "v86", "v87", true, true, 0, false, false, "3p5")'
#root -l 'LMsub.C+(70, 90, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v95", "v89", "v96", "v87", true, true, 0, false, false, "3p5")'
#root -l 'LMsub.C+(70, 300, 0, 35, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v83", "v97", "v86", "v98", true, true, 0, false, false, "3p5")'
root -l 'LMsub.C+(70, 300, 0, 35, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v97", "v86", "v98", true, true, 0, false, false, "3p5")'
#root -l -b -q 'LMsub.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", true, true, 0, true, false, "3p5")'
#root -l -b -q 'LMsub.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", true, true, 0, false, true, "3p5")'
#root -l -b -q 'LMsub.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", false, true, 0, false, false, "3p5")'
#root -l -b -q 'LMsub.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", true, false, 0, false, false, "3p5")'
#root -l -b -q 'LMsub.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", true, true, 1, false, false, "3p5")'
#root -l -b -q 'LMsub.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", true, true, 2, false, false, "3p5")'
#root -l -b -q 'LMsub.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", true, true, 3, false, false, "3p5")'
#root -l -b -q 'LMsub.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", true, true, 4, false, false, "3p5")'
#root -l -b -q 'LMsub.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", true, true, 5, false, false, "3p5")'

#for((ipar=0; ipar<9; ipar++))
#do
#	root -l -b -q 'LMsub_Par.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, 1, false, "v88", "v89", "v86", "v87", "3p5", '$ipar')'
#done

#root -l -b -q 'LMsub_Jvar.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 1, false, "v88", "v89", "v86", "v87", "3p5")'

#root -l 'LMsub_trk.C+(false, false, 70, 300, 0, 35, -2.4, 2.4, 0, 3, 3, 1, false, "v83", "v97", "v86", "v98", "3p5")'
#root -l 'LMsub_trk.C+(false, false, 70, 300, 0, 35, -2.4, 2.4, 0, 3, 3, 1, false, "v83", "v97", "v86", "v98", "3p5")'
#root -l 'LMsub_trk.C+(true, false, 70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 1, false, "v90", "v91", "v86", "v87", "3p5")'
#root -l -b -q 'LMsub_trk.C+(true, true, 70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 1, false, "v92", "v93", "v86", "v87", "3p5")'
#root -l 'LMsub_MC.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 1, false, "v90", "v91", "v86", "v87", "3p5")'

#root -l -b -q 'CompSub.C+(false, true, "3p5")'
#root -l -b -q 'Compv2.C+(false, true, "3p5")'
