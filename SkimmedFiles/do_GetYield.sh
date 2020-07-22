#!/bin/bash
#GetYieldData.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, version, Weight, SigSys, Bkgsys, MupT)
#GetYieldMC(multMin, multMax, ptMin, ptMax, rapMin, rapMax, version, MupT)

#root -l -b -q 'GetYieldData.C+(110, 300, 0, 4, -2.4, 2.4, "v16", "3p5")'
#root -l -b -q 'GetYieldData.C+(110, 300, 4, 7, -2.4, 2.4, "v16", "3p5")'
#root -l -b -q 'GetYieldData.C+(110, 300, 7, 10, -2.4, 2.4, "v16", "3p5")'
#root -l -b -q 'GetYieldData.C+(110, 300, 10, 30, -2.4, 2.4, "v16", "3p5")'

#root -l -b -q 'GetYieldMC.C+(110, 300, 0, 4, -2.4, 2.4, "v16", "4")'
#root -l -b -q 'GetYieldMC.C+(110, 300, 4, 7, -2.4, 2.4, "v16", "4")'
#root -l -b -q 'GetYieldMC.C+(110, 300, 7, 10, -2.4, 2.4, "v16", "4")'
#root -l -b -q 'GetYieldMC.C+(110, 300, 10, 30, -2.4, 2.4, "v16", "4")'

#root -l -b -q 'GetYieldData.C+(0, 40, 0, 4, -2.4, 2.4, "v18", "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 40, 4, 7, -2.4, 2.4, "v18", "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 40, 7, 10, -2.4, 2.4, "v18", "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 40, 10, 30, -2.4, 2.4, "v18", "3p5")'

#root -l -b -q 'GetYieldMC.C+(0, 40, 0, 4, -2.4, 2.4, "v18", "3p5")'
#root -l -b -q 'GetYieldMC.C+(0, 40, 4, 7, -2.4, 2.4, "v18", "3p5")'
#root -l -b -q 'GetYieldMC.C+(0, 40, 7, 10, -2.4, 2.4, "v18", "3p5")'
#root -l -b -q 'GetYieldMC.C+(0, 40, 10, 30, -2.4, 2.4, "v18", "3p5")'

#root -l -b -q 'GetYieldData.C+(90, 300, 0, 3, -2.4, 2.4, "v56", true, false, false, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 300, 3, 6, -2.4, 2.4, "v56", true, false, false, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 300, 6, 10, -2.4, 2.4, "v56", true, false, false, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 300, 10, 30, -2.4, 2.4, "v56", true, false, false, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 300, 0, 2, -2.4, 2.4, "v57", false, false, false, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 300, 2, 4, -2.4, 2.4, "v57", false, false, false, "3p5")'
root -l -b -q 'GetYieldData.C+(0, 300, 4, 6, -2.4, 2.4, "v57", false, false, false, "3p5")'
root -l -b -q 'GetYieldData.C+(0, 300, 6, 8, -2.4, 2.4, "v57", false, false, false, "3p5")'
root -l -b -q 'GetYieldData.C+(0, 300, 8, 10, -2.4, 2.4, "v57", false, false, false, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 300, 10, 15, -2.4, 2.4, "v57", false, false, false, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 300, 15, 30, -2.4, 2.4, "v57", false, false, false, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 300, 9, 10, -2.4, 2.4, "v47", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 300, 10, 12, -2.4, 2.4, "v47", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 300, 12, 15, -2.4, 2.4, "v47", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 300, 15, 30, -2.4, 2.4, "v47", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 0, 3, -2.4, 2.4, "v55", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 3, 6, -2.4, 2.4, "v55", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 6, 10, -2.4, 2.4, "v55", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 10, 30, -2.4, 2.4, "v55", true, "3p5")'
#root -l -b -q 'GetYieldDataNoStat.C+(110, 300, 0, 4, -2.4, 2.4, "v19", true, "3p5")'
#root -l -b -q 'GetYieldDataNoStat.C+(110, 300, 4, 7, -2.4, 2.4, "v19", true, "3p5")'
#root -l -b -q 'GetYieldDataNoStat.C+(110, 300, 7, 10, -2.4, 2.4, "v19", true, "3p5")'
#root -l -b -q 'GetYieldDataNoStat.C+(110, 300, 10, 30, -2.4, 2.4, "v19", true, "3p5")'
#root -l -b -q 'GetYieldDataNoStat.C+(90, 300, 0, 3, -2.4, 2.4, "v56", true, "3p5")'
#root -l -b -q 'GetYieldDataNoStat.C+(90, 300, 3, 6, -2.4, 2.4, "v56", true, "3p5")'
#root -l -b -q 'GetYieldDataNoStat.C+(90, 300, 6, 10, -2.4, 2.4, "v56", true, "3p5")'
#root -l -b -q 'GetYieldDataNoStat.C+(90, 300, 10, 30, -2.4, 2.4, "v56", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 0, 4, -2.4, 2.4, "v51", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 4, 7, -2.4, 2.4, "v51", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 7, 10, -2.4, 2.4, "v51", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 10, 30, -2.4, 2.4, "v51", true, "3p5")'
#root -l -b -q 'GetYieldMC.C+(90, 300, 0, 3, -2.4, 2.4, "v56", "3p5")'
#root -l -b -q 'GetYieldMC.C+(90, 300, 3, 6, -2.4, 2.4, "v56", "3p5")'
#root -l -b -q 'GetYieldMC.C+(90, 300, 6, 10, -2.4, 2.4, "v56", "3p5")'
#root -l -b -q 'GetYieldMC.C+(90, 300, 10, 30, -2.4, 2.4, "v56", "3p5")'
#root -l -b -q 'GetYieldMCNoStat.C+(90, 300, 0, 3, -2.4, 2.4, "v56", "3p5")'
#root -l -b -q 'GetYieldMCNoStat.C+(90, 300, 3, 6, -2.4, 2.4, "v56", "3p5")'
#root -l -b -q 'GetYieldMCNoStat.C+(90, 300, 6, 10, -2.4, 2.4, "v56", "3p5")'
#root -l -b -q 'GetYieldMCNoStat.C+(90, 300, 10, 30, -2.4, 2.4, "v56", "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 0, 4, -2.4, 2.4, "v28", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 4, 7, -2.4, 2.4, "v28", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 7, 10, -2.4, 2.4, "v28", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 50, 10, 30, -2.4, 2.4, "v28", true, "3p5")'
