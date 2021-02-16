#!/bin/bash
#SimultaneousFitData.C(multMin, multMax, rapMin, rapMax, TrkptMin , TrkptMax, maxF, bkgN, AwayN, isfine, version, MupT, isAccRW, isEffRW, isTnP, SigSys, BkgSys)
#SimultaneousFitMC.C(multMin, multMax, rapMin, rapMax, TrkptMin , TrkptMax, maxF, AwayN, isfine, version, MupT)
#maxF = 2, 3
#bkgN = 0: expo*err, 1: pol1, 2: pol2, 3: pol3
#NU = 1: 1S, 2: 12S, 3: 123S
#detacut = 1: 1, 2: 1.5, 3: 2
version="v73"

#multMin=("0" "40" "100" "200" "300")
#multMax=("40" "100" "200" "300" "1500")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")
multMin=("0")
multMax=("300")
#multMin=("90")
#multMax=("300")
#multMin=("0")
#multMax=("50")
#multMin=("0")
#multMax=("45")
#multMin=("0")
#multMax=("55")
#multMin=("0")
#multMax=("60")
rapMin=("-2.4")
rapMax=("2.4")
TrkptMin=("0")
TrkptMax=("3")

for((i=0; i<"${#multMin[@]}"; i++))
do
	for((k=0; k<"${#rapMin[@]}"; k++))
	do
		for((l=0; l<"${#TrkptMin[@]}"; l++))
		do
			#root -l -b -q 'SimultaneousFitData.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, true, false, false)'
			#root -l -b -q 'SimultaneousFitData.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 3, 1, false, '\"$version\"', "3p5", true, true, true, false, false)'
			#root -l -b -q 'SimultaneousFitData.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 2, 1, false, '\"$version\"', "3p5", false, true, true, false, false)'
			#root -l -b -q 'SimultaneousFitData.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 2, 1, false, '\"$version\"', "3p5", true, false, true, false, false)'
			#root -l -b -q 'SimultaneousFitData.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, false, false, false)'
			#root -l -b -q 'SimultaneousFitData.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, true, true, false)'
			#root -l -b -q 'SimultaneousFitData.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 2, 1, false, '\"$version\"', "3p5", true, true, true, false, true)'
			root -l 'SimultaneousFitMC.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 1, false, '\"$version\"', "3p5")'

			#for((ipar=0; ipar<9; ipar++))
			#do
			#	root -l -b -q 'FreePar.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', false, '\"$version\"', "3p5", '$ipar')'
			#done
		done
	done
done
