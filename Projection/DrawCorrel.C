//Headers{{{
#include <Riostream.h> 
#include <TSystem.h> 
#include <TBrowser.h> 
#include <TROOT.h> 
#include <TStyle.h> 
#include <TFile.h> 
#include <TTree.h>
#include <TNtuple.h> 
#include <TCanvas.h> 
#include <TGraph.h> 
#include <TGraphAsymmErrors.h> 
#include <TGraphErrors.h> 
#include <TH1.h> 
#include <TH2.h> 
#include <TF1.h> 
#include <TProfile.h> 
#include <TMath.h> 
#include <TLegend.h> 
#include <TString.h> 
#include <TLatex.h> 
#include <TInterpreter.h> 
#include <fstream>
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
//}}}

void DrawCorrel(const Bool_t isMC = false, const Bool_t isTrk = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TString MupT = "4")
{ 
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fullDIR = mainDIR + Form("/CorrDist/CorrDistFullRatio/%s/MupT%s", version.Data(), MupT.Data());
	TString fullsameDIR = mainDIR + Form("/CorrDist/CorrDistFullSame/%s/MupT%s", version.Data(), MupT.Data());
	TString fullmixDIR = mainDIR + Form("/CorrDist/CorrDistFullMix/%s/MupT%s", version.Data(), MupT.Data());
	TString cut1DIR = mainDIR + Form("/CorrDist/CorrDistCut1Ratio/%s/MupT%s", version.Data(), MupT.Data());
	TString cut1sameDIR = mainDIR + Form("/CorrDist/CorrDistCut1Same/%s/MupT%s", version.Data(), MupT.Data());
	TString cut1mixDIR = mainDIR + Form("/CorrDist/CorrDistCut1Mix/%s/MupT%s", version.Data(), MupT.Data());
	TString cut1p5DIR = mainDIR + Form("/CorrDist/CorrDistCut1p5Ratio/%s/MupT%s", version.Data(), MupT.Data());
	TString cut1p5sameDIR = mainDIR + Form("/CorrDist/CorrDistCut1p5Same/%s/MupT%s", version.Data(), MupT.Data());
	TString cut1p5mixDIR = mainDIR + Form("/CorrDist/CorrDistCut1p5Mix/%s/MupT%s", version.Data(), MupT.Data());
	TString cut2DIR = mainDIR + Form("/CorrDist/CorrDistCut2Ratio/%s/MupT%s", version.Data(), MupT.Data());
	TString cut2sameDIR = mainDIR + Form("/CorrDist/CorrDistCut2Same/%s/MupT%s", version.Data(), MupT.Data());
	TString cut2mixDIR = mainDIR + Form("/CorrDist/CorrDistCut2Mix/%s/MupT%s", version.Data(), MupT.Data());

	void * dirf = gSystem->OpenDirectory(fullDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fullDIR.Data(), kTRUE);

	void * dirfs = gSystem->OpenDirectory(fullsameDIR.Data());
	if(dirfs) gSystem->FreeDirectory(dirfs);
	else gSystem->mkdir(fullsameDIR.Data(), kTRUE);

	void * dirfb = gSystem->OpenDirectory(fullmixDIR.Data());
	if(dirfb) gSystem->FreeDirectory(dirfb);
	else gSystem->mkdir(fullmixDIR.Data(), kTRUE);

	void * dirc1 = gSystem->OpenDirectory(cut1DIR.Data());
	if(dirc1) gSystem->FreeDirectory(dirc1);
	else gSystem->mkdir(cut1DIR.Data(), kTRUE);

	void * dirc1s = gSystem->OpenDirectory(cut1sameDIR.Data());
	if(dirc1s) gSystem->FreeDirectory(dirc1s);
	else gSystem->mkdir(cut1sameDIR.Data(), kTRUE);

	void * dirc1b = gSystem->OpenDirectory(cut1mixDIR.Data());
	if(dirc1b) gSystem->FreeDirectory(dirc1b);
	else gSystem->mkdir(cut1mixDIR.Data(), kTRUE);

	void * dirc1p5 = gSystem->OpenDirectory(cut1p5DIR.Data());
	if(dirc1p5) gSystem->FreeDirectory(dirc1p5);
	else gSystem->mkdir(cut1p5DIR.Data(), kTRUE);

	void * dirc1p5s = gSystem->OpenDirectory(cut1p5sameDIR.Data());
	if(dirc1p5s) gSystem->FreeDirectory(dirc1p5s);
	else gSystem->mkdir(cut1p5sameDIR.Data(), kTRUE);

	void * dirc1p5b = gSystem->OpenDirectory(cut1p5mixDIR.Data());
	if(dirc1p5b) gSystem->FreeDirectory(dirc1p5b);
	else gSystem->mkdir(cut1p5mixDIR.Data(), kTRUE);

	void * dirc2 = gSystem->OpenDirectory(cut2DIR.Data());
	if(dirc2) gSystem->FreeDirectory(dirc2);
	else gSystem->mkdir(cut2DIR.Data(), kTRUE);

	void * dirc2s = gSystem->OpenDirectory(cut2sameDIR.Data());
	if(dirc2s) gSystem->FreeDirectory(dirc2s);
	else gSystem->mkdir(cut2sameDIR.Data(), kTRUE);

	void * dirc2b = gSystem->OpenDirectory(cut2mixDIR.Data());
	if(dirc2b) gSystem->FreeDirectory(dirc2b);
	else gSystem->mkdir(cut2mixDIR.Data(), kTRUE);
//}}}

	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString Direction[2] = {"Pbp", "pPb"};
	TString Away[4] = {"Full", "2", "1p5", "1"};
	TString Trk;
	if(isTrk) Trk = "trk_";
	else Trk = "";

	TFile *samePbp[2];
	TFile *mixPbp[2];

//Define canvas and histogram{{{

//Define canvas{{{
	TCanvas* c_ratio_reco_fine[4];
	TCanvas* c_same_reco_fine[4];
	TCanvas* c_mix_reco_fine[4];
	TCanvas* c_ratio_reco_coarse[4];
	TCanvas* c_same_reco_coarse[4];
	TCanvas* c_mix_reco_coarse[4];
	TCanvas* c_ratio_gen_fine[4];
	TCanvas* c_same_gen_fine[4];
	TCanvas* c_mix_gen_fine[4];
	TCanvas* c_ratio_gen_coarse[4];
	TCanvas* c_same_gen_coarse[4];
	TCanvas* c_mix_gen_coarse[4];
	for(Int_t iaway = 0; iaway < 4; iaway++)
	{
		if(isMC)
		{
			c_ratio_gen_fine[iaway] = new TCanvas(Form("c_ratio_gen%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
			c_same_gen_fine[iaway] = new TCanvas(Form("c_same_gen%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
			c_mix_gen_fine[iaway] = new TCanvas(Form("c_mix_gen%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
			c_ratio_gen_coarse[iaway] = new TCanvas(Form("c_ratio_gen%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
			c_same_gen_coarse[iaway] = new TCanvas(Form("c_same_gen%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
			c_mix_gen_coarse[iaway] = new TCanvas(Form("c_mix_gen%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		}
		c_ratio_reco_fine[iaway] = new TCanvas(Form("c_ratio_reco%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_same_reco_fine[iaway] = new TCanvas(Form("c_same_reco%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_mix_reco_fine[iaway] = new TCanvas(Form("c_mix_reco%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_ratio_reco_coarse[iaway] = new TCanvas(Form("c_ratio_reco%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_same_reco_coarse[iaway] = new TCanvas(Form("c_same_reco%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_mix_reco_coarse[iaway] = new TCanvas(Form("c_mix_reco%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
	}
//}}}

//Define histogram{{{
	TH2D *hSamePbpReco_fine[4][2];
	TH2D *hSamePbpGen_fine[4][2];
	TH2D *hMixPbpReco_fine[4][2];
	TH2D *hMixPbpGen_fine[4][2];
	TH2D *hSamePbpReco_coarse[4][2];
	TH2D *hSamePbpGen_coarse[4][2];
	TH2D *hMixPbpReco_coarse[4][2];
	TH2D *hMixPbpGen_coarse[4][2];
//}}}

//}}}

//define muon pt value{{{
	Double_t MupTCut;
	if(MupT == "0") MupTCut = 0;
	else if(MupT == "0p5") MupTCut = 0.5;
	else if(MupT == "1") MupTCut = 1.0;
	else if(MupT == "1p5") MupTCut = 1.5;
	else if(MupT == "2") MupTCut = 2.0;
	else if(MupT == "2p5") MupTCut = 2.5;
	else if(MupT == "3") MupTCut = 3.0;
	else if(MupT == "3p5") MupTCut = 3.5;
	else if(MupT == "4") MupTCut = 4.0;
	else
	{
		cout << "There is no such muon pT cut value" << endl;
		return;
	}
//}}}

	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->SetNDC();

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{
//Get files{{{
		for(Int_t ipPb = 0; ipPb < 2; ipPb++)
		{
			samePbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/%sdeta-dphi_%s_distribution_same_%s_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Direction[ipPb].Data(), MorD.Data(), imass), "READ");
			mixPbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/%sdeta-dphi_%s_distribution_mix_%s_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Direction[ipPb].Data(), MorD.Data(), imass), "READ");
		}
//}}}

		for(Int_t iaway = 0; iaway < 4; iaway++)
		{
			for(Int_t ipPb = 0; ipPb < 2; ipPb++)
			{
//get plot{{{
				if(isMC)
				{
					hSamePbpGen_fine[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sGen%d_1", Direction[ipPb].Data(), iaway+1));
					hSamePbpGen_coarse[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sGen%d_2", Direction[ipPb].Data(), iaway+1));
					hMixPbpGen_fine[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sGen%d_1", Direction[ipPb].Data(), iaway+1));
					hMixPbpGen_coarse[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sGen%d_2", Direction[ipPb].Data(), iaway+1));
					hSamePbpGen_fine[iaway][ipPb]->Sumw2();
					hSamePbpGen_coarse[iaway][ipPb]->Sumw2();
					hMixPbpGen_fine[iaway][ipPb]->Sumw2();
					hMixPbpGen_coarse[iaway][ipPb]->Sumw2();
				}
				hSamePbpReco_fine[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sReco%d_1", Direction[ipPb].Data(), iaway+1));
				hSamePbpReco_coarse[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sReco%d_2", Direction[ipPb].Data(), iaway+1));
				hMixPbpReco_fine[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sReco%d_1", Direction[ipPb].Data(), iaway+1));
				hMixPbpReco_coarse[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sReco%d_2", Direction[ipPb].Data(), iaway+1));
				hSamePbpReco_fine[iaway][ipPb]->Sumw2();
				hSamePbpReco_coarse[iaway][ipPb]->Sumw2();
				hMixPbpReco_fine[iaway][ipPb]->Sumw2();
				hMixPbpReco_coarse[iaway][ipPb]->Sumw2();
//}}}
			}

//merge direction{{{
			if(isMC)
			{
				hSamePbpGen_fine[iaway][0]->Add(hSamePbpGen_fine[iaway][1]);
				hSamePbpGen_coarse[iaway][0]->Add(hSamePbpGen_coarse[iaway][1]);
				hMixPbpGen_fine[iaway][0]->Add(hMixPbpGen_fine[iaway][1]);
				hMixPbpGen_coarse[iaway][0]->Add(hMixPbpGen_coarse[iaway][1]);
			}
			hSamePbpReco_fine[iaway][0]->Add(hSamePbpReco_fine[iaway][1]);
			hSamePbpReco_coarse[iaway][0]->Add(hSamePbpReco_coarse[iaway][1]);
			hMixPbpReco_fine[iaway][0]->Add(hMixPbpReco_fine[iaway][1]);
			hMixPbpReco_coarse[iaway][0]->Add(hMixPbpReco_coarse[iaway][1]);
//}}}

//Draw{{{
			if(isMC)
			{
//same fine{{{
				c_same_gen_fine[iaway]->cd();
				hSamePbpGen_fine[iaway][0]->Draw("Surf1");
				lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.15,0.9, Form(" p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				c_same_gen_fine[iaway]->SaveAs(Form("CorrDist/CorrDist%sSame/%s/MupT%s/%splot_corr_same_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//mix fine{{{
				c_mix_gen_fine[iaway]->cd();
				hMixPbpGen_fine[iaway][0]->Draw("Surf1");
				lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				c_mix_gen_fine[iaway]->SaveAs(Form("CorrDist/CorrDist%sMix/%s/MupT%s/%splot_corr_mix_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//ratio fine{{{
				c_ratio_gen_fine[iaway]->cd();
				hSamePbpGen_fine[iaway][0]->Divide(hMixPbpGen_fine[iaway][0]);
				hSamePbpGen_fine[iaway][0]->Draw("Surf1");
				lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				c_ratio_gen_fine[iaway]->SaveAs(Form("CorrDist/CorrDist%sRatio/%s/MupT%s/%splot_corr_ratio_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//same coarse{{{
				c_same_gen_coarse[iaway]->cd();
				hSamePbpGen_coarse[iaway][0]->Draw("Surf1");
				lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				c_same_gen_coarse[iaway]->SaveAs(Form("CorrDist/CorrDist%sSame/%s/MupT%s/%splot_corr_same_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//mix coarse{{{
				c_mix_gen_coarse[iaway]->cd();
				hMixPbpGen_coarse[iaway][0]->Draw("Surf1");
				lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				c_mix_gen_coarse[iaway]->SaveAs(Form("CorrDist/CorrDist%sMix/%s/MupT%s/%splot_corr_mix_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//ratio coarse{{{
				c_ratio_gen_coarse[iaway]->cd();
				hSamePbpGen_coarse[iaway][0]->Divide(hMixPbpGen_coarse[iaway][0]);
				hSamePbpGen_coarse[iaway][0]->Draw("Surf1");
				lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.15,0.85, Form("%d #leq< p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				c_ratio_gen_coarse[iaway]->SaveAs(Form("CorrDist/CorrDist%sRatio/%s/MupT%s/%splot_corr_ratio_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}
			}
//same fine{{{
			c_same_reco_fine[iaway]->cd();
			hSamePbpReco_fine[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form(" p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			c_same_reco_fine[iaway]->SaveAs(Form("CorrDist/CorrDist%sSame/%s/MupT%s/%splot_corr_same_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//mix fine{{{
			c_mix_reco_fine[iaway]->cd();
			hMixPbpReco_fine[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			c_mix_reco_fine[iaway]->SaveAs(Form("CorrDist/CorrDist%sMix/%s/MupT%s/%splot_corr_mix_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//ratio fine{{{
			c_ratio_reco_fine[iaway]->cd();
			hSamePbpReco_fine[iaway][0]->Divide(hMixPbpReco_fine[iaway][0]);
			hSamePbpReco_fine[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			c_ratio_reco_fine[iaway]->SaveAs(Form("CorrDist/CorrDist%sRatio/%s/MupT%s/%splot_corr_ratio_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//same coarse{{{
			c_same_reco_coarse[iaway]->cd();
			hSamePbpReco_coarse[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			c_same_reco_coarse[iaway]->SaveAs(Form("CorrDist/CorrDist%sSame/%s/MupT%s/%splot_corr_same_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//mix coarse{{{
			c_mix_reco_coarse[iaway]->cd();
			hMixPbpReco_coarse[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			c_mix_reco_coarse[iaway]->SaveAs(Form("CorrDist/CorrDist%sMix/%s/MupT%s/%splot_corr_mix_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//ratio coarse{{{
			c_ratio_reco_coarse[iaway]->cd();
			hSamePbpReco_coarse[iaway][0]->Divide(hMixPbpReco_coarse[iaway][0]);
			hSamePbpReco_coarse[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			c_ratio_reco_coarse[iaway]->SaveAs(Form("CorrDist/CorrDist%sRatio/%s/MupT%s/%splot_corr_ratio_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//}}}
		}
	}
}
