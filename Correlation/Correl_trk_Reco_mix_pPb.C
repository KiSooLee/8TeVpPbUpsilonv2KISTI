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
#include <TMath.h>
/*
#include "Style_Upv2.h"
#include "Upsilon.h"
*/
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"

using namespace std;
//}}}

void Correl_trk_Reco_mix_pPb(const bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TString MupT = "4", const TString trkptversion = "v1")
{
	SetStyle();

//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data());
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
	TChain* tin2_tmp = new TChain("UpsilonTree");
	if(isMC)
	{
		for(Int_t ibin = 10; ibin < 40; ibin++)
		{
			fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);
			fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);
			//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_%s_%d_nonemb.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);
			//fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_%s_%d_nonemb.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);
			tin1_tmp->Add(fname1.Data());
			tin2_tmp->Add(fname2.Data());
		}
	}
	else
	{
		for(Int_t ibin = 0; ibin < 120; ibin++)//for analysis
		//for(Int_t ibin = 20; ibin < 40; ibin++)//for multiplicity scan
		{
			//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//storage
			//fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//storage
			//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_%s_OS_CutGP_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//CutGPlus
			//fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_%s_OS_CutGP_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//CutGPlus
			fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_%s_OS_Olv_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//Overlaping vertex filter
			fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_%s_OS_Olv_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//Overlaping vertex filter
			//fname1 = Form("/cms/scratch/kilee/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//scratch
			//fname2 = Form("/cms/scratch/kilee/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//scratch
			tin1_tmp->Add(fname1.Data());
			tin2_tmp->Add(fname2.Data());
		}
	}
	TTree* tin1 = tin1_tmp->CloneTree();
	TTree* tin2 = tin2_tmp->CloneTree();
	tin1_tmp->Reset();
	tin2_tmp->Reset();

	TFile* ftrk = new TFile("../AccEff/Plots/Hijing_8TeV_dataBS.root", "READ");
//}}}

	TH2D* htrk = (TH2D*) ftrk->Get("rTotalEff3D_0");

//Define canvas & hist{{{
	const Int_t Netabin1 = 32;
	const Int_t Nphibin1 = 32;
	const Int_t Netabin2 = 16;
	const Int_t Nphibin2 = 16;

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

	TH2D* hReco1_1 = new TH2D("hMixpPbReco1_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco1_2 = new TH2D("hMixpPbReco1_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco2_1 = new TH2D("hMixpPbReco2_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco2_2 = new TH2D("hMixpPbReco2_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco3_1 = new TH2D("hMixpPbReco3_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco3_2 = new TH2D("hMixpPbReco3_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco4_1 = new TH2D("hMixpPbReco4_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco4_2 = new TH2D("hMixpPbReco4_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco5_1 = new TH2D("hMixpPbReco5_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1, -(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco5_2 = new TH2D("hMixpPbReco5_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2, -(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());

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
	Int_t mult1;
	Int_t mult2;
	Float_t zVtx1;
	Float_t zVtx2;
	Int_t Ntrg_Reco1;
	Int_t Ntrg_Reco2;
	Int_t Nass_Reco1;
	Int_t Nass_Reco2;
	TClonesArray* Vec_trg_Reco1;
	TClonesArray* Vec_trg_Reco2;
	TClonesArray* Vec_ass_Reco1;
	TClonesArray* Vec_ass_Reco2;
	Vec_trg_Reco1 = 0;
	Vec_trg_Reco2 = 0;
	Vec_ass_Reco1 = 0;
	Vec_ass_Reco2 = 0;

	TBranch* b_mult1;
	TBranch* b_mult2;
	TBranch* b_zVtx1;
	TBranch* b_zVtx2;
	TBranch* b_Ntrg_Reco1;
	TBranch* b_Ntrg_Reco2;
	TBranch* b_Nass_Reco1;
	TBranch* b_Nass_Reco2;
	TBranch* b_Vec_trg_Reco1;
	TBranch* b_Vec_trg_Reco2;
	TBranch* b_Vec_ass_Reco1;
	TBranch* b_Vec_ass_Reco2;

	tin1->SetBranchAddress("mult", &mult1, &b_mult1);
	tin1->SetBranchAddress("zVtx", &zVtx1, &b_zVtx1);
	tin1->SetBranchAddress("Ntrg_Reco", &Ntrg_Reco1, &b_Ntrg_Reco1);
	tin1->SetBranchAddress("Nass_Reco", &Nass_Reco1, &b_Nass_Reco1);
	tin1->SetBranchAddress("Vec_trg_Reco", &Vec_trg_Reco1, &b_Vec_trg_Reco1);
	tin1->SetBranchAddress("Vec_ass_Reco", &Vec_ass_Reco1, &b_Vec_ass_Reco1);

	tin2->SetBranchAddress("mult", &mult2, &b_mult2);
	tin2->SetBranchAddress("zVtx", &zVtx2, &b_zVtx2);
	tin2->SetBranchAddress("Ntrg_Reco", &Ntrg_Reco2, &b_Ntrg_Reco2);
	tin2->SetBranchAddress("Nass_Reco", &Nass_Reco2, &b_Nass_Reco2);
	tin2->SetBranchAddress("Vec_trg_Reco", &Vec_trg_Reco2, &b_Vec_trg_Reco2);
	tin2->SetBranchAddress("Vec_ass_Reco", &Vec_ass_Reco2, &b_Vec_ass_Reco2);
//}}}

//Define lorentz vector{{{
	TLorentzVector* vec_trg_Reco1 = new TLorentzVector;
	TLorentzVector* vec_trg_Reco2 = new TLorentzVector;
	TLorentzVector* vec_trk_Reco1 = new TLorentzVector;
	TLorentzVector* vec_trk_Reco2 = new TLorentzVector;
	vec_trg_Reco1 = 0;
	vec_trg_Reco2 = 0;
	vec_trk_Reco1 = 0;
	vec_trk_Reco2 = 0;
//}}}

	const Int_t Nevt1 = tin1->GetEntries();
	const Int_t Nevt2 = tin2->GetEntries();

	if(Nevt1 > 0 && Nevt2 > 0)
	{
		for(Int_t ievt = 0; ievt < Nevt1; ievt++)
		{
			if(ievt%100 == 0) cout << "1st Events: " << ievt << " / " << Nevt1 << " [" << Form("%.1f", ((double)ievt/(double)Nevt1)*100) << " %]" << endl;
			tin1->GetEntry(ievt);

			//if(Nass_Reco1 <= 0 || zVtx1 == -99) continue;
			if(Nass_Reco1 <= 0) continue;
			for(Int_t itrg = 0; itrg < Ntrg_Reco1; itrg++)
			{
				vec_trg_Reco1 = (TLorentzVector*) Vec_trg_Reco1->At(itrg);
				if(vec_trg_Reco1 == 0) continue;
				else break;
			}
			Double_t trg_pt1 = vec_trg_Reco1->Pt();

			for(Int_t itrk1 = 0; itrk1 < Nass_Reco1; itrk1++)
			{
				vec_trk_Reco1 = (TLorentzVector*) Vec_ass_Reco1->At(itrk1);
				if(vec_trk_Reco1 == 0) continue;
				Double_t trg_eta = vec_trk_Reco1->Eta();
				Double_t trg_phi = vec_trk_Reco1->Phi();
				Double_t trg_pt = vec_trk_Reco1->Pt();

				Double_t trkeff_trg = 1.;
				trkeff_trg = htrk->GetBinContent(htrk->GetBin(htrk->GetXaxis()->FindBin(trg_eta), htrk->GetYaxis()->FindBin(trg_pt)));

//correlation{{{
				for(Int_t irand = 0; irand < 10; irand++)
				{
					Int_t rNum = gRandom->Integer(Nevt2);
					tin2->GetEntry(rNum);

					for(Int_t itrg = 0; itrg < Ntrg_Reco2; itrg++)
					{
						vec_trg_Reco2 = (TLorentzVector*) Vec_trg_Reco2->At(itrg);
					}
					Double_t trg_pt2 = vec_trg_Reco2->Pt();
					//if(zVtx2 == -99 || TMath::Abs(zVtx1 - zVtx2) > 20. || Nass_Reco2 <= 0)
					if(TMath::Abs(zVtx1 - zVtx2) > 20. || Nass_Reco2 <= 0)
					{
						irand--;
						continue;
					}
/*
//multiplicity restrict for high{{{
					if(mult1 >= 70 && mult1 < 80)
					{
						if (mult2 < 70 || mult2 >= 80)
						{
							irand--;
							continue;
						}
					}
					else if(mult1 >= 80 && mult1 < 90)
					{
						if (mult2 < 80 || mult2 >= 90)
						{
							irand--;
							continue;
						}
					}
					else if(mult1 >= 90 && mult1 < 110)
					//else if(mult1 >= 90 && mult1 < 120)
					{
						if (mult2 < 90 || mult2 >= 110)
						//if (mult2 < 90 || mult2 >= 120)
						{
							irand--;
							continue;
						}
					}
					else if(mult1 >= 110 && mult1 < 150)
					//else if(mult1 >= 120 && mult1 < 150)
					{
						if (mult2 < 110 || mult2 >= 150)
						//if (mult2 < 120 || mult2 >= 150)
						{
							irand--;
							continue;
						}
					}
					else if(mult1 >= 150 && mult1 < 300)
					{
						if (mult2 < 150 || mult2 >= 300)
						{
							irand--;
							continue;
						}
					}
//}}}
*/

//multiplicity restrict for low{{{
					if(mult1 >= 0 && mult1 < 35)
					{
						if (mult2 < 0 || mult2 >= 35)
						{
							irand--;
							continue;
						}
					}
					else if(mult1 >= 35 && mult1 < 50)
					{
						if (mult2 < 35 || mult2 >= 50)
						{
							irand--;
							continue;
						}
					}
//}}}

//pt restrict{{{
					if(trg_pt1 >= 0 && trg_pt1 < 3)
					{
						if(trg_pt2 < 0 || trg_pt2 >= 3)
						{
							irand--;
							continue;
						}
					}
					else if(trg_pt1 >= 3 && trg_pt1 < 6)
					{
						if(trg_pt2 < 3 || trg_pt2 >= 6)
						{
							irand--;
							continue;
						}
					}
					else if(trg_pt1 >= 6 && trg_pt1 < 10)
					{
						if(trg_pt2 < 6 || trg_pt2 >= 10)
						{
							irand--;
							continue;
						}
					}
					else if(trg_pt1 >= 10 && trg_pt1 < 30)
					{
						if(trg_pt2 < 10 || trg_pt2 >= 30)
						{
							irand--;
							continue;
						}
					}
//}}}

					for(Int_t itrk2 = 0; itrk2 < Nass_Reco2; itrk2++)
					{
						vec_trk_Reco2 = (TLorentzVector*) Vec_ass_Reco2->At(itrk2);
						if(vec_trk_Reco2 == 0) continue;

//calculate correl{{{
						Double_t ass_eta = vec_trk_Reco2->Eta();
						Double_t ass_phi = vec_trk_Reco2->Phi();
						Double_t ass_pt = vec_trk_Reco2->Pt();
						Double_t deta = ass_eta - trg_eta;
						Double_t dphi = ass_phi - trg_phi;

						if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
						if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
						if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
//}}}

//fill hist{{{
						Double_t trkeff_ass = 1.;
						trkeff_ass = htrk->GetBinContent(htrk->GetBin(htrk->GetXaxis()->FindBin(ass_eta), htrk->GetYaxis()->FindBin(ass_pt)));

						hReco1_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
						hReco1_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
						if(fabs(deta) > 2.0)
						{
							hReco2_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
							hReco2_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
						}
						if(fabs(deta) > 1.5)
						{
							hReco3_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
							hReco3_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
						}
						if(fabs(deta) > 1.0)
						{
							hReco4_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
							hReco4_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
						}
						if(fabs(deta) < 1.0)
						{
							hReco5_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
							hReco5_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco1*trkeff_trg*trkeff_ass) ));
						}
//}}}
					}
				}
//}}}
			}
		}

		for(Int_t ievt = 0; ievt < Nevt2; ievt++)
		{
			if(ievt%100 == 0) cout << "2nd Events: " << ievt << " / " << Nevt2 << " [" << Form("%.1f", ((double)ievt/(double)Nevt2)*100) << " %]" << endl;
			tin2->GetEntry(ievt);

			//if(Nass_Reco2 <= 0 || zVtx2 == -99) continue;
			if(Nass_Reco2 <= 0) continue;
			for(Int_t itrg = 0; itrg < Ntrg_Reco2; itrg++)
			{
				vec_trg_Reco2 = (TLorentzVector*) Vec_trg_Reco2->At(itrg);
				if(vec_trg_Reco2 == 0) continue;
				else break;
			}
			Double_t trg_pt2 = vec_trg_Reco2->Pt();

			for(Int_t itrk1 = 0; itrk1 < Nass_Reco2; itrk1++)
			{
				vec_trk_Reco2 = (TLorentzVector*) Vec_ass_Reco2->At(itrk1);
				if(vec_trk_Reco2 == 0) continue;
				Double_t trg_eta = vec_trk_Reco2->Eta();
				Double_t trg_phi = vec_trk_Reco2->Phi();
				Double_t trg_pt = vec_trk_Reco2->Pt();

				Double_t trkeff_trg = 1.;
				trkeff_trg = htrk->GetBinContent(htrk->GetBin(htrk->GetXaxis()->FindBin(trg_eta), htrk->GetYaxis()->FindBin(trg_pt)));

//correlation{{{
				for(Int_t irand = 0; irand < 10; irand++)
				{
					Int_t rNum = gRandom->Integer(Nevt1);
					tin1->GetEntry(rNum);
					//if(zVtx1 == -99 || TMath::Abs(zVtx1 - zVtx2) > 20. || Nass_Reco1 <= 0)
					for(Int_t itrg = 0; itrg < Ntrg_Reco1; itrg++)
					{
						vec_trg_Reco1 = (TLorentzVector*) Vec_trg_Reco1->At(itrg);
						if(vec_trg_Reco1 == 0) continue;
						else break;
					}
					Double_t trg_pt1 = vec_trg_Reco1->Pt();

					if(TMath::Abs(zVtx1 - zVtx2) > 20. || Nass_Reco1 <= 0)
					{
						irand--;
						continue;
					}
/*
//multiplicity restrict for high{{{
					if(mult2 >= 70 && mult2 < 80)
					{
						if (mult1 < 70 || mult1 >= 80)
						{
							irand--;
							continue;
						}
					}
					else if(mult2 >= 80 && mult2 < 90)
					{
						if (mult1 < 80 || mult1 >= 90)
						{
							irand--;
							continue;
						}
					}
					else if(mult2 >= 90 && mult2 < 110)
					//else if(mult2 >= 90 && mult2 < 120)
					{
						if (mult1 < 90 || mult1 >= 110)
						//if (mult1 < 90 || mult1 >= 120)
						{
							irand--;
							continue;
						}
					}
					else if(mult2 >= 110 && mult2 < 150)
					//else if(mult2 >= 120 && mult2 < 150)
					{
						if (mult1 < 110 || mult1 >= 150)
						//if (mult1 < 120 || mult1 >= 150)
						{
							irand--;
							continue;
						}
					}
					else if(mult2 >= 150 && mult2 < 300)
					{
						if (mult1 < 150 || mult1 >= 300)
						{
							irand--;
							continue;
						}
					}
//}}}
*/

//multiplicity restrict for low{{{
					if(mult2 >= 0 && mult2 < 35)
					{
						if (mult1 < 0 || mult1 >= 35)
						{
							irand--;
							continue;
						}
					}
					else if(mult2 >= 35 && mult2 < 50)
					{
						if (mult1 < 35 || mult1 >= 50)
						{
							irand--;
							continue;
						}
					}
//}}}

//pt restrict{{{
					if(trg_pt2 >= 0 && trg_pt2 < 3)
					{
						if(trg_pt1 < 0 || trg_pt1 >= 3)
						{
							irand--;
							continue;
						}
					}
					else if(trg_pt2 >= 3 && trg_pt2 < 6)
					{
						if(trg_pt1 < 3 || trg_pt1 >= 6)
						{
							irand--;
							continue;
						}
					}
					else if(trg_pt2 >= 6 && trg_pt2 < 10)
					{
						if(trg_pt1 < 6 || trg_pt1 >= 10)
						{
							irand--;
							continue;
						}
					}
					else if(trg_pt2 >= 10 && trg_pt2 < 30)
					{
						if(trg_pt1 < 10 || trg_pt1 >= 30)
						{
							irand--;
							continue;
						}
					}
//}}}

					for(Int_t itrk2 = 0; itrk2 < Nass_Reco1; itrk2++)
					{
						vec_trk_Reco1 = (TLorentzVector*) Vec_ass_Reco1->At(itrk2);
						if(vec_trk_Reco1 == 0) continue;

//calculate correl{{{
						Double_t ass_eta = vec_trk_Reco1->Eta();
						Double_t ass_phi = vec_trk_Reco1->Phi();
						Double_t ass_pt = vec_trk_Reco1->Pt();
						Double_t deta = ass_eta - trg_eta;
						Double_t dphi = ass_phi - trg_phi;
	
						if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
						if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
						if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
//}}}

//fill hist{{{
						Double_t trkeff_ass = 1.;
						trkeff_ass = htrk->GetBinContent(htrk->GetBin(htrk->GetXaxis()->FindBin(ass_eta), htrk->GetYaxis()->FindBin(ass_pt)));

						hReco1_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
						hReco1_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
						if(fabs(deta) > 2.0)
						{
							hReco2_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
							hReco2_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
						}
						if(fabs(deta) > 1.5)
						{
							hReco3_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
							hReco3_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
						}
						if(fabs(deta) > 1.0)
						{
							hReco4_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
							hReco4_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
						}
						if(fabs(deta) < 1.0)
						{
							hReco5_1->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
							hReco5_2->Fill(deta, dphi, 1/( (double)(10*Nass_Reco2*trkeff_trg*trkeff_ass) ));
						}
//}}}
					}
				}
//}}}
			}
		}
	}

//draw{{{
	cReco1_1->cd();
	hReco1_1->Scale(1./(Nevt1+Nevt2));
	hReco1_1->Draw("Surf1");
	cReco1_2->cd();
	hReco1_2->Scale(1./(Nevt1+Nevt2));
	hReco1_2->Draw("Surf1");
	cReco2_1->cd();
	hReco2_1->Scale(1./(Nevt1+Nevt2));
	hReco2_1->Draw("Surf1");
	cReco2_2->cd();
	hReco2_2->Scale(1./(Nevt1+Nevt2));
	hReco2_2->Draw("Surf1");
	cReco3_1->cd();
	hReco3_1->Scale(1./(Nevt1+Nevt2));
	hReco3_1->Draw("Surf1");
	cReco3_2->cd();
	hReco3_2->Scale(1./(Nevt1+Nevt2));
	hReco3_2->Draw("Surf1");
	cReco4_1->cd();
	hReco4_1->Scale(1./(Nevt1+Nevt2));
	hReco4_1->Draw("Surf1");
	cReco4_2->cd();
	hReco4_2->Scale(1./(Nevt1+Nevt2));
	hReco4_2->Draw("Surf1");
	cReco5_1->cd();
	hReco5_1->Scale(1./(Nevt1+Nevt2));
	hReco5_1->Draw("Surf1");
	cReco5_2->cd();
	hReco5_2->Scale(1./(Nevt1+Nevt2));
	hReco5_2->Draw("Surf1");
//}}}

//store{{{
	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s/trk_deta-dphi_Reco_pPb_distribution_mix_%s.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data(), MorD.Data()), "RECREATE");
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
