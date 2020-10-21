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

void RatioNProjection_jet(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const TStiring trkptversion = "v1", const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Bool_t isTnP = true, const TString MupT = "4", const Bool_t isBkg = true)
{ 
	SetStyle();

//Define names{{{
	TString Direction[2] = {"Pbp", "pPb"};
	const Int_t Naway = 4;
	TString Away[Naway] = {"2", "1p5", "1", "short"};
	TString SysDir;
	if( isAccRW && isEffRW && isTnP ) SysDir = "Nominal";
	else if( !isAccRW && isEffRW && isTnP) SysDir = "SysAcc";
	else if( isAccRW && !isEffRW && isTnP) SysDir = "SysEff";
	else if( isAccRW && isEffRW && !isTnP) SysDir = "SysTnP";
	else
	{
		cout << "There is no such option" << endl;
		return;
	}
	TString PorB;
	if(isBkg) PorB = "bkg";
	else PorB = "peak";
//}}}

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fileDIR = mainDIR + Form("/CorrDist/CorrFiles/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());

	void * dirfile = gSystem->OpenDirectory(fileDIR.Data());
	if(dirfile) gSystem->FreeDirectory(dirfile);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);
//}}}

	TFile *samePbp[2];
	TFile *mixPbp[2];

//Define histogram{{{
	TH2D *hSamePbp_fine[Naway][2];
	TH2D *hMixPbp_fine[Naway][2];
	TH1D *hSameDeltaPhi_fine[Naway];
	TH1D *hMixDeltaPhi_fine[Naway];

	TH2D *hSamePbp_coarse[Naway][2];
	TH2D *hMixPbp_coarse[Naway][2];
	TH1D *hSameDeltaPhi_coarse[Naway];
	TH1D *hMixDeltaPhi_coarse[Naway];
//}}}

	TFile* fout = new TFile(Form("CorrDist/CorrFiles/%s/MupT%s/%s/dphi_distribution_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_Acc%o_Eff%o_TnP%o_MupT%s_%s.root", version.Data(), MupT.Data(), SysDir.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), isAccRW, isEffRW, isTnP, MupT.Data(), PorB.Data()), "RECREATE");

//Get files{{{
	for(Int_t ipPb = 0; ipPb < 2; ipPb++)
	{
		samePbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s/deta-dphi_Reco_%s_distribution_same_Data_Acc%o_Eff%o_TnP%o_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data(), Direction[ipPb].Data(), isAccRW, isEffRW, isTnP, PorB.Data()), "READ");
		mixPbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s_trk%s/deta-dphi_Reco_%s_distribution_mix_Data_Acc%o_Eff%o_TnP%o_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), trkptversion.Data(), Direction[ipPb].Data(), isAccRW, isEffRW, isTnP, PorB.Data()), "READ");
	}
//}}}

	for(Int_t iaway = 0; iaway < Naway; iaway++)
	{
		for(Int_t ipPb = 0; ipPb < 2; ipPb++)
		{
//get plot{{{
			hSamePbp_fine[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sReco%d_1", Direction[ipPb].Data(), iaway+2));
			hSamePbp_coarse[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sReco%d_2", Direction[ipPb].Data(), iaway+2));
			hMixPbp_fine[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sReco%d_1", Direction[ipPb].Data(), iaway+2));
			hMixPbp_coarse[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sReco%d_2", Direction[ipPb].Data(), iaway+2));
			hSamePbp_fine[iaway][ipPb]->Sumw2();
			hSamePbp_coarse[iaway][ipPb]->Sumw2();
			hMixPbp_fine[iaway][ipPb]->Sumw2();
			hMixPbp_coarse[iaway][ipPb]->Sumw2();
//}}}
		}

//merge direction{{{
		hSamePbp_fine[iaway][0]->Add(hSamePbp_fine[iaway][1]);
		hSamePbp_coarse[iaway][0]->Add(hSamePbp_coarse[iaway][1]);
		hMixPbp_fine[iaway][0]->Add(hMixPbp_fine[iaway][1]);
		hMixPbp_coarse[iaway][0]->Add(hMixPbp_coarse[iaway][1]);
//}}}
	}

	//self normalize mixed event
	Double_t NormFactor_fine = hMixPbp_fine[3][0]->GetBinContent(hMixPbp_fine[3][0]->FindBin(0, 0));
	Double_t NormFactor_coarse = hMixPbp_coarse[3][0]->GetBinContent(hMixPbp_coarse[3][0]->FindBin(0, 0));

	for(Int_t iaway = 0; iaway < Naway; iaway++)
	{
		hMixPbp_fine[iaway][0]->Scale(1./NormFactor_fine);
		hMixPbp_coarse[iaway][0]->Scale(1./NormFactor_coarse);

//projection{{{
		hSameDeltaPhi_fine[iaway] = (TH1D*)hSamePbp_fine[iaway][0]->ProjectionY();
		hSameDeltaPhi_coarse[iaway] = (TH1D*)hSamePbp_coarse[iaway][0]->ProjectionY();
		hMixDeltaPhi_fine[iaway] = (TH1D*)hMixPbp_fine[iaway][0]->ProjectionY();
		hMixDeltaPhi_coarse[iaway] = (TH1D*)hMixPbp_coarse[iaway][0]->ProjectionY();

		hSameDeltaPhi_fine[iaway]->SetName(Form("hSameRecoDeltaPhi%s_fine", Away[iaway].Data()));
		hSameDeltaPhi_coarse[iaway]->SetName(Form("hSameRecoDeltaPhi%s_coarse", Away[iaway].Data()));
		hMixDeltaPhi_fine[iaway]->SetName(Form("hMixRecoDeltaPhi%s_fine", Away[iaway].Data()));
		hMixDeltaPhi_coarse[iaway]->SetName(Form("hMixRecoDeltaPhi%s_coarse", Away[iaway].Data()));

		FormTH1Marker(hSameDeltaPhi_fine[iaway], 0, 0, 1.4);
		FormTH1Marker(hSameDeltaPhi_coarse[iaway], 0, 0, 1.4);
		FormTH1Marker(hMixDeltaPhi_fine[iaway], 0, 0, 1.4);
		FormTH1Marker(hMixDeltaPhi_coarse[iaway], 0, 0, 1.4);
//}}}

//Get ratio{{{
		TH1D* hRatioDeltaPhi_fine = (TH1D*) hSameDeltaPhi_fine[iaway]->Clone(Form("hRatioRecoDeltaPhi%s_fine", Away[iaway].Data()));
		TH1D* hRatioDeltaPhi_coarse = (TH1D*) hSameDeltaPhi_coarse[iaway]->Clone(Form("hRatioRecoDeltaPhi%s_coarse", Away[iaway].Data()));

		hRatioDeltaPhi_fine->Divide(hMixDeltaPhi_fine[iaway]);
		hRatioDeltaPhi_coarse->Divide(hMixDeltaPhi_coarse[iaway]);
//}}}

//Store dphi projection{{{
		fout->cd();
		hSameDeltaPhi_fine[iaway]->Write();
		hSameDeltaPhi_coarse[iaway]->Write();
		hMixDeltaPhi_fine[iaway]->Write();
		hMixDeltaPhi_coarse[iaway]->Write();
		hRatioDeltaPhi_fine->Write();
		hRatioDeltaPhi_coarse->Write();
//}}}
	}
	fout->Close();
}
