#!/bin/bash
#dataskim.C(isMC, Generation, Weight, isAccRW, isEffRW, isTnP, isSS, MupT)

root -l -b -q 'dataskim.C+(false, 1, true, true, true, 0, false, "3p5")'
#root -l -b -q 'dataskim.C+(false, 1, true, true, true, 0, true, "3p5")'
#root -l -b -q 'dataskim.C+(false, 1, true, false, true, 0, false, "3p5")'
#root -l -b -q 'dataskim.C+(false, 1, true, true, false, 0, false, "3p5")'
#root -l -b -q 'dataskim.C+(false, 1, true, true, true, 1, false, "3p5")'
#root -l -b -q 'dataskim.C+(false, 1, true, true, true, 2, false, "3p5")'
#root -l -b -q 'dataskim.C+(false, 1, true, true, true, 3, false, "3p5")'
#root -l -b -q 'dataskim.C+(false, 1, true, true, true, 4, false, "3p5")'
#root -l -b -q 'dataskim.C+(false, 1, true, true, true, 5, false, "3p5")'
#root -l -b -q 'dataskim.C+(true, 2, false, true, true, true, "3p5")'
#root -l -b -q 'dataskim.C+(true, 3, false, true, true, true, "3p5")'
