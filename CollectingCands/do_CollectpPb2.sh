#!/bin/bash
#Collect_Reco_pPb2.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, trkptversion, isSS, imass)
#Collect_Gen_pPb2.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, imass)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 0)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 4)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 7)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 30)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 36)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 44)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 46)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 52)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 55)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 57)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 61)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 74)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 83)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 86)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 90)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 92)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 102)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 105)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 108)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 110)'
root -l -b -q 'Collect_Reco_pPb2.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 119)'
#root -l -b -q 'Collect_Reco_pPb2.C+(false, 0, 35, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
#root -l -b -q 'Collect_Reco_pPb2.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", 119)'
#root -l -b -q 'Collect_Reco_pPb2.C+(false, 0, 45, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", '$1')'
#root -l -b -q 'Collect_Reco_pPb2.C+(false, 0, 50, 9, 10, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
#root -l -b -q 'Collect_Reco_pPb2.C+(true, 0, 300, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1", 46)'
#root -l -b -q 'Collect_Reco_pPb2.C+(true, 0, 50, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
#root -l -b -q 'Collect_Gen_pPb2.C+(70, 300, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(70, 300, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(70, 300, 6, 10, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(70, 300, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(70, 300, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(70, 300, 12, 15, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(70, 300, 15, 20, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(70, 300, 20, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 50, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 50, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 50, 6, 10, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 50, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 50, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 50, 12, 15, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 50, 20, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#for((i=0; i<120; i++))
#do
#	root -l -b -q 'Collect_Reco_pPb2.C+(true, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_pPb2.C+(true, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_pPb2.C+(true, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_pPb2.C+(true, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_pPb2.C+(true, 0, 50, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#done
#root -l -b -q 'Collect_Gen_pPb2.C+(0, 40, 10, 30, -2.4, 2.4, 0, 3, "4", 0)'
