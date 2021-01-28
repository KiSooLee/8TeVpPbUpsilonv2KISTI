#!/bin/bash
#move files from scratch to storage

mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp1/total_MupT3p5/
mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp2/total_MupT3p5/
mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb1/total_MupT3p5/
mkdir /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb2/total_MupT3p5/
rm /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp1/total_MupT3p5/*MC*.root
rm /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultPbp2/total_MupT3p5/*MC*.root
rm /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb1/total_MupT3p5/*MC*.root
rm /xrootd_user/kilee/xrootd/pPb_8TeV_OniaTrkTree/resultpPb2/total_MupT3p5/*MC*.root
xrdcp /cms/scratch/kilee/resultPbp1/total_MupT3p5/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/total_MupT3p5/
xrdcp /cms/scratch/kilee/resultPbp2/total_MupT3p5/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/total_MupT3p5/
xrdcp /cms/scratch/kilee/resultpPb1/total_MupT3p5/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/total_MupT3p5/
xrdcp /cms/scratch/kilee/resultpPb2/total_MupT3p5/* root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/total_MupT3p5/
