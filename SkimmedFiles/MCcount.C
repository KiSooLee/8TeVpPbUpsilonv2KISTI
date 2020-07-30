//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaveText.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TParameter.h>
#include <TSystem.h>
#include <RooRealVar.h>
#include <RooArgSet.h>
#include <RooDataSet.h>
#include <RooWorkspace.h>
#include <RooPlot.h>
#include <RooHist.h>
#include <RooGaussian.h>
#include <RooCBShape.h>
#include <RooChebychev.h>
#include <RooPolynomial.h>
#include <RooExponential.h>
#include <RooGenericPdf.h>
#include <RooAddPdf.h>
#include <RooFitResult.h>
#include <RooFormulaVar.h>
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
#include "../Headers/tnp_weight_lowptpPb.h"
using namespace std;
using namespace RooFit;
//}}}

void MCcount()
{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString yieldDIR = mainDIR + "/Yield";
	void * dirpY = gSystem->OpenDirectory(yieldDIR.Data());
	if(dirpY) gSystem->FreeDirectory(dirpY);
	else gSystem->mkdir(yieldDIR.Data(), kTRUE);

	TFile* fout = new TFile(Form("Yield/Yield_count_MC_MupT3p5_test.root"), "RECREATE");

	TFile* fin = new TFile(Form("Skim_OniaTree_MC_PADoubleMuon_weight0_MupT3p5.root"), "READ");
	TTree* tin = (TTree*) fin->Get("UpsilonTree");

	Double_t pt;
	Double_t mupl_pt;
	Double_t mumi_pt;
	Double_t mupl_eta;
	Double_t mumi_eta;
	TBranch* b_pt;
	TBranch* b_mupl_pt;
	TBranch* b_mupl_eta;
	TBranch* b_mumi_pt;
	TBranch* b_mumi_eta;
	tin->SetBranchAddress("pt", &pt, &b_pt);
	tin->SetBranchAddress("mupl_pt", &mupl_pt, &b_mupl_pt);
	tin->SetBranchAddress("mupl_eta", &mupl_eta, &b_mupl_eta);
	tin->SetBranchAddress("mumi_pt", &mumi_pt, &b_mumi_pt);
	tin->SetBranchAddress("mumi_eta", &mumi_eta, &b_mumi_eta);

	TH1D* h1 = new TH1D("h1", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
	for(Int_t ievt = 0; ievt < tin->GetEntries(); ievt++)
	{
		tin->GetEntry(ievt);
		Double_t mupl_muid_tnp = tnp_weight_muid_ppb(mupl_pt, mupl_eta, 0);
		Double_t mupl_trk_tnp = tnp_weight_trk_ppb(mupl_eta, 0);
		Double_t mupl_trg_tnp = tnp_weight_trg_ppb(mupl_pt, mupl_eta, 3, 0);
		Double_t mumi_muid_tnp = tnp_weight_muid_ppb(mumi_pt, mumi_eta, 0);
		Double_t mumi_trk_tnp = tnp_weight_trk_ppb(mumi_eta, 0);
		Double_t mumi_trg_tnp = tnp_weight_trg_ppb(mumi_pt, mumi_eta, 3, 0);
		Double_t mupl_tnp = mupl_muid_tnp*mupl_trk_tnp*mupl_trg_tnp;
		Double_t mumi_tnp = mumi_muid_tnp*mumi_trk_tnp*mumi_trg_tnp;
		h1->Fill(pt/(mupl_tnp*mumi_tnp));
	}

	fout->cd();
	h1->Write();
	fout->Close();
}
