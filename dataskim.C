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

#include "Headers/Style_Upv2.h"
#include "Headers/Upsilon.h"

using namespace std;
using namespace RooFit;
//}}}

bool InAcc(Double_t muPt, Double_t muEta);

void dataskim(bool isMC = false)
{
//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/SkimmedFiles";
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

	TString DM;
	if(isMC) DM = "MC";
	else DM = "RD";

//Get files{{{
	TString fname1, fname2;
	TChain* tin = new TChain("hionia/myTree");
	//fname1 = "oniaTree_pPb_20170504.root";//KUNPL
	//fname2 = "oniaTree_Pbp_20170504.root";//KUNPL
	fname1 = "/xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb_20170504.root";//KISTI
	fname2 = "/xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_Pbp_20170504.root";//KISTI
	tin->Add(fname1.Data());
	tin->Add(fname2.Data());
//}}}

	TFile* fout;
	//fout = new TFile(Form("SkimmedFiles/Skim_OniaTree_%s_PADoubleMuon_full.root", DM.Data()), "RECREATE");
	//fout = new TFile(Form("SkimmedFiles/Skim_OniaTree_%s_PADoubleMuon_noAcc.root", DM.Data()), "RECREATE");
	fout = new TFile(Form("SkimmedFiles/Skim_OniaTree_%s_PADoubleMuon_MupT3p5.root", DM.Data()), "RECREATE");

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//Tree variables{{{
	UInt_t eventNb;
	ULong64_t HLTriggers;

//data{{{
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
	Int_t Reco_trk_size;
	Int_t Reco_trk_charge[MaxTrk];
	Int_t Reco_isgoodTrk[MaxTrk];
	Int_t Reco_isMuTrk[MaxTrk];
	TClonesArray* Reco_trk_4mom;
	Reco_trk_4mom = 0;
//}}}

//MC{{{
	Int_t Gen_QQ_size;
	TClonesArray* Gen_QQ_4mom;
	TClonesArray* Gen_QQ_mupl_4mom;
	TClonesArray* Gen_QQ_mumi_4mom;
	Gen_QQ_4mom = 0;
	Gen_QQ_mupl_4mom = 0;
	Gen_QQ_mumi_4mom = 0;
	Int_t Gen_trk_size;
	Int_t Gen_trk_charge[MaxTrk];
	Int_t Gen_isMuTrk[MaxTrk];
	TClonesArray* Gen_trk_4mom;
	Gen_trk_4mom = 0;
//}}}

//}}}

//Branch{{{
	TBranch* b_eventNb;
	TBranch* b_HLTriggers;

//data{{{
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
	TBranch* b_Reco_trk_size;
	TBranch* b_Reco_trk_charge;
	TBranch* b_Reco_isgoodTrk;
	TBranch* b_Reco_isMuTrk;
	TBranch* b_Reco_trk_4mom;
//data}}}

//MC{{{
	TBranch* b_Gen_QQ_size;
	TBranch* b_Gen_QQ_4mom;
	TBranch* b_Gen_QQ_mupl_4mom;
	TBranch* b_Gen_QQ_mumi_4mom;
	TBranch* b_Gen_trk_size;
	TBranch* b_Gen_trk_charge;
	TBranch* b_Gen_isMuTrk;
	TBranch* b_Gen_trk_4mom;
//data}}}

//}}}

//Branch address{{{

//data{{{
	tin->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
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
	tin->SetBranchAddress("Reco_trk_size", &Reco_trk_size, &b_Reco_trk_size);
	tin->SetBranchAddress("Reco_trk_charge", Reco_trk_charge, &b_Reco_trk_charge);
	tin->SetBranchAddress("Reco_isgoodTrk", Reco_isgoodTrk, &b_Reco_isgoodTrk);
	tin->SetBranchAddress("Reco_isMuTrk", Reco_isMuTrk, &b_Reco_isMuTrk);
	tin->SetBranchAddress("Reco_trk_4mom", &Reco_trk_4mom, &b_Reco_trk_4mom);
//}}}

//MC{{{
	if(isMC)
	{
		tin->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
		tin->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom, &b_Gen_QQ_4mom);
		tin->SetBranchAddress("Gen_QQ_mupl_4mom", &Gen_QQ_mupl_4mom, &b_Gen_QQ_mupl_4mom);
		tin->SetBranchAddress("Gen_QQ_mumi_4mom", &Gen_QQ_mumi_4mom, &b_Gen_QQ_mumi_4mom);
		tin->SetBranchAddress("Gen_trk_size", &Gen_trk_size, &b_Gen_trk_size);
		tin->SetBranchAddress("Gen_trk_charge", Gen_trk_charge, &b_Gen_trk_charge);
		tin->SetBranchAddress("Gen_isMuTrk", Gen_isMuTrk, &b_Gen_isMuTrk);
		tin->SetBranchAddress("Gen_trk_4mom", &Gen_trk_4mom, &b_Gen_trk_4mom);
	}
//}}}

//}}}

//RooFit variable{{{
	RooRealVar* Roomass = new RooRealVar("mass", "dimuon mass", 0, 100, "GeV/c^{2}");
	RooRealVar* Roopt = new RooRealVar("pt", "p_{T} of dimuon", 0, 100, "GeV/c");
	RooRealVar* Rooy = new RooRealVar("y", "rapidity of dimuon", -3., 3, "");
	RooRealVar* Roomult = new RooRealVar("mult", "track multiplicity of event", 0, 300, "");
	RooRealVar* Rooweight = new RooRealVar("weight", "p_{T} weight", 0, 10000, "");
	RooArgSet* argset = new RooArgSet(*Roomass, *Roopt, *Rooy, *Roomult, *Rooweight);
	RooDataSet* dataset = new RooDataSet("dataset", "dataset", *argset);
//}}}

//Define LorentzVector{{{
	TLorentzVector* Up_Reco_4mom = new TLorentzVector;
	TLorentzVector* mupl_Reco_4mom = new TLorentzVector;
	TLorentzVector* mumi_Reco_4mom = new TLorentzVector;
	TLorentzVector* Trk_Reco_4mom = new TLorentzVector;
	Up_Reco_4mom = 0;
	mupl_Reco_4mom = 0;
	mumi_Reco_4mom = 0;
	Trk_Reco_4mom = 0;
	TLorentzVector* Up_Gen_4mom = new TLorentzVector;
	TLorentzVector* mupl_Gen_4mom = new TLorentzVector;
	TLorentzVector* mumi_Gen_4mom = new TLorentzVector;
	TLorentzVector* Trk_Gen_4mom = new TLorentzVector;
	Up_Gen_4mom = 0;
	mupl_Gen_4mom = 0;
	mumi_Gen_4mom = 0;
	Trk_Gen_4mom = 0;

	vector<TVector3>* Vec_trg = new vector<TVector3>;
	vector<TVector3>* Vec_ass = new vector<TVector3>;
//}}}

	DiMuon DMGenset;
	TTree* toutGen;
	toutGen = new TTree("UpsilonGenTree", "");
	toutGen->SetMaxTreeSize(10000000000000);
	DMGenset.BuildBranch(toutGen);

	DiMuon DMset;

	TTree* tout = new TTree("UpsilonTree", "");
	tout->SetMaxTreeSize(10000000000000);
	DMset.BuildBranch(tout);

	TH1D* hEvent = new TH1D("hEvent", "", 20 ,0.5, 21.5);

	const Int_t Nevt = tin->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << "[" << Form("%.1f", ( (double)ievt/(double)Nevt)*100 ) << " %]" << endl;
		tin->GetEntry(ievt);

		hEvent->GetXaxis()->SetBinLabel(1,"Events total");
		hEvent->Fill(1);

		DMGenset.clear();
		if(isMC)
		{
			for(Int_t iqq = 0; iqq < Gen_QQ_size; iqq++)
			{
				Up_Gen_4mom = (TLorentzVector*) Gen_QQ_4mom->At(iqq);
				mupl_Gen_4mom = (TLorentzVector*) Gen_QQ_mupl_4mom->At(iqq);
				mumi_Gen_4mom = (TLorentzVector*) Gen_QQ_mumi_4mom->At(iqq);
				DMGenset.mass = Up_Gen_4mom->M();
				DMGenset.pt = Up_Gen_4mom->Pt();
				DMGenset.y = Up_Gen_4mom->Rapidity();
				DMGenset.weight = 1.;
				toutGen->Fill();
			}
		}

		DMset.clear();

		if( (HLTriggers&1)!=1 ) continue;
		hEvent->GetXaxis()->SetBinLabel(3, "Event trigger");
		hEvent->Fill(3);

//Get track multiplicity{{{
		Int_t Tot_Ntrk = 0;
		for(Int_t itrk = 0; itrk < Reco_trk_size; itrk++)
		{
			if( Reco_isgoodTrk[itrk] && !Reco_isMuTrk[itrk] ) Tot_Ntrk++;
		}
//}}}

		DMset.mult = Tot_Ntrk;
		DMset.eventNb = eventNb;

//Get trigger vector{{{
		for(Int_t iqq = 0; iqq < Reco_QQ_size; iqq++)
		{
			hEvent->GetXaxis()->SetBinLabel(4,"Di-muons Total");
			hEvent->Fill(4);

			Up_Reco_4mom = (TLorentzVector*) Reco_QQ_4mom->At(iqq);
			mupl_Reco_4mom = (TLorentzVector*) Reco_QQ_mupl_4mom->At(iqq);
			mumi_Reco_4mom = (TLorentzVector*) Reco_QQ_mumi_4mom->At(iqq);

//Cuts for muon and Upsilon{{{
			if( (Reco_QQ_trig[iqq]&1) != 1 ) continue;
			hEvent->GetXaxis()->SetBinLabel(7,"Di-muons trig");
			hEvent->Fill(7);

			if( !InAcc(mupl_Reco_4mom->Pt(), mupl_Reco_4mom->Eta()) ) continue;
			if( !InAcc(mumi_Reco_4mom->Pt(), mumi_Reco_4mom->Eta()) ) continue;
//			hEvent->GetXaxis()->SetBinLabel(5,"Di-muons Accep");
//			hEvent->Fill(5);

			//if( Up_Reco_4mom->M() < 8 || Up_Reco_4mom->M() > 14) continue;
			//if( abs(Up_Reco_4mom->Rapidity()) > 2.4 ) continue;
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
			hEvent->GetXaxis()->SetBinLabel(8,"Di-muons mu ID");
			hEvent->Fill(8);

			if( Reco_QQ_VtxProb[iqq] < 0.01 ) continue;
			hEvent->GetXaxis()->SetBinLabel(6,"Di-muons Vtx prob.");
			hEvent->Fill(6);

			if( Reco_QQ_sign[iqq] != 0) continue;
			hEvent->GetXaxis()->SetBinLabel(9,"Di-muoons charge sign");
			hEvent->Fill(9);
			//if( abs(Up_Reco_4mom->Eta()) > 2.4 ) continue;
//}}}

			DMset.mass = Up_Reco_4mom->M();
			DMset.pt = Up_Reco_4mom->Pt();
			DMset.y = Up_Reco_4mom->Rapidity();
			DMset.mult = Tot_Ntrk;
			DMset.weight = 1.;
			tout->Fill();

			Roomass->setVal( (double)DMset.mass );
			Roopt->setVal( (double)DMset.pt );
			Rooy->setVal( (double)DMset.y );
			Roomult->setVal( (double)DMset.mult );
			Rooweight->setVal( (double)DMset.weight );
			dataset->add(*argset);
		}
//}}}
	}
	dataset->Write();
	tout->Write();
	toutGen->Write();
	fout->Close();
}

bool InAcc(Double_t muPt, Double_t muEta)
{
	//return( TMath::Abs(muEta) < 2.4 && muPt >= 4);
	return( TMath::Abs(muEta) < 2.4 && muPt >= 3.5);
}
