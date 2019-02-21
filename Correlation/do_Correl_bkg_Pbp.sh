#!/bin/bash
#Correl_bkg_Pbp.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version)

#version="v11"

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

root -l -b -q 'Correl_bkg_Pbp.C+(false, 110, 300, 0, 4, -2.4, 2.4, 0, 3, "v16", '$1')'
#ls
#root -l -b -q 'mCorrel_bkg_Pbp.C+(false, 110, 300, 0, 4, -2.4, 2.4, 0, 3, "v16", 0)'
