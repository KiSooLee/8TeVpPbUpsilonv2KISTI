#!/bin/bash
#Collect_Reco_pPb1.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, trkptversion, isSS, imass)
#Collect_Gen_pPb1.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, imass)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 2)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 9)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 12)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 15)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 21)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 24)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 32)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 35)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 43)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 53)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 56)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 59)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 63)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 71)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 74)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 79)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 83)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 85)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 88)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 106)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 111)'
root -l -b -q 'Collect_Reco_pPb1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 117)'
#root -l -b -q 'Collect_Reco_pPb1.C+(false, 0, 35, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
#root -l -b -q 'Collect_Reco_pPb1.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", 6)'
#root -l -b -q 'Collect_Reco_pPb1.C+(false, 0, 50, 9, 10, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
#root -l -b -q 'Collect_Reco_pPb1.C+(true, 0, 300, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1", 53)'
#root -l -b -q 'Collect_Reco_pPb1.C+(true, 0, 50, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
#root -l -b -q 'Collect_Gen_pPb1.C+(70, 300, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(70, 300, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(70, 300, 6, 10, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(70, 300, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(70, 300, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(70, 300, 12, 15, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(70, 300, 15, 20, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(70, 300, 20, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(0, 50, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(0, 50, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(0, 50, 6, 10, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(0, 50, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(0, 50, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(0, 50, 12, 15, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_pPb1.C+(0, 50, 20, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#for((i=0; i<120; i++))
#do
#	root -l -b -q 'Collect_Reco_pPb1.C+(true, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_pPb1.C+(true, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_pPb1.C+(true, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_pPb1.C+(true, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_pPb1.C+(true, 0, 50, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#done
#root -l -b -q 'Collect_Gen_pPb1.C+(0, 40, 10, 30, -2.4, 2.4, 0, 3, "4", 0)'
