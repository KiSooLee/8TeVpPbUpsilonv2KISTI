//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaveText.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TParameter.h>
#include <TSystem.h>
#include <RooRealVar.h>
#include <RooArgSet.h>
#include <RooDataSet.h>
#include <RooWorkspace.h>
#include <RooPlot.h>
#include <RooHist.h>
#include <RooGaussian.h>
#include <RooCBShape.h>
#include <RooChebychev.h>
#include <RooPolynomial.h>
#include <RooExponential.h>
#include <RooGenericPdf.h>
#include <RooAddPdf.h>
#include <RooFitResult.h>
#include <RooFormulaVar.h>
#include "../Headers/Style_Upv2.h"
#include "../Headers/Upsilon.h"
using namespace std;
using namespace RooFit;
//}}}

void GetYieldDataNoStat(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString version = "v1", const bool Weight = true, const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Int_t isTnP = 0, const bool SigSys = false, const bool BkgSys = false, const TString MupT = "4")
{
//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString massDIR = mainDIR + "/MassDist";
	void * dirpM = gSystem->OpenDirectory(massDIR.Data());
	if(dirpM) gSystem->FreeDirectory(dirpM);
	else gSystem->mkdir(massDIR.Data(), kTRUE);

	TString yieldDIR = mainDIR + "/Yield";
	void * dirpY = gSystem->OpenDirectory(yieldDIR.Data());
	if(dirpY) gSystem->FreeDirectory(dirpY);
	else gSystem->mkdir(yieldDIR.Data(), kTRUE);
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
	TString TnPs;
	if (isTnP == 0) TnPs = "w";
	else if (isTnP == 1) TnPs = "statup";
	else if (isTnP == 2) TnPs = "statdw";
	else if (isTnP == 3) TnPs = "systup";
	else if (isTnP == 4) TnPs = "systdw";
	else if (isTnP == 5) TnPs = "wo";
	else
	{
		cout << "There is no such TnP index" << endl;
		return;
	}
//}}}

	SetStyle();

	const Double_t RangeLow = 8;
	const Double_t RangeHigh = 14;
	const Int_t Nmassbins = 120;
	TFile* fout;
	if(Weight) fout = new TFile(Form("Yield/Plot_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Data_%s_Acc%o_Eff%o_TnP%s_SigSys%o_BkgSys%o_OS_MupT%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), version.Data(), isAccRW, isEffRW, TnPs.Data(), SigSys, BkgSys, MupT.Data()), "RECREATE");
	else fout = new TFile(Form("Yield/Plot_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Data_%s_noWeight_OS_MupT%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), version.Data(), MupT.Data()), "RECREATE");

//Define parameters{{{
	Double_t sig11;
	Double_t Frac, alp, N;
	Double_t erfm, erfsig, erfp0;
	Double_t chebyp0, chebyp1, chebyp2, chebyp3;
//}}}

//Get parameter{{{
	ifstream in;
	if(Weight) in.open(Form("Parameter/Parameters_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Data_%s_Acc%o_Eff%o_TnP%s_SigSys%o_BkgSys%o_OS_MupT%s.txt", multMin, multMax, (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), version.Data(), isAccRW, isEffRW, TnPs.Data(), SigSys, BkgSys, MupT.Data()));
	else in.open(Form("Parameter/Parameters_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Data_%s_noWeight_OS_MupT%s.txt", multMin, multMax, (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), version.Data(), MupT.Data()));
	if(in.is_open())
	{
		while(!in.eof())
		{
			if(!in.good())
			{
				cout << "Parameter File is wrong!!! Please Check!!!" << endl;
				return;
			}
			else
			{
				if(SigSys) in >> sig11 >> Frac >> alp >> N >> erfm >> erfsig >> erfp0;
				else if(BkgSys) in >> sig11 >> Frac >> alp >> N >> chebyp0 >> chebyp1 >> chebyp2 >> chebyp3;
				else in >> sig11 >> Frac >> alp >> N >> erfm >> erfsig >> erfp0;
			}
		}
	}
	in.close();
//}}}

//Get data{{{
	TFile* fin;
	if(Weight) fin = new TFile(Form("Skim_OniaTree_Data_PADoubleMuon_Acc%o_Eff%o_TnP%s_OS_MupT%s.root", isAccRW, isEffRW, TnPs.Data(), MupT.Data()), "READ");
	else fin = new TFile(Form("Skim_OniaTree_Data_PADoubleMuon_noWeight_OS_MupT%s.root", MupT.Data()), "READ");
	RooDataSet* dataset = (RooDataSet*) fin->Get("dataset");
	RooWorkspace* ws = new RooWorkspace(Form("workspace"));
	ws->import(*dataset);
	ws->data("dataset")->Print();

	RooDataSet* initialDS = (RooDataSet*) dataset->reduce(RooArgSet(*(ws->var("mass")), *(ws->var("pt")), *(ws->var("y")), *(ws->var("mult")), *(ws->var("weight"))));
	initialDS->SetName("initialDS");
	RooDataSet* weightedDS = new RooDataSet("weightedDS", "weight dataset", *initialDS->get(), Import(*initialDS), WeightVar(*ws->var("weight")));
//}}}

//Reduce dataset{{{
	RooDataSet* reducedDS = (RooDataSet*) weightedDS->reduce(RooArgSet(*(ws->var("mass"))), Form("(mult>=%d&&mult<%d)&&(pt>=%f&&pt<%f)&&(y>=%f&&y<%f)", multMin, multMax, ptMin, ptMax, rapMin, rapMax));
	reducedDS->SetName("reducedDS");
	ws->import(*reducedDS);
	ws->var("mass")->setRange(RangeLow, RangeHigh);
	ws->var("mass")->Print();
//}}}

//Set Canvas and Pad{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
	c1->cd();
	TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.98, 1.0);
	pad_mass->Draw();
	TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.05, 0.98, 0.25);
	pad_pull->SetBottomMargin(0);
	pad_pull->Draw();
	TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.65, 0.35, 0.85, 0.92);
	pad_leg->SetBottomMargin(0);
	//pad_leg->Draw();

	//TH1D* hYield = new TH1D(Form("hYield_mult_%d_%d_pt_%.1f_%.1f_rap_%.1f_%.1f", (int)multBinsArr[imult], (int)multBinsArr[imult+1], ptBinsArr[ipt], ptBinsArr[ipt+1]), "", 3, 0, 3);
	TH1D* hYield = new TH1D("hYield", "", 3, 0, 3);
//}}}

	pad_mass->cd();
	RooPlot* massPlot = ws->var("mass")->frame(Nmassbins);
	ws->data("reducedDS")->plotOn(massPlot, Name("massPlot"), MarkerSize(0.8));

//Signal function{{{

//mean{{{
	RooRealVar mean1S("mean1S", "mean of Upsilon 1S", U1S_mass, U1S_mass-0.01, U1S_mass+0.01);
	RooRealVar mratio2("mratio2", "mratio2", U2S_mass/U1S_mass);
	RooRealVar mratio3("mratio3", "mratio3", U3S_mass/U1S_mass);
	RooFormulaVar mean2S("mean2S", "mean1S*mratio2", RooArgSet(mean1S, mratio2));
	RooFormulaVar mean3S("mean3S", "mean1S*mratio3", RooArgSet(mean1S, mratio3));
//}}}

//sigma{{{
	RooRealVar sigma1S_1("sigma1S_1", "sigma1 of 1S", 0.05, 0.01, 0.2);
	//RooRealVar sigma1S_1("sigma1S_1", "sigma1 of 1S", 0.05, 0.01, 0.18);//for 110~300, 4~6 GeV
	//RooRealVar sigma1S_1("sigma1S_1", "sigma1 of 1S", 0.05, 0.01, 0.17);//for 110~300, 0~2 GeV
	//RooRealVar sigma1S_1("sigma1S_1", "sigma1 of 1S", 0.05, 0.01, 0.15);//for 110~300, 4~7 GeV
	RooFormulaVar sigma2S_1("sigma2S_1", "@0*@1", RooArgList(sigma1S_1, mratio2));
	RooFormulaVar sigma3S_1("sigma3S_1", "@0*@1", RooArgList(sigma1S_1, mratio3));

	RooRealVar* x1S = new RooRealVar("x1S", "sigma ratio", 0.35, 0, 1);

	RooFormulaVar sigma1S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_1, *x1S));
	RooFormulaVar sigma2S_2("sigma2S_2", "@0*@1", RooArgList(sigma1S_2, mratio2));
	RooFormulaVar sigma3S_2("sigma3S_2", "@0*@1", RooArgList(sigma1S_2, mratio3));
//}}}

	RooRealVar alpha("alpha", "alpha of Crystal ball", 2.0, 0.5, 20.0);
	RooRealVar n("n", "n of Crystal ball", 2.0, 0.5, 20.0);
	//RooRealVar alpha("alpha", "alpha of Crystal ball", 2.0, 1.7, 20.0);//for 110~300, 4~6 GeV
	//RooRealVar n("n", "n of Crystal ball", 2.0, 1.7, 20.0);//for 110~300, 4~6 GeV
	//RooRealVar alpha("alpha", "alpha of Crystal ball", 2.0, 2.0, 20.0);//for 110~300, 10~30 GeV
	//RooRealVar n("n", "n of Crystal ball", 2.0, 2.0, 20.0);//for 110~300, 10~39 GeV
	//RooRealVar alpha("alpha", "alpha of Crystal ball", 2.0, 1.7, 20.0);//for 0~2 GeV
	//RooRealVar n("n", "n of Crystal ball", 2.0, 1.7, 20.0);//for 0~2 GeV
	RooRealVar* frac = new RooRealVar("frac", "CB fraction", 0.5, 0, 1);

//twoCB function{{{
	RooCBShape* CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *(ws->var("mass")), mean1S, sigma1S_1, alpha, n);
	RooCBShape* CB2S_1 = new RooCBShape("CB2S_1", "2S Crystal ball function1", *(ws->var("mass")), mean2S, sigma2S_1, alpha, n);
	RooCBShape* CB3S_1 = new RooCBShape("CB3S_1", "3S Crystal ball function1", *(ws->var("mass")), mean3S, sigma3S_1, alpha, n);
	RooCBShape* CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *(ws->var("mass")), mean1S, sigma1S_2, alpha, n);
	RooCBShape* CB2S_2 = new RooCBShape("CB2S_2", "2S Crystal ball function2", *(ws->var("mass")), mean2S, sigma2S_2, alpha, n);
	RooCBShape* CB3S_2 = new RooCBShape("CB3S_2", "3S Crystal ball function2", *(ws->var("mass")), mean3S, sigma3S_2, alpha, n);
	RooGaussian* G1S = new RooGaussian("G1S", "1S Gaussian", *(ws->var("mass")), mean1S, sigma1S_2);
	RooGaussian* G2S = new RooGaussian("G2S", "2S Gaussian", *(ws->var("mass")), mean2S, sigma2S_2);
	RooGaussian* G3S = new RooGaussian("G3S", "3S Gaussian", *(ws->var("mass")), mean3S, sigma3S_2);

	RooAddPdf* twoCB1S = new RooAddPdf("twoCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2), RooArgList(*frac));
	RooAddPdf* twoCB2S = new RooAddPdf("twoCB2S", "Sum of 2S Crystal ball", RooArgList(*CB2S_1, *CB2S_2), RooArgList(*frac));
	RooAddPdf* twoCB3S = new RooAddPdf("twoCB3S", "Sum of 3S Crystal ball", RooArgList(*CB3S_1, *CB3S_2), RooArgList(*frac));
	RooAddPdf* CBG1S = new RooAddPdf("CBG1S", "Sum of 1S Crystal ball Gauss", RooArgList(*CB1S_1, *G1S), RooArgList(*frac));
	RooAddPdf* CBG2S = new RooAddPdf("CBG2S", "Sum of 2S Crystal ball Gauss", RooArgList(*CB2S_1, *G2S), RooArgList(*frac));
	RooAddPdf* CBG3S = new RooAddPdf("CBG3S", "Sum of 3S Crystal ball Gauss", RooArgList(*CB3S_1, *G3S), RooArgList(*frac));
//}}}

//}}}

//Background function{{{
	//RooRealVar Erfmean("Erfmean", "Mean of Errfunction", 5, 5, 9.5);
	//RooRealVar Erfsigma("Erfsigma", "Sigma of Errfunction", 1, 0, 40);
	RooRealVar Erfmean("Erfmean", "Mean of Errfunction", 5, 0, 10.0);//for 0~40, 4~7 GeV
	RooRealVar Erfsigma("Erfsigma", "Sigma of Errfunction", 1, 0, 100);//for 0~40, 4~7 GeV
	//RooRealVar Erfmean("Erfmean", "Mean of Errfunction", 6, 6, 9.5);//for 110~300, 0~2 GeV
	//RooRealVar Erfsigma("Erfsigma", "Sigma of Errfunction", 1, 0, 3);//for 110~300, 0~2 GeV
	RooRealVar Erfp0("Erfp0", "1st parameter of Errfunction", 1, 0, 100);
	RooRealVar Chebp0("Chebp0", "1st parameter of Chebychev", 0.1, -1, 1);
	RooRealVar Chebp1("Chebp1", "2st parameter of Chebychev", 0.1, -1, 1);
	RooRealVar Chebp2("Chebp2", "3st parameter of Chebychev", 0.1, -1, 1);
	RooRealVar Chebp3("Chebp3", "4st parameter of Chebychev", 0.1, -1, 1);
	//RooRealVar Chebp4("Chebp4", "5st parameter of Chebychev", 0.1, -100, 100);

	RooGenericPdf* bkgErf = new RooGenericPdf("bkgErf", "Error background", "TMath::Exp(-@0/@1)*(TMath::Erf((@0-@2)/(TMath::Sqrt(2)*@3))+1)*0.5", RooArgList(*(ws->var("mass")), Erfp0, Erfmean, Erfsigma));
	RooChebychev* bkgCheb4 = new RooChebychev("bkgCheb4", "Error background", *(ws->var("mass")), RooArgList(Chebp0, Chebp1, Chebp2, Chebp3));
//}}}

//Select Pdf{{{
	RooGenericPdf* Signal1S;
	RooGenericPdf* Signal2S;
	RooGenericPdf* Signal3S;
	if(SigSys)
	{
		Signal1S = (RooGenericPdf*) CBG1S;
		Signal2S = (RooGenericPdf*) CBG2S;
		Signal3S = (RooGenericPdf*) CBG3S;
	}
	else
	{
		Signal1S = (RooGenericPdf*) twoCB1S;
		Signal2S = (RooGenericPdf*) twoCB2S;
		Signal3S = (RooGenericPdf*) twoCB3S;
	}

	RooGenericPdf* Background;
	if(BkgSys) Background = (RooGenericPdf*) bkgCheb4;
	else Background = (RooGenericPdf*) bkgErf;
//}}}

//Set Parameters{{{
	sigma1S_1.setVal(sig11); //sigma1S_1.setConstant();
	//sigma1S_2.setVal(sig12); //sigma1S_2.setConstant();
	//sigma2S_1.setVal(sig21); //sigma2S_1.setConstant();
	//sigma2S_2.setVal(sig22); //sigma2S_2.setConstant();
	//sigma3S_1.setVal(sig31); //sigma3S_1.setConstant();
	//sigma3S_2.setVal(sig32); //sigma3S_2.setConstant();
	alpha.setVal(alp); //alpha.setConstant();
	n.setVal(N); //n.setConstant();
	frac->setVal(Frac); //frac->setConstant();

	if(BkgSys)
	{
		Chebp0.setVal(chebyp0);
		Chebp1.setVal(chebyp1);
		Chebp2.setVal(chebyp2);
		Chebp3.setVal(chebyp3);
		//Chebp4.setVal(chebyp4);
	}
	else
	{
		Erfmean.setVal(erfm); //Erfmean.setConstant(erfm);
		Erfsigma.setVal(erfsig); //Erfsigma.setConstant(erfsig);
		Erfp0.setVal(erfp0); //Erfp0.setConstant(erfp0);
	}
//}}}

//Draw mass plot{{{
	RooRealVar* nSig1S = new RooRealVar("nSig1S", "# of 1S signal", 400, -1000, 1000000);
	RooRealVar* nSig2S = new RooRealVar("nSig2S", "# of 2S signal", 100, -1000, 300000);
	RooRealVar* nSig3S = new RooRealVar("nSig3S", "# of 3S signal", 10, -1000, 90000);
	RooRealVar* nBkg = new RooRealVar("nBkg", "number of background", 300, -1000, 10000000);
	RooAddPdf* model = new RooAddPdf("model", "1S+2S+3S+Bkg", RooArgList(*Signal1S, *Signal2S, *Signal3S, *Background), RooArgList(*nSig1S, *nSig2S, *nSig3S, *nBkg));
	ws->import(*model);

	RooFitResult* Result = ws->pdf("model")->fitTo(*reducedDS, Save(), Hesse(kTRUE), Range(RangeLow, RangeHigh), Minos(0), SumW2Error(kTRUE), Extended(kTRUE));
	ws->pdf("model")->plotOn(massPlot, Name("modelPlot"));
	ws->pdf("model")->plotOn(massPlot, Name("Sgns"), Components(RooArgSet(*Signal1S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
	ws->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal2S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
	ws->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal3S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
	ws->pdf("model")->plotOn(massPlot, Name("bkgs"), Components(RooArgSet(*Background)), LineColor(kBlue), LineStyle(kDashed));
	massPlot->SetTitle(Form("twoCB"));
	massPlot->SetXTitle("M (GeV/c^{2})");
	massPlot->GetXaxis()->CenterTitle();
	massPlot->GetYaxis()->CenterTitle();
	massPlot->SetYTitle("Counts");
	massPlot->GetYaxis()->SetTitleOffset(1.5);
	massPlot->Draw();
	Result->Print("v");

	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 42, 0.04);
	lt1->DrawLatex(0.6,0.83, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
	lt1->DrawLatex(0.6,0.76, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
	lt1->DrawLatex(0.6,0.69, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int)ptMin, (int)ptMax));
	CMSP(0.12, 0.92);
	lumiText(0.64, 0.92); // 0.56, 0.92

	//TLegend *leg2 = new TLegend(0.4798607,0.2108508,0.7499645,0.3786851);
	//TLegend *leg2 = new TLegend(0.60,0.57,0.80,0.80);
	//TLegend *leg2 = new TLegend(0.62,0.45,0.80,0.60);
	TLegend *leg2 = new TLegend(0.59,0.40,0.80,0.62);
	leg2->SetFillStyle(0);
	leg2->SetFillColor(0);
	leg2->SetBorderSize(0);
	leg2->SetTextFont(43);
	leg2->SetTextSize(19);
	//leg2->SetTextSize(0.035);
	leg2->AddEntry(massPlot->findObject("massPlot"),"Data","pe");
	leg2->AddEntry(massPlot->findObject("modelPlot"),"Total fit","l");
	leg2->AddEntry(massPlot->findObject("Sgns"),"Signal","pl");
	leg2->AddEntry(massPlot->findObject("bkgs"),"Background","pl");
    leg2->Draw("same");


	WriteMessage("Fitting is Done !!!");
	//}}}
    
	//Draw pull distribution{{{
	pad_pull->cd();
	RooHist* hpull = massPlot->pullHist("massPlot", "modelPlot");
	RooPlot* pullPlot = ws->var("mass")->frame(Title("Pull Distribution"));
	pullPlot->addPlotable(hpull, "P");
	pullPlot->Draw();

	Double_t chi2 = 0.;
	Double_t *ypull = hpull->GetY();
	Double_t Npullbin = 0;
	for(Int_t ibin = 0; ibin < Nmassbins; ibin++)
	{
		if(ypull[ibin] == 0) continue;
		chi2 += TMath::Power(ypull[ibin], 2);
		Npullbin++;
	}
	Int_t Nfitpar = Result->floatParsFinal().getSize();
	Int_t ndf = Npullbin - Nfitpar;

	TLatex* NormChi2tex = new TLatex();
	FormLatex(NormChi2tex, 42, 0.10);
	NormChi2tex->DrawLatex(0.15, 0.95, Form("#chi^{2}/ndf: %3.f/%d", chi2, ndf));
	WriteMessage("Pull distribution is Done !!!");
//}}}

//Draw result values{{{
	pad_leg->cd();
	RooPlot* legPlot = ws->var("mass")->frame(Name("Fit Results"), Title("Fit Results"));
	RooArgList parList = Result->floatParsFinal();
	parList.Print("v");
	ws->pdf("model")->paramOn(legPlot, Layout(0, 0.93, 0.97), Parameters(parList));
	legPlot->getAttText()->SetTextAlign(11);
	legPlot->getAttText()->SetTextSize(0.09);

    /*
	TPaveText* Ptext = (TPaveText*) legPlot->findObject(Form("%s_paramBox", ws->pdf("model")->GetName()));
	Ptext->SetY1(0.01);
	Ptext->SetY2(0.95);
	//Ptext->Draw();
    */
	WriteMessage("Writing result is Done !!!");
//}}}

	if(Weight) c1->SaveAs(Form("MassDist/NoStatMassDistribution_mult_%d-%d_pt_%d-%d_rap_%d-%d_Data_%s_%dbin_Acc%o_Eff%o_TnP%s_SigSys%o_BkgSys%o_OS_MupT%s.pdf", multMin, multMax, (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), version.Data(), Nmassbins, isAccRW, isEffRW, TnPs.Data(), SigSys, BkgSys, MupT.Data()));
	else c1->SaveAs(Form("MassDist/NoStatMassDistribution_mult_%d-%d_pt_%d-%d_rap_%d-%d_Data_%s_%dbin_noWeight_OS_MupT%s.pdf", multMin, multMax, (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), version.Data(), Nmassbins, MupT.Data()));
	
	fout->cd();
	massPlot->Write();
	fout->Close();
}
