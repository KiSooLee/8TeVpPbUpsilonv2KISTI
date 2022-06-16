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
#include <iostream>
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
//}}}

void extV23(const Bool_t isMC = false, const Bool_t isGen = false, const Bool_t isTrk = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v1", const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Int_t isTnP = 0, const TString MupT = "4", const Bool_t isSS = false, const Int_t FMax = 3)
{ 
	SetStyle();

//Define names{{{
	TString MorD;
	if(isMC) MorD = "MC";
	else MorD = "Data";
	TString RorG;
	if(isGen) RorG = "Gen";
	else RorG = "Reco";
	TString Away[3] = {"2", "1p5", "1"};
	TString Trk;
	if(isTrk) Trk = "trk_";
	else Trk = "";
	TString SS;
	if(isSS) SS = "SS";//same sign
	else SS = "OS";//opposite sign
	TString TnPs;
	if(isTnP == 0) TnPs = "w";
	else if(isTnP == 1) TnPs = "statup";
	else if(isTnP == 2) TnPs = "statdw";
	else if(isTnP == 3) TnPs = "systup";
	else if(isTnP == 4) TnPs = "systdw";
	else if(isTnP == 5) TnPs = "wo";
	else
	{
		cout << "There is no such TnP index" << endl;
		return;
	}
	TString Fourier;
	if(FMax == 2) Fourier = "quad";
	else if(FMax == 3) Fourier = "tra";
	else
	{
		cout << "no such level of fourier" << endl;
		return;
	}
	TString SysDir;
	if( isTrk || isMC || (!isMC && isAccRW && isEffRW && (isTnP == 0)) ) SysDir = "Nominal";
	else if( !isMC && !isAccRW && isEffRW && (isTnP == 0) ) SysDir = "SysAcc";
	else if( !isMC && isAccRW && !isEffRW && (isTnP == 0) ) SysDir = "SysEff";
	else if( !isMC && isAccRW && isEffRW && (isTnP != 0) ) SysDir = "SysTnP";
	else
	{
		cout << "There is no such option" << endl;
		return;
	}
//}}}

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString dphiDIR1 = mainDIR + Form("/ProjDist/CorrDistdphi/%s/MupT%s/Away1/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString dphiDIR1p5 = mainDIR + Form("/ProjDist/CorrDistdphi/%s/MupT%s/Away1p5/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString dphiDIR2 = mainDIR + Form("/ProjDist/CorrDistdphi/%s/MupT%s/Away2/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString v2DIR = mainDIR + Form("/ProjDist/V2Dist/%s/MupT%s/%s", version.Data(), MupT.Data(), SysDir.Data());
	TString fileDIR = mainDIR + Form("/ProjDist/DistFiles/%s/MupT%s", version.Data(), MupT.Data());

	void * dird1 = gSystem->OpenDirectory(dphiDIR1.Data());
	if(dird1) gSystem->FreeDirectory(dird1);
	else gSystem->mkdir(dphiDIR1.Data(), kTRUE);

	void * dird1p5 = gSystem->OpenDirectory(dphiDIR1p5.Data());
	if(dird1p5) gSystem->FreeDirectory(dird1p5);
	else gSystem->mkdir(dphiDIR1p5.Data(), kTRUE);

	void * dird2 = gSystem->OpenDirectory(dphiDIR2.Data());
	if(dird2) gSystem->FreeDirectory(dird2);
	else gSystem->mkdir(dphiDIR2.Data(), kTRUE);

	void * dirv = gSystem->OpenDirectory(v2DIR.Data());
	if(dirv) gSystem->FreeDirectory(dirv);
	else gSystem->mkdir(v2DIR.Data(), kTRUE);

	void * dirf = gSystem->OpenDirectory(fileDIR.Data());
	if(dirv) gSystem->FreeDirectory(dirv);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);
//}}}

	TFile* fin;

//Define canvas and histogram{{{

//Define canvas{{{
	TCanvas* cSame_fine[3];
	TCanvas* cSame_coarse[3];
	TCanvas* cMix_fine[3];
	TCanvas* cMix_coarse[3];
	TCanvas* cdphi_fine[3];
	TCanvas* cdphi_coarse[3];
	TCanvas* cv2_fine[3];
	TCanvas* cv2_coarse[3];
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		cSame_fine[iaway] = new TCanvas(Form("cSame_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cSame_coarse[iaway] = new TCanvas(Form("cSame_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		cMix_fine[iaway] = new TCanvas(Form("cMix_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cMix_coarse[iaway] = new TCanvas(Form("cMix_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		cdphi_fine[iaway] = new TCanvas(Form("cdphi_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cdphi_coarse[iaway] = new TCanvas(Form("cdphi_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
		cv2_fine[iaway] = new TCanvas(Form("cv2_%s_fine", Away[iaway].Data()), "", 0, 0, 600, 600);
		cv2_coarse[iaway] = new TCanvas(Form("cv2_%s_coarse", Away[iaway].Data()), "", 0, 0, 600, 600);
	}
//}}}

//Define histogram{{{
	TH1D* hSDeltaPhi_fine[3];
	TH1D* hSDeltaPhi_coarse[3];
	TH1D* hMDeltaPhi_fine[3];
	TH1D* hMDeltaPhi_coarse[3];
	TH1D* hRDeltaPhi_fine[3];
	TH1D* hRDeltaPhi_coarse[3];
//}}}

//Define graph value{{{
	Double_t v2v_fine[3][mass_narr-1] = {{0.}};
	Double_t v2Ev_fine[3][mass_narr-1] = {{0.}};
	Double_t v2v_coarse[3][mass_narr-1] = {{0.}};
	Double_t v2Ev_coarse[3][mass_narr-1] = {{0.}};
	Double_t v3v_coarse[3][mass_narr-1] = {{0.}};
	Double_t v3Ev_coarse[3][mass_narr-1] = {{0.}};
	Double_t v1v_fine[3][mass_narr-1] = {{0.}};
	Double_t v1v_coarse[3][mass_narr-1] = {{0.}};
	Double_t massCentArr[mass_narr-1];
	Double_t massE[mass_narr-1] = {0.};
	Double_t massValsArr[mass_narr];
	if(isMC) massValsArr[0] = 8.5;
	else massValsArr[0] = 8;
//}}}

//}}}

	TLatex *lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->SetNDC();
	TLatex *lt2 = new TLatex();
	FormLatex(lt2, 12, 0.04);
	lt2->SetNDC();

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

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{
		if(isTrk || isGen)
		{
			if (imass == 0) fin = new TFile(Form("../Projection/CorrDist/CorrFiles/%s/MupT%s/%s/%sdphi_distribution_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s.root", version.Data(), MupT.Data(), SysDir.Data(), Trk.Data(), RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data()), "READ");
			else continue;
		}
		else fin = new TFile(Form("../Projection/CorrDist/CorrFiles/%s/MupT%s/%s/%sdphi_distribution_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%d.root", version.Data(), MupT.Data(), SysDir.Data(), Trk.Data(), RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), imass), "READ");

		for(Int_t iaway = 0; iaway < 3; iaway++)
		{
//Get dphiplot{{{
			hSDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hSame%sDeltaPhi%s_fine", RorG.Data(), Away[iaway].Data()));
			hSDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hSame%sDeltaPhi%s_coarse", RorG.Data(), Away[iaway].Data()));
			hMDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hMix%sDeltaPhi%s_fine", RorG.Data(), Away[iaway].Data()));
			hMDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hMix%sDeltaPhi%s_coarse", RorG.Data(), Away[iaway].Data()));
			hRDeltaPhi_fine[iaway] = (TH1D*) fin->Get(Form("hRatio%sDeltaPhi%s_fine", RorG.Data(), Away[iaway].Data()));
			hRDeltaPhi_coarse[iaway] = (TH1D*) fin->Get(Form("hRatio%sDeltaPhi%s_coarse", RorG.Data(), Away[iaway].Data()));
			hSDeltaPhi_fine[iaway]->Sumw2();
	      hSDeltaPhi_coarse[iaway]->Sumw2();
			hMDeltaPhi_fine[iaway]->Sumw2();
	      hMDeltaPhi_coarse[iaway]->Sumw2();
			hRDeltaPhi_fine[iaway]->Sumw2();
	      hRDeltaPhi_coarse[iaway]->Sumw2();
//}}}

//Define fitting function{{{
			TF1 *vn_fine = 0;
			if(FMax == 2) vn_fine = new TF1(Form("vn_Away%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
			else if(FMax == 3) vn_fine = new TF1(Form("vn_Away%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x)+2*[3]*cos(3*x))",-6.28,6.28);
			vn_fine->SetLineColor(kViolet+1);
			vn_fine->SetLineStyle(1);
			vn_fine->SetLineWidth(2);
			TF1 *vn_coarse = 0;
			if(FMax == 2) vn_coarse = new TF1(Form("vn_Away%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
			else if(FMax == 3) vn_coarse = new TF1(Form("vn_Away%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x)+2*[3]*cos(3*x))",-6.28,6.28);
			vn_coarse->SetLineColor(kViolet+1);
			vn_coarse->SetLineStyle(1);
			vn_coarse->SetLineWidth(2);
//}}}

//fine{{{

//same{{{
			cSame_fine[iaway]->cd();
			hSDeltaPhi_fine[iaway]->Draw("pe");
			lt1->DrawLatex(0.20,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.20,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.20,0.78, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.20,0.71, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.20,0.71, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.20,0.59, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			if(isTrk || isMC) cSame_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sSame_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data()));
			else cSame_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sSame_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), imass));
//}}}

//mix{{{
			cMix_fine[iaway]->cd();
			hMDeltaPhi_fine[iaway]->Draw("pe");
			lt1->DrawLatex(0.20,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.20,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.20,0.78, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.20,0.71, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.20,0.71, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.20,0.59, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			if(isTrk || isMC) cMix_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sMix_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data()));
			else cMix_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sMix_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), imass));
//}}}

//ratio{{{
			cdphi_fine[iaway]->cd();
			cdphi_fine[iaway]->SetLeftMargin(0.15);
			cdphi_fine[iaway]->SetRightMargin(0.03);
			hRDeltaPhi_fine[iaway]->SetMaximum(1.03*hRDeltaPhi_fine[iaway]->GetMaximum());
			hRDeltaPhi_fine[iaway]->GetYaxis()->SetTitleOffset(1.28);
			hRDeltaPhi_fine[iaway]->GetYaxis()->SetTitleSize(0.42);
			hRDeltaPhi_fine[iaway]->GetYaxis()->SetTitle("#frac{1}{N_{trig}} #frac{d^{2}N^{pair}}{d#Delta#phi}");
			hRDeltaPhi_fine[iaway]->Draw("pe");
			hRDeltaPhi_fine[iaway]->Fit(vn_fine,"rqm");
			v2v_fine[iaway][imass] = vn_fine->GetParameter(1);
			v2Ev_fine[iaway][imass] = vn_fine->GetParError(1);
			TF1 *v1_fine = new TF1(Form("v1_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(x))",-6.28,6.28);
			v1_fine->SetLineColor(kBlue+1);
			v1_fine->SetLineStyle(2);
			v1_fine->SetLineWidth(2);
			v1_fine->SetParameter(0, vn_fine->GetParameter(0));
			v1_fine->SetParameter(1, vn_fine->GetParameter(2));
			TF1 *v2_fine = new TF1(Form("v2_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
			v2_fine->SetLineColor(kRed+1);
			v2_fine->SetLineStyle(2);
			v2_fine->SetLineWidth(2);
			v2_fine->SetParameter(0, vn_fine->GetParameter(0));
			v2_fine->SetParameter(1, vn_fine->GetParameter(1));
			TF1 *v3_fine = 0;
			if(FMax == 3)
			{
				v3_fine = new TF1(Form("v3_%s_fine", Away[iaway].Data()),"[0]*(1+2*[1]*cos(3*x))",-6.28,6.28);
				v3_fine->SetLineColor(kYellow+1);
				v3_fine->SetLineStyle(2);
				v3_fine->SetLineWidth(2);
				v3_fine->SetParameter(0, vn_fine->GetParameter(0));
				v3_fine->SetParameter(1, vn_fine->GetParameter(3));
			}
			v1_fine->Draw("same");
			v2_fine->Draw("same");
			if(FMax == 3) v3_fine->Draw("same");
			//CMSP(0.17, 0.92);
			CMS(0.17, 0.92);
			lumiText(0.60, 0.92);
			lt1->DrawLatex(0.20,0.85, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.20,0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.20,0.75, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.20,0.70, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.20,0.70, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.20,0.65, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.20,0.65, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.20,0.65, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.20,0.60, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			//lt1->DrawLatex(0.5,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_fine->GetParameter(1), vn_fine->GetParError(1)));
			TLegend* l_fine = new TLegend(0.76, 0.15, 0.9, 0.35);
			FormLegend(l_fine, 0.035);
			l_fine->AddEntry(vn_fine, "Total", "l");
			l_fine->AddEntry(v1_fine, "v1", "l");
			l_fine->AddEntry(v2_fine, "v2", "l");
			if(FMax == 3) l_fine->AddEntry(v3_fine, "v3", "l");
			l_fine->Draw();
			if(isTrk || isMC) cdphi_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sFit_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%s.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), MupT.Data(), Fourier.Data()));
			else cdphi_fine[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sFit_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%s_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), Fourier.Data(), imass));
//}}}

//}}}

//coarse{{{

//same{{{
			cSame_coarse[iaway]->cd();
			hSDeltaPhi_coarse[iaway]->Draw("pe");
			lt1->DrawLatex(0.20,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.20,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.20,0.78, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.20,0.71, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.20,0.71, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.20,0.59, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			if(isTrk || isMC) cSame_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sSame_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data()));
			else cSame_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sSame_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), imass));
//}}}

//mix{{{
			cMix_coarse[iaway]->cd();
			hMDeltaPhi_coarse[iaway]->Draw("pe");
			lt1->DrawLatex(0.20,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.20,0.85, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.20,0.78, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.20,0.71, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.20,0.71, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.20,0.64, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.20,0.59, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			if(isTrk || isMC) cMix_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sMix_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data()));
			else cMix_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sMix_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), imass));
//}}}

//ratio{{{
			cdphi_coarse[iaway]->cd();
			cdphi_coarse[iaway]->SetLeftMargin(0.15);
			cdphi_coarse[iaway]->SetRightMargin(0.03);
			hRDeltaPhi_coarse[iaway]->SetMaximum(1.03*hRDeltaPhi_coarse[iaway]->GetMaximum());
			hRDeltaPhi_coarse[iaway]->GetYaxis()->SetTitleOffset(1.28);
			hRDeltaPhi_coarse[iaway]->GetYaxis()->SetTitleSize(0.042);
			hRDeltaPhi_coarse[iaway]->GetYaxis()->SetTitle("#frac{1}{N_{trig}} #frac{d^{2}N^{pair}}{d#Delta#phi}");
			hRDeltaPhi_coarse[iaway]->Draw("pe");
			hRDeltaPhi_coarse[iaway]->Fit(vn_coarse,"rqm");
			v2v_coarse[iaway][imass] = vn_coarse->GetParameter(1);
			v2Ev_coarse[iaway][imass] = vn_coarse->GetParError(1);
			if(FMax == 3)
			{
				v3v_coarse[iaway][imass] = vn_coarse->GetParameter(3);
				v3Ev_coarse[iaway][imass] = vn_coarse->GetParError(3);
			}
			TF1* v1_coarse = new TF1(Form("v1_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(x))",-6.28,6.28);
			v1_coarse->SetLineColor(kBlue+1);
			v1_coarse->SetLineStyle(2);
			v1_coarse->SetLineWidth(2);
			v1_coarse->SetParameter(0, vn_coarse->GetParameter(0));
			v1_coarse->SetParameter(1, vn_coarse->GetParameter(2));
			TF1* v2_coarse = new TF1(Form("v2_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(2*x))",-6.28,6.28);
			v2_coarse->SetLineColor(kRed+1);
			v2_coarse->SetLineStyle(2);
			v2_coarse->SetLineWidth(2);
			v2_coarse->SetParameter(0, vn_coarse->GetParameter(0));
			v2_coarse->SetParameter(1, vn_coarse->GetParameter(1));
			TF1* v3_coarse = 0;
			if(FMax == 3)
			{
				v3_coarse = new TF1(Form("v3_%s_coarse", Away[iaway].Data()),"[0]*(1+2*[1]*cos(3*x))",-6.28,6.28);
				v3_coarse->SetLineColor(kYellow+1);
				v3_coarse->SetLineStyle(2);
				v3_coarse->SetLineWidth(2);
				v3_coarse->SetParameter(0, vn_coarse->GetParameter(0));
				v3_coarse->SetParameter(1, vn_coarse->GetParameter(3));
			}
			v1_coarse->Draw("same");
			v2_coarse->Draw("same");
			if(FMax == 3) v3_coarse->Draw("same");
			//CMSP(0.17, 0.92);
			CMS(0.17, 0.92);
			lumiText(0.60, 0.92);
			lt1->DrawLatex(0.20,0.85, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
			lt1->DrawLatex(0.20,0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
			lt1->DrawLatex(0.20,0.75, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
			if((int) TrkptMin == 0) lt1->DrawLatex(0.20,0.70, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
			else lt1->DrawLatex(0.20,0.70, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
			if(iaway == 0) lt1->DrawLatex(0.20,0.65, "|#Delta#eta^{trk}| > 2.0");
			else if(iaway == 1) lt1->DrawLatex(0.20,0.65, "|#Delta#eta^{trk}| > 1.5");
			else if(iaway == 2) lt1->DrawLatex(0.20,0.65, "|#Delta#eta^{trk}| > 1.0");
			lt1->DrawLatex(0.20,0.60, Form("%.2f #leq m_{#mu+#mu-} < %.2f GeV/c^{2}", 8+0.05*massBinsArr[imass], 8+0.05*(massBinsArr[imass+1])));
			//lt1->DrawLatex(0.5,0.2,Form("v_{2} : %0.3f #pm %0.4f", vn_coarse->GetParameter(1), vn_coarse->GetParError(1)));
			TLegend* l_coarse = new TLegend(0.76, 0.15, 0.9, 0.35);
			FormLegend(l_coarse, 0.035);
			l_coarse->AddEntry(vn_coarse, "Total", "l");
			l_coarse->AddEntry(v1_coarse, "v1", "l");
			l_coarse->AddEntry(v2_coarse, "v2", "l");
			if(FMax == 3) l_coarse->AddEntry(v3_coarse, "v3", "l");
			l_coarse->Draw();
			if(isTrk || isMC) cdphi_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sFit_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_MupT%s_%s.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), MupT.Data(), Fourier.Data()));
			else cdphi_coarse[iaway]->SaveAs(Form("ProjDist/CorrDistdphi/%s/MupT%s/Away%s/%s/%sFit_corr_%s_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%s_%d.pdf", version.Data(), MupT.Data(), Away[iaway].Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), Fourier.Data(), imass));
//}}}

//}}}
		}
		massCentArr[imass] = 8 + massBinsArr[imass]*0.05 + (massBinsArr[imass+1]-massBinsArr[imass])*0.05/2.;
		massValsArr[imass+1] = 8 + massBinsArr[imass+1]*0.05;
	}

//define reference hist{{{
	TH1D* hRef_fine[3];
	TH1D* hRef_coarse[3];
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		if(isTrk || isGen)
		{
			hRef_fine[iaway] = new TH1D(Form("hRef_%s_fine", Away[iaway].Data()), "", 1, 8, 14);
			hRef_coarse[iaway] = new TH1D(Form("hRef_%s_coarse", Away[iaway].Data()), "", 1, 8, 14);
		}
		else
		{
			hRef_fine[iaway] = new TH1D(Form("hRef_%s_fine", Away[iaway].Data()), "", mass_narr-1, massValsArr);
			hRef_coarse[iaway] = new TH1D(Form("hRef_%s_coarse", Away[iaway].Data()), "", mass_narr-1, massValsArr);
		}
		FormTH1(hRef_fine[iaway], 0);
		FormTH1(hRef_coarse[iaway], 0);
		hRef_fine[iaway]->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
		hRef_coarse[iaway]->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
		if(isTrk)
		{
			hRef_fine[iaway]->GetYaxis()->SetTitle("v_{2}^{trk-trk}");
			hRef_coarse[iaway]->GetYaxis()->SetTitle("v_{2}^{trk-trk}");
		}
		else
		{
			hRef_fine[iaway]->GetYaxis()->SetTitle("v_{2}^{#mu#mu-trk}");
			hRef_coarse[iaway]->GetYaxis()->SetTitle("v_{2}^{#mu#mu-trk}");
		}
		if(isTrk)
		{
			if(isMC)
			{
				hRef_fine[iaway]->SetMinimum(-0.01);
				hRef_fine[iaway]->SetMaximum(0.05);
				hRef_coarse[iaway]->SetMinimum(-0.01);
				hRef_coarse[iaway]->SetMaximum(0.05);
			}
			else
			{
				hRef_fine[iaway]->SetMinimum(-0.01);
				hRef_fine[iaway]->SetMaximum(0.01);
				hRef_coarse[iaway]->SetMinimum(-0.01);
				hRef_coarse[iaway]->SetMaximum(0.01);
			}
		}
		else
		{
			//for high-multiplicity
	/*
			hRef_fine[iaway]->SetMinimum(-0.03);
			hRef_fine[iaway]->SetMaximum(0.03);
			hRef_coarse[iaway]->SetMinimum(-0.03);
			hRef_coarse[iaway]->SetMaximum(0.03);
	*/
			//for low-multiplicity
			hRef_fine[iaway]->SetMinimum(-0.03);
			hRef_fine[iaway]->SetMaximum(0.06);
			hRef_coarse[iaway]->SetMinimum(-0.03);
			hRef_coarse[iaway]->SetMaximum(0.06);
		}
	}
//}}}

	TGraphErrors* gv2_fine[3];
	TGraphErrors* gv2_coarse[3];
	TGraphErrors* gv3_coarse[3];
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
//Define graph{{{
		gv2_fine[iaway] = new TGraphErrors(mass_narr-1, massCentArr, v2v_fine[iaway], massE, v2Ev_fine[iaway]);
		gv2_fine[iaway]->SetName(Form("gv2_Away%s_fine", Away[iaway].Data()));
		gv2_fine[iaway]->SetMaximum(0.05);
		gv2_fine[iaway]->SetMinimum(-0.05);
		gv2_coarse[iaway] = new TGraphErrors(mass_narr-1, massCentArr, v2v_coarse[iaway], massE, v2Ev_coarse[iaway]);
		gv2_coarse[iaway]->SetName(Form("gv2_Away%s_coarse", Away[iaway].Data()));
		gv2_coarse[iaway]->SetMaximum(0.05);
		gv2_coarse[iaway]->SetMinimum(-0.05);
		gv3_coarse[iaway] = new TGraphErrors(mass_narr-1, massCentArr, v3v_coarse[iaway], massE, v3Ev_coarse[iaway]);
		gv3_coarse[iaway]->SetName(Form("gv3_Away%s_coarse", Away[iaway].Data()));
		gv3_coarse[iaway]->SetMaximum(0.05);
		gv3_coarse[iaway]->SetMinimum(-0.05);
//}}}

//fine{{{
		cv2_fine[iaway]->cd();
		if(isTrk || isGen)
		{
			hRef_fine[iaway]->SetBinContent(1, v2v_fine[iaway][0]);
			hRef_fine[iaway]->SetBinError(1, v2Ev_fine[iaway][0]);
		}
		hRef_fine[iaway]->Draw();
		gv2_fine[iaway]->SetMarkerStyle(20);
		gv2_fine[iaway]->SetMarkerSize(1.2);
		//gv2_1fine->SetMarkerSize(0);
		if(!isTrk) gv2_fine[iaway]->Draw("pesame");
		lt2->DrawLatex(0.20,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
		lt2->DrawLatex(0.50,0.46, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
		lt2->DrawLatex(0.50,0.39, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt2->DrawLatex(0.50,0.32, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt2->DrawLatex(0.50,0.32, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		if(iaway == 0) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 2.0");
		else if(iaway == 1) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 1.5");
		else if(iaway == 2) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 1.0");
		if(isTrk || isMC) cv2_fine[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/%s/%sv2_dist_%s_%s_fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Fourier.Data()));
		else cv2_fine[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/%s/%sv2_dist_%s_%s_fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), Fourier.Data()));
		//cv2_1fine->SaveAs(Form("ProjDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data()));
//}}}

//coarse{{{
		cv2_coarse[iaway]->cd();
		if(isTrk || isGen)
		{
			hRef_coarse[iaway]->SetBinContent(1, v2v_coarse[iaway][0]);
			hRef_coarse[iaway]->SetBinError(1, v2Ev_coarse[iaway][0]);
		}
		hRef_coarse[iaway]->Draw();
		gv2_coarse[iaway]->SetMarkerStyle(20);
		gv2_coarse[iaway]->SetMarkerSize(1.2);
		//gv2_coarse->SetMarkerSize(0);
		if(!isTrk && !isGen) gv2_coarse[iaway]->Draw("pesame");
		lt2->DrawLatex(0.20,0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
		lt2->DrawLatex(0.50,0.46, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
		lt2->DrawLatex(0.50,0.39, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt2->DrawLatex(0.50,0.32, Form("0.3 #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt2->DrawLatex(0.50,0.32, Form("%d #leq p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		if(iaway == 0) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 2.0");
		else if(iaway == 1) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 1.5");
		else if(iaway == 2) lt2->DrawLatex(0.50,0.25, "|#Delta#eta^{trk}| > 1.0");
		if(isTrk || isMC) cv2_coarse[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/%s/%sv2_dist_%s_%s_coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Fourier.Data()));
		else cv2_coarse[iaway]->SaveAs(Form("ProjDist/V2Dist/%s/MupT%s/%s/%sv2_dist_%s_%s_coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%s.pdf", version.Data(), MupT.Data(), SysDir.Data(), Trk.Data(), RorG.Data(), Away[iaway].Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), Fourier.Data()));
		//cv2_1fine->SaveAs(Form("ProjDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_noMarker_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data()));
//}}}
	}

	TFile* fout;
	if(isTrk || isMC) fout = new TFile(Form("ProjDist/DistFiles/%s/MupT%s/%sv2_dist_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_MupT%s_%s.root", version.Data(), MupT.Data(), Trk.Data(), RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), MupT.Data(), Fourier.Data()), "RECREATE");
	else fout = new TFile(Form("ProjDist/DistFiles/%s/MupT%s/%sv2_dist_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_Acc%o_Eff%o_TnP%s_%s_MupT%s_%s.root", version.Data(), MupT.Data(), Trk.Data(), RorG.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, MorD.Data(), version.Data(), isAccRW, isEffRW, TnPs.Data(), SS.Data(), MupT.Data(), Fourier.Data()), "RECREATE");
	fout->cd();
	for(Int_t iaway = 0; iaway < 3; iaway++)
	{
		if(isTrk || isGen)
		{
			hRef_fine[iaway]->Write();
			hRef_coarse[iaway]->Write();
		}
		else
		{
			gv2_fine[iaway]->Write();
			gv2_coarse[iaway]->Write();
			gv3_coarse[iaway]->Write();
		}
	}
	fout->Close();
}
