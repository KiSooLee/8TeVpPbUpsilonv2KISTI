//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TH1.h>
#include <TF1.h>
#include <iostream>
#include <TString.h>
#include <TLegend.h>
#include <TMath.h>
#include "../../Headers/Upsilon.h"
#include "../../Headers/Style_Upv2.h"
//}}}

void ReweightFunction(const Int_t multMin = 0, const Int_t multMax = 300, const TString version = "v1", const TString MupT = "4")
{
	SetStyle();

//define muon pt value{{{
	Double_t MupTCut;
	if(MupT == "0") MupTCut = 0;
	else if(MupT == "0p5") MupTCut = 0.5;
	else if(MupT == "1") MupTCut = 1.0;
	else if(MupT == "1p5") MupTCut = 1.5;
	else if(MupT == "2") MupTCut = 2.0;
	else if(MupT == "2p5") MupTCut = 2.5;
	else if(MupT == "3") MupTCut = 3.0;
	else if(MupT == "3p5") MupTCut = 3.5;
	else if(MupT == "4") MupTCut = 4.0;
	else
	{
		cout << "There is no such muon pT cut value" << endl;
		return;
	}
//}}}

	TFile* fMC  = new TFile(Form("Yield_count_MC_PADoubleMuon_1S_MupT%s_official.root", MupT.Data()), "READ");
	TH1D* hMCtmp = (TH1D*) fMC->Get("h1");
	TH1D* hdata = new TH1D("hdata", ";p_{T} (GeV/c);dN/dp_{T}", pt_narr-1, ptBinsArr);
	TH1D* hMC = new TH1D("hMC", ";p_{T} (GeV/c);dN/dp_{T}", pt_narr-1, ptBinsArr);
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
	TCanvas* c3 = new TCanvas("c3", "", 0, 0, 600, 800);
	FormTH1Marker(hdata, 1, 1, 1);
	FormTH1Marker(hMC, 0, 1, 1);

	Double_t binwidth = 0;
	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		TFile* fin  = new TFile(Form("Yield_Mult_%d-%d_pt_%d-%d_rap_-24-24_Data_%s_noWeight_MupT%s.root", multMin, multMax, (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], version.Data(), MupT.Data()), "READ");
		TH1D* htmp = (TH1D*) fin->Get("hYield");
		binwidth = hdata->GetBinWidth(ipt+1);
		hdata->SetBinContent(ipt+1, (double)htmp->GetBinContent(1)/binwidth);
		hdata->SetBinError(ipt+1, htmp->GetBinError(1)/TMath::Sqrt(binwidth));
		hMC->SetBinContent(ipt+1, hMCtmp->GetBinContent(ipt+1)/binwidth);
		hMC->SetBinError(ipt+1, hMCtmp->GetBinError(ipt+1)/TMath::Sqrt(binwidth));
	}
	c1->cd();
	hdata->Draw("pe");
	c1->SaveAs(Form("BinWidth_Kinematic_dist_Data_1S_%s_MupT%s.pdf", version.Data(), MupT.Data()));
	c2->cd();
	hMC->Draw("pe");
	c2->SaveAs(Form("BinWidth_Kinematic_dist_MC_1S_%s_MupT%s.pdf", version.Data(), MupT.Data()));

	hdata->Scale(1./hdata->Integral());
	hMC->Scale(1./hMC->Integral());

	c3->cd();
	TPad* pad_comp = new TPad("pad_comp", "pad_comp", 0, 0.25, 0.98, 1.0);
	TPad* pad_ratio = new TPad("pad_ratio", "pad_ratio", 0, 0.05, 0.98, 0.25);
	pad_comp->SetBottomMargin(0.001);
	pad_ratio->SetBottomMargin(0.18);
	pad_ratio->SetTopMargin(0.001);
	pad_comp->Draw();
	pad_ratio->Draw();

	pad_comp->cd();
	hdata->SetMaximum(0.35);
	hdata->Draw("pe");
	hMC->Draw("pesame");
	TLatex* lt1 = new TLatex();
	lt1->SetNDC();
	lt1->SetTextSize(0.04);
	lt1->DrawLatex(0.54,0.59, Form("%d < N^{offline}_{trk} < %d", multMin, multMax));
	lt1->DrawLatex(0.54,0.51, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.54,0.43,"|y^{#varUpsilon}| < 2.4");
	TLegend* leg1 = new TLegend(0.65, 0.70, 0.9, 0.85);
	FormLegend(leg1, 0.04);
	leg1->AddEntry(hdata, "DATA", "pe");
	leg1->AddEntry(hMC, "MC", "pe");
	leg1->Draw();

	pad_ratio->cd();
	TH1D* hratio = (TH1D*) hdata->Clone("hratio");
	hratio->Divide(hMC);
	hratio->SetMarkerColor(1);
	hratio->SetLineColor(1);
	hratio->GetYaxis()->SetTitle("DATA/MC");
	hratio->GetYaxis()->SetTitleSize(0.15);
	hratio->GetYaxis()->SetTitleOffset(0.2);
	hratio->GetXaxis()->SetTitleSize(0.1);
	hratio->GetXaxis()->SetTitleOffset(0.8);
	hratio->SetMaximum(1.3);
	hratio->SetMinimum(0.7);
	hratio->Draw("pe");
	TF1* fit1 = new TF1("fit1", "([0]*x*x+[1]*x+[2])/((x-[3])*(x-[3])*(x-[3]))", 0, 30);
	fit1->SetLineColor(100);
	hratio->Fit(fit1, "rqm");
	SetLine(2, 0, 1, 30, 1, 0, 3);
	c3->SaveAs(Form("Kinematic_dist_comp_1S_%s_MupT%s.pdf", version.Data(), MupT.Data()));

	TFile* fout = new TFile(Form("Kinematic_dist_comp_1S_%s_MupT%s.root", version.Data(), MupT.Data()), "RECREATE");
	fout->cd();
	hdata->Write();
	hMC->Write();
	hratio->Write();
	fit1->Write();
	fout->Close();
}
