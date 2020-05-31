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

void DrawCorrel(const Bool_t isMC = false, const Bool_t isGen = false, const Bool_t isTrk = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const bool Weight = true, const TString MupT = "4")
{ 
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fullDIR = mainDIR + Form("/CorrDist/CorrDistFullRatio/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString fullsameDIR = mainDIR + Form("/CorrDist/CorrDistFullSame/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString fullmixDIR = mainDIR + Form("/CorrDist/CorrDistFullMix/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString cut1sameDIR = mainDIR + Form("/CorrDist/CorrDistCut1Same/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString cut1mixDIR = mainDIR + Form("/CorrDist/CorrDistCut1Mix/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString cut1p5sameDIR = mainDIR + Form("/CorrDist/CorrDistCut1p5Same/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString cut1p5mixDIR = mainDIR + Form("/CorrDist/CorrDistCut1p5Mix/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString cut2sameDIR = mainDIR + Form("/CorrDist/CorrDistCut2Same/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString cut2mixDIR = mainDIR + Form("/CorrDist/CorrDistCut2Mix/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString shortsameDIR = mainDIR + Form("/CorrDist/CorrDistShortSame/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);
	TString shortmixDIR = mainDIR + Form("/CorrDist/CorrDistShortMix/%s/MupT%s/Weight%o", version.Data(), MupT.Data(), Weight);

	void * dirf = gSystem->OpenDirectory(fullDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fullDIR.Data(), kTRUE);

	void * dirfs = gSystem->OpenDirectory(fullsameDIR.Data());
	if(dirfs) gSystem->FreeDirectory(dirfs);
	else gSystem->mkdir(fullsameDIR.Data(), kTRUE);

	void * dirfb = gSystem->OpenDirectory(fullmixDIR.Data());
	if(dirfb) gSystem->FreeDirectory(dirfb);
	else gSystem->mkdir(fullmixDIR.Data(), kTRUE);

	void * dirc1s = gSystem->OpenDirectory(cut1sameDIR.Data());
	if(dirc1s) gSystem->FreeDirectory(dirc1s);
	else gSystem->mkdir(cut1sameDIR.Data(), kTRUE);

	void * dirc1b = gSystem->OpenDirectory(cut1mixDIR.Data());
	if(dirc1b) gSystem->FreeDirectory(dirc1b);
	else gSystem->mkdir(cut1mixDIR.Data(), kTRUE);

	void * dirc1p5s = gSystem->OpenDirectory(cut1p5sameDIR.Data());
	if(dirc1p5s) gSystem->FreeDirectory(dirc1p5s);
	else gSystem->mkdir(cut1p5sameDIR.Data(), kTRUE);

	void * dirc1p5b = gSystem->OpenDirectory(cut1p5mixDIR.Data());
	if(dirc1p5b) gSystem->FreeDirectory(dirc1p5b);
	else gSystem->mkdir(cut1p5mixDIR.Data(), kTRUE);

	void * dirc2s = gSystem->OpenDirectory(cut2sameDIR.Data());
	if(dirc2s) gSystem->FreeDirectory(dirc2s);
	else gSystem->mkdir(cut2sameDIR.Data(), kTRUE);

	void * dirc2b = gSystem->OpenDirectory(cut2mixDIR.Data());
	if(dirc2b) gSystem->FreeDirectory(dirc2b);
	else gSystem->mkdir(cut2mixDIR.Data(), kTRUE);

	void * dirshs = gSystem->OpenDirectory(shortsameDIR.Data());
	if(dirshs) gSystem->FreeDirectory(dirshs);
	else gSystem->mkdir(shortsameDIR.Data(), kTRUE);

	void * dirshb = gSystem->OpenDirectory(shortmixDIR.Data());
	if(dirshb) gSystem->FreeDirectory(dirshb);
	else gSystem->mkdir(shortmixDIR.Data(), kTRUE);
//}}}

//set name{{{
	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString RorG;
	if(isGen) RorG = "Gen";
	else RorG = "Reco";
	TString Direction[2] = {"Pbp", "pPb"};
	const Int_t Naway = 5;
	TString Away[Naway] = {"Full", "Cut2", "Cut1p5", "Cut1", "Short"};
	TString Trk;
	if(isTrk) Trk = "trk_";
	else Trk = "";
//}}}

	TFile *samePbp[2];
	TFile *mixPbp[2];

//Define canvas and histogram{{{

//Define canvas{{{
	TCanvas* c_ratio_fine[Naway];
	TCanvas* c_same_fine[Naway];
	TCanvas* c_mix_fine[Naway];
	TCanvas* c_ratio_coarse[Naway];
	TCanvas* c_same_coarse[Naway];
	TCanvas* c_mix_coarse[Naway];
	for(Int_t iaway = 0; iaway < Naway; iaway++)
	{
		c_ratio_fine[iaway] = new TCanvas(Form("c_ratio_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_same_fine[iaway] = new TCanvas(Form("c_same_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_mix_fine[iaway] = new TCanvas(Form("c_mix_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_ratio_coarse[iaway] = new TCanvas(Form("c_ratio_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_same_coarse[iaway] = new TCanvas(Form("c_same_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		c_mix_coarse[iaway] = new TCanvas(Form("c_mix_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
	}
//}}}

//Define histogram{{{
	TH2D *hSamePbp_fine[Naway][2];
	TH2D *hMixPbp_fine[Naway][2];
	TH2D *hSamePbp_coarse[Naway][2];
	TH2D *hMixPbp_coarse[Naway][2];
//}}}

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

	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->SetNDC();

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{
//Get files{{{
		for(Int_t ipPb = 0; ipPb < 2; ipPb++)
		{
			samePbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/%sdeta-dphi_%s_%s_distribution_same_%s_weight%o_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Trk.Data(), RorG.Data(), Direction[ipPb].Data(), MorD.Data(), Weight, imass), "READ");
			mixPbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/%sdeta-dphi_%s_%s_distribution_mix_%s_weight%o_%d.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Trk.Data(), RorG.Data(), Direction[ipPb].Data(), MorD.Data(), Weight, imass), "READ");
		}
//}}}

		for(Int_t iaway = 0; iaway < Naway; iaway++)
		{
			for(Int_t ipPb = 0; ipPb < 2; ipPb++)
			{
//get plot{{{
				hSamePbp_fine[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%s%s%d_1", Direction[ipPb].Data(), RorG.Data(), iaway+1));
				hSamePbp_coarse[iaway][ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%s%s%d_2", Direction[ipPb].Data(), RorG.Data(), iaway+1));
				hMixPbp_fine[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%s%s%d_1", Direction[ipPb].Data(), RorG.Data(), iaway+1));
				hMixPbp_coarse[iaway][ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%s%s%d_2", Direction[ipPb].Data(), RorG.Data(), iaway+1));
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

//Draw{{{

//same fine{{{
			c_same_fine[iaway]->cd();
			hSamePbp_fine[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form(" p_{T}^{#mu} > %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass]+1)));
			//lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 14.0));
			c_same_fine[iaway]->SaveAs(Form("CorrDist/CorrDist%sSame/%s/MupT%s/Weight%o/%splot_corr_same_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
//}}}

//mix fine{{{
			c_mix_fine[iaway]->cd();
			hMixPbp_fine[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass]+1)));
			//lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 14.0));
			c_mix_fine[iaway]->SaveAs(Form("CorrDist/CorrDist%sMix/%s/MupT%s/Weight%o/%splot_corr_mix_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
//}}}

//ratio fine{{{
			if(iaway == 0)
			{
				c_ratio_fine[iaway]->cd();
				hSamePbp_fine[iaway][0]->Divide(hMixPbp_fine[iaway][0]);
				hSamePbp_fine[iaway][0]->Draw("Surf1");
				lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass]+1)));
				//lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 14.0));
				c_ratio_fine[iaway]->SaveAs(Form("CorrDist/CorrDist%sRatio/%s/MupT%s/Weight%o/%splot_corr_ratio_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
			}
//}}}

//same coarse{{{
			c_same_coarse[iaway]->cd();
			hSamePbp_coarse[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass]+1)));
			//lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 14.0));
			c_same_coarse[iaway]->SaveAs(Form("CorrDist/CorrDist%sSame/%s/MupT%s/Weight%o/%splot_corr_same_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
//}}}

//mix coarse{{{
			c_mix_coarse[iaway]->cd();
			hMixPbp_coarse[iaway][0]->Draw("Surf1");
			lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass]+1)));
			//lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 14.0));
			c_mix_coarse[iaway]->SaveAs(Form("CorrDist/CorrDist%sMix/%s/MupT%s/Weight%o/%splot_corr_mix_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
//}}}

//ratio coarse{{{
			if(iaway == 0)
			{
				c_ratio_coarse[iaway]->cd();
				hSamePbp_coarse[iaway][0]->Divide(hMixPbp_coarse[iaway][0]);
				hSamePbp_coarse[iaway][0]->Draw("Surf1");
				lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
				lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
				lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
				if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
				else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
				lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass]+1)));
				//lt1->DrawLatex(0.15,0.75, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 14.0));
				c_ratio_coarse[iaway]->SaveAs(Form("CorrDist/CorrDist%sRatio/%s/MupT%s/Weight%o/%splot_corr_ratio_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_weight%o_%d.pdf", Away[iaway].Data(), version.Data(), MupT.Data(), Weight, Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), Weight, imass));
			}
//}}}

//}}}
		}
	}
}
