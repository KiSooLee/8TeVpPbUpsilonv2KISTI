#ifndef STYLE_KISOO_H
#define STYLE_KISOO_H

//Headers{{{
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TLine.h>
#include <TText.h>
#include <TString.h>
#include <iostream>
#include <RooPlot.h>
//}}}

const Int_t colorArr[] = {1, 100, 60, 419, 222, 93, 219, 228};
const Int_t markerArr[] = {20, 21, 29, 33, 34, 22, 23, 28};
const Int_t hfillArr[]  = {2004, 2011, 2022, 2020, 2025, 3006, 3007, 2016};

void SetStyle()
{
//{{{
	gROOT->SetStyle("Plain");
	gStyle->SetOptFit(1);
	gStyle->SetTitleFont(62,"xyz");
	gStyle->SetLabelFont(62,"xyz");
	gStyle->SetPalette(1);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0000);
	gStyle->SetTitleFillColor(0);
	gStyle->SetStatColor(0);

	gStyle->SetFrameBorderMode(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameLineColor(kBlack);

	gStyle->SetCanvasColor(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasBorderSize(0);
	gStyle->SetCanvasDefH(600);
	gStyle->SetCanvasDefW(600);

	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.12);
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.065);
	gStyle->SetPadColor(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadBorderSize(0);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
//}}}
}

void FormLegend(TLegend* leg, Double_t size)
{
//{{{
	leg->SetFillStyle(0);
	leg->SetFillColor(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(size);
//}}}
}

void FormLatex(TLatex* latex, Int_t align, Double_t size)
{
//{{{
	latex->SetNDC();
	latex->SetTextAlign(align);
	latex->SetTextFont(42);
	latex->SetTextSize(size);
//}}}
}

void FormTH1(TH1* h1, Int_t color)
{
//{{{
	h1->Sumw2();
	h1->GetXaxis()->CenterTitle();
	h1->GetYaxis()->CenterTitle();
	h1->GetXaxis()->SetTitleOffset(1.0);
	h1->GetYaxis()->SetTitleOffset(1.0);
	h1->GetXaxis()->SetTitleSize(0.048);
	h1->GetYaxis()->SetTitleSize(0.048);
	h1->GetXaxis()->SetTitleFont(42);
	h1->GetYaxis()->SetTitleFont(42);
	h1->GetXaxis()->SetLabelOffset(0.007);
	h1->GetYaxis()->SetLabelOffset(0.007);
	h1->GetXaxis()->SetLabelSize(0.04);
	h1->GetYaxis()->SetLabelSize(0.04);
	h1->GetXaxis()->SetLabelFont(42);
	h1->GetYaxis()->SetLabelFont(42);
	h1->SetLineColor(colorArr[color]);
	h1->SetLineWidth(2);
//}}}
}

void FormTH1Marker(TH1* h1, Int_t color, Int_t marker, Double_t size)
{
//{{{
	h1->Sumw2();
	h1->GetXaxis()->CenterTitle();
	h1->GetYaxis()->CenterTitle();
	h1->GetXaxis()->SetTitleOffset(1.0);
	h1->GetYaxis()->SetTitleOffset(1.0);
	h1->GetXaxis()->SetTitleSize(0.048);
	h1->GetYaxis()->SetTitleSize(0.048);
	h1->GetXaxis()->SetTitleFont(42);
	h1->GetYaxis()->SetTitleFont(42);
	h1->GetXaxis()->SetLabelOffset(0.007);
	h1->GetYaxis()->SetLabelOffset(0.007);
	h1->GetXaxis()->SetLabelSize(0.04);
	h1->GetYaxis()->SetLabelSize(0.04);
	h1->GetXaxis()->SetLabelFont(42);
	h1->GetYaxis()->SetLabelFont(42);
	h1->SetLineColor(colorArr[color]);
	h1->SetLineWidth(2);
	h1->SetMarkerStyle(markerArr[marker]);
	h1->SetMarkerColor(colorArr[color]);
	h1->SetMarkerSize(size);
//}}}
}

void FormTH1Fill(TH1* h1, Int_t color, Int_t hfill)
{
//{{{
	h1->Sumw2();
	h1->GetXaxis()->CenterTitle();
	h1->GetYaxis()->CenterTitle();
	h1->GetXaxis()->SetTitleOffset(1.0);
	h1->GetYaxis()->SetTitleOffset(1.0);
	h1->GetXaxis()->SetTitleSize(0.048);
	h1->GetYaxis()->SetTitleSize(0.048);
	h1->GetXaxis()->SetTitleFont(42);
	h1->GetYaxis()->SetTitleFont(42);
	h1->GetXaxis()->SetLabelOffset(0.007);
	h1->GetYaxis()->SetLabelOffset(0.007);
	h1->GetXaxis()->SetLabelSize(0.04);
	h1->GetYaxis()->SetLabelSize(0.04);
	h1->GetXaxis()->SetLabelFont(42);
	h1->GetYaxis()->SetLabelFont(42);
	h1->SetFillColor(colorArr[color]);
	h1->SetFillStyle(hfillArr[hfill]);
	h1->SetLineColor(colorArr[color]);
	h1->SetLineWidth(2);
//}}}
}

void FormTH2(TH2* h1)
{
//{{{
	h1->Sumw2();
	h1->GetXaxis()->CenterTitle();
	h1->GetYaxis()->CenterTitle();
	h1->GetZaxis()->CenterTitle();
	h1->GetXaxis()->SetTitleOffset(1.0);
	h1->GetYaxis()->SetTitleOffset(1.0);
	h1->GetZaxis()->SetTitleOffset(1.0);
	h1->GetXaxis()->SetTitleSize(0.048);
	h1->GetYaxis()->SetTitleSize(0.048);
	h1->GetZaxis()->SetTitleSize(0.048);
	h1->GetXaxis()->SetTitleFont(42);
	h1->GetYaxis()->SetTitleFont(42);
	h1->GetZaxis()->SetTitleFont(42);
	h1->GetXaxis()->SetLabelOffset(0.007);
	h1->GetYaxis()->SetLabelOffset(0.007);
	h1->GetZaxis()->SetLabelOffset(0.007);
	h1->GetXaxis()->SetLabelSize(0.04);
	h1->GetYaxis()->SetLabelSize(0.04);
	h1->GetZaxis()->SetLabelSize(0.04);
	h1->GetXaxis()->SetLabelFont(42);
	h1->GetYaxis()->SetLabelFont(42);
	h1->GetZaxis()->SetLabelFont(42);
//}}}
}

void MaxRange(TH1* h1, TH1* h2, Double_t weight = 1.2, Double_t min = 1)
{
//{{{
	Double_t max1 = weight*h1->GetBinContent(h1->GetMaximumBin());
	Double_t max2 = weight*h2->GetBinContent(h2->GetMaximumBin());
	h1->SetAxisRange(min, TMath::Max(max1, max2), "Y");
	h2->SetAxisRange(min, TMath::Max(max1, max2), "Y");
//}}}
}

void RooMaxRange(RooPlot* h1, RooPlot* h2, Double_t weight = 1.2, Double_t min = 1)
{
//{{{
	Double_t max1 = weight*h1->GetMaximum();
	Double_t max2 = weight*h2->GetMaximum();
	h1->SetAxisRange(min, TMath::Max(max1, max2), "Y");
	h2->SetAxisRange(min, TMath::Max(max1, max2), "Y");
//}}}
}

void FormGraph(TGraph* g1, Int_t color, Int_t marker, Double_t size)
{
//{{{
	g1->GetXaxis()->CenterTitle();
	g1->GetYaxis()->CenterTitle();
	g1->GetXaxis()->SetTitleOffset(1.0);
	g1->GetYaxis()->SetTitleOffset(1.0);
	g1->GetXaxis()->SetTitleSize(0.048);
	g1->GetYaxis()->SetTitleSize(0.048);
	g1->GetXaxis()->SetTitleFont(42);
	g1->GetYaxis()->SetTitleFont(42);
	g1->GetXaxis()->SetLabelOffset(0.007);
	g1->GetYaxis()->SetLabelOffset(0.007);
	g1->GetXaxis()->SetLabelSize(0.04);
	g1->GetYaxis()->SetLabelSize(0.04);
	g1->GetXaxis()->SetLabelFont(42);
	g1->GetYaxis()->SetLabelFont(42);
	g1->SetLineColor(colorArr[color]);
	g1->SetMarkerStyle(markerArr[marker]);
	g1->SetMarkerColor(colorArr[color]);
	g1->SetMarkerSize(size);
//}}}
}

void SetLine(Int_t style, Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t color = 1, Double_t width = 1)
{
//{{{
	TLine* l1 = new TLine(x1, y1, x2, y2);
	l1->SetLineStyle(style);//1: solid line, 2: dashed line
	l1->SetLineWidth(width);
	l1->SetLineColor(colorArr[color]);
	l1->Draw();
//}}}
}

void WriteMessage(TString message)
{
//{{{
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "[[[[[[[[[[ " << message.Data() << " ]]]]]]]]]]" << endl;
	cout << "[[[[[[[[[[ " << message.Data() << " ]]]]]]]]]]" << endl;
	cout << "[[[[[[[[[[ " << message.Data() << " ]]]]]]]]]]" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
//}}}
}

void CMSP(Double_t x, Double_t y)
{
//{{{
	TLatex* latex = new TLatex();
	latex->SetNDC();
	latex->SetTextAlign(11);
	latex->SetTextFont(61);
	latex->SetTextSize(0.06);
	latex->DrawLatex(x, y, "CMS");
	latex->SetTextFont(52);
	latex->SetTextSize(0.0456);
	latex->DrawLatex(x+0.13, y, "Preliminary");
//}}}
}

void lumiText(Double_t x, Double_t y)
{
//{{{
	TLatex* latex = new TLatex();
	latex->SetNDC();
	latex->SetTextFont(42);
	latex->SetTextAlign(11);
	latex->SetTextSize(0.04);
	latex->DrawLatex(x, y, "pPb 186 nb^{-1} (8.16 TeV)");
//}}}
}
#endif
