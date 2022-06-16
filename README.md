# 8TeVpPbUpsilonv2KISTI

1. Upsilon v2 analysis is using onia analyzer. All the sequences are using onia tree. You can find how to make onia tree in the following link.
https://twiki.cern.ch/twiki/bin/viewauth/CMS/PPb8TeVUpsilonv2#Analysis_environment_Setting

2. The analysis is based on the two particle correlation method. For the future convenience the onia tree need to be merged to two half file.
e.g) pPb1.root(first half of pPb), pPb2.root (rest half of pPb),
	Pbp1.root (first half of Pbp), Pbp2.root (rest half of Pbp),
	pPb.root (full of pPb), Pbp.root (full of Pbp)

3. With the selected track multiplicity, full case onia tree is skimmed by dataskim.C in order to draw mass distribution. do_skim.sh is used to run dataskim.C

4. To get the initial parameter for the simultaneous fitting, mass distribution is fitted using Roofit. Mass fitting is done in the SkimmedFiles/ directory.
	Macros are separated into GetYieldData.C and GetYieldMC.C because the fitting range and background fucntion are different between Data and MC. do_GetYield.sh is used to run GetYieldData.C and GetYieldMC.C.
	Also there is version for Note or paper named as ~NoStat.C.
	Initial and final parameters for the signal and background are stored in the Parameter/ directory.
	There is another directory inside the SkimmedFiles/ directory Yield/. The yield distribution is ploted by YieldDist.C. The macro runs by do_YieldDist.sh.

5. Data should be re-weighted by acceptance and efficiency due to signal loss of detector. Acceptance and efficiency are calculated from MC. But MC need to be re-weighted because its kinematics could be different from data. 
	From the skimmed MC, SkimmedFiles/MCcount.C counts the yield directly. TnP is applied in this macro.
	SkimmedFiles/Yield/ReweightFunction.C compare the counts of MC and data. From its ratio, MC re-weighting function is extracted. In this comparison, data is unweighted yield from GetYieldData.C. SkimmedFiles/Yield/do_FindReweight.sh runs the macro.

6. Calculation of acceptance and efficiency is done in the AccEff/ directory. All the MC re-weighting is added as option in the macors.
	Acc.C calculates acceptance and DrawAcc.C draw the plot.
	Eff.C calculate efficiency and DrawEff.C draw the plot.
	do_Acc.sh and do_Eff.sh run the macros.
	These acceptance and efficiency are applied in the dataskim.C and Correlation/

7. Trigger and associate particles should be matched to analysis condition. All the event selections are applied in the sorting process.
	Sorting process is done in the SortCands/ directory.
	submit_Sort_Pbp1.jds, submit_Sort_Pbp2.jds, submit_Sort_pPb1.jds, submit_Sort_pPb2.jds submit batch jobs using condor system. Each file makes 120 jobs which is seperated by 50 MeV mass range.
	Batch job runs do_mSortPbp1.sh, do_mSortPbp2.sh, do_mSortpPb1.sh, do_mSortpPb2.sh and these shells run SortPbp1.C, SortPbp2.C, SortpPb1.C, SortpPb2.C macros. 
	The results are automatically stored in the scratch(based on KISTI T3 server). So need to be transfered to storage or local via movefile.sh.

8. Because of the large number of tracks, correlation process takes too long time. In order to reduce running time, root file is collected into selected pT, y, multiplicity range.
	Collecting process is done in the CollectingCands/ directory.
	submit_Coll_Pbp1.jds, submit_Coll_Pbp2.jds, submit_Coll_pPb1.jds, submit_Coll_pPb2.jds are used for batch job.
	do_CollectPbp1.sh, do_CollectPbp2.sh, do_CollectpPb1.sh, do_CollectpPb2.sh run the macros.
	Collect_Reco_Pbp1.C, Collect_Reco_Pbp2.C, Collect_Reco_pPb1.C, Collect_Reco_pPb2.C macros are used.
	This result also stored in the scratch. Can be moved via movefile.sh

9. Based on the mass ranges defined in the Headers/Upsilon.h, collected files are merged to retain enough statistics. Using this statistics Upsilon and tracks are correlated (dphi-deta).
	This correlation process is done in the Correlation/ directory.
	Batch job can be used also in this process. But it is not essential.
	For upsilon-track: submit_Corr_same_Pbp.jds, submit_Corr_same_pPb.jds, submit_Corr_mix_Pbp.jds, submit_Corr_mix_pPb.jds.
	For track-track: submit_Corr_trk_same_Pbp.jds, submit_Corr_trk_same_pPb.jds, submit_Corr_trk_mix_Pbp.jds, submit_Corr_trk_mix_pPb.jds.

	And upsilon-track correlation and track-track correlation are separated. They will be subtracted in the final step.
	For upsilon-track: do_Correl_same_Pbp.sh, do_Correl_same_pPb.sh, do_Correl_mix_Pbp.sh, do_Correl_mix_pPb.sh.
	For track-track: do_Correl_trk_same_Pbp.sh, do_Correl_trk_same_pPb.sh, do_Correl_trk_mix_Pbp.sh, do_Correl_trk_mix_pPb.sh.

	In this process, same event correlation and mixed event correlation are calculated. The reason why the sorting and collecting are separeted into 1 and 2 is for the mixed event (to avoid using same event between trigger and tracks).
	When we choose random event, it should also have similar multiplicity with trigger event. It depends on the multiplicity definition. So you should change in the mixed macro.
	For upsiln-track: Correl_Reco_same_Pbp.C, Correl_Reco_same_pPb.C, Correl_Reco_mix_Pbp.C, Correl_Reco_mix_pPb.C.
	For track-track: Correl_trk_Reco_same_Pbp.C, Correl_trk_Reco_same_pPb.C, Correl_trk_Reco_mix_Pbp.C, Correl_trk_Reco_mix_pPb.C.

	Also there are some different macros for the jet yield ratio calculation which is used in the low-multiplicity subtraction.
	Correl_Reco_same_Pbp_jet.C, Correl_Reco_same_pPb_jet.C, Correl_Reco_mix_Pbp_jet.C, Correl_Reco_mix_pPb_jet.C.

10. The correlated distribution should be projected to dphi axis and divided in order to subtract combinatorial background.
	The projection process is done in the Projection/ directory.
	DrawCorrel.C draws correlation plots of same event and mixed event separately as 2-D deta vs. dphi distribution.
	RatioNProjection.C projects the 2-D plot into dphi axis and divide mixed event from same event.
	RatioNProjection_jet.C projects the 2-D plot into dphi axis for the jet yield.
	do_projection.sh runs the macros.

11. The projected dphi plot is expressed as the combination of Fourier harmonics. The second order parameter is v2 value called observed v2.
	The extraction process is done in the ExtractV2/ directory.
	extV23.C extracts observed v2 by fitting dN/dphi. do_extV2.sh runs the macro.

12. The observed v2 contains both of signal and background di-muon v2. In order to extract real signal upsilon v2 from the observed v2, signal fraction as a function of mass is needed.
	The simultaneous fitting method is applied. The simultaneous function finds parameters satisfying multiple plots. In this analysis, mass plot and v2 plot are used. From the mass plot, signal fraction is obtained and the signal fraction is used to distinguish signal v2.
	This process is done in the SignalV2/ directory.
	The two kinds of initial paraemters are used to do the simultaneous fitting. One thing is the result of mass fitting from the SkimmedFiles/ directory. The other thing is background fitting parameter of observed v2 stored in the SignalV2/Parameter/ directory.
	SimultaneousFitData.C macro extracts signal v2 and do_Simul.sh runs the macro. Also there is macro for MC SimultaneousFitMC.C.
	DrawSigv2.C macro draw the result v2 distribution and do_Drawv2.sh runs the macro.

13. The extracted v2 could be not the pure v2. Even if |deta| > 1 is applied to remove jet effect, there is still probability of residual back-to-back jet correlation.
	To remove this jet effect, low-multiplicity subtraction is needed because the low-multiplicity events are expected to have only back-to-back jet events.
	This process is done in the LMsub/ directory.
	The result of low-multiplicity v2 should be scaled by these two factors.
	First factor is jet yield ratio because the v2 value is proportional to jet yield. So low-multiplicity v2 (from the jet) should be scaled to match to high-multiplicity.
	Second factor is number of associator. The number of jet is proportional to the number of associator. Because the number of associator is higher at the high-multiplicity, the jet yield should be scaled with the number of associator.
	The number of associator is calculated with the Nass.C macro. do_Nass.sh runs the macro.
	The jet yield is uses the files for jet study made in the previous step. ZYAM.C fits the minimum value as 0 in order to get pure jet yield. The fitting range for each bin should be selected in the macro.
	JetYieldRatio.C calculates jet ratio between high and low-multiplicity. This ratio as a function of pT is fitted with constant function because the ratio is expected to be constant regardless of pT.
	These macros run by do_side.sh.
	With the all values from previous step, low-multiplicity is subtracted by LMsub.C macro.
	The macro run by do_sub.sh.
	There are also macros for track-track correlation and MC.

14. As mentioned previously, the track component should be subtracted in order to see the v2 of di-muon.
	Track component subtraction is done in the SubtractTrk/ directory.
	Track-track correlation contains square of track while upsilon-track contains one track v2. So the square root of track-track is divided form the upsilon-track.
	do_Subtract.sh runs Subtract_Trk.C macro.
 
15. While statistical uncertainty is automatically obtained from the fitting, systematical uncertainty need to be calculated. All the variations are included as obtion in the every step.
	The difference between nomial and variation is calculated in the Systematics/ directory.
	Each systematic sources are calculated with Variation_*.C macro. And VarComp.C compare them and add.
	do_Vriation.sh runs all the macros.

16. The final result with systematics and comparison with other result is done in the Final/ directory.
	Significance.C macro draw the result and do_Final.sh runs the macro.
