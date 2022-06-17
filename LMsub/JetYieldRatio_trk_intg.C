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

void JetYieldRatio_trk_intg(const Int_t multMinhi = 110, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 40, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString versionhi = "v19", const TString versionlow = "v20", const TString MupT = "3p5", const Bool_t isfine = true)
{
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fileDIR = mainDIR + Form("/File");
	TString plotDIR = mainDIR + Form("/Plots/JRatio");

	void * dirf = gSystem->OpenDirectory(fileDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);

	void * dirp = gSystem->OpenDirectory(plotDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(plotDIR.Data(), kTRUE);
//}}}

//Define names{{{
	TString BandName[2] = {"short", "long"};
	TString Fine;
	if(isfine == true) Fine = "fine";
	else Fine = "coarse";

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

	TFile* fjet[2];
	Double_t JComp[2];
	Double_t JCompE[2];
	Double_t JYield[2];
	Double_t JYieldE[2];
	Double_t JRatio;
	Double_t JRatioE;

	for(Int_t imult = 0; imult < 2; imult++)
	{
		fjet[imult] = new TFile(Form("File/trk_Sideband_Mult_%d-%d_pt_12-30_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_%s.root", multMins[imult], multMaxs[imult], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versions[imult].Data(), MupT.Data(), Fine.Data()));

		TH1D* htmpshort = (TH1D*) fjet[imult]->Get(Form("hJYield_short"));
		TH1D* htmplong = (TH1D*) fjet[imult]->Get(Form("hJYield_long"));
		JComp[imult] = htmpshort->GetBinContent(1);
		JCompE[imult] = htmpshort->GetBinError(1);
cout << versions[imult] << ": short-long: " << ": Val: " << JComp[imult] << endl;
cout << versions[imult] << ": short-long: " << ": Err: " << JCompE[imult] << endl;
	}

	JRatio = JComp[0]/JComp[1];
	JRatioE = JRatio*TMath::Sqrt( TMath::Power(JCompE[0]/JComp[0], 2) + TMath::Power(JCompE[1]/JComp[1], 2) );

	TGraphErrors* gJRatio = new TGraphErrors(1);
	gJRatio->SetPoint(0, 21, JRatio);
	gJRatio->SetPointError(0, 0, JRatioE);
	gJRatio->SetName("gJRatio");
	FormGraph(gJRatio, 0, 0, 1.2);
	TH1D* htmp = new TH1D("htmp", Form(";p_{T};J_{jet}(%d<N^{offline}_{trk}<%d)/J_{jet}(N^{offline}_{trk}<%d)", multMinhi, multMaxhi, multMaxlow), 10, 0, ptBinsArr[pt_narr-1]);
	FormTH1(htmp, 0);

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	c1->cd();
	htmp->SetMinimum(0.0);
	htmp->SetMaximum(2.0);
	htmp->Draw();
	gJRatio->Draw("samepe");
	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->DrawLatex(0.4, 0.7, Form("J_{high}/J_{low} = %.2f #pm %.2f", JRatio, JRatioE));
	c1->SaveAs(Form("Plots/JRatio/trk_JRatio_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_MupT%s.pdf", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Fine.Data(), MupT.Data()));

	TFile* fout = new TFile(Form("File/trk_JRatio_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Fine.Data(), MupT.Data()), "RECREATE");
	fout->cd();
	gJRatio->Write();
	fout->Close();
}
