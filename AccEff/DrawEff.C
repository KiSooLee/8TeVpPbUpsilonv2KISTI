//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TSystem.h>
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
//}}}

void DrawEff(const Int_t Generation = 1, const TString MupT = "3p5", const Bool_t isRW = true, const Bool_t isTnP = true)
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

	const Int_t Ny = 5;
	const Double_t ybins[Ny] = {0., 1.6, 1.8, 2.1, 2.4};

	TFile* fin = new TFile(Form("Plots/EffPlots_Upsilon_%dS_RW%o_TnP%o_MupT%s.root", Generation, isRW, isTnP, MupT.Data()), "READ");

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* h1[Ny-1];
	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.05);
	lt1->SetNDC();
	TLegend* leg1 = new TLegend(0.5, 0.18, 0.85, 0.48);
	FormLegend(leg1, 0.05);
	c1->cd();
	for(Int_t iy = 0; iy < Ny-1; iy++)
	{
		h1[iy] = (TH1D*) fin->Get(Form("hEff_%d", iy));
		if(iy < 2) FormTH1Marker(h1[iy], iy, iy, 1.6);
		else FormTH1Marker(h1[iy], iy, iy, 2.0);
		if(iy == 0) h1[iy]->Draw("pe");
		else h1[iy]->Draw("samepe");
		leg1->AddEntry(h1[iy], Form("%.1f < |y^{#varUpsilon}| #leq %.1f", ybins[iy], ybins[iy+1]), "pe");
	}
	leg1->Draw();
	lt1->DrawLatex(0.16, 0.28, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.16, 0.20, Form("|#eta^{#mu}| > 2.4 GeV/c"));
	c1->SaveAs(Form("Plots/Eff_comp_Upsilon_%dS_RW%o_TnP%o_MupT%s.pdf", Generation, isRW, isTnP, MupT.Data()));
}
