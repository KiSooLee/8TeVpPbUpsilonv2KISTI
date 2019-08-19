#!/bin/bash
#Correl_Reco_mix_Pbp.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, imass)
#Correl_Gen_mix_Pbp.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, imass)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Correl_Reco_mix_Pbp.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v17", "3p5", '$1')'
#root -l -b -q 'Correl_Gen_mix_Pbp.C+(0, 40, 10, 30, -2.4, 2.4, 0, 3, "v17", "3p5", '$1')'
for((i=0; i<18; i++))
do
	root -l -b -q 'Correl_Reco_mix_Pbp.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v17", "3p5", '$i')'
done
#root -l -b -q 'Correl_Gen_mix_Pbp.C+(0, 40, 10, 30, -2.4, 2.4, 0, 3, "v17", "3p5", 7)'
