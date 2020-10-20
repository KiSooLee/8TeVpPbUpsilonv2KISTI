#!/bin/bash
#Correl_Reco_same_Pbp.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion, isAccRW, isEffRW, isTnP, imass)
#Correl_Gen_same_Pbp.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, imass)
#Correl_Reco_same_Pbp_jet.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion, isAccRW, isEffRW, isTnP, isBkg)

#Setting for condor job
#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Correl_Reco_same_Pbp.C+(false, 90, 300, 10, 30, -2.4, 2.4, 0, 3, "v48", "3p5", "v1", true, 0)'
#root -l -b -q 'Correl_Gen_same_Pbp.C+(0, 40, 0, 3, -2.4, 2.4, 0, 3, "v17", "4", '$1')'

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
root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 11, 15, -2.4, 2.4, 0, 3, "v67", "3p5", "v1", true, true, false, true)'
root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 11, 15, -2.4, 2.4, 0, 3, "v67", "3p5", "v1", true, true, false, false)'
root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 15, 19, -2.4, 2.4, 0, 3, "v67", "3p5", "v1", true, true, false, true)'
root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 15, 19, -2.4, 2.4, 0, 3, "v67", "3p5", "v1", true, true, false, false)'
root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 19, 30, -2.4, 2.4, 0, 3, "v67", "3p5", "v1", true, true, false, true)'
root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(90, 300, 19, 30, -2.4, 2.4, 0, 3, "v67", "3p5", "v1", true, true, false, false)'

########## jet low-multiplicity ##########
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 11, 15, -2.4, 2.4, 0, 3, "v68", "3p5", "v1", true, true, false, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 11, 15, -2.4, 2.4, 0, 3, "v68", "3p5", "v1", true, true, false, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 15, 19, -2.4, 2.4, 0, 3, "v68", "3p5", "v1", true, true, false, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 15, 19, -2.4, 2.4, 0, 3, "v68", "3p5", "v1", true, true, false, false)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 19, 30, -2.4, 2.4, 0, 3, "v68", "3p5", "v1", true, true, false, true)'
#root -l -b -q 'Correl_Reco_same_Pbp_jet.C+(0, 50, 19, 30, -2.4, 2.4, 0, 3, "v68", "3p5", "v1", true, true, false, false)'

