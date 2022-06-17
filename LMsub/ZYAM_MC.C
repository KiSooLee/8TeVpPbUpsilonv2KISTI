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

void ZYAM_MC(const Bool_t isGen = true, const Int_t multMin = 110, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v19", const TString MupT = "3p5", const Bool_t Fine = true)
{
	SetStyle();

//Define names{{{
	TString Band[2] = {"short", "2"};
	TString BandName[2] = {"short", "long"};
	TString ForC;
	if(Fine) ForC = "fine";
	else ForC = "coarse";
	TString RorG;
	if (isGen) RorG = "Gen";
	else RorG = "Reco";
//}}}

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fileDIR = mainDIR + Form("/File");
	TString plotDIR = mainDIR + Form("/Plots/%s", version.Data());

	void * dirf = gSystem->OpenDirectory(fileDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);

	void * dirp = gSystem->OpenDirectory(plotDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(plotDIR.Data(), kTRUE);
//}}}

//fitting range{{{
//{{peak_short, peak_long}}

//70~300 new pt bin v86 GEN{{{
/*
	//9~10 GeV fine
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2] = {0.6, -0.5};
	const Double_t fitmax[2] = {2.3, 1.0};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2] = {0.6, -1.0};
	const Double_t fitmax[2] = {2.3, 1.0};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2] = {0.5, 0.6};
	const Double_t fitmax[2] = {1.4, 2.6};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2] = {0.7, 1.3};
	const Double_t fitmax[2] = {1.5, 2.0};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2] = {0.8, 0.2};
	const Double_t fitmax[2] = {1.8, 1.1};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2] = {0.7, 1.3};
	const Double_t fitmax[2] = {1.5, 2.0};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2] = {0.5, 1.0};
	const Double_t fitmax[2] = {2.0, 2.0};
*/
//}}}

//0~50 new pt bin v87 GEN{{{
/*
	//10~12 GeV fine
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0}
*/

	//12~15 GeV coarse
	const Double_t fitmin[2] = {0.5, 0.5};
	const Double_t fitmax[2] = {1.8, 1.4};

/*
	//15~20 GeV fine
	const Double_t fitmin[2] = {0.7, 1.3};
	const Double_t fitmax[2] = {1.5, 2.0};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2] = {0.6, 0.5};
	const Double_t fitmax[2] = {1.6, 2.2};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2] = {0.7, 1.3};
	const Double_t fitmax[2] = {1.5, 2.0};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2] = {0.6, 0.2};
	const Double_t fitmax[2] = {2.6, 1.2};
*/
//}}}

//70~300 new pt bin v86 RECO{{{
/*
	//9~10 GeV fine
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2] = {0.6, -0.5};
	const Double_t fitmax[2] = {2.3, 1.0};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2] = {0.6, -1.0};
	const Double_t fitmax[2] = {2.3, 1.0};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2] = {0.6, 0.6};
	const Double_t fitmax[2] = {2.6, 2.6};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2] = {0.7, 1.3};
	const Double_t fitmax[2] = {1.5, 2.0};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2] = {0.3, 0.5};
	const Double_t fitmax[2] = {2.2, 2.2};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2] = {0.7, 1.3};
	const Double_t fitmax[2] = {1.5, 2.0};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2] = {0.5, 1.0};
	const Double_t fitmax[2] = {2.4, 2.0};
*/
//}}}

//0~50 new pt bin v87 RECO{{{
/*
	//10~12 GeV fine
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2] = {0.5, -1.0};
	const Double_t fitmax[2] = {2.2, 1.0}
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2] = {0.5, 0.5};
	const Double_t fitmax[2] = {1.4, 1.4};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2] = {0.7, 1.3};
	const Double_t fitmax[2] = {1.5, 2.0};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2] = {1.2, 0.5};
	const Double_t fitmax[2] = {1.8, 2.2};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2] = {0.7, 1.3};
	const Double_t fitmax[2] = {1.5, 2.0};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2] = {1.0, 0.2};
	const Double_t fitmax[2] = {2.0, 1.2};
*/
//}}}

//}}}

	Double_t JYield[2];
	Double_t JYieldE2[2];

//Define histogram{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 300);
	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 300);
	TCanvas* c3 = new TCanvas("c3", "", 0, 0, 600, 300);
	c1->Divide(2, 1);
	c2->Divide(2, 1);
	c3->Divide(2, 1);
	TH1D* h1[2];
	TH1D* h1_ZYAM[2];
	TH1D* hJYield[2];

	for(Int_t isl = 0; isl < 2; isl++)
	{
		hJYield[isl] = new TH1D(Form("hJYield_%s", BandName[isl].Data()), "", 1, 0, 1);
	}
//}}}

	TFile* fin = new TFile(Form("../Projection/CorrDist/CorrFiles/%s/MupT%s/Nominal/dphi_distribution_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_MupT%s.root", version.Data(), MupT.Data(), RorG.Data(),  multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data()), "READ");

	for(Int_t isl = 0; isl < 2; isl++)//short & long range loop
	{
		h1[isl] = (TH1D*) fin->Get(Form("hRatio%sDeltaPhi%s_%s", RorG.Data(), Band[isl].Data(), ForC.Data()));
		h1[isl]->SetName(Form("h_%s", BandName[isl].Data()));
		h1[isl]->GetYaxis()->SetTitle("#frac{1}{N_{trig}}#frac{dN^{pair}}{d#Delta#phi}");
		h1[isl]->GetYaxis()->SetTitleSize(0.045);
		h1_ZYAM[isl] = (TH1D*) h1[isl]->Clone(Form("hZYAM_%s", BandName[isl].Data()));
		h1_ZYAM[isl]->Reset();
		h1_ZYAM[isl]->GetYaxis()->SetTitle("#frac{1}{N_{trig}}#frac{dN^{pair}}{d#Delta#phi}-C_{ZYAM}");
		h1_ZYAM[isl]->GetYaxis()->SetTitleSize(0.045);
		TF1* f1 = new TF1(Form("f_%d", isl), "[0]*x*x+[1]*x+[2]", fitmin[isl], fitmax[isl]);
		f1->SetLineColor(kRed);
		f1->SetParameter(0, 10);

		c1->cd(isl+1);
		h1[isl]->SetMaximum(h1[isl]->GetMaximum()*1.05);
		h1[isl]->Draw();
		h1[isl]->Fit(Form("f_%d", isl), "ML", "", fitmin[isl], fitmax[isl]);

//event info{{{
		TLatex* lt1 = new TLatex();
		FormLatex(lt1, 12, 0.04);
		lt1->DrawLatex(0.16, 0.83, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
		if(isl == 0) lt1->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| < 1"));
		else lt1->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| > 2"));
		lt1->DrawLatex(0.16, 0.73, Form("%d #leq p^{#Upsilon}_{T} < %d", (int)ptMin, (int)ptMax));
//}}}

		Double_t Min = f1->GetMinimum(fitmin[isl], fitmax[isl]);

		for(Int_t ibin = 0; ibin < h1[isl]->GetNbinsX(); ibin++)
		{
			Double_t vals = h1[isl]->GetBinContent(ibin+1);
			Double_t Evals = h1[isl]->GetBinError(ibin+1);
			h1_ZYAM[isl]->SetBinContent(ibin+1, vals-Min);
			h1_ZYAM[isl]->SetBinError(ibin+1, Evals);

			if( (Fine && (ibin >= 1 && ibin < 14) ) || (!Fine && (ibin >= 1 && ibin < 7)) )
			{
				if(h1_ZYAM[isl]->GetBinContent(ibin+1) > 0) JYield[isl] += h1_ZYAM[isl]->GetBinContent(ibin+1);
				else JYield[isl] += 0;
				JYieldE2[isl] += h1_ZYAM[isl]->GetBinError(ibin+1)*h1_ZYAM[isl]->GetBinError(ibin+1);
			}
		}
		c2->cd(isl+1);
		h1_ZYAM[isl]->SetMaximum(h1_ZYAM[isl]->GetMaximum()*2);
		h1_ZYAM[isl]->Draw();
		SetLine(1, -1.45, 0, 4.45, 0, 0, 3);

		TLatex* lt2 = new TLatex();
		FormLatex(lt2, 12, 0.04);
		lt2->DrawLatex(0.16, 0.83, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
		if(isl == 0) lt2->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| < 1"));
		else lt2->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| > 2"));
		lt2->DrawLatex(0.16, 0.73, Form("%d #leq p^{#Upsilon}_{T} < %d", (int)ptMin, (int)ptMax));

		c3->cd(isl+1);
		hJYield[isl]->SetBinContent(1, JYield[isl]);
		hJYield[isl]->SetBinError(1, TMath::Sqrt(JYieldE2[isl]));
		hJYield[isl]->SetMinimum(0);
		hJYield[isl]->Draw("pe");

		TLatex* lt3 = new TLatex();
		FormLatex(lt3, 12, 0.04);
		lt3->DrawLatex(0.55, 0.40, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
		if(isl == 0) lt3->DrawLatex(0.55, 0.35, Form("|#Delta#eta| < 1"));
		else lt3->DrawLatex(0.55, 0.35, Form("|#Delta#eta| > 2"));
		lt3->DrawLatex(0.55, 0.30, Form("%d #leq p^{#Upsilon}_{T} < %d", (int)ptMin, (int)ptMax));
		lt3->DrawLatex(0.55, 0.20, Form("%.2f #pm  %.2f", JYield[isl], TMath::Sqrt(JYieldE2[isl])));
	}

	c1->SaveAs(Form("Plots/%s/Before_ZYAM_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_%s.pdf", version.Data(), RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), ForC.Data()));
	c2->SaveAs(Form("Plots/%s/After_ZYAM_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_%s.pdf", version.Data(), RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), ForC.Data()));
	c3->SaveAs(Form("Plots/%s/JetYield_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_%s.pdf", version.Data(), RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), ForC.Data()));

	TFile* fout;
	fout = new TFile(Form("File/Sideband_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_%s.root", RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), ForC.Data()), "RECREATE");
	fout->cd();
	for(Int_t isl = 0; isl < 2; isl++)
	{
		h1[isl]->Write();
		h1_ZYAM[isl]->Write();
		hJYield[isl]->Write();
	}
	fout->Close();
}
