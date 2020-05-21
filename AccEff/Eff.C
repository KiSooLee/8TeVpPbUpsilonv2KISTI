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

#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"

using namespace std;
using namespace RooFit;
//}}}

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut);

void Eff(const TString MupT = "3p5", const Int_t Generation = 1)
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
	TChain* tin = new TChain("hionia/myTree");
	TString fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_Pbp_MC_%dS_20190613.root", Generation);
	TString fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb_MC_%dS_20190613.root", Generation);
	tin->Add(fname1.Data());
	const Int_t Nevtcut = tin->GetEntries();
	tin->Add(fname2.Data());
//}}}

//binning{{{
	const Int_t Npt1 = 14;
	const Int_t Npt2 = 8;
	const Double_t ptbins1[Npt1] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9.,
											10., 15., 20., 30.};
	const Double_t ptbins2[Npt2] = {0., 2., 4., 6., 8., 10., 15., 30.};
	const Int_t Ny = 5;
	const Double_t ybins[Ny] = {0., 1.6, 1.8, 2.1, 2.4};
//}}}

//Define canvas and histogram{{{
	TCanvas* cyDenintgr = new TCanvas("cyDenintgr", "", 0, 0, 600, 600);
	TCanvas* cyNumintgr = new TCanvas("cyNumintgr", "", 0, 0, 600, 600);
	TCanvas* cyEffintgr = new TCanvas("cyEffintgr", "", 0, 0, 600, 600);
	TCanvas* cptDenintgr = new TCanvas("cptDenintgr", "", 0, 0, 600, 600);
	TCanvas* cptNumintgr = new TCanvas("cptNumintgr", "", 0, 0, 600, 600);
	TCanvas* cptEffintgr = new TCanvas("cptEffintgr", "", 0, 0, 600, 600);
	TCanvas* cDen[Ny-1];
	TCanvas* cNum[Ny-1];
	TCanvas* cEff[Ny-1];
	TH1D* hyDenintgr = new TH1D("hyDenintgr", ";y^{#varUpsilon};Entries", 250, -2.5, 2.5);
	TH1D* hyNumintgr = new TH1D("hyNumintgr", ";y^{#varUpsilon};Entries", 250, -2.5, 2.5);
	TH1D* hptDenintgr = new TH1D("hptDenintgr", ";p_{T}y^{#varUpsilon};Entries", 300, 0, 30);
	TH1D* hptNumintgr = new TH1D("hptNumintgr", ";p_{T}y^{#varUpsilon};Entries", 300, 0, 30);
	FormTH1Marker(hyDenintgr, 0, 0, 1.2);
	FormTH1Marker(hyNumintgr, 0, 0, 1.2);
	FormTH1Marker(hptDenintgr, 0, 0, 1.2);
	FormTH1Marker(hptNumintgr, 0, 0, 1.2);
	TH1D* hyEffintgr;
	TH1D* hptEffintgr;
	TH1D* hDen[Ny-1];
	TH1D* hNum[Ny-1];
	TH1D* hEff[Ny-1];
	for(Int_t iy = 0; iy < Ny-1; iy++)
	{
		cDen[iy] = new TCanvas(Form("cDen_%d", iy), "", 0, 0, 600, 600);
		cNum[iy] = new TCanvas(Form("cNum_%d", iy), "", 0, 0, 600, 600);
		cEff[iy] = new TCanvas(Form("cEff_%d", iy), "", 0, 0, 600, 600);
		if(iy == 0)
		{
			hDen[iy] = new TH1D(Form("hDen_%d", iy), ";p_{T}^{#varUpsilon};Entries", Npt1-1, ptbins1);
			hNum[iy] = new TH1D(Form("hNum_%d", iy), ";p_{T}^{#varUpsilon};Entries", Npt1-1, ptbins1);
		}
		else
		{
			hDen[iy] = new TH1D(Form("hDen_%d", iy), ";p_{T}^{#varUpsilon};Entries", Npt2-1, ptbins2);
			hNum[iy] = new TH1D(Form("hNum_%d", iy), ";p_{T}^{#varUpsilon};Entries", Npt2-1, ptbins2);
		}
		FormTH1Marker(hDen[iy], 0, 0, 1.2);
		FormTH1Marker(hNum[iy], 0, 0, 1.2);
	}
//}}}

	const Int_t MaxQQ = 250;

//Tree variables{{{
	ULong64_t HLTriggers;
	Int_t Reco_QQ_size;
	Int_t Reco_QQ_type[MaxQQ];
	Int_t Reco_QQ_sign[MaxQQ];
	Float_t Reco_QQ_VtxProb[MaxQQ];
	ULong64_t Reco_QQ_trig[MaxQQ];
	Bool_t Reco_QQ_mupl_TMOneStaTight[MaxQQ];
	Bool_t Reco_QQ_mumi_TMOneStaTight[MaxQQ];
	Bool_t Reco_QQ_mupl_highPurity[MaxQQ];
	Bool_t Reco_QQ_mumi_highPurity[MaxQQ];
	Int_t Reco_QQ_mupl_nTrkWMea[MaxQQ];
	Int_t Reco_QQ_mumi_nTrkWMea[MaxQQ];
	Int_t Reco_QQ_mupl_nPixWMea[MaxQQ];
	Int_t Reco_QQ_mumi_nPixWMea[MaxQQ];
	Float_t Reco_QQ_mupl_dxy[MaxQQ];
	Float_t Reco_QQ_mumi_dxy[MaxQQ];
	Float_t Reco_QQ_mupl_dz[MaxQQ];
	Float_t Reco_QQ_mumi_dz[MaxQQ];
	TClonesArray* Reco_QQ_4mom;
	TClonesArray* Reco_QQ_mupl_4mom;
	TClonesArray* Reco_QQ_mumi_4mom;
	Reco_QQ_4mom = 0;
	Reco_QQ_mupl_4mom = 0;
	Reco_QQ_mumi_4mom = 0;

	Int_t Gen_QQ_size;
	TClonesArray* Gen_QQ_4mom;
	TClonesArray* Gen_QQ_mupl_4mom;
	TClonesArray* Gen_QQ_mumi_4mom;
	Gen_QQ_4mom = 0;
	Gen_QQ_mupl_4mom = 0;
	Gen_QQ_mumi_4mom = 0;
//}}}

//Branch{{{
	TBranch* b_HLTriggers;
	TBranch* b_Reco_QQ_size;
	TBranch* b_Reco_QQ_type;
	TBranch* b_Reco_QQ_sign;
	TBranch* b_Reco_QQ_VtxProb;
	TBranch* b_Reco_QQ_trig;
	TBranch* b_Reco_QQ_mupl_TMOneStaTight;
	TBranch* b_Reco_QQ_mumi_TMOneStaTight;
	TBranch* b_Reco_QQ_mupl_highPurity;
	TBranch* b_Reco_QQ_mumi_highPurity;
	TBranch* b_Reco_QQ_mupl_nTrkWMea;
	TBranch* b_Reco_QQ_mumi_nTrkWMea;
	TBranch* b_Reco_QQ_mupl_nPixWMea;
	TBranch* b_Reco_QQ_mumi_nPixWMea;
	TBranch* b_Reco_QQ_mupl_dxy;
	TBranch* b_Reco_QQ_mumi_dxy;
	TBranch* b_Reco_QQ_mupl_dz;
	TBranch* b_Reco_QQ_mumi_dz;
	TBranch* b_Reco_QQ_4mom;
	TBranch* b_Reco_QQ_mupl_4mom;
	TBranch* b_Reco_QQ_mumi_4mom;
	TBranch* b_Gen_QQ_size;
	TBranch* b_Gen_QQ_4mom;
	TBranch* b_Gen_QQ_mupl_4mom;
	TBranch* b_Gen_QQ_mumi_4mom;
//}}}

//Branch address{{{
	tin->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
	tin->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
	tin->SetBranchAddress("Reco_QQ_type", Reco_QQ_type, &b_Reco_QQ_type);
	tin->SetBranchAddress("Reco_QQ_sign", Reco_QQ_sign, &b_Reco_QQ_sign);
	tin->SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb, &b_Reco_QQ_VtxProb);
	tin->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
	tin->SetBranchAddress("Reco_QQ_mupl_TMOneStaTight", Reco_QQ_mupl_TMOneStaTight, &b_Reco_QQ_mupl_TMOneStaTight);
	tin->SetBranchAddress("Reco_QQ_mumi_TMOneStaTight", Reco_QQ_mumi_TMOneStaTight, &b_Reco_QQ_mumi_TMOneStaTight);
	tin->SetBranchAddress("Reco_QQ_mupl_highPurity", Reco_QQ_mupl_highPurity, &b_Reco_QQ_mupl_highPurity);
	tin->SetBranchAddress("Reco_QQ_mumi_highPurity", Reco_QQ_mumi_highPurity, &b_Reco_QQ_mumi_highPurity);
	tin->SetBranchAddress("Reco_QQ_mupl_nTrkWMea", Reco_QQ_mupl_nTrkWMea, &b_Reco_QQ_mupl_nTrkWMea);
	tin->SetBranchAddress("Reco_QQ_mumi_nTrkWMea", Reco_QQ_mumi_nTrkWMea, &b_Reco_QQ_mumi_nTrkWMea);
	tin->SetBranchAddress("Reco_QQ_mupl_nPixWMea", Reco_QQ_mupl_nPixWMea, &b_Reco_QQ_mupl_nPixWMea);
	tin->SetBranchAddress("Reco_QQ_mumi_nPixWMea", Reco_QQ_mumi_nPixWMea, &b_Reco_QQ_mumi_nPixWMea);
	tin->SetBranchAddress("Reco_QQ_mupl_dxy", Reco_QQ_mupl_dxy, &b_Reco_QQ_mupl_dxy);
	tin->SetBranchAddress("Reco_QQ_mumi_dxy", Reco_QQ_mumi_dxy, &b_Reco_QQ_mumi_dxy);
	tin->SetBranchAddress("Reco_QQ_mupl_dz", Reco_QQ_mupl_dz, &b_Reco_QQ_mupl_dz);
	tin->SetBranchAddress("Reco_QQ_mumi_dz", Reco_QQ_mumi_dz, &b_Reco_QQ_mumi_dz);
	tin->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
	tin->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom, &b_Reco_QQ_mupl_4mom);
	tin->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom, &b_Reco_QQ_mumi_4mom);
	tin->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
	tin->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom, &b_Gen_QQ_4mom);
	tin->SetBranchAddress("Gen_QQ_mupl_4mom", &Gen_QQ_mupl_4mom, &b_Gen_QQ_mupl_4mom);
	tin->SetBranchAddress("Gen_QQ_mumi_4mom", &Gen_QQ_mumi_4mom, &b_Gen_QQ_mumi_4mom);
//}}}

//Define LorentzVector{{{
	TLorentzVector* Up_Reco_4mom = new TLorentzVector;
	TLorentzVector* mupl_Reco_4mom = new TLorentzVector;
	TLorentzVector* mumi_Reco_4mom = new TLorentzVector;
	TLorentzVector* Up_Gen_4mom = new TLorentzVector;
	TLorentzVector* mupl_Gen_4mom = new TLorentzVector;
	TLorentzVector* mumi_Gen_4mom = new TLorentzVector;
	Up_Reco_4mom = 0;
	mupl_Reco_4mom = 0;
	mumi_Reco_4mom = 0;
	Up_Gen_4mom = 0;
	mupl_Gen_4mom = 0;
	mumi_Gen_4mom = 0;
//}}}

	const Int_t Nevt = tin->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << "[" << Form("%.1f", ( (double)ievt/(double)Nevt)*100 ) << " %]" << endl;
		tin->GetEntry(ievt);

//Fill Denominator{{{
		for(Int_t iqq = 0; iqq < Gen_QQ_size; iqq++)
		{
			Up_Gen_4mom = (TLorentzVector*) Gen_QQ_4mom->At(iqq);
			mupl_Gen_4mom = (TLorentzVector*) Gen_QQ_mupl_4mom->At(iqq);
			mumi_Gen_4mom = (TLorentzVector*) Gen_QQ_mumi_4mom->At(iqq);
			if( !InAcc(mupl_Gen_4mom->Pt(), mupl_Gen_4mom->Eta(), MupTCut) ) continue;
			if( !InAcc(mumi_Gen_4mom->Pt(), mumi_Gen_4mom->Eta(), MupTCut) ) continue;
			if(ievt < Nevtcut) hyDenintgr->Fill(Up_Gen_4mom->Rapidity());
			else hyDenintgr->Fill(-1.*Up_Gen_4mom->Rapidity());
			hptDenintgr->Fill(Up_Gen_4mom->Pt());
			for(Int_t iy = 0; iy < Ny-1; iy++)
			{
				if(fabs(Up_Gen_4mom->Rapidity()) > ybins[iy] && fabs(Up_Gen_4mom->Rapidity()) <= ybins[iy+1])
				hDen[iy]->Fill(Up_Gen_4mom->Pt());
			}
		}
//}}}

//Fill Numerator{{{
		if( (HLTriggers&1)!=1 ) continue;

		for(Int_t iqq = 0; iqq < Reco_QQ_size; iqq++)
		{
			Up_Reco_4mom = (TLorentzVector*) Reco_QQ_4mom->At(iqq);
			mupl_Reco_4mom = (TLorentzVector*) Reco_QQ_mupl_4mom->At(iqq);
			mumi_Reco_4mom = (TLorentzVector*) Reco_QQ_mumi_4mom->At(iqq);

//Cuts for muon and Upsilon{{{
			if( (Reco_QQ_trig[iqq]&1) != 1 ) continue;

			if( !InAcc(mupl_Reco_4mom->Pt(), mupl_Reco_4mom->Eta(), MupTCut) ) continue;
			if( !InAcc(mumi_Reco_4mom->Pt(), mumi_Reco_4mom->Eta(), MupTCut) ) continue;

			bool muplSoft = ( (Reco_QQ_mupl_TMOneStaTight[iqq] == true) &&
									(Reco_QQ_mupl_nTrkWMea[iqq] > 5) &&
									(Reco_QQ_mupl_nPixWMea[iqq] > 0) &&
									(Reco_QQ_mupl_dxy[iqq] < 0.3) &&
									(Reco_QQ_mupl_dz[iqq] < 20.0) &&
									(Reco_QQ_mupl_highPurity[iqq] == true) //purity used for pPb not PbPb
									);
			bool mumiSoft = ( (Reco_QQ_mumi_TMOneStaTight[iqq] == true) &&
									(Reco_QQ_mumi_nTrkWMea[iqq] > 5) &&
									(Reco_QQ_mumi_nPixWMea[iqq] > 0) &&
									(Reco_QQ_mumi_dxy[iqq] < 0.3) &&
									(Reco_QQ_mumi_dz[iqq] < 20.0) &&
									(Reco_QQ_mumi_highPurity[iqq] == true) //purity used for pPb not PbPb
									);
			if( !(muplSoft && mumiSoft) ) continue;

			if( Reco_QQ_VtxProb[iqq] < 0.01 ) continue;

			if( Reco_QQ_sign[iqq] != 0) continue;
//}}}

			hyNumintgr->Fill(Up_Reco_4mom->Rapidity());
			hptNumintgr->Fill(Up_Reco_4mom->Pt());

			for(Int_t iy = 0; iy < Ny-1; iy++)
			{
				if(fabs(Up_Reco_4mom->Rapidity()) > ybins[iy] && fabs(Up_Reco_4mom->Rapidity()) <= ybins[iy+1])
				hNum[iy]->Fill(Up_Reco_4mom->Pt());
			}
		}
//}}}
	}

	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.05);
	lt1->SetNDC();

	cyDenintgr->cd();
	hyDenintgr->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cyDenintgr->SaveAs(Form("Plots/Denominator_for_eff_Up%dS_yintegral_MupT%s.pdf", Generation, MupT.Data()));

	cptDenintgr->cd();
	hptDenintgr->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cptDenintgr->SaveAs(Form("Plots/Denominator_for_eff_Up%dS_ptintegral_MupT%s.pdf", Generation, MupT.Data()));

	cyNumintgr->cd();
	hyNumintgr->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cyNumintgr->SaveAs(Form("Plots/Numerator_for_eff_Up%dS_yintegral_MupT%s.pdf", Generation, MupT.Data()));

	cptNumintgr->cd();
	hptNumintgr->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cptNumintgr->SaveAs(Form("Plots/Numerator_for_eff_Up%dS_ptintegral_MupT%s.pdf", Generation, MupT.Data()));

	cyEffintgr->cd();
	hyEffintgr = (TH1D*) hyNumintgr->Clone(Form("hEffyintgr"));
	hyEffintgr->GetYaxis()->SetTitle("Efficiency");
	hyEffintgr->Divide(hyDenintgr);
	hyEffintgr->SetMaximum(1.1);
	hyEffintgr->SetMinimum(0.);
	hyEffintgr->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cyEffintgr->SaveAs(Form("Plots/eff_Up%dS_yintegral_MupT%s.pdf", Generation, MupT.Data()));

	cptEffintgr->cd();
	hptEffintgr = (TH1D*) hptNumintgr->Clone(Form("hEffptintgr"));
	hptEffintgr->GetYaxis()->SetTitle("Efficiency");
	hptEffintgr->Divide(hptDenintgr);
	hptEffintgr->SetMaximum(1.1);
	hptEffintgr->SetMinimum(0.);
	hptEffintgr->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cptEffintgr->SaveAs(Form("Plots/eff_Up%dS_ptintegral_MupT%s.pdf", Generation, MupT.Data()));

	for(Int_t iy = 0; iy < Ny-1; iy++)
	{
		cDen[iy]->cd();
		hDen[iy]->Draw("pe");
		lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.6, 0.77, Form("%.1f < #eta #leq %.1f", ybins[iy], ybins[iy+1]));
		cDen[iy]->SaveAs(Form("Plots/Denominator_for_eff_Up%dS_Ny%d_etabin%d_MupT%s.pdf", Generation, Ny, iy, MupT.Data()));
		cNum[iy]->cd();
		hNum[iy]->Draw("pe");
		lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.6, 0.77, Form("%.1f < #eta #leq %.1f", ybins[iy], ybins[iy+1]));
		cNum[iy]->SaveAs(Form("Plots/Numerator_for_eff_Up%dS_Ny%d_etabin%d_MupT%s.pdf", Generation, Ny, iy, MupT.Data()));
		cEff[iy]->cd();
		hEff[iy] = (TH1D*) hNum[iy]->Clone(Form("hEff_%d", iy));
		hEff[iy]->GetYaxis()->SetTitle("efficiency");
		hEff[iy]->Divide(hDen[iy]);
		hEff[iy]->SetMaximum(1.1);
		hEff[iy]->SetMinimum(0.);
		hEff[iy]->Draw("pe");
		lt1->DrawLatex(0.6, 0.44, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.6, 0.37, Form("%.1f < #eta #leq %.1f", ybins[iy], ybins[iy+1]));
		cEff[iy]->SaveAs(Form("Plots/eff_Up%dS_Ny%d_etabin%d_MupT%s.pdf", Generation, Ny, iy, MupT.Data()));
	}

	TFile* fout = new TFile(Form("Plots/EffPlots_Upsilon_%dS_Ny%d_MupT%s.root", Generation, Ny, MupT.Data()), "RECREATE");
	fout->cd();
	hyDenintgr->Write();
	hyNumintgr->Write();
	hyEffintgr->Write();
	hptDenintgr->Write();
	hptNumintgr->Write();
	hptEffintgr->Write();
	for(Int_t iy = 0; iy < Ny-1; iy++)
	{
		hDen[iy]->Write();
		hNum[iy]->Write();
		hEff[iy]->Write();
	}
	fout->Close();
}

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut)
{
	return( TMath::Abs(muEta) < 2.4 && muPt >= MupTCut);
}
