#!/bin/bash
#Variation.C(multMinhi, multMaxhi, multMinlow, multMaxlow, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, maxF, bkgN, isFine, versionhi, versionlow, Jversionhi, Jversionlow, isAccRW, isEffRW, isTnP, SigSys, BkgSys, MupT)
#Variation_Par.C(multMinhi, multMaxhi, multMinlow, multMaxlow, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, maxF, isFine, versionhi, versionlow, Jversionhi, Jversionlow, MupT, FreeParN)

#root -l -b -q 'Variation.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 3, false, "v56", "v55", "v65", "v66", true, true, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v56", "v55", "v65", "v66", true, true, true, true, false, "3p5")'
#root -l -b -q 'Variation.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v56", "v55", "v65", "v66", true, true, true, false, true, "3p5")'
#root -l -b -q 'Variation.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v56", "v55", "v65", "v66", false, true, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v56", "v55", "v65", "v66", true, false, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v56", "v55", "v65", "v66", true, true, false, false, false, "3p5")'

#for((ipar=0; ipar<9; ipar++))
#do
#	root -l -b -q 'Variation_Par.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v56", "v55", "v65", "v66", "3p5", '$ipar')'
#done

#root -l 'ParSum.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v56", "v55", "v65", "v66", "3p5")'

#root -l 'Variation_Jvar.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v56", "v55", "v65", "v66", "3p5")'

#root -l 'VarComp.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v56", "v55", "v65", "v66", "3p5")'

root -l 'MCclosure.C+(00, 300, -2.4, 2.4, 0, 3, 3, false, "v73", "3p5")'
