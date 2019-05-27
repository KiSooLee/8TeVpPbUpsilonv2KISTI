//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <iostream>
#include <TString.h>
#include <TLegend.h>
#include <TMath.h>
#include "../../Headers/Upsilon.h"
#include "../../Headers/Style_Upv2.h"
//}}}

void YieldDist(TString version = "v1", TString MupT = "4")
{
	gStyle->SetOptStat(0000);

//Define canvas and histograms{{{
	TCanvas* c1S = new TCanvas("c1S", "", 0, 0, 600, 600);
	TCanvas* c2S = new TCanvas("c2S", "", 0, 0, 600, 600);
	TCanvas* c3S = new TCanvas("c3S", "", 0, 0, 600, 600);
	TCanvas* call = new TCanvas("call", "", 0, 0, 600, 600);
	TCanvas* c1SN = new TCanvas("c1SN", "", 0, 0, 600, 600);
	TCanvas* c2SN = new TCanvas("c2SN", "", 0, 0, 600, 600);
	TCanvas* c3SN = new TCanvas("c3SN", "", 0, 0, 600, 600);
	TCanvas* callN = new TCanvas("callN", "", 0, 0, 600, 600);
	TH1D* h1S, * h1SN;
	TH1D* h2S, * h2SN;
	TH1D* h3S, * h3SN;
	if(mult_narr > 2)
	{
		h1S = new TH1D("h1S", ";multiplicity;Counts", mult_narr-1, multBinsArr);
		h2S = new TH1D("h2S", ";multiplicity;Counts", mult_narr-1, multBinsArr);
		h3S = new TH1D("h3S", ";multiplicity;Counts", mult_narr-1, multBinsArr);
		h1SN = new TH1D("h1SN", ";multiplicity;Counts", mult_narr-1, multBinsArr);
		h2SN = new TH1D("h2SN", ";multiplicity;Counts", mult_narr-1, multBinsArr);
		h3SN = new TH1D("h3SN", ";multiplicity;Counts", mult_narr-1, multBinsArr);
	}
	else if(pt_narr > 2)
	{
		h1S = new TH1D("h1S", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
		h2S = new TH1D("h2S", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
		h3S = new TH1D("h3S", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
		h1SN = new TH1D("h1SN", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
		h2SN = new TH1D("h2SN", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
		h3SN = new TH1D("h3SN", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
	}
	else if(rap_narr > 2)
	{
		h1S = new TH1D("h1S", ";y;Counts", rap_narr-1, rapBinsArr);
		h2S = new TH1D("h2S", ";y;Counts", rap_narr-1, rapBinsArr);
		h3S = new TH1D("h3S", ";y;Counts", rap_narr-1, rapBinsArr);
		h1SN = new TH1D("h1SN", ";y;Counts", rap_narr-1, rapBinsArr);
		h2SN = new TH1D("h2SN", ";y;Counts", rap_narr-1, rapBinsArr);
		h3SN = new TH1D("h3SN", ";y;Counts", rap_narr-1, rapBinsArr);
	}
	FormTH1Marker(h1S, 0, 1, 1);
	FormTH1Marker(h2S, 1, 1, 1);
	FormTH1Marker(h3S, 2, 1, 1);
	FormTH1Marker(h1SN, 0, 1, 1);
	FormTH1Marker(h2SN, 1, 1, 1);
	FormTH1Marker(h3SN, 2, 1, 1);
//}}}

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

	for(Int_t imult = 0; imult < mult_narr-1; imult++)
	{
		for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
		{
			for(Int_t irap = 0; irap < rap_narr-1; irap++)
			{
				TFile* fin  = new TFile(Form("Yield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_%s_MupT%s.root", (int)multBinsArr[imult], (int)multBinsArr[imult+1], (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)(10*rapBinsArr[irap]), (int)(10*rapBinsArr[irap+1]), version.Data(), MupT.Data()), "READ");
				TH1D* hin = (TH1D*) fin->Get("hYield");

				Double_t w1S = 0;
				Double_t w2S = 0;
				Double_t w3S = 0;

//Fill contents{{{
				if(mult_narr > 2)
				{
					w1S = h1S->GetBinWidth(imult+1);
					w2S = h2S->GetBinWidth(imult+1);
					w3S = h3S->GetBinWidth(imult+1);
					h1S->SetBinContent(imult+1, (double)hin->GetBinContent(1));
					h1S->SetBinError(imult+1, hin->GetBinError(1));
					h2S->SetBinContent(imult+1, (double)hin->GetBinContent(2));
					h2S->SetBinError(imult+1, hin->GetBinError(2));
					h3S->SetBinContent(imult+1, (double)hin->GetBinContent(3));
					h3S->SetBinError(imult+1, hin->GetBinError(3));
					h1SN->SetBinContent(imult+1, (double)hin->GetBinContent(1)/w1S);
					h1SN->SetBinError(imult+1, hin->GetBinError(1)/TMath::Sqrt(w1S));
					h2SN->SetBinContent(imult+1, (double)hin->GetBinContent(2)/w2S);
					h2SN->SetBinError(imult+1, hin->GetBinError(2)/TMath::Sqrt(w2S));
					h3SN->SetBinContent(imult+1, (double)hin->GetBinContent(3)/w3S);
					h3SN->SetBinError(imult+1, hin->GetBinError(3)/TMath::Sqrt(w3S));
				}
				else if (pt_narr > 2)
				{
					w1S = h1S->GetBinWidth(ipt+1);
					w2S = h2S->GetBinWidth(ipt+1);
					w3S = h3S->GetBinWidth(ipt+1);
					h1S->SetBinContent(ipt+1, (double)hin->GetBinContent(1));
					h1S->SetBinError(ipt+1, hin->GetBinError(1));
					h2S->SetBinContent(ipt+1, (double)hin->GetBinContent(2));
					h2S->SetBinError(ipt+1, hin->GetBinError(2));
					h3S->SetBinContent(ipt+1, (double)hin->GetBinContent(3));
					h3S->SetBinError(ipt+1, hin->GetBinError(3));
					h1SN->SetBinContent(ipt+1, (double)hin->GetBinContent(1)/w1S);
					h1SN->SetBinError(ipt+1, hin->GetBinError(1)/TMath::Sqrt(w1S));
					h2SN->SetBinContent(ipt+1, (double)hin->GetBinContent(2)/w2S);
					h2SN->SetBinError(ipt+1, hin->GetBinError(2)/TMath::Sqrt(w2S));
					h3SN->SetBinContent(ipt+1, (double)hin->GetBinContent(3)/w3S);
					h3SN->SetBinError(ipt+1, hin->GetBinError(3)/TMath::Sqrt(w3S));
				}
				else if(rap_narr > 2)
				{
					w1S = h1S->GetBinWidth(irap+1);
					w2S = h2S->GetBinWidth(irap+1);
					w3S = h3S->GetBinWidth(irap+1);
					h1S->SetBinContent(irap+1, (double)hin->GetBinContent(1));
					h1S->SetBinError(irap+1, hin->GetBinError(1));
					h2S->SetBinContent(irap+1, (double)hin->GetBinContent(2));
					h2S->SetBinError(irap+1, hin->GetBinError(2));
					h3S->SetBinContent(irap+1, (double)hin->GetBinContent(3));
					h3S->SetBinError(irap+1, hin->GetBinError(3));
					h1SN->SetBinContent(irap+1, (double)hin->GetBinContent(1)/w1S);
					h1SN->SetBinError(irap+1, hin->GetBinError(1)/TMath::Sqrt(w1S));
					h2SN->SetBinContent(irap+1, (double)hin->GetBinContent(2)/w2S);
					h2SN->SetBinError(irap+1, hin->GetBinError(2)/TMath::Sqrt(w2S));
					h3SN->SetBinContent(irap+1, (double)hin->GetBinContent(3)/w3S);
					h3SN->SetBinError(irap+1, hin->GetBinError(3)/TMath::Sqrt(w3S));
				}
//}}}

				fin->Close();
			}
		}
	}
	h1S->SetMinimum(0);
	h2S->SetMinimum(0);
	h3S->SetMinimum(0);
	h1SN->SetMinimum(0);
	h2SN->SetMinimum(0);
	h3SN->SetMinimum(0);

	c1S->cd();
	h1S->Draw("petext0");
	TLatex* lt1 = new TLatex();
	lt1->SetNDC();
	lt1->SetTextSize(0.04);
	lt1->DrawLatex(0.54,0.70, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.54,0.63,Form("%d < p_{T}^{#Upsilon} < %d GeV/c", (int)ptBinsArr[0], (int)ptBinsArr[pt_narr-1]));
	lt1->DrawLatex(0.54,0.56,Form("%d < mult. < %d", (int)multBinsArr[0], (int)multBinsArr[mult_narr-1]));
	lt1->DrawLatex(0.54,0.49,"|y^{#Upsilon}| < 2.4");
	c1S->SaveAs(Form("Yield_distribution_1S_%s_MupT%s.pdf", version.Data(), MupT.Data()));

	c1SN->cd();
	h1SN->Draw();
	TLatex* lt1N = new TLatex();
	lt1N->SetNDC();
	lt1N->SetTextSize(0.04);
	lt1N->DrawLatex(0.54,0.70, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1N->DrawLatex(0.54,0.63,Form("%d < p_{T}^{#Upsilon} < %d GeV/c", (int)ptBinsArr[0], (int)ptBinsArr[pt_narr-1]));
	lt1N->DrawLatex(0.54,0.56,Form("%d < mult. < %d", (int)multBinsArr[0], (int)multBinsArr[mult_narr-1]));
	lt1N->DrawLatex(0.54,0.49,"|y^{#Upsilon}| < 2.4");
	c1SN->SaveAs(Form("Yield_distribution_1SN_%s_MupT%s.pdf", version.Data(), MupT.Data()));

	c2S->cd();
	h2S->Draw("petext0");
	c2S->SaveAs(Form("Yield_distribution_2S_%s_MupT%s.pdf", version.Data(), MupT.Data()));

	c2SN->cd();
	h2SN->Draw();
	c2SN->SaveAs(Form("Yield_distribution_2SN_%s_MupT%s.pdf", version.Data(), MupT.Data()));

	c3S->cd();
	h3S->Draw("petext0");
	c3S->SaveAs(Form("Yield_distribution_3S_%s_MupT%s.pdf", version.Data(), MupT.Data()));

	c3SN->cd();
	h3SN->Draw();
	c3SN->SaveAs(Form("Yield_distribution_3SN_%s_MupT%s.pdf", version.Data(), MupT.Data()));

	call->cd();
	h1S->Draw();
	h2S->Draw("same");
	h3S->Draw("same");
	TLegend* l1 = new TLegend(0.7, 0.7, 0.9, 0.9);
	FormLegend(l1, 0.04);
	l1->AddEntry(h1S, "#Upsilon (1S)", "pl");
	l1->AddEntry(h2S, "#Upsilon (2S)", "pl");
	l1->AddEntry(h3S, "#Upsilon (3S)", "pl");
	l1->Draw();
	lt1N->DrawLatex(0.54,0.66, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1N->DrawLatex(0.54,0.59,Form("%d < p_{T}^{#Upsilon} < %d GeV/c", (int)ptBinsArr[0], (int)ptBinsArr[pt_narr-1]));
	lt1N->DrawLatex(0.54,0.52,Form("%d < mult. < %d", (int)multBinsArr[0], (int)multBinsArr[mult_narr-1]));
	lt1N->DrawLatex(0.54,0.45,"|y^{#Upsilon}| < 2.4");
	call->SaveAs(Form("Yield_distribution_all_%s_MupT%s.pdf", version.Data(), MupT.Data()));

	callN->cd();
	h1SN->Draw();
	h2SN->Draw("same");
	h3SN->Draw("same");
	TLegend* l1N = new TLegend(0.7, 0.7, 0.9, 0.9);
	FormLegend(l1N, 0.04);
	l1N->AddEntry(h1S, "#Upsilon (1S)", "pl");
	l1N->AddEntry(h2S, "#Upsilon (2S)", "pl");
	l1N->AddEntry(h3S, "#Upsilon (3S)", "pl");
	l1N->Draw();
	lt1N->DrawLatex(0.54,0.66, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1N->DrawLatex(0.54,0.59,Form("%d < p_{T}^{#Upsilon} < %d GeV/c", (int)ptBinsArr[0], (int)ptBinsArr[pt_narr-1]));
	lt1N->DrawLatex(0.54,0.52,Form("%d < mult. < %d", (int)multBinsArr[0], (int)multBinsArr[mult_narr-1]));
	lt1N->DrawLatex(0.54,0.45,"|y^{#Upsilon}| < 2.4");
	callN->SaveAs(Form("Yield_distribution_allN_%s_MupT%s.pdf", version.Data(), MupT.Data()));
}
