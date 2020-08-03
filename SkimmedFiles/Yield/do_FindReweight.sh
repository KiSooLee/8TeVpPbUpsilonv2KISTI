#!/bin/bash
#ReweightFunction.C(multMin, multMax, version, MupT)

version="v57"
root -l -b -q 'ReweightFunction.C+(0, 300, '\"$version\"', "3p5")'
#root -l 'ReweightFunction.C+(0, 300, '\"$version\"', "3p5")'
