#!/bin/bash
#Subtract_Trk.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, maxF, version, MupT)

version="v19"

#multMin=("0" "40" "100" "200" "300")
#multMax=("40" "100" "200" "300" "1500")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")
#multMin=("0")
#multMax=("40")
multMin=("110")
multMax=("300")
ptMin=("0" "4" "7" "10")
ptMax=("4" "7" "10" "30")
rapMin=("-2.4")
rapMax=("2.4")
TrkptMin=("0")
TrkptMax=("3")

for((i=0; i<"${#multMin[@]}"; i++))
do
	for((j=0; j<"${#ptMin[@]}"; j++))
	do
		for((k=0; k<"${#rapMin[@]}"; k++))
		do
			for((l=0; l<"${#TrkptMin[@]}"; l++))
			do
				root -l -b -q 'Subtract_Trk.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 2, '\"$version\"', "3p5", true)'
				root -l -b -q 'Subtract_Trk.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3, '\"$version\"', "3p5", true)'
			done
		done
	done
done
