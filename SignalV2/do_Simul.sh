#!/bin/bash
#SimultaneousFit.C(multMin, multMax, rapMin, rapMax, TrkptMin , TrkptMax, maxF, bkgN, NU, detacut, isfine, version)
#maxF = 2, 3
#bkgN = 0: expo*err, 1: pol2
#NU = 1: 1S, 2: 12S, 3: 123S
#detacut = 1: 1, 2: 1.5, 3: 2
version="v16"

#multMin=("0" "40" "100" "200" "300")
#multMax=("40" "100" "200" "300" "1500")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")
multMin=("110")
multMax=("300")
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
			root -l -b -q 'SimultaneousFit.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 2, 1, 3, 1, true, '\"$version\"')'
			root -l -b -q 'SimultaneousFit.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 1, 3, 1, true, '\"$version\"')'
			root -l -b -q 'SimultaneousFit.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 2, 1, 3, 1, false, '\"$version\"')'
			root -l -b -q 'SimultaneousFit.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 1, 3, 1, false, '\"$version\"')'
		done
	done
done
