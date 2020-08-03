#!/bin/bash
#YieldDist.C(version, Weight, isAccRW, isEffRW, isTnP, SigSys, BkgSys, MupT)

version="v57"
root -l -b -q 'YieldDist.C+('\"$version\"', false, false, false, false, false, false, "3p5")'
