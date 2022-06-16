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

void Collect_Gen_pPb2(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString MupT = "4", const TString trkptversion = "v1")
{
//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_pPb2_MupT%s_trk%s", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data());
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//Get files{{{
	TString fname1;
	TChain* tin1 = new TChain("UpsilonTree");
	fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/total_MupT%s/Sort_OniaTree_pPb2_PADoubleMuon_MC_Gen.root", MupT.Data());
	//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/total_MupT%s/Sort_OniaTree_pPb2_PADoubleMuon_MC_%d_nonemb.root", MupT.Data(), imass);
	tin1->Add(fname1.Data());
//}}}

//get variables{{{
	Int_t mult;
	Float_t zVtx;
	Int_t Ntrg_Gen;
	Int_t Nass_Gen;
	TClonesArray* Vec_trg_Gen;
	TClonesArray* Vec_ass_Gen;
	Vec_trg_Gen = 0;
	Vec_ass_Gen = 0;

	TBranch* b_mult;
	TBranch* b_zVtx;
	TBranch* b_Ntrg_Gen;
	TBranch* b_Nass_Gen;
	TBranch* b_Vec_trg_Gen;
	TBranch* b_Vec_ass_Gen;

	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("zVtx", &zVtx, &b_zVtx);
	tin1->SetBranchAddress("Ntrg_Gen", &Ntrg_Gen, &b_Ntrg_Gen);
	tin1->SetBranchAddress("Nass_Gen", &Nass_Gen, &b_Nass_Gen);
	tin1->SetBranchAddress("Vec_trg_Gen", &Vec_trg_Gen, &b_Vec_trg_Gen);
	tin1->SetBranchAddress("Vec_ass_Gen", &Vec_ass_Gen, &b_Vec_ass_Gen);

	TLorentzVector* vec_trg_Gen = new TLorentzVector;
	TLorentzVector* vec_ass_Gen = new TLorentzVector;
	vec_trg_Gen = 0;
	vec_ass_Gen = 0;
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

		Int_t TrueNtrgGen = 0;
		Int_t TrueNassGen = 0;

		if(multMin <= mult && mult < multMax)
		{
//Get collected GEN trigger{{{
			for(Int_t itrg = 0; itrg < Ntrg_Gen; itrg++)
			{
				vec_trg_Gen = (TLorentzVector*) Vec_trg_Gen->At(itrg);
				if(vec_trg_Gen == 0) continue;
				Double_t trg_pt = vec_trg_Gen->Pt();
				Double_t trg_y = vec_trg_Gen->Rapidity();
	
				if(ptMin <= trg_pt && trg_pt < ptMax && rapMin <= trg_y && trg_y < rapMax)
				{
					new ( (*DMset.Vec_trg_Gen)[TrueNtrgGen] )TLorentzVector(*vec_trg_Gen);
					TrueNtrgGen++;
				}
			}
//}}}

//Get collected GEN associator{{{
			if(TrueNtrgGen != 0)
			{
				for(Int_t itrk = 0; itrk < Nass_Gen; itrk++)
				{
					vec_ass_Gen = (TLorentzVector*) Vec_ass_Gen->At(itrk);
					if(vec_ass_Gen == 0) continue;
					Double_t TrkptMintmp = 0.;
					if(TrkptMin == 0)
					{
						if(trkptversion == "v1") TrkptMintmp = 0.3;
						else if(trkptversion == "v2") TrkptMintmp = 0.4;
						else if(trkptversion == "v3") TrkptMintmp = 0.5;
					}
					else TrkptMintmp = TrkptMin;
		
					if(vec_ass_Gen->Pt() >= TrkptMintmp && vec_ass_Gen->Pt() < TrkptMax)
					{
						new ( (*DMset.Vec_ass_Gen)[TrueNassGen] )TLorentzVector(*vec_ass_Gen);
						TrueNassGen++;
					}
				}
			}
//}}}
		}
		if(TrueNtrgGen != 0 && TrueNassGen != 0)
		{
			DMset.Ntrg_Gen = TrueNtrgGen;
			DMset.Nass_Gen = TrueNassGen;
			DMset.zVtx = zVtx;
			DMset.mult = mult;
			tout->Fill();
		}
	}
//store{{{
	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_pPb2_MupT%s_trk%s/Sort_OniaTree_Gen_pPb2_PADoubleMuon_MC.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data()), "RECREATE");
	fout->cd();
	tout->Write();
	fout->Close();
//}}}
}
