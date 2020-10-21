#!/bin/bash
#DrawCorrel.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, trkptversion, isAccRW, isEffRW, isTnP, MupT)
#RatioNProjection.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, trkptversion, isAccRW, isEffRW, isTnP, MupT)
#DrawCorrel_jet.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, isAccRW, isEffRW, isTnP, MupT, isBkg)

#RatioNProjection.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, trkptversion, isAccRW, isEffRW, isTnP, MupT)
#RatioNProjection_jet.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, trkptversion, isAccRW, isEffRW, isTnP, MupT, isBkg)

version="v67"
#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")
multMin=("90")
multMax=("300")
#multMin=("0")
#multMax=("50")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
#ptMin=("5" "6" "7" "8" "9" "10" "12" "15")
#ptMax=("6" "7" "8" "9" "10" "12" "15" "30")
#ptMin=("9" "10" "12" "15")
#ptMax=("10" "12" "15" "30")
ptMin=("11" "15" "19")
ptMax=("15" "19" "30")
#ptMin=("9")
#ptMax=("12")
rapMin=("-2.4")
rapMax=("2.4")
TrkptMin=("0")
TrkptMax=("3")
#TrkptMin=("0")
#TrkptMax=("10")

for((i=0; i<"${#multMin[@]}"; i++))
do
	for((j=0; j<"${#ptMin[@]}"; j++))
	do
		for((k=0; k<"${#rapMin[@]}"; k++))
		do
			for((l=0; l<"${#TrkptMin[@]}"; l++))
			do
########## Draw ##########
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, true, "3p5")'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, true, "3p5")'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, true, "3p5")'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, false, "3p5")'

########## Draw jet ##########
				root -l -b -q 'DrawCorrel_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, true, "3p5", true)'
				root -l -b -q 'DrawCorrel_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, true, "3p5", false)'
				root -l -b -q 'DrawCorrel_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, true, "3p5", true)'
				root -l -b -q 'DrawCorrel_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, true, "3p5", false)'
				root -l -b -q 'DrawCorrel_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, true, "3p5", true)'
				root -l -b -q 'DrawCorrel_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, true, "3p5", false)'
				root -l -b -q 'DrawCorrel_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, false, "3p5", true)'
				root -l -b -q 'DrawCorrel_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, false, "3p5", false)'

########## old ##########
				#root -l -b -q 'ForAN.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', "v48", true, "3p5")'

########## project ##########
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, true, "3p5")'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, true, "3p5")'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, true, "3p5")'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, false, "3p5")'

########## project jet ##########
				root -l -b -q 'RatioNProjection_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, true, "3p5", true)'
				root -l -b -q 'RatioNProjection_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, true, "3p5", false)'
				root -l -b -q 'RatioNProjection_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, true, "3p5", true)'
				root -l -b -q 'RatioNProjection_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, true, "3p5", false)'
				root -l -b -q 'RatioNProjection_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, true, "3p5", true)'
				root -l -b -q 'RatioNProjection_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, true, "3p5", false)'
				root -l -b -q 'RatioNProjection_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, false, "3p5", true)'
				root -l -b -q 'RatioNProjection_jet.C+('${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, false, "3p5", false)'
			done
		done
	done
done
