#!/bin/bash
#ZYAM.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, isAccRW, isEffRW, isTnP, MupT, Fine)
#ZYAM_trk.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, TrkptMin, TrkptMax, version, MupT, Fine)
#JetYieldRatio.C(multMinhi, multMaxhi, multMinlow, multMaxlow, rapMin, rapMax, TrkptMin, TrkptMax, versionhi, versionlow, isAccRW, isEffRW, isTnP, SigSys, BkgSys, MupT, Fine)
#CompJRatio.C(Fine, Weight, MupT)

#root -l 'ZYAM.C+(70, 90, 12, 30, -2.4, 2.4, 0, 3, "v96", true, true, 0, "3p5", false)'
#root -l 'ZYAM.C+(70, 300, 10, 12, -2.4, 2.4, 0, 3, "v86", true, true, 5, "3p5", false)'
#root -l 'ZYAM.C+(70, 300, 15, 20, -2.4, 2.4, 0, 3, "v86", true, true, 5, "3p5", false)'
#root -l 'ZYAM.C+(70, 300, 20, 30, -2.4, 2.4, 0, 3, "v86", true, true, 5, "3p5", false)'
#root -l 'ZYAM.C+(0, 50, 10, 12, -2.4, 2.4, 0, 3, "v87", true, true, 5, "3p5", false)'
#root -l 'ZYAM.C+(0, 35, 12, 30, -2.4, 2.4, 0, 3, "v98", true, true, 0, "3p5", false)'
#root -l 'ZYAM.C+(0, 50, 20, 30, -2.4, 2.4, 0, 3, "v87", true, true, 5, "3p5", false)'
#root -l -b -q 'ZYAM.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "v87", true, false, 0, "3p5", false)'
#root -l -b -q 'ZYAM.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "v87", true, true, 1, "3p5", false)'
#root -l -b -q 'ZYAM.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "v87", true, true, 2, "3p5", false)'
#root -l -b -q 'ZYAM.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "v87", true, true, 3, "3p5", false)'
#root -l -b -q 'ZYAM.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "v87", true, true, 4, "3p5", false)'
#root -l -b -q 'ZYAM.C+(0, 50, 15, 20, -2.4, 2.4, 0, 3, "v87", true, true, 5, "3p5", false)'
#root -l 'ZYAM_MC.C+(true, 70, 300, 12, 15, -2.4, 2.4, 0, 3, "v86", "3p5", false)'
#root -l 'ZYAM_MC.C+(true, 0, 50, 12, 15, -2.4, 2.4, 0, 3, "v87", "3p5", false)'
#root -l 'ZYAM_trk.C+(70, 300, 12, 15, -2.4, 2.4, 0, 3, "v86", "3p5", false)'
#root -l 'ZYAM_trk.C+(0, 35, 20, 30, -2.4, 2.4, 0, 3, "v98", "3p5", false)'
#root -l 'ZYAM_trk_MC.C+(true, 70, 300, 15, 20, -2.4, 2.4, 0, 3, "v86", "3p5", false)'
#root -l 'ZYAM_trk_MC.C+(false, 0, 50, 20, 30, -2.4, 2.4, 0, 3, "v87", "3p5", false)'
#root -l 'GetValtest.C+(0, 50, 20, 30, -2.4, 2.4, 0, 3, "v60", true, true, true, "3p5", false)'
#root -l 'ZYAMrange.C+(0, 50, 15, 30, -2.4, 2.4, 0, 3, "v41", true, true, true, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 35, -2.4, 2.4, 0, 3, "v86", "v98", true, true, 0, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", true, true, 0, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", false, true, 0, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", true, false, 0, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", true, true, 1, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", true, true, 2, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", true, true, 3, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", true, true, 4, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", true, true, 5, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", true, true, 0, true, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", true, true, 0, false, true, "3p5", false)'
#root -l 'JetYieldRatio.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, "v65", "v66", true, true, true, true, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, "v65", "v66", true, true, true, false, true, "3p5", false)'
#root -l 'JetYieldRatio.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, "v65", "v66", false, true, true, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, "v65", "v66", true, false, true, false, false, "3p5", false)'
#root -l 'JetYieldRatio.C+(90, 300, 0, 50, -2.4, 2.4, 0, 3, "v65", "v66", true, true, false, false, false, "3p5", false)'
#root -l 'JetYieldRatio_intg.C+(70, 90, 0, 50, -2.4, 2.4, 0, 3, "v96", "v87", true, true, 0, false, false, "3p5", false)'
#root -l 'JetYieldRatio_MC.C+(true, 70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", "3p5", false)'
root -l 'JetYieldRatio_trk.C+(70, 300, 0, 35, -2.4, 2.4, 0, 3, "v86", "v98", "3p5", false)'
#root -l 'JetYieldRatio_trk_intg.C+(120, 300, 0, 50, -2.4, 2.4, 0, 3, "v96", "v87", "3p5", false)'
#root -l 'JetYieldRatio_trk_MC.C+(false, 70, 300, 0, 50, -2.4, 2.4, 0, 3, "v86", "v87", "3p5", false)'
#root -l -b -q 'CompJRatio.C+(false, true, "3p5")'
