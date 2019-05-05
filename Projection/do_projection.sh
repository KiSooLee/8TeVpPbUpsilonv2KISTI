#!/bin/bash
#DrawCorrel.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, MupT)
#RatioNProjection.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, MupT)

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
				root -l -b -q 'DrawCorrel.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', "v17", "4")'
				root -l -b -q 'RatioNProjection.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', "v17", "4")'
			done
		done
	done
done
