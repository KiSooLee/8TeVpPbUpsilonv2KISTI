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

void Subtract_Trk_GEN(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Bool_t isfine = true, const TString version = "v56", const TString MupT = "4")
{
	SetStyle();

//set fitting condition name{{{
	TString Fine;
	if(isfine) Fine = "fine";
	else Fine = "coarse";
	TString Ffit;
	if(maxF == 2) Ffit = "_quad";
	else if(maxF == 3) Ffit = "_tra";
	else
	{
		cout << "there is no such Furier function" << endl;
		return;
	}
//}}}

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString pDIR = mainDIR + Form("/V2Plot/MupT%s", MupT.Data());
	TString fDIR = mainDIR + Form("/V2File/MupT%s", MupT.Data());

	void * dirp = gSystem->OpenDirectory(pDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(pDIR.Data(), kTRUE);
	void * dirf = gSystem->OpenDirectory(fDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fDIR.Data(), kTRUE);
//}}}

//Define canvas for yield and vn dist{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* hist = new TH1D("hist", ";p_{T} (GeV/c);v_{2}(#varUpsilon)", 30, 0, 30);
	FormTH1Marker(hist, 0, 0, 1.4);
	hist->SetMinimum(-0.05);
	hist->SetMaximum(0.8);
//}}}

	TFile* fout = new TFile(Form("V2File/MupT%s/Final_v2_Gen_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_MupT%s.root", MupT.Data(), multMin, multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fsigtrk[pt_narr];
	TFile* ftrktrk[pt_narr];
	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		fsigtrk[ipt] = new TFile(Form("../ExtractV2/ProjDist/DistFiles/%s/MupT%s/v2_dist_Gen_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_MupT%s%s.root", version.Data(), MupT.Data(), multMin, multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Ffit.Data()), "READ");

		ftrktrk[ipt] = new TFile(Form("../ExtractV2/ProjDist/DistFiles/%s/MupT%s/trk_v2_dist_Gen_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_MupT%s%s.root", version.Data(), MupT.Data(), multMin, multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Ffit.Data()), "READ");
	}
//}}}

//calculate v2 value{{{
	TH1D* hsigtrk[pt_narr];
	TH1D* htrktrk[pt_narr];
	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		hsigtrk[ipt] = (TH1D*) fsigtrk[ipt]->Get(Form("hRef_coarse"));
		htrktrk[ipt] = (TH1D*) ftrktrk[ipt]->Get(Form("hRef_coarse"));
	}

	Double_t v2xsigtrk[200];
	Double_t v2ysigtrk[200];
	//Double_t v2xtrktrk[200];
	Double_t v2ytrktrk[200];
	Double_t Exsigtrk[200];
	Double_t Eysigtrk[200];
	//Double_t Extrktrk[200];
	Double_t Eytrktrk[200];
	Double_t v2ysig[200];
	Double_t Eysig[200];

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		v2xsigtrk[ipt] = ptBinsArr[ipt] + (ptBinsArr[ipt+1]-ptBinsArr[ipt])/2;
		v2ysigtrk[ipt] = hsigtrk[ipt]->GetBinContent(1);
		Eysigtrk[ipt] = hsigtrk[ipt]->GetBinError(1);
		v2ytrktrk[ipt] = htrktrk[ipt]->GetBinContent(1);
		Eytrktrk[ipt] = htrktrk[ipt]->GetBinError(1);

		if(v2ytrktrk[ipt] > 0) v2ysig[ipt] = v2ysigtrk[ipt]/TMath::Sqrt(v2ytrktrk[ipt]);
		else if(v2ytrktrk[ipt] < 0) v2ysig[ipt] = v2ysigtrk[ipt]/TMath::Sqrt(fabs(v2ytrktrk[ipt]));
		else v2ysig[ipt] = v2ysigtrk[ipt];

		Eysig[ipt] = fabs(v2ysig[ipt])*TMath::Sqrt( TMath::Power( Eysigtrk[ipt]/v2ysigtrk[ipt], 2 )+TMath::Power( Eytrktrk[ipt]/(2*v2ytrktrk[ipt]), 2 ) );
	}

	TGraphErrors* gv2 = new TGraphErrors(pt_narr-1, v2xsigtrk, v2ysig, Exsigtrk, Eysig);
	gv2->SetName(Form("gv2"));
	gv2->SetMarkerStyle(20);

	c1->cd();
	hist->Draw();
	gv2->Draw("samepe");
	c1->SaveAs(Form("V2Plot/MupT%s/Final_v2_dist_Gen_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_MupT%s.pdf", MupT.Data(), multMin, multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data()));
	fout->cd();
	gv2->Write();
	fout->Close();
//}}}
}
