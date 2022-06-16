#!/bin/bash
#Eff.C(Generation, MupT, isRW, isTnP)
#DrawEff.C(Generation, MupT, isRW, isTnP)
#DrawAccEff.C(Generation, MupT, isRW, isTnP)

root -l -b -q 'Eff.C+(1, "3p5", true, 0)'
root -l -b -q 'Eff.C+(1, "3p5", true, 1)'
root -l -b -q 'Eff.C+(1, "3p5", true, 2)'
root -l -b -q 'Eff.C+(1, "3p5", true, 3)'
root -l -b -q 'Eff.C+(1, "3p5", true, 4)'
root -l -b -q 'Eff.C+(1, "3p5", true, 5)'
root -l -b -q 'Eff.C+(1, "3p5", false, 0)'
#root -l -b -q 'Eff.C+(1, "10", true, true)'
#root -l -b -q 'DrawEff.C+(1, "3p5", false, true)'
#root -l -b -q 'DrawEff.C+(1, "3p5", true, true)'
#root -l -b -q 'DrawEff.C+(1, "3p5", true, false)'
