#!/bin/bash
#dataskim.C(isMC, MupT)

root -l -b -q 'dataskim.C+(false, "3p5")'
root -l -b -q 'dataskim.C+(false, "4")'
