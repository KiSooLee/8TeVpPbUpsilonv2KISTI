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

void Variation_TnP(const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 50, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Bool_t isfine = true, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v41", const TString MupT = "4")
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
	TCanvas* c4 = new TCanvas("c4", "", 0, 0, 600, 600);
	TCanvas* c5 = new TCanvas("c5", "", 0, 0, 600, 600);
	TCanvas* c6 = new TCanvas("c6", "", 0, 0, 600, 600);
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

	TFile* fout = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPs_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fref;
	TFile* fstatup;
	TFile* fstatdw;
	TFile* fsystup;
	TFile* fsystdw;
	fref = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	fstatup = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPstatup_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	fstatdw = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPstatdw_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	fsystup = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPsystup_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	fsystdw = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPsystdw_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
//}}}

//calculate v2 value{{{

//get graph{{{
	TGraphErrors* gref = (TGraphErrors*) fref->Get(Form("gv2"));
	gref->SetName("gv2_ref");
	gref->SetMarkerColor(kRed+1);
	gref->SetMarkerSize(1.4);
	gref->SetLineColor(kRed+1);
	TGraphErrors* gstat_up = (TGraphErrors*) fstatup->Get(Form("gv2"));
	gstat_up->SetName("gv2_stat_up");
	gstat_up->SetMarkerColor(1);
	gstat_up->SetMarkerSize(1.4);
	gstat_up->SetLineColor(1);
	TGraphErrors* gstat_dw = (TGraphErrors*) fstatdw->Get(Form("gv2"));
	gstat_dw->SetName("gv2_stat_dw");
	gstat_dw->SetMarkerColor(kBlue+1);
	gstat_dw->SetMarkerSize(1.4);
	gstat_dw->SetLineColor(kBlue+1);
	TGraphErrors* gsyst_up = (TGraphErrors*) fsystup->Get(Form("gv2"));
	gsyst_up->SetName("gv2_syst_up");
	gsyst_up->SetMarkerColor(1);
	gsyst_up->SetMarkerSize(1.4);
	gsyst_up->SetLineColor(1);
	TGraphErrors* gsyst_dw = (TGraphErrors*) fsystdw->Get(Form("gv2"));
	gsyst_dw->SetName("gv2_syst_dw");
	gsyst_dw->SetMarkerColor(kBlue+1);
	gsyst_dw->SetMarkerSize(1.4);
	gsyst_dw->SetLineColor(kBlue+1);
//}}}

//set parameter{{{
	Double_t v2xref[4];
	Double_t v2yref[4];
	Double_t v2xstat_up[4];
	Double_t v2ystat_up[4];
	Double_t v2xstat_dw[4];
	Double_t v2ystat_dw[4];
	Double_t v2xsyst_up[4];
	Double_t v2ysyst_up[4];
	Double_t v2xsyst_dw[4];
	Double_t v2ysyst_dw[4];
	Double_t Exref[4];
	Double_t Eyref[4];
	Double_t Exstat_up[4];
	Double_t Eystat_up[4];
	Double_t Exstat_dw[4];
	Double_t Eystat_dw[4];
	Double_t Exsyst_up[4];
	Double_t Eysyst_up[4];
	Double_t Exsyst_dw[4];
	Double_t Eysyst_dw[4];
	Double_t v2ydiff_stat_up[4];
	Double_t Ev2ydiff_stat_up[4];
	Double_t v2ydiff_stat_dw[4];
	Double_t Ev2ydiff_stat_dw[4];
	Double_t v2ydiff_syst_up[4];
	Double_t Ev2ydiff_syst_up[4];
	Double_t v2ydiff_syst_dw[4];
	Double_t Ev2ydiff_syst_dw[4];
	Double_t v2yratio_stat_up[4];
	Double_t Ev2yratio_stat_up[4];
	Double_t v2yratio_stat_dw[4];
	Double_t Ev2yratio_stat_dw[4];
	Double_t v2yratio_syst_up[4];
	Double_t Ev2yratio_syst_up[4];
	Double_t v2yratio_syst_dw[4];
	Double_t Ev2yratio_syst_dw[4];
//}}}

	for(Int_t ibin = 0; ibin < gref->GetN(); ibin++)
	{
//get points and error{{{
		gref->GetPoint(ibin, v2xref[ibin], v2yref[ibin]);
		gstat_up->GetPoint(ibin, v2xstat_up[ibin], v2ystat_up[ibin]);
		gstat_dw->GetPoint(ibin, v2xstat_dw[ibin], v2ystat_dw[ibin]);
		gsyst_up->GetPoint(ibin, v2xsyst_up[ibin], v2ysyst_up[ibin]);
		gsyst_dw->GetPoint(ibin, v2xsyst_dw[ibin], v2ysyst_dw[ibin]);

		Exref[ibin] = gref->GetErrorX(ibin);
		Exstat_up[ibin] = gstat_up->GetErrorX(ibin);
		Exstat_dw[ibin] = gstat_dw->GetErrorX(ibin);
		Exsyst_up[ibin] = gsyst_up->GetErrorX(ibin);
		Exsyst_dw[ibin] = gsyst_dw->GetErrorX(ibin);

		Eyref[ibin] = gref->GetErrorY(ibin);
		Eystat_up[ibin] = gstat_up->GetErrorY(ibin);
		Eystat_dw[ibin] = gstat_dw->GetErrorY(ibin);
		Eysyst_up[ibin] = gsyst_up->GetErrorY(ibin);
		Eysyst_dw[ibin] = gsyst_dw->GetErrorY(ibin);
//}}}

//set graph{{{
		gstat_up->SetPoint(ibin, v2xstat_up[ibin]+0.5, v2ystat_up[ibin]);
		gstat_up->SetPointError(ibin, Exstat_up[ibin], Eystat_up[ibin]);
		gstat_dw->SetPoint(ibin, v2xstat_dw[ibin]-0.5, v2ystat_dw[ibin]);
		gstat_dw->SetPointError(ibin, Exstat_dw[ibin], Eystat_dw[ibin]);
		gsyst_up->SetPoint(ibin, v2xsyst_up[ibin]+0.5, v2ysyst_up[ibin]);
		gsyst_up->SetPointError(ibin, Exsyst_up[ibin], Eysyst_up[ibin]);
		gsyst_dw->SetPoint(ibin, v2xsyst_dw[ibin]-0.5, v2ysyst_dw[ibin]);
		gsyst_dw->SetPointError(ibin, Exsyst_dw[ibin], Eysyst_dw[ibin]);
//}}}

//get difference{{{
		v2ydiff_stat_up[ibin] = v2yref[ibin]-v2ystat_up[ibin];
		v2ydiff_stat_dw[ibin] = v2yref[ibin]-v2ystat_dw[ibin];
		Ev2ydiff_stat_up[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eystat_up[ibin]*Eystat_up[ibin]);
		Ev2ydiff_stat_dw[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eystat_dw[ibin]*Eystat_dw[ibin]);
		v2ydiff_syst_up[ibin] = v2yref[ibin]-v2ysyst_up[ibin];
		v2ydiff_syst_dw[ibin] = v2yref[ibin]-v2ysyst_dw[ibin];
		Ev2ydiff_syst_up[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eysyst_up[ibin]*Eysyst_up[ibin]);
		Ev2ydiff_syst_dw[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eysyst_dw[ibin]*Eysyst_dw[ibin]);
//}}}

//get ratio{{{
		v2yratio_stat_up[ibin] = v2ystat_up[ibin]/v2yref[ibin];
		v2yratio_stat_dw[ibin] = v2ystat_dw[ibin]/v2yref[ibin];
		Ev2yratio_stat_up[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eystat_up[ibin]*Eystat_up[ibin]);
		Ev2yratio_stat_dw[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eystat_dw[ibin]*Eystat_dw[ibin]);
		v2yratio_syst_up[ibin] = v2ysyst_up[ibin]/v2yref[ibin];
		v2yratio_syst_dw[ibin] = v2ysyst_dw[ibin]/v2yref[ibin];
		Ev2yratio_syst_up[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eysyst_up[ibin]*Eysyst_up[ibin]);
		Ev2yratio_syst_dw[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eysyst_dw[ibin]*Eysyst_dw[ibin]);
//}}}
	//	rate[ibin] = v2ydiff[ibin]/TMath::Abs(v2yref[ibin]);
//cout << rate[ibin] << endl;
	}

	c1->cd();
	hist1->Draw();
	gref->Draw("samepe");
	gstat_up->Draw("samepe");
	gstat_dw->Draw("samepe");
	TLegend* lg1 = new TLegend(0.6, 0.65, 0.9, 0.85);
	FormLegend(lg1, 0.04);
	lg1->AddEntry(gref, "Default", "pl");
	lg1->AddEntry(gstat_up, "Up", "pl");
	lg1->AddEntry(gstat_dw, "Down", "pl");
	lg1->Draw();
	c1->SaveAs(Form("SystPlot/MupT%s/Syst_v2_comp_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPstat_SigSys0_BkgSys0_pol2_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c2->cd();
	hist1->Draw();
	gref->Draw("samepe");
	gsyst_up->Draw("samepe");
	gsyst_dw->Draw("samepe");
	TLegend* lg2 = new TLegend(0.6, 0.65, 0.9, 0.85);
	FormLegend(lg2, 0.04);
	lg2->AddEntry(gref, "Default", "pl");
	lg2->AddEntry(gsyst_up, "Up", "pl");
	lg2->AddEntry(gsyst_dw, "Down", "pl");
	lg2->Draw();
	c2->SaveAs(Form("SystPlot/MupT%s/Syst_v2_comp_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPsyst_SigSys0_BkgSys0_pol2_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c3->cd();
	hist2->Draw();
	TGraphErrors* gdiff_stat_up = new TGraphErrors(gref->GetN(), v2xref, v2ydiff_stat_up, Exref, Ev2ydiff_stat_up);
	gdiff_stat_up->SetName("gv2_stat_up");
	gdiff_stat_up->SetMarkerStyle(20);
	gdiff_stat_up->SetMarkerColor(kRed+1);
	gdiff_stat_up->SetMarkerSize(1.4);
	gdiff_stat_up->SetLineColor(kRed+1);
	gdiff_stat_up->Draw("samepe");
	TGraphErrors* gdiff_stat_dw = new TGraphErrors(gref->GetN(), v2xref, v2ydiff_stat_dw, Exref, Ev2ydiff_stat_dw);
	gdiff_stat_dw->SetName("gv2_stat_dw");
	gdiff_stat_dw->SetMarkerStyle(20);
	gdiff_stat_dw->SetMarkerColor(kBlue+1);
	gdiff_stat_dw->SetMarkerSize(1.4);
	gdiff_stat_dw->SetLineColor(kBlue+1);
	gdiff_stat_dw->Draw("samepe");
	SetLine(1, 0, 0, 30, 0, 0, 3);
	TLegend* lg3 = new TLegend(0.6, 0.65, 0.9, 0.85);
	FormLegend(lg3, 0.04);
	lg3->AddEntry(gdiff_stat_up, "Up", "pl");
	lg3->AddEntry(gdiff_stat_dw, "Down", "pl");
	lg3->Draw();
	c3->SaveAs(Form("SystPlot/MupT%s/Syst_v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPstat_SigSys0_BkgSys0_pol2_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c4->cd();
	hist2->Draw();
	TGraphErrors* gdiff_syst_up = new TGraphErrors(gref->GetN(), v2xref, v2ydiff_syst_up, Exref, Ev2ydiff_syst_up);
	gdiff_syst_up->SetName("gv2_syst_up");
	gdiff_syst_up->SetMarkerStyle(20);
	gdiff_syst_up->SetMarkerColor(kRed+1);
	gdiff_syst_up->SetMarkerSize(1.4);
	gdiff_syst_up->SetLineColor(kRed+1);
	gdiff_syst_up->Draw("samepe");
	TGraphErrors* gdiff_syst_dw = new TGraphErrors(gref->GetN(), v2xref, v2ydiff_syst_dw, Exref, Ev2ydiff_syst_dw);
	gdiff_syst_dw->SetName("gv2_syst_dw");
	gdiff_syst_dw->SetMarkerStyle(20);
	gdiff_syst_dw->SetMarkerColor(kBlue+1);
	gdiff_syst_dw->SetMarkerSize(1.4);
	gdiff_syst_dw->SetLineColor(kBlue+1);
	gdiff_syst_dw->Draw("samepe");
	SetLine(1, 0, 0, 30, 0, 0, 3);
	TLegend* lg4 = new TLegend(0.6, 0.65, 0.9, 0.85);
	FormLegend(lg4, 0.04);
	lg4->AddEntry(gdiff_syst_up, "Up", "pl");
	lg4->AddEntry(gdiff_syst_dw, "Down", "pl");
	lg4->Draw();
	c4->SaveAs(Form("SystPlot/MupT%s/Syst_v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPsyst_SigSys0_BkgSys0_pol2_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c5->cd();
	hist3->Draw();
	TGraphErrors* gratio_stat_up = new TGraphErrors(gref->GetN(), v2xref, v2yratio_stat_up, Exref, Ev2yratio_stat_up);
	gratio_stat_up->SetName("gv2_ratio_stat_up");
	gratio_stat_up->SetMarkerStyle(20);
	gratio_stat_up->SetMarkerColor(kRed+1);
	gratio_stat_up->SetMarkerSize(1.4);
	gratio_stat_up->SetLineColor(kRed+1);
	gratio_stat_up->Draw("samepe");
	TGraphErrors* gratio_stat_dw = new TGraphErrors(gref->GetN(), v2xref, v2yratio_stat_dw, Exref, Ev2yratio_stat_dw);
	gratio_stat_dw->SetName("gv2_ratio_stat_dw");
	gratio_stat_dw->SetMarkerStyle(20);
	gratio_stat_dw->SetMarkerColor(kBlue+1);
	gratio_stat_dw->SetMarkerSize(1.4);
	gratio_stat_dw->SetLineColor(kBlue+1);
	gratio_stat_dw->Draw("samepe");
	SetLine(1, 0, 1, 30, 1, 0, 3);
	TLegend* lg5 = new TLegend(0.6, 0.65, 0.9, 0.85);
	FormLegend(lg5, 0.04);
	lg5->AddEntry(gratio_stat_up, "Up", "pl");
	lg5->AddEntry(gratio_stat_dw, "Down", "pl");
	lg5->Draw();
	c5->SaveAs(Form("SystPlot/MupT%s/Syst_v2_ratio_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPstat_SigSys0_BkgSys0_pol2_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c6->cd();
	hist3->Draw();
	TGraphErrors* gratio_syst_up = new TGraphErrors(gref->GetN(), v2xref, v2yratio_syst_up, Exref, Ev2yratio_syst_up);
	gratio_syst_up->SetName("gv2_ratio_syst_up");
	gratio_syst_up->SetMarkerStyle(20);
	gratio_syst_up->SetMarkerColor(kRed+1);
	gratio_syst_up->SetMarkerSize(1.4);
	gratio_syst_up->SetLineColor(kRed+1);
	gratio_syst_up->Draw("samepe");
	TGraphErrors* gratio_syst_dw = new TGraphErrors(gref->GetN(), v2xref, v2yratio_syst_dw, Exref, Ev2yratio_syst_dw);
	gratio_syst_dw->SetName("gv2_ratio_stat_dw");
	gratio_syst_dw->SetMarkerStyle(20);
	gratio_syst_dw->SetMarkerColor(kBlue+1);
	gratio_syst_dw->SetMarkerSize(1.4);
	gratio_syst_dw->SetLineColor(kBlue+1);
	gratio_syst_dw->Draw("samepe");
	SetLine(1, 0, 1, 30, 1, 0, 3);
	TLegend* lg6 = new TLegend(0.6, 0.65, 0.9, 0.85);
	FormLegend(lg6, 0.04);
	lg6->AddEntry(gratio_syst_up, "Up", "pl");
	lg6->AddEntry(gratio_syst_dw, "Down", "pl");
	lg6->Draw();
	c6->SaveAs(Form("SystPlot/MupT%s/Syst_v2_ratio_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPsyst_SigSys0_BkgSys0_pol2_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	fout->cd();
	gdiff_stat_up->Write();
	gdiff_stat_dw->Write();
	gdiff_syst_up->Write();
	gdiff_syst_dw->Write();
	fout->Close();
//}}}
}
