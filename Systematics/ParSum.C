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

void ParSum(const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 50, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Bool_t isfine = true, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v41", const TString MupT = "4")
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
	TH1D* hist = new TH1D("hist", "", 30, 0, 30);
	FormTH1Marker(hist, 0, 0, 1.4);
	hist->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist->GetYaxis()->SetTitle("v_{2} diff.");
	hist->SetMinimum(-0.001);
	hist->SetMaximum(0.01);
//}}}

	TFile* fout = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_ParSum.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fpar[9];
	TGraphErrors* gpar[9];
	Double_t v2xpar[9][4];
	Double_t v2ypar[9][4];
	Double_t Expar[9][4];
	Double_t Eypar[9][4];
	Double_t v2ysum[4] = {0.};
	Double_t Ev2ysum[4] = {0.000001, 0.000001, 0.000001, 0.000001};

	for(Int_t ipar = 0; ipar < 9; ipar++)
	{
		fpar[ipar] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_FreePar%d.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data(), ipar), "READ");
		gpar[ipar] = (TGraphErrors*) fpar[ipar]->Get(Form("gv2"));
		gpar[ipar]->SetName(Form("gv2_par%d", ipar));

		for(Int_t ibin = 0; ibin < gpar[0]->GetN(); ibin++)
		{
			gpar[ipar]->GetPoint(ibin, v2xpar[ipar][ibin], v2ypar[ipar][ibin]);
		}
	}
	for(Int_t ibin = 0; ibin < gpar[0]->GetN(); ibin++)
	{
		for(Int_t ipar = 0; ipar < 9; ipar++)
		{
			v2ysum[ibin] += v2ypar[ipar][ibin]*v2ypar[ipar][ibin];
		}
		v2ysum[ibin] = TMath::Sqrt(v2ysum[ibin]/9);
	}
//}}}

	c1->cd();
	hist->Draw();
	TGraphErrors* gsum = new TGraphErrors(gpar[0]->GetN(), v2xpar[0], v2ysum, Expar[0], Ev2ysum);
	gsum->SetName("gsum");
	gsum->SetMarkerStyle(20);
	gsum->SetMarkerSize(1.4);
	gsum->Draw("samepe");
	SetLine(1, 0, 0, 30, 0, 0, 3);
	c1->SaveAs(Form("SystPlot/MupT%s/Syst_v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_ParSum.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	fout->cd();
	gsum->Write();
	fout->Close();
}
