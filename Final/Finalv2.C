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
#include "Upsilon.h"
#include "Style_Upv2.h"
//}}}

void Finalv2(const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 50, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Bool_t isfine = true, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v41", const TString MupT = "4")
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

	void * dirp = gSystem->OpenDirectory(pDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(pDIR.Data(), kTRUE);
//}}}

//Define canvas for yield and vn dist{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	c1->cd();
	TPad* pad_pt = new TPad("pad_pt", "pad_pt", 0, 0, 0.80, 1);
	pad_pt->SetLeftMargin(0.16);
	pad_pt->SetRightMargin(0);
	pad_pt->Draw();
	TPad* pad_int = new TPad("pad_int", "pad_int", 0.80, 0, 1, 1);
	pad_int->SetLeftMargin(0);
	pad_int->Draw();
	TH1D* hist1 = new TH1D("hist1", "", 31, 0, 31);
	FormTH1Marker(hist1, 0, 0, 1.4);
	hist1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist1->GetYaxis()->SetTitle("v_{2}^{sub}");
	hist1->GetYaxis()->SetTitleOffset(1.4);
	hist1->SetMinimum(-0.08);
	hist1->SetMaximum(0.15);
	TH1D* hist1_int = new TH1D("hist1_int", "", 1, 0, 1);
	FormTH1Marker(hist1_int, 0, 0, 1.4);
	hist1_int->SetMinimum(-0.08);
	hist1_int->SetMaximum(0.15);
	hist1_int->GetXaxis()->SetBinLabel(1, "0-30");
	hist1_int->GetXaxis()->SetLabelSize(0.3);
	hist1_int->GetYaxis()->SetTickSize(0.12);
	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
	TH1D* hist2 = new TH1D("hist2", "", 30, 0, 30);
	FormTH1Marker(hist2, 0, 0, 1.4);
	hist2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist2->GetYaxis()->SetTitle("v_{2}^{sub}");
	hist2->GetYaxis()->SetTitleOffset(1.4);
	hist2->SetMinimum(-0.08);
	hist2->SetMaximum(0.15);
	TCanvas* c3 = new TCanvas("c3", "", 0, 0, 600, 600);
	TH1D* hist3 = new TH1D("hist3", "", 30, 0, 30);
	FormTH1Marker(hist3, 0, 0, 1.4);
	hist3->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist3->GetYaxis()->SetTitle("v_{2}^{sub}");
	hist3->GetYaxis()->SetTitleOffset(1.4);
	hist3->SetMinimum(-0.08);
	hist3->SetMaximum(0.15);
//}}}

//Get vn file{{{
	TFile* fv2 = new TFile(Form("Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	TFile* fv2_int = new TFile(Form("Final_v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_v88_by_v89_jet_%s_by_%s_Acc1_Eff1_TnPw_SigSys0_BkgSys0_pol2_MupT%s.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	TFile* fsys = new TFile(Form("v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_by_%s_jet_%s_by_%s_MupT%s_syst.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	TFile* fsys_int = new TFile(Form("v2_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_v88_by_v89_jet_%s_by_%s_MupT%s_syst.root", multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
	TFile* fJpsi = new TFile("HIN_18_010_JPsi_v2_mult185_250.root", "READ");
//}}}

//Draw v2 value{{{
	TGraphErrors* gv2 = (TGraphErrors*) fv2->Get(Form("gv2"));
	TH1D* hsys = (TH1D*) fsys->Get("hsum");
	TGraphErrors* gv2_int = (TGraphErrors*) fv2_int->Get(Form("gv2"));
	TH1D* hsys_int = (TH1D*) fsys_int->Get("hsum");
	TGraphErrors* gJpsi = (TGraphErrors*) fJpsi->Get("v2vspt_sub");

//Define variables{{{
	Double_t v2xval[4];
	Double_t v2yval[4];
	Double_t Exv2[4];
	Double_t Eyv2[4];
	Double_t v2sys[4];
	Double_t Exsys[4] = {1.5, 1.5, 2.0, 10.0};
	Double_t v2xint[1] = {0};
	Double_t v2yint[1] = {0};
	Double_t Exv2_int[1] = {0};
	Double_t Eyv2_int[1] = {0};
	Double_t Exsys_int[1] = {0.4};
	Double_t v2sys_int[1] = {0};
	Double_t v2xvalPbPbUp[4];
	Double_t v2yvalPbPbUp[4] = {0.004, -0.018, 0.058, 0.018};
	Double_t Exv2PbPbUp[4];
	Double_t Eyv2PbPbUp[4] = {0.019, 0.019, 0.023, 0.021};
	Double_t v2sysPbPbUp[4] = {0.012, 0.005, 0.004, 0.007};
/*
	for(Int_t i = 0; i < 4; i++)
	{
		v2sysPbPbUp[i] = TMath::Sqrt(Eyv2PbPbUp[i]*Eyv2PbPbUp[i]+v2sysPbPbUp[i]*v2sysPbPbUp[i]);
	}
*/
	Double_t ExsysPbPbUp[4] = {0.5, 0.5, 0.5, 0.5};
	Double_t v2xvalJpsi[6];
	Double_t v2yvalJpsi[6];
	Double_t Exv2Jpsi[6];
	Double_t Eyv2Jpsi[6];
	Double_t v2sysJpsi[6];
	Double_t ExsysJpsi[6] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
	string   thchar[3];
	Double_t thpt[4];
	Double_t thv2[4];
	Double_t thxE[4] = {0.0};
	Double_t thv2E[4];
//}}}

//get pPb Upsilon v2{{{
	for(Int_t ibin = 0; ibin < 4; ibin++)
	{
		gv2->GetPoint(ibin, v2xval[ibin], v2yval[ibin]);
		v2sys[ibin] = hsys->GetBinContent(ibin+1);
cout << "uncertainty bin " << ibin << ", syst.: " << v2sys[ibin] << endl;
		v2xvalPbPbUp[ibin] = v2xval[ibin];
		Exv2[ibin] = gv2->GetErrorX(ibin);
		Exv2PbPbUp[ibin] = gv2->GetErrorX(ibin);
		Eyv2[ibin] = gv2->GetErrorY(ibin);
cout << "uncertainty bin " << ibin << ", stat.: " << Eyv2[ibin] << endl;
		//v2sys[ibin] = TMath::Sqrt(v2sys[ibin]*v2sys[ibin]+Eyv2[ibin]*Eyv2[ibin]);
	}
	gv2_int->GetPoint(0, v2xint[0], v2yint[0]);
	v2sys_int[0] = hsys_int->GetBinContent(1);
	v2xint[0] = 0.5;
	Exv2_int[0] = gv2_int->GetErrorX(0);
	Eyv2_int[0] = gv2_int->GetErrorY(0);
	//v2sys_int[0] = TMath::Sqrt(v2sys_int[0]*v2sys_int[0]+Eyv2_int[0]*Eyv2_int[0]);
//}}}

//get J/psi v2{{{
	for(Int_t jbin = 0; jbin < gJpsi->GetN(); jbin++)
	{
		gJpsi->GetPoint(jbin, v2xvalJpsi[jbin], v2yvalJpsi[jbin]);
		Eyv2Jpsi[jbin] = gJpsi->GetErrorY(jbin);
		v2sysJpsi[jbin] = fabs(v2yvalJpsi[jbin])*0.13;
		//v2sysJpsi[jbin] = TMath::Sqrt(Eyv2Jpsi[jbin]*Eyv2Jpsi[jbin]+v2sysJpsi[jbin]*v2sysJpsi[jbin]);
	}
//}}}

//get theory{{{
	ifstream in1;
	in1.open("SHINCHON_pPb_Y1S_v2_HM25perc.txt");
	if(in1.is_open())
	{
		in1 >> thchar[0] >> thchar[1] >> thchar[2];
		in1 >> thpt[0] >> thv2[0] >> thv2E[0];
		in1 >> thpt[1] >> thv2[1] >> thv2E[1];
		in1 >> thpt[2] >> thv2[2] >> thv2E[2];
		in1 >> thpt[3] >> thv2[3] >> thv2E[3];
	}
	in1.close();
//}}}

//pPb Upsilon v2 graph{{{
	TGraphErrors* gv2val = new TGraphErrors(gv2->GetN(), v2xval, v2yval, Exv2, Eyv2);
	gv2val->SetName(Form("gv2val"));
	gv2val->SetMarkerStyle(20);
	gv2val->SetMarkerColor(213);
	TGraphErrors* gv2sys = new TGraphErrors(gv2->GetN(), v2xval, v2yval, Exsys, v2sys);
	gv2sys->SetName(Form("gv2sys"));
	//gv2sys->SetMarkerStyle(20);
	FormGraph(gv2sys, 64, 20, 0.14);
	//gv2sys->SetFillColor(64);
	gv2sys->SetFillColorAlpha(64, 0.7);
	gv2sys->SetLineWidth(1);
	gv2sys->SetFillStyle(2002);
	gv2sys->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	gv2sys->GetYaxis()->SetTitle("v_{2}");
	gv2sys->GetYaxis()->SetRangeUser(-0.08, 0.15);
	gv2sys->GetXaxis()->SetLimits(0, 30);
	gv2sys->SetLineColor(64);

	TGraphErrors* gv2val_int = new TGraphErrors(1, v2xint, v2yint, Exv2_int, Eyv2_int);
	gv2val_int->SetName(Form("gv2val_int"));
	gv2val_int->SetMarkerStyle(20);
	gv2val_int->SetMarkerColor(213);
	TGraphErrors* gv2sys_int = new TGraphErrors(1, v2xint, v2yint, Exsys_int, v2sys_int);
	gv2sys_int->SetName(Form("gv2sys_int"));
	FormGraph(gv2sys_int, 64, 20, 0.14);
	gv2sys_int->SetFillColorAlpha(64, 0.7);
	gv2sys_int->SetLineWidth(1);
	gv2sys_int->SetFillStyle(2002);
	gv2sys_int->GetYaxis()->SetRangeUser(-0.08, 0.15);
	gv2sys_int->GetXaxis()->SetLimits(0, 1);
	gv2sys_int->SetLineColor(64);
//}}}

//PbPb Upsilon v2 graph{{{
	TGraphErrors* gv2valPbPbUp = new TGraphErrors(gv2->GetN(), v2xvalPbPbUp, v2yvalPbPbUp, Exv2PbPbUp, Eyv2PbPbUp);
	gv2valPbPbUp->SetName(Form("gv2valPbPbUp"));
	gv2valPbPbUp->SetMarkerStyle(21);
	gv2valPbPbUp->SetMarkerColor(221);
	TGraphErrors* gv2sysPbPbUp = new TGraphErrors(gv2->GetN(), v2xvalPbPbUp, v2yvalPbPbUp, ExsysPbPbUp, v2sysPbPbUp);
	gv2sysPbPbUp->SetName(Form("gv2sysPbPbUp"));
	FormGraph(gv2sysPbPbUp, 610, 20, 0.14);
	gv2sysPbPbUp->SetFillStyle(2002);
	gv2sysPbPbUp->SetFillColorAlpha(610, 0.7);
	gv2sysPbPbUp->SetLineColor(610);
	gv2sysPbPbUp->SetLineWidth(1);
//}}}

//pPb J/psi v2 graph{{{
	gJpsi->SetName(Form("gv2valJpsi"));
	gJpsi->SetMarkerStyle(21);
	gJpsi->SetMarkerColor(420);
	gJpsi->SetLineWidth(1);
	TGraphErrors* gv2sysJpsi = new TGraphErrors(gJpsi->GetN(), v2xvalJpsi, v2yvalJpsi, ExsysJpsi, v2sysJpsi);
	gv2sysJpsi->SetName(Form("gv2sysJpsi"));
	FormGraph(gv2sysJpsi, 416, 20, 0.14);
	gv2sysJpsi->SetFillColorAlpha(416, 0.7);
	gv2sysJpsi->SetFillStyle(2002);
	gv2sysJpsi->SetLineWidth(1);
	gv2sysJpsi->SetLineColor(416);
//}}}

//theory v2 graph{{{
	TGraphErrors* gv2theory = new TGraphErrors(4, thpt, thv2, thxE, thv2E);
	gv2theory->SetName("gv2theory");
	gv2theory->SetFillColor(92);
	gv2theory->SetLineColor(93);
//}}}

//Draw pPb Upsilon v2{{{
	pad_pt->cd();
	hist1->Draw();
	gv2sys->Draw("5");
	gv2val->Draw("same pe");
	SetLine(1, 0, 0, 31, 0, 0, 3);
	//CMSP(0.16, 0.92);
	CMS(0.16, 0.92);
	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 42, 0.05);
	lt1->DrawLatex(0.25,0.83, Form("#Upsilon (1S), 0 < |y_{lab}| < 2.4"));
	//lt1->DrawLatex(0.25,0.76, Form("%d #leq N^{offline}_{trk} < %d (N^{offline}_{trk} < %d sub.)", multMinhi, multMaxhi, multMaxlow));
	lt1->DrawLatex(0.25,0.76, Form("%d #leq N^{offline}_{trk} < %d", multMinhi, multMaxhi));
	//gv2theory->Draw("same3");
	//TLegend* leg0 = new TLegend(0.25, 0.62, 0.80, 0.69);
	//FormLegend(leg0, 0.045);
	//leg0->SetMargin(0.15);
	//leg0->AddEntry(gv2theory, "PLB. 801 (2020) 135147", "l");
	//leg0->AddEntry(gv2theory, "SHINCHON_MC", "l");
	//leg0->Draw();
	pad_int->cd();
	hist1_int->Draw();
	gv2sys_int->Draw("5");
	gv2val_int->Draw("same pe");
	c1->cd();
	lumiText(0.59, 0.92);
	//c1->Update();
	c1->Modified();
	c1->SaveAs(Form("V2Plot/MupT%s/Result_v2_dist_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));
//}}}

//Comp PbPb Upsilon v2{{{
	c2->cd();
	c2->SetLeftMargin(0.16);
	c2->SetRightMargin(0.03);
	hist2->Draw();
	gv2sys->Draw("5");
	gv2val->Draw("same pe");
	gv2sysPbPbUp->Draw("5 same");
	gv2valPbPbUp->Draw("same pe");
	SetLine(1, 0, 0, 30, 0, 0, 3);
	//CMSP(0.16, 0.92);
	CMS(0.16, 0.92);
	lumiText(0.59, 0.92);
	TLegend* leg1 = new TLegend(0.2, 0.72, 0.95, 0.87);
	FormLegend(leg1, 0.04);
	leg1->SetMargin(0.05);
	leg1->AddEntry(gv2val, Form("#Upsilon (1S), pPb 8.16 TeV (%d #leq N^{offline}_{trk} < %d)", multMinhi, multMaxhi), "pe");
	//leg1->AddEntry(gv2val, Form("#Upsilon (1S) pPb 8.16 TeV (%d #leq N^{offline}_{trk} < %d (N^{offline}_{trk} < %d sub.))", multMinhi, multMaxhi, multMaxlow), "pe");
	leg1->AddEntry(gv2valPbPbUp, "#Upsilon (1S), PbPb 5.02 TeV (Cent. 10-90 %)", "pe");
	leg1->Draw();
	c2->SaveAs(Form("V2Plot/MupT%s/Result_v2_comp_PbPb_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));
//}}}

//Comp pPb J/psi v2{{{
	c3->cd();
	c3->SetLeftMargin(0.16);
	c3->SetRightMargin(0.03);
	hist3->Draw();
	gv2sys->Draw("5");
	gv2val->Draw("same pe");
	gv2sysJpsi->Draw("5");
	gJpsi->Draw("same pe");
	SetLine(1, 0, 0, 30, 0, 0, 3);
	//CMSP(0.16, 0.92);
	CMS(0.16, 0.92);
	lumiText(0.59, 0.92);
	TLegend* leg2 = new TLegend(0.50, 0.60, 0.90, 0.87);
	FormLegend(leg2, 0.035);
	leg2->SetMargin(0.05);
	leg2->AddEntry(gv2val, Form("#Upsilon (1S), 0 < |y_{lab}| < 2.4"), "pe");
	//leg2->AddEntry(gv2sys, Form("70 #leq N^{offline}_{trk} < 300 (N^{offline}_{trk} < %d sub.)", multMaxlow), "");
	leg2->AddEntry(gv2sys, Form("70 #leq N^{offline}_{trk} < 300"), "");
	leg2->AddEntry(gJpsi, "Prompt J/#psi, 1.4 < |y_{lab}| < 2.4", "pe");
	//leg2->AddEntry(gv2sysJpsi, "180 #leq N^{offline}_{trk} < 250 (N^{offline}_{trk} < 35 sub.)", "");
	leg2->AddEntry(gv2sysJpsi, "180 #leq N^{offline}_{trk} < 250", "");
	leg2->Draw();
	c3->SaveAs(Form("V2Plot/MupT%s/Result_v2_comp_Jpsi_Reco_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_by_%s_jet_%s_by_%s_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));
//}}}

//}}}
}
