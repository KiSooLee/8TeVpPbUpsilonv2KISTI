#!/bin/bash
#Sort0.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version)

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

version="v1"
root -l -b -q 'mSortpPb2.C+(false, 0, 1500, 0, 500, -2.4, 2.4, 0, 100, '\"$version\"', '$1')'
#root -l -b -q 'mSortpPb2.C+(false, 0, 1500, 0, 500, -2.4, 2.4, 1, 3, '\"$version\"', '$1')'
#root -l -b -q 'mSortpPb2.C+(false, 200, 1500, 0, 500, -2.4, 2.4, 0, 100, '\"$version\"', '$1')'
#root -l -b -q 'mSortpPb2.C+(false, 200, 1500, 0, 500, -2.4, 2.4, 1, 3, '\"$version\"', '$1')'
#root -l -b -q 'mSortpPb2.C+(false, 150, 1500, 0, 500, -2.4, 2.4, 0, 100, '\"$version\"', '$1')'
#root -l -b -q 'mSortpPb2.C+(false, 150, 1500, 0, 500, -2.4, 2.4, 1, 3, '\"$version\"', '$1')'
#root -l -b -q 'mSortpPb2.C+(false, 100, 1500, 0, 500, -2.4, 2.4, 0, 100, '\"$version\"', '$1')'
#root -l -b -q 'mSortpPb2.C+(false, 100, 1500, 0, 500, -2.4, 2.4, 1, 3, '\"$version\"', '$1')'
#root -l -b -q 'mSortpPb2.C+(false, 0, 40, 0, 500, -2.4, 2.4, 0, 100, '\"$version\"', '$1')'
#root -l -b -q 'mSortpPb2.C+(false, 0, 40, 0, 500, -2.4, 2.4, 1, 3, '\"$version\"', '$1')'
