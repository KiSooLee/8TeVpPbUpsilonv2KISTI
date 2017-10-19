# 8TeVpPbUpsilonv2KISTI

1. Before correlate events the single muon, dimuon, tracks should be checked. Trigger, soft muon cut, dimuon mass range etc. are applied in the sorting process.
	submit_Sort_Pbp1.jds, submit_Sort_Pbp2.jds, submit_Sort_pPb1.jds, submit_Sort_pPb2.jds are submit batch jobs using condor system. Each file makes 120 jobs which is seperated by 50 MeV mass range.
	Batch job runs do_mSortPbp1.sh, do_mSortPbp2.sh, do_mSortpPb1.sh, do_mSortpPb2.sh and these shells run mSortPbp1.C, mSortPbp2.C, mSortpPb1.C, mSortpPb2.C macros. 

2. The Sorted files are heavy. So they should be moved to the storage. StoreSort.sh moves files to the storage and file_check.sh checks if the files are succesfully moved.

3. Correlation also uses batch job. submit_Corr_sig_Pbp.jds, submit_Corr_sig_pPb.jds, submit_Corr_bkg_Pbp.jds, submit_Corr_bkg_pPb.jds are the batch job files.
	Each file runs do_mCorrel_sig_Pbp.sh, do_mCorrel_sig_pPb.sh, do_mCorrel_bkg_Pbp.sh, do_mCorrel_bkg_pPb.sh.
	Each shell runs mCorrel_sig_Pbp.C, mCorrel_sig_pPb.C, mCorrel_bkg_Pbp.C, mCorrel_bkg_pPb.C.

4. Correlated results are stored in the root file and moved by Naming_deta_dphi.sh

5. To draw deta-dphi and dphi projection extV2fromCount_Coarse.C is used. do_extV2.sh runs this macro. This macro makes deta-dphi and dphi plots and root file of dphi.
