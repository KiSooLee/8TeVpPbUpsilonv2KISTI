#!/bin/bash

multMin="100"
multMax="1500"
ptMin="0"
ptMax="500"
rapMin="-24"
rapMax="24"
TrkptMin="0"
TrkptMax="100"
version="v1"

rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/Sort_OniaTree_Pbp1_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_*.root
rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/Sort_OniaTree_Pbp2_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_*.root
rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/Sort_OniaTree_pPb1_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_*.root
rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/Sort_OniaTree_pPb2_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_*.root

for((i=0; i<120; i++))
do
	cp Sort_OniaTree_Pbp1_PADoubleMuon_$i.root /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/Sort_OniaTree_Pbp1_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_$i.root
	cp Sort_OniaTree_Pbp2_PADoubleMuon_$i.root /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/Sort_OniaTree_Pbp2_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_$i.root
	cp Sort_OniaTree_pPb1_PADoubleMuon_$i.root /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/Sort_OniaTree_pPb1_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_$i.root
	cp Sort_OniaTree_pPb2_PADoubleMuon_$i.root /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/Sort_OniaTree_pPb2_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_$i.root
done
