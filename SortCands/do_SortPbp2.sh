#!/bin/bash
#SortPbp2.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, imass)

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

root -l -b -q 'SortPbp2.C+(false, 0, 1500, 0, 30, -2.4, 2.4, 0, 10, "4", '$1')'
#root -l -b -q 'SortPbp2.C+(false, 0, 1500, 0, 30, -2.4, 2.4, 0, 10, "4", 110)'
