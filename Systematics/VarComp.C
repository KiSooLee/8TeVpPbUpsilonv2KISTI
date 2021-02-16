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

void VarComp(const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 50, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Bool_t isfine = true, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v41", const TString MupT = "4")
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
	TString pDIR = mainDIR + Form("/SystPlot/MupT%s", MupT.Data());
	TString fDIR = mainDIR + Form("/SystFile/MupT%s", MupT.Data());

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
	TH1D* hsum = new TH1D("hsum", ";p_{T} (GeV/c);syst.", pt_narr-1, ptBinsArr);
	FormTH1Marker(hsum, 0, 0, 1.4);
	hsum->SetMinimum(-0.01);
	hsum->SetMaximum(0.05);
//}}}

	const TString SysName[8] = {"Acc.", "Eff.", "TnP", "Sig.", "Bkg.", "v2Bkg.",
										"Par.", "Jratio"};
	const Int_t colorN[8] = {97, 69, 78, 609, 796, 875, 923, 28};

	TFile* fout = new TFile(Form("SystFile/MupT%s/v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_MupT%s_syst.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fsys[8];
	fsys[0] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc0_Eff1_TnP1_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Acceptance
	fsys[1] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff0_TnP1_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Efficiency 
	fsys[2] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP0_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//TnP
	fsys[3] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys1_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Signal function
	fsys[4] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys0_BkgSys1_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Background function
	fsys[5] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys0_BkgSys0_pol3_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//v2 background function
	fsys[6] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys0_BkgSys0_pol2_MupT%s_ParSum.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//parameter
	fsys[7] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnP1_SigSys0_BkgSys0_pol2_MupT%s_Jvar.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Jratio variation
//}}}

//calculate v2 value{{{
	TGraphErrors* gsys[9];
	for(Int_t isys = 0; isys < 6; isys++)
	{
		gsys[isys] = (TGraphErrors*) fsys[isys]->Get(Form("Graph"));
		gsys[isys]->SetName(Form("gv2_sys_%d", isys));
	}
	gsys[6] = (TGraphErrors*) fsys[6]->Get(Form("gsum"));
	gsys[6]->SetName("gv2_sys_6");
	gsys[7] = (TGraphErrors*) fsys[7]->Get(Form("gv2_pl"));
	gsys[7]->SetName("gv2_sys_7");
	gsys[8] = (TGraphErrors*) fsys[7]->Get(Form("gv2_mi"));
	gsys[8]->SetName("gv2_sys_8");

	TH1D* hsys[8];
	for(Int_t isys = 0; isys < 8; isys++)
	{
		hsys[isys] = new TH1D(Form("hsys_%d", isys), ";p_{T} (GeV/c);syst.", pt_narr-1, ptBinsArr);
		FormTH1(hsys[isys], 0);
		hsys[isys]->SetLineColor(colorN[isys]);
	}
	hsys[0]->SetMinimum(-0.01);
	hsys[0]->SetMaximum(0.05);
	Double_t v2xsys[8][4];
	Double_t v2ysys[8][4];
	Double_t v2syssum[4] = {0.};

	for(Int_t isys = 0; isys < 7; isys++)
	{
		for(Int_t ibin = 0; ibin < 4; ibin++)
		{
			gsys[isys]->GetPoint(ibin, v2xsys[isys][ibin], v2ysys[isys][ibin]);
			hsys[isys]->SetBinContent(ibin+1, fabs(v2ysys[isys][ibin]));
			v2syssum[ibin] += v2ysys[isys][ibin]*v2ysys[isys][ibin];
		}
	}
	for(Int_t ibin = 0; ibin < 4; ibin++)
	{
		gsys[7]->GetPoint(ibin, v2xsys[7][ibin], v2ysys[7][ibin]);
		gsys[8]->GetPoint(ibin, v2xsys[8][ibin], v2ysys[8][ibin]);
		hsys[7]->SetBinContent(ibin+1, TMath::Max(fabs(v2ysys[7][ibin]),fabs(v2ysys[8][ibin])));
cout << "pl: " << v2ysys[7][ibin] << ", mi: " << v2ysys[8][ibin] << endl;
		v2syssum[ibin] += TMath::Max(fabs(v2ysys[7][ibin]),fabs(v2ysys[8][ibin]))*TMath::Max(fabs(v2ysys[7][ibin]),fabs(v2ysys[8][ibin]));
		v2syssum[ibin] = TMath::Sqrt(v2syssum[ibin]);
		hsum->SetBinContent(ibin+1, v2syssum[ibin]);
	}

	c1->cd();
	TLegend* lg1 = new TLegend(0.6, 0.4, 0.9, 0.85);
	FormLegend(lg1, 0.04);
	for(Int_t isys = 0; isys < 8; isys++)
	{
		if(isys == 0) hsys[isys]->Draw("hist");
		else hsys[isys]->Draw("histsame");
		lg1->AddEntry(hsys[isys], Form("%s", SysName[isys].Data()), "l");
	}
	lg1->Draw();
	SetLine(1, 0, 0, 30, 0, 0, 3);
	c1->SaveAs(Form("SystPlot/MupT%s/Syst_v2_comp_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c2->cd();
	hsum->Draw("hist");
	SetLine(1, 0, 0, 30, 0, 0, 3);
	c2->SaveAs(Form("SystPlot/MupT%s/Syst_v2_sum_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	fout->cd();
	hsum->Write();
	fout->Close();
//}}}
}
