#!/bin/bash
#YieldDist.C(version, Weight, isAccRW, isEffRW, isTnP, SigSys, BkgSys, MupT)

version="v56"
root -l -b -q 'YieldDist.C+('\"$version\"', true, true, true, true, false, false, "3p5")'
root -l -b -q 'YieldDist.C+('\"$version\"', true, true, true, true, true, false, "3p5")'
root -l -b -q 'YieldDist.C+('\"$version\"', true, true, true, true, false, true, "3p5")'
root -l -b -q 'YieldDist.C+('\"$version\"', true, false, true, true, false, false, "3p5")'
root -l -b -q 'YieldDist.C+('\"$version\"', true, true, false, true, false, false, "3p5")'
root -l -b -q 'YieldDist.C+('\"$version\"', true, true, true, false, false, false, "3p5")'

########## for re-weighting ##########
#root -l -b -q 'YieldDist.C+('\"$version\"', false, false, false, false, false, false, "3p5")'
