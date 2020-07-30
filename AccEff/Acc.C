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

#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooArgSet.h>

#include "../Style_Upv2.h"
#include "../Upsilon.h"

using namespace std;
using namespace RooFit;
//}}}

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut);

void Acc(const Int_t Generation = 1, const TString MupT = "3p5", const Bool_t isRW = true)
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
//}}}

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/Plots";

	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//Get files{{{
	TChain* tin_tmp = new TChain("Ana");
	for(Int_t i = 0; i < 25; i++)
	{
		tin_tmp->Add(Form("root://cms-xrdr.sdfarm.kr:2094///xrd/store/user/kilee/MB/Pbp_Up1S_GENonly_multiplicity_v1_20200704/Upsilon1S_pPb-Bst_8p16-Pythia8/Pbp_Up1S_GENonly_multiplicity_v1_20200704/200703_152703/0000/mcStudy_Up1S_816TeV_%d.root", i+1));
	}
	TTree* tin = tin_tmp->CloneTree();
	tin_tmp->Reset();
	TFile* freweight = new TFile(Form("../SkimmedFiles/Yield/Kinematic_dist_comp_%dS_v57_MupT%s.root", Generation, MupT.Data()), "READ");
	TF1* funcrw = (TF1*) freweight->Get("fit1");
//}}}

//Define histogram{{{
	const Int_t npt = 13;
	Double_t ptBin[npt+1] = {0,1,2,3,4,5,6,7,8,9,10,15,20,30};

	TH1D* hGen0016 = new TH1D("hGen0016", ";p_{T}^{#varUpsilon} GeV/c;Entries", npt, ptBin);
	TH1D* hGen1618 = new TH1D("hGen1618", ";p_{T}^{#varUpsilon} GeV/c;Entries", npt, ptBin);
	TH1D* hGen1821 = new TH1D("hGen1821", ";p_{T}^{#varUpsilon} GeV/c;Entries", npt, ptBin);
	TH1D* hGen2124 = new TH1D("hGen2124", ";p_{T}^{#varUpsilon} GeV/c;Entries", npt, ptBin);

	TH1D* hAccGen0016 = new TH1D("hAccGen0016", ";p_{T}^{#varUpsilon} GeV/c;Entries", npt, ptBin);
	TH1D* hAccGen1618 = new TH1D("hAccGen1618", ";p_{T}^{#varUpsilon} GeV/c;Entries", npt, ptBin);
	TH1D* hAccGen1821 = new TH1D("hAccGen1821", ";p_{T}^{#varUpsilon} GeV/c;Entries", npt, ptBin);
	TH1D* hAccGen2124 = new TH1D("hAccGen2124", ";p_{T}^{#varUpsilon} GeV/c;Entries", npt, ptBin);

	TH1D* hGenPt = new TH1D("hGenPt", ";p_{T}^{#varUpsilon} GeV/c;Entries", 30, 0, 30);
	TH1D* hAccGenPt = new TH1D("hAccGenPt", ";p_{T}^{#varUpsilon} GeV/c;Entries", 30, 0, 30);
	TH1D* hGeny = new TH1D("hGeny", ";y;Entries", 48, -2.4, 2.4);
	TH1D* hAccGeny = new TH1D("hAccGeny", ";y;Entries", 48, -2.4, 2.4);

	FormTH1Marker(hGen0016, 0, 0, 1.2);
	FormTH1Marker(hGen1618, 0, 0, 1.2);
	FormTH1Marker(hGen1821, 0, 0, 1.2);
	FormTH1Marker(hGen2124, 0, 0, 1.2);
	FormTH1Marker(hAccGen0016, 0, 0, 1.2);
	FormTH1Marker(hAccGen1618, 0, 0, 1.2);
	FormTH1Marker(hAccGen1821, 0, 0, 1.2);
	FormTH1Marker(hAccGen2124, 0, 0, 1.2);
	FormTH1Marker(hGenPt, 0, 0, 1.2);
	FormTH1Marker(hAccGenPt, 0, 0, 1.2);
	FormTH1Marker(hGeny, 0, 0, 1.2);
	FormTH1Marker(hAccGeny, 0, 0, 1.2);
//}}}

//Tree variables{{{
	double mass = 0.0, pt = 0.0, phi = 0.0, eta = 0.0, rap = 0.0;
	double pt1 = 0.0, phi1 = 0.0, eta1 = 0.0, eng1 = 0.0;
	double pt2 = 0.0, phi2 = 0.0, eta2 = 0.0, eng2 = 0.0;

	TBranch* b_mass;
	TBranch* b_pt;
	TBranch* b_phi;
	TBranch* b_eta;
	TBranch* b_rap;
	TBranch* b_pt1;
	TBranch* b_phi1;
	TBranch* b_eta1;
	TBranch* b_eng1;
	TBranch* b_pt2;
	TBranch* b_phi2;
	TBranch* b_eta2;
	TBranch* b_eng2;

	tin->SetBranchAddress("mass", &mass,   &b_mass);
	tin->SetBranchAddress("pt",   &pt,     &b_pt);
	tin->SetBranchAddress("phi",  &phi,    &b_phi);
	tin->SetBranchAddress("eta",  &eta,    &b_eta);
	tin->SetBranchAddress("rap",  &b_rap,  &b_rap);
	tin->SetBranchAddress("pt1",  &pt1,    &b_pt1);
	tin->SetBranchAddress("phi1", &phi1,   &b_phi1);
	tin->SetBranchAddress("eta1", &eta1,   &b_eta1);
	tin->SetBranchAddress("eng1", &b_rap1, &b_rap1);
	tin->SetBranchAddress("pt2",  &pt2,    &b_pt2);
	tin->SetBranchAddress("phi2", &phi2,   &b_phi2);
	tin->SetBranchAddress("eta2", &eta2,   &b_eta2);
	tin->SetBranchAddress("eng2", &b_rap2, &b_rap2);
//}}}

	const Int_t Nevt = tin->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << "[" << Form("%.1f", ( (double)ievt/(double)Nevt)*100 ) << " %]" << endl;
		tin->GetEntry(ievt);

		Double_t reweight = 1.;
		if(isRW) reweight = reweight = funcrw->Eval(pt);

		if( fabs(rap) <= 2.4 && pt >= 0.0 && pt <= 30.0)
		{
//Fill total{{{
			hGenPt->Fill(pt, reweight);
			hGeny->Fill(rap, reweight);
			if( fbas(rap) <= 1.6) hGen0016->Fill(pt, reweight);
			if( fbas(rap) > 1.6 && fabs(rap) <= 1.8 ) hGen0016->Fill(pt, reweight);
			if( fbas(rap) > 1.8 && fabs(rap) <= 2.1 ) hGen0016->Fill(pt, reweight);
			if( fbas(rap) > 2.1 && fabs(rap) <= 2.4 ) hGen0016->Fill(pt, reweight);
//}}}

			if( InAcc(pt1, eta1) && InAcc(pt2, eta2) );
			{
//Fill within acceptance{{{
				hAccGenPt->Fill(pt, reweight);
				hAccGeny->Fill(rap, reweight);
				if( fbas(rap) <= 1.6) hAccGen0016->Fill(pt, reweight);
				if( fbas(rap) > 1.6 && fabs(rap) <= 1.8 ) hAccGen0016->Fill(pt, reweight);
				if( fbas(rap) > 1.8 && fabs(rap) <= 2.1 ) hAccGen0016->Fill(pt, reweight);
				if( fbas(rap) > 2.1 && fabs(rap) <= 2.4 ) hAccGen0016->Fill(pt, reweight);
//}}}
			}
		}
	}

//Draw{{{
	TCanvas* cGenPt = new TCanvas("cGenPt", "", 0, 0, 600, 600);
	cGenPt->cd();
	hGenPt->Draw("pe");
	cGenPt->SaveAs(Form("Plots/GenPt_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, MupT.Data()));

	TCanvas* cAccGenPt = new TCanvas("cAccGenPt", "", 0, 0, 600, 600);
	cAccGenPt->cd();
	hAccGenPt->Draw("pe");
	cAccGenPt->SaveAs(Form("Plots/GenPt_inAcc_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, MupT.Data()));

	TH1D* hAccPt = (TH1D*) hAccGenPt->Clone("hAccPt");
	hAccPt->Divide(hGenPt);
	hAccPt->GetYaxis()->SetTitle("Acc.");

	TCanvas* cAccPt = new TCanvas("cAccPt", "", 0, 0, 600, 600);
	cAccPt->cd();
	hAccPt->Draw("pe");
	cAccPt->SaveAs(Form("Plots/AccPt_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, MupT.Data()));

	TCanvas* cGeny = new TCanvas("cGeny", "", 0, 0, 600, 600);
	cGeny->cd();
	hGeny->Draw("pe");
	cGeny->SaveAs(Form("Plots/Geny_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, MupT.Data()));

	TCanvas* cAccGeny = new TCanvas("cAccGeny", "", 0, 0, 600, 600);
	cAccGeny->cd();
	hAccGeny->Draw("pe");
	cAccGeny->SaveAs(Form("Plots/Geny_inAcc_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, MupT.Data()));

	TH1D* hAccy = (TH1D*) hAccGeny->Clone("hAccy");
	hAccy->Divide(hGeny);
	hAccy->GetYaxis()->SetTitle("Acc.");

	TCanvas* cAccy = new TCanvas("cAccy", "", 0, 0, 600, 600);
	cAccy->cd();
	hAccy->Draw("pe");
	cAccy->SaveAs(Form("Plots/Accy_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, MupT.Data()));
//}}}

	TH1D* hAcc0016 = (TH1D*) hAccGen0016->Clone("hAcc0016");
	TH1D* hAcc1618 = (TH1D*) hAccGen1618->Clone("hAcc1618");
	TH1D* hAcc1821 = (TH1D*) hAccGen1821->Clone("hAcc1821");
	TH1D* hAcc2124 = (TH1D*) hAccGen2124->Clone("hAcc2124");
	hAcc0016->Divide(hGen0016);
	hAcc1618->Divide(hGen1618);
	hAcc1821->Divide(hGen1821);
	hAcc2124->Divide(hGen2124);
	hAcc0016->GetYaxis()->SetTitle("Acc.");
	hAcc1618->GetYaxis()->SetTitle("Acc.");
	hAcc1821->GetYaxis()->SetTitle("Acc.");
	hAcc2124->GetYaxis()->SetTitle("Acc.");

//save{{{
	TFile* fout = new TFile(Form("Plots/AccPlots_Upsilon_%dS_RW%o_MupT%s.root", Generation, isRW, MupT.Data()), "RECREATE");
	fout->cd();
	hGenPt->Write();
	hGeny->Write();
	hAccGenPt->Write();
	hAccGeny->Write();
	hAccPt->Write();
	hAccy->Write();
	hGen0016-Write();
	hGen1618-Write();
	hGen1821-Write();
	hGen2124-Write();
	hAccGen0016-Write();
	hAccGen1618-Write();
	hAccGen1821-Write();
	hAccGen2124-Write();
	hAcc0016-Write();
	hAcc1618-Write();
	hAcc1821-Write();
	hAcc2124-Write();
	fout->Close();
//}}}
}

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut)
{
	return( TMath::Abs(muEta) < 2.4 && muPt >= MupTCut);
}
