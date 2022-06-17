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

void LMsub_MC(const Int_t multMinhi = 110, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 40, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 3, const Int_t AwayN = 1, const Bool_t isfine = true, const TString versionhi = "v19", const TString versionlow = "v20", const TString Jversionhi = "v19", const TString Jversionlow = "v20", const TString MupT = "3p5")
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

	TFile* fv2_Reco[2];
	TFile* fv2_Gen[2][pt_narr];
	TFile* fass_reco[2][pt_narr];
	TFile* fass_gen[2][pt_narr];
	TFile* fjet[2][pt_narr];

	TGraphErrors* g1_Reco[2];
	TH1D* hass_reco[2][pt_narr];
	TH1D* hass_gen[2][pt_narr];
	Double_t Nass_reco[2][pt_narr];
	Double_t Nass_gen[2][pt_narr];

	Double_t v2x_reco[2][pt_narr];
	Double_t v2y_reco[2][pt_narr];
	Double_t v2xE_reco[2][pt_narr];
	Double_t v2yE_reco[2][pt_narr];

	Double_t v2y_gen[2][pt_narr];
	Double_t v2yE_gen[2][pt_narr];

	Double_t v2sub_reco[pt_narr];
	Double_t v2subE_reco[pt_narr];
	Double_t v2sub_gen[pt_narr];
	Double_t v2subE_gen[pt_narr];

	for(Int_t imult = 0; imult < 2; imult++)
	{
		fv2_Reco[imult] = new TFile(Form("../SignalV2/V2Dist/V2File/%s/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_pol2_%s_%s_MC_%s_MupT%s%s.root", versions[imult].Data(), multMins[imult], multMaxs[imult], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Away.Data(), Fine.Data(), versions[imult].Data(), MupT.Data(), Ffit.Data()), "READ");
		TGraphErrors* gtemp_reco = (TGraphErrors*) fv2_Reco[imult]->Get(Form("v2_1s_vs_pt"));
		g1_Reco[imult] = (TGraphErrors*) gtemp_reco->Clone(Form("g1_Reco_%s", HorL[imult].Data()));

		for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
		{
			g1_Reco[imult]->GetPoint(ipt, v2x_reco[imult][ipt], v2y_reco[imult][ipt]);
	
			v2xE_reco[imult][ipt] = g1_Reco[imult]->GetErrorX(ipt);
			v2yE_reco[imult][ipt] = g1_Reco[imult]->GetErrorY(ipt);

			fv2_Gen[imult][ipt] = new TFile(Form("../ExtractV2/ProjDist/DistFiles/%s/MupT%s/v2_dist_Gen_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_MupT%s%s.root", versions[imult].Data(), MupT.Data(), multMins[imult], multMaxs[imult], (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versions[imult].Data(), MupT.Data(), Ffit.Data()), "READ");
			TH1D* htemp_gen = (TH1D*) fv2_Gen[imult][ipt]->Get(Form("hRef_%s_%s", Away.Data(), Fine.Data()));
			v2y_gen[imult][ipt] = htemp_gen->GetBinContent(1);
			v2yE_gen[imult][ipt] = htemp_gen->GetBinError(1);

			fass_reco[imult][ipt] = new TFile(Form("Plots/Nass/Nass_dist_%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_MC_Reco.root", multMins[imult], multMaxs[imult], (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versions[imult].Data(), MupT.Data()), "READ");
			TH1D* htmpass_reco = (TH1D*) fass_reco[imult][ipt]->Get("h1");
			hass_reco[imult][ipt] = (TH1D*) htmpass_reco->Clone(Form("hass_reco_%s_%d", HorL[imult].Data(), ipt));
			Nass_reco[imult][ipt] = hass_reco[imult][ipt]->GetMean();

			fass_gen[imult][ipt] = new TFile(Form("Plots/Nass/Nass_dist_%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_MC_Gen.root", multMins[imult], multMaxs[imult], (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versions[imult].Data(), MupT.Data()), "READ");
			TH1D* htmpass_gen = (TH1D*) fass_gen[imult][ipt]->Get("h1");
			hass_gen[imult][ipt] = (TH1D*) htmpass_gen->Clone(Form("hass_gen_%s_%d", HorL[imult].Data(), ipt));
			Nass_gen[imult][ipt] = hass_gen[imult][ipt]->GetMean();
		}
	}

	TFile* fJRatio_RECO = new TFile(Form("File/JRatio_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Jversionhi.Data(), Jversionlow.Data(), Fine.Data(), MupT.Data()), "READ");
	TFile* fJRatio_GEN = new TFile(Form("File/JRatio_Gen_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Jversionhi.Data(), Jversionlow.Data(), Fine.Data(), MupT.Data()), "READ");
	TF1* fitin_reco = (TF1*) fJRatio_RECO->Get("fit1");
	TF1* fitin_gen = (TF1*) fJRatio_GEN->Get("fit1");
	Double_t JRatio_reco = fitin_reco->GetParameter(0);
	Double_t JRatio_gen = fitin_gen->GetParameter(0);
	//Double_t JRatio_gen = 1.3;
	Double_t JRatioE_reco = fitin_reco->GetParError(0);
	Double_t JRatioE_gen = fitin_gen->GetParError(0);

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		v2sub_reco[ipt] = v2y_reco[0][ipt] - v2y_reco[1][ipt]*JRatio_reco*Nass_reco[1][ipt]/Nass_reco[0][ipt];
		v2subE_reco[ipt] = TMath::Sqrt( TMath::Power(v2yE_reco[0][ipt], 2) + TMath::Power(v2yE_reco[1][ipt]*JRatio_reco*Nass_reco[1][ipt]/Nass_reco[0][ipt], 2) );

cout << "reco hi: " << v2y_reco[0][ipt] << ", low: " << v2y_reco[1][ipt] << ", Jratio: " << JRatio_reco << ", Nass rate: " << Nass_reco[1][ipt]/Nass_reco[0][ipt] << endl;
cout << "recoE hi: " << v2yE_reco[0][ipt] << ", low: " << v2yE_reco[1][ipt] << endl;
cout << "recoE sub: " << v2subE_reco[ipt] << endl;

		v2sub_gen[ipt] = v2y_gen[0][ipt] - v2y_gen[1][ipt]*JRatio_gen*Nass_gen[1][ipt]/Nass_gen[0][ipt];
		v2subE_gen[ipt] = TMath::Sqrt( TMath::Power(v2yE_gen[0][ipt], 2) + TMath::Power(v2yE_gen[1][ipt]*JRatio_gen*Nass_gen[1][ipt]/Nass_gen[0][ipt], 2) );

cout << "gen hi: " << v2y_gen[0][ipt] << ", low: " << v2y_gen[1][ipt] << ", Jratio: " << JRatio_gen << ", Nass rate: " << Nass_gen[1][ipt]/Nass_gen[0][ipt] << endl;
	}

	TGraphErrors* gv2sub_reco = new TGraphErrors(pt_narr-1, v2x_reco[0], v2sub_reco, v2xE_reco[0], v2subE_reco);
	gv2sub_reco->SetName("gv2sub_reco");
	FormGraph(gv2sub_reco, 0, 0, 1.2);
	TGraphErrors* gv2sub_gen = new TGraphErrors(pt_narr-1, v2x_reco[0], v2sub_gen, v2xE_reco[0], v2subE_gen);
	gv2sub_gen->SetName("gv2sub_gen");
	FormGraph(gv2sub_gen, 0, 0, 1.2);

	TH1D* htmp_reco = new TH1D("htmp_reco", ";p_{T} (GeV/c);V_{2}^{sub}(#varUpsilon-trk) (RECO)", 10, 0, ptBinsArr[pt_narr-1]);
	FormTH1(htmp_reco, 0);
	TH1D* htmp_gen = new TH1D("htmp_gen", ";p_{T} (GeV/c);V_{2}^{sub}(#varUpsilon-trk) (GEN)", 10, 0, ptBinsArr[pt_narr-1]);
	FormTH1(htmp_gen, 0);

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	c1->cd();
	htmp_reco->SetMinimum(-0.02);
	htmp_reco->SetMaximum(0.02);
	htmp_reco->Draw();
	gv2sub_reco->Draw("samepe");
	c1->SaveAs(Form("Plots/Sub/Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_pol2_MupT%s_MC_RECO.pdf", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
	c2->cd();
	htmp_gen->SetMinimum(-0.02);
	htmp_gen->SetMaximum(0.02);
	htmp_gen->Draw();
	gv2sub_gen->Draw("samepe");
	c2->SaveAs(Form("Plots/Sub/Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_pol2_MupT%s_MC_GEN.pdf", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	TFile* fout = new TFile(Form("File/Subv2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_pol2_MupT%s_MC.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");
	fout->cd();
	gv2sub_reco->Write();
	gv2sub_gen->Write();
	fout->Close();
}
