#!/bin/bash
#extV23.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, isAccRW, isEffRW, isTnP, MupT, FMax)

version="v83"

#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")
#multMin=("90")
#multMax=("300")
multMin=("70")
multMax=("300")
#multMin=("0")
#multMax=("50")
#multMin=("0")
#multMax=("35")
#multMin=("70" "90" "120")
#multMax=("90" "120" "300")
#multMin=("0")
#multMax=("300")
ptMin=("0" "3" "6" "10")
ptMax=("3" "6" "10" "30")
#ptMin=("0")
#ptMax=("30")
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
				#root -l -b -q 'extV23.C+(true, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(true, true, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(true, false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(true, true, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", true, 2)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", true, 3)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", false, 2)'
				root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(false, false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", false, 2)'
				#root -l -b -q 'extV23.C+(false, false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 0, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', false, true, 0, "3p5", false, 2)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', false, true, 0, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, false, 0, "3p5", false, 2)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, false, 0, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 1, "3p5", false, 2)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 1, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 2, "3p5", false, 2)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 2, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 3, "3p5", false, 2)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 3, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 4, "3p5", false, 2)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 4, "3p5", false, 3)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 5, "3p5", false, 2)'
				#root -l -b -q 'extV23.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', true, true, 5, "3p5", false, 3)'
				#root -l -b -q 'check_Mix_w_mult.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', 3)'
			done
		done
	done
done
