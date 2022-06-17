//Headers{{{
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <TMath.h>
#include "../Headers/Upsilon.h"
#include "../Headers/Style_Upv2.h"
//}}}

void Variation_Par(const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 50, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Bool_t isfine = true, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v41", const TString MupT = "4", const Int_t FreeParN = 0)
{
	SetStyle();

//set fitting condition name{{{
	TString Fine;
	if(isfine) Fine = "fine";
	else Fine = "coarse";
	TString Ffit;
	if(maxF == 2) Ffit = "_quad";
	else if(maxF == 3) Ffit = "_tra";
	else
	{
		cout << "there is no such Furier function" << endl;
		return;
	}
//}}}

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString pDIR = mainDIR + Form("/SystPlot/MupT%s", MupT.Data());
	TString fDIR = mainDIR + Form("/SystFile/MupT%s", MupT.Data());

	void * dirp = gSystem->OpenDirectory(pDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(pDIR.Data(), kTRUE);
	void * dirf = gSystem->OpenDirectory(fDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fDIR.Data(), kTRUE);
//}}}

//Define canvas for yield and vn dist{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
	TCanvas* c3 = new TCanvas("c3", "", 0, 0, 600, 600);
	TH1D* hist1 = new TH1D("hist1", "", 30, 0, 30);
	FormTH1Marker(hist1, 0, 0, 1.4);
	hist1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist1->GetYaxis()->SetTitle("v_{2}");
	hist1->SetMinimum(-0.07);
	hist1->SetMaximum(0.15);
	TH1D* hist2 = new TH1D("hist2", "", 30, 0, 30);
	FormTH1Marker(hist2, 0, 0, 1.4);
	hist2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist2->GetYaxis()->SetTitle("v_{2} diff.");
	hist2->SetMinimum(-0.1);
	hist2->SetMaximum(0.1);
	TH1D* hist3 = new TH1D("hist3", "", 30, 0, 30);
	FormTH1Marker(hist3, 0, 0, 1.4);
	hist3->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist3->GetYaxis()->SetTitle("v_{2} ratio");
	hist3->SetMinimum(0.0);
	hist3->SetMaximum(2.0);
//}}}

	TFile* fout = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_FreePar%d.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data(), FreeParN), "RECREATE");

//Get vn file{{{
	TFile* fref;
	TFile* fsys;
	fref = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	fsys = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_tra_FreePar%d.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data(), FreeParN), "READ");
//}}}

//calculate v2 value{{{
	TGraphErrors* gref = (TGraphErrors*) fref->Get(Form("gv2"));
	gref->SetName("gv2_ref");
	gref->SetMarkerColor(kRed+1);
	gref->SetMarkerSize(1.4);
	gref->SetLineColor(kRed+1);
	TGraphErrors* gsys = (TGraphErrors*) fsys->Get(Form("gv2"));
	gsys->SetName("gv2_sys");
	gsys->SetMarkerColor(1);
	gsys->SetMarkerSize(1.4);
	gsys->SetLineColor(1);

	Double_t v2xref[4];
	Double_t v2yref[4];
	Double_t v2xsys[4];
	Double_t v2ysys[4];
	Double_t Exref[4];
	Double_t Eyref[4];
	Double_t Exsys[4];
	Double_t Eysys[4];
	Double_t v2ydiff[4];
	Double_t Ev2ydiff[4];
	Double_t v2yratio[4];
	Double_t Ev2yratio[4];
	Double_t rate[4];

	for(Int_t ibin = 0; ibin < gref->GetN(); ibin++)
	{
		gref->GetPoint(ibin, v2xref[ibin], v2yref[ibin]);
		gsys->GetPoint(ibin, v2xsys[ibin], v2ysys[ibin]);
		Exref[ibin] = gref->GetErrorX(ibin);
		Exsys[ibin] = gsys->GetErrorX(ibin);
		Eyref[ibin] = gref->GetErrorY(ibin);
		Eysys[ibin] = gsys->GetErrorY(ibin);
		gsys->SetPoint(ibin, v2xsys[ibin]+0.5, v2ysys[ibin]);
		gsys->SetPointError(ibin, Exsys[ibin], Eysys[ibin]);
		v2ydiff[ibin] = v2yref[ibin]-v2ysys[ibin];
		Ev2ydiff[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eysys[ibin]*Eysys[ibin]);
		v2yratio[ibin] = v2ysys[ibin]/v2yref[ibin];
		Ev2yratio[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eysys[ibin]*Eysys[ibin]);
	//	rate[ibin] = v2ydiff[ibin]/TMath::Abs(v2yref[ibin]);
//cout << rate[ibin] << endl;
	}

	c1->cd();
	hist1->Draw();
	gref->Draw("samepe");
	gsys->Draw("samepe");
	TLegend* lg1 = new TLegend(0.6, 0.7, 0.9, 0.85);
	FormLegend(lg1, 0.04);
	lg1->AddEntry(gref, "Default", "pl");
	lg1->AddEntry(gsys, "Variation", "pl");
	lg1->Draw();
	c1->SaveAs(Form("SystPlot/MupT%s/Syst_v2_comp_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_FreePar%d.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data(), FreeParN));

	c2->cd();
	hist2->Draw();
	TGraphErrors* gdiff = new TGraphErrors(gref->GetN(), v2xref, v2ydiff, Exref, Ev2ydiff);
	gdiff->SetName("gv2");
	gdiff->SetMarkerStyle(20);
	gdiff->SetMarkerSize(1.4);
	gdiff->Draw("samepe");
	SetLine(1, 0, 0, 30, 0, 0, 3);
	c2->SaveAs(Form("SystPlot/MupT%s/Syst_v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_FreePar%d.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data(), FreeParN));

	c3->cd();
	hist3->Draw();
	TGraphErrors* gratio = new TGraphErrors(gref->GetN(), v2xref, v2yratio, Exref, Ev2yratio);
	gratio->SetName("gv2_ratio");
	gratio->SetMarkerStyle(20);
	gratio->SetMarkerSize(1.4);
	gratio->Draw("samepe");
	SetLine(1, 0, 1, 30, 1, 0, 3);
	c3->SaveAs(Form("SystPlot/MupT%s/Syst_v2_ratio_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_FreePar%d.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data(), FreeParN));

	fout->cd();
	gdiff->Write();
	fout->Close();
//}}}
}
