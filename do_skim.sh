#!/bin/bash
#dataskim.C(isMC, Weight, MupT)

root -l -b -q 'dataskim.C+(false, true, "3p5")'
root -l -b -q 'dataskim.C+(false, true, "4")'
