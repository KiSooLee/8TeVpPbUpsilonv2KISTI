#!/bin/bash
#move files from scratch to storage

pTmin=("0" "4" "7" "10")
pTmax=("4" "7" "10" "30")

for((i=0; i<"${#pTmin[@]}"; i++))
do
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp1/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp2/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb1/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb2/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp1/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp2/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb1/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb2/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	xrdcp /cms/scratch/kilee/resultPbp1/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	xrdcp /cms/scratch/kilee/resultPbp2/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	xrdcp /cms/scratch/kilee/resultpPb1/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	xrdcp /cms/scratch/kilee/resultpPb2/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/120-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	xrdcp /cms/scratch/kilee/resultPbp1/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	xrdcp /cms/scratch/kilee/resultPbp2/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	xrdcp /cms/scratch/kilee/resultpPb1/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	xrdcp /cms/scratch/kilee/resultpPb2/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/100-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
done
