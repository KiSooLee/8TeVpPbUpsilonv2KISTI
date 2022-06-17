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
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"

using namespace std;
//}}}

void Nass(const bool isMC = false, const bool isGen = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TString trackptversion = "v1", const TString MupT = "4")
{
	SetStyle();

//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/Plots/Nass");
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

	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString RorG;
	if(isGen) RorG = "Gen";
	else RorG = "Reco";

	TString RorGsf;
	if(isMC)
	{
		if (isGen) RorGsf = "_Gen";
		else RorGsf = "_Reco";
	}
	else RorGsf = "";

//Get files{{{
	TString fname1, fname2, fname3, fname4;
	TChain* tin1_tmp = new TChain("UpsilonTree");
	Int_t binmin;
	Int_t binmax;
	if (!isMC)
	{
		binmin = 0;
		binmax = 120;
	}
	else if (!isGen)
	{
		binmin = 10;
		binmax = 40;
	}
	else
	{
		binmin = 0;
		binmax = 1;
	}
	for(Int_t ibin = binmin; ibin < binmax; ibin++)
	{
		if (isGen)
		{
			fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_%s_Pbp1_PADoubleMuon_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), RorG.Data(), MorD.Data());
			fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_%s_Pbp2_PADoubleMuon_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), RorG.Data(), MorD.Data());
			fname3 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_%s_pPb1_PADoubleMuon_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), RorG.Data(), MorD.Data());
			fname4 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_%s_pPb2_PADoubleMuon_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), RorG.Data(), MorD.Data());
		}
		else
		{
			//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_%s_Pbp1_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), RorG.Data(), MorD.Data(), ibin);//storage
			//fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_%s_Pbp2_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), RorG.Data(), MorD.Data(), ibin);//storage
			//fname3 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_%s_pPb1_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), RorG.Data(), MorD.Data(), ibin);//storage
			//fname4 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_%s_pPb2_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), RorG.Data(), MorD.Data(), ibin);//storage
			fname1 = Form("/cms/scratch/kilee/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp1_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), MorD.Data(), ibin);//scratch
			fname2 = Form("/cms/scratch/kilee/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp2_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), MorD.Data(), ibin);//scratch
			fname3 = Form("/cms/scratch/kilee/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp1_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), MorD.Data(), ibin);//scratch
			fname4 = Form("/cms/scratch/kilee/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp2_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trackptversion.Data(), MorD.Data(), ibin);//scratch
		}
		tin1_tmp->Add(fname1.Data());
		tin1_tmp->Add(fname2.Data());
		tin1_tmp->Add(fname3.Data());
		tin1_tmp->Add(fname4.Data());
	}
	TTree* tin1 = tin1_tmp->CloneTree();
	tin1_tmp->Reset();

	TFile* ftrk = new TFile("../AccEff/Plots/Hijing_8TeV_dataBS.root", "READ");
	TH2D* htrk = (TH2D*) ftrk->Get("rTotalEff3D_0");
//}}}

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* h1 = new TH1D("h1", ";Nass;Counts", 300, 0, 300);
	FormTH1Marker(h1, 0, 0, 1.4);
	gStyle->SetOptStat("M");

//get variables{{{
	Int_t mult;
	Int_t Nass_Reco;
	Int_t Nass_Gen;

	TBranch* b_mult;
	TBranch* b_Nass_Reco;
	TBranch* b_Nass_Gen;

	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("Nass_Reco", &Nass_Reco, &b_Nass_Reco);
	if (isGen) tin1->SetBranchAddress("Nass_Gen", &Nass_Gen, &b_Nass_Gen);
//}}}

	const Int_t Nevt = tin1->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);
		if (isGen) h1->Fill(Nass_Gen);
		else h1->Fill(Nass_Reco);
	}

//Draw{{{
	c1->cd();
	h1->Draw("pe");
	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 42, 0.04);
	lt1->DrawLatex(0.7,0.83, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
	lt1->DrawLatex(0.7,0.76, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int)ptMin, (int)ptMax));
	lt1->DrawLatex(0.7,0.69, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.7,0.62, Form("Mean: %.0f", h1->GetMean()));
	c1->SaveAs(Form("Plots/Nass/Nass_dist_%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_%s%s.pdf", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), MorD.Data(), RorGsf.Data()));
//}}}

	TFile* fout = new TFile(Form("Plots/Nass/Nass_dist_%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_%s%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), MorD.Data(), RorGsf.Data()), "RECREATE");
	fout->cd();
	h1->Write();
	fout->Close();
}
