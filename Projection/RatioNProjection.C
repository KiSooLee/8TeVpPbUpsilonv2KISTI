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

void RatioNProjection(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1", TString MupT = "4")
{ 

	SetStyle();
	gStyle->SetOptFit(0);

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fileDIR = mainDIR + Form("/CorrDist/CorrFiles/", version.Data());

	void * dirfile = gSystem->OpenDirectory(fileDIR.Data());
	if(dirfile) gSystem->FreeDirectory(dirfile);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);
//}}}

	TFile *sigPbp; TFile *sigpPb;
	TFile *bkgPbp; TFile *bkgpPb;

//Define histogram{{{

//fine{{{

//2D plot{{{
	TH2D *hSig_cut1Pbp_fine;
	TH2D *hSig_cut1pPb_fine;
	TH2D *hBkg_cut1Pbp_fine;
	TH2D *hBkg_cut1pPb_fine;
	TH2D *hSig_cut1p5Pbp_fine;
	TH2D *hSig_cut1p5pPb_fine;
	TH2D *hBkg_cut1p5Pbp_fine;
	TH2D *hBkg_cut1p5pPb_fine;
	TH2D *hSig_cut2Pbp_fine;
	TH2D *hSig_cut2pPb_fine;
	TH2D *hBkg_cut2Pbp_fine;
	TH2D *hBkg_cut2pPb_fine;
//}}}

//1D projection{{{
	TH1D *hSigDeltaPhi1_fine;
	TH1D *hBkgDeltaPhi1_fine;
	TH1D *hSigDeltaPhi1p5_fine;
	TH1D *hBkgDeltaPhi1p5_fine;
	TH1D *hSigDeltaPhi2_fine;
	TH1D *hBkgDeltaPhi2_fine;
//}}}

//}}}

//coarse{{{

//2D plot{{{
	TH2D *hSig_cut1Pbp_coarse;
	TH2D *hSig_cut1pPb_coarse;
	TH2D *hBkg_cut1Pbp_coarse;
	TH2D *hBkg_cut1pPb_coarse;
	TH2D *hSig_cut1p5Pbp_coarse;
	TH2D *hSig_cut1p5pPb_coarse;
	TH2D *hBkg_cut1p5Pbp_coarse;
	TH2D *hBkg_cut1p5pPb_coarse;
	TH2D *hSig_cut2Pbp_coarse;
	TH2D *hSig_cut2pPb_coarse;
	TH2D *hBkg_cut2Pbp_coarse;
	TH2D *hBkg_cut2pPb_coarse;
//}}}

//1D projection{{{
	TH1D *hSigDeltaPhi1_coarse;
	TH1D *hBkgDeltaPhi1_coarse;
	TH1D *hSigDeltaPhi1p5_coarse;
	TH1D *hBkgDeltaPhi1p5_coarse;
	TH1D *hSigDeltaPhi2_coarse;
	TH1D *hBkgDeltaPhi2_coarse;
//}}}

//}}}

//}}}

	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->SetNDC();

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{

//Get files{{{
		sigPbp = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/deta-dphi_Pbp_distribution_sig_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), imass), "READ");
		sigpPb = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/deta-dphi_pPb_distribution_sig_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), imass), "READ");
		bkgPbp = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/deta-dphi_Pbp_distribution_bkg_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), imass), "READ");
		bkgpPb = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/deta-dphi_pPb_distribution_bkg_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), imass), "READ");
//}}}

//Get |deta| > 2 range plot{{{

//get plot{{{
		hSig_cut2Pbp_fine = (TH2D*)sigPbp->Get("hSigPbp2_1"); hSig_cut2Pbp_fine->Sumw2();
		hSig_cut2Pbp_coarse = (TH2D*)sigPbp->Get("hSigPbp2_2"); hSig_cut2Pbp_coarse->Sumw2();
		hSig_cut2pPb_fine = (TH2D*)sigpPb->Get("hSigpPb2_1"); hSig_cut2pPb_fine->Sumw2();
		hSig_cut2pPb_coarse = (TH2D*)sigpPb->Get("hSigpPb2_2"); hSig_cut2pPb_coarse->Sumw2();
		hBkg_cut2Pbp_fine = (TH2D*)bkgPbp->Get("hBkgPbp2_1"); hBkg_cut2Pbp_fine->Sumw2();
		hBkg_cut2Pbp_coarse = (TH2D*)bkgPbp->Get("hBkgPbp2_2"); hBkg_cut2Pbp_coarse->Sumw2();
		hBkg_cut2pPb_fine = (TH2D*)bkgpPb->Get("hBkgpPb2_1"); hBkg_cut2pPb_fine->Sumw2();
		hBkg_cut2pPb_coarse = (TH2D*)bkgpPb->Get("hBkgpPb2_2"); hBkg_cut2pPb_coarse->Sumw2();
		hSig_cut2Pbp_fine->Add(hSig_cut2pPb_fine);
		hSig_cut2Pbp_coarse->Add(hSig_cut2pPb_coarse);
		hBkg_cut2Pbp_fine->Add(hBkg_cut2pPb_fine);
		hBkg_cut2Pbp_coarse->Add(hBkg_cut2pPb_coarse);
//}}}

//projection{{{
		hSigDeltaPhi2_fine = (TH1D*)hSig_cut2Pbp_fine->ProjectionY();
		hBkgDeltaPhi2_fine = (TH1D*)hBkg_cut2Pbp_fine->ProjectionY();
		hSigDeltaPhi2_coarse = (TH1D*)hSig_cut2Pbp_coarse->ProjectionY();
		hBkgDeltaPhi2_coarse = (TH1D*)hBkg_cut2Pbp_coarse->ProjectionY();

		hSigDeltaPhi2_fine->SetName("hSigDeltaPhi2_fine");
		hBkgDeltaPhi2_fine->SetName("hBkgDeltaPhi2_fine");
		hSigDeltaPhi2_coarse->SetName("hSigDeltaPhi2_coarse");
		hBkgDeltaPhi2_coarse->SetName("hBkgDeltaPhi2_coarse");

		FormTH1Marker(hSigDeltaPhi2_fine, 0, 0, 1.4);
		FormTH1Marker(hBkgDeltaPhi2_fine, 0, 0, 1.4);
		FormTH1Marker(hSigDeltaPhi2_coarse, 0, 0, 1.4);
		FormTH1Marker(hBkgDeltaPhi2_coarse, 0, 0, 1.4);

		TH1D* hRatioDeltaPhi2_fine = (TH1D*) hSigDeltaPhi2_fine->Clone("hRatioDeltaPhi2_fine");
		TH1D* hRatioDeltaPhi2_coarse = (TH1D*) hSigDeltaPhi2_coarse->Clone("hRatioDeltaPhi2_coarse");

		hRatioDeltaPhi2_fine->Divide(hBkgDeltaPhi2_fine);
		hRatioDeltaPhi2_coarse->Divide(hBkgDeltaPhi2_coarse);
//}}}

//}}}

//Get |deta| > 1.5 range plot{{{

//get plot{{{
		hSig_cut1p5Pbp_fine = (TH2D*)sigPbp->Get("hSigPbp3_1"); hSig_cut1p5Pbp_fine->Sumw2();
		hSig_cut1p5Pbp_coarse = (TH2D*)sigPbp->Get("hSigPbp3_2"); hSig_cut1p5Pbp_coarse->Sumw2();
		hSig_cut1p5pPb_fine = (TH2D*)sigpPb->Get("hSigpPb3_1"); hSig_cut1p5pPb_fine->Sumw2();
		hSig_cut1p5pPb_coarse = (TH2D*)sigpPb->Get("hSigpPb3_2"); hSig_cut1p5pPb_coarse->Sumw2();
		hBkg_cut1p5Pbp_fine = (TH2D*)bkgPbp->Get("hBkgPbp3_1"); hBkg_cut1p5Pbp_fine->Sumw2();
		hBkg_cut1p5Pbp_coarse = (TH2D*)bkgPbp->Get("hBkgPbp3_2"); hBkg_cut1p5Pbp_coarse->Sumw2();
		hBkg_cut1p5pPb_fine = (TH2D*)bkgpPb->Get("hBkgpPb3_1"); hBkg_cut1p5pPb_fine->Sumw2();
		hBkg_cut1p5pPb_coarse = (TH2D*)bkgpPb->Get("hBkgpPb3_2"); hBkg_cut1p5pPb_coarse->Sumw2();
		hSig_cut1p5Pbp_fine->Add(hSig_cut1p5pPb_fine);
		hSig_cut1p5Pbp_coarse->Add(hSig_cut1p5pPb_coarse);
		hBkg_cut1p5Pbp_fine->Add(hBkg_cut1p5pPb_fine);
		hBkg_cut1p5Pbp_coarse->Add(hBkg_cut1p5pPb_coarse);
//}}}

//projection{{{
		hSigDeltaPhi1p5_fine = (TH1D*)hSig_cut1p5Pbp_fine->ProjectionY();
		hBkgDeltaPhi1p5_fine = (TH1D*)hBkg_cut1p5Pbp_fine->ProjectionY();
		hSigDeltaPhi1p5_coarse = (TH1D*)hSig_cut1p5Pbp_coarse->ProjectionY();
		hBkgDeltaPhi1p5_coarse = (TH1D*)hBkg_cut1p5Pbp_coarse->ProjectionY();

		FormTH1Marker(hSigDeltaPhi1p5_fine, 0, 0, 1.4);
		FormTH1Marker(hBkgDeltaPhi1p5_fine, 0, 0, 1.4);
		FormTH1Marker(hSigDeltaPhi1p5_coarse, 0, 0, 1.4);
		FormTH1Marker(hBkgDeltaPhi1p5_coarse, 0, 0, 1.4);

		hSigDeltaPhi1p5_fine->SetName("hSigDeltaPhi1p5_fine");
		hBkgDeltaPhi1p5_fine->SetName("hBkgDeltaPhi1p5_fine");
		hSigDeltaPhi1p5_coarse->SetName("hSigDeltaPhi1p5_coarse");
		hBkgDeltaPhi1p5_coarse->SetName("hBkgDeltaPhi1p5_coarse");

		TH1D* hRatioDeltaPhi1p5_fine = (TH1D*) hSigDeltaPhi1p5_fine->Clone("hRatioDeltaPhi1p5_fine");
		TH1D* hRatioDeltaPhi1p5_coarse = (TH1D*) hSigDeltaPhi1p5_coarse->Clone("hRatioDeltaPhi1p5_coarse");

		hRatioDeltaPhi1p5_fine->Divide(hBkgDeltaPhi1p5_fine);
		hRatioDeltaPhi1p5_coarse->Divide(hBkgDeltaPhi1p5_coarse);
//}}}

//}}}

//Get |deta| > 1 range plot{{{

//get plot{{{
		hSig_cut1Pbp_fine = (TH2D*)sigPbp->Get("hSigPbp4_1"); hSig_cut1Pbp_fine->Sumw2();
		hSig_cut1Pbp_coarse = (TH2D*)sigPbp->Get("hSigPbp4_2"); hSig_cut1Pbp_coarse->Sumw2();
		hSig_cut1pPb_fine = (TH2D*)sigpPb->Get("hSigpPb4_1"); hSig_cut1pPb_fine->Sumw2();
		hSig_cut1pPb_coarse = (TH2D*)sigpPb->Get("hSigpPb4_2"); hSig_cut1pPb_coarse->Sumw2();
		hBkg_cut1Pbp_fine = (TH2D*)bkgPbp->Get("hBkgPbp4_1"); hBkg_cut1Pbp_fine->Sumw2();
		hBkg_cut1Pbp_coarse = (TH2D*)bkgPbp->Get("hBkgPbp4_2"); hBkg_cut1Pbp_coarse->Sumw2();
		hBkg_cut1pPb_fine = (TH2D*)bkgpPb->Get("hBkgpPb4_1"); hBkg_cut1pPb_fine->Sumw2();
		hBkg_cut1pPb_coarse = (TH2D*)bkgpPb->Get("hBkgpPb4_2"); hBkg_cut1pPb_coarse->Sumw2();
		hSig_cut1Pbp_fine->Add(hSig_cut1pPb_fine);
		hSig_cut1Pbp_coarse->Add(hSig_cut1pPb_coarse);
		hBkg_cut1Pbp_fine->Add(hBkg_cut1pPb_fine);
		hBkg_cut1Pbp_coarse->Add(hBkg_cut1pPb_coarse);
//}}}

//projection{{{
		hSigDeltaPhi1_fine = (TH1D*)hSig_cut1Pbp_fine->ProjectionY();
		hBkgDeltaPhi1_fine = (TH1D*)hBkg_cut1Pbp_fine->ProjectionY();
		hSigDeltaPhi1_coarse = (TH1D*)hSig_cut1Pbp_coarse->ProjectionY();
		hBkgDeltaPhi1_coarse = (TH1D*)hBkg_cut1Pbp_coarse->ProjectionY();

		FormTH1Marker(hSigDeltaPhi1_fine, 0, 0, 1.4);
		FormTH1Marker(hBkgDeltaPhi1_fine, 0, 0, 1.4);
		FormTH1Marker(hSigDeltaPhi1_coarse, 0, 0, 1.4);
		FormTH1Marker(hBkgDeltaPhi1_coarse, 0, 0, 1.4);

		hSigDeltaPhi1_fine->SetName("hSigDeltaPhi1_fine");
		hBkgDeltaPhi1_fine->SetName("hBkgDeltaPhi1_fine");
		hSigDeltaPhi1_coarse->SetName("hSigDeltaPhi1_coarse");
		hBkgDeltaPhi1_coarse->SetName("hBkgDeltaPhi1_coarse");

		TH1D* hRatioDeltaPhi1_fine = (TH1D*) hSigDeltaPhi1_fine->Clone("hRatioDeltaPhi1_fine");
		TH1D* hRatioDeltaPhi1_coarse = (TH1D*) hSigDeltaPhi1_coarse->Clone("hRatioDeltaPhi1_coarse");

		hRatioDeltaPhi1_fine->Divide(hBkgDeltaPhi1_fine);
		hRatioDeltaPhi1_coarse->Divide(hBkgDeltaPhi1_coarse);
//}}}

//}}}

//Store dphi projection{{{
		TFile* fout = new TFile(Form("CorrDist/CorrFiles/dphi_distribution_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), imass), "RECREATE");
		fout->cd();
		hSigDeltaPhi1_fine->Write();
		hSigDeltaPhi1_coarse->Write();
		hSigDeltaPhi1p5_fine->Write();
		hSigDeltaPhi1p5_coarse->Write();
		hSigDeltaPhi2_fine->Write();
		hSigDeltaPhi2_coarse->Write();
		hBkgDeltaPhi1_fine->Write();
		hBkgDeltaPhi1_coarse->Write();
		hBkgDeltaPhi1p5_fine->Write();
		hBkgDeltaPhi1p5_coarse->Write();
		hBkgDeltaPhi2_fine->Write();
		hBkgDeltaPhi2_coarse->Write();
		hRatioDeltaPhi1_fine->Write();
		hRatioDeltaPhi1_coarse->Write();
		hRatioDeltaPhi1p5_fine->Write();
		hRatioDeltaPhi1p5_coarse->Write();
		hRatioDeltaPhi2_fine->Write();
		hRatioDeltaPhi2_coarse->Write();
		fout->Close();
//}}}

	}
}
