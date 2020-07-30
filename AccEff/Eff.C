//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TBranch.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TVector.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <TSystem.h>

#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooArgSet.h>

#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
#include "../Headers/tnp_weight_lowptpPb.h"

using namespace std;
using namespace RooFit;
//}}}

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut);

void Eff(const Int_t Generation = 1, const TString MupT = "3p5", const Bool_t isRW = true, const Bool_t isTnP = true)
{
	SetStyle();

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

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/Plots";

	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//Get files{{{
	TChain* tin = new TChain("hionia/myTree");
	TString fname1 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_Pbp_MC_%dS_private_20200716.root", Generation);
	TString fname2 = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/oniaTree_pPb_MC_%dS_private_20200716.root", Generation);
	tin->Add(fname1.Data());
	const Int_t Nevtcut = tin->GetEntries();
	tin->Add(fname2.Data());
//}}}

//binning{{{
	const Int_t Npt1 = 14;
	const Int_t Npt2 = 8;
	const Double_t ptbins1[Npt1] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9.,
											10., 15., 20., 30.};
	const Double_t ptbins2[Npt2] = {0., 2., 4., 6., 8., 10., 15., 30.};
	const Int_t Ny = 5;
	const Double_t ybins[Ny] = {0., 1.6, 1.8, 2.1, 2.4};
//}}}

//Define canvas and histogram{{{
	TCanvas* cyDen_tot = new TCanvas("cyDen_tot", "", 0, 0, 600, 600);
	TCanvas* cyNum_tot = new TCanvas("cyNum_tot", "", 0, 0, 600, 600);
	TCanvas* cyEff_tot = new TCanvas("cyEff_tot", "", 0, 0, 600, 600);
	TCanvas* cptDen_tot = new TCanvas("cptDen_tot", "", 0, 0, 600, 600);
	TCanvas* cptNum_tot = new TCanvas("cptNum_tot", "", 0, 0, 600, 600);
	TCanvas* cptEff_tot = new TCanvas("cptEff_tot", "", 0, 0, 600, 600);
	TCanvas* cDen[Ny-1];
	TCanvas* cNum[Ny-1];
	TCanvas* cEff[Ny-1];
	TH1D* hyDen_tot = new TH1D("hyDen_tot", ";y^{#varUpsilon};Entries", 250, -2.5, 2.5);
	TH1D* hyNum_tot = new TH1D("hyNum_tot", ";y^{#varUpsilon};Entries", 250, -2.5, 2.5);
	TH1D* hptDen_tot = new TH1D("hptDen_tot", ";p_{T}y^{#varUpsilon};Entries", 300, 0, 30);
	TH1D* hptNum_tot = new TH1D("hptNum_tot", ";p_{T}y^{#varUpsilon};Entries", 300, 0, 30);
	FormTH1Marker(hyDen_tot, 0, 0, 1.2);
	FormTH1Marker(hyNum_tot, 0, 0, 1.2);
	FormTH1Marker(hptDen_tot, 0, 0, 1.2);
	FormTH1Marker(hptNum_tot, 0, 0, 1.2);
	TH1D* hyEff_tot;
	TH1D* hptEff_tot;
	TH1D* hDen[Ny-1];
	TH1D* hNum[Ny-1];
	TH1D* hEff[Ny-1];
	for(Int_t iy = 0; iy < Ny-1; iy++)
	{
		cDen[iy] = new TCanvas(Form("cDen_%d", iy), "", 0, 0, 600, 600);
		cNum[iy] = new TCanvas(Form("cNum_%d", iy), "", 0, 0, 600, 600);
		cEff[iy] = new TCanvas(Form("cEff_%d", iy), "", 0, 0, 600, 600);
		if(iy == 0)
		{
			hDen[iy] = new TH1D(Form("hDen_%d", iy), ";p_{T}^{#varUpsilon};Entries", Npt1-1, ptbins1);
			hNum[iy] = new TH1D(Form("hNum_%d", iy), ";p_{T}^{#varUpsilon};Entries", Npt1-1, ptbins1);
		}
		else
		{
			hDen[iy] = new TH1D(Form("hDen_%d", iy), ";p_{T}^{#varUpsilon};Entries", Npt2-1, ptbins2);
			hNum[iy] = new TH1D(Form("hNum_%d", iy), ";p_{T}^{#varUpsilon};Entries", Npt2-1, ptbins2);
		}
		FormTH1Marker(hDen[iy], 0, 0, 1.2);
		FormTH1Marker(hNum[iy], 0, 0, 1.2);
	}
//}}}

	const Int_t MaxQQ = 250;

//Tree variables{{{
	ULong64_t HLTriggers;
	Int_t Reco_QQ_size;
	Int_t Reco_QQ_type[MaxQQ];
	Int_t Reco_QQ_sign[MaxQQ];
	Float_t Reco_QQ_VtxProb[MaxQQ];
	ULong64_t Reco_QQ_trig[MaxQQ];
	Bool_t Reco_QQ_mupl_TMOneStaTight[MaxQQ];
	Bool_t Reco_QQ_mumi_TMOneStaTight[MaxQQ];
	Bool_t Reco_QQ_mupl_highPurity[MaxQQ];
	Bool_t Reco_QQ_mumi_highPurity[MaxQQ];
	Int_t Reco_QQ_mupl_nTrkWMea[MaxQQ];
	Int_t Reco_QQ_mumi_nTrkWMea[MaxQQ];
	Int_t Reco_QQ_mupl_nPixWMea[MaxQQ];
	Int_t Reco_QQ_mumi_nPixWMea[MaxQQ];
	Float_t Reco_QQ_mupl_dxy[MaxQQ];
	Float_t Reco_QQ_mumi_dxy[MaxQQ];
	Float_t Reco_QQ_mupl_dz[MaxQQ];
	Float_t Reco_QQ_mumi_dz[MaxQQ];
	TClonesArray* Reco_QQ_4mom;
	TClonesArray* Reco_QQ_mupl_4mom;
	TClonesArray* Reco_QQ_mumi_4mom;
	Reco_QQ_4mom = 0;
	Reco_QQ_mupl_4mom = 0;
	Reco_QQ_mumi_4mom = 0;

	Int_t Gen_QQ_size;
	TClonesArray* Gen_QQ_4mom;
	TClonesArray* Gen_QQ_mupl_4mom;
	TClonesArray* Gen_QQ_mumi_4mom;
	Gen_QQ_4mom = 0;
	Gen_QQ_mupl_4mom = 0;
	Gen_QQ_mumi_4mom = 0;
//}}}

//Branch{{{
	TBranch* b_HLTriggers;
	TBranch* b_Reco_QQ_size;
	TBranch* b_Reco_QQ_type;
	TBranch* b_Reco_QQ_sign;
	TBranch* b_Reco_QQ_VtxProb;
	TBranch* b_Reco_QQ_trig;
	TBranch* b_Reco_QQ_mupl_TMOneStaTight;
	TBranch* b_Reco_QQ_mumi_TMOneStaTight;
	TBranch* b_Reco_QQ_mupl_highPurity;
	TBranch* b_Reco_QQ_mumi_highPurity;
	TBranch* b_Reco_QQ_mupl_nTrkWMea;
	TBranch* b_Reco_QQ_mumi_nTrkWMea;
	TBranch* b_Reco_QQ_mupl_nPixWMea;
	TBranch* b_Reco_QQ_mumi_nPixWMea;
	TBranch* b_Reco_QQ_mupl_dxy;
	TBranch* b_Reco_QQ_mumi_dxy;
	TBranch* b_Reco_QQ_mupl_dz;
	TBranch* b_Reco_QQ_mumi_dz;
	TBranch* b_Reco_QQ_4mom;
	TBranch* b_Reco_QQ_mupl_4mom;
	TBranch* b_Reco_QQ_mumi_4mom;
	TBranch* b_Gen_QQ_size;
	TBranch* b_Gen_QQ_4mom;
	TBranch* b_Gen_QQ_mupl_4mom;
	TBranch* b_Gen_QQ_mumi_4mom;
//}}}

//Branch address{{{
	tin->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
	tin->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
	tin->SetBranchAddress("Reco_QQ_type", Reco_QQ_type, &b_Reco_QQ_type);
	tin->SetBranchAddress("Reco_QQ_sign", Reco_QQ_sign, &b_Reco_QQ_sign);
	tin->SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb, &b_Reco_QQ_VtxProb);
	tin->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
	tin->SetBranchAddress("Reco_QQ_mupl_TMOneStaTight", Reco_QQ_mupl_TMOneStaTight, &b_Reco_QQ_mupl_TMOneStaTight);
	tin->SetBranchAddress("Reco_QQ_mumi_TMOneStaTight", Reco_QQ_mumi_TMOneStaTight, &b_Reco_QQ_mumi_TMOneStaTight);
	tin->SetBranchAddress("Reco_QQ_mupl_highPurity", Reco_QQ_mupl_highPurity, &b_Reco_QQ_mupl_highPurity);
	tin->SetBranchAddress("Reco_QQ_mumi_highPurity", Reco_QQ_mumi_highPurity, &b_Reco_QQ_mumi_highPurity);
	tin->SetBranchAddress("Reco_QQ_mupl_nTrkWMea", Reco_QQ_mupl_nTrkWMea, &b_Reco_QQ_mupl_nTrkWMea);
	tin->SetBranchAddress("Reco_QQ_mumi_nTrkWMea", Reco_QQ_mumi_nTrkWMea, &b_Reco_QQ_mumi_nTrkWMea);
	tin->SetBranchAddress("Reco_QQ_mupl_nPixWMea", Reco_QQ_mupl_nPixWMea, &b_Reco_QQ_mupl_nPixWMea);
	tin->SetBranchAddress("Reco_QQ_mumi_nPixWMea", Reco_QQ_mumi_nPixWMea, &b_Reco_QQ_mumi_nPixWMea);
	tin->SetBranchAddress("Reco_QQ_mupl_dxy", Reco_QQ_mupl_dxy, &b_Reco_QQ_mupl_dxy);
	tin->SetBranchAddress("Reco_QQ_mumi_dxy", Reco_QQ_mumi_dxy, &b_Reco_QQ_mumi_dxy);
	tin->SetBranchAddress("Reco_QQ_mupl_dz", Reco_QQ_mupl_dz, &b_Reco_QQ_mupl_dz);
	tin->SetBranchAddress("Reco_QQ_mumi_dz", Reco_QQ_mumi_dz, &b_Reco_QQ_mumi_dz);
	tin->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
	tin->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom, &b_Reco_QQ_mupl_4mom);
	tin->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom, &b_Reco_QQ_mumi_4mom);
	tin->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
	tin->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom, &b_Gen_QQ_4mom);
	tin->SetBranchAddress("Gen_QQ_mupl_4mom", &Gen_QQ_mupl_4mom, &b_Gen_QQ_mupl_4mom);
	tin->SetBranchAddress("Gen_QQ_mumi_4mom", &Gen_QQ_mumi_4mom, &b_Gen_QQ_mumi_4mom);
//}}}

//Define LorentzVector{{{
	TLorentzVector* Up_Reco_4mom = new TLorentzVector;
	TLorentzVector* mupl_Reco_4mom = new TLorentzVector;
	TLorentzVector* mumi_Reco_4mom = new TLorentzVector;
	TLorentzVector* Up_Gen_4mom = new TLorentzVector;
	TLorentzVector* mupl_Gen_4mom = new TLorentzVector;
	TLorentzVector* mumi_Gen_4mom = new TLorentzVector;
	Up_Reco_4mom = 0;
	mupl_Reco_4mom = 0;
	mumi_Reco_4mom = 0;
	Up_Gen_4mom = 0;
	mupl_Gen_4mom = 0;
	mumi_Gen_4mom = 0;
//}}}

	const Int_t Nevt = tin->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << "[" << Form("%.1f", ( (double)ievt/(double)Nevt)*100 ) << " %]" << endl;
		tin->GetEntry(ievt);

		Double_t reweight = 1.;

//Fill Denominator{{{
		for(Int_t iqq = 0; iqq < Gen_QQ_size; iqq++)
		{
			Up_Gen_4mom = (TLorentzVector*) Gen_QQ_4mom->At(iqq);
			mupl_Gen_4mom = (TLorentzVector*) Gen_QQ_mupl_4mom->At(iqq);
			mumi_Gen_4mom = (TLorentzVector*) Gen_QQ_mumi_4mom->At(iqq);
			if( !InAcc(mupl_Gen_4mom->Pt(), mupl_Gen_4mom->Eta(), MupTCut) ) continue;
			if( !InAcc(mumi_Gen_4mom->Pt(), mumi_Gen_4mom->Eta(), MupTCut) ) continue;
			if(isRW) reweight = funcrw->Eval(Up_Gen_4mom->Pt());
			if(ievt < Nevtcut) hyDen_tot->Fill(Up_Gen_4mom->Rapidity(), reweight);
			else hyDen_tot->Fill(-1.*Up_Gen_4mom->Rapidity(), reweight);
			hptDen_tot->Fill(Up_Gen_4mom->Pt(), reweight);
			for(Int_t iy = 0; iy < Ny-1; iy++)
			{
				if(fabs(Up_Gen_4mom->Rapidity()) > ybins[iy] && fabs(Up_Gen_4mom->Rapidity()) <= ybins[iy+1])
				hDen[iy]->Fill(Up_Gen_4mom->Pt(), reweight);
			}
		}
//}}}

//Fill Numerator{{{
		if( (HLTriggers&1)!=1 ) continue;

		for(Int_t iqq = 0; iqq < Reco_QQ_size; iqq++)
		{
			Up_Reco_4mom = (TLorentzVector*) Reco_QQ_4mom->At(iqq);
			mupl_Reco_4mom = (TLorentzVector*) Reco_QQ_mupl_4mom->At(iqq);
			mumi_Reco_4mom = (TLorentzVector*) Reco_QQ_mumi_4mom->At(iqq);

//Cuts for muon and Upsilon{{{
			if( (Reco_QQ_trig[iqq]&1) != 1 ) continue;

			if( !InAcc(mupl_Reco_4mom->Pt(), mupl_Reco_4mom->Eta(), MupTCut) ) continue;
			if( !InAcc(mumi_Reco_4mom->Pt(), mumi_Reco_4mom->Eta(), MupTCut) ) continue;

			bool muplSoft = ( (Reco_QQ_mupl_TMOneStaTight[iqq] == true) &&
									(Reco_QQ_mupl_nTrkWMea[iqq] > 5) &&
									(Reco_QQ_mupl_nPixWMea[iqq] > 0) &&
									(Reco_QQ_mupl_dxy[iqq] < 0.3) &&
									(Reco_QQ_mupl_dz[iqq] < 20.0) &&
									(Reco_QQ_mupl_highPurity[iqq] == true) //purity used for pPb not PbPb
									);
			bool mumiSoft = ( (Reco_QQ_mumi_TMOneStaTight[iqq] == true) &&
									(Reco_QQ_mumi_nTrkWMea[iqq] > 5) &&
									(Reco_QQ_mumi_nPixWMea[iqq] > 0) &&
									(Reco_QQ_mumi_dxy[iqq] < 0.3) &&
									(Reco_QQ_mumi_dz[iqq] < 20.0) &&
									(Reco_QQ_mumi_highPurity[iqq] == true) //purity used for pPb not PbPb
									);
			if( !(muplSoft && mumiSoft) ) continue;

			if( Reco_QQ_VtxProb[iqq] < 0.01 ) continue;

			if( Reco_QQ_sign[iqq] != 0) continue;
//}}}

			if(isRW) reweight = funcrw->Eval(Up_Reco_4mom->Pt());
			Double_t mupl_muid_tnp = 1.;
			Double_t mupl_trk_tnp = 1.;
			Double_t mupl_trg_tnp = 1.;
			Double_t mumi_muid_tnp = 1.;
			Double_t mumi_trk_tnp = 1.;
			Double_t mumi_trg_tnp = 1.;
			if(isTnP)
			{
				mupl_muid_tnp = tnp_weight_muid_ppb(mupl_Reco_4mom->Pt(), mupl_Reco_4mom->Eta(), 0);
				mupl_trk_tnp = tnp_weight_trk_ppb(mupl_Reco_4mom->Eta(), 0);
				mupl_trg_tnp = tnp_weight_trg_ppb(mupl_Reco_4mom->Pt(), mupl_Reco_4mom->Eta(), 3, 0);
				mumi_muid_tnp = tnp_weight_muid_ppb(mumi_Reco_4mom->Pt(), mumi_Reco_4mom->Eta(), 0);
				mumi_trk_tnp = tnp_weight_trk_ppb(mumi_Reco_4mom->Eta(), 0);
				mumi_trg_tnp = tnp_weight_trg_ppb(mumi_Reco_4mom->Pt(), mumi_Reco_4mom->Eta(), 3, 0);
			}
			Double_t mupl_tnp = mupl_muid_tnp*mupl_trk_tnp*mupl_trg_tnp;
			Double_t mumi_tnp = mumi_muid_tnp*mumi_trk_tnp*mumi_trg_tnp;

			hyNum_tot->Fill(Up_Reco_4mom->Rapidity(), 1./mupl_tnp*mumi_trg_tnp);
			hptNum_tot->Fill(Up_Reco_4mom->Pt(), 1./mupl_tnp*mumi_trg_tnp);

			for(Int_t iy = 0; iy < Ny-1; iy++)
			{
				if(fabs(Up_Reco_4mom->Rapidity()) > ybins[iy] && fabs(Up_Reco_4mom->Rapidity()) <= ybins[iy+1])
				hNum[iy]->Fill(Up_Reco_4mom->Pt(), 1./mupl_tnp*mumi_trg_tnp);
			}
		}
//}}}
	}

	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.05);
	lt1->SetNDC();

	cyDen_tot->cd();
	hyDen_tot->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cyDen_tot->SaveAs(Form("Plots/Denominator_for_eff_Up%dS_yintgr_RW%o_TnP%o_MupT%s.pdf", Generation, isRW, isTnP, MupT.Data()));

	cptDen_tot->cd();
	hptDen_tot->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cptDen_tot->SaveAs(Form("Plots/Denominator_for_eff_Up%dS_ptintgr_RW%o_TnP%o_MupT%s.pdf", Generation, isRW, isTnP, MupT.Data()));

	cyNum_tot->cd();
	hyNum_tot->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cyNum_tot->SaveAs(Form("Plots/Numerator_for_eff_Up%dS_yintgr_RW%o_TnP%o_MupT%s.pdf", Generation, isRW, isTnP, MupT.Data()));

	cptNum_tot->cd();
	hptNum_tot->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cptNum_tot->SaveAs(Form("Plots/Numerator_for_eff_Up%dS_ptintgr_RW%o_TnP%o_MupT%s.pdf", Generation, isRW, isTnP, MupT.Data()));

	cyEff_tot->cd();
	hyEff_tot = (TH1D*) hyNum_tot->Clone(Form("hyEff_tot"));
	hyEff_tot->GetYaxis()->SetTitle("Efficiency");
	hyEff_tot->Divide(hyDen_tot);
	hyEff_tot->SetMaximum(1.1);
	hyEff_tot->SetMinimum(0.0);
	hyEff_tot->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cyEff_tot->SaveAs(Form("Plots/Eff_Up%dS_yintgr_RW%o_TnP%o_MupT%s.pdf", Generation, isRW, isTnP, MupT.Data()));

	cptEff_tot->cd();
	hptEff_tot = (TH1D*) hptNum_tot->Clone(Form("hptEff_tot"));
	hptEff_tot->GetYaxis()->SetTitle("Efficiency");
	hptEff_tot->Divide(hptDen_tot);
	hptEff_tot->SetMaximum(1.1);
	hptEff_tot->SetMinimum(0.0);
	hptEff_tot->Draw("pe");
	lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	cptEff_tot->SaveAs(Form("Plots/Eff_Up%dS_ptintgr_RW%o_TnP%o_MupT%s.pdf", Generation, isRW, isTnP, MupT.Data()));

	for(Int_t iy = 0; iy < Ny-1; iy++)
	{
		cDen[iy]->cd();
		hDen[iy]->Draw("pe");
		lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.6, 0.77, Form("%.1f < #eta #leq %.1f", ybins[iy], ybins[iy+1]));
		cDen[iy]->SaveAs(Form("Plots/Denominator_for_eff_Up%dS_etabin%d_RW%o_TnP%o_MupT%s.pdf", Generation, iy, isRW, isTnP,, MupT.Data()));
		cNum[iy]->cd();
		hNum[iy]->Draw("pe");
		lt1->DrawLatex(0.6, 0.84, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.6, 0.77, Form("%.1f < #eta #leq %.1f", ybins[iy], ybins[iy+1]));
		cNum[iy]->SaveAs(Form("Plots/Numerator_for_eff_Up%dS_etabin%d_RW%o_TnP%o_MupT%s.pdf", Generation, iy, isRW, isTnP,, MupT.Data()));
		cEff[iy]->cd();
		hEff[iy] = (TH1D*) hNum[iy]->Clone(Form("hEff_%d", iy));
		hEff[iy]->GetYaxis()->SetTitle("Efficiency");
		hEff[iy]->Divide(hDen[iy]);
		hEff[iy]->SetMaximum(1.1);
		hEff[iy]->SetMinimum(0.);
		hEff[iy]->Draw("pe");
		lt1->DrawLatex(0.6, 0.44, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.6, 0.37, Form("%.1f < #eta #leq %.1f", ybins[iy], ybins[iy+1]));
		cEff[iy]->SaveAs(Form("Plots/eff_Up%dS_Ny%d_etabin%d_RW%o_TnP%o_MupT%s.pdf", Generation, iy, isRW, isTnP,, MupT.Data()));
	}

	TFile* fout = new TFile(Form("Plots/EffPlots_Upsilon_%dS_RW%o_TnP%o_MupT%s.root", Generation, isRW, isTnP, MupT.Data()), "RECREATE");
	fout->cd();
	hyDen_tot->Write();
	hyNum_tot->Write();
	hyEff_tot->Write();
	hptDen_tot->Write();
	hptNum_tot->Write();
	hptEff_tot->Write();
	for(Int_t iy = 0; iy < Ny-1; iy++)
	{
		hDen[iy]->Write();
		hNum[iy]->Write();
		hEff[iy]->Write();
	}
	fout->Close();
}

bool InAcc(Double_t muPt, Double_t muEta, Double_t MupTCut)
{
	return( TMath::Abs(muEta) < 2.4 && muPt >= MupTCut);
}
