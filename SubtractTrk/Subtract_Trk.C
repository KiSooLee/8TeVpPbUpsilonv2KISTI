//Headers{{{
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <TMath.h>
#include "../Headers/Upsilon.h"
#include "../Headers/Style_Upv2.h"
//}}}

void Subtract_Trk(const Bool_t isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const TString version = "v13", const TString MupT = "4", const bool Weight = true)
{
	SetStyle();
	gStyle->SetOptFit(0000);

//set fitting condition name{{{
	TString Away[3];
	Away[0] = "1";
	Away[1] = "1p5";
	Away[2] = "2";
	TString Fine[2];
	Fine[0] = "fine";
	Fine[1] = "coarse";
	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString Ffit;
	if(maxF == 2) Ffit = "";
	else if(maxF == 3) Ffit = "_tra";
	else
	{
		cout << "there is no such Furier function" << endl;
		return;
	}
//}}}

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fDIR = mainDIR + Form("/V2File/%s", version.Data());
	TString aDIR[3];
	TString pDIR[3];

	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		aDIR[iaway] = mainDIR + Form("/V2Plot/%s/Away%s", version.Data(), Away[iaway].Data());
		pDIR[iaway] = mainDIR + Form("/V2Plot/%s/Away%s/MupT%s", version.Data(), Away[iaway].Data(), MupT.Data());
	}

	void * dirf = gSystem->OpenDirectory(fDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fDIR.Data(), kTRUE);

	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		void * dira = gSystem->OpenDirectory(aDIR[iaway].Data());
		if(dira) gSystem->FreeDirectory(dira);
		else gSystem->mkdir(aDIR[iaway].Data(), kTRUE);

		void * dirp = gSystem->OpenDirectory(pDIR[iaway].Data());
		if(dirp) gSystem->FreeDirectory(dirp);
		else gSystem->mkdir(pDIR[iaway].Data(), kTRUE);
	}
//}}}

//Define canvas for yield and vn dist{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* hist;
	if(isMC) hist = new TH1D("hist", "", 20, 8.5, 10.);
	else hist = new TH1D("hist", "", 20, 8., 14.);
	FormTH1Marker(hist, 0, 0, 1.4);
	hist->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
	hist->GetYaxis()->SetTitle("v_{2}^{S+B}");
	if(ptMin < 5)
	{
		hist->SetMinimum(-0.2);
		hist->SetMaximum(0.2);
	}
	else if(ptMin < 8)
	{
		hist->SetMinimum(-0.1);
		hist->SetMaximum(0.3);
	}
	else
	{
		hist->SetMinimum(-0.1);
		hist->SetMaximum(0.4);
	}
//}}}

	TFile* fout;
	fout = new TFile(Form("V2File/%s/v2_sig_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_weight%o%s.root", version.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Weight, Ffit.Data()), "RECREATE");

//Get vn file{{{
	TFile* fsigtrk;
	TFile* ftrktrk;
	fsigtrk = new TFile(Form("../ExtractV2/ProjDist/DistFiles/%s/MupT%s/v2_dist_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_weight%o%s.root", version.Data(), MupT.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Weight, Ffit.Data()), "READ");
	ftrktrk = new TFile(Form("../ExtractV2/ProjDist/DistFiles/%s/MupT%s/trk_v2_dist_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_weight%o%s.root", version.Data(), MupT.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Weight, Ffit.Data()), "READ");
//}}}

	for(Int_t ifine = 0; ifine < 2; ifine++)
	{
		for(Int_t iaway = 0; iaway < 3; iaway++)
		{
//calculate v2 value{{{
			TGraphErrors* gsigtrk = (TGraphErrors*) fsigtrk->Get(Form("gv2_Away%s_%s", Away[iaway].Data(), Fine[ifine].Data()));
			TGraphErrors* gtrktrk = (TGraphErrors*) ftrktrk->Get(Form("gv2_Away%s_%s", Away[iaway].Data(), Fine[ifine].Data()));

			Double_t v2xsigtrk[200];
			Double_t v2ysigtrk[200];
			Double_t v2xtrktrk[200];
			Double_t v2ytrktrk[200];
			Double_t Exsigtrk[200];
			Double_t Eysigtrk[200];
			Double_t Extrktrk[200];
			Double_t Eytrktrk[200];
			Double_t v2ysig[200];
			Double_t Eysig[200];

			for(Int_t ibin = 0; ibin < gsigtrk->GetN(); ibin++)
			{
				gsigtrk->GetPoint(ibin, v2xsigtrk[ibin], v2ysigtrk[ibin]);
				gtrktrk->GetPoint(ibin, v2xtrktrk[ibin], v2ytrktrk[ibin]);
				Exsigtrk[ibin] = gsigtrk->GetErrorX(ibin);
				Extrktrk[ibin] = gtrktrk->GetErrorX(ibin);
				Eysigtrk[ibin] = gsigtrk->GetErrorY(ibin);
				Eytrktrk[ibin] = gtrktrk->GetErrorY(ibin);

				v2ysig[ibin] = v2ysigtrk[ibin]/TMath::Sqrt(v2ytrktrk[ibin]);
				Eysig[ibin] = fabs(v2ysig[ibin])*TMath::Sqrt( TMath::Power( Eysigtrk[ibin]/v2ysigtrk[ibin], 2 )+TMath::Power( Eytrktrk[ibin]/(2*v2ytrktrk[ibin]), 2 ) );
			}

			TGraphErrors* gv2 = new TGraphErrors(gsigtrk->GetN(), v2xsigtrk, v2ysig, Exsigtrk, Eysig);
			gv2->SetName(Form("gv2_Away%s_%s", Away[iaway].Data(), Fine[ifine].Data()));
			gv2->SetMarkerStyle(20);

			TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
			c1->cd();
			hist->Draw();
			gv2->Draw("samepe");
			c1->SaveAs(Form("V2Plot/%s/Away%s/MupT%s/Sigv2_dist_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_weight%o%s.pdf", version.Data(), Away[iaway].Data(), MupT.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Weight, Ffit.Data()));

			fout->cd();
			gv2->Write();
//}}}
		}
	}
}
