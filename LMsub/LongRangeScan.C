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

void LongRangeScan(const Int_t multMin = 0, const Int_t multMax = 10, const Double_t TrkptMin = 0, const Double_t TrkptMax = 3, const TString version = "v49", const TString MupT = "3p5")
{
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString plotDIR = mainDIR + Form("/Plots/");

	void * dirp = gSystem->OpenDirectory(plotDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(plotDIR.Data(), kTRUE);
//}}}

	TCanvas* ctot = new TCanvas("ctot", "", 0, 0, 1200, 300);
	TCanvas* cZYAM = new TCanvas("cZYAM", "", 0, 0, 1200, 300);
	TCanvas* cyield = new TCanvas("cyield", "", 0, 0, 600, 600);
	ctot->Divide(4, 1);
	cZYAM->Divide(4, 1);
	TH1D* hYield = new TH1D("hYield", ";p_{T}^{#Upsilon};Associated Yield", pt_narr-1, ptBinsArr);
	FormTH1Marker(hYield, 0, 0, 1.4);

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
//get plots{{{
		TFile* fin = new TFile(Form("../Projection/CorrDist/CorrFiles/%s/MupT%s/Nominal/trk_dphi_distribution_Reco_Mult_%d-%d_pt_%d-%d_rap_-24-24_Trkpt_%d-%d_Data_%s_MupT%s.root", version.Data(), MupT.Data(), multMin, multMax, (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data()), "READ");
		TH1D* hRDeltaPhi;
		TH1D* hRDeltaPhi_ZYAM;
		hRDeltaPhi = (TH1D*) fin->Get("hRatioRecoDeltaPhi2_coarse");
		hRDeltaPhi->GetYaxis()->SetTitle("#frac{1}{N_{trig}}#frac{dN^{pair}}{d#Delta#phi}");
		hRDeltaPhi_ZYAM = (TH1D*) hRDeltaPhi->Clone(Form("hRDeltaPhi_coarse_ZYAM"));
		hRDeltaPhi_ZYAM->Reset();
		hRDeltaPhi_ZYAM->GetYaxis()->SetTitle("#frac{1}{N_{trig}}#frac{dN^{pair}}{d#Delta#phi}-C_{ZYAM}");
//}}}

		TF1* f1 = new TF1("f1", "[0]*x*x+[1]*x+[2]", 0.2, 1.5);
		f1->SetLineColor(kRed);
		TF1* f2 = new TF1("f2", "[0]*x*x+[1]*x+[2]", -0.8, -0.2);
		f2->SetLineColor(kRed);
		ctot->cd(ipt+1);
		hRDeltaPhi->Draw();
		if(multMin == 80 && ipt ==3) hRDeltaPhi->Fit("f2", "ML", "", -1.0, 0.0);
		else hRDeltaPhi->Fit("f1", "ML", "", 0.2, 1.5);

		TLatex* lt1 = new TLatex();
		FormLatex(lt1, 12, 0.08);
		if(ipt == 0)
		{
			lt1->DrawLatex(0.16, 0.83, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.16, 0.73, "|#Delta#eta| > 2");
		}
		lt1->DrawLatex(0.16, 0.63, Form("%d #leq p_{T} < %d", (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1]));

		Double_t Min;
		if(multMin == 80 && ipt == 3) Min = f2->GetMinimum(-1.0, 0.0);
		else Min = f1->GetMinimum(0.2, 1.5);
		Double_t JYield = 0;
		Double_t JYieldEE = 0;
		for(Int_t ibin = 0; ibin < hRDeltaPhi->GetNbinsX(); ibin++)
		{
			Double_t vals = hRDeltaPhi->GetBinContent(ibin+1);
			Double_t Evals = hRDeltaPhi->GetBinError(ibin+1);
			hRDeltaPhi_ZYAM->SetBinContent(ibin+1, vals-Min);
			hRDeltaPhi_ZYAM->SetBinError(ibin+1, Evals);
			if( ibin >= 1 && ibin < 7 )
			{
				JYield += hRDeltaPhi_ZYAM->GetBinContent(ibin+1);
				JYieldEE += TMath::Power(hRDeltaPhi_ZYAM->GetBinError(ibin+1), 2);
			}
		}
		cZYAM->cd(ipt+1);
		hRDeltaPhi_ZYAM->Draw();
		SetLine(1, -1.45, 0, 4.45, 0, 0, 3);

		TLatex* lt2 = new TLatex();
		FormLatex(lt2, 12, 0.08);
		if(ipt == 0)
		{
			lt2->DrawLatex(0.16, 0.83, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt2->DrawLatex(0.16, 0.73, "|#Delta#eta| > 2");
		}
		lt2->DrawLatex(0.16, 0.63, Form("%d #leq p_{T} < %d", (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1]));

		hYield->SetBinContent(ipt+1, JYield);
		hYield->SetBinError(ipt+1, TMath::Sqrt(JYieldEE));
	}
	cyield->cd();
	hYield->SetMinimum(-0.02);
	hYield->SetMaximum(0.1);
	hYield->Draw("pe");
	SetLine(1, 0, 0, 30, 0, 0, 3);

	ctot->SaveAs(Form("Plots/LongRange_dphi_dist_mult_%d-%d_%s.pdf", multMin, multMax, version.Data()));
	cZYAM->SaveAs(Form("Plots/LongRange_dphi_ZYAM_dist_mult_%d-%d_%s.pdf", multMin, multMax, version.Data()));
	cyield->SaveAs(Form("Plots/LongRange_Associated_Yield_dist_mult_%d-%d_%s.pdf", multMin, multMax, version.Data()));
	TFile* fout = new TFile(Form("File/LongRange_Associated_Yield_mult_%d-%d_%s.root", multMin, multMax, version.Data()), "RECREATE");
	fout->cd();
	hYield->Write();
	fout->Close();
}
