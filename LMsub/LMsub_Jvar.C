//Headers{{{
#include <Riostream.h> 
#include <TSystem.h> 
#include <TBrowser.h> 
#include <TROOT.h> 
#include <TStyle.h> 
#include <TFile.h> 
#include <TTree.h>
#include <TNtuple.h> 
#include <TCanvas.h> 
#include <TGraph.h> 
#include <TGraphAsymmErrors.h> 
#include <TGraphErrors.h> 
#include <TH1.h> 
#include <TH2.h> 
#include <TF1.h> 
#include <TProfile.h> 
#include <TMath.h> 
#include <TLegend.h> 
#include <TString.h> 
#include <TLatex.h> 
#include <TInterpreter.h> 
#include <fstream>
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
//}}}

void LMsub_Jvar(const Int_t multMinhi = 110, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 40, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 3, const Int_t AwayN = 1, const Bool_t isfine = true, const TString versionhi = "v19", const TString versionlow = "v20", const TString Jversionhi = "v19", const TString Jversionlow = "v20", const TString MupT = "3p5")
{
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fileDIR = mainDIR + Form("/File");
	TString plotDIR = mainDIR + Form("/Plots/Sub");

	void * dirf = gSystem->OpenDirectory(fileDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);

	void * dirp = gSystem->OpenDirectory(plotDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(plotDIR.Data(), kTRUE);
//}}}

//Define names{{{
	TString SorB[2] = {"sig", "bkg"};
	TString BandName[2] = {"short", "long"};
	TString Away;
	if(AwayN == 1) Away = "1";
	else if(AwayN == 2) Away = "1p5";
	else if(AwayN == 3) Away = "2";
	else
	{
		cout << "out of delta eta cut range list" << endl;
		return;
	}
	TString Fine;
	if(isfine == true) Fine = "fine";
	else Fine = "coarse";
	TString Ffit;
	if(maxF == 2) Ffit = "_quad";
	else if(maxF == 3) Ffit = "_tra";
	else
	{
		cout << "there is no such Furier function" << endl;
		return;
	}

	Int_t multMins[2];
	multMins[0] = multMinhi;
	multMins[1] = multMinlow;
	Int_t multMaxs[2];
	multMaxs[0] = multMaxhi;
	multMaxs[1] = multMaxlow;
	TString versions[2];
	versions[0] = Form("%s", versionhi.Data());
	versions[1] = Form("%s", versionlow.Data());
	const TString HorL[2] = {"hi", "low"};
//}}}

	const Int_t NPT = 4;
	TFile* fv2[2];
	TFile* fass[2][NPT];
	TFile* fjet[2][NPT];

	TGraphErrors* g1[2];
	TH1D* hass[2][NPT];
	Double_t Nass[2][NPT];
	Double_t JComp[2][NPT][2];
	Double_t JYield[2][NPT];
	for(Int_t imult = 0; imult < 2; imult++)
	{
		fv2[imult] = new TFile(Form("../SignalV2/V2Dist/V2File/%s/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_pol2_%s_%s_Data_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_OS_MupT%s%s.root", versions[imult].Data(), multMins[imult], multMaxs[imult], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Away.Data(), Fine.Data(), versions[imult].Data(), MupT.Data(), Ffit.Data()), "READ");
		TGraphErrors* gtemp = (TGraphErrors*) fv2[imult]->Get(Form("v2_1s_vs_pt"));
		g1[imult] = (TGraphErrors*) gtemp->Clone(Form("g1_%s", HorL[imult].Data()));

		for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
		{
			fass[imult][ipt] = new TFile(Form("Plots/Nass/Nass_dist_%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_Data.root", multMins[imult], multMaxs[imult], (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versions[imult].Data(), MupT.Data()), "READ");
			TH1D* htmpass = (TH1D*) fass[imult][ipt]->Get("h1");
			hass[imult][ipt] = (TH1D*) htmpass->Clone(Form("hass_%s_%d", HorL[imult].Data(), ipt));
			Nass[imult][ipt] = hass[imult][ipt]->GetMean();
		}
	}

	TFile* fJRatio = new TFile(Form("File/JRatio_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Jversionhi.Data(), Jversionlow.Data(), Fine.Data(), MupT.Data()), "READ");
	TF1* fitin = (TF1*) fJRatio->Get("fit1");
	Double_t JRatio = fitin->GetParameter(0);
	Double_t JRatioE = fitin->GetParError(0);

	Double_t v2xhi[NPT];
	Double_t v2yhi[NPT];
	Double_t v2xEhi[NPT];
	Double_t v2yEhi[NPT];
	Double_t v2xlow[NPT];
	Double_t v2ylow[NPT];
	Double_t v2xElow[NPT];
	Double_t v2yElow[NPT];
	Double_t v2sub_pl[NPT];
	Double_t v2sub_mi[NPT];
	Double_t v2subE[NPT];
	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		g1[0]->GetPoint(ipt, v2xhi[ipt], v2yhi[ipt]);
		g1[1]->GetPoint(ipt, v2xlow[ipt], v2ylow[ipt]);
		v2xEhi[ipt] = g1[0]->GetErrorX(ipt);
		v2xElow[ipt] = g1[1]->GetErrorX(ipt);
		v2yEhi[ipt] = g1[0]->GetErrorY(ipt);
		v2yElow[ipt] = g1[1]->GetErrorY(ipt);
		if(ipt == pt_narr-2)
		{
			v2sub_pl[ipt] = v2yhi[ipt] - v2ylow[ipt]*(JRatio+JRatioE)*Nass[1][ipt]/Nass[0][ipt];
			v2sub_mi[ipt] = v2yhi[ipt] - v2ylow[ipt]*(JRatio-JRatioE)*Nass[1][ipt]/Nass[0][ipt];
		}
		else
		{
			v2sub_pl[ipt] = v2yhi[ipt] - v2ylow[ipt]*(JRatio+3*JRatioE)*Nass[1][ipt]/Nass[0][ipt];
			v2sub_mi[ipt] = v2yhi[ipt] - v2ylow[ipt]*(JRatio-3*JRatioE)*Nass[1][ipt]/Nass[0][ipt];
		}
		v2subE[ipt] = TMath::Sqrt( TMath::Power(v2yEhi[ipt], 2) + TMath::Power(v2yElow[ipt]*JRatio*Nass[1][ipt]/Nass[0][ipt], 2) );
	}

	TGraphErrors* gv2sub_pl = new TGraphErrors(pt_narr-1, v2xhi, v2sub_pl, v2xEhi, v2subE);
	gv2sub_pl->SetName("gv2sub_pl");
	FormGraph(gv2sub_pl, 0, 0, 1.2);
	TGraphErrors* gv2sub_mi = new TGraphErrors(pt_narr-1, v2xhi, v2sub_mi, v2xEhi, v2subE);
	gv2sub_mi->SetName("gv2sub_mi");
	FormGraph(gv2sub_mi, 0, 0, 1.2);
	TH1D* htmp = new TH1D("htmp", ";p_{T} (GeV/c);V_{2}^{sub}(#varUpsilon-trk)", 10, 0, ptBinsArr[pt_narr-1]);
	FormTH1(htmp, 0);

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	c1->cd();
	htmp->SetMinimum(-0.006);
	//htmp->SetMaximum(0.2);
	htmp->SetMaximum(0.02);
	htmp->Draw();
	gv2sub_pl->Draw("samepe");
	gv2sub_mi->Draw("samepe");
	c1->SaveAs(Form("Plots/Sub/Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_Jvar.pdf", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	TFile* fout = new TFile(Form("File/Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_Jvar.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");
	fout->cd();
	gv2sub_pl->Write();
	gv2sub_mi->Write();
	fout->Close();
}
