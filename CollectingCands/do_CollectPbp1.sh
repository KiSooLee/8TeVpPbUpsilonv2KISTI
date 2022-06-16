#!/bin/bash
#Collect_Reco_Pbp1.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, trkptversion, isSS, imass)
#Collect_Gen_Pbp1.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, imass)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 3)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 7)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 21)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 27)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 32)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 38)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 40)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 56)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 61)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 64)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 75)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 86)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 89)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 91)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 99)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 102)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 108)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 112)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 115)'
root -l -b -q 'Collect_Reco_Pbp1.C+(false, 70, 300, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, 118)'
#root -l -b -q 'Collect_Reco_Pbp1.C+(false, 0, 35, 12, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
#root -l -b -q 'Collect_Reco_Pbp1.C+(false, 50, 60, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1", 20)'
#root -l -b -q 'Collect_Reco_Pbp1.C+(false, 0, 45, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", '$1')'
#root -l -b -q 'Collect_Reco_Pbp1.C+(false, 0, 50, 9, 10, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
#root -l -b -q 'Collect_Reco_Pbp1.C+(true, 70, 300, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1", false, 29)'
#root -l -b -q 'Collect_Reco_Pbp1.C+(true, 0, 50, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$1')'
#root -l -b -q 'Collect_Gen_Pbp1.C+(70, 300, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(70, 300, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(70, 300, 6, 10, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(70, 300, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(70, 300, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(70, 300, 12, 15, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(70, 300, 15, 20, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(70, 300, 20, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(0, 50, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(0, 50, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(0, 50, 6, 10, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(0, 50, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(0, 50, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(0, 50, 12, 15, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "3p5", "v1")'
#root -l -b -q 'Collect_Gen_Pbp1.C+(0, 50, 20, 30, -2.4, 2.4, 0, 3, "3p5", "v1")'
#for((i=0; i<120; i++))
#do
#	root -l -b -q 'Collect_Reco_Pbp1.C+(true, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_Pbp1.C+(true, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_Pbp1.C+(true, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_Pbp1.C+(true, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#	root -l -b -q 'Collect_Reco_Pbp1.C+(true, 0, 50, 0, 30, -2.4, 2.4, 0, 3, "3p5", "v1", false, '$i')'
#done
#root -l -b -q 'Collect_Gen_Pbp1.C+(0, 40, 10, 30,g -2.4, 2.4, 0, 3, "4", 0)'
