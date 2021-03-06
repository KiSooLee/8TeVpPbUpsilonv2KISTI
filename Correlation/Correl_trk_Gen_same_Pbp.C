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

void Correl_trk_Gen_same_Pbp(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TString MupT = "4", const TString trkptversion = "v1")
{
	SetStyle();

//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data());
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//Get files{{{
	TString fname1, fname2;
	TChain* tin1_tmp = new TChain("UpsilonTree");
	//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Gen_Pbp1_PADoubleMuon_MC_29.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data());
	//fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Gen_Pbp2_PADoubleMuon_MC_29.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data());
	fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Gen_Pbp1_PADoubleMuon_MC_29_nonemb.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data());
	fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Gen_Pbp2_PADoubleMuon_MC_29_nonemb.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data());
	tin1_tmp->Add(fname1.Data());
	tin1_tmp->Add(fname2.Data());
	TTree* tin1 = tin1_tmp->CloneTree();
	tin1_tmp->Reset();
//}}}

//Define canvas & hist{{{
	const Int_t Netabin1 = 32;
	const Int_t Nphibin1 = 32;
	const Int_t Netabin2 = 16;
	const Int_t Nphibin2 = 16;

	TCanvas* cGen1_1 = new TCanvas("cGen1_1", "", 0, 0, 600, 600);
	TCanvas* cGen1_2 = new TCanvas("cGen1_2", "", 0, 0, 600, 600);
	TCanvas* cGen2_1 = new TCanvas("cGen2_1", "", 0, 0, 600, 600);
	TCanvas* cGen2_2 = new TCanvas("cGen2_2", "", 0, 0, 600, 600);
	TCanvas* cGen3_1 = new TCanvas("cGen3_1", "", 0, 0, 600, 600);
	TCanvas* cGen3_2 = new TCanvas("cGen3_2", "", 0, 0, 600, 600);
	TCanvas* cGen4_1 = new TCanvas("cGen4_1", "", 0, 0, 600, 600);
	TCanvas* cGen4_2 = new TCanvas("cGen4_2", "", 0, 0, 600, 600);
	TCanvas* cGen5_1 = new TCanvas("cGen5_1", "", 0, 0, 600, 600);
	TCanvas* cGen5_2 = new TCanvas("cGen5_2", "", 0, 0, 600, 600);

	TH2D* hGen1_1 = new TH2D("hSamePbpGen1_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hGen1_2 = new TH2D("hSamePbpGen1_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hGen2_1 = new TH2D("hSamePbpGen2_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hGen2_2 = new TH2D("hSamePbpGen2_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hGen3_1 = new TH2D("hSamePbpGen3_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hGen3_2 = new TH2D("hSamePbpGen3_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hGen4_1 = new TH2D("hSamePbpGen4_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hGen4_2 = new TH2D("hSamePbpGen4_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hGen5_1 = new TH2D("hSamePbpGen5_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hGen5_2 = new TH2D("hSamePbpGen5_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());

	FormTH2(hGen1_1);
	FormTH2(hGen1_2);
	FormTH2(hGen2_1);
	FormTH2(hGen2_2);
	FormTH2(hGen3_1);
	FormTH2(hGen3_2);
	FormTH2(hGen4_1);
	FormTH2(hGen4_2);
	FormTH2(hGen5_1);
	FormTH2(hGen5_2);
//}}}

//get variables{{{
	Int_t mult;
	Int_t Nass_Gen;
	TClonesArray* Vec_ass_Gen;
	Vec_ass_Gen = 0;

	TBranch* b_mult;
	TBranch* b_Nass_Gen;
	TBranch* b_Vec_ass_Gen;

	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("Nass_Gen", &Nass_Gen, &b_Nass_Gen);
	tin1->SetBranchAddress("Vec_ass_Gen", &Vec_ass_Gen, &b_Vec_ass_Gen);

	TLorentzVector* vec_trk_Gen1 = new TLorentzVector;
	TLorentzVector* vec_trk_Gen2 = new TLorentzVector;
	vec_trk_Gen1 = 0;
	vec_trk_Gen2 = 0;
//}}}

	const Int_t Nevt = tin1->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);

		for(Int_t itrk1 = 0; itrk1 < Nass_Gen; itrk1++)
		{
			vec_trk_Gen1 = (TLorentzVector*) Vec_ass_Gen->At(itrk1);
			if(vec_trk_Gen1 == 0) continue;
			Double_t trg_eta_tmp = vec_trk_Gen1->Eta();
			Double_t trg_phi_tmp = vec_trk_Gen1->Phi();

			for(Int_t itrk2 = 0; itrk2 < Nass_Gen; itrk2++)
			{
				if(itrk1 == itrk2) continue;
				vec_trk_Gen2 = (TLorentzVector*) Vec_ass_Gen->At(itrk2);
				if(vec_trk_Gen2 == 0) continue;

//calculate correl{{{
				Double_t ass_eta = vec_trk_Gen2->Eta();
				Double_t ass_phi = vec_trk_Gen2->Phi();
				Double_t deta = ass_eta - trg_eta_tmp;
				Double_t dphi = ass_phi - trg_phi_tmp;

				if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
				if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
				if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
//}}}

//fill hist{{{
				hGen1_1->Fill(deta, dphi, 1/( (double)Nass_Gen) );
				hGen1_2->Fill(deta, dphi, 1/( (double)Nass_Gen) );
				if(fabs(deta) > 2.0)
				{
					hGen2_1->Fill(deta, dphi, 1/( (double)Nass_Gen) );
					hGen2_2->Fill(deta, dphi, 1/( (double)Nass_Gen) );
				}
				if(fabs(deta) > 1.5)
				{
					hGen3_1->Fill(deta, dphi, 1/( (double)Nass_Gen) );
					hGen3_2->Fill(deta, dphi, 1/( (double)Nass_Gen) );
				}
				if(fabs(deta) > 1.0)
				{
					hGen4_1->Fill(deta, dphi, 1/( (double)Nass_Gen) );
					hGen4_2->Fill(deta, dphi, 1/( (double)Nass_Gen) );
				}
				if(fabs(deta) < 1.0)
				{
					hGen5_1->Fill(deta, dphi, 1/( (double)Nass_Gen) );
					hGen5_2->Fill(deta, dphi, 1/( (double)Nass_Gen) );
				}
//}}}
			}
		}
	}

//Draw{{{
	cGen1_1->cd();
	hGen1_1->Scale(1./Nevt);
	hGen1_1->Draw("Surf1");
	cGen1_2->cd();
	hGen1_2->Scale(1./Nevt);
	hGen1_2->Draw("Surf1");
	cGen2_1->cd();
	hGen2_1->Scale(1./Nevt);
	hGen2_1->Draw("Surf1");
	cGen2_2->cd();
	hGen2_2->Scale(1./Nevt);
	hGen2_2->Draw("Surf1");
	cGen3_1->cd();
	hGen3_1->Scale(1./Nevt);
	hGen3_1->Draw("Surf1");
	cGen3_2->cd();
	hGen3_2->Scale(1./Nevt);
	hGen3_2->Draw("Surf1");
	cGen4_1->cd();
	hGen4_1->Scale(1./Nevt);
	hGen4_1->Draw("Surf1");
	cGen4_2->cd();
	hGen4_2->Scale(1./Nevt);
	hGen4_2->Draw("Surf1");
	cGen5_1->cd();
	hGen5_1->Scale(1./Nevt);
	hGen5_1->Draw("Surf1");
	cGen5_2->cd();
	hGen5_2->Scale(1./Nevt);
	hGen5_2->Draw("Surf1");
//}}}

//store{{{
	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s/trk_deta-dphi_Gen_Pbp_distribution_same_MC.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data()), "RECREATE");
	fout->cd();
	hGen1_1->Write();
	hGen1_2->Write();
	hGen2_1->Write();
	hGen2_2->Write();
	hGen3_1->Write();
	hGen3_2->Write();
	hGen4_1->Write();
	hGen4_2->Write();
	hGen5_1->Write();
	hGen5_2->Write();
	fout->Close();
//}}}
}
