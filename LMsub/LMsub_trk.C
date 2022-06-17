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

void LMsub_trk(const bool isMC = false, const bool isGen = false, const Int_t multMinhi = 110, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 40, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 3, const Int_t AwayN = 1, const Bool_t isfine = true, const TString versionhi = "v19", const TString versionlow = "v20", const TString Jversionhi = "v19", const TString Jversionlow = "v20", const TString MupT = "3p5")
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
	TString Away;
	if(AwayN == 1) Away = "1";
	else if(AwayN == 2) Away = "1p5";
	else if(AwayN == 3) Away = "2";
	else
	{
		cout << "out of delta eta cut range list" << endl;
		return;
	}
	TString MorD;
	if (isMC == true) MorD = "MC";
	else MorD = "Data";
	TString RorG;
	if (isGen == true) RorG = "Gen";
	else RorG = "Reco";
	TString MorDsf;
	if (isMC == true) MorDsf = "_MC";
	else MorDsf = "";
	TString RorGsf;
	if (isMC == true)
	{
		if (isGen == true) RorGsf = "_Gen";
		else RorGsf = "_Reco";
	}
	else RorGsf = "";

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
	TFile* fv2[2][NPT];
	TFile* fass[2][NPT];
	TFile* fjet[2][NPT];

	TH1D* h1[2][NPT];
	TH1D* hass[2][NPT];
	Double_t v2x[2][NPT];
	Double_t v2y[2][NPT];
	Double_t v2xE[2][NPT] = {0.};
	Double_t v2yE[2][NPT];
	Double_t v2sub[NPT];
	Double_t v2subE[NPT];
	Double_t Nass[2][NPT];
	Double_t JComp[2][NPT];
	Double_t JYield[2][NPT];
	for(Int_t imult = 0; imult < 2; imult++)
	{
		for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
		{
			fv2[imult][ipt] = new TFile(Form("../ExtractV2/ProjDist/DistFiles/%s/MupT%s/trk_v2_dist_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s%s.root", versions[imult].Data(), MupT.Data(), RorG.Data(), multMins[imult], multMaxs[imult], (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), versions[imult].Data(), MupT.Data(), Ffit.Data()), "READ");
cout << "mult: " << imult << ", f: " << fv2[imult][ipt] << endl;
			TH1D* htemp;
			if(imult == 1) htemp = (TH1D*) fv2[imult][ipt]->Get(Form("hRef_%s_%s", Away.Data(), Fine.Data()));
			//if(imult == 0) htemp = (TH1D*) fv2[imult][ipt]->Get(Form("hRef_%s", Fine.Data()));
			else htemp = (TH1D*) fv2[imult][ipt]->Get(Form("hRef_%s", Fine.Data()));
cout << "mult: " << imult << ", h: " << htemp << endl;
			h1[imult][ipt] = (TH1D*) htemp->Clone(Form("h1_%s_%d", HorL[imult].Data(), ipt));
cout << "mult: " << imult << ", hclone: " << h1[imult][ipt] << endl;
			v2y[imult][ipt] = h1[imult][ipt]->GetBinContent(1);
			v2yE[imult][ipt] = h1[imult][ipt]->GetBinError(1);

			//fass[imult][ipt] = new TFile(Form("Plots/Nass/Nass_dist_%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_%s_%s.root", multMins[imult], multMaxs[imult], (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versions[imult].Data(), MupT.Data(), MorD.Data(), RorG.Data()), "READ");
			fass[imult][ipt] = new TFile(Form("Plots/Nass/Nass_dist_%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_%s.root", multMins[imult], multMaxs[imult], (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versions[imult].Data(), MupT.Data(), MorD.Data()), "READ");
			TH1D* htmpass = (TH1D*) fass[imult][ipt]->Get("h1");
			hass[imult][ipt] = (TH1D*) htmpass->Clone(Form("hass_%s_%d", HorL[imult].Data(), ipt));
			Nass[imult][ipt] = hass[imult][ipt]->GetMean();
		}
	}

	TFile* fJRatio = new TFile(Form("File/trk_JRatio_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Jversionhi.Data(), Jversionlow.Data(), Fine.Data(), MupT.Data()), "READ");
	TF1* fitin = (TF1*) fJRatio->Get("fit1");
	Double_t JRatio = fitin->GetParameter(0);
	Double_t JRatioE = fitin->GetParError(0);
	//TGraphErrors* fitin = (TGraphErrors*) fJRatio->Get("gJRatio");
	//Double_t JRatio;
	//Double_t JRatioE;
	//Double_t Jx1;
	//Double_t Jx2;
	//fitin->GetPoint(0, Jx1, JRatio);
	//JRatioE = fitin->GetErrorY(0);

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		v2sub[ipt] = v2y[0][ipt] - v2y[1][ipt]*JRatio*Nass[1][ipt]/Nass[0][ipt];
		v2subE[ipt] = TMath::Sqrt( TMath::Power(v2yE[0][ipt], 2) + TMath::Power(v2yE[1][ipt]*JRatio*Nass[1][ipt]/Nass[0][ipt], 2) );
		v2x[0][ipt] = ptBinsArr[ipt] + (ptBinsArr[ipt+1]-ptBinsArr[ipt])/2;
	}

	TGraphErrors* gv2sub = new TGraphErrors(pt_narr-1, v2x[0], v2sub, v2xE[0], v2subE);
	gv2sub->SetName("gv2sub");
	FormGraph(gv2sub, 0, 0, 1.2);
	TH1D* htmp = new TH1D("htmp", ";p_{T} (GeV/c);V_{2}^{sub}(trk-trk)", 10, 0, ptBinsArr[pt_narr-1]);
	FormTH1(htmp, 0);

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	c1->cd();
	htmp->SetMinimum(-0.005);
	//htmp->SetMinimum(-0.02);
	htmp->SetMaximum(0.2);
	//htmp->SetMaximum(0.05);
	htmp->Draw();
	gv2sub->Draw("samepe");
	c1->SaveAs(Form("Plots/Sub/trk_Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_MupT%s%s%s.pdf", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data(), MorDsf.Data(), RorGsf.Data()));

	TFile* fout = new TFile(Form("File/trk_Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_MupT%s%s%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data(), MorDsf.Data(), RorGsf.Data()), "RECREATE");
	fout->cd();
	gv2sub->Write();
	fout->Close();
}
