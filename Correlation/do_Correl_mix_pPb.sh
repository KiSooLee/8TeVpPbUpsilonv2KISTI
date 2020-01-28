#!/bin/bash
#Correl_Reco_mix_pPb.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, imass)
#Correl_Gen_mix_pPb.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version, MupT, imass)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

#root -l -b -q 'Correl_Reco_mix_pPb.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "4", '$1')'
#root -l -b -q 'Correl_Gen_mix_pPb.C+(0, 40, 10, 30, -2.4, 2.4, 0, 3, "v17", "4", '$1')'
#root -l -b -q 'Correl_Reco_mix_pPb.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "4", 4)'
for((i=0; i<20; i++))
do
	root -l -b -q 'Correl_Reco_mix_pPb.C+(false, 110, 300, 10, 30, -2.4, 2.4, 0, 3, "v19", "3p5", true, '$i')'
done
#for((i=0; i<20; i++))
#do
#	root -l -b -q 'Correl_Reco_mix_pPb.C+(false, 0, 40, 10, 30, -2.4, 2.4, 0, 3, "v20", "3p5", '$i')'
#done
#root -l -b -q 'Correl_Gen_mix_pPb.C+(0, 40, 10, 30, -2.4, 2.4, 0, 3, "v17", "4", 7)'
