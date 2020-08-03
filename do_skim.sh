#!/bin/bash
#dataskim.C(isMC, Generation, Weight, isAccRW, isEffRW, isTnP, MupT)

root -l -b -q 'dataskim.C+(true, 1, false, true, true, true, "3p5")'
#root -l -b -q 'dataskim.C+(false, 1, false, true, true, true, "3p5")'
