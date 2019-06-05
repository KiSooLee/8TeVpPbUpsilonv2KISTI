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

void CompSigv2(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Int_t bkgN = 0, const Int_t NU = 1, const Int_t detacut = 1, const Bool_t isfine = true)
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

	TFile* fin1;
	TFile* fin2;
	TFile* fin3;
	TFile* fin4;
	if(maxF == 2)
	{
		fin1 = new TFile(Form("V2Dist/V2File/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_v16_MupT4.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()), "READ");
		fin2 = new TFile(Form("V2Dist/V2File/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_v16_MupT3p5.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()), "READ");
		fin3 = new TFile(Form("V2Dist/V2File/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_v17_MupT4.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()), "READ");
		fin4 = new TFile(Form("V2Dist/V2File/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_v17_MupT3p5.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()), "READ");
	}
	else if(maxF == 3)
	{
		fin1 = new TFile(Form("V2Dist/V2File/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_v16_MupT4_tra.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()), "READ");
		fin2 = new TFile(Form("V2Dist/V2File/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_v16_MupT3p5_tra.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()), "READ");
		fin3 = new TFile(Form("V2Dist/V2File/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_v17_MupT4_tra.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()), "READ");
		fin4 = new TFile(Form("V2Dist/V2File/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_v17_MupT3p5_tra.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()), "READ");
	}
	else
	{
		cout << "No such Fourier value in this analysis" << endl;
		return;
	}
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* htmp = new TH1D("htmp", ";p_{T};v_{2}", 10, 0, 30);
	FormTH1(htmp, 0);

	TGraphErrors *gin1 = (TGraphErrors*) fin1->Get(Form("v2vspt"));
	TGraphErrors *gin2 = (TGraphErrors*) fin2->Get(Form("v2vspt"));
	TGraphErrors *gin3 = (TGraphErrors*) fin3->Get(Form("v2vspt"));
	TGraphErrors *gin4 = (TGraphErrors*) fin4->Get(Form("v2vspt"));
	TGraphErrors *g1 = (TGraphErrors*) gin1->Clone("g1");
	TGraphErrors *g2 = (TGraphErrors*) gin2->Clone("g2");
	TGraphErrors *g3 = (TGraphErrors*) gin3->Clone("g3");
	TGraphErrors *g4 = (TGraphErrors*) gin4->Clone("g3");
	FormGraph(g1, 0, 0, 1);
	FormGraph(g2, 0, 0, 1);
	FormGraph(g3, 1, 1, 1);
	FormGraph(g4, 1, 1, 1);
	g2->SetMarkerStyle(24);
	g4->SetMarkerStyle(25);

	c1->cd();
	htmp->SetMinimum(-0.02);
	htmp->SetMaximum(0.02);
	htmp->Draw();
	g1->Draw("samepe");
	Double_t x2[10] = {0.};
	Double_t x3[10] = {0.};
	Double_t x4[10] = {0.};
	Double_t y2[10] = {0.};
	Double_t y3[10] = {0.};
	Double_t y4[10] = {0.};
	for(Int_t i = 0; i < g1->GetN(); i++)
	{
		g2->GetPoint(i, x2[i], y2[i]);
		g3->GetPoint(i, x3[i], y3[i]);
		g4->GetPoint(i, x4[i], y4[i]);
		g2->SetPoint(i, x2[i]+0.2, y2[i]);
		g3->SetPoint(i, x3[i]+0.5, y3[i]);
		g4->SetPoint(i, x4[i]+0.7, y4[i]);
	}
	g2->Draw("samepe");
	g3->Draw("samepe");
	g4->Draw("samepe");
	TLegend* leg1 = new TLegend(0.4, 0.2, 0.8, 0.4);
	FormLegend(leg1, 0.04);
	leg1->AddEntry(g1, "Coarse bin Mu pT > 4", "pl");
	leg1->AddEntry(g2, "Coarse bin Mu pT > 3.5", "pl");
	leg1->AddEntry(g3, "fine bin Mu pT > 4", "pl");
	leg1->AddEntry(g4, "fine bin Mu pT > 3.5", "pl");
	leg1->Draw();
	if(maxF == 2) c1->SaveAs(Form("V2Dist/SigV2/V2Comp_sig_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s.pdf", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()));
	else if(maxF == 3) c1->SaveAs(Form("V2Dist/SigV2/V2Comp_sig_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_tra.pdf", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data()));
	else
	{
		cout << "No such Fourier value in this analysis" << endl;
		return;
	}
}
