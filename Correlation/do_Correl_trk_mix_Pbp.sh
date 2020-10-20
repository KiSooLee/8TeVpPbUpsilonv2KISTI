#!/bin/bash
#Correl_trk_Reco_mix_Pbp.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, trkptversion)
#Correl_trk_Gen_mix_Pbp.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 40, 0, 3, -2.4, 2.4, 0, 3, "v18", "3p5", '$1')'
#root -l -b -q 'Correl_trk_Gen_mix_Pbp.C+(0, 40, 0, 3, -2.4, 2.4, 0, 3, "v18", "4", '$1')'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(true, 0, 40, 0, 3, -2.4, 2.4, 0, 3, "v18", "3p5", 8)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp_jet.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, true)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp_jet.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, false)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 9, 10, -2.4, 2.4, 0, 3, "v60", "3p5", "v1", true)'

########## nominal high-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 300, 0, 3, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 300, 3, 6, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 300, 6, 10, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 300, 10, 30, -2.4, 2.4, 0, 3, "v56", "3p5", "v1", true)'

########## nominal low-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 3, 6, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 6, 10, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 10, 30, -2.4, 2.4, 0, 3, "v55", "3p5", "v1", true)'

#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, 18)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, 19)'

########## jet high-multiplicity ##########
root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 300, 11, 15, -2.4, 2.4, 0, 3, "v67", "3p5", "v1")'
root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 300, 15, 19, -2.4, 2.4, 0, 3, "v67", "3p5", "v1")'
root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 300, 19, 30, -2.4, 2.4, 0, 3, "v67", "3p5", "v1")'

########## jet low-multiplicity ##########
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 11, 15, -2.4, 2.4, 0, 3, "v68", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 15, 19, -2.4, 2.4, 0, 3, "v68", "3p5", "v1")'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 19, 30, -2.4, 2.4, 0, 3, "v68", "3p5", "v1")'

#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v42", "3p5", "v1", true, 9)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 50, 0, 3, -2.4, 2.4, 0, 3, "v42", "3p5", "v1", true, 10)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 45, 55, 0, 3, -2.4, 2.4, 0, 3, "v50", "3p5", "v1", true, 0)'
