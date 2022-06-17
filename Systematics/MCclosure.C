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

void MCclosure(const Int_t multMinhi = 0, const Int_t multMaxhi = 300, const Int_t multMinlow = 0, const Int_t multMaxlow = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const TString versionhi = "v56", const TString versionlow = "v55", const TString Jversionhi = "v47", const TString Jversionlow = "v48", const TString MupT = "4")
{
	SetStyle();

//set fitting condition name{{{
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
	TCanvas* c3 = new TCanvas("c3", "", 0, 0, 600, 600);
	TH1D* hist1 = new TH1D("hist1", "", 30, 0, 30);
	FormTH1Marker(hist1, 0, 0, 1.4);
	hist1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist1->GetYaxis()->SetTitle("v_{2}");
	hist1->SetMinimum(-0.1);
	hist1->SetMaximum(0.3);
	TH1D* hist2 = new TH1D("hist2", "", 30, 0, 30);
	FormTH1Marker(hist2, 0, 0, 1.4);
	hist2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist2->GetYaxis()->SetTitle("v_{2} diff.");
	hist2->SetMinimum(-0.08);
	hist2->SetMaximum(0.15);
	TH1D* hist3 = new TH1D("hist3", "", 30, 0, 30);
	FormTH1Marker(hist3, 0, 0, 1.4);
	hist3->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hist3->GetYaxis()->SetTitle("v_{2} ratio");
	hist3->SetMinimum(0.7);
	hist3->SetMaximum(1.5);
//}}}

	TFile* fout = new TFile(Form("SystFile/MupT%s/v2_diff_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_by_%s_jet_%s_by_%s_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "RECREATE");

//Get vn file{{{
	TFile* fin = new TFile(Form("../SubtractTrk/V2File/MupT%s/Final_v2_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_by_%s_jet_%s_by_%s_MupT%s.root", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()), "READ");
//}}}

//calculate v2 value{{{
	TGraphErrors* greco = (TGraphErrors*) fin->Get(Form("gv2_reco"));
	greco->SetMarkerColor(kRed+1);
	greco->SetMarkerSize(1.4);
	greco->SetLineColor(kRed+1);
	TGraphErrors* ggen = (TGraphErrors*) fin->Get(Form("gv2_gen"));
	ggen->SetMarkerColor(1);
	ggen->SetMarkerSize(1.4);
	ggen->SetLineColor(1);

	Double_t v2xgen[4];
	Double_t v2ygen[4];
	Double_t v2xreco[4];
	Double_t v2yreco[4];
	Double_t Exgen[4];
	Double_t Eygen[4];
	Double_t Exreco[4];
	Double_t Eyreco[4];
	Double_t v2ydiff[4];
	Double_t Ev2ydiff[4];
	Double_t v2yratio[4];
	Double_t Ev2yratio[4];
	Double_t rate[4];

	for(Int_t ibin = 0; ibin < greco->GetN(); ibin++)
	{
		greco->GetPoint(ibin, v2xreco[ibin], v2yreco[ibin]);
		ggen->GetPoint(ibin, v2xgen[ibin], v2ygen[ibin]);
		Exreco[ibin] = greco->GetErrorX(ibin);
		Eyreco[ibin] = greco->GetErrorY(ibin);
		Exgen[ibin] = ggen->GetErrorX(ibin);
		Eygen[ibin] = ggen->GetErrorY(ibin);
		ggen->SetPoint(ibin, v2xgen[ibin]+0.5, v2ygen[ibin]);
		ggen->SetPointError(ibin, Exgen[ibin], Eygen[ibin]);
		v2ydiff[ibin] = v2yreco[ibin]-v2ygen[ibin];
		Ev2ydiff[ibin] = TMath::Sqrt(Eyreco[ibin]*Eyreco[ibin]+Eygen[ibin]*Eygen[ibin]);
		v2yratio[ibin] = v2yreco[ibin]/v2ygen[ibin];
		Ev2yratio[ibin] = (v2yreco[ibin]/v2ygen[ibin])*TMath::Sqrt( Eyreco[ibin]*Eyreco[ibin]/(v2yreco[ibin]*v2yreco[ibin]) + Eygen[ibin]*Eygen[ibin]/(v2ygen[ibin]*v2ygen[ibin]) );
	//	rate[ibin] = v2ydiff[ibin]/TMath::Abs(v2yref[ibin]);
//cout << rate[ibin] << endl;
	}

	c1->cd();
	hist1->Draw();
	ggen->Draw("samepe");
	greco->Draw("samepe");
	TLegend* lg1 = new TLegend(0.6, 0.7, 0.9, 0.85);
	FormLegend(lg1, 0.04);
	lg1->AddEntry(ggen, "Gen", "pl");
	lg1->AddEntry(greco, "Reco", "pl");
	lg1->Draw();
	TLatex *lt1 = new TLatex();
	FormLatex(lt1, 12, 0.05);
	lt1->DrawLatex(0.20, 0.83, "PYTHIA 8.16 TeV");
	lt1->DrawLatex(0.20, 0.77, "EPOS embedded");
	c1->SaveAs(Form("SystPlot/MupT%s/Syst_v2_comp_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_by_%s_jet_%s_by_%s_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c2->cd();
	hist2->Draw();
	TGraphErrors* gdiff = new TGraphErrors(greco->GetN(), v2xreco, v2ydiff, Exreco, Ev2ydiff);
	gdiff->SetName("gv2_diff");
	gdiff->SetMarkerStyle(20);
	gdiff->SetMarkerSize(1.4);
	gdiff->Draw("samepe");
	SetLine(1, 0, 0, 30, 0, 0, 3);
	TLegend* lg2 = new TLegend(0.6, 0.7, 0.9, 0.85);
	FormLegend(lg2, 0.04);
	lg2->AddEntry(gdiff, "Reco-Gen", "pl");
	lg2->Draw();
	TLatex *lt2 = new TLatex();
	FormLatex(lt2, 12, 0.05);
	lt2->DrawLatex(0.20, 0.83, "PYTHIA 8.16 TeV");
	lt2->DrawLatex(0.20, 0.77, "EPOS embedded");
	c2->SaveAs(Form("SystPlot/MupT%s/Syst_v2_diff_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_by_%s_jet_%s_by_%s_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	c3->cd();
	hist3->Draw();
	TGraphErrors* gratio = new TGraphErrors(greco->GetN(), v2xreco, v2yratio, Exreco, Ev2yratio);
	gratio->SetName("gv2_ratio");
	gratio->SetMarkerStyle(20);
	gratio->SetMarkerSize(1.4);
	gratio->Draw("samepe");
	SetLine(1, 0, 1, 30, 1, 0, 3);
	TLegend* lg3 = new TLegend(0.6, 0.7, 0.9, 0.85);
	FormLegend(lg3, 0.04);
	lg3->AddEntry(gratio, "Reco/Gen", "pl");
	lg3->Draw();
	TLatex *lt3 = new TLatex();
	FormLatex(lt3, 12, 0.05);
	lt3->DrawLatex(0.20, 0.83, "PYTHIA 8.16 TeV");
	lt3->DrawLatex(0.20, 0.77, "EPOS embedded");
	c3->SaveAs(Form("SystPlot/MupT%s/Syst_v2_ratio_Mult_%d-%d_by_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_by_%s_jet_%s_by_%s_MupT%s.pdf", MupT.Data(), multMinhi, multMaxhi, multMinlow, multMaxlow, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, versionhi.Data(), versionlow.Data(), Jversionhi.Data(), Jversionlow.Data(), MupT.Data()));

	fout->cd();
	gdiff->Write();
	gratio->Write();
	fout->Close();
//}}}
}
