//Headers{{{
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

using namespace std;
//}}}

void mCorrel_trk_sig_pPb(bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1", const Int_t imass = 0)
{
//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_%s", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data());
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//Get files{{{
	TString fname1, fname2;
	TChain* tin1 = new TChain("UpsilonTree");
	for(Int_t ibin = massBinsArr[imass]; ibin < massBinsArr[imass+1]; ibin++)
	{
		fname1 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d/Sort_OniaTree_pPb1_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, ibin);
		fname2 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d/Sort_OniaTree_pPb2_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, ibin);
		tin1->Add(fname1.Data());
		tin1->Add(fname2.Data());
	}
//}}}

//Make plots{{{
	Int_t Netabin1 = 32;
	Int_t Nphibin1 = 32;
	TCanvas* c1_1 = new TCanvas("c1_1", "", 0, 0, 600, 600);
	TCanvas* c2_1 = new TCanvas("c2_1", "", 0, 0, 600, 600);
	TCanvas* c3_1 = new TCanvas("c3_1", "", 0, 0, 600, 600);
	TCanvas* c4_1 = new TCanvas("c4_1", "", 0, 0, 600, 600);
	TH2D* h1_1 = new TH2D("hSigpPb1_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1,-4.95,4.95,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* h2_1 = new TH2D("hSigpPb2_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1,-4.95,4.95,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* h3_1 = new TH2D("hSigpPb3_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1,-4.95,4.95,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* h4_1 = new TH2D("hSigpPb4_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1,-4.95,4.95,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	FormTH2(h1_1);
	FormTH2(h2_1);
	FormTH2(h3_1);
	FormTH2(h4_1);
//}}}

//get variables{{{
	Int_t Nass;
	Double_t mult;
	TClonesArray* Vec_ass;
	Vec_ass = 0;

	TBranch* b_Nass;
	TBranch* b_mult;
	TBranch* b_Vec_ass;

	tin1->SetBranchAddress("Nass", &Nass, &b_Nass);
	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("Vec_ass", &Vec_ass, &b_Vec_ass);

	TLorentzVector* vec_trk1 = new TLorentzVector;
	TLorentzVector* vec_trk2 = new TLorentzVector;
	vec_trk1 = 0;
	vec_trk2 = 0;
//}}}

	const Int_t Nevt = tin1->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);

//signal{{{
		for(Int_t itrk1 = 0; itrk1 < Nass; itrk1++)
		{
			vec_trk1 = (TLorentzVector*) Vec_ass->At(itrk1);
			if(vec_trk1 == 0) continue;
			Double_t trg_eta_tmp = vec_trk1->Eta();
			Double_t trg_phi_tmp = vec_trk1->Phi();

			for(Int_t itrk2 = 0; itrk2 < Nass; itrk2++)
			{
				if(itrk1 == itrk2) continue;
				vec_trk2 = (TLorentzVector*) Vec_ass->At(itrk2);
				if(vec_trk2 == 0) continue;
				Double_t ass_eta = vec_trk2->Eta();
				Double_t ass_phi = vec_trk2->Phi();
				Double_t deta = ass_eta - trg_eta_tmp;
				Double_t dphi = ass_phi - trg_phi_tmp;
				if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
				if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
				if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
				h1_1->Fill(deta, dphi, 1/( (double)Nass*2) );
				if(fabs(deta) > 2.0)
				{
					h2_1->Fill(deta, dphi, 1/( (double)Nass*2) );
				}
				if(fabs(deta) > 1.5)
				{
					h3_1->Fill(deta, dphi, 1/( (double)Nass*2) );
				}
				if(fabs(deta) > 1.0)
				{
					h4_1->Fill(deta, dphi, 1/( (double)Nass*2) );
				}
			}
		}
//}}}
	}

//Draw{{{
	c1_1->cd();
	h1_1->Draw("Surf1");
	c2_1->cd();
	h2_1->Draw("Surf1");
	c3_1->cd();
	h3_1->Draw("Surf1");
	c4_1->cd();
	h4_1->Draw("Surf1");
//}}}

//store{{{
	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s/trk_deta-dphi_pPb_distribution_sig_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "RECREATE");
	fout->cd();
	h1_1->Write();
	h2_1->Write();
	h3_1->Write();
	h4_1->Write();
	fout->Close();
//}}}
}
