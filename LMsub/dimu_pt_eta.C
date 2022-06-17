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
#include <TLegend.h>

#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooArgSet.h>

#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"

using namespace std;
using namespace RooFit;
//}}}

void dimu_pt_eta(const Int_t multMin = 70, const Int_t multMax = 300, const TString MupT = "3p5", const TString trkptversion = "v1", const Bool_t Weight = true)
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

	const Int_t ptMin[4] = {0, 3, 6, 10};
	const Int_t ptMax[4] = {3, 6, 10, 30};
	const Double_t ptval[10] = {0, 2, 3, 4, 5, 6, 8, 10, 15, 30};

//Get files{{{
	TString fname1[4], fname2[4], fname3[4], fname4[4];
	TChain* tin1_tmp = new TChain("UpsilonTree");
	for(Int_t ibin = 0; ibin < 120; ibin++)
	{
		for(Int_t ipt = 0; ipt < 4; ipt++)
		{
			fname1[ipt] = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_-24-24_0-3_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp1_PADoubleMuon_Data_%d.root", multMin, multMax, ptMin[ipt], ptMax[ipt], MupT.Data(), trkptversion.Data(), ibin);
			fname2[ipt] = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_-24-24_0-3_MupT%s_trk%s/Sort_OniaTree_Reco_Pbp2_PADoubleMuon_Data_%d.root", multMin, multMax, ptMin[ipt], ptMax[ipt], MupT.Data(), trkptversion.Data(), ibin);
			fname3[ipt] = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_-24-24_0-3_MupT%s_trk%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_Data_%d.root", multMin, multMax, ptMin[ipt], ptMax[ipt], MupT.Data(), trkptversion.Data(), ibin);
			fname4[ipt] = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_-24-24_0-3_MupT%s_trk%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_Data_%d.root", multMin, multMax, ptMin[ipt], ptMax[ipt], MupT.Data(), trkptversion.Data(), ibin);
			//fname1[ipt] = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_-24-24_0-3_MupT%s/Sort_OniaTree_Reco_Pbp1_PADoubleMuon_Data_%d.root", multMin, multMax, ptMin[ipt], ptMax[ipt], MupT.Data(), ibin);
			//fname2[ipt] = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_-24-24_0-3_MupT%s/Sort_OniaTree_Reco_Pbp2_PADoubleMuon_Data_%d.root", multMin, multMax, ptMin[ipt], ptMax[ipt], MupT.Data(), ibin);
			//fname3[ipt] = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_-24-24_0-3_MupT%s/Sort_OniaTree_Reco_pPb1_PADoubleMuon_Data_%d.root", multMin, multMax, ptMin[ipt], ptMax[ipt], MupT.Data(), ibin);
			//fname4[ipt] = Form("root://cms-xrdr.private.lo:2094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_-24-24_0-3_MupT%s/Sort_OniaTree_Reco_pPb2_PADoubleMuon_Data_%d.root", multMin, multMax, ptMin[ipt], ptMax[ipt], MupT.Data(), ibin);
			tin1_tmp->Add(fname1[ipt].Data());
			tin1_tmp->Add(fname2[ipt].Data());
			tin1_tmp->Add(fname3[ipt].Data());
			tin1_tmp->Add(fname4[ipt].Data());
		}
	}
	TTree* tin1 = tin1_tmp->CloneTree();
	tin1_tmp->Reset();

	TFile* facc = new TFile("../AccEff/Plots/acc_acc_upsi_816.root", "READ");
	TFile* feff = new TFile("../AccEff/Plots/EffPlots_Upsilon_1S_Ny5_MupT3p5.root", "READ");
//}}}

//canvas and hist{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1200, 1200);
	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 1200, 1200);
	TCanvas* c3 = new TCanvas("c3", "", 0, 0, 1200, 1200);
	TCanvas* c4 = new TCanvas("c4", "", 0, 0, 1200, 1200);
	c1->Divide(3, 3);
	c2->Divide(3, 3);
	c3->Divide(3, 3);
	c4->Divide(3, 3);
	TH1D* heta_tot[9];
	TH1D* heta_peak[9];
	TH1D* heta_lbkg[9];
	TH1D* heta_hbkg[9];
	for(Int_t i = 0; i < 9; i++)
	{
		heta_tot[i] = new TH1D(Form("heta_tot_%d", i), ";|#eta|;Entries", 50, 0, 5);
		heta_peak[i] = new TH1D(Form("heta_peak_%d", i), ";|#eta|;Entries", 50, 0, 5);
		heta_lbkg[i] = new TH1D(Form("heta_lbkg_%d", i), ";|#eta|;Entries", 50, 0, 5);
		heta_hbkg[i] = new TH1D(Form("heta_hbkg_%d", i), ";|#eta|;Entries", 50, 0, 5);
		FormTH1Marker(heta_tot[i], 0, 3, 1.2);
		FormTH1Marker(heta_peak[i], 0, 3, 1.2);
		FormTH1Marker(heta_lbkg[i], 0, 3, 1.2);
		FormTH1Marker(heta_hbkg[i], 0, 3, 1.2);
	}
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
//}}}

//get variables{{{
	Int_t mult;
	Int_t Ntrg_Reco;
	TClonesArray* Vec_trg_Reco;
	Vec_trg_Reco = 0;

	TBranch* b_mult;
	TBranch* b_Ntrg_Reco;
	TBranch* b_Vec_trg_Reco;

	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("Ntrg_Reco", &Ntrg_Reco, &b_Ntrg_Reco);
	tin1->SetBranchAddress("Vec_trg_Reco", &Vec_trg_Reco, &b_Vec_trg_Reco);

	TLorentzVector* vec_trg_Reco = new TLorentzVector;
	vec_trg_Reco = 0;
//}}}

	const Int_t Nevt = tin1->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%10000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);

		for(Int_t itrg = 0; itrg < Ntrg_Reco; itrg++)
		{
			vec_trg_Reco = (TLorentzVector*) Vec_trg_Reco->At(itrg);
			if(vec_trg_Reco == 0) continue;
			Double_t trg_y = vec_trg_Reco->Rapidity();
			Double_t trg_pt = vec_trg_Reco->Pt();
			Double_t trg_eta = vec_trg_Reco->Eta();
			Double_t trg_phi = vec_trg_Reco->Phi();
			Double_t trg_m = vec_trg_Reco->M();

			Double_t upacc = 1.;
			Double_t upeff = 1.;
			if(Weight)
			{
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
			}
			for(Int_t ipts = 0; ipts < 9; ipts++)
			{
				if( trg_pt >= ptval[ipts] && trg_pt < ptval[ipts+1] ) heta_tot[ipts]->Fill(TMath::Abs(trg_eta), 1./( (double)upacc*upeff));
				if( trg_pt >= ptval[ipts] && trg_pt < ptval[ipts+1] && (trg_m > 9 && trg_m < 10) ) heta_peak[ipts]->Fill(TMath::Abs(trg_eta), 1./( (double)upacc*upeff));
				if( trg_pt >= ptval[ipts] && trg_pt < ptval[ipts+1] && trg_m < 9 ) heta_lbkg[ipts]->Fill(TMath::Abs(trg_eta), 1./( (double)upacc*upeff));
				if( trg_pt >= ptval[ipts] && trg_pt < ptval[ipts+1] && trg_m > 11 ) heta_hbkg[ipts]->Fill(TMath::Abs(trg_eta), 1./( (double)upacc*upeff));
			}
		}
	}

	for(Int_t ipts = 0; ipts < 9; ipts++)
	{
		c1->cd(ipts+1);
		heta_tot[ipts]->Draw("pe");
		c2->cd(ipts+1);
		heta_peak[ipts]->Draw("pe");
		c3->cd(ipts+1);
		heta_lbkg[ipts]->Draw("pe");
		c4->cd(ipts+1);
		heta_hbkg[ipts]->Draw("pe");
	}
	c1->SaveAs(Form("Plots/Di-mu_eta_dist_mult_%d-%d_MupT%s_total.pdf", multMin, multMax, MupT.Data()));
	c2->SaveAs(Form("Plots/Di-mu_eta_dist_mult_%d-%d_MupT%s_peak.pdf", multMin, multMax, MupT.Data()));
	c3->SaveAs(Form("Plots/Di-mu_eta_dist_mult_%d-%d_MupT%s_lowbkg.pdf", multMin, multMax, MupT.Data()));
	c4->SaveAs(Form("Plots/Di-mu_eta_dist_mult_%d-%d_MupT%s_highbkg.pdf", multMin, multMax, MupT.Data()));
	TFile* fout = new TFile(Form("Plots/Di-mu_eta_dist_mult_%d-%d_MupT%s.root", multMin, multMax, MupT.Data()), "RECREATE");
	fout->cd();
	for(Int_t ipts = 0; ipts < 9; ipts++)
	{
		heta_tot[ipts]->Write();
		heta_peak[ipts]->Write();
		heta_lbkg[ipts]->Write();
		heta_hbkg[ipts]->Write();
	}
}
