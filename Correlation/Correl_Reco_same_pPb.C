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

void Correl_Reco_same_pPb(const bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TString MupT = "4", const TString trkptversion = "v1", const Bool_t isAccRW= true, const Bool_t isEffRW = true, const Bool_t isTnP = true, const Int_t imass = 0)
{
	SetStyle();

//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data());
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";

//Get files{{{
	TString fname1, fname2;
	TChain* tin1_tmp = new TChain("UpsilonTree");
	for(Int_t ibin = massBinsArr[imass]; ibin < massBinsArr[imass+1]; ibin++)
	{
		fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_%s_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);
		fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_%s_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);
		tin1_tmp->Add(fname1.Data());
		tin1_tmp->Add(fname2.Data());
	}
	TTree* tin1 = tin1_tmp->CloneTree();
	tin1_tmp->Reset();

	TFile* facc = new TFile(Form("../AccEff/Plots/AccPlots_Upsilon_1S_RW%o_MupT%s.root", isAccRW, MupT.Data()), "READ");
	TFile* feff = new TFile(Form("../AccEff/Plots/EffPlots_Upsilon_1S_RW%o_TnP%o_MupT%s.root", isEffRW, isTnP, MupT.Data()), "READ");
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
		hacc[iy] = (TH1D*) facc->Get(Form("hAcc%s%s", yabin[iy].Data(), yabin[iy+1].Data()));
		heff[iy] = (TH1D*) feff->Get(Form("hEff_%d", iy));
	}
	TH2D* htrk = (TH2D*) ftrk->Get("rTotalEff3D_0");
//}}}

//Define canvas & hist{{{
	Int_t Netabin1 = 32;
	//Int_t Netabin1 = 46;//wide1
	//Int_t Netabin1 = 66;//wide2
	Int_t Nphibin1 = 32;
	Int_t Netabin2 = 16;
	Int_t Nphibin2 = 16;

	TCanvas* cReco1_1 = new TCanvas("cReco1_1", "", 0, 0, 600, 600);
	TCanvas* cReco1_2 = new TCanvas("cReco1_2", "", 0, 0, 600, 600);
	TCanvas* cReco2_1 = new TCanvas("cReco2_1", "", 0, 0, 600, 600);
	TCanvas* cReco2_2 = new TCanvas("cReco2_2", "", 0, 0, 600, 600);
	TCanvas* cReco3_1 = new TCanvas("cReco3_1", "", 0, 0, 600, 600);
	TCanvas* cReco3_2 = new TCanvas("cReco3_2", "", 0, 0, 600, 600);
	TCanvas* cReco4_1 = new TCanvas("cReco4_1", "", 0, 0, 600, 600);
	TCanvas* cReco4_2 = new TCanvas("cReco4_2", "", 0, 0, 600, 600);
	TCanvas* cReco5_1 = new TCanvas("cReco5_1", "", 0, 0, 600, 600);
	TCanvas* cReco5_2 = new TCanvas("cReco5_2", "", 0, 0, 600, 600);

	TH2D* hReco1_1 = new TH2D("hSamepPbReco1_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco1_2 = new TH2D("hSamepPbReco1_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco2_1 = new TH2D("hSamepPbReco2_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco2_2 = new TH2D("hSamepPbReco2_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco3_1 = new TH2D("hSamepPbReco3_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco3_2 = new TH2D("hSamepPbReco3_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco4_1 = new TH2D("hSamepPbReco4_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco4_2 = new TH2D("hSamepPbReco4_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco5_1 = new TH2D("hSamepPbReco5_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco5_2 = new TH2D("hSamepPbReco5_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());

/*
//wide bin first case{{{
	TH2D* h1_1 = new TH2D("hSigpPb1_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1,-7.5,7.5,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());//wide1
	TH2D* h1_2 = new TH2D("hSigpPb1_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2,-7.5,7.5,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());//wide1
	TH2D* h4_1 = new TH2D("hSigpPb4_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1,-7.5,7.5,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());//wide1
	TH2D* h4_2 = new TH2D("hSigpPb4_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2,-7.5,7.5,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());//wide1
//}}}
*/
/*
//wide bin second case{{{
	TH2D* h1_1 = new TH2D("hSigpPb1_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1,-10.5,10.5,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());//wide2
	TH2D* h1_2 = new TH2D("hSigpPb1_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2,-10.5,10.5,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());//wide2
	TH2D* h4_1 = new TH2D("hSigpPb4_1", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin1,-10.5,10.5,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());//wide2
	TH2D* h4_2 = new TH2D("hSigpPb4_2", ";#Delta#eta;#Delta#phi;S(#Delta#eta,#Delta#phi)", Netabin2,-10.5,10.5,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());//wide2
//}}}
*/
	FormTH2(hReco1_1);
	FormTH2(hReco1_2);
	FormTH2(hReco2_1);
	FormTH2(hReco2_2);
	FormTH2(hReco3_1);
	FormTH2(hReco3_2);
	FormTH2(hReco4_1);
	FormTH2(hReco4_2);
	FormTH2(hReco5_1);
	FormTH2(hReco5_2);
//}}}

//get variables{{{
	Int_t mult;
	Int_t Ntrg_Reco;
	Int_t Nass_Reco;
	TClonesArray* Vec_trg_Reco;
	TClonesArray* Vec_ass_Reco;
	Vec_trg_Reco = 0;
	Vec_ass_Reco = 0;

	TBranch* b_mult;
	TBranch* b_Ntrg_Reco;
	TBranch* b_Nass_Reco;
	TBranch* b_Vec_trg_Reco;
	TBranch* b_Vec_ass_Reco;

	tin1->SetBranchAddress("mult", &mult, &b_mult);
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

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);

		for(Int_t itrg = 0; itrg < Ntrg_Reco; itrg++)
		{
			vec_trg_Reco = (TLorentzVector*) Vec_trg_Reco->At(itrg);
			if(vec_trg_Reco == 0) continue;
			Double_t trg_y = vec_trg_Reco->Rapidity();
			Double_t trg_pt = vec_trg_Reco->Pt();
			Double_t trg_eta = vec_trg_Reco->Eta();
			Double_t trg_phi = vec_trg_Reco->Phi();

			Double_t upacc = 1.;
			Double_t upeff = 1.;
			if(!isMC)
			{
				for(Int_t iy = 0; iy < Ny; iy++)
				{
					if(fabs(trg_y) > ybin[iy] && fabs(trg_y) <= ybin[iy+1])
					{
						upacc = hacc[iy]->GetBinContent(hacc[iy]->FindBin(trg_pt));
						upeff = heff[iy]->GetBinContent(heff[iy]->FindBin(trg_pt));
						break;
					}
				}
			}

			for(Int_t itrk = 0; itrk < Nass_Reco; itrk++)
			{
				vec_ass_Reco = (TLorentzVector*) Vec_ass_Reco->At(itrk);
				if(vec_ass_Reco == 0) continue;

//calculate correl{{{
				Double_t ass_eta = vec_ass_Reco->Eta();
				Double_t ass_phi = vec_ass_Reco->Phi();
				Double_t ass_pt = vec_ass_Reco->Pt();
				Double_t deta = ass_eta - trg_eta;
				Double_t dphi = ass_phi - trg_phi;

				if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
				if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
				if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
//}}}

//fill hist{{{
				Double_t trkeff = 1.;
				if(!isMC) trkeff = htrk->GetBinContent(htrk->GetBin(htrk->GetXaxis()->FindBin(ass_eta), htrk->GetYaxis()->FindBin(ass_pt)));

				hReco1_1->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
				hReco1_2->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
				if(fabs(deta) > 2.0)
				{
					hReco2_1->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
					hReco2_2->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
				}
				if(fabs(deta) > 1.5)
				{
					hReco3_1->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
					hReco3_2->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
				}
				if(fabs(deta) > 1.0)
				{
					hReco4_1->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
					hReco4_2->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
				}
				if(fabs(deta) < 1.0)
				{
					hReco5_1->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
					hReco5_2->Fill(deta, dphi, 1/( (double)Ntrg_Reco*upacc*upeff*trkeff ));
				}
//}}}
			}
		}
	}

//Draw{{{
	cReco1_1->cd();
	hReco1_1->Scale(1./Nevt);
	hReco1_1->Draw("Surf1");
	cReco1_2->cd();
	hReco1_2->Scale(1./Nevt);
	hReco1_2->Draw("Surf1");
	cReco2_1->cd();
	hReco2_1->Scale(1./Nevt);
	hReco2_1->Draw("Surf1");
	cReco2_2->cd();
	hReco2_2->Scale(1./Nevt);
	hReco2_2->Draw("Surf1");
	cReco3_1->cd();
	hReco3_1->Scale(1./Nevt);
	hReco3_1->Draw("Surf1");
	cReco3_2->cd();
	hReco3_2->Scale(1./Nevt);
	hReco3_2->Draw("Surf1");
	cReco4_1->cd();
	hReco4_1->Scale(1./Nevt);
	hReco4_1->Draw("Surf1");
	cReco4_2->cd();
	hReco4_2->Scale(1./Nevt);
	hReco4_2->Draw("Surf1");
	cReco5_1->cd();
	hReco5_1->Scale(1./Nevt);
	hReco5_1->Draw("Surf1");
	cReco5_2->cd();
	hReco5_2->Scale(1./Nevt);
	hReco5_2->Draw("Surf1");
//}}}

//store{{{
	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s/deta-dphi_Reco_pPb_distribution_same_%s_Acc%o_Eff%o_TnP%o_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data(), MorD.Data(), isAccRW, isEffRW, isTnP, imass), "RECREATE");
	fout->cd();
	hReco1_1->Write();
	hReco1_2->Write();
	hReco2_1->Write();
	hReco2_2->Write();
	hReco3_1->Write();
	hReco3_2->Write();
	hReco4_1->Write();
	hReco4_2->Write();
	hReco5_1->Write();
	hReco5_2->Write();
	fout->Close();
//}}}
}
