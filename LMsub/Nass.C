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

void Nass(const bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TString trackptversion = "v1", const TString MupT = "4", const bool Weight = false)
{
	SetStyle();

//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/Plots/Nass");
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";

//Get files{{{
	TString fname1, fname2, fname3, fname4;
	TChain* tin1_tmp = new TChain("UpsilonTree");
	for(Int_t ibin = 0; ibin < 120; ibin++)
	{
		fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp1_PADoubleMuon_%s_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), MorD.Data(), ibin);
		fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp2_PADoubleMuon_%s_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), MorD.Data(), ibin);
		fname3 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_%s_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), MorD.Data(), ibin);
		fname4 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_%s_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), MorD.Data(), ibin);
		tin1_tmp->Add(fname1.Data());
		tin1_tmp->Add(fname2.Data());
		tin1_tmp->Add(fname3.Data());
		tin1_tmp->Add(fname4.Data());
	}
	TTree* tin1 = tin1_tmp->CloneTree();
	tin1_tmp->Reset();

	TFile* facc = new TFile("../AccEff/Plots/test_acc_upsi_816.root", "READ");
	TFile* feff = new TFile("../AccEff/Plots/EffPlots_Upsilon_1S_Ny5_MupT3p5.root", "READ");
	TFile* ftrk = new TFile("../AccEff/Plots/Hijing_8TeV_dataBS.root", "READ");
//}}}

//Get weighting factor{{{
	const Int_t Ny = 4;
	const Double_t ybin[Ny+1] = {0.0, 1.6, 1.8, 2.1, 2.4};
	const TString yabin[Ny+1] = {"00", "16", "18", "21", "24"};
	TH1D* hacc[Ny];
	TH1D* heff[Ny];
	for(Int_t iy = 0; iy < Ny; iy++)
	{
		hacc[iy] = (TH1D*) facc->Get(Form("hAccPt%s%s", yabin[iy].Data(), yabin[iy+1].Data()));
		heff[iy] = (TH1D*) feff->Get(Form("hEff_%d", iy));
	}
	TH2D* htrk = (TH2D*) ftrk->Get("rTotalEff3D_0");
//}}}

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* h1 = new TH1D("h1", ";Nass;Counts", 300, 0, 300);
	FormTH1Marker(h1, 0, 0, 1.4);
	gStyle->SetOptStat("M");

//get variables{{{
	Int_t mult;
	Int_t Nass_Reco;

	TBranch* b_mult;
	TBranch* b_Nass_Reco;

	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("Nass_Reco", &Nass_Reco, &b_Nass_Reco);
//}}}

	const Int_t Nevt = tin1->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);
		h1->Fill(Nass_Reco);
	}

//Draw{{{
	c1->cd();
	h1->Draw("pe");
	c1->SaveAs(Form("Plots/Nass/Nass_dist_%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_%s.pdf", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), MorD.Data()));
//}}}

	TFile* fout = new TFile(Form("Plots/Nass/Nass_dist_%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), MorD.Data()), "RECREATE");
	fout->cd();
	h1->Write();
	fout->Close();
}
