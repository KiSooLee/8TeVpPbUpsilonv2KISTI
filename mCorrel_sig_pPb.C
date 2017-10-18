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
#include "Style_Kisoo.h"
#include "Upsilon.h"

using namespace std;
//}}}

void mCorrel_sig_pPb(bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1", const Int_t imass = 0, const Int_t nmbin = 120)
{
/*
//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/SigCorr";
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}
*/
	TString DM;
	if(isMC) DM = "MC";
	else DM = "RD";

//Get files{{{
	TString fname1, fname2;
	TChain* tin1 = new TChain("UpsilonTree");
	for(Int_t ibin = 0; ibin < 120/nmbin; ibin++)
	{
		//fname1 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/Sort_OniaTree_pPb1_PADoubleMuon_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%d.root", DM.Data(), (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), imass*(120/nmbin)+ibin);
		//fname2 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/Sort_OniaTree_pPb2_PADoubleMuon_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%d.root", DM.Data(), (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), imass*(120/nmbin)+ibin);
		fname1 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/Sort_OniaTree_pPb1_PADoubleMuon_RD_Mult_0-1500_pt_0-500_rap_-24-24_Trkpt_0-100_v1_%d.root", imass*(120/nmbin)+ibin);
		fname2 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/Sort_OniaTree_pPb2_PADoubleMuon_RD_Mult_0-1500_pt_0-500_rap_-24-24_Trkpt_0-100_v1_%d.root", imass*(120/nmbin)+ibin);
		tin1->Add(fname1.Data());
		tin1->Add(fname2.Data());
	}
//}}}

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//Make plots{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
	TCanvas* c3 = new TCanvas("c3", "", 0, 0, 600, 600);
	TH2D* h1 = new TH2D("h1", ";#Delta#eta;#Delta#phi", Netabin,-4.95,4.95,Nphibin,-(0.5-1.0/((double)(Nphibin+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin+1)))*TMath::Pi());
	TH2D* h2 = new TH2D("h2", ";#Delta#eta;#Delta#phi", Netabin,-4.95,4.95,Nphibin,-(0.5-1.0/((double)(Nphibin+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin+1)))*TMath::Pi());
	TH2D* h3 = new TH2D("h3", ";#Delta#eta;#Delta#phi", Netabin,-4.95,4.95,Nphibin,-(0.5-1.0/((double)(Nphibin+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin+1)))*TMath::Pi());
	FormTH2(h1);
	FormTH2(h2);
	FormTH2(h3);
//}}}

//get variables{{{
	Int_t Ntrg;
	Int_t Nass;
	Double_t mult;
	TClonesArray* Vec_trg;
	TClonesArray* Vec_ass;
	Vec_trg = 0;
	Vec_ass = 0;

	TBranch* b_Ntrg;
	TBranch* b_Nass;
	TBranch* b_mult;
	TBranch* b_Vec_trg;
	TBranch* b_Vec_ass;

	tin1->SetBranchAddress("Ntrg", &Ntrg, &b_Ntrg);
	tin1->SetBranchAddress("Nass", &Nass, &b_Nass);
	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("Vec_trg", &Vec_trg, &b_Vec_trg);
	tin1->SetBranchAddress("Vec_ass", &Vec_ass, &b_Vec_ass);

	TLorentzVector* vec_trg = new TLorentzVector;
	TLorentzVector* vec_ass = new TLorentzVector;
	vec_trg = 0;
	vec_ass = 0;
//}}}

	const Int_t Nevt = tin1->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);

		if(multMin <= mult < multMax)
		{
//peak Correlate{{{
			for(Int_t itrg = 0; itrg < Ntrg; itrg++)
			{
				vec_trg = (TLorentzVector*) Vec_trg->At(itrg);
				Double_t trg_eta = vec_trg->Eta();
				Double_t trg_phi = vec_trg->Phi();
				Double_t trg_pt = vec_trg->Pt();

				if(ptMin <= trg_pt < ptMax)
				{
//signal{{{
					for(Int_t itrk = 0; itrk < Nass; itrk++)
					{
						vec_ass = (TLorentzVector*) Vec_ass->At(itrk);
						Double_t ass_pt = vec_ass->Pt();
	
						if(TrkptMin <= ass_pt < TrkptMax)
						{
							Double_t ass_eta = vec_ass->Eta();
							Double_t ass_phi = vec_ass->Phi();
							Double_t deta = ass_eta - trg_eta;
							Double_t dphi = ass_phi - trg_phi;
							if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
							if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
							if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
							h1->Fill(deta, dphi, 1/(double)Ntrg);
							if(fabs(deta) > 2.0) h2->Fill(deta, dphi, 1/(double)Ntrg);
							if(fabs(deta) > 1.0) h3->Fill(deta, dphi, 1/(double)Ntrg);
						}
					}
//}}}
				}
			}
//}}}
		}
	}

	c1->cd();
	h1->Draw("Surf1");
	c2->cd();
	h2->Draw("Surf1");
	c3->cd();
	h3->Draw("Surf1");

	TFile* fout = new TFile(Form("deta-dphi_pPb_distribution_sig_%d.root", imass), "RECREATE");
	fout->cd();
	h1->Write();
	h2->Write();
	h3->Write();
	fout->Close();
}
