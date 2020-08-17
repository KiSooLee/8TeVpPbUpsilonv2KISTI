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

void Subtract_Trk(const Bool_t isMC = false, const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 50, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Int_t bkgN = 0, const Bool_t isfine = true, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v41", const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Bool_t isTnP = true, const TString MupT = "4")
{
	SetStyle();

//set fitting condition name{{{
	TString Fine;
	if(isfine) Fine = "fine";
	else Fine = "coarse";
	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
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
	TString aDIR = mainDIR + Form("/V2Plot/MupT%s", MupT.Data());

	void * dira = gSystem->OpenDirectory(aDIR.Data());
	if(dira) gSystem->FreeDirectory(dira);
	else gSystem->mkdir(aDIR.Data(), kTRUE);
//}}}

//Define canvas for yield and vn dist{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* hist = new TH1D("hist", "", 30, 0, 30);
	FormTH1Marker(hist, 0, 0, 1.4);
	hist->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist->GetYaxis()->SetTitle("v_{2}");
	hist->SetMinimum(-0.05);
	hist->SetMaximum(0.15);
//}}}

	TFile* fout = new TFile(Form("V2Plot/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_by_%s_jet_%s_by_%s_Acc%o_Eff%o_TnP%o_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), isAccRW, isEffRW, isTnP, MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fsigtrk;
	TFile* ftrktrk;
	fsigtrk = new TFile(Form("../LMsub/File/Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_Acc%o_Eff%o_TnP%o_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), isAccRW, isEffRW, isTnP, MupT.Data()), "READ");
	ftrktrk = new TFile(Form("../LMsub/File/trk_Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
//}}}

//calculate v2 value{{{
	TGraphErrors* gsigtrk = (TGraphErrors*) fsigtrk->Get(Form("gv2sub"));
	TGraphErrors* gtrktrk = (TGraphErrors*) ftrktrk->Get(Form("gv2sub"));

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

		if(v2ytrktrk[ibin] > 0) v2ysig[ibin] = v2ysigtrk[ibin]/TMath::Sqrt(v2ytrktrk[ibin]);
		else if(v2ytrktrk[ibin] < 0) v2ysig[ibin] = v2ysigtrk[ibin]/TMath::Sqrt(fabs(v2ytrktrk[ibin]));
		else v2ysig[ibin] = v2ysigtrk[ibin];

		//if(ptMin == 4 && ibin == 0) Eysig[ibin] = 0.1;
		//else Eysig[ibin] = fabs(v2ysig[ibin])*TMath::Sqrt( TMath::Power( Eysigtrk[ibin]/v2ysigtrk[ibin], 2 )+TMath::Power( Eytrktrk[ibin]/(2*v2ytrktrk[ibin]), 2 ) );

		Eysig[ibin] = fabs(v2ysig[ibin])*TMath::Sqrt( TMath::Power( Eysigtrk[ibin]/v2ysigtrk[ibin], 2 )+TMath::Power( Eytrktrk[ibin]/(2*v2ytrktrk[ibin]), 2 ) );
	}

	TGraphErrors* gv2 = new TGraphErrors(gsigtrk->GetN(), v2xsigtrk, v2ysig, Exsigtrk, Eysig);
	gv2->SetName(Form("gv2"));
	gv2->SetMarkerStyle(20);

	c1->cd();
	hist->Draw();
	gv2->Draw("samepe");
	c1->SaveAs(Form("V2Plot/MupT%s/Final_v2_dist_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_by_%s_jet_%s_by_%s_Acc%o_Eff%o_TnP%o_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), isAccRW, isEffRW, isTnP, MupT.Data()));
	fout->cd();
	gv2->Write();
	fout->Close();
//}}}
}
