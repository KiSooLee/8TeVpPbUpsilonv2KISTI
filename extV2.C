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
#include "Style_Upv2.h"
#include "Upsilon.h"
//}}}

void extV2(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1")
{ 
	SetStyle();
	gStyle->SetOptFit(0);

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString dphiDIR = mainDIR + "/CorrDist/CorrDistdphi";
	TString v2DIR = mainDIR + "/CorrDist/V2Dist";

	void * dird = gSystem->OpenDirectory(dphiDIR.Data());
	if(dird) gSystem->FreeDirectory(dird);
	else gSystem->mkdir(dphiDIR.Data(), kTRUE);

	void * dirv = gSystem->OpenDirectory(v2DIR.Data());
	if(dirv) gSystem->FreeDirectory(dirv);
	else gSystem->mkdir(v2DIR.Data(), kTRUE);
//}}}

	TFile* fin;

//Define canvas and histogram{{{

//Define canvas{{{
	TCanvas* cS1_fine = new TCanvas("cS1_fine", "", 0, 0, 600, 600);
	TCanvas* cS1_coarse = new TCanvas("cS1_coarse", "", 0, 0, 600, 600);
	TCanvas* cS1p5_fine = new TCanvas("cS1p5_fine", "", 0, 0, 600, 600);
	TCanvas* cS1p5_coarse = new TCanvas("cS1p5_coarse", "", 0, 0, 600, 600);
	TCanvas* cS2_fine = new TCanvas("cS2_fine", "", 0, 0, 600, 600);
	TCanvas* cS2_coarse = new TCanvas("cS2_coarse", "", 0, 0, 600, 600);
	TCanvas* cB1_fine = new TCanvas("cB1_fine", "", 0, 0, 600, 600);
	TCanvas* cB1_coarse = new TCanvas("cB1_coarse", "", 0, 0, 600, 600);
	TCanvas* cB1p5_fine = new TCanvas("cB1p5_fine", "", 0, 0, 600, 600);
	TCanvas* cB1p5_coarse = new TCanvas("cB1p5_coarse", "", 0, 0, 600, 600);
	TCanvas* cB2_fine = new TCanvas("cB2_fine", "", 0, 0, 600, 600);
	TCanvas* cB2_coarse = new TCanvas("cB2_coarse", "", 0, 0, 600, 600);
	TCanvas* cdphi1_fine = new TCanvas("cdphi1_fine", "", 0, 0, 600, 600);
	TCanvas* cdphi1_coarse = new TCanvas("cdphi1_coarse", "", 0, 0, 600, 600);
	TCanvas* cdphi1p5_fine = new TCanvas("cdphi1p5_fine", "", 0, 0, 600, 600);
	TCanvas* cdphi1p5_coarse = new TCanvas("cdphi1p5_coarse", "", 0, 0, 600, 600);
	TCanvas* cdphi2_fine = new TCanvas("cdphi2_fine", "", 0, 0, 600, 600);
	TCanvas* cdphi2_coarse = new TCanvas("cdphi2_coarse", "", 0, 0, 600, 600);
	TCanvas* cv2_1fine = new TCanvas("cv2_1fine", "", 0, 0, 600, 600);
	TCanvas* cv2_1coarse = new TCanvas("cv2_1coarse", "", 0, 0, 600, 600);
	TCanvas* cv2_1p5fine = new TCanvas("cv2_1p5fine", "", 0, 0, 600, 600);
	TCanvas* cv2_1p5coarse = new TCanvas("cv2_1p5coarse", "", 0, 0, 600, 600);
	TCanvas* cv2_2fine = new TCanvas("cv2_2fine", "", 0, 0, 600, 600);
	TCanvas* cv2_2coarse = new TCanvas("cv2_2coarse", "", 0, 0, 600, 600);
//}}}

//Define histogram{{{
	TH1D* hSDeltaPhi1_fine;
	TH1D* hSDeltaPhi1_coarse;
	TH1D* hSDeltaPhi1p5_fine;
	TH1D* hSDeltaPhi1p5_coarse;
	TH1D* hSDeltaPhi2_fine;
	TH1D* hSDeltaPhi2_coarse;
	TH1D* hBDeltaPhi1_fine;
	TH1D* hBDeltaPhi1_coarse;
	TH1D* hBDeltaPhi1p5_fine;
	TH1D* hBDeltaPhi1p5_coarse;
	TH1D* hBDeltaPhi2_fine;
	TH1D* hBDeltaPhi2_coarse;
	TH1D* hDeltaPhi1_fine;
	TH1D* hDeltaPhi1_coarse;
	TH1D* hDeltaPhi1p5_fine;
	TH1D* hDeltaPhi1p5_coarse;
	TH1D* hDeltaPhi2_fine;
	TH1D* hDeltaPhi2_coarse;
	Double_t v2s_1fine[mass_narr-1], v2Es_1fine[mass_narr-1];
	Double_t v2s_1coarse[mass_narr-1], v2Es_1coarse[mass_narr-1];
	Double_t v2s_1p5fine[mass_narr-1], v2Es_1p5fine[mass_narr-1];
	Double_t v2s_1p5coarse[mass_narr-1], v2Es_1p5coarse[mass_narr-1];
	Double_t v2s_2fine[mass_narr-1], v2Es_2fine[mass_narr-1];
	Double_t v2s_2coarse[mass_narr-1], v2Es_2coarse[mass_narr-1];
	Double_t v1s_1fine[mass_narr-1];
	Double_t v1s_1coarse[mass_narr-1];
	Double_t v1s_1p5fine[mass_narr-1];
	Double_t v1s_1p5coarse[mass_narr-1];
	Double_t v1s_2fine[mass_narr-1];
	Double_t v1s_2coarse[mass_narr-1];
	Double_t v0s_1fine[mass_narr-1];
	Double_t v0s_1coarse[mass_narr-1];
	Double_t v0s_1p5fine[mass_narr-1];
	Double_t v0s_1p5coarse[mass_narr-1];
	Double_t v0s_2fine[mass_narr-1];
	Double_t v0s_2coarse[mass_narr-1];
	Double_t massCentArr[mass_narr-1];
	Double_t massValsArr[mass_narr];
	massValsArr[0] = 8;
//}}}

	TLatex *lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->SetNDC();
	TLatex *lt2 = new TLatex();
	FormLatex(lt2, 12, 0.04);
	lt2->SetNDC();
//}}}

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{
		fin = new TFile(Form("CorrDist/CorrFiles/dphi_distribution_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");

//Get dphiplot{{{
		hSDeltaPhi1_fine = (TH1D*) fin->Get("hSigDeltaPhi1_fine");
		hSDeltaPhi1_coarse = (TH1D*) fin->Get("hSigDeltaPhi1_coarse");
		hSDeltaPhi1p5_fine = (TH1D*) fin->Get("hSigDeltaPhi1p5_fine");
		hSDeltaPhi1p5_coarse = (TH1D*) fin->Get("hSigDeltaPhi1p5_coarse");
		hSDeltaPhi2_fine = (TH1D*) fin->Get("hSigDeltaPhi2_fine");
		hSDeltaPhi2_coarse = (TH1D*) fin->Get("hSigDeltaPhi2_coarse");
		hBDeltaPhi1_fine = (TH1D*) fin->Get("hBkgDeltaPhi1_fine");
		hBDeltaPhi1_coarse = (TH1D*) fin->Get("hBkgDeltaPhi1_coarse");
		hBDeltaPhi1p5_fine = (TH1D*) fin->Get("hBkgDeltaPhi1p5_fine");
		hBDeltaPhi1p5_coarse = (TH1D*) fin->Get("hBkgDeltaPhi1p5_coarse");
		hBDeltaPhi2_fine = (TH1D*) fin->Get("hBkgDeltaPhi2_fine");
		hBDeltaPhi2_coarse = (TH1D*) fin->Get("hBkgDeltaPhi2_coarse");
		hDeltaPhi1_fine = (TH1D*) fin->Get("hRatioDeltaPhi1_fine");
		hDeltaPhi1_coarse = (TH1D*) fin->Get("hRatioDeltaPhi1_coarse");
		hDeltaPhi1p5_fine = (TH1D*) fin->Get("hRatioDeltaPhi1p5_fine");
		hDeltaPhi1p5_coarse = (TH1D*) fin->Get("hRatioDeltaPhi1p5_coarse");
		hDeltaPhi2_fine = (TH1D*) fin->Get("hRatioDeltaPhi2_fine");
		hDeltaPhi2_coarse = (TH1D*) fin->Get("hRatioDeltaPhi2_coarse");
		hSDeltaPhi1_fine->Sumw2();
      hSDeltaPhi1_coarse->Sumw2();
		hSDeltaPhi1p5_fine->Sumw2();
      hSDeltaPhi1p5_coarse->Sumw2();
      hSDeltaPhi2_fine->Sumw2();
      hSDeltaPhi2_coarse->Sumw2();
		hBDeltaPhi1_fine->Sumw2();
      hBDeltaPhi1_coarse->Sumw2();
		hBDeltaPhi1p5_fine->Sumw2();
      hBDeltaPhi1p5_coarse->Sumw2();
      hBDeltaPhi2_fine->Sumw2();
      hBDeltaPhi2_coarse->Sumw2();
		hDeltaPhi1_fine->Sumw2();
      hDeltaPhi1_coarse->Sumw2();
		hDeltaPhi1p5_fine->Sumw2();
      hDeltaPhi1p5_coarse->Sumw2();
      hDeltaPhi2_fine->Sumw2();
      hDeltaPhi2_coarse->Sumw2();
//}}}

//fit dphi with vn function{{{

//Define fitting function{{{
		TF1 *vn_1fine = new TF1("vn_1fine","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
		vn_1fine->SetLineColor(kViolet+1);
		vn_1fine->SetLineStyle(1);
		vn_1fine->SetLineWidth(2);
		TF1 *vn_1coarse = new TF1("vn_1coarse","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
		vn_1coarse->SetLineColor(kViolet+1);
		vn_1coarse->SetLineStyle(1);
		vn_1coarse->SetLineWidth(2);
		TF1 *vn_1p5fine = new TF1("vn_1p5fine","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
		vn_1p5fine->SetLineColor(kViolet+1);
		vn_1p5fine->SetLineStyle(1);
		vn_1p5fine->SetLineWidth(2);
		TF1 *vn_1p5coarse = new TF1("vn_1p5coarse","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
		vn_1p5coarse->SetLineColor(kViolet+1);
		vn_1p5coarse->SetLineStyle(1);
		vn_1p5coarse->SetLineWidth(2);
		TF1 *vn_2fine = new TF1("vn_2fine","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
		vn_2fine->SetLineColor(kViolet+1);
		vn_2fine->SetLineStyle(1);
		vn_2fine->SetLineWidth(2);
		TF1 *vn_2coarse = new TF1("vn_2coarse","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
		vn_2coarse->SetLineColor(kViolet+1);
		vn_2coarse->SetLineStyle(1);
		vn_2coarse->SetLineWidth(2);
//}}}

//|deta| < 1{{{

//fine{{{
		cS1_fine->cd();
		hSDeltaPhi1_fine->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		cS1_fine->SaveAs(Form("CorrDist/CorrDistdphi/S_corr1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		cB1_fine->cd();
		hBDeltaPhi1_fine->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		cB1_fine->SaveAs(Form("CorrDist/CorrDistdphi/B_corr1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		cdphi1_fine->cd();
		hDeltaPhi1_fine->Draw("pe");
		hDeltaPhi1_fine->Fit(vn_1fine,"rqm");
		v2s_1fine[imass] = vn_1fine->GetParameter(1);
		v2Es_1fine[imass] = vn_1fine->GetParError(1);
		TF1 *v1_1fine = new TF1("v1_1fine","[0]*(1+2*[1]*cos(x))",-6.28,6.28);
		v1_1fine->SetLineColor(kBlue+1);
		v1_1fine->SetLineStyle(2);
		v1_1fine->SetLineWidth(2);
		v1_1fine->SetParameter(0, vn_1fine->GetParameter(0));
		v1_1fine->SetParameter(1, vn_1fine->GetParameter(2));
		TF1 *v2_1fine = new TF1("v2_1fine","[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
		v2_1fine->SetLineColor(kRed+1);
		v2_1fine->SetLineStyle(2);
		v2_1fine->SetLineWidth(2);
		v2_1fine->SetParameter(0, vn_1fine->GetParameter(0));
		v2_1fine->SetParameter(1, vn_1fine->GetParameter(1));
		v1_1fine->Draw("same");
		v2_1fine->Draw("same");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_1fine->GetParameter(1), vn_1fine->GetParError(1)));
		TLegend* l_1fine = new TLegend(0.77, 0.8, 0.95, 0.95);
		FormLegend(l_1fine, 0.04);
		l_1fine->AddEntry(vn_1fine, "total", "l");
		l_1fine->AddEntry(v1_1fine, "v1", "l");
		l_1fine->AddEntry(v2_1fine, "v2", "l");
		l_1fine->Draw();
		cdphi1_fine->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
//}}}

//coarse{{{
		cS1_coarse->cd();
		hSDeltaPhi1_coarse->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		cS1_coarse->SaveAs(Form("CorrDist/CorrDistdphi/S_corr1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));

		cB1_coarse->cd();
		hBDeltaPhi1_coarse->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		cB1_coarse->SaveAs(Form("CorrDist/CorrDistdphi/B_corr1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));

		cdphi1_coarse->cd();
		hDeltaPhi1_coarse->Draw("pe");
		hDeltaPhi1_coarse->Fit(vn_1coarse,"rqm");
		v2s_1coarse[imass] = vn_1coarse->GetParameter(1);
		v2Es_1coarse[imass] = vn_1coarse->GetParError(1);
		TF1 *v1_1coarse = new TF1("v1_1coarse","[0]*(1+2*[1]*cos(x))",-6.28,6.28);
		v1_1coarse->SetLineColor(kBlue+1);
		v1_1coarse->SetLineStyle(2);
		v1_1coarse->SetLineWidth(2);
		v1_1coarse->SetParameter(0, vn_1coarse->GetParameter(0));
		v1_1coarse->SetParameter(1, vn_1coarse->GetParameter(2));
		TF1 *v2_1coarse = new TF1("v2_1coarse","[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
		v2_1coarse->SetLineColor(kRed+1);
		v2_1coarse->SetLineStyle(2);
		v2_1coarse->SetLineWidth(2);
		v2_1coarse->SetParameter(0, vn_1coarse->GetParameter(0));
		v2_1coarse->SetParameter(1, vn_1coarse->GetParameter(1));
		v1_1coarse->Draw("same");
		v2_1coarse->Draw("same");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
		lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_1coarse->GetParameter(1), vn_1coarse->GetParError(1)));
		TLegend* l_1coarse= new TLegend(0.77, 0.8, 0.95, 0.95);
		FormLegend(l_1coarse, 0.04);
		l_1coarse->AddEntry(vn_1coarse, "total", "l");
		l_1coarse->AddEntry(v1_1coarse, "v1", "l");
		l_1coarse->AddEntry(v2_1coarse, "v2", "l");
		l_1coarse->Draw();
		cdphi1_coarse->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//}}}

//|deta| < 1.5{{{

//fine{{{
		cS1p5_fine->cd();
		hSDeltaPhi1p5_fine->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		cS1p5_fine->SaveAs(Form("CorrDist/CorrDistdphi/S_corr1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		cB1p5_fine->cd();
		hBDeltaPhi1p5_fine->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		cB1p5_fine->SaveAs(Form("CorrDist/CorrDistdphi/B_corr1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		cdphi1p5_fine->cd();
		hDeltaPhi1p5_fine->Draw("pe");
		hDeltaPhi1p5_fine->Fit(vn_1p5fine,"rqm");
		v2s_1p5fine[imass] = vn_1p5fine->GetParameter(1);
		v2Es_1p5fine[imass] = vn_1p5fine->GetParError(1);
		TF1 *v1_1p5fine = new TF1("v1_1p5fine","[0]*(1+2*[1]*cos(x))",-6.28,6.28);
		v1_1p5fine->SetLineColor(kBlue+1);
		v1_1p5fine->SetLineStyle(2);
		v1_1p5fine->SetLineWidth(2);
		v1_1p5fine->SetParameter(0, vn_1p5fine->GetParameter(0));
		v1_1p5fine->SetParameter(1, vn_1p5fine->GetParameter(2));
		TF1 *v2_1p5fine = new TF1("v2_1p5fine","[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
		v2_1p5fine->SetLineColor(kRed+1);
		v2_1p5fine->SetLineStyle(2);
		v2_1p5fine->SetLineWidth(2);
		v2_1p5fine->SetParameter(0, vn_1p5fine->GetParameter(0));
		v2_1p5fine->SetParameter(1, vn_1p5fine->GetParameter(1));
		v1_1p5fine->Draw("same");
		v2_1p5fine->Draw("same");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_1p5fine->GetParameter(1), vn_1p5fine->GetParError(1)));
		TLegend* l_1p5fine = new TLegend(0.77, 0.8, 0.95, 0.95);
		FormLegend(l_1p5fine, 0.04);
		l_1p5fine->AddEntry(vn_1p5fine, "total", "l");
		l_1p5fine->AddEntry(v1_1p5fine, "v1", "l");
		l_1p5fine->AddEntry(v2_1p5fine, "v2", "l");
		l_1p5fine->Draw();
		cdphi1p5_fine->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
//}}}

//coarse{{{
		cS1p5_coarse->cd();
		hSDeltaPhi1p5_coarse->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		cS1p5_coarse->SaveAs(Form("CorrDist/CorrDistdphi/S_corr1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));

		cB1p5_coarse->cd();
		hBDeltaPhi1p5_coarse->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		cB1p5_coarse->SaveAs(Form("CorrDist/CorrDistdphi/B_corr1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));

		cdphi1p5_coarse->cd();
		hDeltaPhi1p5_coarse->Draw("pe");
		hDeltaPhi1p5_coarse->Fit(vn_1p5coarse,"rqm");
		v2s_1p5coarse[imass] = vn_1p5coarse->GetParameter(1);
		v2Es_1p5coarse[imass] = vn_1p5coarse->GetParError(1);
		TF1 *v1_1p5coarse = new TF1("v1_1p5coarse","[0]*(1+2*[1]*cos(x))",-6.28,6.28);
		v1_1p5coarse->SetLineColor(kBlue+1);
		v1_1p5coarse->SetLineStyle(2);
		v1_1p5coarse->SetLineWidth(2);
		v1_1p5coarse->SetParameter(0, vn_1p5coarse->GetParameter(0));
		v1_1p5coarse->SetParameter(1, vn_1p5coarse->GetParameter(2));
		TF1 *v2_1p5coarse = new TF1("v2_1p5coarse","[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
		v2_1p5coarse->SetLineColor(kRed+1);
		v2_1p5coarse->SetLineStyle(2);
		v2_1p5coarse->SetLineWidth(2);
		v2_1p5coarse->SetParameter(0, vn_1p5coarse->GetParameter(0));
		v2_1p5coarse->SetParameter(1, vn_1p5coarse->GetParameter(1));
		v1_1p5coarse->Draw("same");
		v2_1p5coarse->Draw("same");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
		lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_1p5coarse->GetParameter(1), vn_1p5coarse->GetParError(1)));
		TLegend* l_1p5coarse = new TLegend(0.77, 0.8, 0.95, 0.95);
		FormLegend(l_1p5coarse, 0.04);
		l_1p5coarse->AddEntry(vn_1p5coarse, "total", "l");
		l_1p5coarse->AddEntry(v1_1p5coarse, "v1", "l");
		l_1p5coarse->AddEntry(v2_1p5coarse, "v2", "l");
		l_1p5coarse->Draw();
		cdphi1p5_coarse->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//}}}

//|deta| < 2{{{

//fine{{{
		cS2_fine->cd();
		hSDeltaPhi2_fine->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		cS2_fine->SaveAs(Form("CorrDist/CorrDistdphi/S_corr2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		cB2_fine->cd();
		hBDeltaPhi2_fine->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		cB2_fine->SaveAs(Form("CorrDist/CorrDistdphi/B_corr2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		cdphi2_fine->cd();
		hDeltaPhi2_fine->Draw("pe");
		hDeltaPhi2_fine->Fit(vn_2fine,"rqm");
		v2s_2fine[imass] = vn_2fine->GetParameter(1);
		v2Es_2fine[imass] = vn_2fine->GetParError(1);
		TF1 *v1_2fine = new TF1("v1_2fine","[0]*(1+2*[1]*cos(x))",-6.28,6.28);
		v1_2fine->SetLineColor(kBlue+1);
		v1_2fine->SetLineStyle(2);
		v1_2fine->SetLineWidth(2);
		v1_2fine->SetParameter(0, vn_2fine->GetParameter(0));
		v1_2fine->SetParameter(1, vn_2fine->GetParameter(2));
		TF1 *v2_2fine = new TF1("v2_2fine","[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
		v2_2fine->SetLineColor(kRed+1);
		v2_2fine->SetLineStyle(2);
		v2_2fine->SetLineWidth(2);
		v2_2fine->SetParameter(0, vn_2fine->GetParameter(0));
		v2_2fine->SetParameter(1, vn_2fine->GetParameter(1));
		v1_2fine->Draw("same");
		v2_2fine->Draw("same");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_2fine->GetParameter(1), vn_2fine->GetParError(1)));
		TLegend* l_2fine = new TLegend(0.77, 0.8, 0.95, 0.95);
		FormLegend(l_2fine, 0.04);
		l_2fine->AddEntry(vn_2fine, "total", "l");
		l_2fine->AddEntry(v1_2fine, "v1", "l");
		l_2fine->AddEntry(v2_2fine, "v2", "l");
		l_2fine->Draw();
		cdphi2_fine->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
//}}}

//coarse{{{
		cS2_coarse->cd();
		hSDeltaPhi2_coarse->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		cS2_coarse->SaveAs(Form("CorrDist/CorrDistdphi/S_corr2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));

		cB2_coarse->cd();
		hBDeltaPhi2_coarse->Draw("pe");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		cB2_coarse->SaveAs(Form("CorrDist/CorrDistdphi/B_corr2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));

		cdphi2_coarse->cd();
		hDeltaPhi2_coarse->Draw("pe");
		hDeltaPhi2_coarse->Fit(vn_2coarse,"rqm");
		v2s_2coarse[imass] = vn_2coarse->GetParameter(1);
		v2Es_2coarse[imass] = vn_2coarse->GetParError(1);
		TF1 *v1_2coarse = new TF1("v1_2coarse","[0]*(1+2*[1]*cos(x))",-6.28,6.28);
		v1_2coarse->SetLineColor(kBlue+1);
		v1_2coarse->SetLineStyle(2);
		v1_2coarse->SetLineWidth(2);
		v1_2coarse->SetParameter(0, vn_2coarse->GetParameter(0));
		v1_2coarse->SetParameter(1, vn_2coarse->GetParameter(2));
		TF1 *v2_2coarse = new TF1("v2_2coarse","[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
		v2_2coarse->SetLineColor(kRed+1);
		v2_2coarse->SetLineStyle(2);
		v2_2coarse->SetLineWidth(2);
		v2_2coarse->SetParameter(0, vn_2coarse->GetParameter(0));
		v2_2coarse->SetParameter(1, vn_2coarse->GetParameter(1));
		v1_2coarse->Draw("same");
		v2_2coarse->Draw("same");
		lt1->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
		lt1->DrawLatex(0.6,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_2coarse->GetParameter(1), vn_2coarse->GetParError(1)));
		TLegend* l_2coarse = new TLegend(0.77, 0.8, 0.95, 0.95);
		FormLegend(l_2coarse, 0.04);
		l_2coarse->AddEntry(vn_2coarse, "total", "l");
		l_2coarse->AddEntry(v1_2coarse, "v1", "l");
		l_2coarse->AddEntry(v2_2coarse, "v2", "l");
		l_2coarse->Draw();
		cdphi2_coarse->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_sepa_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//}}}

//}}}

		massCentArr[imass] = 8 + massBinsArr[imass]*0.05 + (massBinsArr[imass+1]-massBinsArr[imass])*0.05/2.;
		massValsArr[imass+1] = 8 + massBinsArr[imass+1]*0.05;
	}

//Define graph{{{
	TH1D* hRef = new TH1D("hRef", "", mass_narr-1, massValsArr);
	FormTH1(hRef, 0);
	hRef->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
	hRef->GetYaxis()->SetTitle("v_{2}^{S+B}");
	hRef->SetMinimum(-0.05);
	hRef->SetMaximum(0.05);

	TGraphErrors* gv2_1fine = new TGraphErrors(mass_narr-1, massCentArr, v2s_1fine, 0, v2Es_1fine);
	gv2_1fine->SetName("gv2_1fine");
	gv2_1fine->SetMaximum(0.05);
	gv2_1fine->SetMinimum(-0.05);
	TGraphErrors* gv2_1coarse = new TGraphErrors(mass_narr-1, massCentArr, v2s_1coarse, 0, v2Es_1coarse);
	gv2_1coarse->SetName("gv2_1coarse");
	gv2_1coarse->SetMaximum(0.05);
	gv2_1coarse->SetMinimum(-0.05);
	TGraphErrors* gv2_1p5fine = new TGraphErrors(mass_narr-1, massCentArr, v2s_1p5fine, 0, v2Es_1p5fine);
	gv2_1p5fine->SetName("gv2_1p5fine");
	gv2_1p5fine->SetMaximum(0.05);
	gv2_1p5fine->SetMinimum(-0.05);
	TGraphErrors* gv2_1p5coarse = new TGraphErrors(mass_narr-1, massCentArr, v2s_1p5coarse, 0, v2Es_1p5coarse);
	gv2_1p5coarse->SetName("gv2_1p5coarse");
	gv2_1p5coarse->SetMaximum(0.05);
	gv2_1p5coarse->SetMinimum(-0.05);
	TGraphErrors* gv2_2fine = new TGraphErrors(mass_narr-1, massCentArr, v2s_2fine, 0, v2Es_2fine);
	gv2_2fine->SetName("gv2_2fine");
	gv2_2fine->SetMaximum(0.05);
	gv2_2fine->SetMinimum(-0.05);
	TGraphErrors* gv2_2coarse = new TGraphErrors(mass_narr-1, massCentArr, v2s_2coarse, 0, v2Es_2coarse);
	gv2_2coarse->SetName("gv2_2coarse");
	gv2_2coarse->SetMaximum(0.05);
	gv2_2coarse->SetMinimum(-0.05);
//}}}

//|deta| < 1{{{
	cv2_1fine->cd();
	hRef->Draw();
	gv2_1fine->SetMarkerStyle(20);
	gv2_1fine->SetMarkerSize(1.2);
	//gv2_1fine->SetMarkerSize(0);
	gv2_1fine->Draw("pesame");
	lt2->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
	lt2->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt2->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
	cv2_1fine->SaveAs(Form("CorrDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_sepa_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
	//cv2_1fine->SaveAs(Form("CorrDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));

	cv2_1coarse->cd();
	hRef->Draw();
	gv2_1coarse->SetMarkerStyle(20);
	gv2_1coarse->SetMarkerSize(1.2);
	//gv2_1coarse->SetMarkerSize(0);
	gv2_1coarse->Draw("pesame");
	lt2->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
	lt2->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt2->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.0");
	cv2_1coarse->SaveAs(Form("CorrDist/V2Dist/v2_dist_1coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_sepa_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
	//cv2_1coarse->SaveAs(Form("CorrDist/V2Dist/v2_dist_1coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
//}}}

//|deta| < 1.5{{{
	cv2_1p5fine->cd();
	hRef->Draw();
	gv2_1p5fine->SetMarkerStyle(20);
	gv2_1p5fine->SetMarkerSize(1.2);
	//gv2_1p5fine->SetMarkerSize(0);
	gv2_1p5fine->Draw("pesame");
	lt2->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
	lt2->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt2->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
	cv2_1p5fine->SaveAs(Form("CorrDist/V2Dist/v2_dist_1p5fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_sepa_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
	//cv2_1p5fine->SaveAs(Form("CorrDist/V2Dist/v2_dist_1p5fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));

	cv2_1p5coarse->cd();
	hRef->Draw();
	gv2_1p5coarse->SetMarkerStyle(20);
	gv2_1p5coarse->SetMarkerSize(1.2);
	//gv2_1p5coarse->SetMarkerSize(0);
	gv2_1p5coarse->Draw("pesame");
	lt2->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
	lt2->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt2->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 1.5");
	cv2_1p5coarse->SaveAs(Form("CorrDist/V2Dist/v2_dist_1p5coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_sepa_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
	//cv2_1p5coarse->SaveAs(Form("CorrDist/V2Dist/v2_dist_1p5coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
//}}}

//|deta| < 2{{{
	cv2_2fine->cd();
	hRef->Draw();
	gv2_2fine->SetMarkerStyle(20);
	gv2_2fine->SetMarkerSize(1.2);
	//gv2_2fine->SetMarkerSize(0);
	gv2_2fine->Draw("pesame");
	lt2->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
	lt2->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt2->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
	cv2_2fine->SaveAs(Form("CorrDist/V2Dist/v2_dist_2fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_sepa_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
	//cv2_2fine->SaveAs(Form("CorrDist/V2Dist/v2_dist_2fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));

	cv2_2coarse->cd();
	hRef->Draw();
	gv2_2coarse->SetMarkerStyle(20);
	gv2_2coarse->SetMarkerSize(1.2);
	//gv2_2coarse->SetMarkerSize(0);
	gv2_2coarse->Draw("pesame");
	lt2->DrawLatex(0.2,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
	lt2->DrawLatex(0.2,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt2->DrawLatex(0.2,0.8, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt2->DrawLatex(0.2,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	lt2->DrawLatex(0.2,0.75, "|#Delta#eta^{trk}| > 2.0");
	cv2_2coarse->SaveAs(Form("CorrDist/V2Dist/v2_dist_2coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_sepa_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
	//cv2_2coarse->SaveAs(Form("CorrDist/V2Dist/v2_dist_2coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
//}}}

	TFile* fout = new TFile(Form("CorrDist/CorrFiles/v2_dist_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "RECREATE");
	fout->cd();
	gv2_1fine->Write();
	gv2_1coarse->Write();
	gv2_1p5fine->Write();
	gv2_1p5coarse->Write();
	gv2_2fine->Write();
	gv2_2coarse->Write();
}
