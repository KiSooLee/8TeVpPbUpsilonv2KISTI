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
#include "Style_Upv2.h"
#include "Upsilon.h"
/*
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
*/
using namespace std;
//}}}

void Collect_pPb2(bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString MupT = "4", const Int_t imass = 0)
{
//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_pPb2", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax);
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//Get files{{{
	TString fname1;
	TChain* tin1 = new TChain("UpsilonTree");
	fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/total_MupT%s/Sort_OniaTree_pPb2_PADoubleMuon_%d.root", MupT.Data(), imass);
	tin1->Add(fname1.Data());
//}}}

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//get variables{{{
	Int_t Ntrg;
	Int_t Nass;
	Double_t mult;
	Float_t zVtx;
	TClonesArray* Vec_trg;
	TClonesArray* Vec_ass;
	Vec_trg = 0;
	Vec_ass = 0;

	TBranch* b_Ntrg;
	TBranch* b_Nass;
	TBranch* b_mult;
	TBranch* b_zVtx;
	TBranch* b_Vec_trg;
	TBranch* b_Vec_ass;

	tin1->SetBranchAddress("Ntrg", &Ntrg, &b_Ntrg);
	tin1->SetBranchAddress("Nass", &Nass, &b_Nass);
	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("zVtx", &zVtx, &b_zVtx);
	tin1->SetBranchAddress("Vec_trg", &Vec_trg, &b_Vec_trg);
	tin1->SetBranchAddress("Vec_ass", &Vec_ass, &b_Vec_ass);

	TLorentzVector* vec_trg = new TLorentzVector;
	TLorentzVector* vec_ass = new TLorentzVector;
	vec_trg = 0;
	vec_ass = 0;
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
		Int_t TrueNtrg = 0;
		Int_t TrueNass = 0;

		if(multMin <= mult && mult < multMax)
		{
//Get collected trig{{{
			for(Int_t itrg = 0; itrg < Ntrg; itrg++)
			{
				vec_trg = (TLorentzVector*) Vec_trg->At(itrg);
				if(vec_trg == 0) continue;
				Double_t trg_pt = vec_trg->Pt();
				Double_t trg_y = vec_trg->Rapidity();

				if(ptMin <= vec_trg->Pt() && vec_trg->Pt() < ptMax && rapMin <= vec_trg->Rapidity() && vec_trg->Rapidity() < rapMax)
				{
					new ( (*DMset.Vec_trg)[TrueNtrg] )TLorentzVector(*vec_trg);
					TrueNtrg++;
				}
			}
//}}}

//Get collected associator{{{
			if(TrueNtrg != 0)
			{
				for(Int_t itrk = 0; itrk < Nass; itrk++)
				{
					vec_ass = (TLorentzVector*) Vec_ass->At(itrk);
					if(vec_ass == 0) continue;
					Double_t TrkptMintmp = 0.;
					if(TrkptMin == 0) TrkptMintmp = 0.3;
					else TrkptMintmp = TrkptMin;
					if(vec_ass->Pt() >= TrkptMintmp && vec_ass->Pt() < TrkptMax)
					{
						new ( (*DMset.Vec_ass)[TrueNass] )TLorentzVector(*vec_ass);
						TrueNass++;
					}
				}
			}
//}}}
		}
		if(TrueNtrg != 0 && TrueNass != 0 && zVtx > -98)
		{
			DMset.Ntrg = TrueNtrg;
			DMset.Nass = TrueNass;
			DMset.mult = mult;
			DMset.zVtx = zVtx;
			tout->Fill();
		}
	}
//store{{{
	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_pPb2/Sort_OniaTree_pPb2_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, imass), "RECREATE");
	fout->cd();
	tout->Write();
	fout->Close();
//}}}
}
