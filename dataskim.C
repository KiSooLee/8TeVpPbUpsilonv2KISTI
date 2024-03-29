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

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut);

void dataskim(const Bool_t isMC = false, const Int_t Generation = 1, const Bool_t Weight = true, const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Int_t isTnP = 0, const Bool_t isSS = false, const TString MupT = "3p5")
{
//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/SkimmedFiles";
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//define muon pt value{{{
	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString SS;
	if(isSS) SS = "SS";//same sign
	else SS = "OS";//opposite sign
	Double_t MupTCut;
	if(MupT == "0") MupTCut = 0;
	else if(MupT == "0p5") MupTCut = 0.5;
	else if(MupT == "1") MupTCut = 1.0;
	else if(MupT == "1p5") MupTCut = 1.5;
	else if(MupT == "2") MupTCut = 2.0;
	else if(MupT == "2p5") MupTCut = 2.5;
	else if(MupT == "3") MupTCut = 3.0;
	else if(MupT == "3p3") MupTCut = 3.3;
	else if(MupT == "3p4") MupTCut = 3.4;
	else if(MupT == "3p5") MupTCut = 3.5;
	else if(MupT == "4") MupTCut = 4.0;
	else if(MupT == "10") MupTCut = 10.0;
	else
	{
		cout << "There is no such muon pT cut value" << endl;
		return;
	}
	TString TnPs;
	if(isTnP == 0) TnPs = "w";
	else if (isTnP == 1) TnPs = "statup";
	else if (isTnP == 2) TnPs = "statdw";
	else if (isTnP == 3) TnPs = "systup";
	else if (isTnP == 4) TnPs = "systdw";
	else if (isTnP == 5) TnPs = "wo";
	else
	{
		cout << "There is no such TnP index" << endl;
		return;
	}
//}}}

//Get files{{{
	TString fname1, fname2;
	TChain* tin = new TChain("hionia/myTree");
	//fname1 = "oniaTree_pPb_20170504.root";//KUNPL
	//fname2 = "oniaTree_Pbp_20170504.root";//KUNPL
	if(isMC)
	{
		//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb_MC_%dS_20190613.root", Generation);//official non-embedded
		//fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_Pbp_MC_%dS_20190613.root", Generation);//official non-embedded
		//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb_MC_%dS_official_20201109.root", Generation);//official 1S embedded
		//fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_Pbp_MC_%dS_official_20201109.root", Generation);//official 1S embedded
		//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb_MC_%dS_official_20210815.root", Generation);//official 2S embedded
		//fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_Pbp_MC_%dS_official_20210815.root", Generation);//official 2S embedded
		fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb_MC_%dS_official_20210818.root", Generation);//official 3S embedded
		fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_Pbp_MC_%dS_official_20210818.root", Generation);//official 3S embedded
	}
	else
	{
		fname1 = "root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb_20170504.root";//KISTI
		fname2 = "root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_Pbp_20170504.root";//KISTI
	}
	tin->Add(fname1.Data());
	const Int_t Nevtcut = tin->GetEntries();
	tin->Add(fname2.Data());

	TFile* facc;
	TFile* feff;
	TH1F* hAcc0016 = 0;
	TH1F* hAcc1618 = 0;
	TH1F* hAcc1821 = 0;
	TH1F* hAcc2124 = 0;
	TH1F* hEff0016 = 0;
	TH1F* hEff1618 = 0;
	TH1F* hEff1821 = 0;
	TH1F* hEff2124 = 0;
	if(Weight)
	{
		facc = new TFile(Form("AccEff/Plots/AccPlots_Upsilon_%dS_RW%o_MupT%s.root", Generation, isAccRW, MupT.Data()),"READ");
		feff = new TFile(Form("AccEff/Plots/EffPlots_Upsilon_%dS_RW%o_TnP%s_MupT%s.root", Generation, isEffRW, TnPs.Data(), MupT.Data()),"READ");
		hAcc0016 = (TH1F*) facc->Get("hAcc0016");
		hAcc1618 = (TH1F*) facc->Get("hAcc1618");
		hAcc1821 = (TH1F*) facc->Get("hAcc1821");
		hAcc2124 = (TH1F*) facc->Get("hAcc2124");
		hEff0016 = (TH1F*) feff->Get("hEff_0");
		hEff1618 = (TH1F*) feff->Get("hEff_1");
		hEff1821 = (TH1F*) feff->Get("hEff_2");
		hEff2124 = (TH1F*) feff->Get("hEff_3");
	}
//}}}

	TFile* fout;
	if(isMC)
	{
		//fout = new TFile(Form("SkimmedFiles/Skim_OniaTree_%s_PADoubleMuon_%dS_MupT%s.root", MorD.Data(), Generation, MupT.Data()), "RECREATE");
		fout = new TFile(Form("SkimmedFiles/Skim_OniaTree_%s_PADoubleMuon_%dS_MupT%s_official.root", MorD.Data(), Generation, MupT.Data()), "RECREATE");
		//fout = new TFile(Form("SkimmedFiles/Skim_OniaTree_%s_PADoubleMuon_%dS_MupT%s_official_non-embedded.root", MorD.Data(), Generation, MupT.Data()), "RECREATE");
	}
	else if(!Weight) fout = new TFile(Form("SkimmedFiles/Skim_OniaTree_%s_PADoubleMuon_noWeight_%s_MupT%s.root", MorD.Data(), SS.Data(), MupT.Data()), "RECREATE");
	else fout = new TFile(Form("SkimmedFiles/Skim_OniaTree_%s_PADoubleMuon_Acc%o_Eff%o_TnP%s_%s_MupT%s.root", MorD.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data()), "RECREATE");

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//Tree variables{{{
	UInt_t eventNb;
	ULong64_t HLTriggers;
	Int_t Ntracks;

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
	Bool_t Reco_isgoodTrk[MaxTrk];
	Bool_t Reco_isMuTrk[MaxTrk];
	TClonesArray* Reco_trk_4mom;
	Reco_trk_4mom = 0;
//}}}

//Branch{{{
	TBranch* b_eventNb;
	TBranch* b_HLTriggers;
	TBranch* b_Ntracks;
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
//}}}

//Branch address{{{
	tin->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
	tin->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
	tin->SetBranchAddress("Ntracks", &Ntracks, &b_Ntracks);
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

//RooFit variable{{{
	RooRealVar* Roomass = new RooRealVar("mass", "dimuon mass", 0, 100, "GeV/c^{2}");
	RooRealVar* Roopt = new RooRealVar("pt", "p_{T} of dimuon", 0, 100, "GeV/c");
	RooRealVar* Rooy = new RooRealVar("y", "rapidity of dimuon", -3., 3, "");
	RooRealVar* Roophi = new RooRealVar("phi", "phi of dimuon", -3.15, 3.15, "");
	RooRealVar* Roomult = new RooRealVar("mult", "track multiplicity of event", 0, 300, "");
	RooRealVar* Rooweight = new RooRealVar("weight", "p_{T} weight", 0, 10000, "");
	RooArgSet* argset = new RooArgSet(*Roomass, *Roopt, *Rooy, *Roophi, *Roomult, *Rooweight);
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

	vector<TVector3>* Vec_trg = new vector<TVector3>;
	vector<TVector3>* Vec_ass = new vector<TVector3>;
//}}}

	DiMuon DMset;

	TTree* tout = new TTree("UpsilonTree", "");
	tout->SetMaxTreeSize(10000000000000);
	DMset.BuildBranch(tout);

	TH1D* hEvent = new TH1D("hEvent", "", 10 ,0.5, 11.5);

	const Int_t Nevt = tin->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << "[" << Form("%.1f", ( (double)ievt/(double)Nevt)*100 ) << " %]" << endl;
		tin->GetEntry(ievt);

		hEvent->GetXaxis()->SetBinLabel(1,"Events total");
		hEvent->Fill(1);

		DMset.clear();

		if( (HLTriggers&1)!=1 ) continue;
		hEvent->GetXaxis()->SetBinLabel(2, "Event trigger");
		hEvent->Fill(2);

		DMset.mult = Ntracks;
		DMset.eventNb = eventNb;

//Get trigger vector{{{
		for(Int_t iqq = 0; iqq < Reco_QQ_size; iqq++)
		{
			hEvent->GetXaxis()->SetBinLabel(3,"Di-muons Total");
			hEvent->Fill(3);

			Up_Reco_4mom = (TLorentzVector*) Reco_QQ_4mom->At(iqq);
			mupl_Reco_4mom = (TLorentzVector*) Reco_QQ_mupl_4mom->At(iqq);
			mumi_Reco_4mom = (TLorentzVector*) Reco_QQ_mumi_4mom->At(iqq);

//Cuts for muon and Upsilon{{{
			if( (Reco_QQ_trig[iqq]&1) != 1 ) continue;
			hEvent->GetXaxis()->SetBinLabel(4,"Di-muons trig");
			hEvent->Fill(4);

			if( !InAcc(mupl_Reco_4mom->Pt(), mupl_Reco_4mom->Eta(), MupTCut) ) continue;
			if( !InAcc(mumi_Reco_4mom->Pt(), mumi_Reco_4mom->Eta(), MupTCut) ) continue;
			hEvent->GetXaxis()->SetBinLabel(5,"Di-muons Accep");
			hEvent->Fill(5);

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
			hEvent->GetXaxis()->SetBinLabel(6,"Di-muons mu ID");
			hEvent->Fill(6);

			if( Reco_QQ_VtxProb[iqq] < 0.01 ) continue;
			hEvent->GetXaxis()->SetBinLabel(7,"Di-muons Vtx prob.");
			hEvent->Fill(7);
			if( (!isSS && (Reco_QQ_sign[iqq] != 0)) || (isSS && (Reco_QQ_sign[iqq] == 0)) ) continue;
			hEvent->GetXaxis()->SetBinLabel(8,"Di-muoons charge sign");
			hEvent->Fill(8);
//}}}

			DMset.mass = Up_Reco_4mom->M();
			DMset.pt = Up_Reco_4mom->Pt();
			DMset.phi = Up_Reco_4mom->Phi();
			DMset.mupl_pt = mupl_Reco_4mom->Pt();
			DMset.mumi_pt = mumi_Reco_4mom->Pt();
			DMset.mupl_eta = mupl_Reco_4mom->Eta();
			DMset.mumi_eta = mumi_Reco_4mom->Eta();
			if(ievt < Nevtcut) DMset.y = Up_Reco_4mom->Rapidity();
			else DMset.y = (-1.)*Up_Reco_4mom->Rapidity();
			DMset.mult = Ntracks;

         // Get weight number 
			double eff = 1.0, acc = 1.0, wgt = 1.0;
			if(!isMC && Weight)
			{
				if(fabs(Up_Reco_4mom->Rapidity()) <= 1.6)
				{
					eff = hEff0016->GetBinContent(hEff0016->FindBin(Up_Reco_4mom->Pt()));
					acc = hAcc0016->GetBinContent(hAcc0016->FindBin(Up_Reco_4mom->Pt()));
				}
				else if(fabs(Up_Reco_4mom->Rapidity()) > 1.6 && fabs(Up_Reco_4mom->Rapidity()) <= 1.8)
				{
					eff = hEff1618->GetBinContent(hEff1618->FindBin(Up_Reco_4mom->Pt()));
					acc = hAcc1618->GetBinContent(hAcc1618->FindBin(Up_Reco_4mom->Pt()));
				}
				else if(fabs(Up_Reco_4mom->Rapidity()) > 1.8 && fabs(Up_Reco_4mom->Rapidity()) <= 2.1)
				{
					eff = hEff1821->GetBinContent(hEff1821->FindBin(Up_Reco_4mom->Pt()));
					acc = hAcc1821->GetBinContent(hAcc1821->FindBin(Up_Reco_4mom->Pt()));
				}
				else if(fabs(Up_Reco_4mom->Rapidity()) > 2.1 && fabs(Up_Reco_4mom->Rapidity()) <= 2.4)
				{
					eff = hEff2124->GetBinContent(hEff2124->FindBin(Up_Reco_4mom->Pt()));
					acc = hAcc2124->GetBinContent(hAcc2124->FindBin(Up_Reco_4mom->Pt()));
				}
				wgt = 1.0/(eff*acc);
			}
			DMset.weight = wgt;
			tout->Fill();

			Roomass->setVal( (double)DMset.mass );
			Roopt->setVal( (double)DMset.pt );
			Rooy->setVal( (double)DMset.y );
			Roophi->setVal( (double)DMset.phi );
			Roomult->setVal( (double)DMset.mult );
			Rooweight->setVal( (double)DMset.weight );
			dataset->add(*argset);
		}
//}}}
	}
	dataset->Write();
	tout->Write();
	fout->Close();
}

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut)
{
	return( TMath::Abs(muEta) < 2.4 && muPt >= MupTCut);
}
