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

using namespace std;
using namespace RooFit;
//}}}

void DrawAcc(const Int_t Generation = 1, const TString MupT = "3p5", const Bool_t isRW = true)
{
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/Plots";

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

	const Int_t Ny = 4;
	const Double_t ybin[Ny+1] = {0.0, 1.6, 1.8, 2.1, 2.4};
	const TString yabin[Ny+1] = {"00", "16", "18", "21", "24"};

	TFile* fAcc = new TFile(Form("Plots/AccPlots_Upsilon_%dS_RW%o_v78_MupT%s_tmp.root", Generation, isRW, MupT.Data()), "READ");
	TH1D* hGenPt = (TH1D*) fAcc->Get("hGenPt");
	TH1D* hAccGenPt = (TH1D*) fAcc->Get("hAccGenPt");
	TH1D* hGeny = (TH1D*) fAcc->Get("hGeny");
	TH1D* hAccGeny = (TH1D*) fAcc->Get("hAccGeny");
	TH1D* hGen[Ny];
	TH1D* hAccGen[Ny];
	for(Int_t iy = 0; iy < Ny; iy++)
	{
		hGen[iy] = (TH1D*) fAcc->Get(Form("hGen%s%s", yabin[iy].Data(), yabin[iy+1].Data()));
		hAccGen[iy] = (TH1D*) fAcc->Get(Form("hAccGen%s%s", yabin[iy].Data(), yabin[iy+1].Data()));
	}

//Draw integrated{{{
	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.045);

	TCanvas* cGenPt = new TCanvas("cGenPt", "", 0, 0, 600, 600);
	cGenPt->cd();
	hGenPt->Draw("pe");
	cGenPt->SaveAs(Form("Plots/GenPt_tot_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, isRW, MupT.Data()));

	TCanvas* cAccGenPt = new TCanvas("cAccGenPt", "", 0, 0, 600, 600);
	cAccGenPt->cd();
	hAccGenPt->Draw("pe");
	cAccGenPt->SaveAs(Form("Plots/GenPt_inAcc_tot_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, isRW, MupT.Data()));

	TH1D* hAccPt = (TH1D*) hAccGenPt->Clone("hAccPt");
	hAccPt->Divide(hGenPt);
	hAccPt->GetYaxis()->SetTitle("Acc.");

	TCanvas* cAccPt = new TCanvas("cAccPt", "", 0, 0, 600, 600);
	cAccPt->cd();
	hAccPt->SetMaximum(1.0);
	hAccPt->SetMinimum(0.0);
	hAccPt->Draw("pe");
	lt1->DrawLatex(0.2, 0.82, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.2, 0.75, Form("|#eta^{#mu}| < 2.4"));
	cAccPt->SaveAs(Form("Plots/AccPt_tot_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, isRW, MupT.Data()));

	TCanvas* cGeny = new TCanvas("cGeny", "", 0, 0, 600, 600);
	cGeny->cd();
	hGeny->Draw("pe");
	cGeny->SaveAs(Form("Plots/Geny_tot_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, isRW, MupT.Data()));

	TCanvas* cAccGeny = new TCanvas("cAccGeny", "", 0, 0, 600, 600);
	cAccGeny->cd();
	hAccGeny->Draw("pe");
	cAccGeny->SaveAs(Form("Plots/Geny_inAcc_tot_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, isRW, MupT.Data()));

	TH1D* hAccy = (TH1D*) hAccGeny->Clone("hAccy");
	hAccy->Divide(hGeny);
	hAccy->GetYaxis()->SetTitle("Acc.");

	TCanvas* cAccy = new TCanvas("cAccy", "", 0, 0, 600, 600);
	cAccy->cd();
	hAccy->SetMaximum(1.0);
	hAccy->SetMinimum(0.0);
	hAccy->Draw("pe");
	lt1->DrawLatex(0.2, 0.82, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.2, 0.75, Form("|#eta^{#mu}| < 2.4"));
	cAccy->SaveAs(Form("Plots/Accy_tot_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, isRW, MupT.Data()));
//}}}

	TH1D* hAcc[Ny];
	for(Int_t iy = 0; iy < Ny; iy++)
	{
		hAcc[iy] = (TH1D*) hAccGen[iy]->Clone(Form("hAcc%s%s", yabin[iy].Data(), yabin[iy+1].Data()));
		hAcc[iy]->Divide(hGen[iy]);
		hAcc[iy]->GetYaxis()->SetTitle("Acc.");
	}
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	c1->cd();
	TLegend* leg1 = new TLegend(0.15, 0.6, 0.5, 0.85);
	FormLegend(leg1, 0.045);
	TLatex* lt2 = new TLatex();
	FormLatex(lt2, 12, 0.045);
	for(Int_t iy = 0; iy < Ny; iy++)
	{
		if(iy == 0)
		{
			hAcc[iy]->SetMaximum(1.2);
			hAcc[iy]->SetMinimum(0.0);
			hAcc[iy]->Draw("pe");
		}
		else hAcc[iy]->Draw("samepe");
		leg1->AddEntry(hAcc[iy], Form("%.1f < |y^{#varUpsilon}| #leq %.1f", ybin[iy], ybin[iy+1]), "pe");
	}
	leg1->Draw();
	lt2->DrawLatex(0.65, 0.82, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt2->DrawLatex(0.65, 0.75, Form("|#eta^{#mu}| < 2.4"));
	c1->SaveAs(Form("Plots/Acc_comp_Upsilon_%dS_RW%o_MupT%s.pdf", Generation, isRW, MupT.Data()));

	TFile* fout = new TFile(Form("Plots/AccPlots_Upsilon_%dS_RW%o_v78_MupT%s.root", Generation, isRW, MupT.Data()), "RECREATE");
	fout->cd();
	hAccPt->Write();
	hAccy->Write();
	for(Int_t iy = 0; iy < Ny; iy++)
	{
		hAcc[iy]->Write();
	}
	fout->Close();
}
