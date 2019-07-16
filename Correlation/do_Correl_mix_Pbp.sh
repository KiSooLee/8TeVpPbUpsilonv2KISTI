#!/bin/bash
#Correl_mix_Pbp.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, imass)

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

root -l -b -q 'Correl_mix_Pbp.C+(true, 0, 40, 0, 4, -2.4, 2.4, 0, 3, "v18", "3p5", '$1')'
#root -l -b -q 'Correl_mix_Pbp.C+(true, 0, 40, 0, 4, -2.4, 2.4, 0, 3, "v18", "3p5", 7)'
