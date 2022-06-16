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

void Correl_Reco_mix_Pbp_jet(const Bool_t isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TString MupT = "4", const TString trkptversion = "v1", const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Int_t isTnP = 0, const Bool_t isBkg = true)
{
	SetStyle();

//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data());
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//Define names{{{
	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString PorB;
	if(isBkg) PorB = "bkg";
	else PorB = "peak";
	TString TnPs;
	if(isTnP == 0) TnPs = "w";
	else if(isTnP == 1) TnPs = "statup";
	else if(isTnP == 2) TnPs = "statdw";
	else if(isTnP == 3) TnPs = "systup";
	else if(isTnP == 4) TnPs = "systdw";
	else if(isTnP == 5) TnPs = "wo";
	else
	{
		cout << "There is no such TnP index" << endl;
		return;
	}
//}}}

//Get files{{{
	TString fname1, fname2;
	TChain* tin1_tmp = new TChain("UpsilonTree");
	TChain* tin2_tmp = new TChain("UpsilonTree");
	for(Int_t ibin = 0; ibin < 120; ibin++)
	{
		//if( (isBkg && (ibin < 20 || ibin >= 60)) || (!isBkg && (ibin >= 26 && ibin < 32)) )
		if( (!isMC && isBkg && (ibin < 20 || ibin >= 60)) || (!isMC && !isBkg && (ibin >= 22 && ibin < 36)) || (isMC && (ibin >= 10 && ibin < 40)) )
		{
			//fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp1_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//storage
			//fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp2_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//storage
			fname1 = Form("/cms/scratch/kilee/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp1_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//scratch
			fname2 = Form("/cms/scratch/kilee/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp2_PADoubleMuon_%s_OS_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, MupT.Data(), trkptversion.Data(), MorD.Data(), ibin);//scratch
			tin1_tmp->Add(fname1.Data());
			tin2_tmp->Add(fname2.Data());
		}
	}
	TTree* tin1 = tin1_tmp->CloneTree();
	TTree* tin2 = tin2_tmp->CloneTree();
	tin1_tmp->Reset();
	tin2_tmp->Reset();

	TFile* facc = new TFile(Form("../AccEff/Plots/AccPlots_Upsilon_1S_RW%o_MupT%s.root", isAccRW, MupT.Data()), "READ");
	TFile* feff = new TFile(Form("../AccEff/Plots/EffPlots_Upsilon_1S_RW%o_TnP%s_MupT%s.root", isEffRW, TnPs.Data(), MupT.Data()), "READ");
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
	const Int_t Netabin1 = 32;
	//const Int_t Netabin1 = 46;//wide1
	//const Int_t Netabin1 = 66;//wide2
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

	TH2D* hReco1_1 = new TH2D("hMixPbpReco1_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco1_2 = new TH2D("hMixPbpReco1_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco2_1 = new TH2D("hMixPbpReco2_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco2_2 = new TH2D("hMixPbpReco2_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco3_1 = new TH2D("hMixPbpReco3_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco3_2 = new TH2D("hMixPbpReco3_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco4_1 = new TH2D("hMixPbpReco4_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco4_2 = new TH2D("hMixPbpReco4_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* hReco5_1 = new TH2D("hMixPbpReco5_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1, -4.95, 4.95, Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* hReco5_2 = new TH2D("hMixPbpReco5_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2, -4.95, 4.95, Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(), (1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());

/*
//wide bin first case{{{
	TH2D* h1_1 = new TH2D("hisBkgPbp1_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1,-7.5,7.5,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());//wide1
	TH2D* h1_2 = new TH2D("hisBkgPbp1_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2,-7.5,7.5,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());//wide1
	TH2D* h4_1 = new TH2D("hisBkgPbp4_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1,-7.5,7.5,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());//wide1
	TH2D* h4_2 = new TH2D("hisBkgPbp4_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2,-7.5,7.5,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());//wide1
//}}}
*/
/*
//wide bin second case{{{
	TH2D* h1_1 = new TH2D("hisBkgPbp1_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1,-10.5,10.5,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());//wide2
	TH2D* h1_2 = new TH2D("hisBkgPbp1_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2,-10.5,10.5,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());//wide2
	TH2D* h4_1 = new TH2D("hisBkgPbp4_1", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin1,-10.5,10.5,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());//wide2
	TH2D* h4_2 = new TH2D("hisBkgPbp4_2", ";#Delta#eta;#Delta#phi;B(#Delta#eta,#Delta#phi)", Netabin2,-10.5,10.5,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());//wide2
//za}}}
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
	TLorentzVector* vec_ass_Reco1 = new TLorentzVector;
	TLorentzVector* vec_ass_Reco2 = new TLorentzVector;
	vec_trg_Reco1 = 0;
	vec_trg_Reco2 = 0;
	vec_ass_Reco1 = 0;
	vec_ass_Reco2 = 0;
//}}}

	const Int_t Nevt1 = tin1->GetEntries();
	const Int_t Nevt2 = tin2->GetEntries();

	if(Nevt1 > 0 && Nevt2 > 0)
	{
		for(Int_t ievt = 0; ievt < Nevt1; ievt++)
		{
			if(ievt%100 == 0) cout << "1st Events: " << ievt << " / " << Nevt1 << " [" << Form("%.1f", ((double)ievt/(double)Nevt1)*100) << " %]" << endl;
			tin1->GetEntry(ievt);

			if(Ntrg_Reco1 <= 0 || zVtx1 == -99) continue;
			for(Int_t itrg = 0; itrg < Ntrg_Reco1; itrg++)
			{
				vec_trg_Reco1 = (TLorentzVector*) Vec_trg_Reco1->At(itrg);
				if(vec_trg_Reco1 == 0) continue;
				Double_t trg_y = vec_trg_Reco1->Rapidity();
				Double_t trg_pt = vec_trg_Reco1->Pt();
				Double_t trg_eta = vec_trg_Reco1->Eta();
				Double_t trg_phi = vec_trg_Reco1->Phi();

				Double_t upacc = 1.;
				Double_t upeff = 1.;
				for(Int_t iy = 0; iy < Ny; iy++)
				{
					if(fabs(trg_y) > ybin[iy] && fabs(trg_y) <= ybin[iy+1])
					{
						upacc = hacc[iy]->GetBinContent(hacc[iy]->FindBin(trg_pt));
						upeff = heff[iy]->GetBinContent(heff[iy]->FindBin(trg_pt));
						break;
					}
				}

//correlation{{{
				for(Int_t irand = 0; irand < 10; irand++)
				{
					Int_t rNum = gRandom->Integer(Nevt2);
					tin2->GetEntry(rNum);
					if(zVtx2 == -99 || TMath::Abs(zVtx1 - zVtx2) > 20. || Nass_Reco2 <= 0)
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
					//else if(mult1 >= 90 && mult1 < 110)
					else if(mult1 >= 90 && mult1 < 120)
					{
						//if (mult2 < 90 || mult2 >= 110)
						if (mult2 < 90 || mult2 >= 120)
						{
							irand--;
							continue;
						}
					}
					//else if(mult1 >= 110 && mult1 < 150)
					else if(mult1 >= 120 && mult1 < 150)
					{
						//if (mult2 < 110 || mult2 >= 150)
						if (mult2 < 120 || mult2 >= 150)
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

					for(Int_t itrk = 0; itrk < Nass_Reco2; itrk++)
					{
						vec_ass_Reco2 = (TLorentzVector*) Vec_ass_Reco2->At(itrk);
						if(vec_ass_Reco2 == 0) continue;

//calculate correl{{{
						Double_t ass_eta = vec_ass_Reco2->Eta();
						Double_t ass_phi = vec_ass_Reco2->Phi();
						Double_t ass_pt = vec_ass_Reco2->Pt();
						Double_t deta = ass_eta - trg_eta;
						Double_t dphi = ass_phi - trg_phi;

						if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
						if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
						if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
//}}}

//fill hist{{{
						Double_t trkeff = 1.;
						trkeff = htrk->GetBinContent(htrk->GetBin(htrk->GetXaxis()->FindBin(ass_eta), htrk->GetYaxis()->FindBin(ass_pt)));

						hReco1_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
						hReco1_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
						if(fabs(deta) > 2.0)
						{
							hReco2_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
							hReco2_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
						}
						if(fabs(deta) > 1.5)
						{
							hReco3_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
							hReco3_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
						}
						if(fabs(deta) > 1.0)
						{
							hReco4_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
							hReco4_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
						}
						if(fabs(deta) < 1.0)
						{
							hReco5_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
							hReco5_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco1*upacc*upeff*trkeff) ));
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

			if(Ntrg_Reco2 <= 0 || zVtx2 == -99) continue;
			for(Int_t itrg = 0; itrg < Ntrg_Reco2; itrg++)
			{
				vec_trg_Reco2 = (TLorentzVector*) Vec_trg_Reco2->At(itrg);
				if(vec_trg_Reco2 == 0) continue;
				Double_t trg_y = vec_trg_Reco2->Rapidity();
				Double_t trg_pt = vec_trg_Reco2->Pt();
				Double_t trg_eta = vec_trg_Reco2->Eta();
				Double_t trg_phi = vec_trg_Reco2->Phi();

				Double_t upacc = 1.;
				Double_t upeff = 1.;
				for(Int_t iy = 0; iy < Ny; iy++)
				{
					if(fabs(trg_y) > ybin[iy] && fabs(trg_y) <= ybin[iy+1])
					{
						upacc = hacc[iy]->GetBinContent(hacc[iy]->FindBin(trg_pt));
						upeff = heff[iy]->GetBinContent(heff[iy]->FindBin(trg_pt));
						break;
					}
					else continue;
				}

//correlation{{{
				for(Int_t irand = 0; irand < 10; irand++)
				{
					Int_t rNum = gRandom->Integer(Nevt1);
					tin1->GetEntry(rNum);
					if(zVtx1 == -99 || TMath::Abs(zVtx1 - zVtx2) > 20. || Nass_Reco1 <= 0)
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
					//else if(mult2 >= 90 && mult2 < 110)
					else if(mult2 >= 90 && mult2 < 120)
					{
						//if (mult1 < 90 || mult1 >= 110)
						if (mult1 < 90 || mult1 >= 120)
						{
							irand--;
							continue;
						}
					}
					//else if(mult2 >= 110 && mult2 < 150)
					else if(mult2 >= 120 && mult2 < 150)
					{
						//if (mult1 < 110 || mult1 >= 150)
						if (mult1 < 120 || mult1 >= 150)
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

					for(Int_t itrk = 0; itrk < Nass_Reco1; itrk++)
					{
						vec_ass_Reco1 = (TLorentzVector*) Vec_ass_Reco1->At(itrk);
						if(vec_ass_Reco1 == 0) continue;

//calculate correl{{{
						Double_t ass_eta = vec_ass_Reco1->Eta();
						Double_t ass_phi = vec_ass_Reco1->Phi();
						Double_t ass_pt = vec_ass_Reco1->Pt();
						Double_t deta = ass_eta - trg_eta;
						Double_t dphi = ass_phi - trg_phi;

						if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
						if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
						if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
//}}}

//fill hist{{{
						Double_t trkeff = 1.;
						trkeff = htrk->GetBinContent(htrk->GetBin(htrk->GetXaxis()->FindBin(ass_eta), htrk->GetYaxis()->FindBin(ass_pt)));

						hReco1_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
						hReco1_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
						if(fabs(deta) > 2.0)
						{
							hReco2_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
							hReco2_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
						}
						if(fabs(deta) > 1.5)
						{
							hReco3_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
							hReco3_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
						}
						if(fabs(deta) > 1.0)
						{
							hReco4_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
							hReco4_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
						}
						if(fabs(deta) < 1.0)
						{
							hReco5_1->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
							hReco5_2->Fill(deta, dphi, 1/( (double)(10*Ntrg_Reco2*upacc*upeff*trkeff) ));
						}
//}}}
					}
				}
//}}}
			}
		}
	}

//Draw{{{
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
	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s/deta-dphi_Reco_Pbp_distribution_mix_%s_Acc%o_Eff%o_TnP%s_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data(), MorD.Data(), isAccRW, isEffRW, TnPs.Data(), PorB.Data()), "RECREATE");
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
