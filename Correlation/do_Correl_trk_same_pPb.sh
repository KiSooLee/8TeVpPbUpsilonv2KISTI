#!/bin/bash
#Correl_trk_Reco_same_pPb.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion)
#Correl_trk_Gen_same_pPb.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 40, 0, 3, -2.4, 2.4, 0, 3, "v18", "3p5", '$1')'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 40, 0, 3, -2.4, 2.4, 0, 3, "v18", "4", '$1')'
#root -l -b -q 'Correl_trk_Reco_same_pPb_jet.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, true)'
#root -l -b -q 'Correl_trk_Reco_same_pPb_jet.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, false)'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 9, 10, -2.4, 2.4, 0, 3, "v41", "3p5", "v1", true)'

########## nominal high-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 300, 0, 3, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 300, 3, 6, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 300, 6, 10, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 300, 10, 30, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true)'

########### nominal low-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true)'

########## jet high-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 300, 11, 15, -2.4, 2.4, 0, 3, "v67", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 300, 15, 19, -2.4, 2.4, 0, 3, "v67", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 300, 19, 30, -2.4, 2.4, 0, 3, "v67", "3p5", "v1")'

########## jet low-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 11, 15, -2.4, 2.4, 0, 3, "v68", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 15, 19, -2.4, 2.4, 0, 3, "v68", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 19, 30, -2.4, 2.4, 0, 3, "v68", "3p5", "v1")'

########## low-multiplicity scan ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 40, 50, 0, 3, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 40, 50, 3, 6, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 40, 50, 6, 10, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 40, 50, 10, 30, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 50, 60, 0, 3, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 50, 60, 3, 6, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 50, 60, 6, 10, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 50, 60, 10, 30, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 60, 70, 0, 3, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 60, 70, 3, 6, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 60, 70, 6, 10, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 60, 70, 10, 30, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 45, 55, 0, 3, -2.4, 2.4, 0, 3, "v70", "3p5", "v1")'
root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 45, 55, 3, 6, -2.4, 2.4, 0, 3, "v70", "3p5", "v1")'
root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 45, 55, 6, 10, -2.4, 2.4, 0, 3, "v70", "3p5", "v1")'
root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 45, 55, 10, 30, -2.4, 2.4, 0, 3, "v70", "3p5", "v1")'
