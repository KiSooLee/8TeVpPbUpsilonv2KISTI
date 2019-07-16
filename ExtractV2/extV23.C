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

void extV23(const Bool_t isMC = false, const Bool_t isTrk = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TString MupT = "4")
{ 
	SetStyle();
	gStyle->SetOptFit(0);

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString dphiDIR = mainDIR + Form("/ProjDist/CorrDistdphi/%s/MupT%s", version.Data(), MupT.Data());
	TString v2DIR = mainDIR + Form("/ProjDist/V2Dist/%s/MupT%s", version.Data(), MupT.Data());
	TString fileDIR = mainDIR + Form("/ProjDist/DistFiles/%s/MupT%s", version.Data(), MupT.Data());

	void * dird = gSystem->OpenDirectory(dphiDIR.Data());
	if(dird) gSystem->FreeDirectory(dird);
	else gSystem->mkdir(dphiDIR.Data(), kTRUE);

	void * dirv = gSystem->OpenDirectory(v2DIR.Data());
	if(dirv) gSystem->FreeDirectory(dirv);
	else gSystem->mkdir(v2DIR.Data(), kTRUE);

	void * dirf = gSystem->OpenDirectory(fileDIR.Data());
	if(dirv) gSystem->FreeDirectory(dirv);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);
//}}}

	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString Away[3] = {"2", "1p5", "1"};
	TString Trk;
	if(isTrk) Trk = "trk_";
	else Trk = "";

	TFile* fin;

//Define canvas and histogram{{{

//Define canvas{{{
	TCanvas* cSR_fine[3];
	TCanvas* cSR_coarse[3];
	TCanvas* cMR_fine[3];
	TCanvas* cMR_coarse[3];
	TCanvas* cdphiR_fine[3];
	TCanvas* cdphiR_coarse[3];
	TCanvas* cv2R_fine[3];
	TCanvas* cv2R_coarse[3];
	TCanvas* cSG_fine[3];
	TCanvas* cSG_coarse[3];
	TCanvas* cMG_fine[3];
	TCanvas* cMG_coarse[3];
	TCanvas* cdphiG_fine[3];
	TCanvas* cdphiG_coarse[3];
	TCanvas* cv2G_fine[3];
	TCanvas* cv2G_coarse[3];
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		if(isMC)
		{
			cSG_fine[iaway] = new TCanvas(Form("cSG_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
			cSG_coarse[iaway] = new TCanvas(Form("cSG_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
			cMG_fine[iaway] = new TCanvas(Form("cMG_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
			cMG_coarse[iaway] = new TCanvas(Form("cMG_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
			cdphiG_fine[iaway] = new TCanvas(Form("cdphiG_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
			cdphiG_coarse[iaway] = new TCanvas(Form("cdphiG_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
			cv2G_fine[iaway] = new TCanvas(Form("cv2G_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
			cv2G_coarse[iaway] = new TCanvas(Form("cv2G_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		}
		cSR_fine[iaway] = new TCanvas(Form("cSR_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cSR_coarse[iaway] = new TCanvas(Form("cSR_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		cMR_fine[iaway] = new TCanvas(Form("cMR_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cMR_coarse[iaway] = new TCanvas(Form("cMR_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		cdphiR_fine[iaway] = new TCanvas(Form("cdphiR_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cdphiR_coarse[iaway] = new TCanvas(Form("cdphiR_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		cv2R_fine[iaway] = new TCanvas(Form("cv2R_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cv2R_coarse[iaway] = new TCanvas(Form("cv2R_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
	}
//}}}

//Define histogram{{{
	TH1D* hSRDeltaPhi_fine[3];
	TH1D* hSRDeltaPhi_coarse[3];
	TH1D* hMRDeltaPhi_fine[3];
	TH1D* hMRDeltaPhi_coarse[3];
	TH1D* hRRDeltaPhi_fine[3];
	TH1D* hRRDeltaPhi_coarse[3];
	TH1D* hSGDeltaPhi_fine[3];
	TH1D* hSGDeltaPhi_coarse[3];
	TH1D* hMGDeltaPhi_fine[3];
	TH1D* hMGDeltaPhi_coarse[3];
	TH1D* hRGDeltaPhi_fine[3];
	TH1D* hRGDeltaPhi_coarse[3];
	Double_t v2R_fine[3][mass_narr-1], v2ER_fine[3][mass_narr-1];
	Double_t v2R_coarse[3][mass_narr-1], v2ER_coarse[3][mass_narr-1];
	Double_t v1R_fine[3][mass_narr-1];
	Double_t v1R_coarse[3][mass_narr-1];
	Double_t v2G_fine[3][mass_narr-1], v2EG_fine[3][mass_narr-1];
	Double_t v2G_coarse[3][mass_narr-1], v2EG_coarse[3][mass_narr-1];
	Double_t v1G_fine[3][mass_narr-1];
	Double_t v1G_coarse[3][mass_narr-1];
	Double_t massCentArr[mass_narr-1];
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
		fin = new TFile(Form("../Projection/CorrDist/CorrFiles/%s/MupT%s/%sdphi_distribution_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_%d.root", version.Data(), MupT.Data(), Trk.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), imass), "READ");

		for(Int_t iaway = 0; iaway < 3; iaway++)
		{
//Get dphiplot{{{
			if(isMC)
			{
				hSGDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hSameGenDeltaPhi%s_fine", Away[iaway].Data()));
				hSGDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hSameGenDeltaPhi%s_coarse", Away[iaway].Data()));
				hMGDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hMixGenDeltaPhi%s_fine", Away[iaway].Data()));
				hMGDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hMixGenDeltaPhi%s_coarse", Away[iaway].Data()));
				hRGDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hRatioGenDeltaPhi%s_fine", Away[iaway].Data()));
				hRGDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hRatioGenDeltaPhi%s_coarse", Away[iaway].Data()));
				hSGDeltaPhi_fine[iaway]->Sumw2();
		      hSGDeltaPhi_coarse[iaway]->Sumw2();
				hMGDeltaPhi_fine[iaway]->Sumw2();
		      hMGDeltaPhi_coarse[iaway]->Sumw2();
				hRGDeltaPhi_fine[iaway]->Sumw2();
		      hRGDeltaPhi_coarse[iaway]->Sumw2();
			}

			hSRDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hSameRecoDeltaPhi%s_fine", Away[iaway].Data()));
			hSRDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hSameRecoDeltaPhi%s_coarse", Away[iaway].Data()));
			hMRDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hMixRecoDeltaPhi%s_fine", Away[iaway].Data()));
			hMRDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hMixRecoDeltaPhi%s_coarse", Away[iaway].Data()));
			hRRDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hRatioRecoDeltaPhi%s_fine", Away[iaway].Data()));
			hRRDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hRatioRecoDeltaPhi%s_coarse", Away[iaway].Data()));
			hSRDeltaPhi_fine[iaway]->Sumw2();
	      hSRDeltaPhi_coarse[iaway]->Sumw2();
			hMRDeltaPhi_fine[iaway]->Sumw2();
	      hMRDeltaPhi_coarse[iaway]->Sumw2();
			hRRDeltaPhi_fine[iaway]->Sumw2();
	      hRRDeltaPhi_coarse[iaway]->Sumw2();
//}}}

//fit dphi with vn function{{{

//Define fitting function{{{
			TF1 *vnR_fine = new TF1(Form("vnR_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x)+2*[3]*cos(3*x))",-6.28,6.28);
			vnR_fine->SetLineColor(kViolet+1);
			vnR_fine->SetLineStyle(1);
			vnR_fine->SetLineWidth(2);
			TF1 *vnR_coarse = new TF1(Form("vnR_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x)+2*[3]*cos(3*x))",-6.28,6.28);
			vnR_coarse->SetLineColor(kViolet+1);
			vnR_coarse->SetLineStyle(1);
			vnR_coarse->SetLineWidth(2);

			TF1 *vnG_fine = new TF1(Form("vnG_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x)+2*[3]*cos(3*x))",-6.28,6.28);
			vnG_fine->SetLineColor(kViolet+1);
			vnG_fine->SetLineStyle(1);
			vnG_fine->SetLineWidth(2);
			TF1 *vnG_coarse = new TF1(Form("vnG_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x)+2*[3]*cos(3*x))",-6.28,6.28);
			vnG_coarse->SetLineColor(kViolet+1);
			vnG_coarse->SetLineStyle(1);
			vnG_coarse->SetLineWidth(2);
//}}}

			if(isMC)
			{
//fine{{{

//same{{{
				cSG_fine[iaway]->cd();
				hSGDeltaPhi_fine[iaway]->Draw("pe");
				lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %s #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
				else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
				else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
				cSG_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sSame_corr_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//mix{{{
				cMG_fine[iaway]->cd();
				hMGDeltaPhi_fine[iaway]->Draw("pe");
				lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
				else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
				else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
				cMG_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sMix_corr_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//ratio{{{
		cdphiG_fine[iaway]->cd();
		hRGDeltaPhi_fine[iaway]->Draw("pe");
		hRGDeltaPhi_fine[iaway]->Fit(vnG_fine,"rqm");
		v2G_fine[iaway][imass] = vnG_fine->GetParameter(1);
		v2EG_fine[iaway][imass] = vnG_fine->GetParError(1);
		TF1 *v1G_fine = new TF1(Form("v1G_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(x))",-6.28,6.28);
		v1G_fine->SetLineColor(kBlue+1);
		v1G_fine->SetLineStyle(2);
		v1G_fine->SetLineWidth(2);
		v1G_fine->SetParameter(0, vnG_fine->GetParameter(0));
		v1G_fine->SetParameter(1, vnG_fine->GetParameter(2));
		TF1 *v2G_fine = new TF1(Form("v2G_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
		v2G_fine->SetLineColor(kRed+1);
		v2G_fine->SetLineStyle(2);
		v2G_fine->SetLineWidth(2);
		v2G_fine->SetParameter(0, vnG_fine->GetParameter(0));
		v2G_fine->SetParameter(1, vnG_fine->GetParameter(1));
		TF1 *v3G_fine = new TF1(Form("v3G_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(3*x))",-6.28,6.28);
		v3G_fine->SetLineColor(kYellow+1);
		v3G_fine->SetLineStyle(2);
		v3G_fine->SetLineWidth(2);
		v3G_fine->SetParameter(0, vnG_fine->GetParameter(0));
		v3G_fine->SetParameter(1, vnG_fine->GetParameter(3));
		v1G_fine->Draw("same");
		v2G_fine->Draw("same");
		v3G_fine->Draw("same");
		lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
		lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vnG_fine->GetParameter(1), vnG_fine->GetParError(1)));
		TLegend* lR_fine = new TLegend(0.77, 0.8, 0.95, 0.95);
		FormLegend(lG_fine, 0.04);
		lG_fine->AddEntry(vnG_fine, "total", "l");
		lG_fine->AddEntry(v1G_fine, "v1", "l");
		lG_fine->AddEntry(v2G_fine, "v2", "l");
		lG_fine->AddEntry(v3G_fine, "v3", "l");
		lG_fine->Draw();
		cdphiG_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sfit_corr_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_tra_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//}}}

//coarse{{{

//same{{{
				cSG_coarse[iaway]->cd();
				hSGDeltaPhi_coarse[iaway]->Draw("pe");
				lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %s #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
				else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
				else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
				cSG_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sSame_corr_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//mix{{{
				cMG_coarse[iaway]->cd();
				hMGDeltaPhi_coarse[iaway]->Draw("pe");
				lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
				else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
				else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
				cMG_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sMix_corr_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//ratio{{{
			cdphiG_coarse[iaway]->cd();
			hRGDeltaPhi_coarse[iaway]->Draw("pe");
			hRGDeltaPhi_coarse[iaway]->Fit(vnG_coarse,"rqm");
			v2G_coarse[iaway][imass] = vnG_coarse->GetParameter(1);
			v2EG_coarse[iaway][imass] = vnG_coarse->GetParError(1);
			TF1* v1G_coarse = new TF1(Form("v1G_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(x))",-6.28,6.28);
			v1G_coarse->SetLineColor(kBlue+1);
			v1G_coarse->SetLineStyle(2);
			v1G_coarse->SetLineWidth(2);
			v1G_coarse->SetParameter(0, vnG_coarse->GetParameter(0));
			v1G_coarse->SetParameter(1, vnG_coarse->GetParameter(2));
			TF1* v2G_coarse = new TF1(Form("v2G_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
			v2G_coarse->SetLineColor(kRed+1);
			v2G_coarse->SetLineStyle(2);
			v2G_coarse->SetLineWidth(2);
			v2G_coarse->SetParameter(0, vnG_coarse->GetParameter(0));
			v2G_coarse->SetParameter(1, vnG_coarse->GetParameter(1));
			TF1* v3G_coarse = new TF1(Form("v3G_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(3*x))",-6.28,6.28);
			v3G_coarse->SetLineColor(kYellow+1);
			v3G_coarse->SetLineStyle(2);
			v3G_coarse->SetLineWidth(2);
			v3G_coarse->SetParameter(0, vnG_coarse->GetParameter(0));
			v3G_coarse->SetParameter(1, vnG_coarse->GetParameter(3));
			v1G_coarse->Draw("same");
			v2G_coarse->Draw("same");
			v3G_coarse->Draw("same");
			lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vnG_coarse->GetParameter(1), vnG_coarse->GetParError(1)));
			TLegend* lG_coarse = new TLegend(0.77, 0.8, 0.95, 0.95);
			FormLegend(lG_coarse, 0.04);
			lG_coarse->AddEntry(vnG_coarse, "total", "l");
			lG_coarse->AddEntry(v1G_coarse, "v1", "l");
			lG_coarse->AddEntry(v2G_coarse, "v2", "l");
			lG_coarse->AddEntry(v3G_coarse, "v3", "l");
			lG_coarse->Draw();
			cdphiG_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sfit_corr_Gen_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_tra_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//}}}
			}

//fine{{{

//same{{{
			cSR_fine[iaway]->cd();
			hSRDeltaPhi_fine[iaway]->Draw("pe");
			lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %s #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
			cSR_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sSame_corr_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//mix{{{
			cMR_fine[iaway]->cd();
			hMRDeltaPhi_fine[iaway]->Draw("pe");
			lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
			cMR_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sMix_corr_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//ratio{{{
		cdphiR_fine[iaway]->cd();
		hRRDeltaPhi_fine[iaway]->Draw("pe");
		hRRDeltaPhi_fine[iaway]->Fit(vnR_fine,"rqm");
		v2R_fine[iaway][imass] = vnR_fine->GetParameter(1);
		v2ER_fine[iaway][imass] = vnR_fine->GetParError(1);
		TF1 *v1R_fine = new TF1(Form("v1R_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(x))",-6.28,6.28);
		v1R_fine->SetLineColor(kBlue+1);
		v1R_fine->SetLineStyle(2);
		v1R_fine->SetLineWidth(2);
		v1R_fine->SetParameter(0, vnR_fine->GetParameter(0));
		v1R_fine->SetParameter(1, vnR_fine->GetParameter(2));
		TF1 *v2R_fine = new TF1(Form("v2R_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
		v2R_fine->SetLineColor(kRed+1);
		v2R_fine->SetLineStyle(2);
		v2R_fine->SetLineWidth(2);
		v2R_fine->SetParameter(0, vnR_fine->GetParameter(0));
		v2R_fine->SetParameter(1, vnR_fine->GetParameter(1));
		TF1 *v3R_fine = new TF1(Form("v3R_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(3*x))",-6.28,6.28);
		v3R_fine->SetLineColor(kYellow+1);
		v3R_fine->SetLineStyle(2);
		v3R_fine->SetLineWidth(2);
		v3R_fine->SetParameter(0, vnR_fine->GetParameter(0));
		v3R_fine->SetParameter(1, vnR_fine->GetParameter(3));
		v1R_fine->Draw("same");
		v2R_fine->Draw("same");
		v3R_fine->Draw("same");
		lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
		lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vnR_fine->GetParameter(1), vnR_fine->GetParError(1)));
		TLegend* lR_fine = new TLegend(0.77, 0.8, 0.95, 0.95);
		FormLegend(lR_fine, 0.04);
		lR_fine->AddEntry(vnR_fine, "total", "l");
		lR_fine->AddEntry(v1R_fine, "v1", "l");
		lR_fine->AddEntry(v2R_fine, "v2", "l");
		lR_fine->AddEntry(v3R_fine, "v3", "l");
		lR_fine->Draw();
		cdphiR_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sfit_corr_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_tra_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//}}}

//coarse{{{

//same{{{
			cSR_coarse[iaway]->cd();
			hSRDeltaPhi_coarse[iaway]->Draw("pe");
			lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %s #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
			cSR_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sSame_corr_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//mix{{{
			cMR_coarse[iaway]->cd();
			hMRDeltaPhi_coarse[iaway]->Draw("pe");
			lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
			cMR_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sMix_corr_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//ratio{{{
		cdphiR_coarse[iaway]->cd();
		hRRDeltaPhi_coarse[iaway]->Draw("pe");
		hRRDeltaPhi_coarse[iaway]->Fit(vnR_coarse,"rqm");
		v2R_coarse[iaway][imass] = vnR_coarse->GetParameter(1);
		v2ER_coarse[iaway][imass] = vnR_coarse->GetParError(1);
		TF1* v1R_coarse = new TF1(Form("v1R_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(x))",-6.28,6.28);
		v1R_coarse->SetLineColor(kBlue+1);
		v1R_coarse->SetLineStyle(2);
		v1R_coarse->SetLineWidth(2);
		v1R_coarse->SetParameter(0, vnR_coarse->GetParameter(0));
		v1R_coarse->SetParameter(1, vnR_coarse->GetParameter(2));
		TF1* v2R_coarse = new TF1(Form("v2R_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
		v2R_coarse->SetLineColor(kRed+1);
		v2R_coarse->SetLineStyle(2);
		v2R_coarse->SetLineWidth(2);
		v2R_coarse->SetParameter(0, vnR_coarse->GetParameter(0));
		v2R_coarse->SetParameter(1, vnR_coarse->GetParameter(1));
		TF1* v3R_coarse = new TF1(Form("v3R_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(3*x))",-6.28,6.28);
		v3R_coarse->SetLineColor(kYellow+1);
		v3R_coarse->SetLineStyle(2);
		v3R_coarse->SetLineWidth(2);
		v3R_coarse->SetParameter(0, vnR_coarse->GetParameter(0));
		v3R_coarse->SetParameter(1, vnR_coarse->GetParameter(3));
		v1R_coarse->Draw("same");
		v2R_coarse->Draw("same");
		v3R_coarse->Draw("same");
		lt1->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
		lt1->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		if(iaway == 0) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		else if(iaway == 1) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		else if(iaway == 2) lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vnR_coarse->GetParameter(1), vnR_coarse->GetParError(1)));
		TLegend* lR_coarse = new TLegend(0.77, 0.8, 0.95, 0.95);
		FormLegend(lR_coarse, 0.04);
		lR_coarse->AddEntry(vnR_coarse, "total", "l");
		lR_coarse->AddEntry(v1R_coarse, "v1", "l");
		lR_coarse->AddEntry(v2R_coarse, "v2", "l");
		lR_coarse->AddEntry(v3R_coarse, "v3", "l");
		lR_coarse->Draw();
		cdphiR_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/%sfit_corr_Reco_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_tra_%d.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), imass));
//}}}

//}}}

//}}}
		}
		massCentArr[imass] = 8 + massBinsArr[imass]*0.05 + (massBinsArr[imass+1]-massBinsArr[imass])*0.05/2.;
		massValsArr[imass+1] = 8 + massBinsArr[imass+1]*0.05;
	}

	TH1D* hRef = new TH1D("hRef", "", mass_narr-1, massValsArr);
	FormTH1(hRef, 0);
	hRef->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
	hRef->GetYaxis()->SetTitle("v_{2}^{S+B}");
	hRef->SetMinimum(-0.05);
	hRef->SetMaximum(0.05);

	TGraphErrors* gv2R_fine[3];
	TGraphErrors* gv2R_coarse[3];
	TGraphErrors* gv2G_fine[3];
	TGraphErrors* gv2G_coarse[3];
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		if(isMC)
		{
//Define graph{{{
			gv2G_fine[iaway] = new TGraphErrors(mass_narr-1, massCentArr, v2G_fine[iaway], 0, v2EG_fine[iaway]);
			gv2G_fine[iaway]->SetName(Form("gv2G_%s_fine", Away[iaway].Data()));
			gv2G_fine[iaway]->SetMaximum(0.05);
			gv2G_fine[iaway]->SetMinimum(-0.05);
			gv2G_coarse[iaway] = new TGraphErrors(mass_narr-1, massCentArr, v2G_coarse[iaway], 0, v2EG_coarse[iaway]);
			gv2G_coarse[iaway]->SetName(Form("gv2G_%s_coarse", Away[iaway].Data()));
			gv2G_coarse[iaway]->SetMaximum(0.05);
			gv2G_coarse[iaway]->SetMinimum(-0.05);
//}}}

//fine{{{
			cv2G_fine[iaway]->cd();
			hRef->Draw();
			gv2G_fine[iaway]->SetMarkerStyle(20);
			gv2G_fine[iaway]->SetMarkerSize(1.2);
			//gv2_1fine->SetMarkerSize(0);
			gv2G_fine[iaway]->Draw("pesame");
			lt2->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt2->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt2->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt2->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
			cv2G_fine[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/%sv2_dist_Gen_%s_fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_tra.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[away].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data()));
			//cv2_1fine->SaveAs(Form("ProjDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data()));
//}}}

//coarse{{{
			cv2G_coarse[iaway]->cd();
			hRef->Draw();
			gv2G_coarse[iaway]->SetMarkerStyle(20);
			gv2G_coarse[iaway]->SetMarkerSize(1.2);
			//gv2_coarse->SetMarkerSize(0);
			gv2G_coarse[iaway]->Draw("pesame");
			lt2->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
			lt2->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
			lt2->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt2->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
			cv2G_coarse[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/%sv2_dist_Gen_%s_coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_tra.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[away].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data()));
			//cv2_1fine->SaveAs(Form("ProjDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data()));
//}}}
		}
//Define graph{{{
		gv2R_fine[iaway] = new TGraphErrors(mass_narr-1, massCentArr, v2R_fine[iaway], 0, v2ER_fine[iaway]);
		gv2R_fine[iaway]->SetName(Form("gv2R_%s_fine", Away[iaway].Data()));
		gv2R_fine[iaway]->SetMaximum(0.05);
		gv2R_fine[iaway]->SetMinimum(-0.05);
		gv2R_coarse[iaway] = new TGraphErrors(mass_narr-1, massCentArr, v2R_coarse[iaway], 0, v2ER_coarse[iaway]);
		gv2R_coarse[iaway]->SetName(Form("gv2R_%s_coarse", Away[iaway].Data()));
		gv2R_coarse[iaway]->SetMaximum(0.05);
		gv2R_coarse[iaway]->SetMinimum(-0.05);
//}}}

//fine{{{
		cv2R_fine[iaway]->cd();
		hRef->Draw();
		gv2R_fine[iaway]->SetMarkerStyle(20);
		gv2R_fine[iaway]->SetMarkerSize(1.2);
		//gv2_1fine->SetMarkerSize(0);
		gv2R_fine[iaway]->Draw("pesame");
		lt2->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
		lt2->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
		lt2->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt2->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		if(iaway == 0) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		else if(iaway == 1) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		else if(iaway == 2) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		cv2R_fine[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/%sv2_dist_Reco_%s_fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_tra.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[away].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data()));
		//cv2_1fine->SaveAs(Form("ProjDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data()));
//}}}

//coarse{{{
		cv2R_coarse[iaway]->cd();
		hRef->Draw();
		gv2R_coarse[iaway]->SetMarkerStyle(20);
		gv2R_coarse[iaway]->SetMarkerSize(1.2);
		//gv2_coarse->SetMarkerSize(0);
		gv2R_coarse[iaway]->Draw("pesame");
		lt2->DrawLatex(0.2,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq #N^{trk} < %d", multMin, multMax));
		lt2->DrawLatex(0.2,0.9, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
		lt2->DrawLatex(0.2,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.4 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt2->DrawLatex(0.2,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		if(iaway == 0) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		else if(iaway == 1) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		else if(iaway == 2) lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		cv2R_coarse[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/%sv2_dist_Reco_%s_coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_tra.pdf", version.Data(), MupT.Data(), Trk.Data(), Away[away].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data()));
		//cv2_1fine->SaveAs(Form("ProjDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data()));
//}}}
	}

	TFile* fout = new TFile(Form("ProjDist/DistFiles/%s/MupT%s/%sv2_dist_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_tra.root", version.Data(), MupT.Data(), Tkr.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data()), "RECREATE");
	fout->cd();
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		if(isMC)
		{
			gv2G_fine[iaway]->Write();
			gv2G_coarse[iaway]->Write();
		}
		gv2R_fine[iaway]->Write();
		gv2R_coarse[iaway]->Write();
	}
}
