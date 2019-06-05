#!/bin/bash
#DrawSigv2.C(multMin, multMax, rapMin, rapMax, TrkptMin , TrkptMax, maxF, bkgN, NU, detacut, isfine, version, MupT)

#maxF = 2, 3
#bkgN = 0: expo*err, 1: pol2, 2: pol1
#NU = 1: 1S, 2: 12S, 3: 123S
#detacut = 1: 1, 2: 1.5, 3: 2

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
			root -l -b -q 'CompSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 2, 1, 3, 1, true)'
			root -l -b -q 'CompSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 1, 3, 1, true)'
			root -l -b -q 'CompSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 2, 1, 3, 1, false)'
			root -l -b -q 'CompSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, 1, 3, 1, false)'
		done
	done
done
