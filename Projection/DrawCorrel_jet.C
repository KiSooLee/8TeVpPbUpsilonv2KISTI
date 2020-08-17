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

void DrawCorrel_jet(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Bool_t isTnP = true, const TString MupT = "4", const Bool_t isBkg = true)
{ 
	SetStyle();

//set name{{{
	TString Direction[2] = {"Pbp", "pPb"};
	TString PorB;
	if(isBkg) PorB = "bkg";
	else PorB = "peak";
	TString SysDir;
	if( isAccRW && isEffRW && isTnP ) SysDir = "Nominal";
	else if( !isAccRW && isEffRW && isTnP ) SysDir = "SysAcc";
	else if( isAccRW && !isEffRW && isTnP ) SysDir = "SysEff";
	else if( isAccRW && isEffRW && !isTnP ) SysDir = "SysTnP";
	else
	{
		cout << "There is no such option" << endl;
		return;
	}
//}}}

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fullDIR = mainDIR + Form("/CorrDist/CorrDistFullRatio/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString fullsameDIR = mainDIR + Form("/CorrDist/CorrDistFullSame/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString fullmixDIR = mainDIR + Form("/CorrDist/CorrDistFullMix/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString cut1sameDIR = mainDIR + Form("/CorrDist/CorrDistCut1Same/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString cut1mixDIR = mainDIR + Form("/CorrDist/CorrDistCut1Mix/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString cut1p5sameDIR = mainDIR + Form("/CorrDist/CorrDistCut1p5Same/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString cut1p5mixDIR = mainDIR + Form("/CorrDist/CorrDistCut1p5Mix/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString cut2sameDIR = mainDIR + Form("/CorrDist/CorrDistCut2Same/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString cut2mixDIR = mainDIR + Form("/CorrDist/CorrDistCut2Mix/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString shortsameDIR = mainDIR + Form("/CorrDist/CorrDistShortSame/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString shortmixDIR = mainDIR + Form("/CorrDist/CorrDistShortMix/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());

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

	TFile* samePbp[2];
	TFile* mixPbp[2];

	//for narrow mass range
	//const Double_t massMin = 9.3;
	//const Double_t massMax = 9.6;
	//for wide mass range
	const Double_t massMin = 9.1;
	const Double_t massMax = 9.8;

//Define canvas and histogram{{{
	TCanvas* c_same_fine = new TCanvas("c_same_Full_fine", "", 0, 0, 600, 600);
	TCanvas* c_same_coarse = new TCanvas("c_same_FUll_coarse", "", 0, 0, 600, 600);
	TCanvas* c_mix_fine = new TCanvas("c_mix_Full_fine", "", 0, 0, 600, 600);
	TCanvas* c_mix_coarse = new TCanvas("c_mix_FUll_coarse", "", 0, 0, 600, 600);
	TCanvas* c_ratio_fine = new TCanvas("c_ratio_Full_fine", "", 0, 0, 600, 600);
	TCanvas* c_ratio_coarse = new TCanvas("c_ratio_FUll_coarse", "", 0, 0, 600, 600);

	TH2D *hSamePbp_fine[2];
	TH2D *hMixPbp_fine[2];
	TH2D *hSamePbp_coarse[2];
	TH2D *hMixPbp_coarse[2];
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

//Get files{{{
	for(Int_t ipPb = 0; ipPb < 2; ipPb++)
	{
		samePbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/deta-dphi_Reco_%s_distribution_same_Data_Acc%o_Eff%o_TnP%o_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Direction[ipPb].Data(), isAccRW, isEffRW, isTnP, PorB.Data()), "READ");
		mixPbp[ipPb] = new TFile(Form("../Correlation/%d-%d_%d-%d_%d-%d_%d-%d_%s_MupT%s/deta-dphi_Reco_%s_distribution_mix_Data_Acc%o_Eff%o_TnP%o_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Direction[ipPb].Data(), isAccRW, isEffRW, isTnP, PorB.Data()), "READ");
	}
//}}}

	for(Int_t ipPb = 0; ipPb < 2; ipPb++)
	{
//get plot{{{
		hSamePbp_fine[ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sReco1_1", Direction[ipPb].Data()));
		hSamePbp_coarse[ipPb] = (TH2D*)samePbp[ipPb]->Get(Form("hSame%sReco1_2", Direction[ipPb].Data()));
		hMixPbp_fine[ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sReco1_1", Direction[ipPb].Data()));
		hMixPbp_coarse[ipPb] = (TH2D*)mixPbp[ipPb]->Get(Form("hMix%sReco1_2", Direction[ipPb].Data()));
		hSamePbp_fine[ipPb]->Sumw2();
		hSamePbp_coarse[ipPb]->Sumw2();
		hMixPbp_fine[ipPb]->Sumw2();
		hMixPbp_coarse[ipPb]->Sumw2();
//}}}
	}

//merge direction{{{
	hSamePbp_fine[0]->Add(hSamePbp_fine[1]);
	hSamePbp_coarse[0]->Add(hSamePbp_coarse[1]);
	hMixPbp_fine[0]->Add(hMixPbp_fine[1]);
	hMixPbp_coarse[0]->Add(hMixPbp_coarse[1]);
//}}}

//Draw{{{

//same fine{{{
	c_same_fine->cd();
	hSamePbp_fine[0]->Draw("Surf1");
	lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
	lt1->DrawLatex(0.15,0.9, Form(" p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	if(isBkg) lt1->DrawLatex(0.15,0.75, Form("8.0 #leq m_{#mu+#mu-} < 9.0 GeV/c^{2}, 11 #leq m_{#mu+#mu-} < 14 combined"));
	else lt1->DrawLatex(0.15,0.75, Form("%.1f #leq m_{#mu+#mu-} < %.1f GeV/c^{2}", massMin, massMax));^
	c_same_fine->SaveAs(Form("CorrDist/CorrDistFullSame/%s/MupT%s/%s/plot_corr_same_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_Data_%s_MupT%s_Acc%o_Eff%o_TnP%o_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), MupT.Data(), isAccRW, isEffRW, isTnP, PorB.Data()));
//}}}

//mix fine{{{
	c_mix_fine->cd();
	hMixPbp_fine[0]->Draw("Surf1");
	lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
	lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	if(isBkg) lt1->DrawLatex(0.15,0.75, Form("8.0 #leq m_{#mu+#mu-} < 9.0 GeV/c^{2}, 11 #leq m_{#mu+#mu-} < 14 combined"));
	else lt1->DrawLatex(0.15,0.75, Form("%.1f #leq m_{#mu+#mu-} < %.1f GeV/c^{2}", massMin, massMax));
	c_mix_fine->SaveAs(Form("CorrDist/CorrDistFullMix/%s/MupT%s/%s/plot_corr_mix_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_Data_%s_MupT%s_Acc%o_Eff%o_TnP%o_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), MupT.Data(), isAccRW, isEffRW, isTnP, PorB.Data()));
//}}}

//ratio fine{{{
	c_ratio_fine->cd();
	hSamePbp_fine[0]->Divide(hMixPbp_fine[0]);
	hSamePbp_fine[0]->GetXaxis()->SetRangeUser(-3.6, 3.6);
	hSamePbp_fine[0]->Draw("Surf1");
	lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
	lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	if(isBkg) lt1->DrawLatex(0.15,0.75, Form("8.0 #leq m_{#mu+#mu-} < 9.0 GeV/c^{2}, 11 #leq m_{#mu+#mu-} < 14 combined"));
	else lt1->DrawLatex(0.15,0.75, Form("%.1f #leq m_{#mu+#mu-} < %.1f GeV/c^{2}", massMin, massMax));
	c_ratio_fine->SaveAs(Form("CorrDist/CorrDistFullRatio/%s/MupT%s/%s/plot_corr_ratio_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_Data_%s_MupT%s_Acc%o_Eff%o_TnP%o_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), MupT.Data(), isAccRW, isEffRW, isTnP, PorB.Data()));
//}}}

//same coarse{{{
	c_same_coarse->cd();
	hSamePbp_coarse[0]->Draw("Surf1");
	lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
	lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	if(isBkg) lt1->DrawLatex(0.15,0.75, Form("8.0 #leq m_{#mu+#mu-} < 9.0 GeV/c^{2}, 11 #leq m_{#mu+#mu-} < 14 combined"));
	else lt1->DrawLatex(0.15,0.75, Form("%.1f #leq m_{#mu+#mu-} < %.1f GeV/c^{2}", massMin, massMax));
	c_same_coarse->SaveAs(Form("CorrDist/CorrDistFullSame/%s/MupT%s/%s/plot_corr_same_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_Data_%s_MupT%s_Acc%o_Eff%o_TnP%o_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), MupT.Data(), isAccRW, isEffRW, isTnP, PorB.Data()));
//}}}

//mix coarse{{{
	c_mix_coarse->cd();
	hMixPbp_coarse[0]->Draw("Surf1");
	lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
	lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	if(isBkg) lt1->DrawLatex(0.15,0.75, Form("8.0 #leq m_{#mu+#mu-} < 9.0 GeV/c^{2}, 11 #leq m_{#mu+#mu-} < 14 combined"));
	else lt1->DrawLatex(0.15,0.75, Form("%.1f #leq m_{#mu+#mu-} < %.1f GeV/c^{2}", massMin, massMax));
	c_mix_coarse->SaveAs(Form("CorrDist/CorrDistFullMix/%s/MupT%s/%s/plot_corr_mix_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_Data_%s_MupT%s_Acc%o_Eff%o_TnP%o_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), MupT.Data(), isAccRW, isEffRW, isTnP, PorB.Data()));
//}}}

//ratio coarse{{{
	c_ratio_coarse->cd();
	hSamePbp_coarse[0]->Divide(hMixPbp_coarse[0]);
	hSamePbp_coarse[0]->GetXaxis()->SetRangeUser(-3.6, 3.6);
	hSamePbp_coarse[0]->Draw("Surf1");
	lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
	lt1->DrawLatex(0.15,0.9, Form("p_{T}^{#mu} > %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.15,0.85, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
	if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.8, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
	else lt1->DrawLatex(0.15,0.8, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
	if(isBkg) lt1->DrawLatex(0.15,0.75, Form("8.0 #leq m_{#mu+#mu-} < 9.0 GeV/c^{2}, 11 #leq m_{#mu+#mu-} < 14 combined"));
	else lt1->DrawLatex(0.15,0.75, Form("%.1f #leq m_{#mu+#mu-} < %.1f GeV/c^{2}", massMin, massMax));
	c_ratio_coarse->SaveAs(Form("CorrDist/CorrDistFullRatio/%s/MupT%s/%s/plot_corr_ratio_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_Data_%s_MupT%s_Acc%o_Eff%o_TnP%o_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), MupT.Data(), isAccRW, isEffRW, isTnP, PorB.Data()));
//}}}

//}}}
}
