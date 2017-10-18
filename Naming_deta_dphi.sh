#!/bin/bash

multMin="0"
multMax="100"
ptMin="0"
ptMax="500"
rapMin="-24"
rapMax="24"
TrkptMin="1"
TrkptMax="3"
ndeta="33"
ndphi="33"
version="v1"
nmbin="20"

for((i=0; i<20; i++))
do
	mv deta-dphi_Pbp_distribution_sig_$i.root SortFiles/Sig/deta-dphi_Pbp_distribution_sig_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_neta_$ndeta\_nphi_$ndphi\_$version\_$nmbin\mbin_$i.root
	mv deta-dphi_pPb_distribution_sig_$i.root SortFiles/Sig/deta-dphi_pPb_distribution_sig_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_neta_$ndeta\_nphi_$ndphi\_$version\_$nmbin\mbin_$i.root
	mv deta-dphi_Pbp_distribution_bkg_$i.root SortFiles/Bkg/deta-dphi_Pbp_distribution_bkg_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_neta_$ndeta\_nphi_$ndphi\_$version\_$nmbin\mbin_$i.root
	mv deta-dphi_pPb_distribution_bkg_$i.root SortFiles/Bkg/deta-dphi_pPb_distribution_bkg_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_neta_$ndeta\_nphi_$ndphi\_$version\_$nmbin\mbin_$i.root
done
