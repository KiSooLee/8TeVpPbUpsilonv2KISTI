//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TBranch.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TVector.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <TSystem.h>
#include <TLegend.h>

#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooArgSet.h>

#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"

using namespace std;
using namespace RooFit;
//}}}

void Draw_pt_eta(const TString MupT = "3p5", const TString trkptversion = "v1")
{
	SetStyle();

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
	const TString ranges[4] = {"_tot", "_peak", "_lbkg", "_hbkg"};
//}}}

	const Double_t ptval[9] = {0, 2, 3, 4, 5, 6, 8, 10, 15};
	Double_t meanetahi[4][8] = {};
	Double_t erretahi[4][8] = {};
	Double_t meanetalow[4][8] = {};
	Double_t erretalow[4][8] = {};

	TFile* fin1 = new TFile(Form("Plots/Di-mu_eta_dist_mult_90-300_MupT%s.root", MupT.Data()), "READ");
	TFile* fin2 = new TFile(Form("Plots/Di-mu_eta_dist_mult_0-50_MupT%s.root", MupT.Data()), "READ");

	TCanvas* c1[4];
	TCanvas* c2[4];
	TCanvas* c3 = new TCanvas("c3", "", 0, 0, 600, 600);
	TCanvas* c4 = new TCanvas("c4", "", 0, 0, 600, 600);
	TH1D* heta_hi[4][8];
	TH1D* heta_low[4][8];
	TH1D* hpthi[4];
	TH1D* hptlow[4];
	TH1D* hratio[4];
	for(Int_t i = 0; i < 4; i++)
	{
		c1[i] = new TCanvas(Form("c1%s", ranges[i].Data()), "", 0, 0, 600, 600);
		c2[i] = new TCanvas(Form("c2%s", ranges[i].Data()), "", 0, 0, 600, 600);
		hpthi[i] = new TH1D(Form("hpthi%s", ranges[i].Data()), ";p_{T};|#eta|", 8, ptval);
		hptlow[i] = new TH1D(Form("hptlow%s", ranges[i].Data()), ";p_{T};|#eta|", 8, ptval);
		hratio[i] = new TH1D(Form("hratio%s", ranges[i].Data()), ";p_{T};|#eta| ratio", 8, ptval);
		FormTH1Marker(hpthi[i], 0, 0, 1.2);
		FormTH1Marker(hptlow[i], 1, 0, 1.2);
	}

	for(Int_t i = 0; i < 4; i++)
	{
		for(Int_t j = 0; j < 8; j++)
		{
			heta_hi[i][j] = (TH1D*) fin1->Get(Form("heta%s_%d", ranges[i].Data(), j));
			heta_low[i][j] = (TH1D*) fin2->Get(Form("heta%s_%d", ranges[i].Data(), j));
			meanetahi[i][j] = heta_hi[i][j]->GetMean();
			erretahi[i][j] = heta_hi[i][j]->GetMeanError();
			meanetalow[i][j] = heta_low[i][j]->GetMean();
			erretalow[i][j] = heta_low[i][j]->GetMeanError();
			hpthi[i]->SetBinContent(j+1, meanetahi[i][j]);
			hpthi[i]->SetBinError(j+1, erretahi[i][j]);
			hptlow[i]->SetBinContent(j+1, meanetalow[i][j]);
			hptlow[i]->SetBinError(j+1, erretalow[i][j]);
		}
		TLegend* leg1 = new TLegend(0.50, 0.72, 0.95, 0.87);
		FormLegend(leg1, 0.04);
		c1[i]->cd();
		hpthi[i]->SetMaximum(2.5);
		hpthi[i]->SetMinimum(0.0);
		hpthi[i]->GetYaxis()->SetTitle("<#eta>");
		hpthi[i]->Draw("pe");
		hptlow[i]->Draw("pesame");
		leg1->AddEntry(hpthi[i], "90 #leq mult < 300", "pe");
		leg1->AddEntry(hptlow[i], "0 #leq mult < 50", "pe");
		leg1->Draw();
		c1[i]->SaveAs(Form("Plots/Di-mu_eta_vs_pt_dist_mult_90-300_0-50_comp_MupT%s%s.pdf", MupT.Data(), ranges[i].Data()));

		c2[i]->cd();
		hratio[i] = (TH1D*) hpthi[i]->Clone(Form("hratio%s", ranges[i].Data()));
		hratio[i]->Divide(hptlow[i]);
		hratio[i]->SetMaximum(1.1);
		hratio[i]->SetMinimum(0.0);
		hratio[i]->GetYaxis()->SetTitle("<#eta>_{high}/<#eta>_{low}");
		hratio[i]->Draw("pe");
		SetLine(2, 0, 1, 15, 1, 0, 3);
		c2[i]->SaveAs(Form("Plots/Di-mu_eta_vs_pt_dist_mult_90-300_0-50_ratio_MupT%s%s.pdf", MupT.Data(), ranges[i].Data()));
	}
	c3->cd();
	TLegend* leg2 = new TLegend(0.50, 0.72, 0.95, 0.87);
	FormLegend(leg2, 0.04);
	for(Int_t i = 0; i < 4; i++)
	{
		FormTH1Marker(hpthi[i], i, 1, 1.2);
		if(i == 0)
		{
			hpthi[i]->SetMaximum(2.0);
			hpthi[i]->SetMinimum(1.0);
			hpthi[i]->Draw("pe");
		}
		else hpthi[i]->Draw("pesame");
		leg2->AddEntry(hpthi[i], Form("%s", ranges[i].Data()), "pe");
	}
	leg2->Draw();
	c3->SaveAs(Form("Plots/Di-mu_eta_vs_pt_dist_mult_90-300_MupT%s.pdf", MupT.Data()));

	c4->cd();
	TLegend* leg3 = new TLegend(0.50, 0.72, 0.95, 0.87);
	FormLegend(leg3, 0.04);
	for(Int_t i = 0; i < 4; i++)
	{
		FormTH1Marker(hptlow[i], i, 1, 1.2);
		if(i == 0)
		{
			hptlow[i]->SetMaximum(2.0);
			hptlow[i]->SetMinimum(1.0);
			hptlow[i]->Draw("pe");
		}
		else hptlow[i]->Draw("pesame");
		leg3->AddEntry(hptlow[i], Form("%s", ranges[i].Data()), "pe");
	}
	leg3->Draw();
	c4->SaveAs(Form("Plots/Di-mu_eta_vs_pt_dist_mult_0-50_MupT%s.pdf", MupT.Data()));
}
