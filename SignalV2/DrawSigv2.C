//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TString.h>
#include <iostream>
#include <fstream>

#include "../Headers/Upsilon.h"
#include "../Headers/Style_Upv2.h"
//}}}

void DrawSigv2(const Bool_t isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 3, const Int_t bkgN = 0, const Int_t AwayN = 1, const Bool_t isfine = true, const TString version = "v13", const TString MupT = "4", const Bool_t Weight = true)
{
	SetStyle();

//set fitting condition name{{{
	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString bkgF;
	if(bkgN == 0) bkgF = "exp";
	else if(bkgN == 1) bkgF = "pol1";
	else if(bkgN == 2) bkgF = "pol2";
	else if(bkgN == 3) bkgF = "pol3";
	else if(bkgN == 4) bkgF = "erf";
	else
	{
		cout << "out of background list" << endl;
		return;
	}
	TString Away;
	if(AwayN == 1) Away = "1";
	else if(AwayN == 2) Away = "1p5";
	else if(AwayN == 3) Away = "2";
	else
	{
		cout << "out of delta eta cut range list" << endl;
		return;
	}
	TString Fine;
	if(isfine == true) Fine = "fine";
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

	TFile* fin = new TFile(Form("V2Dist/V2File/%s/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_Data_%s_MupT%s_weight%o%s.root", version.Data(), multMin, multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Away.Data(), Fine.Data(), version.Data(), MupT.Data(), Weight, Ffit.Data()), "READ");

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* htmp = new TH1D("htmp", ";p_{T};v_{2}", 10, 0, ptBinsArr[pt_narr-1]);
	FormTH1(htmp, 0);

	TGraphErrors *gin = (TGraphErrors*) fin->Get(Form("v2_1s_vs_pt"));
	TGraphErrors *g1 = (TGraphErrors*) gin->Clone("g1");
	FormGraph(g1, 0, 0, 1.2);

	c1->cd();
	//htmp->SetMinimum(-0.02);
	//htmp->SetMaximum(0.02);
	htmp->SetMinimum(-0.2);
	htmp->SetMaximum(0.2);
	htmp->Draw();
	g1->Draw("samepe");
	c1->SaveAs(Form("V2Dist/SigV2/V2Dist_sig_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_Data_%s_MupT%s_weight%o%s.pdf", multMin, multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Away.Data(), Fine.Data(), version.Data(), MupT.Data(), Weight, Ffit.Data()));
}
