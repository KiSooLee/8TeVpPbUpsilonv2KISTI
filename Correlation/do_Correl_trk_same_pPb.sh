#!/bin/bash
#Correl_trk_Reco_same_pPb.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion, Weight, imass)
#Correl_trk_Gen_same_pPb.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, imass)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 40, 10, 30, -2.4, 2.4, 0, 3, "v18", "3p5", '$1')'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 40, 10, 30, -2.4, 2.4, 0, 3, "v18", "4", '$1')'
#root -l -b -q 'Correl_trk_Reco_same_pPb_jet.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, true)'
#root -l -b -q 'Correl_trk_Reco_same_pPb_jet.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, false)'
for((i=0; i<20; i++))
do
	root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 120, 300, 10, 30, -2.4, 2.4, 0, 3, "v35", "3p5", "v1", true, '$i')'
done
#for((i=0; i<20; i++))
#do
#	root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 40, 10, 30, -2.4, 2.4, 0, 3, "v20", "3p5", true, '$i')'
#done
#for((i=0; i<20; i++))
#do
#	root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 40, 90, 10, 30, -2.4, 2.4, 0, 3, "v21", "3p5", false, '$i')'
#done
#for((i=0; i<20; i++))
#do
#	root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 110, 10, 30, -2.4, 2.4, 0, 3, "v22", "3p5", false, '$i')'
#done
#for((i=0; i<18; i++))
#do
#	root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 40, 10, 30, -2.4, 2.4, 0, 3, "v17", "4", '$i')'
#done
#for((i=0; i<14; i++))
#do
#	root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 40, 10, 30, -2.4, 2.4, 0, 3, "v31", "3p5", true, '$i')'
#done
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v25", "3p5", false, 0)'
