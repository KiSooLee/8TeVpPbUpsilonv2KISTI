#!/bin/bash
#GetYield.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, version, Weight, MupT)

#version="v13"
#root -l -b -q 'GetYield.C+(0, 300, 0, 4, -2.4, 2.4, "v2")'
#root -l -b -q 'GetYield.C+(0, 300, 4, 6, -2.4, 2.4, "v2")'
#root -l -b -q 'GetYield.C+(0, 300, 6, 10, -2.4, 2.4, "v2")'
#root -l -b -q 'GetYield.C+(0, 300, 10, 30, -2.4, 2.4, "v2")'

#root -l -b -q 'GetYield.C+(110, 300, 0, 4, -2.4, 2.4, "v13")'
#root -l -b -q 'GetYield.C+(110, 300, 4, 6, -2.4, 2.4, "v13")'
#root -l -b -q 'GetYield.C+(110, 300, 6, 10, -2.4, 2.4, "v13")'
#root -l -b -q 'GetYield.C+(110, 300, 10, 30, -2.4, 2.4, "v13")'

#root -l -b -q 'GetYield.C+(0, 300, 0, 4, -2.4, 2.4, "v15")'
#root -l -b -q 'GetYield.C+(0, 300, 4, 7, -2.4, 2.4, "v15")'
#root -l -b -q 'GetYield.C+(0, 300, 7, 10, -2.4, 2.4, "v15")'
#root -l -b -q 'GetYield.C+(0, 300, 10, 30, -2.4, 2.4, "v15")'

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

#root -l -b -q 'GetYieldData.C+(0, 40, 0, 4, -2.4, 2.4, "v18", "4")'
#root -l -b -q 'GetYieldData.C+(0, 40, 4, 7, -2.4, 2.4, "v18", "4")'
#root -l -b -q 'GetYieldData.C+(0, 40, 7, 10, -2.4, 2.4, "v18", "4")'
#root -l -b -q 'GetYieldData.C+(0, 40, 10, 30, -2.4, 2.4, "v18", "4")'

#root -l -b -q 'GetYieldMC.C+(0, 40, 0, 4, -2.4, 2.4, "v18", "3p5")'
#root -l -b -q 'GetYieldMC.C+(0, 40, 4, 7, -2.4, 2.4, "v18", "3p5")'
#root -l -b -q 'GetYieldMC.C+(0, 40, 7, 10, -2.4, 2.4, "v18", "3p5")'
#root -l -b -q 'GetYieldMC.C+(0, 40, 10, 30, -2.4, 2.4, "v18", "3p5")'

#root -l -b -q 'GetYieldMC.C+(0, 40, 0, 4, -2.4, 2.4, "v18", "4")'
#root -l -b -q 'GetYieldMC.C+(0, 40, 4, 7, -2.4, 2.4, "v18", "4")'
#root -l -b -q 'GetYieldMC.C+(0, 40, 7, 10, -2.4, 2.4, "v18", "4")'
#root -l -b -q 'GetYieldMC.C+(0, 40, 10, 30, -2.4, 2.4, "v18", "4")'

root -l -b -q 'GetYieldData.C+(110, 300, 0, 4, -2.4, 2.4, "v19", true, "3p5")'
root -l -b -q 'GetYieldData.C+(110, 300, 4, 7, -2.4, 2.4, "v19", true, "3p5")'
root -l -b -q 'GetYieldData.C+(110, 300, 7, 10, -2.4, 2.4, "v19", true, "3p5")'
root -l -b -q 'GetYieldData.C+(110, 300, 10, 30, -2.4, 2.4, "v19", true, "3p5")'

#root -l -b -q 'GetYieldData.C+(0, 40, 0, 4, -2.4, 2.4, "v20", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 40, 4, 7, -2.4, 2.4, "v20", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 40, 7, 10, -2.4, 2.4, "v20", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(0, 40, 10, 30, -2.4, 2.4, "v20", true, "3p5")'

#root -l -b -q 'GetYieldData.C+(40, 90, 0, 4, -2.4, 2.4, "v21", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(40, 90, 4, 7, -2.4, 2.4, "v21", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(40, 90, 7, 10, -2.4, 2.4, "v21", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(40, 90, 10, 30, -2.4, 2.4, "v21", true, "3p5")'

#root -l -b -q 'GetYieldData.C+(90, 110, 0, 4, -2.4, 2.4, "v22", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 110, 4, 7, -2.4, 2.4, "v22", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 110, 7, 10, -2.4, 2.4, "v22", true, "3p5")'
#root -l -b -q 'GetYieldData.C+(90, 110, 10, 30, -2.4, 2.4, "v22", true, "3p5")'

