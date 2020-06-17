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

void mult(const bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString MupT = "4", const Int_t imass = 0)
{
//Get files{{{
	TString fname1;
	TChain* tin1 = new TChain("UpsilonTree");
	for(Int_t imass = 0; imass < 120; imass++)
	{
		fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/total_MupT%s/Sort_OniaTree_Pbp1_PADoubleMuon_Data_%d.root", MupT.Data(), imass);
		tin1->Add(fname1.Data());
	}
//}}}

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

	Int_t mult;
	TBranch* b_mult;
	tin1->SetBranchAddress("mult", &mult, &b_mult);

	const Int_t Nevt = tin1->GetEntries();

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* h1 = new TH1D("h1", "", 300, 0, 300);
	TH1D* h2 = new TH1D("h2", "", 300, 0, 300);

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		tin1->GetEntry(ievt);
		h1->Fill(mult);
		if(mult > 110) h2->Fill(mult);
	}
	c1->cd();
	h1->Draw();
	h2->Draw();
	c1->SaveAs("multiplicity_sample.pdf");
	cout << "total count: " << h1->Integral() << endl;
	cout << "high count: " << h2->Integral() << endl;
	cout << "ratio: " << h2->Integral()/h1->Integral() << endl;
}
