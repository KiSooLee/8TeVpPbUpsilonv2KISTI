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
#include <iostream>
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
//}}}

void extV23(const Bool_t isMC = false, const Bool_t isGen = false, const Bool_t isTrk = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const bool Weight = true, const TString MupT = "4", const Int_t FMax = 3)
{ 
	SetStyle();
	gStyle->SetOptFit(0);

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString dphiDIR1 = mainDIR + Form("/ProjDist/CorrDistdphi/%s/MupT%s/Away1/Weight%o", version.Data(), MupT.Data(), Weight);
	TString dphiDIR1p5 = mainDIR + Form("/ProjDist/CorrDistdphi/%s/MupT%s/Away1p5/Weight%o", version.Data(), MupT.Data(), Weight);
	TString dphiDIR2 = mainDIR + Form("/ProjDist/CorrDistdphi/%s/MupT%s/Away2/Weight%o", version.Data(), MupT.Data(), Weight);
	TString v2DIR = mainDIR + Form("/ProjDist/V2Dist/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString fileDIR = mainDIR + Form("/ProjDist/DistFiles/%s/MupT%s", version.Data(), MupT.Data());

	void * dird1 = gSystem->OpenDirectory(dphiDIR1.Data());
	if(dird1) gSystem->FreeDirectory(dird1);
	else gSystem->mkdir(dphiDIR1.Data(), kTRUE);

	void * dird1p5 = gSystem->OpenDirectory(dphiDIR1p5.Data());
	if(dird1p5) gSystem->FreeDirectory(dird1p5);
	else gSystem->mkdir(dphiDIR1p5.Data(), kTRUE);

	void * dird2 = gSystem->OpenDirectory(dphiDIR2.Data());
	if(dird2) gSystem->FreeDirectory(dird2);
	else gSystem->mkdir(dphiDIR2.Data(), kTRUE);

	void * dirv = gSystem->OpenDirectory(v2DIR.Data());
	if(dirv) gSystem->FreeDirectory(dirv);
	else gSystem->mkdir(v2DIR.Data(), kTRUE);

	void * dirf = gSystem->OpenDirectory(fileDIR.Data());
	if(dirv) gSystem->FreeDirectory(dirv);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);
//}}}

//Define names{{{
	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString RorG;
	if(isGen) RorG = "Gen";
	else RorG = "Reco";
	TString Away[3] = {"2", "1p5", "1"};
	TString Trk;
	if(isTrk) Trk = "trk_";
	else Trk = "";
	TString Fourier;
	if(FMax == 2) Fourier = "quad";
	else if(FMax == 3) Fourier = "tra";
	else
	{
		cout << "no such level of fourier" << endl;
		return;
	}
//}}}

	TFile* fin;

//Define canvas and histogram{{{

//Define canvas{{{
	TCanvas* cSame_fine[3];
	TCanvas* cSame_coarse[3];
	TCanvas* cMix_fine[3];
	TCanvas* cMix_coarse[3];
	TCanvas* cdphi_fine[3];
	TCanvas* cdphi_coarse[3];
	TCanvas* cv2_fine[3];
	TCanvas* cv2_coarse[3];
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		cSame_fine[iaway] = new TCanvas(Form("cSame_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cSame_coarse[iaway] = new TCanvas(Form("cSame_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		cMix_fine[iaway] = new TCanvas(Form("cMix_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cMix_coarse[iaway] = new TCanvas(Form("cMix_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		cdphi_fine[iaway] = new TCanvas(Form("cdphi_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cdphi_coarse[iaway] = new TCanvas(Form("cdphi_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		cv2_fine[iaway] = new TCanvas(Form("cv2_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cv2_coarse[iaway] = new TCanvas(Form("cv2_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
	}
//}}}

//Define histogram{{{
	TH1D* hSDeltaPhi_fine[3];
	TH1D* hSDeltaPhi_coarse[3];
	TH1D* hMDeltaPhi_fine[3];
	TH1D* hMDeltaPhi_coarse[3];
	TH1D* hRDeltaPhi_fine[3];
	TH1D* hRDeltaPhi_coarse[3];
//}}}

//Define graph value{{{
	Double_t v2v_fine[3][mass_narr-1] = {{0.}};
	Double_t v2Ev_fine[3][mass_narr-1] = {{0.}};
	Double_t v2v_coarse[3][mass_narr-1] = {{0.}};
	Double_t v2Ev_coarse[3][mass_narr-1] = {{0.}};
	Double_t v1v_fine[3][mass_narr-1] = {{0.}};
	Double_t v1v_coarse[3][mass_narr-1] = {{0.}};
	Double_t massCentArr[mass_narr-1];
	Double_t massE[mass_narr-1] = {0.};
	Double_t massValsArr[mass_narr];
	massValsArr[0] = 8;
//}}}

//}}}

	TLatex *lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->SetNDC();
	TLatex *lt2 = new TLatex();
	FormLatex(lt2, 12, 0.04);
	lt2->SetNDC();

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

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{
		fin = new TFile(Form("../Projection/CorrDist/CorrFiles/%s/MupT%s/%sdphi_distribution_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_weight%o_MupT%s_%d.root", version.Data(), MupT.Data(), Trk.Data(), RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), Weight, MupT.Data(), imass), "READ");

		for(Int_t iaway = 0; iaway < 3; iaway++)
		{
//Get dphiplot{{{
			hSDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hSame%sDeltaPhi%s_fine", RorG.Data(), Away[iaway].Data()));
			hSDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hSame%sDeltaPhi%s_coarse", RorG.Data(), Away[iaway].Data()));
			hMDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hMix%sDeltaPhi%s_fine", RorG.Data(), Away[iaway].Data()));
			hMDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hMix%sDeltaPhi%s_coarse", RorG.Data(), Away[iaway].Data()));
			hRDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hRatio%sDeltaPhi%s_fine", RorG.Data(), Away[iaway].Data()));
			hRDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hRatio%sDeltaPhi%s_coarse", RorG.Data(), Away[iaway].Data()));
			hSDeltaPhi_fine[iaway]->Sumw2();
	      hSDeltaPhi_coarse[iaway]->Sumw2();
			hMDeltaPhi_fine[iaway]->Sumw2();
	      hMDeltaPhi_coarse[iaway]->Sumw2();
			hRDeltaPhi_fine[iaway]->Sumw2();
	      hRDeltaPhi_coarse[iaway]->Sumw2();
//}}}

//Define fitting function{{{
			TF1 *vn_fine = 0;
			if(FMax == 2) vn_fine = new TF1(Form("vn_Away%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
			else if(FMax == 3) vn_fine = new TF1(Form("vn_Away%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x)+2*[3]*cos(3*x))",-6.28,6.28);
			vn_fine->SetLineColor(kViolet+1);
			vn_fine->SetLineStyle(1);
			vn_fine->SetLineWidth(2);
			TF1 *vn_coarse = 0;
			if(FMax == 2) vn_coarse = new TF1(Form("vn_Away%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
			else if(FMax == 3) vn_coarse = new TF1(Form("vn_Away%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x)+2*[3]*cos(3*x))",-6.28,6.28);
			vn_coarse->SetLineColor(kViolet+1);
			vn_coarse->SetLineStyle(1);
			vn_coarse->SetLineWidth(2);
//}}}

//fine{{{

//same{{{
			cSame_fine[iaway]->cd();
			hSDeltaPhi_fine[iaway]->Draw("pe");
			lt1->DrawLatex(0.17,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.17,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.17,0.80, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.17,0.75, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.17,0.75, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.17,0.65, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			cSame_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/Weight%o/%sSame_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
//}}}

//mix{{{
			cMix_fine[iaway]->cd();
			hMDeltaPhi_fine[iaway]->Draw("pe");
			lt1->DrawLatex(0.17,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.17,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.17,0.80, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.17,0.75, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.17,0.75, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.17,0.65, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			cMix_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/Weight%o/%sMix_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
//}}}

//ratio{{{
			cdphi_fine[iaway]->cd();
			hRDeltaPhi_fine[iaway]->Draw("pe");
			hRDeltaPhi_fine[iaway]->Fit(vn_fine,"rqm");
			v2v_fine[iaway][imass] = vn_fine->GetParameter(1);
			v2Ev_fine[iaway][imass] = vn_fine->GetParError(1);
			TF1 *v1_fine = new TF1(Form("v1_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(x))",-6.28,6.28);
			v1_fine->SetLineColor(kBlue+1);
			v1_fine->SetLineStyle(2);
			v1_fine->SetLineWidth(2);
			v1_fine->SetParameter(0, vn_fine->GetParameter(0));
			v1_fine->SetParameter(1, vn_fine->GetParameter(2));
			TF1 *v2_fine = new TF1(Form("v2_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
			v2_fine->SetLineColor(kRed+1);
			v2_fine->SetLineStyle(2);
			v2_fine->SetLineWidth(2);
			v2_fine->SetParameter(0, vn_fine->GetParameter(0));
			v2_fine->SetParameter(1, vn_fine->GetParameter(1));
			TF1 *v3_fine = 0;
			if(FMax == 3)
			{
				v3_fine = new TF1(Form("v3_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(3*x))",-6.28,6.28);
				v3_fine->SetLineColor(kYellow+1);
				v3_fine->SetLineStyle(2);
				v3_fine->SetLineWidth(2);
				v3_fine->SetParameter(0, vn_fine->GetParameter(0));
				v3_fine->SetParameter(1, vn_fine->GetParameter(3));
			}
			v1_fine->Draw("same");
			v2_fine->Draw("same");
			if(FMax == 3) v3_fine->Draw("same");
			lt1->DrawLatex(0.17,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.17,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.17,0.80, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.17,0.75, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.17,0.75, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.17,0.65, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_fine->GetParameter(1), vn_fine->GetParError(1)));
			TLegend* l_fine = new TLegend(0.77, 0.72, 0.95, 0.87);
			FormLegend(l_fine, 0.04);
			l_fine->AddEntry(vn_fine, "total", "l");
			l_fine->AddEntry(v1_fine, "v1", "l");
			l_fine->AddEntry(v2_fine, "v2", "l");
			if(FMax == 3) l_fine->AddEntry(v3_fine, "v3", "l");
			l_fine->Draw();
			cdphi_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/Weight%o/%sFit_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%s_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), Weight, Fourier.Data(), imass));
//}}}

//}}}

//coarse{{{

//same{{{
			cSame_coarse[iaway]->cd();
			hSDeltaPhi_coarse[iaway]->Draw("pe");
			lt1->DrawLatex(0.17,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.17,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.17,0.80, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.17,0.75, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.17,0.75, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.17,0.65, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			cSame_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/Weight%o/%sSame_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
//}}}

//mix{{{
			cMix_coarse[iaway]->cd();
			hMDeltaPhi_coarse[iaway]->Draw("pe");
			lt1->DrawLatex(0.17,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.17,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.17,0.80, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.17,0.75, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.17,0.75, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.17,0.65, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			cMix_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/Weight%o/%sMix_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
//}}}

//ratio{{{
			cdphi_coarse[iaway]->cd();
			hRDeltaPhi_coarse[iaway]->Draw("pe");
			hRDeltaPhi_coarse[iaway]->Fit(vn_coarse,"rqm");
			v2v_coarse[iaway][imass] = vn_coarse->GetParameter(1);
			v2Ev_coarse[iaway][imass] = vn_coarse->GetParError(1);
			TF1* v1_coarse = new TF1(Form("v1_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(x))",-6.28,6.28);
			v1_coarse->SetLineColor(kBlue+1);
			v1_coarse->SetLineStyle(2);
			v1_coarse->SetLineWidth(2);
			v1_coarse->SetParameter(0, vn_coarse->GetParameter(0));
			v1_coarse->SetParameter(1, vn_coarse->GetParameter(2));
			TF1* v2_coarse = new TF1(Form("v2_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
			v2_coarse->SetLineColor(kRed+1);
			v2_coarse->SetLineStyle(2);
			v2_coarse->SetLineWidth(2);
			v2_coarse->SetParameter(0, vn_coarse->GetParameter(0));
			v2_coarse->SetParameter(1, vn_coarse->GetParameter(1));
			TF1* v3_coarse = 0;
			if(FMax == 3)
			{
				v3_coarse = new TF1(Form("v3_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(3*x))",-6.28,6.28);
				v3_coarse->SetLineColor(kYellow+1);
				v3_coarse->SetLineStyle(2);
				v3_coarse->SetLineWidth(2);
				v3_coarse->SetParameter(0, vn_coarse->GetParameter(0));
				v3_coarse->SetParameter(1, vn_coarse->GetParameter(3));
			}
			v1_coarse->Draw("same");
			v2_coarse->Draw("same");
			if(FMax == 3) v3_coarse->Draw("same");
			lt1->DrawLatex(0.17,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.17,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.17,0.80, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.17,0.75, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.17,0.75, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.17,0.70, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.17,0.65, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_coarse->GetParameter(1), vn_coarse->GetParError(1)));
			TLegend* l_coarse = new TLegend(0.77, 0.72, 0.95, 0.87);
			FormLegend(l_coarse, 0.04);
			l_coarse->AddEntry(vn_coarse, "total", "l");
			l_coarse->AddEntry(v1_coarse, "v1", "l");
			l_coarse->AddEntry(v2_coarse, "v2", "l");
			if(FMax == 3) l_coarse->AddEntry(v3_coarse, "v3", "l");
			l_coarse->Draw();
			cdphi_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/Weight%o/%sFit_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%s_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), Weight, Fourier.Data(), imass));
//}}}

//}}}
		}
		massCentArr[imass] = 8 + massBinsArr[imass]*0.05 + (massBinsArr[imass+1]-massBinsArr[imass])*0.05/2.;
		massValsArr[imass+1] = 8 + massBinsArr[imass+1]*0.05;
	}

	TH1D* hRef = new TH1D("hRef", "", mass_narr-1, massValsArr);
	FormTH1(hRef, 0);
	hRef->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
	if(isTrk) hRef->GetYaxis()->SetTitle("v_{2}^{trk-trk}");
	else hRef->GetYaxis()->SetTitle("v_{2}^{#mu#mu-trk}");
	if(isTrk)
	{
		hRef->SetMinimum(-0.01);
		hRef->SetMaximum(0.01);
	}
	else
	{
		//for high-multiplicity
/*
		hRef->SetMinimum(-0.03);
		hRef->SetMaximum(0.03);
*/
		//for low-multiplicity
		hRef->SetMinimum(-0.03);
		hRef->SetMaximum(0.06);
	}

	TGraphErrors* gv2_fine[3];
	TGraphErrors* gv2_coarse[3];
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
//Define graph{{{
		gv2_fine[iaway] = new TGraphErrors(mass_narr-1, massCentArr, v2v_fine[iaway], massE, v2Ev_fine[iaway]);
		gv2_fine[iaway]->SetName(Form("gv2_Away%s_fine", Away[iaway].Data()));
		gv2_fine[iaway]->SetMaximum(0.05);
		gv2_fine[iaway]->SetMinimum(-0.05);
		gv2_coarse[iaway] = new TGraphErrors(mass_narr-1, massCentArr, v2v_coarse[iaway], massE, v2Ev_coarse[iaway]);
		gv2_coarse[iaway]->SetName(Form("gv2_Away%s_coarse", Away[iaway].Data()));
		gv2_coarse[iaway]->SetMaximum(0.05);
		gv2_coarse[iaway]->SetMinimum(-0.05);
//}}}

//fine{{{
		cv2_fine[iaway]->cd();
		hRef->Draw();
		gv2_fine[iaway]->SetMarkerStyle(20);
		gv2_fine[iaway]->SetMarkerSize(1.2);
		//gv2_1fine->SetMarkerSize(0);
		gv2_fine[iaway]->Draw("pesame");
		lt2->DrawLatex(0.17,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
		lt2->DrawLatex(0.50,0.40, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
		lt2->DrawLatex(0.50,0.35, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt2->DrawLatex(0.50,0.30, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt2->DrawLatex(0.50,0.20, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		if(iaway == 0) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 2.0");
		else if(iaway == 1) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 1.5");
		else if(iaway == 2) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 1.0");
		cv2_fine[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/Weight%o/%sv2_dist_%s_%s_fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_weight%o_%s.pdf", version.Data(), MupT.Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Weight, Fourier.Data()));
		//cv2_1fine->SaveAs(Form("ProjDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data()));
//}}}

//coarse{{{
		cv2_coarse[iaway]->cd();
		hRef->Draw();
		gv2_coarse[iaway]->SetMarkerStyle(20);
		gv2_coarse[iaway]->SetMarkerSize(1.2);
		//gv2_coarse->SetMarkerSize(0);
		gv2_coarse[iaway]->Draw("pesame");
		lt2->DrawLatex(0.17,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
		lt2->DrawLatex(0.50,0.40, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
		lt2->DrawLatex(0.50,0.35, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt2->DrawLatex(0.50,0.30, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt2->DrawLatex(0.50,0.30, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		if(iaway == 0) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 2.0");
		else if(iaway == 1) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 1.5");
		else if(iaway == 2) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 1.0");
		cv2_coarse[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/Weight%o/%sv2_dist_%s_%s_coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_weight%o_%s.pdf", version.Data(), MupT.Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Weight, Fourier.Data()));
		//cv2_1fine->SaveAs(Form("ProjDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data()));
//}}}
	}

	TFile* fout = new TFile(Form("ProjDist/DistFiles/%s/MupT%s/%sv2_dist_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_weight%o_%s.root", version.Data(), MupT.Data(), Trk.Data(), RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Weight, Fourier.Data()), "RECREATE");
	fout->cd();
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		gv2_fine[iaway]->Write();
		gv2_coarse[iaway]->Write();
	}
	fout->Close();
}
