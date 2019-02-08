# 8TeVpPbUpsilonv2KISTI

1. pPb v2 study is using track multiplicity instead of centrality. By running GetNtrack.C multiplicity distribution can be achieved.

2. With the selected track multiplicity onia tree is skimmed by dataskim.C in order to draw mass distribution. do_skim.sh is used to run dataskim.C

3. To determine pT range mass distribution is fitted by two Crystal ball function. Initial and final parameters for the Crystal ball are stored in the SkimmedFiles/Parameter/ directory.
	Mass fitting is done by SkimmedFiles/GetYield.C. SkimmedFiles/do_GetYield.sh is used to run GetYield.C

4. Trigger and associate particles should be matched to analysis condition. Single muon, dimuon, tracks should be checked. Trigger, soft muon cut, dimuon mass range etc. are applied in the sorting process.
	submit_Sort_Pbp1.jds, submit_Sort_Pbp2.jds, submit_Sort_pPb1.jds, submit_Sort_pPb2.jds are submit batch jobs using condor system. Each file makes 120 jobs which is seperated by 50 MeV mass range.
	Batch job runs do_mSortPbp1.sh, do_mSortPbp2.sh, do_mSortpPb1.sh, do_mSortpPb2.sh and these shells run mSortPbp1.C, mSortPbp2.C, mSortpPb1.C, mSortpPb2.C macros. 
	The results are automatically stored in the storage.

5. Because of the large events, correlation process takes too long time. In order to reduce running time, root file is collected in selected pT, y, multiplicity range.
	Same jds and shell files with sorting process are used. So jds files need to be modified output name. Shell files also need to be modified command line.
	Collect_Pbp1.C, Collect_Pbp2.C, Collect_pPb1.C, Collect_pPb2.C macros are used.

6. With the mass ranges defined in the Upsilon.h collected files are merged to retain enough statistics. Using this statistics Upsilon and tracks are correlated.
	Correlation also uses batch job. submit_Corr_sig_Pbp.jds, submit_Corr_sig_pPb.jds, submit_Corr_bkg_Pbp.jds, submit_Corr_bkg_pPb.jds are the batch job files.
	Each file runs do_mCorrel_sig_Pbp.sh, do_mCorrel_sig_pPb.sh, do_mCorrel_bkg_Pbp.sh, do_mCorrel_bkg_pPb.sh.
	Each shell runs mCorrel_sig_Pbp.C, mCorrel_sig_pPb.C, mCorrel_bkg_Pbp.C, mCorrel_bkg_pPb.C.

7. DrawCorrel.C draws correlation plots of same event and mixed event separately as 2-D deta vs. dphi distribution.
	do_projection.sh runs the macro.

8. 2-D plot is projected to dphi axis in order to extract v2 by fitting dN/dphi plot. Same event and mixed event are projected separately and same event is divided by mixed event.
	RatioNProjection.C is macro for ratio. do_projection.sh runs this macro also. So command line should be modified.

9. extV2.C extracts observed v2 by fitting dN/dphi. do_extV2.sh runs the macro.

10. Observed v2 is combination of signal v2 and background v2. Separation of signal and background is done by simultaneous fitting of mass and v2. It is assumed that the signal background ratio of mass is same in the v2.
	SimultaneousFit.C macro extracts signal v2. do_Simul.sh runs the macro.

11. DrawSigv2.C draws final signal v2 distribution.
