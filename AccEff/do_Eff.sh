#!/bin/bash
#Eff.C(Generation, MupT, isRW, isTnP)

root -l -b -q 'Eff.C+(1, "3p5", false, true)'
root -l -b -q 'Eff.C+(1, "3p5", true, true)'
root -l -b -q 'Eff.C+(1, "3p5", true, false)'
#root -l -b -q 'DrawEff.C+(1, "3p5", true)'
