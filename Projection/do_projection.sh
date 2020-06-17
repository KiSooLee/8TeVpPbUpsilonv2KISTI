#!/bin/bash
#DrawCorrel.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, Weight, MupT)
#RatioNProjection.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, MupT)

#multMin=("0" "40" "100" "200" "300")
#multMax=("40" "100" "200" "300" "1500")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")
#multMin=("110")
#multMax=("300")
#multMin=("120")
#multMax=("300")
multMin=("100")
multMax=("300")
#multMin=("0")
#multMax=("40")
#multMin=("0")
#multMax=("45")
#multMin=("0")
#multMax=("50")
#multMin=("0")
#multMax=("55")
#multMin=("0")
#multMax=("60")
#multMin=("0")
#multMin=("40")
#multMax=("90")
#multMin=("90")
#multMax=("110")
ptMin=("0" "4" "7" "10")
ptMax=("4" "7" "10" "30")
#ptMin=("0" "4" "7")
#ptMax=("4" "7" "10")
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
				root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', "v36", true, "3p5", "v1")'
				#root -l -b -q 'ForAN.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', "v28", true, "3p5")'
				root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', "v36", true, "3p5", "v1")'
				#root -l -b -q 'RatioNProjection_jet.C+(false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', "v31", true, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', "v31", true, "3p5", false)'
			done
		done
	done
done
