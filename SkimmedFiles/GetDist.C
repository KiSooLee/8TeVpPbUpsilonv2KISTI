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

//Get data{{{
	TFile* fin = new TFile(Form("Skim_OniaTree_Data_PADoubleMuon_weight0_MupT%s.root", MupT.Data()), "READ");
	TTree* tin = (TTree*) fin->Get("UpsilonTree");
//}}}

//get variables{{{
	Int_t mult;
	Double_t mass;
	Double_t pt;
	Double_t y;
	Double_t weight;

	TBranch* b_mult;
	TBranch* b_mass;
	TBranch* b_pt;
	TBranch* b_y;
	TBranch* b_weight;

	tin->SetBranchAddress("mult", &mult, &b_mult);
	tin->SetBranchAddress("mass", &mass, &b_mass);
	tin->SetBranchAddress("pt", &pt, &b_pt);
	tin->SetBranchAddress("y", &y, &b_y);
	tin->SetBranchAddress("weight", &weight, &b_weight);
//}}}

//Set Canvas and Hist{{{
	TCanvas* cpt = new TCanvas("cpt", "", 0, 0, 600, 600);
	TCanvas* cpt_log = new TCanvas("cpt_log", "", 0, 0, 600, 600);
	TCanvas* cy = new TCanvas("cy", "", 0, 0, 600, 600);
	TCanvas* cmult = new TCanvas("cmult", "", 0, 0, 600, 600);
	TH1D* hpt = new TH1D("hpt", ";pT (GeV/c);Counts", 60, 0, 30);
	TH1D* hy = new TH1D("hy", ";y;Counts", 50, -2.4, 2.4);
	TH1D* hmult = new TH1D("hmult", ";multiplicity;Counts", 100, 0, 300);
	TH1D* hmult_hi = new TH1D("hmult_hi", ";multiplicity;Counts", 100, 0, 300);
	FormTH1Marker(hpt, 0, 0, 1.3);
	FormTH1Marker(hy, 0, 0, 1.3);
	FormTH1Marker(hmult, 0, 0, 1.3);
	FormTH1Fill(hmult_hi, 2, 0);
	hmult_hi->SetFillStyle(3004);
//}}}

	const Int_t Nevt = tin->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin->GetEntry(ievt);

		if(9 <= mass && mass < 10)
		{
			hpt->Fill(pt, weight);
			hy->Fill(y, weight);
			hmult->Fill(mult, weight);
			//if(mult > 110) hmult_hi->Fill(mult, weight);
			if(mult > 90) hmult_hi->Fill(mult, weight);
		}
	}
	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);

	cpt->cd();
	hpt->Draw("pe");
	CMSP(0.12, 0.92);
	lumiText(0.56, 0.92);
	lt1->DrawLatex(0.57,0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.57,0.85, "9 #leq m_{#mu+#mu-} < 10 GeV/c^{2}");
	cpt->SaveAs(Form("MassDist/Dimu-dist_pt_MupT%s.pdf", MupT.Data()));
	cpt->SaveAs(Form("MassDist/Dimu-dist_pt_MupT%s.png", MupT.Data()));
	cpt_log->cd();
	cpt_log->SetLogy();
	hpt->Draw("pe");
	CMSP(0.12, 0.92);
	lumiText(0.56, 0.92);
	lt1->DrawLatex(0.57,0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.57,0.85, "9 #leq m_{#mu+#mu-} < 10 GeV/c^{2}");
	cpt_log->SaveAs(Form("MassDist/Dimu-dist_pt_log_MupT%s.pdf", MupT.Data()));
	cpt_log->SaveAs(Form("MassDist/Dimu-dist_pt_log_MupT%s.png", MupT.Data()));

	cy->cd();
	hy->Draw("pe");
	CMSP(0.12, 0.92);
	lumiText(0.56, 0.92);
	lt1->DrawLatex(0.57,0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.57,0.85, "9 #leq m_{#mu+#mu-} < 10 GeV/c^{2}");
	cy->SaveAs(Form("MassDist/Dimu-dist_y_MupT%s.pdf", MupT.Data()));
	cy->SaveAs(Form("MassDist/Dimu-dist_y_MupT%s.png", MupT.Data()));

	cmult->cd();
	cmult->SetLogy();
	hmult->Draw("pe");
	hmult_hi->Draw("histsame");
	CMSP(0.12, 0.92);
	lumiText(0.56, 0.92);
	lt1->DrawLatex(0.57,0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.57,0.85, "9 #leq m_{#mu+#mu-} < 10 GeV/c^{2}");
	cmult->SaveAs(Form("MassDist/Dimu-dist_mult90_MupT%s.pdf", MupT.Data()));
	cmult->SaveAs(Form("MassDist/Dimu-dist_mult90_MupT%s.png", MupT.Data()));

	cout << "Dimu 110: " << hmult->Integral(37, 100) << endl;
	cout << "Dimu 90: " << hmult->Integral(30, 100) << endl;
	cout << "HM: " << hmult->Integral(40, 100)*10/7 << endl;
}
