#!/bin/bash
#DrawSigv2.C(multMin, multMax, rapMin, rapMax, TrkptMin , TrkptMax, maxF, bkgN, AwayN, isfine, version, MupT, isAccRW, isEffRW, isTnP, SigSys, BkgSys)

#maxF = 2, 3
#bkgN = 0: expo*err, 1: pol2, 2: pol1
#NU = 1: 1S, 2: 12S, 3: 123S
#detacut = 1: 1, 2: 1.5, 3: 2
version="v73"

#multMin=("110")
#multMax=("300")
#multMin=("70")
multMax=("300")
multMin=("0")
#multMax=("50")
rapMin=("-2.4")
rapMax=("2.4")
TrkptMin=("0")
TrkptMax=("3")

for((i=0; i<"${#multMin[@]}"; i++))
do
	for((j=0; j<"${#rapMin[@]}"; j++))
	do
		for((k=0; k<"${#TrkptMin[@]}"; k++))
		do
			root -l 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, 0, false, false)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 3, 1, false, '\"$version\"', "3p5", true, true, 0, false, false)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, 0, true, false)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, 0, false, true)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", false, true, 0, false, false)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", true, false, 0, false, false)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, 1, false, false)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, 2, false, false)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, 3, false, false)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, 4, false, false)'
			#root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, 5, false, false)'
			#root -l -b -q 'DrawObSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 2, 1, 3, 1, true, '\"$version\"', "3p5")'
			#root -l -b -q 'DrawObSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 1, 3, 1, true, '\"$version\"', "3p5")'
			#root -l -b -q 'DrawObSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 2, 1, 3, 1, false, '\"$version\"', "3p5")'
			#root -l -b -q 'DrawObSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 1, 3, 1, false, '\"$version\"', "3p5")'
			#for((ipar=0; ipar<9; ipar++))
			#do
			#	root -l -b -q 'DrawSigv2_Par.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$j]}', '${rapMax[$j]}', '${TrkptMin[$k]}', '${TrkptMax[$k]}', false, '\"$version\"', "3p5", '$ipar')'
			#done
		done
	done
done
