//Headers: should be modified when you run in local{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TBranch.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TVector.h>
#include <TLorentzVector.h>
#include <iostream>
#include <fstream>
#include <TString.h>
#include <TH1.h>
#include <TF1.h>
#include <TSystem.h>
/*
#include "Style_Upv2.h"
#include "Upsilon.h"
*/
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"

using namespace std;
//}}}

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut);

void SortpPb1_Gen(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString MupT = "4")
{
//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_pPb1_MupT%s", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data());
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

//Get files{{{
	TString fname1;
	TChain* tin = new TChain("hionia/myTree");
	//fname1 = "root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb1_MC_1S_private_20200716.root";//private embedded
	fname1 = "root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb1_MC_1S_official_20201109.root";//official embedded
	//fname1 = "root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb1_MC_1S_non-embed.root";//official non-embedded
	tin->Add(fname1.Data());
//}}}

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//tree variables{{{
	UInt_t eventNb;
	Float_t zVtx;
	Int_t Ntracks;

	Int_t Gen_QQ_size;
	Int_t Gen_QQ_type[MaxQQ];
	TClonesArray* Gen_QQ_4mom;
	TClonesArray* Gen_QQ_mupl_4mom;
	TClonesArray* Gen_QQ_mumi_4mom;
	Gen_QQ_4mom = 0;
	Gen_QQ_mupl_4mom = 0;
	Gen_QQ_mumi_4mom = 0;
	Int_t Gen_trk_size;
	Int_t Gen_trk_charge[MaxTrk];
	TClonesArray* Gen_trk_4mom;
	Gen_trk_4mom = 0;
//}}}

//Branches{{{
	TBranch* b_eventNb;
	TBranch* b_zVtx;
	TBranch* b_Ntracks;

	TBranch* b_Gen_QQ_size;
	TBranch* b_Gen_QQ_type;
	TBranch* b_Gen_QQ_4mom;
	TBranch* b_Gen_QQ_mupl_4mom;
	TBranch* b_Gen_QQ_mumi_4mom;
	TBranch* b_Gen_trk_size;
	TBranch* b_Gen_trk_charge;
	TBranch* b_Gen_trk_4mom;
//}}}

//Branche address{{{
	tin->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
	tin->SetBranchAddress("zVtx", &zVtx, &b_zVtx);
	tin->SetBranchAddress("Ntracks", &Ntracks, &b_Ntracks);

	tin->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
	tin->SetBranchAddress("Gen_QQ_type", &Gen_QQ_type, &b_Gen_QQ_type);
	tin->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom, &b_Gen_QQ_4mom);
	tin->SetBranchAddress("Gen_QQ_mupl_4mom", &Gen_QQ_mupl_4mom, &b_Gen_QQ_mupl_4mom);
	tin->SetBranchAddress("Gen_QQ_mumi_4mom", &Gen_QQ_mumi_4mom, &b_Gen_QQ_mumi_4mom);
	tin->SetBranchAddress("Gen_trk_size", &Gen_trk_size, &b_Gen_trk_size);
	tin->SetBranchAddress("Gen_trk_4mom", &Gen_trk_4mom, &b_Gen_trk_4mom);
//}}}

//Define LorentzVector{{{
	TLorentzVector* Up_Gen_4mom = new TLorentzVector;
	TLorentzVector* mupl_Gen_4mom = new TLorentzVector;
	TLorentzVector* mumi_Gen_4mom = new TLorentzVector;
	TLorentzVector* Trk_Gen_4mom = new TLorentzVector;
	Up_Gen_4mom = 0;
	mupl_Gen_4mom = 0;
	mumi_Gen_4mom = 0;
	Trk_Gen_4mom = 0;
//}}}

//initialize dataset{{{
	DiMuon DMset;
	TTree* tout= new TTree("UpsilonTree", "");
	tout->SetMaxTreeSize(10000000000000);
	DMset.BuildBranch(tout);
//}}}

	const Int_t Nevt = tin->GetEntries();
	Float_t vz = -99.;

	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_pPb1_MupT%s/Sort_OniaTree_pPb1_PADoubleMuon_MC_Gen.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data()), "RECREATE");//embedded MC sample
	//TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_pPb1_MupT%s/Sort_OniaTree_pPb1_PADoubleMuon_MC_Gen_nonemb.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data()), "RECREATE");//nen-embedded MC sample

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	//for(Int_t ievt = 0; ievt < 100000; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)(ievt)/(double)(Nevt)*100)) << " %]" << endl;
		tin->GetEntry(ievt);

		DMset.clear();

		Int_t NtrgGen = 0;
		Int_t NassGen = 0;
		Int_t MultGen = 0;
		Bool_t is_inMassGen = false;

		vz = zVtx;

//Get trigger vector{{{
		for(Int_t iqq = 0; iqq < Gen_QQ_size; iqq++)
		{
			Up_Gen_4mom = (TLorentzVector*) Gen_QQ_4mom->At(iqq);
			mupl_Gen_4mom = (TLorentzVector*) Gen_QQ_mupl_4mom->At(iqq);
			mumi_Gen_4mom = (TLorentzVector*) Gen_QQ_mumi_4mom->At(iqq);

			if( Up_Gen_4mom->M() > 9 && Up_Gen_4mom->M() <= 10 && Up_Gen_4mom->Rapidity() >= -2.4 && Up_Gen_4mom->Rapidity() <= 2.4 && Up_Gen_4mom->Pt() >= ptMin && Up_Gen_4mom->Pt() < ptMax)
			{
				if( !InAcc(mupl_Gen_4mom->Pt(), mupl_Gen_4mom->Eta(), MupTCut) ) continue;
				if( !InAcc(mumi_Gen_4mom->Pt(), mumi_Gen_4mom->Eta(), MupTCut) ) continue;

				new( (*DMset.Vec_trg_Gen)[NtrgGen] )TLorentzVector(*Up_Gen_4mom);
				NtrgGen++;
				is_inMassGen = true;
			}
		}
//}}}

//Get associator vector{{{
		if(is_inMassGen)
		{
			for(Int_t itrk = 0; itrk < Gen_trk_size; itrk++)
			{
				Trk_Gen_4mom = (TLorentzVector*) Gen_trk_4mom->At(itrk);
				TVector3 Trk_vector;

				if(Trk_Gen_4mom->Eta() <= 2.4 && Trk_Gen_4mom->Eta() >= -2.4 && Trk_Gen_4mom->Pt() >= 0.4)
				{
					MultGen++;
				}

				if(Trk_Gen_4mom->Eta() <= 2.4 && Trk_Gen_4mom->Eta() >= -2.4 && Trk_Gen_4mom->Pt() >= TrkptMin && Trk_Gen_4mom->Pt() < TrkptMax && Trk_Gen_4mom->Pt() >= 0.3)
				{
					new( (*DMset.Vec_ass_Gen)[NassGen] )TLorentzVector(*Trk_Gen_4mom);
					NassGen++;
				}
			}
		}
//}}}

		if( is_inMassGen && (NassGen != 0) ) 
		{
			DMset.Ntrg_Gen = NtrgGen;
			DMset.Nass_Gen = NassGen;
			DMset.zVtx = vz;
			DMset.mult = MultGen;
			tout->Fill();
		}
	}
	tout->Write();
	fout->Close();
}

//External function{{{
bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut)
{
	return ( TMath::Abs(muEta) < 2.4 && muPt >= MupTCut);
}
//}}}
