#!/bin/bash
#Variation.C(multMinhi, multMaxhi, multMinlow, multMaxlow, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, maxF, bkgN, isFine, versionhi, versionlow, Jversionhi, Jversionlow, isAccRW, isEffRW, isTnP, SigSys, BkgSys, MupT)
#Variation_Par.C(multMinhi, multMaxhi, multMinlow, multMaxlow, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, maxF, isFine, versionhi, versionlow, Jversionhi, Jversionlow, MupT, FreeParN)

#root -l 'Variation_Samev2.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v83", "v85", "v86", "v87", true, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 3, false, "v88", "v89", "v86", "v87", true, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, true, false, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, false, true, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", false, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, false, false, false, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, false, false, "3p5")'
#root -l -b -q 'Variation.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, 2, false, "v88", "v89", "v86", "v87", true, true, false, false, "3p5")'
#
#root -l -b -q 'Variation_TnP.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v83", "v85", "v86", "v87", "3p5")'
#
#for((ipar=0; ipar<9; ipar++))
#do
#	root -l -b -q 'Variation_Par.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v88", "v89", "v86", "v87", "3p5", '$ipar')'
#done
#
#root -l 'ParSum.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v83", "v85", "v86", "v87", "3p5")'
#
#root -l -b -q 'Variation_Jvar.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v83", "v85", "v86", "v87", "3p5")'

#root -l 'MCclosure.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, "v90", "v91", "v86", "v87", "3p5")'

root -l -b -q 'VarComp.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, 3, false, "v83", "v85", "v86", "v87", "3p5")'
