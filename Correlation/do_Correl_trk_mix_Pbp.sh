#!/bin/bash
#Correl_trk_Reco_mix_Pbp.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, Weight, imass)
#Correl_trk_Gen_mix_Pbp.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, imass)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 40, 0, 4, -2.4, 2.4, 0, 3, "v18", "3p5", '$1')'
#root -l -b -q 'Correl_trk_Gen_mix_Pbp.C+(0, 40, 0, 4, -2.4, 2.4, 0, 3, "v18", "4", '$1')'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(true, 0, 40, 0, 4, -2.4, 2.4, 0, 3, "v18", "3p5", 8)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp_jet.C+(false, 110, 300, 0, 4, -2.4, 2.4, 0, 3, "v19", "3p5", true, true)'
#root -l -b -q 'Correl_trk_Reco_mix_Pbp_jet.C+(false, 110, 300, 0, 4, -2.4, 2.4, 0, 3, "v19", "3p5", true, false)'
for((i=0; i<20; i++))
do
	root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 110, 300, 0, 4, -2.4, 2.4, 0, 3, "v19", "3p5", true, '$i')'
done
#for((i=0; i<20; i++))
#do
#	root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 40, 0, 4, -2.4, 2.4, 0, 3, "v20", "3p5", true, '$i')'
#done
#for((i=0; i<20; i++))
#do
#	root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 40, 90, 0, 4, -2.4, 2.4, 0, 3, "v21", "3p5", false, '$i')'
#done
#for((i=0; i<20; i++))
#do
#	root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 110, 0, 4, -2.4, 2.4, 0, 3, "v22", "3p5", false, '$i')'
#	root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 110, 0, 4, -2.4, 2.4, 0, 3, "v22", "3p5", false, '$i')'
#	root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 110, 0, 4, -2.4, 2.4, 0, 3, "v22", "3p5", false, '$i')'
#	root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 90, 110, 0, 4, -2.4, 2.4, 0, 3, "v22", "3p5", false, '$i')'
#done
#for((i=0; i<18; i++))
#do
#	root -l -b -q 'Correl_trk_Gen_mix_Pbp.C+(0, 40, 0, 4, -2.4, 2.4, 0, 3, "v18", "4", '$i')'
#done
#for((i=0; i<14; i++))
#do
#	root -l -b -q 'Correl_trk_Reco_mix_Pbp.C+(false, 0, 60, 0, 4, -2.4, 2.4, 0, 3, "v30", "3p5", true, '$i')'
#done
