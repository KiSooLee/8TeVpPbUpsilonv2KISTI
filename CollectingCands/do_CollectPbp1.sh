#!/bin/bash
#Collect_Pbp1.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, imass)

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

root -l -b -q 'Collect_Pbp1.C+(false, 0, 40, 10, 30, -2.4, 2.4, 0, 3, "4", '$1')'
#root -l -b -q 'Collect_Pbp1.C+(false, 0, 40, 10, 30, -2.4, 2.4, 0, 3, "4", 115)'
