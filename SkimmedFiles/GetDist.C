//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaveText.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TParameter.h>
#include <TSystem.h>
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
//}}}

void GetDist(TString MupT = "3p5")
{
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString massDIR = mainDIR + "/MassDist";
	void * dirpM = gSystem->OpenDirectory(massDIR.Data());
	if(dirpM) gSystem->FreeDirectory(dirpM);
	else gSystem->mkdir(massDIR.Data(), kTRUE);
//}}}

//Get data{{{
	TFile* fin = new TFile(Form("Skim_OniaTree_Data_PADoubleMuon_MupT%s.root", MupT.Data()), "READ");
	TTree* tin = (TTree*) fin->Get("UpsilonTree");
//}}}

//get variables{{{
	Int_t mult;
	Double_t mass;
	Double_t pt;
	Double_t y;

	TBranch* b_mult;
	TBranch* b_mass;
	TBranch* b_pt;
	TBranch* b_y;

	tin->SetBranchAddress("mult", &mult, &b_mult);
	tin->SetBranchAddress("mass", &mass, &b_mass);
	tin->SetBranchAddress("pt", &pt, &b_pt);
	tin->SetBranchAddress("y", &y, &b_y);
//}}}

//Set Canvas and Hist{{{
	TCanvas* cpt = new TCanvas("cpt", "", 0, 0, 600, 600);
	TCanvas* cy = new TCanvas("cy", "", 0, 0, 600, 600);
	TCanvas* cmult = new TCanvas("cmult", "", 0, 0, 600, 600);
	TH1D* hpt = new TH1D("hpt", ";pT (GeV/c);Counts", 60, 0, 30);
	TH1D* hy = new TH1D("hy", ";y;Counts", 50, -2.4, 2.4);
	TH1D* hmult = new TH1D("hmult", ";multiplicity;Counts", 100, 0, 300);
	FormTH1Fill(hpt, 2, 4);
	FormTH1Fill(hy, 2, 4);
	FormTH1Fill(hmult, 2, 4);
//}}}

	const Int_t Nevt = tin->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin->GetEntry(ievt);

		if(9 <= mass && mass < 10)
		{
			hpt->Fill(pt);
			hy->Fill(y);
			hmult->Fill(mult);
		}
	}
	cpt->cd();
	hpt->SetFillStyle(2003);
	hpt->Draw("hist");
	cpt->SaveAs(Form("MassDist/Dimu-dist_pt_MupT%s.pdf", MupT.Data()));
	cpt->SaveAs(Form("MassDist/Dimu-dist_pt_MupT%s.png", MupT.Data()));
	cy->cd();
	hy->SetFillStyle(2003);
	hy->Draw("hist");
	cy->SaveAs(Form("MassDist/Dimu-dist_y_MupT%s.pdf", MupT.Data()));
	cy->SaveAs(Form("MassDist/Dimu-dist_y_MupT%s.png", MupT.Data()));
	cmult->cd();
	hmult->SetFillStyle(2003);
	hmult->Draw("hist");
	cmult->SaveAs(Form("MassDist/Dimu-dist_mult_MupT%s.pdf", MupT.Data()));
	cmult->SaveAs(Form("MassDist/Dimu-dist_mult_MupT%s.png", MupT.Data()));
}
