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

void Subtract_Trk_MC(const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 50, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Bool_t isfine = true, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v41", const TString MupT = "4")
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
	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
	TH1D* hist = new TH1D("hist", ";p_{T} (GeV/c);v_{2}(#varUpsilon)", 30, 0, 30);
	FormTH1Marker(hist, 0, 0, 1.4);
	hist->SetMinimum(-0.005);
	hist->SetMaximum(0.005);
//}}}

	TFile* fout = new TFile(Form("V2File/MupT%s/Final_v2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_by_%s_jet_%s_by_%s_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fsigtrk = new TFile(Form("../LMsub/File/Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_pol2_MupT%s_MC.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	TFile* ftrktrk_reco = new TFile(Form("../LMsub/File/trk_Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_MupT%s_MC_Reco.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	TFile* ftrktrk_gen = new TFile(Form("../LMsub/File/trk_Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_MupT%s_MC_Gen.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
//}}}

//calculate v2 value{{{
	TGraphErrors* gsigtrk_reco = (TGraphErrors*) fsigtrk->Get(Form("gv2sub_reco"));
	TGraphErrors* gsigtrk_gen = (TGraphErrors*) fsigtrk->Get(Form("gv2sub_gen"));
	TGraphErrors* gtrktrk_reco = (TGraphErrors*) ftrktrk_reco->Get(Form("gv2sub"));
	ftrktrk_reco->SetName("gv2_trk_reco");
	TGraphErrors* gtrktrk_gen = (TGraphErrors*) ftrktrk_gen->Get(Form("gv2sub"));
	ftrktrk_gen->SetName("gv2_trk_gen");

	Double_t v2xsigtrk_reco[200];
	Double_t v2ysigtrk_reco[200];
	Double_t v2xtrktrk_reco[200];
	Double_t v2ytrktrk_reco[200];
	Double_t Exsigtrk_reco[200];
	Double_t Eysigtrk_reco[200];
	Double_t Eytrktrk_reco[200];

	Double_t v2xsigtrk_gen[200];
	Double_t v2ysigtrk_gen[200];
	Double_t v2xtrktrk_gen[200];
	Double_t v2ytrktrk_gen[200];
	Double_t Exsigtrk_gen[200];
	Double_t Eysigtrk_gen[200];
	Double_t Eytrktrk_gen[200];

	Double_t v2ysig_reco[200];
	Double_t Eysig_reco[200];
	Double_t v2ysig_gen[200];
	Double_t Eysig_gen[200];

	for(Int_t ibin = 0; ibin < gsigtrk_reco->GetN(); ibin++)
	{
		gsigtrk_reco->GetPoint(ibin, v2xsigtrk_reco[ibin], v2ysigtrk_reco[ibin]);
		gsigtrk_gen->GetPoint(ibin, v2xsigtrk_gen[ibin], v2ysigtrk_gen[ibin]);
		gtrktrk_reco->GetPoint(ibin, v2xtrktrk_reco[ibin], v2ytrktrk_reco[ibin]);
		gtrktrk_gen->GetPoint(ibin, v2xtrktrk_gen[ibin], v2ytrktrk_gen[ibin]);

		Exsigtrk_reco[ibin] = gsigtrk_reco->GetErrorX(ibin);
		Eysigtrk_reco[ibin] = gsigtrk_reco->GetErrorY(ibin);
		Exsigtrk_gen[ibin] = gsigtrk_gen->GetErrorX(ibin);
		Eysigtrk_gen[ibin] = gsigtrk_gen->GetErrorY(ibin);

		Eytrktrk_reco[ibin] = gtrktrk_reco->GetErrorY(ibin);
		Eytrktrk_gen[ibin] = gtrktrk_gen->GetErrorY(ibin);

		if(v2ytrktrk_reco[ibin] > 0) v2ysig_reco[ibin] = v2ysigtrk_reco[ibin]/TMath::Sqrt(v2ytrktrk_reco[ibin]);
		else if(v2ytrktrk_reco[ibin] < 0) v2ysig_reco[ibin] = v2ysigtrk_reco[ibin]/TMath::Sqrt(fabs(v2ytrktrk_reco[ibin]));
		else v2ysig_reco[ibin] = v2ysigtrk_reco[ibin];

cout << "RECO: " << ibin << ": " << v2ysigtrk_reco[ibin] << " / " << v2ytrktrk_reco[ibin] << " ^(1/2) = " << v2ysig_reco[ibin] << endl;

		//if(v2ytrktrk_gen[ibin] > 0) v2ysig_gen[ibin] = v2ysigtrk_gen[ibin]/TMath::Sqrt(v2ytrktrk_gen[ibin]);
		//else if(v2ytrktrk_gen[ibin] < 0) v2ysig_gen[ibin] = v2ysigtrk_gen[ibin]/TMath::Sqrt(fabs(v2ytrktrk_gen[ibin]));
		//else v2ysig_gen[ibin] = v2ysigtrk_gen[ibin];
		v2ysig_gen[ibin] = v2ysigtrk_gen[ibin];

cout << "GEN: " << ibin << ": " << v2ysigtrk_gen[ibin] << " / " << v2ytrktrk_gen[ibin] << " ^(1/2) = " << v2ysig_gen[ibin] << endl;

		Eysig_reco[ibin] = fabs(v2ysig_reco[ibin])*TMath::Sqrt( TMath::Power( Eysigtrk_reco[ibin]/v2ysigtrk_reco[ibin], 2 )+TMath::Power( Eytrktrk_reco[ibin]/(2*v2ytrktrk_reco[ibin]), 2 ) );
cout << "reco error: " << "pt bin: " << ibin << Eysig_reco[ibin] << endl;
		//Eysig_gen[ibin] = fabs(v2ysig_gen[ibin])*TMath::Sqrt( TMath::Power( Eysigtrk_gen[ibin]/v2ysigtrk_gen[ibin], 2 )+TMath::Power( Eytrktrk_gen[ibin]/(2*v2ytrktrk_gen[ibin]), 2 ) );
		Eysig_gen[ibin] = fabs(v2ysig_gen[ibin]);
	}

	TGraphErrors* gv2_reco = new TGraphErrors(gsigtrk_reco->GetN(), v2xsigtrk_reco, v2ysig_reco, Exsigtrk_reco, Eysig_reco);
	gv2_reco->SetName(Form("gv2_reco"));
	gv2_reco->SetMarkerStyle(20);
	TGraphErrors* gv2_gen = new TGraphErrors(gsigtrk_gen->GetN(), v2xsigtrk_gen, v2ysig_gen, Exsigtrk_gen, Eysig_gen);
	gv2_gen->SetName(Form("gv2_gen"));
	gv2_gen->SetMarkerStyle(20);

	c1->cd();
	hist->SetTitle("RECO");
	hist->Draw();
	gv2_reco->Draw("samepe");
	c1->SaveAs(Form("V2Plot/MupT%s/Final_v2_dist_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_by_%s_jet_%s_by_%s_pol2_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c2->cd();
	hist->SetTitle("GEN");
	//hist->SetMinimum(-0.3);
	hist->Draw();
	gv2_gen->Draw("samepe");
	c2->SaveAs(Form("V2Plot/MupT%s/Final_v2_dist_Gen_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_by_%s_jet_%s_by_%s_pol2_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	fout->cd();
	gv2_reco->Write();
	gv2_gen->Write();
	fout->Close();
//}}}
}
