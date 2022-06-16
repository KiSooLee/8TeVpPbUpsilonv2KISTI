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

#include "Style_Upv2.h"
#include "Upsilon.h"
/*
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
*/
using namespace std;
//}}}

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut);

void SortpPb1_Reco(const bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString MupT = "4", const Bool_t isSS = false, const Int_t imass = 0)
{
//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_pPb1_MupT%s", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data());
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString SS;//sign
	if(isSS) SS = "SS";//same sign
	else SS = "OS";//opposite sign

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
	if(isMC)
	{
		
		//fname1 = "root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb1_MC_1S_private_20200716.root";//private embedded
		fname1 = "root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb1_MC_1S_official_20201109.root";//official embedded
		//fname1 = "root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb1_MC_1S_non-embed.root";//official non-embedded
	}
	else
	{
		fname1 = "root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb1.root";
	}
	tin->Add(fname1.Data());
//}}}

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//tree variables{{{
	UInt_t eventNb;
	Float_t zVtx;
	ULong64_t HLTriggers;
	Int_t Ntracks;
	Int_t Reco_QQ_size;
	Int_t Reco_QQ_type[MaxQQ];
	Int_t Reco_QQ_sign[MaxQQ];
	Float_t Reco_QQ_VtxProb[MaxQQ];
	ULong64_t Reco_QQ_trig[MaxQQ];
	Float_t Reco_QQ_mupl_dxy[MaxQQ];
	Float_t Reco_QQ_mumi_dxy[MaxQQ];
	Float_t Reco_QQ_mupl_dz[MaxQQ];
	Float_t Reco_QQ_mumi_dz[MaxQQ];
	Bool_t Reco_QQ_mupl_TMOneStaTight[MaxQQ];
	Bool_t Reco_QQ_mumi_TMOneStaTight[MaxQQ];
	Bool_t Reco_QQ_mupl_highPurity[MaxQQ];
	Bool_t Reco_QQ_mumi_highPurity[MaxQQ];
	Int_t Reco_QQ_mupl_nTrkWMea[MaxQQ];
	Int_t Reco_QQ_mumi_nTrkWMea[MaxQQ];
	Int_t Reco_QQ_mupl_nPixWMea[MaxQQ];
	Int_t Reco_QQ_mumi_nPixWMea[MaxQQ];
	TClonesArray* Reco_QQ_4mom;
	TClonesArray* Reco_QQ_mupl_4mom;
	TClonesArray* Reco_QQ_mumi_4mom;
	Reco_QQ_4mom = 0;
	Reco_QQ_mupl_4mom = 0;
	Reco_QQ_mumi_4mom = 0;
	Int_t Reco_trk_size;
	Int_t Reco_trk_charge[MaxTrk];
	Float_t Reco_trk_dxyError[MaxTrk];
	Float_t Reco_trk_dzError[MaxTrk];
	Bool_t Reco_isgoodTrk[MaxTrk];
	Bool_t Reco_isMuTrk[MaxTrk];
	TClonesArray* Reco_trk_4mom;
	Reco_trk_4mom = 0;

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
	TBranch* b_Reco_trk_dxyError;
	TBranch* b_Reco_trk_dzError;
	TBranch* b_Reco_isgoodTrk;
	TBranch* b_Reco_isMuTrk;
	TBranch* b_Reco_trk_4mom;

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
	tin->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
	tin->SetBranchAddress("Ntracks", &Ntracks, &b_Ntracks);
	tin->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
	tin->SetBranchAddress("Reco_QQ_type", &Reco_QQ_type, &b_Reco_QQ_type);
	tin->SetBranchAddress("Reco_QQ_sign", &Reco_QQ_sign, &b_Reco_QQ_sign);
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
	tin->SetBranchAddress("Reco_trk_dxyError", Reco_trk_dxyError, &b_Reco_trk_dxyError);
	tin->SetBranchAddress("Reco_trk_dzError", Reco_trk_dzError, &b_Reco_trk_dzError);
	tin->SetBranchAddress("Reco_isgoodTrk", Reco_isgoodTrk, &b_Reco_isgoodTrk);
	tin->SetBranchAddress("Reco_isMuTrk", Reco_isMuTrk, &b_Reco_isMuTrk);
	tin->SetBranchAddress("Reco_trk_4mom", &Reco_trk_4mom, &b_Reco_trk_4mom);
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
//}}}

//initialize dataset{{{
	DiMuon DMset;
	TTree* tout= new TTree("UpsilonTree", "");
	tout->SetMaxTreeSize(10000000000000);
	DMset.BuildBranch(tout);
//}}}

	const Int_t Nevt = tin->GetEntries();
	Float_t vz = -99.;

	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_pPb1_MupT%s/Sort_OniaTree_pPb1_PADoubleMuon_%s_%s_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), MorD.Data(), SS.Data(), imass), "RECREATE");//same sign
	//TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_pPb1_MupT%s/Sort_OniaTree_pPb1_PADoubleMuon_%s_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), MorD.Data(), imass), "RECREATE");//same sign
	//TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_pPb1_MupT%s/Sort_OniaTree_pPb1_PADoubleMuon_%s_nonemb_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), MorD.Data(), imass), "RECREATE");//nen-embedded MC sample

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	//for(Int_t ievt = 0; ievt < 100000; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)(ievt)/(double)(Nevt)*100)) << " %]" << endl;
		tin->GetEntry(ievt);

		DMset.clear();

		Int_t NtrgReco = 0;
		Int_t NassReco = 0;
		Bool_t is_inMassReco = false;
		Bool_t has_AssoReco = false;

		Int_t NtrgGen = 0;
		Int_t NassGen = 0;
		Bool_t is_inMassGen = false;
		Bool_t has_AssoGen = false;

		if(Ntracks >= multMin && Ntracks < multMax)
		{
			vz = zVtx;

			if( (HLTriggers&1)!=1 ) continue;

//Get trigger vector{{{
			for(Int_t iqq = 0; iqq < Reco_QQ_size; iqq++)
			{
				Up_Reco_4mom = (TLorentzVector*) Reco_QQ_4mom->At(iqq);
				mupl_Reco_4mom = (TLorentzVector*) Reco_QQ_mupl_4mom->At(iqq);
				mumi_Reco_4mom = (TLorentzVector*) Reco_QQ_mumi_4mom->At(iqq);

				if( Up_Reco_4mom->M() > 8+(0.05*imass) && Up_Reco_4mom->M() <= 8+(0.05*(imass+1)) && Up_Reco_4mom->Rapidity() >= -2.4 && Up_Reco_4mom->Rapidity() <= 2.4 && Up_Reco_4mom->Pt() >= ptMin && Up_Reco_4mom->Pt() < ptMax)
				{
//Cuts for muon and Upsilon{{{
					if( (Reco_QQ_trig[iqq]&1)!=1 ) continue;
					if( !InAcc(mupl_Reco_4mom->Pt(), mupl_Reco_4mom->Eta(), MupTCut) ) continue;
					if( !InAcc(mumi_Reco_4mom->Pt(), mumi_Reco_4mom->Eta(), MupTCut) ) continue;
					bool muplSoft = ( (Reco_QQ_mupl_TMOneStaTight[iqq]) &&
											(Reco_QQ_mupl_nTrkWMea[iqq] > 5) &&
											(Reco_QQ_mupl_nPixWMea[iqq] > 0) &&
											(Reco_QQ_mupl_dxy[iqq] < 0.3) &&
											(Reco_QQ_mupl_dz[iqq] < 20.) &&
											(Reco_QQ_mupl_highPurity[iqq]==true) );
					bool mumiSoft = ( (Reco_QQ_mumi_TMOneStaTight[iqq]) &&
											(Reco_QQ_mumi_nTrkWMea[iqq] > 5) &&
											(Reco_QQ_mumi_nPixWMea[iqq] > 0) &&
											(Reco_QQ_mumi_dxy[iqq] < 0.3) &&
											(Reco_QQ_mumi_dz[iqq] < 20.) &&
											(Reco_QQ_mumi_highPurity[iqq]==true) );
					if( !(muplSoft && mumiSoft) ) continue;
					if( Reco_QQ_VtxProb[iqq] < 0.01 ) continue;
					if( (!isSS && (Reco_QQ_sign[iqq] != 0)) || (isSS && (Reco_QQ_sign[iqq] == 0)) ) continue;
//}}}

					new( (*DMset.Vec_trg_Reco)[NtrgReco] )TLorentzVector(*Up_Reco_4mom);
					NtrgReco++;
					is_inMassReco = true;
				}
			}
//}}}

//Get associator vector{{{
			if(is_inMassReco)
			{
				for(Int_t itrk = 0; itrk < Reco_trk_size; itrk++)
				{
					Trk_Reco_4mom = (TLorentzVector*) Reco_trk_4mom->At(itrk);
					TVector3 Trk_vector;
	
					if(Trk_Reco_4mom->Eta() <= 2.4 && Trk_Reco_4mom->Eta() >= -2.4 && Reco_isgoodTrk[itrk] && !Reco_isMuTrk[itrk] && Trk_Reco_4mom->Pt() >= TrkptMin && Trk_Reco_4mom->Pt() < TrkptMax && Trk_Reco_4mom->Pt() > 0.3)
					{
						new( (*DMset.Vec_ass_Reco)[NassReco] )TLorentzVector(*Trk_Reco_4mom);
						NassReco++;
					}
				}
			}
//}}}
		}
		if( is_inMassReco && (NassReco != 0) )
		{
			DMset.Ntrg_Reco = NtrgReco;
			DMset.Nass_Reco = NassReco;
			DMset.zVtx = vz;
			DMset.mult = Ntracks;
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
