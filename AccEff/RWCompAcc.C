//Headers{{{
#include <TROOT.h>
#include <TSystem.h>
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
#include <TCanvas.h>
#include <TPad.h>
#include <TH1.h>
#include <TLatex.h>
#include <TLegend.h>

#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"

using namespace std;
using namespace RooFit;
//}}}

void RWCompAcc(const Int_t Generation = 1, const TString MupT = "3p5")
{
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/Plots";

	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

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

	TFile* fRW0 = new TFile(Form("Plots/AccPlots_Upsilon_%dS_RW0_MupT%s.root", Generation, MupT.Data()), "READ");
	TFile* fRW1 = new TFile(Form("Plots/AccPlots_Upsilon_%dS_RW1_MupT%s.root", Generation, MupT.Data()), "READ");
	TH1D* hRW0 = (TH1D*) fRW0->Get("hAccPt");
	TH1D* hRW1 = (TH1D*) fRW1->Get("hAccPt");
	FormTH1Marker(hRW, 0, 0, 2.0);
	FormTH1Marker(hRW, 1, 0, 2.0);

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 800);
	c1->cd();
	TPad* pad_comp = new TPad("pad_comp", "pad_comp", 0, 0.25, 0.98, 1.0);
	TPad* pad_ratio = new TPad("pad_ratio", "pad_ratio", 0, 0.05, 0.98, 0.25);
	pad_comp->SetBottomMargin(0.001);
	pad_ratio->SetBottomMargin(0.18);
	pad_ratio->SetTopMargin(0.001);
	pad_comp->Draw();
	pad_ratio->Draw();

	pad_comp->cd();
	hRW0->SetMaximum(1.2);
	hRW0->SetMinimum(0.0);
	hRW0->Draw("pe");
	hRW1->Draw("pesame");
	TLegend* leg1 = new TLegend(0.5, 0.5, 0.9, 0.8);
	FormLegend(leg1, 0.045);
	leg1->AddEntry(hRW0, "Non-weighted", "pe");
	leg1->AddEntry(hRW1, "dN/dp_{T} weighted", "pe");
	leg1->Draw();
	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.045);
	lt1->DrawLatex(0.7, 0.82, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.7, 0.75, Form("|#eta^{#mu}| < 2.4"));

	pad_ratio->cd();
	TH1D* hratio = (TH1D*) hRW1->Clone("hratio");
	hratio->Divide(hRW0);
	hratio->GetYaxis()->SetTitle("Ratio");
	hratio->GetYaxis()->SetTitleSize(0.15);
	hratio->GetYaxis()->SetTitleOffset(0.2);
	hratio->GetXaxis()->SetTitleSize(0.1);
	hratio->GetXaxis()->SetTitleOffset(0.8);
	hratio->Draw("pe");
	lt1->DrawLatex(0.4, 0.82, "Acc.dN/dp_{T} weighted/ Acc. non-weighted");
	SetLine(2, 0, 1, 30, 1, 0, 3);
	c1->SaveAs(Form("Plots/Acc_comp_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, isRW, MupT.Data()));
}
