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

void JetYieldRatio_intg(const Int_t multMinhi = 110, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 40, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString versionhi = "v19", const TString versionlow = "v20", const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Int_t isTnP = 0, const Bool_t SigSys = false, const Bool_t BkgSys = false, const TString MupT = "3p5", const Bool_t isfine = true)
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
	TString TnPs;
	if(isTnP == 0) TnPs = "w";
	else if(isTnP == 1) TnPs = "statup";
	else if(isTnP == 2) TnPs = "statdw";
	else if(isTnP == 3) TnPs = "systup";
	else if(isTnP == 4) TnPs = "systdw";
	else if(isTnP == 5) TnPs = "wo";
	else
	{
		cout << "There is no such TnP index" << endl;
		return;
	}
	TString PorB[2] = {"peak", "bkg"};
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
	Double_t JComp[2][2];
	Double_t JCompE[2][2];
	Double_t JYield[2];
	Double_t JYieldE[2];
	Double_t JRatio;
	Double_t JRatioE;

	for(Int_t imult = 0; imult < 2; imult++)
	{
		fjet[imult] = new TFile(Form("File/Sideband_Mult_%d-%d_pt_12-30_rap_%d-%d_Trkpt_%d-%d_%s_Acc%o_Eff%o_TnP%s_MupT%s_%s.root", multMins[imult], multMaxs[imult], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versions[imult].Data(), isAccRW, isEffRW, TnPs.Data(), MupT.Data(), Fine.Data()));

		for(Int_t ipb = 0; ipb < 2; ipb++)
		{
			TH1D* htmpshort = (TH1D*) fjet[imult]->Get(Form("hJYield_%s_short", PorB[ipb].Data()));
			JComp[imult][ipb] = htmpshort->GetBinContent(1);
			JCompE[imult][ipb] = htmpshort->GetBinError(1);
cout << versions[imult] << ": short-long: " << PorB[ipb] << ": Val: " << JComp[imult][ipb] << endl;
cout << versions[imult] << ": short-long: " << PorB[ipb] << ": Err: " << JCompE[imult][ipb] << endl;
		}

		TFile* ffit = new TFile(Form("../SkimmedFiles/Yield/Yield_Mult_%d-%d_pt_12-30_rap_%d-%d_Data_%s_Acc%o_Eff%o_TnP%s_SigSys%o_BkgSys%o_OS_MupT%s.root", multMins[imult], multMaxs[imult], (int)(10*rapMin), (int)(10*rapMax), versions[imult].Data(), isAccRW, isEffRW, TnPs.Data(), SigSys, BkgSys, MupT.Data()), "READ");
		TH1D* htmpfrac = (TH1D*) ffit->Get("hfrac");
		Double_t f;
		f = htmpfrac->GetBinContent(5)/( htmpfrac->GetBinContent(5)+htmpfrac->GetBinContent(6) );
		JYield[imult] = ( JComp[imult][0]-(1-f)*JComp[imult][1] )/f;
		JYieldE[imult] = TMath::Sqrt( TMath::Power(JCompE[imult][0]/f, 2) + TMath::Power((1-f)*JCompE[imult][1]/f, 2) );
cout << versions[imult] << ": fraction: " << f << endl;
cout << versions[imult] << ": signal: " << ": Val: " << JYield[imult] << endl;
cout << versions[imult] << ": signal: " << ": Err: " << JYieldE[imult] << endl;
	}

	JRatio = JYield[0]/JYield[1];
	JRatioE = JRatio*TMath::Sqrt( TMath::Power(JYieldE[0]/JYield[0], 2) + TMath::Power(JYieldE[1]/JYield[1], 2) );

	TGraphErrors* gJRatio = new TGraphErrors(1);
	gJRatio->SetPoint(0, 21, JRatio);
	gJRatio->SetPointError(0, 0, JRatioE);
	gJRatio->SetName("gJRatio");
	FormGraph(gJRatio, 0, 0, 1.2);
	TH1D* htmp = new TH1D("htmp", Form(";p_{T};J^{sig}_{jet}(%d<N^{offline}_{trk}<%d)/J^{sig}_{jet}(N^{offline}_{trk}<%d)", multMinhi, multMaxhi, multMaxlow), 10, 0, ptBinsArr[pt_narr-1]);
	FormTH1(htmp, 0);

	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	c1->cd();
	htmp->SetMinimum(0.0);
	htmp->SetMaximum(4.0);
	htmp->Draw();
	gJRatio->Draw("samepe");
	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->DrawLatex(0.4, 0.7, Form("J_{high}/J_{low} = %.2f #pm %.2f", JRatio, JRatioE));

	c1->SaveAs(Form("Plots/JRatio/JRatio_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_Acc%o_Eff%o_TnP%s_SigSys%o_BkgSys%o_MupT%s.pdf", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Fine.Data(), isAccRW, isEffRW, TnPs.Data(), SigSys, BkgSys, MupT.Data()));

	TFile* fout = new TFile(Form("File/JRatio_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_Acc%o_Eff%o_TnP%s_SigSys%o_BkgSys%o_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Fine.Data(), isAccRW, isEffRW, TnPs.Data(), SigSys, BkgSys, MupT.Data()), "RECREATE");
	fout->cd();
	gJRatio->Write();
	fout->Close();
}
