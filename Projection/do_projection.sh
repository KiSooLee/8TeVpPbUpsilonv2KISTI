#!/bin/bash
#DrawCorrel.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, trkptversion, isAccRW, isEffRW, isTnP, MupT, isSS)
#RatioNProjection.C(isMC, isGen, isTrk, multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, trkptversion, isAccRW, isEffRW, isTnP, MupT, isSS)
#DrawCorrel_jet.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, isAccRW, isEffRW, isTnP, MupT, isBkg)
#RatioNProjection_jet.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, trkptversion, isAccRW, isEffRW, isTnP, MupT, isBkg)

version="v97"
#rapMin=("-24" "-12" "0" "12")
#rapMax=("-12" "0" "12" "24")
#TrkptMin=("0" "1" "2" "3" "4" "6")
#TrkptMax=("1" "2" "3" "4" "6" "10")
#multMin=("90")
#multMax=("300")
#multMin=("70")
#multMax=("300")
#multMin=("0")
#multMax=("50")
multMin=("0")
multMax=("35")
#multMin=("0")
#multMax=("300")
#multMin=("40" "50" "60" "70" "80")
#multMax=("50" "60" "70" "80" "90")
#multMin=("70" "90" "120")
#multMax=("90" "120" "300")
#multMin=("45")
#multMax=("55")
#ptMin=("0" "3" "6" "10")
#ptMax=("3" "6" "10" "30")
ptMin=("0")
#ptMin=("12")
ptMax=("30")
#ptMin=("5" "6" "7" "8" "9" "10" "12" "15")
#ptMax=("6" "7" "8" "9" "10" "12" "15" "30")
#ptMin=("10" "12" "15" "20")
#ptMax=("12" "15" "20" "30")
#ptMin=("12" "15" "20")
#ptMax=("15" "20" "30")
#ptMin=("9" "10" "11" "15" "20")
#ptMax=("10" "11" "15" "20" "30")
#ptMin=("9" "10")
#ptMax=("10" "12")
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
				#root -l -b -q 'DrawCorrel.C+(true, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(true, true, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(true, false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(true, true, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", true)'
				root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(false, false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 1, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 2, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 3, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 4, "3p5", false)'
				#root -l -b -q 'DrawCorrel.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 5, "3p5", false)'

########## Draw jet ##########
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", true)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, 0, "3p5", true)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, 0, "3p5", true)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, 0, "3p5", false)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 1, "3p5", true)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 1, "3p5", false)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 2, "3p5", true)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 2, "3p5", false)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 3, "3p5", true)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 3, "3p5", false)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 4, "3p5", true)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 4, "3p5", false)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 5, "3p5", true)'
				#root -l -b -q 'DrawCorrel_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 5, "3p5", false)'

########## old ##########
				#root -l -b -q 'ForAN.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', "v48", true, "3p5")'

########## project ##########
				#root -l -b -q 'RatioNProjection.C+(true, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(true, true, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(true, false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(true, true, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", true)'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(false, false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 1, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 2, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 3, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 4, "3p5", false)'
				#root -l -b -q 'RatioNProjection.C+(false, false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 5, "3p5", false)'

########## project jet ##########
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection_jet.C+(true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, 0, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", false, true, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, 0, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, false, 0, "3p5", false)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 1, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 1, "3p5", false)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 2, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 2, "3p5", false)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 3, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 3, "3p5", false)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 4, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 4, "3p5", false)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 5, "3p5", true)'
				#root -l -b -q 'RatioNProjection_jet.C+(false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", true, true, 5, "3p5", false)'
				#root -l -b -q 'RatioNProjection_MC_jet.C+(true, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", "3p5")'
				#root -l -b -q 'RatioNProjection_MC_jet.C+(false, false, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", "3p5")'
				#root -l -b -q 'RatioNProjection_MC_jet.C+(true, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", "3p5")'
				#root -l -b -q 'RatioNProjection_MC_jet.C+(false, true, '${multMin[$i]}', '${multMax[$i]}', '${ptMin[$j]}', '${ptMax[$j]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"', "v1", "3p5")'
			done
		done
	done
done
