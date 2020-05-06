#!/bin/bash
#move files from scratch to storage

pTmin=("0" "4" "7")
pTmax=("4" "7" "10")

for((i=0; i<"${#pTmin[@]}"; i++))
do
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp1/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp2/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb1/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb2/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5
	xrdcp /cms/scratch/kilee/resultPbp1/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5/
	xrdcp /cms/scratch/kilee/resultPbp2/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5/
	xrdcp /cms/scratch/kilee/resultpPb1/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5/
	xrdcp /cms/scratch/kilee/resultpPb2/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/0-60_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5/
done
