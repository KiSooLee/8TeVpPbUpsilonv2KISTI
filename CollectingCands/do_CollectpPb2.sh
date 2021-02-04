#!/bin/bash
#Collect_Reco_pPb2.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, trkptversion, imass)
#Collect_Gen_pPb2.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, imass)

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

#root -l -b -q 'Collect_Reco_pPb2.C+(false, 0, 50, 10, 11, -2.4, 2.4, 0, 3, "3p5", "v1", '$1')'
#root -l -b -q 'Collect_Reco_pPb2.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", 119)'
#root -l -b -q 'Collect_Reco_pPb2.C+(false, 0, 45, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", '$1')'
#root -l -b -q 'Collect_Reco_pPb2.C+(true, 0, 300, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", '$1')'
#root -l -b -q 'Collect_Reco_pPb2.C+(true, 0, 300, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1", 46)'
root -l -b -q 'Collect_Gen_pPb2.C+(0, 300, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", '$1')'
#for((i=0; i<120; i++))
#do
#	root -l -b -q 'Collect_Reco_pPb2.C+(false, 90, 110, 10, 30, -2.4, 2.4, 0, 3, "3p5", '$i')'
#done
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 40, 10, 30, -2.4, 2.4, 0, 3, "4", 0)'
