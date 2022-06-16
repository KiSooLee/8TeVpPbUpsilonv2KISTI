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
#include <TRandom3.h>
#include <TSystem.h>
/*
#include "Style_Upv2.h"
#include "Upsilon.h"
*/
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"

using namespace std;
//}}}

void Collect_Reco_pPb1(const bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString MupT = "4", const TString trkptversion = "v1", const Bool_t isSS = false, const Int_t imass = 0)
{
//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_pPb1_MupT%s_trk%s", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data());
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString SS;
	if(isSS) SS = "SS";//same sign
	else SS = "OS";//opposite sign

//Get files{{{
	TString fname1;
	fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/total_MupT%s/Sort_OniaTree_pPb1_PADoubleMuon_%s_%s_%d.root", MupT.Data(), MorD.Data(), SS.Data(), imass);
	//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/total_MupT%s/Sort_OniaTree_pPb1_PADoubleMuon_%s_%d_nonemb.root", MupT.Data(), MorD.Data(), imass);//non-embedded MC sample
	//fname1 = Form("0-1500_0-30_-24-24_0-10_pPb1/Sort_OniaTree_pPb1_PADoubleMuon_%s_%d.root", MorD.Data(), imass);
	TChain* tin1_tmp = new TChain("UpsilonTree");
	tin1_tmp->Add(fname1.Data());

	TTree* tin1 = tin1_tmp->CloneTree();
	tin1_tmp->Reset();
//}}}

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//get variables{{{
	Int_t mult;
	Float_t zVtx;
	Int_t Ntrg_Reco;
	Int_t Nass_Reco;
	TClonesArray* Vec_trg_Reco;
	TClonesArray* Vec_ass_Reco;
	Vec_trg_Reco = 0;
	Vec_ass_Reco = 0;

	TBranch* b_mult;
	TBranch* b_zVtx;
	TBranch* b_Ntrg_Reco;
	TBranch* b_Nass_Reco;
	TBranch* b_Vec_trg_Reco;
	TBranch* b_Vec_ass_Reco;

	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("zVtx", &zVtx, &b_zVtx);
	tin1->SetBranchAddress("Ntrg_Reco", &Ntrg_Reco, &b_Ntrg_Reco);
	tin1->SetBranchAddress("Nass_Reco", &Nass_Reco, &b_Nass_Reco);
	tin1->SetBranchAddress("Vec_trg_Reco", &Vec_trg_Reco, &b_Vec_trg_Reco);
	tin1->SetBranchAddress("Vec_ass_Reco", &Vec_ass_Reco, &b_Vec_ass_Reco);

	TLorentzVector* vec_trg_Reco = new TLorentzVector;
	TLorentzVector* vec_ass_Reco = new TLorentzVector;
	vec_trg_Reco = 0;
	vec_ass_Reco = 0;
//}}}

	const Int_t Nevt = tin1->GetEntries();

//initialize dataset{{{
	DiMuon DMset;
	TTree* tout = new TTree("UpsilonTree", "");
	tout->SetMaxTreeSize(10000000000000);
	DMset.BuildBranch(tout);
//}}}

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);
		DMset.clear();
		Int_t TrueNtrgReco = 0;
		Int_t TrueNassReco = 0;

		if(multMin <= mult && mult < multMax)
		{
//Get collected trig{{{
			for(Int_t itrg = 0; itrg < Ntrg_Reco; itrg++)
			{
				vec_trg_Reco = (TLorentzVector*) Vec_trg_Reco->At(itrg);
				if(vec_trg_Reco == 0) continue;
				Double_t trg_pt = vec_trg_Reco->Pt();
				Double_t trg_y = vec_trg_Reco->Rapidity();

				if(ptMin <= vec_trg_Reco->Pt() && vec_trg_Reco->Pt() < ptMax && rapMin <= vec_trg_Reco->Rapidity() && vec_trg_Reco->Rapidity() < rapMax)
				{
					new ( (*DMset.Vec_trg_Reco)[TrueNtrgReco] )TLorentzVector(*vec_trg_Reco);
					TrueNtrgReco++;
				}
			}
//}}}

//Get collected associator{{{
			if(TrueNtrgReco != 0)
			{
				for(Int_t itrk = 0; itrk < Nass_Reco; itrk++)
				{
					vec_ass_Reco = (TLorentzVector*) Vec_ass_Reco->At(itrk);
					if(vec_ass_Reco == 0) continue;
					Double_t TrkptMintmp = 0.;
					if(TrkptMin == 0)
					{
						if(trkptversion == "v1") TrkptMintmp = 0.3;
						else if(trkptversion == "v2") TrkptMintmp = 0.4;
						else if(trkptversion == "v3") TrkptMintmp = 0.5;
					}
					else TrkptMintmp = TrkptMin;
					if(vec_ass_Reco->Pt() >= TrkptMintmp && vec_ass_Reco->Pt() < TrkptMax)
					{
						new ( (*DMset.Vec_ass_Reco)[TrueNassReco] )TLorentzVector(*vec_ass_Reco);
						TrueNassReco++;
					}
				}
			}
//}}}
		}
		if(TrueNtrgReco != 0 && TrueNassReco != 0 && zVtx > -99)
		{
			DMset.Ntrg_Reco = TrueNtrgReco;
			DMset.Nass_Reco = TrueNassReco;
			DMset.zVtx = zVtx;
			DMset.mult = mult;
			tout->Fill();
		}
	}
//store{{{
	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_pPb1_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_%s_%s_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), SS.Data(), imass), "RECREATE");
	fout->cd();
	tout->Write();
	fout->Close();
//}}}
}
