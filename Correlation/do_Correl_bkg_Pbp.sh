#!/bin/bash
#Correl_bkg_Pbp.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, imass)

#version="v11"

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

root -l -b -q 'Correl_bkg_Pbp.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v17", "3p5", '$1')'
#ls
#root -l -b -q 'Correl_bkg_Pbp.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v16", 8)'
