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

#include <Fit/Fitter.h>
#include <Fit/BinData.h>
#include <Fit/Chi2FCN.h>
#include <Math/WrappedMultiTF1.h>
#include <HFitInterface.h>

#include "../Headers/Upsilon.h"
#include "../Headers/Style_Upv2.h"
//}}}

//external function{{{

//Chi2 calculation{{{
Int_t iparmass[19] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
							16, 17, 18};
Int_t iparvn[30] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
						16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};

struct GlobalChi2_width
{
	GlobalChi2_width(ROOT::Math::IMultiGenFunction & f1,
						ROOT::Math::IMultiGenFunction & f2):
	fChi2_1(&f1), fChi2_2(&f2) {}

	Double_t operator() (const double *par) const
	{
		Double_t p1[17];
		for(Int_t i = 0; i < 17; i++) p1[i] = par[iparmass[i]];
		Double_t p2[26];
		for(Int_t i = 0; i < 26; i++) p2[i] = par[iparvn[i]];
		return (*fChi2_1)(p1) + (*fChi2_2)(p2);
	}
	const ROOT::Math::IMultiGenFunction * fChi2_1;
	const ROOT::Math::IMultiGenFunction * fChi2_2;
};
//}}}

//totalYield{{{
Double_t TotalYield(Double_t* x, Double_t* par)
{
//define basic variables{{{
	Double_t N1 = par[0];
	Double_t N2 = par[1];
	Double_t mean = par[2];
	Double_t sigma = par[3];
	Double_t alpha = par[4];
	Double_t n = par[5];
	Double_t ratio = par[6];
	Double_t frac = par[7];
	Double_t cheb1 = par[8];
	Double_t cheb2 = par[9];
	Double_t sigma1S_2 = sigma*ratio;
//}}}

	//t2 > t1
	Double_t U1S_t1 = (x[0]-mean)/sigma;
	Double_t U1S_t2 = (x[0]-mean)/sigma1S_2;
	if (alpha < 0)
	{
		U1S_t1 = -U1S_t1;
		U1S_t2 = -U1S_t2;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;
	Double_t NC = n/absAlpha*1/(n-1)*exp(-absAlpha*absAlpha/2.);
	Double_t ND = TMath::Sqrt(TMath::Pi()/2.)*(1+TMath::Erf(absAlpha/TMath::Sqrt(2)));
	Double_t N1s_1 = 1./(sigma*(NC+ND));
	Double_t N1s_2 = 1./(sigma1S_2*(NC+ND));

//set value for cases{{{
	Double_t U1S_t1_val;
	Double_t U1S_t2_val;

	if(U1S_t1 >= -absAlpha) U1S_t1_val = exp(-U1S_t1*U1S_t1/2.);
	else U1S_t1_val = a/TMath::Power(b - U1S_t1, n);
	if(U1S_t2 >= -absAlpha) U1S_t2_val = exp(-U1S_t2*U1S_t2/2.);
	else U1S_t2_val = a/TMath::Power(b - U1S_t2, n);
//}}}

	Double_t chebx = (x[0]-9.25)/0.75;

//final upsilon value{{{
	Double_t Sigtot = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val );
	Double_t Bkgtot = N2*( 1 + cheb1*chebx + cheb2*(2*chebx*chebx-1) );
//}}}

	return Sigtot + Bkgtot;
}
//}}}

//totalvn pol2 bkg Upsilon 123S{{{
Double_t Totalvnpol2U123S(Double_t* x, Double_t* par)
{
//define basic variables{{{
	Double_t N1 = par[0];
	Double_t N2 = par[1];
	Double_t mean = par[2];
	Double_t sigma = par[3];
	Double_t alpha = par[4];
	Double_t n = par[5];
	Double_t ratio = par[6];
	Double_t frac = par[7];
	Double_t cheb1 = par[8];
	Double_t cheb2 = par[9];
	Double_t c1s = par[10];
	Double_t c1 = par[11];
	Double_t c2 = par[12];
	Double_t c3 = par[13];
	Double_t sigma1S_2 = sigma*ratio;
//}}}

	//t2 > t1
	Double_t U1S_t1 = (x[0]-mean)/sigma;
	Double_t U1S_t2 = (x[0]-mean)/sigma1S_2;
	if (alpha < 0)
	{
		U1S_t1 = -U1S_t1;
		U1S_t2 = -U1S_t2;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;
	Double_t NC = n/absAlpha*1/(n-1)*exp(-absAlpha*absAlpha/2.);
	Double_t ND = TMath::Sqrt(TMath::Pi()/2.)*(1+TMath::Erf(absAlpha/TMath::Sqrt(2)));
	Double_t N1s_1 = 1./(sigma*(NC+ND));
	Double_t N1s_2 = 1./(sigma1S_2*(NC+ND));

//set value for cases{{{
	Double_t U1S_t1_val;
	Double_t U1S_t2_val;

	if(U1S_t1 >= -absAlpha) U1S_t1_val = exp(-U1S_t1*U1S_t1/2.);
	else U1S_t1_val = a/TMath::Power(b - U1S_t1, n);
	if(U1S_t2 >= -absAlpha) U1S_t2_val = exp(-U1S_t2*U1S_t2/2.);
	else U1S_t2_val = a/TMath::Power(b - U1S_t2, n);
//}}}

	Double_t chebx = (x[0]-9.25)/0.75;

//final upsilon value{{{
	Double_t Sigtot = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val );
	Double_t Bkgtot = N2*( 1 + cheb1*chebx + cheb2*(2*chebx*chebx-1) );
//}}}

//return value{{{
	return c1s*( Sigtot/(Sigtot+Bkgtot) ) + ( c1*x[0]*x[0]+c2*x[0]+c3 )*(1-Sigtot/(Sigtot+Bkgtot));
//}}}

}
//}}}

//pol2 bkg{{{
Double_t pol2bkg(Double_t* x, Double_t* par)
{
	Double_t c1 = par[0];
	Double_t c2 = par[1];
	Double_t c3 = par[2];

	return c1*x[0]*x[0]+c2*x[0]+c3;
}
//}}}

//}}}

void SimultaneousFitMC(const Int_t multMin = 0, const Int_t multMax = 40, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Int_t AwayN = 1, const Bool_t isfine = true, const TString version = "v13", const TString MupT = "4")
{
	SetStyle();
	const Double_t RangeMin = 8.5;
	const Double_t RangeMax = 10;
	const Double_t histMin = -0.02;
	const Double_t histMax = 0.05;

//set fitting condition name{{{
	TString Away;
	if(AwayN == 1) Away = "1";
	else if(AwayN == 2) Away = "1p5";
	else if(AwayN == 3) Away = "2";
	else
	{
		cout << "out of delta eta cut range list" << endl;
		return;
	}
	TString Fine;
	if(isfine == true) Fine = "fine";
	else Fine = "coarse";
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
	TString fDIR = mainDIR + Form("/V2Dist/V2File/%s", version.Data());
	TString sDIR = mainDIR + Form("/V2Dist/SigV2/%s/MupT%s/Away%s", version.Data(), MupT.Data(), Away.Data());

	void * dirf = gSystem->OpenDirectory(fDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fDIR.Data(), kTRUE);

	void * dirs = gSystem->OpenDirectory(sDIR.Data());
	if(dirs) gSystem->FreeDirectory(dirs);
	else gSystem->mkdir(sDIR.Data(), kTRUE);
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

	TFile* fout;
	fout = new TFile(Form("V2Dist/V2File/%s/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_pol2_%s_%s_MC_%s_MupT%s%s.root", version.Data(), multMin, multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Away.Data(), Fine.Data(), version.Data(), MupT.Data(), Ffit.Data()), "RECREATE");
	fout->cd();

	TF1* fyieldtot[pt_narr-1];
	TF1* fvntot[pt_narr-1];
	Double_t v2[pt_narr-1];
	Double_t v2e[pt_narr-1];
	Double_t v2_bkg[pt_narr-1];
	Double_t a[pt_narr-1];
	Double_t b[pt_narr-1];
	Double_t pt[pt_narr-1];

//Define canvas for yield and vn dist{{{
	TCanvas* c1[pt_narr-1];
	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		c1[ipt] = new TCanvas(Form("c1_%d", ipt), "", 0, 0, 1200, 600);
		c1[ipt]->Divide(2, 1);
		pt[ipt] = ptBinsArr[ipt] + (ptBinsArr[ipt+1]-ptBinsArr[ipt])/2;
	}
	TH1D* hist = new TH1D("hist", "", 20, RangeMin, RangeMax);
	FormTH1Marker(hist, 0, 0, 1.4);
	hist->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
	hist->GetYaxis()->SetTitle("v_{2}^{S+B}");
	hist->SetMinimum(histMin);
	hist->SetMaximum(histMax);
//}}}

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
//Get yield distribution{{{
		TFile* fyield = new TFile(Form("../SkimmedFiles/Yield/Yield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_MC_%s_MupT%s.root", multMin, multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), version.Data(), MupT.Data()), "READ");
		TH1D* hyield = (TH1D*) fyield->Get(Form("hmass"));
		hyield->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
		hyield->GetYaxis()->SetTitle("Entries");
		FormTH1Marker(hyield, 0, 0, 1.4);

		c1[ipt]->cd(1);
		hyield->Draw();
//}}}

//Get fitting parameter{{{
		string char1, char2, char3, char4, char5, char6, char7, char8;
		string char9, char10, char11, char12, char13, char14, char15; 
		string char16, char17, char18, char19, char20, char21, char22; 
		string char23;
		Double_t var1, var2, var3, var4, var5, var6, var7, var8, var9;
		Double_t var10, var11, var12, var13, var14, var15, var16, var17;
		Double_t var18, var19, var20, var21, var22, var23;

		ifstream in1;
		in1.open(Form("../SkimmedFiles/Parameter/Result_parameters_mult_%d-%d_pt_%d-%d_rap_%d-%d_MC_%s_MupT%s.txt", multMin, multMax, (int)(10*ptBinsArr[ipt]), (int)(10*ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), version.Data(), MupT.Data()));
		if(in1.is_open())
		{
			in1 >> char1 >> char2 >> char3 >> char4 >> char5 >> char6 >> 
					char7 >> char8 >> char9 >> char10 >> char11 >> char12; 
			in1 >> var1 >> var2 >> var3 >> var4 >> var5 >> var6 >> 
					var7 >> var8 >> var9 >> var10 >> var11 >> var12;
			in1 >> char13 >> char14 >> char15 >> char16 >> char17 >> 
					char18 >> char19;
			in1 >> var13 >> var14 >> var15 >> var16 >> var17 >> var18 >> 
					var19;
			in1 >> char20 >> char21 >> char22 >> char23;
			in1 >> var20 >> var21 >> var22 >> var23;
		}
		in1.close();

		Double_t bpar1, bpar2, bpar3, bpar4, bpar5;
		ifstream in2;
		in2.open(Form("Parameter/v2_bkg_pol2_par_mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s.txt", multMin, multMax, (int)(10*ptBinsArr[ipt]), (int)(10*ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data()));
		if(in2.is_open())
		{
			in2 >> bpar1 >> bpar2 >> bpar3 >> bpar4 >> bpar5;
		}
		in2.close();
//}}}

//Get vn distribution{{{
		TFile* fvn;
		fvn = new TFile(Form("../ExtractV2/ProjDist/DistFiles/%s/MupT%s/v2_dist_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_MC_%s_MupT%s%s.root", version.Data(), MupT.Data(), multMin, multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Ffit.Data()), "READ");

		TGraphErrors* gvn;
		if(isfine == true) gvn = (TGraphErrors*) fvn->Get(Form("gv2_Away%s_fine", Away.Data()));
		else gvn = (TGraphErrors*) fvn->Get(Form("gv2_Away%s_coarse", Away.Data()));

		c1[ipt]->cd(2);
//}}}

//define function for simultaneous fitting{{{
		TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), TotalYield, RangeMin, RangeMax, 10);
		TF1* fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Totalvnpol2U123S, RangeMin, RangeMax, 14);
//}}}

//combine functions{{{
		fyield_simul->SetLineColor(2);
		fyield_simul->SetLineWidth(1);

		fvn_simul->SetLineColor(2);
		fvn_simul->SetLineWidth(1);

		ROOT::Math::WrappedMultiTF1 wmass(*fyield_simul, 1);
		ROOT::Math::WrappedMultiTF1 wvn(*fvn_simul, 1);

		ROOT::Fit::DataOptions opt;
		ROOT::Fit::DataRange massrange;

		massrange.SetRange(RangeMin, RangeMax);
		ROOT::Fit::BinData datamass(opt, massrange);
		ROOT::Fit::FillData(datamass, hyield);

		ROOT::Fit::DataRange vnrange;
		vnrange.SetRange(RangeMin, RangeMax);
		ROOT::Fit::BinData datavn(opt, vnrange);
		ROOT::Fit::FillData(datavn, gvn);

		ROOT::Fit::Chi2Function mass_chi2(datamass, wmass);
		ROOT::Fit::Chi2Function vn_chi2(datavn, wvn);

		GlobalChi2_width globalChi2(mass_chi2, vn_chi2);

		ROOT::Fit::Fitter fitter;
//}}}

//parameter setting{{{
		//parameters
		//par0[0] = 1S const
		//par0[1] = bkg const
		//par0[2] = 1S mean
		//par0[3] = 1S sigma
		//par0[4] = alpha
		//par0[5] = n
		//par0[6] = ratio
		//par0[7] = two crystal ball fraction
		//par0[8] = cheb1
		//par0[9] = cheb2
		//par0[10] = signal v2 component
		//par0[11~] = background v2 components

		const Int_t Npar = 15;
		Double_t par0[Npar];
		par0[0] = var20/10.;
		par0[1] = var21/10.;
		par0[2] = var13;
		par0[3] = var14;
		par0[4] = var16;
		par0[5] = var17;
		par0[6] = var3/var2;
		par0[7] = var15;
		par0[8] = var18;
		par0[9] = var19;
		par0[10] = 0.01;
		par0[11] = bpar1;
		par0[12] = bpar2;
		par0[13] = bpar3;
//}}}

//fit{{{

//combined function condition{{{
		c1[ipt]->cd(2);
		hist->Draw();
		fitter.Config().SetParamsSettings(Npar, par0);
		fitter.Config().ParSettings(0).SetLimits(0, 10000000);
		fitter.Config().ParSettings(1).SetLimits(0, 10000000);
		fitter.Config().ParSettings(2).Fix();
		fitter.Config().ParSettings(3).Fix();
		fitter.Config().ParSettings(4).Fix();
		fitter.Config().ParSettings(5).Fix();
		fitter.Config().ParSettings(6).Fix();
		fitter.Config().ParSettings(7).Fix();
		fitter.Config().ParSettings(8).Fix();
		fitter.Config().ParSettings(9).Fix();
		fitter.Config().MinimizerOptions().SetPrintLevel(0);
		fitter.Config().SetMinimizer("Minuit2","Migrad");
//}}}

		fitter.FitFCN(Npar, globalChi2, 0, datamass.Size()+datavn.Size(), true);
		ROOT::Fit::FitResult result = fitter.Result();
		result.Print(std::cout);

//Yield fitting result{{{
		fyield_simul->SetFitResult(result, iparmass);
		fyield_simul->SetRange(massrange().first, massrange().second);
		fyield_simul->SetLineColor(kRed);
		hyield->GetListOfFunctions()->Add(fyield_simul);

		TF1* fyield_bkg = new TF1(Form("fyield_bkg_%d", ipt), "[0]*( 1 + [1]*((x-9.25)/0.75) + [2]*(2*(x-9.25)*(x-9.25)/0.5625-1) )", RangeMin, RangeMax);
		fyield_bkg->FixParameter(0, fyield_simul->GetParameter(1));
		fyield_bkg->FixParameter(1, fyield_simul->GetParameter(8));
		fyield_bkg->FixParameter(2, fyield_simul->GetParameter(9));

		fyield_bkg->SetLineColor(kBlue);
		fyield_bkg->SetLineWidth(1);
		hyield->GetListOfFunctions()->Add(fyield_bkg);
//}}}

//vn fitting result{{{
		fvn_simul->SetFitResult(result, iparvn);
		fvn_simul->SetRange(vnrange().first, vnrange().second);
		fvn_simul->SetLineColor(2);

		TF1* fvn_bkg;
		fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), pol2bkg, RangeMin, RangeMax, 3);
		fvn_bkg->FixParameter(0, fvn_simul->GetParameter(11));
		fvn_bkg->FixParameter(1, fvn_simul->GetParameter(12));
		fvn_bkg->FixParameter(2, fvn_simul->GetParameter(13));

		fvn_bkg->SetLineColor(kMagenta);
		fvn_bkg->SetLineWidth(1);

		gvn->GetListOfFunctions()->Add(fvn_simul);
		gvn->GetListOfFunctions()->Add(fvn_bkg);
		gvn->SetTitle("");
		gvn->SetMarkerSize(0.8);
		gvn->SetLineWidth(1);
		gvn->Draw("PESAME");
//}}}

//}}}

//store individual function{{{
		fout->cd();
		fyieldtot[ipt] = (TF1*) fyield_simul->Clone();
		fyieldtot[ipt]->SetName(Form("massfit_pt%d", ipt));
		fyieldtot[ipt]->Write();

		fvntot[ipt] = (TF1*) fvn_simul->Clone();
		fvntot[ipt]->SetName(Form("vnfit_pt%d", ipt));
		fvntot[ipt]->Write();
//}}}

		v2[ipt] = fvn_simul->GetParameter(10);
		v2e[ipt] = fvn_simul->GetParError(10);

//get Chi2{{{
		Double_t xmass[200];
		Double_t pullmass[200];

		Float_t Chi2Yield = 0;
		Int_t NdfYield = hyield->GetNbinsX() - fyield_simul->GetNpar();

		for(Int_t ibin = 0; ibin < hyield->GetNbinsX(); ibin++)
		{
			xmass[ibin] = hyield->GetBinCenter(ibin);
			pullmass[ibin] = (hyield->GetBinContent(ibin) - fyield_simul->Eval(xmass[ibin]))/hyield->GetBinError(ibin);
			if(fabs(pullmass[ibin]) < 5)
			{
				Chi2Yield += pullmass[ibin]*pullmass[ibin];
			}
		}
		c1[ipt]->cd(1);
		TLatex* lt1 = new TLatex();
		FormLatex(lt1, 12, 0.04);
		lt1->SetNDC();
		lt1->DrawLatex(0.17, 0.93, Form("pPb #sqrt{s} = 8.16 TeV, %d #leq N^{offline}_{trk} < %d", multMin, multMax));
		lt1->DrawLatex(0.17, 0.83, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.17, 0.77, Form("%d #leq p_{T}^{#varUpsilon} < %d GeV/c", (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1]));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.17,0.70, Form("0.3 #leq p_{T}^{trk} < %d GeV/c", (int)TrkptMax));
		else lt1->DrawLatex(0.17,0.70, Form("%d < p_{T}^{assoc} < %d GeV/c", (int)TrkptMin, (int)TrkptMax));
		lt1->DrawLatex(0.17, 0.64, "|#Delta#eta^{trk}| > 1.0");
		lt1->DrawLatex(0.17, 0.58, Form("Chi2/ndf = %.f/%d", Chi2Yield, NdfYield));

		Double_t xv2[200];
		Double_t pullv2[200];
		Double_t v2y[200];

		Float_t Chi2v2 = 0;
		Int_t Ndfv2 = mass_narr-1-fvn_bkg->GetNpar()+1;

		for(Int_t ibin = 0; ibin < gvn->GetN(); ibin++)
		{
			gvn->GetPoint(ibin, xv2[ibin], v2y[ibin]);
			pullv2[ibin] = (v2y[ibin] - fvn_simul->Eval(xv2[ibin]))/gvn->GetErrorY(ibin);
			if(fabs(pullv2[ibin]) < 100)
			{
				Chi2v2 += pullv2[ibin]*pullv2[ibin];
			}
		}
		c1[ipt]->cd(2);
		lt1->DrawLatex(0.5, 0.18, Form("Chi2/ndf = %.f/%d", Chi2v2, Ndfv2));
//}}}
	}

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		c1[ipt]->SaveAs(Form("V2Dist/SigV2/%s/MupT%s/Away%s/Combined_fit_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_pol2_%s_%s_MC_%s_MupT%s%s.pdf", version.Data(), MupT.Data(), Away.Data(), multMin, multMax, (int)(ptBinsArr[ipt]*10), (int)(ptBinsArr[ipt+1]*10), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Away.Data(), Fine.Data(), version.Data(), MupT.Data(), Ffit.Data()));
	}

	TGraphErrors* v2plot = new TGraphErrors(pt_narr-1, pt, v2, 0, v2e);
	v2plot->SetTitle("");
	v2plot->SetName("v2_1s_vs_pt");
	v2plot->Write();
}
