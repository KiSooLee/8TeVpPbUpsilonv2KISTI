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

void DrawObSigv2(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Int_t bkgN = 0, const Int_t NU = 1, const Int_t detacut = 1, const Bool_t isfine = true, TString version = "v13", TString MupT = "4")
{
	SetStyle();

//set fitting condition name{{{
	TString bkgF;
	if(bkgN == 0) bkgF = "exp";
	else if(bkgN == 1) bkgF = "pol2";
	else
	{
		cout << "out of background list" << endl;
		return;
	}
	TString Ups;
	if(NU == 1) Ups = "1S";
	else if(NU == 2) Ups = "12S";
	else if(NU == 3) Ups = "123S";
	else
	{
		cout << "No such generation in this analysis" << endl;
		return;
	}
	TString DEC;
	if(detacut == 1) DEC = "eta1";
	else if(detacut == 2) DEC = "eta1p5";
	else if(detacut == 3) DEC = "eta2";
	else
	{
		cout << "out of delta eta cut range list" << endl;
		return;
	}
	TString Fine;
	if(isfine == true) Fine = "fine";
	else Fine = "coarse";
//}}}

	TFile* fin;
	if(maxF == 2) fin = new TFile(Form("V2Dist/V2File/Observed_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_%s_MupT%s.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data(), version.Data(), MupT.Data()), "READ");
	else if(maxF == 3) fin = new TFile(Form("V2Dist/V2File/Observed_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_%s_MupT%s_tra.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data(), version.Data(), MupT.Data()), "READ");
	else
	{
		cout << "No such Fourier value in this analysis" << endl;
		return;
	}
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* htmp = new TH1D("htmp", ";p_{T};v_{2}", 10, 0, 30);
	FormTH1(htmp, 0);

	TGraphErrors *gin = (TGraphErrors*) fin->Get(Form("v2vspt"));
	TGraphErrors *g1 = (TGraphErrors*) gin->Clone("g1");
	FormGraph(g1, 0, 0, 1);

	c1->cd();
	htmp->SetMinimum(-0.02);
	htmp->SetMaximum(0.02);
	htmp->Draw();
	g1->Draw("samepe");
	if(maxF == 2) c1->SaveAs(Form("V2Dist/SigV2/V2Dist_obsig_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_%s_MupT%s.pdf", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data(), version.Data(), MupT.Data()));
	else if(maxF == 3) c1->SaveAs(Form("V2Dist/SigV2/V2Dist_obsig_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_%s_MupT%s_tra.pdf", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data(), version.Data(), MupT.Data()));
	else
	{
		cout << "No such Fourier value in this analysis" << endl;
		return;
	}
}
