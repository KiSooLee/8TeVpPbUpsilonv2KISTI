#!/bin/bash
#SortPbp1.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, imass)
#Collect_Pbp1.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, imass)

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

#root -l -b -q 'SortPbp1.C+(false, 0, 1500, 0, 30, -2.4, 2.4, 0, 10, '$1')'
root -l -b -q 'Collect_Pbp1.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "4", '$1')'
#root -l -b -q 'SortPbp1.C+(false, 0, 1500, 0, 30, -2.4, 2.4, 0, 10, 1)'
#root -l -b -q 'Collect_Pbp1.C+(false, 110, 1500, 10, 30, -2.4, 2.4, 1, 3, 0)'
