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
#include "Style_Kisoo.h"
#include "Upsilon.h"
//}}}

void set_plot_style() {
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
}

void extV2fromCount_Coarse(bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1", const Int_t nmbin = 120){ 

	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fullDIR = mainDIR + "/CorrDist/CorrDistFull";
	TString fullsigDIR = mainDIR + "/CorrDist/CorrDistFullSig";
	TString fullbkgDIR = mainDIR + "/CorrDist/CorrDistFullBkg";
	TString cut1DIR = mainDIR + "/CorrDist/CorrDistCut1";
	TString cut1sigDIR = mainDIR + "/CorrDist/CorrDistCut1Sig";
	TString cut1bkgDIR = mainDIR + "/CorrDist/CorrDistCut1Bkg";
	TString cut2DIR = mainDIR + "/CorrDist/CorrDistCut2";
	TString cut2sigDIR = mainDIR + "/CorrDist/CorrDistCut2Sig";
	TString cut2bkgDIR = mainDIR + "/CorrDist/CorrDistCut2Bkg";
	TString dphiDIR = mainDIR + "/CorrDist/CorrDistdphi";
	TString fileDIR = mainDIR + "/CorrDist/CorrFiles";

	void * dirf = gSystem->OpenDirectory(fullDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fullDIR.Data(), kTRUE);

	void * dirfs = gSystem->OpenDirectory(fullsigDIR.Data());
	if(dirfs) gSystem->FreeDirectory(dirfs);
	else gSystem->mkdir(fullsigDIR.Data(), kTRUE);

	void * dirfb = gSystem->OpenDirectory(fullbkgDIR.Data());
	if(dirfb) gSystem->FreeDirectory(dirfb);
	else gSystem->mkdir(fullbkgDIR.Data(), kTRUE);

	void * dirc1 = gSystem->OpenDirectory(cut1DIR.Data());
	if(dirc1) gSystem->FreeDirectory(dirc1);
	else gSystem->mkdir(cut1DIR.Data(), kTRUE);

	void * dirc1s = gSystem->OpenDirectory(cut1sigDIR.Data());
	if(dirc1s) gSystem->FreeDirectory(dirc1s);
	else gSystem->mkdir(cut1sigDIR.Data(), kTRUE);

	void * dirc1b = gSystem->OpenDirectory(cut1bkgDIR.Data());
	if(dirc1b) gSystem->FreeDirectory(dirc1b);
	else gSystem->mkdir(cut1bkgDIR.Data(), kTRUE);

	void * dirc2 = gSystem->OpenDirectory(cut2DIR.Data());
	if(dirc2) gSystem->FreeDirectory(dirc2);
	else gSystem->mkdir(cut2DIR.Data(), kTRUE);

	void * dirc2s = gSystem->OpenDirectory(cut2sigDIR.Data());
	if(dirc2s) gSystem->FreeDirectory(dirc2s);
	else gSystem->mkdir(cut2sigDIR.Data(), kTRUE);

	void * dirc2b = gSystem->OpenDirectory(cut2bkgDIR.Data());
	if(dirc2b) gSystem->FreeDirectory(dirc2b);
	else gSystem->mkdir(cut2bkgDIR.Data(), kTRUE);

	void * dird = gSystem->OpenDirectory(dphiDIR.Data());
	if(dird) gSystem->FreeDirectory(dird);
	else gSystem->mkdir(dphiDIR.Data(), kTRUE);

	void * dirfile = gSystem->OpenDirectory(fileDIR.Data());
	if(dirfile) gSystem->FreeDirectory(dirfile);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);
//}}}

	TString DM;
	if(isMC) DM = "MC";
	else DM = "RD";

  // 0 : no draw, 1 : draw plots
	gStyle->SetOptFit(0);
	TH1D *hMass = new TH1D("hMass",";m_{#mu^{+}#mu^{-}} (GeV/c^{2});v_{2}", nmbin, 8, 14);
	FormTH1Marker(hMass, 0, 0, 1);

//Define fitting function{{{
	Double_t v2s = 0.0;
	Double_t v2Errs = 0.0;

	TF1 *v2Fn = new TF1("v2Fn","[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
	v2Fn->SetLineColor(kViolet+1);
	v2Fn->SetLineStyle(2);
	v2Fn->SetLineWidth(2);
//}}}

	TFile *sigPbp;
	TFile *sigpPb;
	TFile *bkgPbp;
	TFile *bkgpPb;

//Define canvas and histogram{{{
	TCanvas* cfull = new TCanvas("cfull", "", 0, 0, 600, 600);
	TCanvas* cfull_sig = new TCanvas("cfull_sig", "", 0, 0, 600, 600);
	TCanvas* cfull_bkg = new TCanvas("cfull_bkg", "", 0, 0, 600, 600);
	TCanvas* ccut1 = new TCanvas("ccut1", "", 0, 0, 600, 600);
	TCanvas* ccut1_sig = new TCanvas("ccut1_sig", "", 0, 0, 600, 600);
	TCanvas* ccut1_bkg = new TCanvas("ccut1_bkg", "", 0, 0, 600, 600);
	TCanvas* ccut2 = new TCanvas("ccut2", "", 0, 0, 600, 600);
	TCanvas* ccut2_sig = new TCanvas("ccut2_sig", "", 0, 0, 600, 600);
	TCanvas* ccut2_bkg = new TCanvas("ccut2_bkg", "", 0, 0, 600, 600);
	TCanvas* cdphi1 = new TCanvas("cdphi1", "", 0, 0, 600, 600);
	TCanvas* cdphi2 = new TCanvas("cdphi2", "", 0, 0, 600, 600);
	TCanvas* cmass = new TCanvas("cmass", "", 0, 0, 600, 600);
	TH2D* hfullRatio;
	TH2D* hcut1Ratio;
	TH2D* hcut2Ratio;

	if(Netabin > 27)
	{
		hfullRatio = new TH2D("hfullRatio", ";#Delta#eta;#Delta#phi", Netabin-4, -9.9*(Netabin-4)/(2*Netabin), 9.9*(Netabin-4)/(2*Netabin), Nphibin,-(0.5-1.0/(Nphibin+1))*TMath::Pi(),(1.5-1.0/(Nphibin+1))*TMath::Pi());
		hcut1Ratio = new TH2D("hcut1Ratio", ";#Delta#eta;#Delta#phi", Netabin-4, -9.9*(Netabin-4)/(2*Netabin), 9.9*(Netabin-4)/(2*Netabin), Nphibin,-(0.5-1.0/(Nphibin+1))*TMath::Pi(),(1.5-1.0/(Nphibin+1))*TMath::Pi());
		hcut2Ratio = new TH2D("hcut2Ratio", ";#Delta#eta;#Delta#phi", Netabin-4, -9.9*(Netabin-4)/(2*Netabin), 9.9*(Netabin-4)/(2*Netabin), Nphibin,-(0.5-1.0/(Nphibin+1))*TMath::Pi(),(1.5-1.0/(Nphibin+1))*TMath::Pi());
	}
	else
	{
		hfullRatio = new TH2D("hfullRatio", ";#Delta#eta;#Delta#phi", Netabin-2, -9.9*(Netabin-2)/(2*Netabin), 9.9*(Netabin-2)/(2*Netabin), Nphibin,-(0.5-1.0/(Nphibin+1))*TMath::Pi(),(1.5-1.0/(Nphibin+1))*TMath::Pi());
		hcut1Ratio = new TH2D("hcut1Ratio", ";#Delta#eta;#Delta#phi", Netabin-2, -9.9*(Netabin-2)/(2*Netabin), 9.9*(Netabin-2)/(2*Netabin), Nphibin,-(0.5-1.0/(Nphibin+1))*TMath::Pi(),(1.5-1.0/(Nphibin+1))*TMath::Pi());
		hcut2Ratio = new TH2D("hcut2Ratio", ";#Delta#eta;#Delta#phi", Netabin-2, -9.9*(Netabin-2)/(2*Netabin), 9.9*(Netabin-2)/(2*Netabin), Nphibin,-(0.5-1.0/(Nphibin+1))*TMath::Pi(),(1.5-1.0/(Nphibin+1))*TMath::Pi());
	}
	hfullRatio->Sumw2();
	hcut1Ratio->Sumw2();
	hcut2Ratio->Sumw2();

	TH2D *hSigPbp;
	TH2D *hSigpPb;
	TH2D *hBkgPbp;
	TH2D *hBkgpPb;
	TH2D *hSig_cut1Pbp;
	TH2D *hSig_cut1pPb;
	TH2D *hBkg_cut1Pbp;
	TH2D *hBkg_cut1pPb;
	TH2D *hSig_cut2Pbp;
	TH2D *hSig_cut2pPb;
	TH2D *hBkg_cut2Pbp;
	TH2D *hBkg_cut2pPb;
/*
	TH1D *hDeltaPhi1 = new TH1D("hDeltaPhi1", ";#Delta#phi;Counts", Nphibin,-(0.5-1.0/(Nphibin+1))*TMath::Pi(),(1.5-1.0/(Nphibin+1))*TMath::Pi());
	TH1D *hDeltaPhi2 = new TH1D("hDeltaPhi2", ";#Delta#phi;Counts", Nphibin,-(0.5-1.0/(Nphibin+1))*TMath::Pi(),(1.5-1.0/(Nphibin+1))*TMath::Pi());
	FormTH1Marker(hDeltaPhi1, 0, 0, 1.4);
	FormTH1Marker(hDeltaPhi2, 0, 0, 1.4);
*/
	TH1D *hDeltaPhi1;
	TH1D *hDeltaPhi2;
//}}}

	for(Int_t imass = 0; imass < nmbin; imass++)
	{

//Get files{{{
		sigPbp = new TFile(Form("%d-%d_%d-%d_%d-%d_%d_%d_%d/deta-dphi_Pbp_distribution_sig_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, nmbin, imass), "READ");
		sigpPb = new TFile(Form("%d-%d_%d-%d_%d-%d_%d_%d_%d/deta-dphi_pPb_distribution_sig_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, nmbin, imass), "READ");
		bkgPbp = new TFile(Form("%d-%d_%d-%d_%d-%d_%d_%d_%d/deta-dphi_Pbp_distribution_bkg_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, nmbin, imass), "READ");
		bkgpPb = new TFile(Form("%d-%d_%d-%d_%d-%d_%d_%d_%d/deta-dphi_pPb_distribution_bkg_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, nmbin, imass), "READ");
//}}}

//Get full range plot{{{
		hSigPbp = (TH2D*)sigPbp->Get("h1");
		hSigpPb = (TH2D*)sigpPb->Get("h1");
		hBkgPbp = (TH2D*)bkgPbp->Get("h1");
		hBkgpPb = (TH2D*)bkgpPb->Get("h1");
		hSigPbp->Sumw2();
		hSigpPb->Sumw2();
		hBkgPbp->Sumw2();
		hBkgpPb->Sumw2();
		hSigPbp->Add(hSigpPb);
		hBkgPbp->Add(hBkgpPb);
		cfull_sig->cd();
		hSigPbp->Draw("Surf1");
		cfull_sig->SaveAs(Form("CorrDist/CorrDistFullSig/plot_corr_full_sig_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));
		cfull_bkg->cd();
		hBkgPbp->Draw("Surf1");
		cfull_bkg->SaveAs(Form("CorrDist/CorrDistFullBkg/plot_corr_full_bkg_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));

		hSigPbp->Divide(hBkgPbp);
		//hSigPbp->Scale(hBkgPbp->GetBinContent(7,7)); // multiply B(0,0) 
		if(Netabin > 27)
		{
			for(Int_t j = 0; j < Netabin-4; j++)
			{
				for(Int_t k = 0; k < Nphibin; k++)
				{
					hfullRatio->SetBinContent(j+1, k+1, hSigPbp->GetBinContent(j+3, k+1));
				}
			}
		}
		else
		{
			for(Int_t j = 0; j < Netabin-2; j++)
			{
				for(Int_t k = 0; k < Nphibin; k++)
				{
					hfullRatio->SetBinContent(j+1, k+1, hSigPbp->GetBinContent(j+2, k+1));
				}
			}
		}
		cfull->cd();
		hfullRatio->Draw("Surf1");
		cfull->SaveAs(Form("CorrDist/CorrDistFull/plot_corr_full_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));
//}}}

		TLatex *lt1 = new TLatex();
		FormLatex(lt1, 12, 0.04);
		lt1->SetNDC();

//Get |deta| > 2 range plot{{{
		hSig_cut2Pbp = (TH2D*)sigPbp->Get("h2");
		hSig_cut2pPb = (TH2D*)sigpPb->Get("h2");
		hBkg_cut2Pbp = (TH2D*)bkgPbp->Get("h2");
		hBkg_cut2pPb = (TH2D*)bkgpPb->Get("h2");
		hSig_cut2Pbp->Sumw2();
		hSig_cut2pPb->Sumw2();
		hBkg_cut2Pbp->Sumw2();
		hBkg_cut2pPb->Sumw2();
		hSig_cut2Pbp->Add(hSig_cut2pPb);
		hBkg_cut2Pbp->Add(hBkg_cut2pPb);
		ccut2_sig->cd();
		hSig_cut2Pbp->Draw("Surf1");
		ccut2_sig->SaveAs(Form("CorrDist/CorrDistCut2Sig/plot_corr_sig_cut2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));
		ccut2_bkg->cd();
		hBkg_cut2Pbp->Draw("Surf1");
		ccut2_bkg->SaveAs(Form("CorrDist/CorrDistCut2Bkg/plot_corr_bkg_cut2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));
		hSig_cut2Pbp->Divide(hBkg_cut2Pbp);
	//	hSig_cut2Pbp->Scale(hBkgPbp->GetBinContent(7,7)); // multiply B(0,0) 
		if(Netabin > 27)
		{
			for(Int_t j = 0; j < Netabin-4; j++)
			{
				for(Int_t k = 0; k < Nphibin; k++)
				{
					hcut2Ratio->SetBinContent(j+1, k+1, hSig_cut2Pbp->GetBinContent(j+3, k+1));
				}
			}
		}
		else
		{
			for(Int_t j = 0; j < Netabin-2; j++)
			{
				for(Int_t k = 0; k < Nphibin; k++)
				{
					hcut2Ratio->SetBinContent(j+1, k+1, hSig_cut2Pbp->GetBinContent(j+2, k+1));
				}
			}
		}
		ccut2->cd();
		hcut2Ratio->Draw("Surf1");
		ccut2->SaveAs(Form("CorrDist/CorrDistCut2/plot_corr_cut2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));
//}}}

//Get |deta| > 1 range plot{{{
		hSig_cut1Pbp = (TH2D*)sigPbp->Get("h3");
		hSig_cut1pPb = (TH2D*)sigpPb->Get("h3");
		hBkg_cut1Pbp = (TH2D*)bkgPbp->Get("h3");
		hBkg_cut1pPb = (TH2D*)bkgpPb->Get("h3");
		hSig_cut1Pbp->Sumw2();
		hSig_cut1pPb->Sumw2();
		hBkg_cut1Pbp->Sumw2();
		hBkg_cut1pPb->Sumw2();
		hSig_cut1Pbp->Add(hSig_cut1pPb);
		hBkg_cut1Pbp->Add(hBkg_cut1pPb);
		ccut1_sig->cd();
		hSig_cut1Pbp->Draw("Surf1");
		ccut1_sig->SaveAs(Form("CorrDist/CorrDistCut1Sig/plot_corr_sig_cut1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));
		ccut1_bkg->cd();
		hBkg_cut1Pbp->Draw("Surf1");
		ccut1_bkg->SaveAs(Form("CorrDist/CorrDistCut1Bkg/plot_corr_bkg_cut1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));
		hSig_cut1Pbp->Divide(hBkg_cut1Pbp);
	//	hSig_cut1Pbp->Scale(hBkgPbp->GetBinContent(7,7)); // multiply B(0,0) 
		if(Netabin > 27)
		{
			for(Int_t j = 0; j < Netabin-4; j++)
			{
				for(Int_t k = 0; k < Nphibin; k++)
				{
					hcut1Ratio->SetBinContent(j+1, k+1, hSig_cut1Pbp->GetBinContent(j+3, k+1));
				}
			}
		}
		else
		{
			for(Int_t j = 0; j < Netabin-2; j++)
			{
				for(Int_t k = 0; k < Nphibin; k++)
				{
					hcut1Ratio->SetBinContent(j+1, k+1, hSig_cut1Pbp->GetBinContent(j+2, k+1));
				}
			}
		}
		ccut1->cd();
		hcut1Ratio->Draw("Surf1");
		ccut1->SaveAs(Form("CorrDist/CorrDistCut1/plot_corr_cut1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));
//}}}

		hDeltaPhi1 = (TH1D*)hcut1Ratio->ProjectionY();
		hDeltaPhi2 = (TH1D*)hcut2Ratio->ProjectionY();
	FormTH1Marker(hDeltaPhi1, 0, 0, 1.);
	FormTH1Marker(hDeltaPhi2, 0, 0, 1.);
	//	hDeltaPhi1->Sumw2();
	//	hDeltaPhi2->Sumw2();
/*
		for(Int_t j = 0; j < Nphibin; j++)
		{

			Double_t deta_sum1 = 0;
			Double_t deta_sum2 = 0;
			Double_t deta_err_sum1 = 0;
			Double_t deta_err_sum2 = 0;
			for(Int_t k = 0; k < Netabin; k++)
			{
				deta_sum1 += hcut1Ratio->GetBinContent(k+1, j+1);
				deta_sum2 += hcut2Ratio->GetBinContent(k+1, j+1);
				deta_err_sum1 += hcut1Ratio->GetBinError(k+1, j+1);
				deta_err_sum2 += hcut2Ratio->GetBinError(k+1, j+1);
			}
			hDeltaPhi1->SetBinContent(j+1, deta_sum1);
			hDeltaPhi1->SetBinError(j+1, deta_err_sum1);
			hDeltaPhi2->SetBinContent(j+1, deta_sum2);
			hDeltaPhi2->SetBinError(j+1, deta_err_sum2);
		}
*/

//draw dphi projection{{{
		cdphi1->cd();
	//	hDeltaPhi1->Fit(v2Fn,"rqm");
		hDeltaPhi1->Draw("pe");
	//	v2s = v2Fn->GetParameter(1);
	//	v2Errs = v2Fn->GetParError(1);
	//	lt1->DrawLatex(0.4,0.4,Form("v_{2} : %0.3f #+- %0.4f",v2s,v2Errs));
		lt1->DrawLatex(0.4,0.35, "|#Delta#eta^{trk}| > 1.0");
		cdphi1->SaveAs(Form("CorrDist/CorrDistdphi/plot_corr1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));

		cdphi2->cd();
	//	hDeltaPhi2->Fit(v2Fn,"rqm");
		hDeltaPhi2->Draw("pe");
	//	v2s = v2Fn->GetParameter(1);
	//	v2Errs = v2Fn->GetParError(1);
	//	lt1->DrawLatex(0.4,0.4,Form("v_{2} : %0.3f #+- %0.4f",v2s,v2Errs));
		lt1->DrawLatex(0.4,0.35, "|#Delta#eta^{trk}| > 2.0");
		cdphi2->SaveAs(Form("CorrDist/CorrDistdphi/plot_corr2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass));
//}}}

//Store dphi projection{{{
		TFile* fout = new TFile(Form("CorrDist/CorrFiles/dphi_distribution_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%dmbin_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin, Nphibin, version.Data(), nmbin, imass), "RECREATE");
		fout->cd();
		hDeltaPhi1->Write();
		hDeltaPhi2->Write();
		fout->Close();
//}}}

		//hMass->SetBinContent(imass+1,v2s);
		//hMass->SetBinError(imass+1,v2Errs);
	}
/*
	gStyle->SetOptStat(0000);
	cmass->cd();
	hMass->SetMaximum(0.6);
	hMass->SetMinimum(-0.2);
	hMass->Draw("E");
	lt1->DrawLatex(0.16, 0.90, "CMS Preliminary");
	lt1->DrawLatex(0.64, 0.90, Form("%d < p_{T}^{trk} < %d GeV/c", (int)TrkptMin, (int)TrkptMax));
	lt1->DrawLatex(0.64, 0.83, "|#Delta#eta^{trk}| > 2.0");
	lt1->DrawLatex(0.16, 0.83, "p_{T}^{#mu} > 4.0 GeV/c");
	cmass->SaveAs(Form("plot_mass_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%dmbin.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), nmbin));
*/
}
