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

void GetYieldMC(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Int_t Generation = 1, TString version = "v1", TString MupT = "4")
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

//Define mass window{{{
	//const Int_t Nmassbins = 120;
	const Int_t Nmassbins = 150;
	Double_t RangeLow = 0;
	Double_t RangeHigh = 0;
	if(Generation == 1)
	{
		RangeLow = 8.5;
		RangeHigh = 10;
	}
	else if (Generation == 2)
	{
		RangeLow = 9.0;
		RangeHigh = 10.5;
	}
	else if (Generation == 3)
	{
		RangeLow = 9.5;
		RangeHigh = 11;
	}
//}}}

	TFile* fout = new TFile(Form("Yield/Yield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_MC_%dS_%s_MupT%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), Generation, version.Data(), MupT.Data()), "RECREATE");

//Define parameters{{{
	Double_t sig11;
	//Double_t sig11, sig12, sig21, sig22, sig31, sig32;
	Double_t Frac, alp, N;
	Double_t chevp0, chevp1;
//}}}

//Get parameter{{{
	ifstream in;
	in.open(Form("Parameter/Parameters_Mult_%d-%d_pt_%d-%d_rap_%d-%d_MC_%dS_%s_MupT%s.txt", multMin, multMax, (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Generation, version.Data(), MupT.Data()));
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
				in >> sig11 >> Frac >> alp >> N >> chevp0 >> chevp1;
			}
		}
	}
	in.close();
//}}}

//Get data{{{
	TFile* fin = new TFile(Form("Skim_OniaTree_MC_PADoubleMuon_%dS_MupT%s_official.root", Generation, MupT.Data()), "READ");
	//TFile* fin = new TFile(Form("Skim_OniaTree_MC_PADoubleMuon_1S_MupT%s_official_non-embedded.root", MupT.Data()), "READ");
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
	c1->cd();
	TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.98, 1.0);
	pad_mass->Draw();
	TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.05, 0.98, 0.25);
	pad_pull->SetBottomMargin(0);
	pad_pull->Draw();
	TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.15, 0.35, 0.35, 0.92);
	pad_leg->SetBottomMargin(0);
	pad_leg->Draw();

	TH1D* hYield = new TH1D("hYield", "", 3, 0, 3);
//}}}

	pad_mass->cd();
	RooPlot* massPlot = ws->var("mass")->frame(Nmassbins);
	ws->data("reducedDS")->plotOn(massPlot, Name("massPlot"));

//Signal function{{{

//mean
	Double_t U_mass = 0;
	if (Generation == 1) U_mass = U1S_mass;
	else if (Generation == 2) U_mass = U2S_mass;
	else if (Generation == 3) U_mass = U3S_mass;
	RooRealVar mean1S("mean1S", "mean of Upsilon 1S", U_mass, U_mass-0.01, U_mass+0.01);

//sigma
	RooRealVar sigma1S_1("sigma1S_1", "sigma1 of 1S", 0.05, 0.01, 0.3);
	RooRealVar* x1S = new RooRealVar("x1S", "sigma ratio", 0.35, 0, 1);
	RooFormulaVar sigma1S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_1, *x1S));

	RooRealVar alpha("alpha", "alpha of Crystal ball", 2.0, 0.5, 20.0); // for 1S
	RooRealVar n("n", "n of Crystal ball", 2.0, 0.5, 20.0); // for 1S
	//RooRealVar alpha("alpha", "alpha of Crystal ball", 1.6, 1.5, 1.7); // for 2S, 3S
	//RooRealVar n("n", "n of Crystal ball", 2.24, 2.2, 2.3); // for 2S, 3S
	RooRealVar* frac = new RooRealVar("frac", "CB fraction", 0.5, 0, 1);

//twoCB function
	RooCBShape* CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *(ws->var("mass")), mean1S, sigma1S_1, alpha, n);
	RooCBShape* CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *(ws->var("mass")), mean1S, sigma1S_2, alpha, n);

	RooAddPdf* twoCB1S = new RooAddPdf("twoCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2), RooArgList(*frac));
//}}}

//Background function{{{
	RooRealVar p0("p0", "1st parameter of bkg", 0.5, -1, 1);
	RooRealVar p1("p1", "2nd parameter of bkg", 0.5, -1, 1);
	RooChebychev* bkgch = new RooChebychev("bkgch", "Chebychev background", *(ws->var("mass")), RooArgList(p0, p1));
	//RooPolynomial* bkgch = new RooPolynomial("bkgch", "bkgch", *(ws->var("mass")), RooArgList());
//}}}

//Select Pdf{{{
	RooGenericPdf* Signal1S = (RooGenericPdf*) twoCB1S;
	RooGenericPdf* Background = (RooGenericPdf*) bkgch;
//}}}

//Set Parameters{{{
	sigma1S_1.setVal(sig11); //sigma1S_1.setConstant();
	alpha.setVal(alp); //alpha.setConstant();
	n.setVal(N); //n.setConstant();
	frac->setVal(Frac); //frac->setConstant();
	p0.setVal(chevp0);
	p1.setVal(chevp1);
//}}}

//Draw mass plot{{{
	RooRealVar* nSig = new RooRealVar("nSig", "# of signal", 400, -1000, 10000000);
	RooRealVar* nBkg = new RooRealVar("nBkg", "number of background", 300, -1000, 1000000);
	RooAddPdf* model = new RooAddPdf("model", "1S+Bkg", RooArgList(*Signal1S, *Background), RooArgList(*nSig, *nBkg));
	//RooAddPdf* model = new RooAddPdf("model", "1S", RooArgList(*Signal1S), RooArgList(*nSig1S));
	ws->import(*model);

	RooFitResult* Result = ws->pdf("model")->fitTo(*reducedDS, Save(), Hesse(kTRUE), Range(RangeLow, RangeHigh), Minos(0), SumW2Error(kTRUE), Extended(kTRUE));
	ws->pdf("model")->plotOn(massPlot, Name("modelPlot"));
	ws->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal1S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
	ws->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Background)), LineColor(kBlue), LineStyle(kDashed));
	massPlot->SetTitle(Form("twoCB"));
	massPlot->SetXTitle("M (GeV/c^2)");
	massPlot->SetYTitle("Counts");
	massPlot->Draw();
	Result->Print("v");
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
	FormLatex(NormChi2tex, 42, 0.13);
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

	TPaveText* Ptext = (TPaveText*) legPlot->findObject(Form("%s_paramBox", ws->pdf("model")->GetName()));
	Ptext->SetY1(0.01);
	Ptext->SetY2(0.95);
	Ptext->Draw();
	WriteMessage("Writing result is Done !!!");
//}}}

//Save Yield{{{
	Double_t Yield1S = ws->var("nSig")->getVal();
	Double_t Yield1SErr = ws->var("nSig")->getError();
	Double_t YieldBkg = ws->var("nBkg")->getVal();

	hYield->SetBinContent(1, Yield1S);
	hYield->SetBinError(1, Yield1SErr);
//}}}

//Save text{{{
	Double_t meanout = ws->var("mean1S")->getVal();
	Double_t sigma1out = sigma1out = ws->var("sigma1S_1")->getVal();
	Double_t sigma2out = (ws->var("x1S")->getVal())*sigma1out;
	Double_t fracout = ws->var("frac")->getVal();
	Double_t sigmaout = TMath::Sqrt(fracout*sigma1out*sigma1out+(1-fracout)*sigma2out*sigma2out);

	TF1* SgnfcnS = ws->pdf("twoCB1S")->asTF(*(ws->var("mass")));
	TF1* Bkgfc = ws->pdf("bkgch")->asTF(*(ws->var("mass")));

	Double_t TIntgrnS = SgnfcnS->Integral(RangeLow, RangeHigh);
	Double_t TIntgrBkg = Bkgfc->Integral(RangeLow, RangeHigh);
	Double_t IntgrSig = SgnfcnS->Integral(meanout-2*sigmaout, meanout+2*sigmaout);
	Double_t IntgrBkg = Bkgfc->Integral(meanout-2*sigmaout, meanout+2*sigmaout);

	FILE* ftxt;
	ftxt = fopen(Form("Parameter/Result_parameters_mult_%d-%d_pt_%d-%d_rap_%d-%d_MC_%dS_%s_MupT%s.txt", multMin, multMax, (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Generation, version.Data(), MupT.Data()), "w");
	if(ftxt != NULL)
	{
		fprintf(ftxt, "mean  sigma1  sigma2  fraction  totsigma  totsig  totbkg sig  bkg  nsig  nbkg  \n");
		fprintf(ftxt, "%.3f   %.3f   %.3f   %.3f   %.3f   %.3f   %.3f   %.3f   %.3f   %.3f   %.3f	\n", meanout, sigma1out, sigma2out, fracout, sigmaout, TIntgrnS, TIntgrBkg, IntgrSig, IntgrBkg, Yield1S, YieldBkg);
		//fprintf(ftxt, "mean  sigma1  sigma2  fraction  totsigma  totsig  sig  nsig  significance \n");
		fprintf(ftxt, "mean  U1sigma1  fraction  alpha  n  p0  p1 \n");
		fprintf(ftxt, "%.3f   %.3f   %.3f   %.3f   %.3f   %.3f  %.3f   \n", meanout, sigma1out, fracout, ws->var("alpha")->getVal(), ws->var("n")->getVal(), ws->var("p0")->getVal(), ws->var("p1")->getVal());
		//fprintf(ftxt, "mean  U1sigma1  fraction  alpha  n  \n");
		//fprintf(ftxt, "%.3f   %.3f   %.3f   %.3f   %.3f  \n", meanout, sigma1out, fracout, ws->var("alpha")->getVal(), ws->var("n")->getVal());
		fprintf(ftxt, "nSYield  BkgYield  nSIntgr  BkgTIntgr  \n");
		fprintf(ftxt, "%.3f   %.3f   %.3f   %.3f \n", Yield1S, YieldBkg, TIntgrnS, TIntgrBkg);
		//fprintf(ftxt, "1SYield  1SIntgr  \n");
		//fprintf(ftxt, "%.3f   %.3f   \n", Yield1S, TIntgr1S);
	}
//}}}

	c1->SaveAs(Form("MassDist/MassDistribution_mult_%d-%d_pt_%d-%d_rap_%d-%d_MC_%dS_%s_%dbin_MupT%s.pdf", multMin, multMax, (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Generation, version.Data(), Nmassbins, MupT.Data()));
	fout->cd();
	massPlot->Write();
	hYield->Write();
	TH1D* hmass = new TH1D("hmass", "", Nmassbins, RangeLow, RangeHigh);
	reducedDS->fillHistogram(hmass, (*ws->var("mass")));
	hmass->Write();
	SgnfcnS->Write();
}
