#!/bin/bash
#Correl_Reco_same_Pbp.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion, isAccRW, isEffRW, isTnP, imass)
#Correl_Gen_same_Pbp.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion)
#Correl_Reco_same_Pbp_jet.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion, isAccRW, isEffRW, isTnP, isBkg)

#Setting for condor job
#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 10, 30, -2.4, 2.4, 0, 3, "v48", "3p5", "v1", true, 0)'

########## GEN ##########
#root -l -b -q 'Correl_Gen_same_Pbp.C+(0, 300, 0, 3, -2.4, 2.4, 0, 3, "v73", "3p5", "v1")'
#root -l -b -q 'Correl_Gen_same_Pbp.C+(0, 300, 3, 6, -2.4, 2.4, 0, 3, "v73", "3p5", "v1")'
#root -l -b -q 'Correl_Gen_same_Pbp.C+(0, 300, 6, 10, -2.4, 2.4, 0, 3, "v73", "3p5", "v1")'
#root -l -b -q 'Correl_Gen_same_Pbp.C+(0, 300, 10, 30, -2.4, 2.4, 0, 3, "v73", "3p5", "v1")'

########## MC ##########
for((i=0; i<9; i++))
do
	root -l -b -q 'Correl_Reco_same_Pbp.C+(true, 0, 300, 0, 3, -2.4, 2.4, 0, 3, "v73", "3p5", "v1", true, true, true, '$i')'
	root -l -b -q 'Correl_Reco_same_Pbp.C+(true, 0, 300, 3, 6, -2.4, 2.4, 0, 3, "v73", "3p5", "v1", true, true, true, '$i')'
	root -l -b -q 'Correl_Reco_same_Pbp.C+(true, 0, 300, 6, 10, -2.4, 2.4, 0, 3, "v73", "3p5", "v1", true, true, true, '$i')'
	root -l -b -q 'Correl_Reco_same_Pbp.C+(true, 0, 300, 10, 30, -2.4, 2.4, 0, 3, "v73", "3p5", "v1", true, true, true, '$i')'
done

########## nominal high-multiplicity ##########
#for((i=0; i<20; i++))
#do
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 0, 3, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 0, 3, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", false, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 0, 3, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, false, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 0, 3, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, true, false, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 3, 6, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 3, 6, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", false, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 3, 6, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, false, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 3, 6, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, true, false, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 6, 10, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 6, 10, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", false, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 6, 10, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, false, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 6, 10, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, true, false, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 10, 30, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 10, 30, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", false, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 10, 30, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, false, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 10, 30, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true, true, false, '$i')'
#done

#for((i=0; i<18; i++))
#do
#	root -l -b -q 'Correl_Gen_same_Pbp.C+(0, 40, 0, 3, -2.4, 2.4, 0, 3, "v17", "4", '$i')'
#done

########### nominal low-multiplicity ##########
#for((i=0; i<14; i++))
#do
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", false, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, false, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, true, false, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", false, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, false, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, true, false, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", false, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, false, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, true, false, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", false, true, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, false, true, '$i')'
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true, true, false, '$i')'
#done

#for((i=0; i<13; i++))
#do
#	root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v51", "3p5", "v1", true, '$i')'
#done

########## jet high-multiplicity ##########
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 9, 10, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, true, false, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 9, 10, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, true, false, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 10, 11, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, true, false, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 10, 11, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, true, false, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 11, 15, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, false, true, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 11, 15, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, false, true, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 15, 19, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, false, true, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 15, 19, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, false, true, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 19, 30, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, false, true, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 19, 30, -2.4, 2.4, 0, 3, "v65", "3p5", "v1", true, false, true, false)'

########## jet low-multiplicity ##########
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 9, 10, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, false, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 9, 10, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, false, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 10, 11, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, false, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 10, 11, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, false, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 11, 15, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, true, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 11, 15, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, true, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, true, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, true, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 20, 30, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, true, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 20, 30, -2.4, 2.4, 0, 3, "v66", "3p5", "v1", true, true, true, false)'
