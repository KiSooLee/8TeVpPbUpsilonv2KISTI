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
	TH1D* hsum = new TH1D("hsum", ";p_{T} (GeV/c);syst.", pt_narr-1, ptBinsArr);
	FormTH1Marker(hsum, 0, 0, 1.4);
	hsum->SetMinimum(-0.01);
	hsum->SetMaximum(0.05);
//}}}

	const TString SysName[9] = {"Acc.", "Eff.", "Sig.", "Bkg.", "v2Bkg.", "Par.",
										"TnP", "Jratio", "MC"};
	const Int_t colorN[9] = {97, 69, 78, 609, 796, 875, 923, 28, 396};

	TFile* fout = new TFile(Form("SystFile/MupT%s/v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_MupT%s_syst.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fsys[9];
	fsys[0] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc0_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Acceptance
	fsys[1] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff0_TnPw_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Efficiency 
	fsys[2] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys1_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Signal function
	fsys[3] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys1_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Background function
	fsys[4] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol3_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//v2 background function
	fsys[5] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_ParSum.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//parameter
	fsys[6] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPs_SigSys0_BkgSys0_pol2_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//TnP
	fsys[7] = new TFile(Form("SystFile/MupT%s/v2_diff_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s_Jvar.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//Jratio variation
	fsys[8] = new TFile(Form("SystFile/MupT%s/v2_diff_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_v90_by_v91_jet_%s_by_%s_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//MC Closure
	//fsys[8] = new TFile(Form("SystFile/MupT%s/v2_diff_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_v92_by_v93_jet_%s_by_%s_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");//MC Closure integrated
//}}}

//calculate v2 value{{{
	TGraphErrors* gsys[13];
	for(Int_t isys = 0; isys < 5; isys++)
	{
		gsys[isys] = (TGraphErrors*) fsys[isys]->Get(Form("Graph"));
		gsys[isys]->SetName(Form("gv2_sys_%d", isys));
	}
	gsys[5] = (TGraphErrors*) fsys[5]->Get(Form("gsum"));
	gsys[5]->SetName("gv2_sys_5");
	gsys[6] = (TGraphErrors*) fsys[6]->Get(Form("gv2_stat_up"));
	gsys[6]->SetName("gv2_sys_6");
	gsys[7] = (TGraphErrors*) fsys[6]->Get(Form("gv2_stat_dw"));
	gsys[7]->SetName("gv2_sys_7");
	gsys[8] = (TGraphErrors*) fsys[6]->Get(Form("gv2_syst_up"));
	gsys[8]->SetName("gv2_sys_8");
	gsys[9] = (TGraphErrors*) fsys[6]->Get(Form("gv2_syst_dw"));
	gsys[9]->SetName("gv2_sys_9");
	//gsys[10] = (TGraphErrors*) fsys[7]->Get(Form("gv2_diff_pl"));
	gsys[10] = (TGraphErrors*) fsys[7]->Get(Form("gv2_pl"));
	gsys[10]->SetName("gv2_sys_10");
	//gsys[11] = (TGraphErrors*) fsys[7]->Get(Form("gv2_diff_mi"));
	gsys[11] = (TGraphErrors*) fsys[7]->Get(Form("gv2_mi"));
	gsys[11]->SetName("gv2_sys_11");
	gsys[12] = (TGraphErrors*) fsys[8]->Get(Form("gv2_diff"));
	gsys[12]->SetName("gv2_sys_12");

	TH1D* hsys[9];
	//TH1D* hsys[8];
	for(Int_t isys = 0; isys < 9; isys++)
	//for(Int_t isys = 0; isys < 8; isys++)
	{
		hsys[isys] = new TH1D(Form("hsys_%d", isys), ";p_{T} (GeV/c);syst.", pt_narr-1, ptBinsArr);
		FormTH1(hsys[isys], 0);
		hsys[isys]->SetLineColor(colorN[isys]);
	}
	hsys[0]->SetMinimum(-0.01);
	hsys[0]->SetMaximum(0.05);
	Double_t v2xsys[13][4];
	Double_t v2ysys[13][4];
	Double_t v2syssum[4] = {0.};

	for(Int_t isys = 0; isys < 6; isys++)
	{
		for(Int_t ibin = 0; ibin < 4; ibin++)
		{
			gsys[isys]->GetPoint(ibin, v2xsys[isys][ibin], v2ysys[isys][ibin]);
			hsys[isys]->SetBinContent(ibin+1, fabs(v2ysys[isys][ibin]));
			v2syssum[ibin] += v2ysys[isys][ibin]*v2ysys[isys][ibin];
cout << SysName[isys].Data() << ", pt bin " << ibin << ": " << fabs(v2ysys[isys][ibin]) << endl;
		}
	}

	for(Int_t ibin = 0; ibin < 4; ibin++)
	{
		//TnP statistic variation
		gsys[6]->GetPoint(ibin, v2xsys[6][ibin], v2ysys[6][ibin]);
		gsys[7]->GetPoint(ibin, v2xsys[7][ibin], v2ysys[7][ibin]);
		Double_t stat_max = TMath::Max(fabs(v2ysys[6][ibin]),fabs(v2ysys[7][ibin]));
cout << "TnP stat up: " << v2ysys[6][ibin] << ", stat dw: " << v2ysys[7][ibin] << endl;

		//TnP systematic variation
		gsys[8]->GetPoint(ibin, v2xsys[8][ibin], v2ysys[8][ibin]);
		gsys[9]->GetPoint(ibin, v2xsys[9][ibin], v2ysys[9][ibin]);
		Double_t syst_max = TMath::Max(fabs(v2ysys[8][ibin]),fabs(v2ysys[9][ibin]));
cout << "TnP syst up: " << v2ysys[8][ibin] << ", syst dw: " << v2ysys[9][ibin] << endl;

		hsys[6]->SetBinContent(ibin+1, TMath::Sqrt(stat_max*stat_max+syst_max*syst_max));
		v2syssum[ibin] += stat_max*stat_max+syst_max*syst_max;
cout << "TnP total, pt bin " << ibin << ": " << TMath::Sqrt(stat_max*stat_max+syst_max*syst_max) << endl;

		//Jratio variation
		gsys[10]->GetPoint(ibin, v2xsys[10][ibin], v2ysys[10][ibin]);
		gsys[11]->GetPoint(ibin, v2xsys[11][ibin], v2ysys[11][ibin]);
		hsys[7]->SetBinContent(ibin+1, TMath::Max(fabs(v2ysys[10][ibin]),fabs(v2ysys[11][ibin])));
cout << "pl: " << v2ysys[10][ibin] << ", mi: " << v2ysys[11][ibin] << endl;
cout << SysName[7].Data() << ", pt bin " << ibin << ": " << TMath::Max(fabs(v2ysys[10][ibin]),fabs(v2ysys[11][ibin])) << endl;
		v2syssum[ibin] += TMath::Max(fabs(v2ysys[10][ibin]),fabs(v2ysys[11][ibin]))*TMath::Max(fabs(v2ysys[10][ibin]),fabs(v2ysys[11][ibin]));

		//MC Closure test
		gsys[12]->GetPoint(ibin, v2xsys[12][ibin], v2ysys[12][ibin]);
		hsys[8]->SetBinContent(ibin+1, fabs(v2ysys[12][ibin]));
		v2syssum[ibin] += v2ysys[12][ibin]*v2ysys[12][ibin];
cout << "MC Closure, pt bin " << ibin << ": " << v2ysys[12][ibin] << endl;

		v2syssum[ibin] = TMath::Sqrt(v2syssum[ibin]);
		hsum->SetBinContent(ibin+1, v2syssum[ibin]);
cout << "Total, pt bin " << ibin << ": " << v2syssum[ibin] << endl;
	}
//}}}

	c1->cd();
	TLegend* leg1 = new TLegend(0.6, 0.4, 0.9, 0.85);
	FormLegend(leg1, 0.04);
	hsum->SetLineWidth(3);
	hsum->Draw("hist");
	leg1->AddEntry(hsum, "total", "l");
	for(Int_t isys = 0; isys < 9; isys++)
	//for(Int_t isys = 0; isys < 8; isys++)
	{
		hsys[isys]->Draw("histsame");
		leg1->AddEntry(hsys[isys], Form("%s", SysName[isys].Data()), "l");
	}
	leg1->Draw();
	SetLine(1, 0, 0, 30, 0, 0, 3);
	c1->SaveAs(Form("SystPlot/MupT%s/Syst_v2_comp_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	fout->cd();
	hsum->Write();
	fout->Close();
}
