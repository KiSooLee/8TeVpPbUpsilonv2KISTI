#!/bin/bash
#Subtract_Trk.C(multMinhi, multMaxhi, multMinlow, multMaxlow, rapMin, rapMax, TrkptMin, TrkptMax, maxF, bkgF, isFine, versionhi, versionlow, Jversionhi, Jversionlow, isAccRW, isEffRW, isTnP, SigSys, BkgSys, MupT)
#Subtract_Trk_Jvar.C(multMinhi, multMaxhi, multMinlow, multMaxlow, rapMin, rapMax, TrkptMin, TrkptMax, maxF, isFine, versionhi, versionlow, Jversionhi, Jversionlow)
#Subtract_Trk_Par.C(multMinhi, multMaxhi, multMinlow, multMaxlow, rapMin, rapMax, TrkptMin, TrkptMax, maxF, isFine, versionhi, versionlow, Jversionhi, Jversionlow, MupT, FreeParN)
#Subtract_Trk_MC.C(multMin, multMax, rapMin, rapMax, TrkptMin, TrkptMax, maxF, isFine, version, MupT)
#Subtract_Trk_GEN.C(multMin, multMax, rapMin, rapMax, TrkptMin, TrkptMax, maxF, isFine, version, MupT)

#ptMin=("0" "4" "7" "10")
#ptMax=("4" "7" "10" "30")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
#ptMin=("0")
#ptMax=("30")
#ptMin=("0" "4" "7")
#ptMax=("4" "7" "10")
TrkptMin=("0")
TrkptMax=("3")

#root -l -b -q 'Subtract_Trk_Samev2.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v83", "v85", "v86", "v87", true, true, 0, false, false, "3p5")'
#root -l 'Subtract_Trk.C+(70, 90, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v95", "v89", "v96", "v87", true, true, 0, false, false, "3p5")'
#root -l 'Subtract_Trk.C+(70, 90, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v95", "v89", "v96", "v87", true, true, 0, false, false, "3p5")'
root -l 'Subtract_Trk.C+(70, 300, 0, 35, -2.4, 2.4, 0, 3, 3, 2, false, "v83", "v97", "v86", "v98", true, true, 0, false, false, "3p5")'
#root -l 'Subtract_Trk.C+(70, 300, 0, 35, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v97", "v86", "v98", true, true, 0, false, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v83", "v85", "v86", "v87", true, true, 0, false, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 3, false, "v88", "v89", "v86", "v87", true, true, 0, false, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, 0, true, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, 0, false, true, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", false, true, 0, false, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, false, 0, false, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, 1, false, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, 2, false, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, 3, false, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, 4, false, false, "3p5")'
#root -l -b -q 'Subtract_Trk.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, 5, false, false, "3p5")'

#for((ipar=0; ipar<9; ipar++))
#do
#	root -l -b -q 'Subtract_Trk_Par.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v88", "v89", "v86", "v87", "3p5", '$ipar')'
#done

#root -l -b -q 'Subtract_Trk_Jvar.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v88", "v89", "v86", "v87", "3p5")'

#root -l 'Subtract_Trk_MC.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v92", "v93", "v86", "v87", "3p5")'
#root -l 'Subtract_Trk_GEN.C+(70, 300, -2.4, 2.4, 0, 3, 3, false, "v73", "3p5")'


#for((i=0; i<"${#multMin[@]}"; i++))
#do
#	for((j=0; j<"${#ptMin[@]}"; j++))
#	do
#		for((k=0; k<"${#rapMin[@]}"; k++))
#		do
#			for((l=0; l<"${#TrkptMin[@]}"; l++))
#			do
#				root -l -b -q 'Subtract_Trk.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 2, '\"$version\"', "3p5", true)'
#				root -l -b -q 'Subtract_Trk.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, '\"$version\"', "3p5", true)'
#			done
#		done
#	done
#done
