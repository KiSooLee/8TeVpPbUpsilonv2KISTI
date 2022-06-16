#!/bin/bash
#Correl_trk_Reco_same_pPb.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion)
#Correl_trk_Gen_same_pPb.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 40, 0, 3, -2.4, 2.4, 0, 3, "v18", "3p5", '$1')'
#root -l -b -q 'Correl_trk_Reco_same_pPb_jet.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, true)'
#root -l -b -q 'Correl_trk_Reco_same_pPb_jet.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, false)'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 9, 10, -2.4, 2.4, 0, 3, "v41", "3p5", "v1", true)'

########## GEN ##########
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(70, 300, 0, 3, -2.4, 2.4, 0, 3, "v90", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(70, 300, 3, 6, -2.4, 2.4, 0, 3, "v90", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(70, 300, 6, 10, -2.4, 2.4, 0, 3, "v90", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(70, 300, 10, 30, -2.4, 2.4, 0, 3, "v90", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(70, 300, 0, 30, -2.4, 2.4, 0, 3, "v92", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 50, 0, 3, -2.4, 2.4, 0, 3, "v91", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 50, 3, 6, -2.4, 2.4, 0, 3, "v91", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 50, 6, 10, -2.4, 2.4, 0, 3, "v91", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 50, 10, 30, -2.4, 2.4, 0, 3, "v91", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 50, 0, 30, -2.4, 2.4, 0, 3, "v93", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(70, 300, 12, 15, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(70, 300, 15, 20, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(70, 300, 20, 30, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 50, 12, 15, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Gen_same_pPb.C+(0, 50, 20, 30, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'

########## MC ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 70, 300, 0, 3, -2.4, 2.4, 0, 3, "v90", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 70, 300, 3, 6, -2.4, 2.4, 0, 3, "v90", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 70, 300, 6, 10, -2.4, 2.4, 0, 3, "v90", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 70, 300, 10, 30, -2.4, 2.4, 0, 3, "v90", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 70, 300, 0, 30, -2.4, 2.4, 0, 3, "v92", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v91", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "v91", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "v91", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "v91", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 0, 50, 0, 30, -2.4, 2.4, 0, 3, "v93", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 70, 300, 12, 15, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 70, 300, 15, 20, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 70, 300, 20, 30, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 0, 50, 12, 15, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 0, 50, 15, 20, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(true, 0, 50, 20, 30, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'

########## nominal high-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 90, 0, 30, -2.4, 2.4, 0, 3, "v94", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 120, 0, 30, -2.4, 2.4, 0, 3, "v94", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 120, 300, 0, 30, -2.4, 2.4, 0, 3, "v94", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 0, 3, -2.4, 2.4, 0, 3, "v83", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 3, 6, -2.4, 2.4, 0, 3, "v83", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 6, 10, -2.4, 2.4, 0, 3, "v83", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 10, 30, -2.4, 2.4, 0, 3, "v83", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 0, 30, -2.4, 2.4, 0, 3, "v88", "3p5", "v1")'

########### nominal low-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 35, 0, 30, -2.4, 2.4, 0, 3, "v97", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 35, 3, 6, -2.4, 2.4, 0, 3, "v97", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 35, 6, 10, -2.4, 2.4, 0, 3, "v97", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 35, 10, 30, -2.4, 2.4, 0, 3, "v97", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v85", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "v85", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "v85", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "v85", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 0, 30, -2.4, 2.4, 0, 3, "v89", "3p5", "v1")'

########## jet high-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 90, 12, 30, -2.4, 2.4, 0, 3, "v96", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 90, 120, 12, 30, -2.4, 2.4, 0, 3, "v96", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 120, 300, 12, 30, -2.4, 2.4, 0, 3, "v96", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 9, 10, -2.4, 2.4, 0, 3, "v75", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 10, 12, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 12, 15, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 15, 20, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 300, 20, 30, -2.4, 2.4, 0, 3, "v86", "3p5", "v1")'

########## jet low-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 9, 10, -2.4, 2.4, 0, 3, "v66", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 10, 12, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'
root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 35, 12, 30, -2.4, 2.4, 0, 3, "v98", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 35, 15, 20, -2.4, 2.4, 0, 3, "v98", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 35, 20, 30, -2.4, 2.4, 0, 3, "v98", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 12, 15, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 15, 20, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 20, 30, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 0, 50, 12, 30, -2.4, 2.4, 0, 3, "v87", "3p5", "v1")'

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
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 80, 0, 3, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 80, 3, 6, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 80, 6, 10, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 70, 80, 10, 30, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 80, 90, 0, 3, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 80, 90, 3, 6, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 80, 90, 6, 10, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 80, 90, 10, 30, -2.4, 2.4, 0, 3, "v69", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 45, 55, 0, 3, -2.4, 2.4, 0, 3, "v70", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 45, 55, 3, 6, -2.4, 2.4, 0, 3, "v70", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 45, 55, 6, 10, -2.4, 2.4, 0, 3, "v70", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_same_pPb.C+(false, 45, 55, 10, 30, -2.4, 2.4, 0, 3, "v70", "3p5", "v1")'
