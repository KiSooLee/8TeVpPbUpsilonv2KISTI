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

void RatioNProjection(const Bool_t isMC = false, const Bool_t isTrk = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TString MupT = "4")
{ 
	SetStyle();
	gStyle->SetOptFit(0);

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fileDIR = mainDIR + Form("/CorrDist/CorrFiles/%s/MupT%s", version.Data(), MupT.Data());

	void * dirfile = gSystem->OpenDirectory(fileDIR.Data());
	if(dirfile) gSystem->FreeDirectory(dirfile);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);
//}}}

	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString Direction[2] = {"Pbp", "pPb"};
	TString Away[3] = {"2", "1p5", "1"};
	TString Trk;
	if(isTrk) Trk = "trk_";
	else Trk = "";

	TFile *samePbp[2];
	TFile *mixPbp[2];

//Define histogram{{{

//fine{{{
	TH2D *hSameReco_Pbp_fine[3][2];
	TH2D *hSameGen_Pbp_fine[3][2];
	TH2D *hMixReco_Pbp_fine[3][2];
	TH2D *hMixGen_Pbp_fine[3][2];

	TH1D *hSameRecoDeltaPhi_fine[3];
	TH1D *hSameGenDeltaPhi_fine[3];
	TH1D *hMixRecoDeltaPhi_fine[3];
	TH1D *hMixGenDeltaPhi_fine[3];
//}}}

//coarse{{{
	TH2D *hSameReco_Pbp_coarse[3][2];
	TH2D *hSameGen_Pbp_coarse[3][2];
	TH2D *hMixReco_Pbp_coarse[3][2];
	TH2D *hMixGen_Pbp_coarse[3][2];

	TH1D *hSameRecoDeltaPhi_coarse[3];
	TH1D *hSameGenDeltaPhi_coarse[3];
	TH1D *hMixRecoDeltaPhi_coarse[3];
	TH1D *hMixGenDeltaPhi_coarse[3];
//}}}

//}}}

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{
		TFile* fout = new TFile(Form("CorrDist/CorrFiles/%s/MupT%s/%sdphi_distribution_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_%d.root", version.Data(), MupT.Data(), Trk.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), imass), "RECREATE");

//Get files{{{
		for(Int_t ipPb = 0; ipPb < 2; ipPb++)
		{
			samePbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/%sdeta-dphi_%s_distribution_same_%s_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Trk.Data(), Direction[ipPb].Data(), MorD.Data(), imass), "READ");
			mixPbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/%sdeta-dphi_%s_distribution_mix_%s_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Trk.Data(), Direction[ipPb].Data(), MorD.Data(), imass), "READ");
		}
//}}}

		for(Int_t iaway = 0; iaway < 3; iaway++)
		{
			for(Int_t ipPb = 0; ipPb < 2; ipPb++)
			{
//get plot{{{
				if(isMC)
				{
					hSameGen_Pbp_fine[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sGen%d_1", Direction[ipPb].Data(), iaway+2));
					hSameGen_Pbp_coarse[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sGen%d_2", Direction[ipPb].Data(), iaway+2));
					hMixGen_Pbp_fine[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sGen%d_1", Direction[ipPb].Data(), iaway+2));
					hMixGen_Pbp_coarse[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sGen%d_2", Direction[ipPb].Data(), iaway+2));
					hSameGen_Pbp_fine[iaway][ipPb]->Sumw2();
					hSameGen_Pbp_coarse[iaway][ipPb]->Sumw2();
					hMixGen_Pbp_fine[iaway][ipPb]->Sumw2();
					hMixGen_Pbp_coarse[iaway][ipPb]->Sumw2();
				}
				hSameReco_Pbp_fine[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sReco%d_1", Direction[ipPb].Data(), iaway+2));
				hSameReco_Pbp_coarse[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sReco%d_2", Direction[ipPb].Data(), iaway+2));
				hMixReco_Pbp_fine[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sReco%d_1", Direction[ipPb].Data(), iaway+2));
				hMixReco_Pbp_coarse[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sReco%d_2", Direction[ipPb].Data(), iaway+2));
				hSameReco_Pbp_fine[iaway][ipPb]->Sumw2();
				hSameReco_Pbp_coarse[iaway][ipPb]->Sumw2();
				hMixReco_Pbp_fine[iaway][ipPb]->Sumw2();
				hMixReco_Pbp_coarse[iaway][ipPb]->Sumw2();
//}}}
			}

//merge direction{{{
			if(isMC)
			{
				hSameGen_Pbp_fine[iaway][0]->Add(hSameGen_Pbp_fine[iaway][1]);
				hSameGen_Pbp_coarse[iaway][0]->Add(hSameGen_Pbp_coarse[iaway][1]);
				hMixGen_Pbp_fine[iaway][0]->Add(hMixGen_Pbp_fine[iaway][1]);
				hMixGen_Pbp_coarse[iaway][0]->Add(hMixGen_Pbp_coarse[iaway][1]);
			}
			hSameReco_Pbp_fine[iaway][0]->Add(hSameReco_Pbp_fine[iaway][1]);
			hSameReco_Pbp_coarse[iaway][0]->Add(hSameReco_Pbp_coarse[iaway][1]);
			hMixReco_Pbp_fine[iaway][0]->Add(hMixReco_Pbp_fine[iaway][1]);
			hMixReco_Pbp_coarse[iaway][0]->Add(hMixReco_Pbp_coarse[iaway][1]);
//}}}

//projection{{{
			if(isMC)
			{
				hSameGenDeltaPhi_fine[iaway] = (TH1D*)hSameGen_Pbp_fine[iaway][0]->ProjectionY();
				hSameGenDeltaPhi_coarse[iaway] = (TH1D*)hSameGen_Pbp_coarse[iaway][0]->ProjectionY();
				hMixGenDeltaPhi_fine[iaway] = (TH1D*)hMixGen_Pbp_fine[iaway][0]->ProjectionY();
				hMixGenDeltaPhi_coarse[iaway] = (TH1D*)hMixGen_Pbp_coarse[iaway][0]->ProjectionY();

				hSameGenDeltaPhi_fine[iaway]->SetName(Form("hSameGenDeltaPhi%s_fine", Away[iaway].Data()));
				hSameGenDeltaPhi_coarse[iaway]->SetName(Form("hSameGenDeltaPhi%s_coarse", Away[iaway].Data()));
				hMixGenDeltaPhi_fine[iaway]->SetName(Form("hMixGenDeltaPhi%s_fine", Away[iaway].Data()));
				hMixGenDeltaPhi_coarse[iaway]->SetName(Form("hMixGenDeltaPhi%s_coarse", Away[iaway].Data()));

				FormTH1Marker(hSameGenDeltaPhi_fine[iaway], 0, 0, 1.4);
				FormTH1Marker(hSameGenDeltaPhi_coarse[iaway], 0, 0, 1.4);
				FormTH1Marker(hMixGenDeltaPhi_fine[iaway], 0, 0, 1.4);
				FormTH1Marker(hMixGenDeltaPhi_coarse[iaway], 0, 0, 1.4);
			}

			hSameRecoDeltaPhi_fine[iaway] = (TH1D*)hSameReco_Pbp_fine[iaway][0]->ProjectionY();
			hSameRecoDeltaPhi_coarse[iaway] = (TH1D*)hSameReco_Pbp_coarse[iaway][0]->ProjectionY();
			hMixRecoDeltaPhi_fine[iaway] = (TH1D*)hMixReco_Pbp_fine[iaway][0]->ProjectionY();
			hMixRecoDeltaPhi_coarse[iaway] = (TH1D*)hMixReco_Pbp_coarse[iaway][0]->ProjectionY();

			hSameRecoDeltaPhi_fine[iaway]->SetName(Form("hSameRecoDeltaPhi%s_fine", Away[iaway].Data()));
			hSameRecoDeltaPhi_coarse[iaway]->SetName(Form("hSameRecoDeltaPhi%s_coarse", Away[iaway].Data()));
			hMixRecoDeltaPhi_fine[iaway]->SetName(Form("hMixRecoDeltaPhi%s_fine", Away[iaway].Data()));
			hMixRecoDeltaPhi_coarse[iaway]->SetName(Form("hMixRecoDeltaPhi%s_coarse", Away[iaway].Data()));

			FormTH1Marker(hSameRecoDeltaPhi_fine[iaway], 0, 0, 1.4);
			FormTH1Marker(hSameRecoDeltaPhi_coarse[iaway], 0, 0, 1.4);
			FormTH1Marker(hMixRecoDeltaPhi_fine[iaway], 0, 0, 1.4);
			FormTH1Marker(hMixRecoDeltaPhi_coarse[iaway], 0, 0, 1.4);
//}}}

//Get ratio{{{
			TH1D* hRatioRecoDeltaPhi_fine = (TH1D*) hSameRecoDeltaPhi_fine[iaway]->Clone(Form("hRatioRecoDeltaPhi%s_fine", Away[iaway].Data()));
			TH1D* hRatioRecoDeltaPhi_coarse = (TH1D*) hSameRecoDeltaPhi_coarse[iaway]->Clone(Form("hRatioRecoDeltaPhi%s_coarse", Away[iaway].Data()));

			hRatioRecoDeltaPhi_fine->Divide(hMixRecoDeltaPhi_fine[iaway]);
			hRatioRecoDeltaPhi_coarse->Divide(hMixRecoDeltaPhi_coarse[iaway]);

			TH1D* hRatioGenDeltaPhi_fine;
			TH1D* hRatioGenDeltaPhi_coarse;
			if(isMC)
			{
				hRatioGenDeltaPhi_fine = (TH1D*) hSameGenDeltaPhi_fine[iaway]->Clone(Form("hRatioGenDeltaPhi%s_fine", Away[iaway].Data()));
				hRatioGenDeltaPhi_coarse = (TH1D*) hSameGenDeltaPhi_coarse[iaway]->Clone(Form("hRatioGenDeltaPhi%s_coarse", Away[iaway].Data()));

				hRatioGenDeltaPhi_fine->Divide(hMixGenDeltaPhi_fine[iaway]);
				hRatioGenDeltaPhi_coarse->Divide(hMixGenDeltaPhi_coarse[iaway]);
			}
//}}}

//Store dphi projection{{{
			fout->cd();
			if(isMC)
			{
				hSameGenDeltaPhi_fine[iaway]->Write();
				hSameGenDeltaPhi_coarse[iaway]->Write();
				hMixGenDeltaPhi_fine[iaway]->Write();
				hMixGenDeltaPhi_coarse[iaway]->Write();
				hRatioGenDeltaPhi_fine->Write();
				hRatioGenDeltaPhi_coarse->Write();
			}
			hSameRecoDeltaPhi_fine[iaway]->Write();
			hSameRecoDeltaPhi_coarse[iaway]->Write();
			hMixRecoDeltaPhi_fine[iaway]->Write();
			hMixRecoDeltaPhi_coarse[iaway]->Write();
			hRatioRecoDeltaPhi_fine->Write();
			hRatioRecoDeltaPhi_coarse->Write();
//}}}
		}
		fout->Close();
	}
}
