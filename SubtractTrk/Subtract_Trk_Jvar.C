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

void Subtract_Trk_Jvar(const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 50, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Bool_t isfine = true, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v41", const TString MupT = "4")
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
	hist->SetMaximum(0.15);
//}}}

	TFile* fout = new TFile(Form("V2File/MupT%s/Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_Jvar.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fsigtrk;
	TFile* ftrktrk;
	fsigtrk = new TFile(Form("../LMsub/File/Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_Jvar.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	ftrktrk = new TFile(Form("../LMsub/File/trk_Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
//}}}

//calculate v2 value{{{
	TGraphErrors* gsigtrk_pl = (TGraphErrors*) fsigtrk->Get(Form("gv2sub_pl"));
	TGraphErrors* gsigtrk_mi = (TGraphErrors*) fsigtrk->Get(Form("gv2sub_mi"));
	TGraphErrors* gtrktrk = (TGraphErrors*) ftrktrk->Get(Form("gv2sub"));

	Double_t v2xsigtrk_pl[200];
	Double_t v2xsigtrk_mi[200];
	Double_t v2ysigtrk_pl[200];
	Double_t v2ysigtrk_mi[200];
	Double_t v2xtrktrk[200];
	Double_t v2ytrktrk[200];
	Double_t Exsigtrk_pl[200];
	Double_t Exsigtrk_mi[200];
	Double_t Eysigtrk_pl[200];
	Double_t Eysigtrk_mi[200];
	Double_t Extrktrk[200];
	Double_t Eytrktrk[200];
	Double_t v2ysig_pl[200];
	Double_t v2ysig_mi[200];
	Double_t Eysig_pl[200];
	Double_t Eysig_mi[200];

	for(Int_t ibin = 0; ibin < gsigtrk_pl->GetN(); ibin++)
	{
		gsigtrk_pl->GetPoint(ibin, v2xsigtrk_pl[ibin], v2ysigtrk_pl[ibin]);
		gsigtrk_mi->GetPoint(ibin, v2xsigtrk_mi[ibin], v2ysigtrk_mi[ibin]);
		gtrktrk->GetPoint(ibin, v2xtrktrk[ibin], v2ytrktrk[ibin]);
		Exsigtrk_pl[ibin] = gsigtrk_pl->GetErrorX(ibin);
		Exsigtrk_mi[ibin] = gsigtrk_mi->GetErrorX(ibin);
		Extrktrk[ibin] = gtrktrk->GetErrorX(ibin);
		Eysigtrk_pl[ibin] = gsigtrk_pl->GetErrorY(ibin);
		Eysigtrk_mi[ibin] = gsigtrk_mi->GetErrorY(ibin);
		Eytrktrk[ibin] = gtrktrk->GetErrorY(ibin);

		if(v2ytrktrk[ibin] > 0)
		{
			v2ysig_pl[ibin] = v2ysigtrk_pl[ibin]/TMath::Sqrt(v2ytrktrk[ibin]);
			v2ysig_mi[ibin] = v2ysigtrk_mi[ibin]/TMath::Sqrt(v2ytrktrk[ibin]);
		}
		else if(v2ytrktrk[ibin] < 0)
		{
			v2ysig_pl[ibin] = v2ysigtrk_pl[ibin]/TMath::Sqrt(fabs(v2ytrktrk[ibin]));
			v2ysig_mi[ibin] = v2ysigtrk_mi[ibin]/TMath::Sqrt(fabs(v2ytrktrk[ibin]));
		}
		else
		{
			v2ysig_pl[ibin] = v2ysigtrk_pl[ibin];
			v2ysig_mi[ibin] = v2ysigtrk_mi[ibin];
		}

		//if(ptMin == 4 && ibin == 0) Eysig[ibin] = 0.1;
		//else Eysig[ibin] = fabs(v2ysig[ibin])*TMath::Sqrt( TMath::Power( Eysigtrk[ibin]/v2ysigtrk[ibin], 2 )+TMath::Power( Eytrktrk[ibin]/(2*v2ytrktrk[ibin]), 2 ) );

		Eysig_pl[ibin] = fabs(v2ysig_pl[ibin])*TMath::Sqrt( TMath::Power( Eysigtrk_pl[ibin]/v2ysigtrk_pl[ibin], 2 )+TMath::Power( Eytrktrk[ibin]/(2*v2ytrktrk[ibin]), 2 ) );
		Eysig_mi[ibin] = fabs(v2ysig_mi[ibin])*TMath::Sqrt( TMath::Power( Eysigtrk_mi[ibin]/v2ysigtrk_mi[ibin], 2 )+TMath::Power( Eytrktrk[ibin]/(2*v2ytrktrk[ibin]), 2 ) );
	}

	TGraphErrors* gv2_pl = new TGraphErrors(gsigtrk_pl->GetN(), v2xsigtrk_pl, v2ysig_pl, Exsigtrk_pl, Eysig_pl);
	gv2_pl->SetName(Form("gv2_pl"));
	gv2_pl->SetMarkerStyle(20);
	TGraphErrors* gv2_mi = new TGraphErrors(gsigtrk_mi->GetN(), v2xsigtrk_mi, v2ysig_mi, Exsigtrk_mi, Eysig_mi);
	gv2_mi->SetName(Form("gv2_mi"));
	gv2_mi->SetMarkerStyle(20);
	gv2_mi->SetMarkerColor(kRed+1);
	gv2_mi->SetLineColor(kRed+1);

	c1->cd();
	hist->Draw();
	gv2_pl->Draw("samepe");
	gv2_mi->Draw("samepe");
	c1->SaveAs(Form("V2Plot/MupT%s/Final_v2_dist_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_Jvar.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));
	fout->cd();
	gv2_pl->Write();
	gv2_mi->Write();
	fout->Close();
//}}}
}
