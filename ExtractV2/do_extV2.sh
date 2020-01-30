#!/bin/bash
#extV2.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, MupT)
#extV23.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, MupT)

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
				root -l -b -q 'extV2.C+(false, false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', false, "3p5")'
				root -l -b -q 'extV23.C+(false, false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', false, "3p5")'
			done
		done
	done
done
