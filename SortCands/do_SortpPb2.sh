#!/bin/bash
#SortpPb2_Reco.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, MupT, isSS, imass)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'SortpPb2_Reco.C+(true, 0, 1500, 0, 30, -2.4, 2.4, 0, 10, "3p5", false, '$1')'
#root -l -b -q 'SortpPb2_Reco.C+(false, 0, 1500, 0, 30, -2.4, 2.4, 0, 10, "3p5", false, 51)'
root -l -b -q 'SortpPb2_Gen.C+(0, 1500, 0, 30, -2.4, 2.4, 0, 10, "3p5")'
