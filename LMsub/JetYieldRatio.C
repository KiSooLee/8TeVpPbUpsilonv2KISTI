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

void JetYieldRatio(const Int_t multMinhi = 110, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 40, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString versionhi = "v19", const TString versionlow = "v20", const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Int_t isTnP = 0, const Bool_t SigSys = false, const Bool_t BkgSys = false, const TString MupT = "3p5", const Bool_t isfine = true)
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

	const Int_t NPT = 3;

	TFile* fjet[2][NPT];
	Double_t JComp[2][NPT][2];
	Double_t JCompE[2][NPT][2];
	Double_t JYield[2][NPT];
	Double_t JYieldE[2][NPT];
	Double_t JRatio[NPT];
	Double_t JRatioE[NPT];
	Double_t pt[NPT];
	//const Int_t ptbins[NPT+1] = {11, 15, 20, 30};
	const Int_t ptbins[NPT+1] = {12, 15, 20, 30};
	//const Int_t ptbins[NPT+1] = {11, 13, 17, 30};

	for(Int_t imult = 0; imult < 2; imult++)
	{
		for(Int_t ipt = 0; ipt < NPT; ipt++)
		{
			fjet[imult][ipt] = new TFile(Form("File/Sideband_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_Acc%o_Eff%o_TnP%s_MupT%s_%s.root", multMins[imult], multMaxs[imult], ptbins[ipt], ptbins[ipt+1], (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versions[imult].Data(), isAccRW, isEffRW, TnPs.Data(), MupT.Data(), Fine.Data()));

			for(Int_t ipb = 0; ipb < 2; ipb++)
			{
				TH1D* htmpshort = (TH1D*) fjet[imult][ipt]->Get(Form("hJYield_%s_short", PorB[ipb].Data()));
				//TH1D* htmplong = (TH1D*) fjet[imult][ipt]->Get(Form("hJYield_%s_long", PorB[ipb].Data()));
				//if(htmplong->GetBinContent(1) > 0) htmpshort->Add(htmplong, -1);
				JComp[imult][ipt][ipb] = htmpshort->GetBinContent(1);
				JCompE[imult][ipt][ipb] = htmpshort->GetBinError(1);
cout << versions[imult] << ": short-long: " << PorB[ipb] << ": Val: " << JComp[imult][ipt][ipb] << endl;
cout << versions[imult] << ": short-long: " << PorB[ipb] << ": Err: " << JCompE[imult][ipt][ipb] << endl;
			}

			TFile* ffit = new TFile(Form("../SkimmedFiles/Yield/Yield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Data_%s_Acc%o_Eff%o_TnP%s_SigSys%o_BkgSys%o_OS_MupT%s.root", multMins[imult], multMaxs[imult], ptbins[ipt], ptbins[ipt+1], (int)(10*rapMin), (int)(10*rapMax), versions[imult].Data(), isAccRW, isEffRW, TnPs.Data(), SigSys, BkgSys, MupT.Data()), "READ");
			TH1D* htmpfrac = (TH1D*) ffit->Get("hfrac");
			Double_t f;
			//if(!fracRange) f = htmpfrac->GetBinContent(1)/( htmpfrac->GetBinContent(1)+htmpfrac->GetBinContent(2) );
			//else
			//{
			//	//for fine peak range
			//	//f = htmpfrac->GetBinContent(3)/( htmpfrac->GetBinContent(3)+htmpfrac->GetBinContent(4) );
			//	//for wide peak range
			//	f = htmpfrac->GetBinContent(5)/( htmpfrac->GetBinContent(5)+htmpfrac->GetBinContent(6) );
			//}
			f = htmpfrac->GetBinContent(5)/( htmpfrac->GetBinContent(5)+htmpfrac->GetBinContent(6) );
			JYield[imult][ipt] = ( JComp[imult][ipt][0]-(1-f)*JComp[imult][ipt][1] )/f;
			JYieldE[imult][ipt] = TMath::Sqrt( TMath::Power(JCompE[imult][ipt][0]/f, 2) + TMath::Power((1-f)*JCompE[imult][ipt][1]/f, 2) );
cout << versions[imult] << ": fraction: " << f << endl;
cout << versions[imult] << ": signal: " << ": Val: " << JYield[imult][ipt] << endl;
cout << versions[imult] << ": signal: " << ": Err: " << JYieldE[imult][ipt] << endl;
		}
	}

	for(Int_t ipt = 0; ipt < NPT; ipt++)
	{
		JRatio[ipt] = JYield[0][ipt]/JYield[1][ipt];
		JRatioE[ipt] = JRatio[ipt]*TMath::Sqrt( TMath::Power(JYieldE[0][ipt]/JYield[0][ipt], 2) + TMath::Power(JYieldE[1][ipt]/JYield[1][ipt], 2) );
		pt[ipt] = ptbins[ipt] + (ptbins[ipt+1]-ptbins[ipt])/2;
	}

	TGraphErrors* gJRatio = new TGraphErrors(NPT, pt, JRatio, 0, JRatioE);
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
	TF1* fit1 = new TF1("fit1", "[0]", 0, ptbins[NPT]);
	fit1->SetLineColor(2);
	fit1->SetLineWidth(2);
	gJRatio->Fit(fit1, "W");
	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->DrawLatex(0.4, 0.7, Form("J_{high}/J_{low} = %.2f #pm %.2f", fit1->GetParameter(0), fit1->GetParError(0)));

	c1->SaveAs(Form("Plots/JRatio/JRatio_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_Acc%o_Eff%o_TnP%s_SigSys%o_BkgSys%o_MupT%s.pdf", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Fine.Data(), isAccRW, isEffRW, TnPs.Data(), SigSys, BkgSys, MupT.Data()));

	TFile* fout = new TFile(Form("File/JRatio_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_%s_Acc%o_Eff%o_TnP%s_SigSys%o_BkgSys%o_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Fine.Data(), isAccRW, isEffRW, TnPs.Data(), SigSys, BkgSys, MupT.Data()), "RECREATE");
	fout->cd();
	gJRatio->Write();
	fit1->Write();
	fout->Close();
}
