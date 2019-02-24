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

bool InAcc(Double_t muPt, Double_t muEta);

void AccEff()
{
	SetStyle();
	TString version = "v16";
	const Int_t Generation = 3;//1: 1S, 2: 2S, 3:3S

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/Plots";
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//Get files{{{
	TChain* tin = new TChain("hionia/myTree");
	TString fname1 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb_%dS_MC_20190122.root", Generation);//1S
	tin->Add(fname1.Data());
//}}}

	TH2D* hGen = new TH2D("hGen", ";Rapidity;p_{T}^{#varUpsilon}", rap_narr-1, rapBinsArr, pt_narr-1, ptBinsArr);
	TH2D* hAccGen = new TH2D("hAccGen", ";Rapidity;p_{T}^{#varUpsilon}", rap_narr-1, rapBinsArr, pt_narr-1, ptBinsArr);
	TH2D* hReco = new TH2D("hReco", ";Rapidity;p_{T}^{#varUpsilon}", rap_narr-1, rapBinsArr, pt_narr-1, ptBinsArr);
	TH2D* hGeneta = new TH2D("hGeneta", ";p_{T}^{#varUpsilon};PsudoRapidity", pt_narr-1, ptBinsArr, 40, -10, 10);
	TH2D* hRecoeta = new TH2D("hRecoeta", ";p_{T}^{#varUpsilon};PsudoRapidity", pt_narr-1, ptBinsArr, 40, -10, 10);

	FormTH2(hGen);
	FormTH2(hAccGen);
	FormTH2(hReco);
	FormTH2(hGeneta);
	FormTH2(hRecoeta);

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

//Fill Gen{{{
		for(Int_t iqq = 0; iqq < Gen_QQ_size; iqq++)
		{
			Up_Gen_4mom = (TLorentzVector*) Gen_QQ_4mom->At(iqq);
			mupl_Gen_4mom = (TLorentzVector*) Gen_QQ_mupl_4mom->At(iqq);
			mumi_Gen_4mom = (TLorentzVector*) Gen_QQ_mumi_4mom->At(iqq);
			hGen->Fill(Up_Gen_4mom->Rapidity(), Up_Gen_4mom->Pt());
			hGeneta->Fill(Up_Gen_4mom->Pt(), Up_Gen_4mom->Eta());
			if( !InAcc(mupl_Gen_4mom->Pt(), mupl_Gen_4mom->Eta()) ) continue;
			if( !InAcc(mumi_Gen_4mom->Pt(), mumi_Gen_4mom->Eta()) ) continue;
			hAccGen->Fill(Up_Gen_4mom->Rapidity(), Up_Gen_4mom->Pt());
		}
//}}}

		if( (HLTriggers&1)!=1 ) continue;

		for(Int_t iqq = 0; iqq < Reco_QQ_size; iqq++)
		{
			Up_Reco_4mom = (TLorentzVector*) Reco_QQ_4mom->At(iqq);
			mupl_Reco_4mom = (TLorentzVector*) Reco_QQ_mupl_4mom->At(iqq);
			mumi_Reco_4mom = (TLorentzVector*) Reco_QQ_mumi_4mom->At(iqq);

//Cuts for muon and Upsilon{{{
			if( (Reco_QQ_trig[iqq]&1) != 1 ) continue;

			if( !InAcc(mupl_Reco_4mom->Pt(), mupl_Reco_4mom->Eta()) ) continue;
			if( !InAcc(mumi_Reco_4mom->Pt(), mumi_Reco_4mom->Eta()) ) continue;

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

			hReco->Fill(Up_Reco_4mom->Rapidity(), Up_Reco_4mom->Pt());
			hRecoeta->Fill(Up_Reco_4mom->Pt(), Up_Reco_4mom->Eta());
		}
	}

	TCanvas* cGen = new TCanvas("cGen", "", 0, 0, 600, 600);
	cGen->cd();
	hGen->Draw("colztext");
	cGen->SaveAs(Form("Plots/Gen_Upsilon_%dS_%s.pdf", Generation, version.Data()));

	TCanvas* cGeneta = new TCanvas("cGeneta", "", 0, 0, 600, 600);
	cGeneta->cd();
	hGeneta->Draw("colztext");
	cGeneta->SaveAs(Form("Plots/Geneta_Upsilon_%dS_%s.pdf", Generation, version.Data()));

	TCanvas* cAccGen = new TCanvas("cAccGen", "", 0, 0, 600, 600);
	cAccGen->cd();
	hAccGen->Draw("colztext");
	cAccGen->SaveAs(Form("Plots/GenwAcc_Upsilon_%dS_%s.pdf", Generation, version.Data()));

	TCanvas* cReco = new TCanvas("cReco", "", 0, 0, 600, 600);
	cReco->cd();
	hReco->Draw("colztext");
	cReco->SaveAs(Form("Plots/Reco_Upsilon_%dS_%s.pdf", Generation, version.Data()));

	TCanvas* cRecoeta = new TCanvas("cRecoeta", "", 0, 0, 600, 600);
	cRecoeta->cd();
	hRecoeta->Draw("colztext");
	cRecoeta->SaveAs(Form("Plots/Recoeta_Upsilon_%dS_%s.pdf", Generation, version.Data()));

	TH2D* hAcc = (TH2D*) hAccGen->Clone("hAcc");
	hAcc->Divide(hGen);

	TCanvas* cAcc = new TCanvas("cAcc", "", 0, 0, 600, 600);
	cAcc->cd();
	hAcc->Draw("colztext");
	cAcc->SaveAs(Form("Plots/Acc_Upsilon_%dS_%s.pdf", Generation, version.Data()));

	TH2D* hEff = (TH2D*) hReco->Clone("hEff");
	hEff->Divide(hAccGen);

	TCanvas* cEff = new TCanvas("cEff", "", 0, 0, 600, 600);
	cEff->cd();
	hEff->Draw("colztext");
	cEff->SaveAs(Form("Plots/Eff_Upsilon_%dS_%s.pdf", Generation, version.Data()));

	TH2D* hAccEff = (TH2D*) hAcc->Clone("hAccEff");
	hAccEff->Multiply(hEff);

	TCanvas* cAccEff = new TCanvas("cAccEff", "", 0, 0, 600, 600);
	cAccEff->cd();
	hAccEff->Draw("colztext");
	cAccEff->SaveAs(Form("Plots/AccEff_Upsilon_%dS_%s.pdf", Generation, version.Data()));

	TH2D* hEffeta = (TH2D*) hRecoeta->Clone("hEffeta");
	hEffeta->Divide(hGeneta);

	TCanvas* cEffeta = new TCanvas("cEffeta", "", 0, 0, 600, 600);
	cEffeta->cd();
	hEffeta->Draw("colztext");
	cEffeta->SaveAs(Form("Plots/Effeta_Upsilon_%dS_%s.pdf", Generation, version.Data()));

	TFile* fout = new TFile(Form("Plots/AccEffPlots_Upsilon_%dS_%s.root", Generation, version.Data()), "RECREATE");
	fout->cd();
	hGen->Write();
	hGeneta->Write();
	hAccGen->Write();
	hReco->Write();
	hRecoeta->Write();
	hAcc->Write();
	hEff->Write();
	hEffeta->Write();
	hAccEff->Write();
	fout->Close();
}

bool InAcc(Double_t muPt, Double_t muEta)
{
	return( TMath::Abs(muEta) < 2.4 && muPt >= 4);
}
