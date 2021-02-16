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

void Variation_Jvar(const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 50, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Bool_t isfine = true, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v41", const TString MupT = "4")
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
	TH1D* hist1 = new TH1D("hist1", "", 30, 0, 30);
	FormTH1Marker(hist1, 0, 0, 1.4);
	hist1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist1->GetYaxis()->SetTitle("v_{2}");
	hist1->SetMinimum(-0.1);
	hist1->SetMaximum(0.15);
	TH1D* hist2 = new TH1D("hist2", "", 30, 0, 30);
	FormTH1Marker(hist2, 0, 0, 1.4);
	hist2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist2->GetYaxis()->SetTitle("v_{2} diff.");
	hist2->SetMinimum(-0.05);
	hist2->SetMaximum(0.05);
//}}}

	TFile* fout = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys0_BkgSys0_pol2_MupT%s_Jvar.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fref;
	TFile* fsys;
	fref = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	fsys = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys0_BkgSys0_pol2_MupT%s_Jvar.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
//}}}

//calculate v2 value{{{
	TGraphErrors* gref = (TGraphErrors*) fref->Get(Form("gv2"));
	gref->SetName("gv2_ref");
	gref->SetMarkerColor(kRed+1);
	gref->SetLineColor(kRed+1);
	TGraphErrors* gsys_pl = (TGraphErrors*) fsys->Get(Form("gv2_pl"));
	gsys_pl->SetName("gv2_sys_pl");
	gsys_pl->SetMarkerColor(1);
	gsys_pl->SetLineColor(1);
	TGraphErrors* gsys_mi = (TGraphErrors*) fsys->Get(Form("gv2_mi"));
	gsys_mi->SetName("gv2_sys_mi");
	gsys_mi->SetMarkerColor(kBlue+1);
	gsys_mi->SetLineColor(kBlue+1);

	Double_t v2xref[4];
	Double_t v2yref[4];
	Double_t v2xsys_pl[4];
	Double_t v2ysys_pl[4];
	Double_t v2xsys_mi[4];
	Double_t v2ysys_mi[4];
	Double_t Exref[4];
	Double_t Eyref[4];
	Double_t Exsys_pl[4];
	Double_t Eysys_pl[4];
	Double_t Exsys_mi[4];
	Double_t Eysys_mi[4];
	Double_t v2ydiff_pl[4];
	Double_t Ev2ydiff_pl[4];
	Double_t v2ydiff_mi[4];
	Double_t Ev2ydiff_mi[4];

	for(Int_t ibin = 0; ibin < gref->GetN(); ibin++)
	{
		gref->GetPoint(ibin, v2xref[ibin], v2yref[ibin]);
		gsys_pl->GetPoint(ibin, v2xsys_pl[ibin], v2ysys_pl[ibin]);
		gsys_mi->GetPoint(ibin, v2xsys_mi[ibin], v2ysys_mi[ibin]);
		Exref[ibin] = gref->GetErrorX(ibin);
		Exsys_pl[ibin] = gsys_pl->GetErrorX(ibin);
		Exsys_mi[ibin] = gsys_mi->GetErrorX(ibin);
		Eyref[ibin] = gref->GetErrorY(ibin);
		Eysys_pl[ibin] = gsys_pl->GetErrorY(ibin);
		Eysys_mi[ibin] = gsys_mi->GetErrorY(ibin);
		gsys_pl->SetPoint(ibin, v2xsys_pl[ibin]+0.2, v2ysys_pl[ibin]);
		gsys_pl->SetPointError(ibin, Exsys_pl[ibin], Eysys_pl[ibin]);
		gsys_mi->SetPoint(ibin, v2xsys_mi[ibin]+0.4, v2ysys_mi[ibin]);
		gsys_mi->SetPointError(ibin, Exsys_mi[ibin], Eysys_mi[ibin]);
		v2ydiff_pl[ibin] = v2yref[ibin]-v2ysys_pl[ibin];
		v2ydiff_mi[ibin] = v2yref[ibin]-v2ysys_mi[ibin];
		Ev2ydiff_pl[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eysys_pl[ibin]*Eysys_pl[ibin]);
		Ev2ydiff_mi[ibin] = TMath::Sqrt(Eyref[ibin]*Eyref[ibin]+Eysys_mi[ibin]*Eysys_mi[ibin]);
	//	rate[ibin] = v2ydiff[ibin]/TMath::Abs(v2yref[ibin]);
//cout << rate[ibin] << endl;
	}

	c1->cd();
	hist1->Draw();
	gref->Draw("samepe");
	gsys_pl->Draw("samepe");
	gsys_mi->Draw("samepe");
	TLegend* lg1 = new TLegend(0.6, 0.65, 0.9, 0.85);
	FormLegend(lg1, 0.04);
	lg1->AddEntry(gref, "Default", "pl");
	lg1->AddEntry(gsys_pl, Form("J_{ratio}+#sigma"), "pl");
	lg1->AddEntry(gsys_mi, Form("J_{ratio}-#sigma"), "pl");
	lg1->Draw();
	c1->SaveAs(Form("SystPlot/MupT%s/Syst_v2_comp_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys0_BkgSys0_pol2_MupT%s_Jvar.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c2->cd();
	hist2->Draw();
	TGraphErrors* gdiff_pl = new TGraphErrors(gref->GetN(), v2xref, v2ydiff_pl, Exref, Ev2ydiff_pl);
	gdiff_pl->SetName("gv2_pl");
	gdiff_pl->SetMarkerStyle(20);
	gdiff_pl->SetMarkerColor(kRed+1);
	gdiff_pl->SetLineColor(kRed+1);
	gdiff_pl->Draw("samepe");
	TGraphErrors* gdiff_mi = new TGraphErrors(gref->GetN(), v2xref, v2ydiff_mi, Exref, Ev2ydiff_mi);
	gdiff_mi->SetName("gv2_mi");
	gdiff_mi->SetMarkerStyle(20);
	gdiff_mi->SetMarkerColor(kBlue+1);
	gdiff_mi->SetLineColor(kBlue+1);
	gdiff_mi->Draw("samepe");
	SetLine(1, 0, 0, 30, 0, 0, 3);
	c2->SaveAs(Form("SystPlot/MupT%s/Syst_v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys0_BkgSys0_pol2_MupT%s_Jvar.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	fout->cd();
	gdiff_pl->Write();
	gdiff_mi->Write();
	fout->Close();
//}}}
}
