#!/bin/bash
#move files from scratch to storage

pTmin=("0" "3" "6" "10")
pTmax=("3" "6" "10" "30")
#pTmin=("10")
#pTmax=("11")
#pTmin=("10")
#pTmax=("30")
#pTmin=("5" "6" "7" "8" "9" "10" "12")
#pTmax=("6" "7" "8" "9" "10" "12" "15")
#pTmin=("9" "10" "12")
#pTmax=("10" "12" "15")
#pTmin=("15" "19")
#pTmax=("19" "30")

for((i=0; i<"${#pTmin[@]}"; i++))
do
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp1/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp2/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb1/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb2/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp1/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp2/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb1/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb2/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp1/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp2/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb1/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb2/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1
	#xrdcp /cms/scratch/kilee/resultPbp1/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultPbp2/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultpPb1/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultpPb2/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/90-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultPbp1/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultPbp2/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultpPb1/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultpPb2/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/0-50_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultPbp1/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultPbp2/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	xrdcp /cms/scratch/kilee/resultpPb1/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/*Gen* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
	#xrdcp /cms/scratch/kilee/resultpPb2/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/0-300_${pTmin[$i]}-${pTmax[$i]}_-24-24_0-3_MupT3p5_trkv1/
done
