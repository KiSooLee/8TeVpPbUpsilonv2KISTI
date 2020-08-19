# 8TeVpPbUpsilonv2KISTI

1. Upsilon v2 analysis is using onia analyzer. All the sequences are using onia tree.

2. With the selected track multiplicity, onia tree is skimmed by dataskim.C in order to draw mass distribution. do_skim.sh is used to run dataskim.C

3. To determine pT range, mass distribution is fitted by two Crystal ball function. Initial and final parameters for the Crystal ball are stored in the SkimmedFiles/Parameter/ directory.
	Mass fitting is done in the SkimmedFiles/ directory. Macros are separated into GetYieldData.C and GetYieldMC.C because the fitting range is different for Data and MC. do_GetYield.sh is used to run GetYieldData.C and GetYieldMC.C.
	There is another directory inside the SkimmedFiles/ directory Yield/. The yield distribution is ploted by YieldDist.C. The macro runs by do_YieldDist.sh.

4. Data should be re-weighted by acceptance and efficiency due to signal loss of detector. Acceptance and efficiency are calculated with MC. But MC kinematics are not same with data. So it should be re-weighted.
	From the skimmed MC, SkimmedFiles/MCcount.C counts the yield directly. TnP is applied in this macro.
	SkimmedFiles/Yield/ReweightFunction.C compare the counts of MC and data. From its ratio MC re-weighting function is extracted. In this comparison, data is unweighted yield from GetYieldData.C. SkimmedFiles/Yield/do_FindReweight.sh runs the macro.

5. Calculation of acceptance and efficiency is done in the AccEff/ directory. All the MC re-weighting is added as option in the macors. Acc.C calculate acceptance and DrawAcc.C draw the plot. Eff.C calculate efficiency and DrawEff.C draw the plot. do_Acc.sh and do_Eff.sh run the macros.
	These acceptance and efficiency are applied in the dataskim.C and Correlation/Correl_Reco_same_*.C

6. Trigger and associate particles should be matched to analysis condition. Single muon, dimuon, tracks should be checked. Trigger, soft muon cut, dimuon mass range etc. are applied in the sorting process.
	Sorting process is done in the SortCands/ directory.
	submit_Sort_Pbp1.jds, submit_Sort_Pbp2.jds, submit_Sort_pPb1.jds, submit_Sort_pPb2.jds are submitting batch jobs using condor system. Each file makes 120 jobs which is seperated by 50 MeV mass range.
	Batch job runs do_mSortPbp1.sh, do_mSortPbp2.sh, do_mSortpPb1.sh, do_mSortpPb2.sh and these shells run SortPbp1.C, SortPbp2.C, SortpPb1.C, SortpPb2.C macros. 
	The results are automatically stored in the storage (based on KISTI T3 server).

7. Because of the large tracks, correlation process takes too long time. In order to reduce running time, root file is collected in selected pT, y, multiplicity range.
	Collecting process is done in the CollectingCands/ directory.
	submit_Coll_Pbp1.jds, submit_Coll_Pbp2.jds, submit_Coll_pPb1.jds, submit_Coll_pPb2.jds are used for batch job.
	do_CollectPbp1.sh, do_CollectPbp2.sh, do_CollectpPb1.sh, do_CollectpPb2.sh run the macros.
	Collect_Reco_Pbp1.C, Collect_Reco_Pbp2.C, Collect_Reco_pPb1.C, Collect_Reco_pPb2.C macros are used.
	Due to server issue output files are stored in the scratch. The files should be moved to the storage with movefile.sh

8. With the mass ranges defined in the Headers/Upsilon.h, collected files are merged to retain enough statistics. Using this statistics Upsilon and tracks are correlated (dphi-deta).
	This correlation process is done in the Correlation/ directory.
	Batch job can be used also in this process. submit_Corr_same_Pbp.jds, submit_Corr_same_pPb.jds, submit_Corr_mix_Pbp.jds, submit_Corr_mix_pPb.jds, submit_Corr_trk_same_Pbp.jds, submit_Corr_trk_same_pPb.jds, submit_Corr_trk_mix_Pbp.jds, submit_Corr_trk_mix_pPb.jds are prepared. If there is node issue in the server, local run without batch would be better.
	In this process, same event correlation and mixed event correlation are calculated. The reason why the sorting and collecting are separeted into 1 and 2 is for the mixed event (to avoid same event tracks with trigger).
	And upsilon-track correlation and track-track correlation are separated. They will be subtracted in the later process.
	do_Correl_same_Pbp.sh, do_Correl_same_pPb.sh, do_Correl_mix_Pbp.sh, do_Correl_mix_pPb.sh, do_Correl_trk_same_Pbp.sh, do_Correl_trk_same_pPb.sh, do_Correl_trk_mix_Pbp.sh, do_Correl_trk_mix_pPb.sh are shell for the run.
	Correl_Reco_same_Pbp.C, Correl_Reco_same_pPb.C, Correl_Reco_mix_Pbp.C, Correl_Reco_mix_pPb.C, Correl_trk_Reco_same_Pbp.C, Correl_trk_Reco_same_pPb.C, Correl_trk_Reco_mix_Pbp.C, Correl_trk_Reco_mix_pPb.C are macors.
	Also there are some different macros. Correl_Reco_same_Pbp_jet.C, Correl_Reco_same_pPb_jet.C, Correl_Reco_mix_Pbp_jet.C, Correl_Reco_mix_pPb_jet.C. They are for the jet yield ratio calculation which is used in the low-multiplicity subtraction.

9. The correlated distribution should be projected to dphi axis and divided in order to subtract combinatorial background.
	The projection process is done in the Projection/ directory.
	DrawCorrel.C draws correlation plots of same event and mixed event separately as 2-D deta vs. dphi distribution.
	RatioNProjection.C projects the 2-D plot into dphi axis.
	RatioNProjection_jet.C projects the 2-D plot into dphi axis for the jet yield.
	do_projection.sh runs the macros.

10. The projected dphi plot is expressed as the combination of Fourier harmonics. From the second order parameter v2 value is extracted.
	The extraction process is done in the ExtractV2/ directory.
	extV23.C extracts observed v2 by fitting dN/dphi. do_extV2.sh runs the macro.

11. As mentioned previously, the track component should be subtracted in order to see the v2 of di-muon.
	Track component subtraction is done in the SubtractTrk/ directory.
	Track-track correlation contains square of track while upsilon-track contains one track v2. So the square root of track-track is divided form the upsilon-track.
	do_Subtract.sh runs Subtract_Trk.C macro.
 
12. The v2 after track subtraction is called as observed v2. This observed v2 contains both of signal and background di-muon v2. In order to extract real signal upsilon v2 from the observed v2, signal fraction at each mass point is needed.
	The simultaneous fitting method is applied. The simultaneous function finds parameters satisfying multiple plots. In this analysis mass plot and v2 plot are used. From the mass plot signal fraction is obtained and the signal fraction is used to distinguish v2 from signal and background.
	This process is done in the SignalV2/ directory.
	The two kinds of initial paraemters are used to do the simultaneous fitting. One thing is the result of mass fitting from the SkimmedFiles/ directory. Next thing is background fitting parameter of observed v2 stored in the SignalV2/Parameter/ directory.
	SimultaneousFitData.C macro extracts signal v2 and do_Simul.sh runs the macro.
	DrawSigv2.C macro draw the result v2 distribution and do_Drawv2.sh runs the macro.

13. The extracted v2 is could be not the pure v2. Even if |deta| > 1 is applied to remove jet effect, there is still probability of residual back-to-back jet correlation.
	To remove this jet effect low-multiplicity subtraction is needed because the low-multiplicity events are expected to have only back-to-back jet events.
	This process is done in the LMsub/ directory.
	two factors are needed to calculate the effect of low-multiplicity. The result of low-multiplicity v2 should be scaled by these two factors.
	First factor is jet ratio. Jet yield at the each multiplicity could be different. So low-multiplicity v2 (from the jet) should be scaled to match to high-multiplicity.
	Second factor is number of associator. The number of associator affect to the number of jet yield. Because the number of associator is higher at the high-multiplicity, the jet yield should be scaled with the number of associator.
	The number of associator is calculated with the Nass.C macro. do_Nass.sh runs the macro.
	The jet yield is uses the files for jet study made in the previous step. ZYAM.C fits the minimum value as 0 in order to get jet yield. The fitting range for each bin should be selected in the macro.
	JetYieldRatio.C calculates jet ratio between high and low-multiplicity. This ratio as a function of pT is fitted with constant function because the ratio is expected to be constant regardless of pT.
	These macros run by do_side.sh.
	With the all values from previous step, low-multiplicity is subtracted by LMsub.C macro.
	The macro run by do_sub.sh.
