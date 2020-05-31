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
Int_t iparmass[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
							};
//Int_t iparvn[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
Int_t iparvn[25] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
						16, 17, 18, 19, 20, 21, 22, 23, 24};

struct GlobalChi2_width
{
	GlobalChi2_width(ROOT::Math::IMultiGenFunction & f1,
						ROOT::Math::IMultiGenFunction & f2):
	fChi2_1(&f1), fChi2_2(&f2) {}

	Double_t operator() (const double *par) const
	{
		Double_t p1[16];
		for(Int_t i = 0; i < 16; i++) p1[i] = par[iparmass[i]];
		Double_t p2[25];
		for(Int_t i = 0; i < 25; i++) p2[i] = par[iparvn[i]];
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
	Double_t N3 = par[2];
	Double_t N4 = par[3];
	Double_t mean = par[4];
	Double_t sigma = par[5];
	Double_t alpha = par[6];
	Double_t n = par[7];
	Double_t ratio = par[8];
	Double_t frac = par[9];
	Double_t Bkgmean = par[10];
	Double_t Bkgsigma = par[11];
	Double_t Bkgp0 = par[12];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;
//}}}

	//t2 > t1
	Double_t U1S_t1 = (x[0]-mean)/sigma;
	Double_t U1S_t2 = (x[0]-mean)/sigma1S_2;
	Double_t U2S_t1 = (x[0]-mean2)/sigma2S_1;
	Double_t U2S_t2 = (x[0]-mean2)/sigma2S_2;
	Double_t U3S_t1 = (x[0]-mean3)/sigma3S_1;
	Double_t U3S_t2 = (x[0]-mean3)/sigma3S_2;
	if (alpha < 0)
	{
		U1S_t1 = -U1S_t1;
		U1S_t2 = -U1S_t2;
		U2S_t1 = -U2S_t1;
		U2S_t2 = -U2S_t2;
		U3S_t1 = -U3S_t1;
		U3S_t2 = -U3S_t2;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;
	Double_t NC = n/absAlpha*1/(n-1)*exp(-absAlpha*absAlpha/2.);
	Double_t ND = TMath::Sqrt(TMath::Pi()/2.)*(1+TMath::Erf(absAlpha/TMath::Sqrt(2)));
	Double_t N1s_1 = 1./(sigma*(NC+ND));
	Double_t N1s_2 = 1./(sigma1S_2*(NC+ND));
	Double_t N2s_1 = 1./(sigma2S_1*(NC+ND));
	Double_t N2s_2 = 1./(sigma2S_2*(NC+ND));
	Double_t N3s_1 = 1./(sigma3S_1*(NC+ND));
	Double_t N3s_2 = 1./(sigma3S_2*(NC+ND));

//set value for cases{{{
	Double_t U1S_t1_val;
	Double_t U1S_t2_val;
	Double_t U2S_t1_val;
	Double_t U2S_t2_val;
	Double_t U3S_t1_val;
	Double_t U3S_t2_val;

	if(U1S_t1 >= -absAlpha) U1S_t1_val = exp(-U1S_t1*U1S_t1/2.);
	else U1S_t1_val = a/TMath::Power(b - U1S_t1, n);
	if(U1S_t2 >= -absAlpha) U1S_t2_val = exp(-U1S_t2*U1S_t2/2.);
	else U1S_t2_val = a/TMath::Power(b - U1S_t2, n);
	if(U2S_t1 >= -absAlpha) U2S_t1_val = exp(-U2S_t1*U2S_t1/2.);
	else U2S_t1_val = a/TMath::Power(b - U2S_t1, n);
	if(U2S_t2 >= -absAlpha) U2S_t2_val = exp(-U2S_t2*U2S_t2/2.);
	else U2S_t2_val = a/TMath::Power(b - U2S_t2, n);
	if(U3S_t1 >= -absAlpha) U3S_t1_val = exp(-U3S_t1*U3S_t1/2.);
	else U3S_t1_val = a/TMath::Power(b - U3S_t1, n);
	if(U3S_t2 >= -absAlpha) U3S_t2_val = exp(-U3S_t2*U3S_t2/2.);
	else U3S_t2_val = a/TMath::Power(b - U3S_t2, n);
//}}}

//final upsilon value{{{
	Double_t Sigtot = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val )
						+ N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val )
						+ N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Sig1S = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val );
	Double_t Sig2S = N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val );
	Double_t Sig3S = N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Bkgtot = N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
//}}}

	return Sigtot + Bkgtot;
}
//}}}

//totalvn error function bkg{{{
Double_t TotalvnerfU123S(Double_t* x, Double_t* par)
{
//define basic variables{{{
	Double_t N1 = par[0];
	Double_t N2 = par[1];
	Double_t N3 = par[2];
	Double_t N4 = par[3];
	Double_t mean = par[4];
	Double_t sigma = par[5];
	Double_t alpha = par[6];
	Double_t n = par[7];
	Double_t ratio = par[8];
	Double_t frac = par[9];
	Double_t Bkgmean = par[10];
	Double_t Bkgsigma = par[11];
	Double_t Bkgp0 = par[12];
	Double_t c1s = par[13];
	Double_t c2s = par[14];
	Double_t c3s = par[15];
	Double_t cbkg = par[16];
	Double_t emean = par[17];
	Double_t esigma = par[18];
	Double_t ep0 = par[19];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;
//}}}

	//t2 > t1
	Double_t U1S_t1 = (x[0]-mean)/sigma;
	Double_t U1S_t2 = (x[0]-mean)/sigma1S_2;
	Double_t U2S_t1 = (x[0]-mean2)/sigma2S_1;
	Double_t U2S_t2 = (x[0]-mean2)/sigma2S_2;
	Double_t U3S_t1 = (x[0]-mean3)/sigma3S_1;
	Double_t U3S_t2 = (x[0]-mean3)/sigma3S_2;
	if (alpha < 0)
	{
		U1S_t1 = -U1S_t1;
		U1S_t2 = -U1S_t2;
		U2S_t1 = -U2S_t1;
		U2S_t2 = -U2S_t2;
		U3S_t1 = -U3S_t1;
		U3S_t2 = -U3S_t2;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;
	Double_t NC = n/absAlpha*1/(n-1)*exp(-absAlpha*absAlpha/2.);
	Double_t ND = TMath::Sqrt(TMath::Pi()/2.)*(1+TMath::Erf(absAlpha/TMath::Sqrt(2)));
	Double_t N1s_1 = 1./(sigma*(NC+ND));
	Double_t N1s_2 = 1./(sigma1S_2*(NC+ND));
	Double_t N2s_1 = 1./(sigma2S_1*(NC+ND));
	Double_t N2s_2 = 1./(sigma2S_2*(NC+ND));
	Double_t N3s_1 = 1./(sigma3S_1*(NC+ND));
	Double_t N3s_2 = 1./(sigma3S_2*(NC+ND));

//set value for cases{{{
	Double_t U1S_t1_val;
	Double_t U1S_t2_val;
	Double_t U2S_t1_val;
	Double_t U2S_t2_val;
	Double_t U3S_t1_val;
	Double_t U3S_t2_val;

	if(U1S_t1 >= -absAlpha) U1S_t1_val = exp(-U1S_t1*U1S_t1/2.);
	else U1S_t1_val = a/TMath::Power(b - U1S_t1, n);
	if(U1S_t2 >= -absAlpha) U1S_t2_val = exp(-U1S_t2*U1S_t2/2.);
	else U1S_t2_val = a/TMath::Power(b - U1S_t2, n);
	if(U2S_t1 >= -absAlpha) U2S_t1_val = exp(-U2S_t1*U2S_t1/2.);
	else U2S_t1_val = a/TMath::Power(b - U2S_t1, n);
	if(U2S_t2 >= -absAlpha) U2S_t2_val = exp(-U2S_t2*U2S_t2/2.);
	else U2S_t2_val = a/TMath::Power(b - U2S_t2, n);
	if(U3S_t1 >= -absAlpha) U3S_t1_val = exp(-U3S_t1*U3S_t1/2.);
	else U3S_t1_val = a/TMath::Power(b - U3S_t1, n);
	if(U3S_t2 >= -absAlpha) U3S_t2_val = exp(-U3S_t2*U3S_t2/2.);
	else U3S_t2_val = a/TMath::Power(b - U3S_t2, n);
//}}}

//final upsilon value{{{
	Double_t Sigtot = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val ) 
						+ N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val ) 
						+ N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Sig1S = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val );
	Double_t Sig2S = N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val );
	Double_t Sig3S = N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Bkgtot = N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
//}}}

//return value{{{
	return c1s*( Sig1S/(Sigtot+Bkgtot) ) + c2s*( Sig2S/(Sigtot+Bkgtot) ) + c3s*( Sig3S/(Sigtot+Bkgtot) ) + 
			cbkg*( TMath::Exp(-x[0]/ep0)*(TMath::Erf((x[0]-emean)/(TMath::Sqrt(2)*esigma))+1)/2. )*(1-Sigtot/(Sigtot+Bkgtot));
//}}}
}
//}}}

//error function bkg{{{
Double_t erfbkg(Double_t* x, Double_t* par)
{
	Double_t cbkg = par[0];
	Double_t emean = par[1];
	Double_t esigma = par[2];
	Double_t ep0 = par[3];

	return cbkg*(TMath::Exp(-x[0]/ep0)*(TMath::Erf((x[0]-emean)/(TMath::Sqrt(2)*esigma))+1)/2.);
}
//}}}

//totalvn exp function bkg{{{
Double_t TotalvnexpU123S(Double_t* x, Double_t* par)
{
//define basic variables{{{
	Double_t N1 = par[0];
	Double_t N2 = par[1];
	Double_t N3 = par[2];
	Double_t N4 = par[3];
	Double_t mean = par[4];
	Double_t sigma = par[5];
	Double_t alpha = par[6];
	Double_t n = par[7];
	Double_t ratio = par[8];
	Double_t frac = par[9];
	Double_t Bkgmean = par[10];
	Double_t Bkgsigma = par[11];
	Double_t Bkgp0 = par[12];
	Double_t c1s = par[13];
	Double_t c2s = par[14];
	Double_t c3s = par[15];
	Double_t cbkg = par[16];
	Double_t emean = par[17];
	Double_t esigma = par[18];
	Double_t ec0 = par[19];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;
//}}}

	//t2 > t1
	Double_t U1S_t1 = (x[0]-mean)/sigma;
	Double_t U1S_t2 = (x[0]-mean)/sigma1S_2;
	Double_t U2S_t1 = (x[0]-mean2)/sigma2S_1;
	Double_t U2S_t2 = (x[0]-mean2)/sigma2S_2;
	Double_t U3S_t1 = (x[0]-mean3)/sigma3S_1;
	Double_t U3S_t2 = (x[0]-mean3)/sigma3S_2;
	if (alpha < 0)
	{
		U1S_t1 = -U1S_t1;
		U1S_t2 = -U1S_t2;
		U2S_t1 = -U2S_t1;
		U2S_t2 = -U2S_t2;
		U3S_t1 = -U3S_t1;
		U3S_t2 = -U3S_t2;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;
	Double_t NC = n/absAlpha*1/(n-1)*exp(-absAlpha*absAlpha/2.);
	Double_t ND = TMath::Sqrt(TMath::Pi()/2.)*(1+TMath::Erf(absAlpha/TMath::Sqrt(2)));
	Double_t N1s_1 = 1./(sigma*(NC+ND));
	Double_t N1s_2 = 1./(sigma1S_2*(NC+ND));
	Double_t N2s_1 = 1./(sigma2S_1*(NC+ND));
	Double_t N2s_2 = 1./(sigma2S_2*(NC+ND));
	Double_t N3s_1 = 1./(sigma3S_1*(NC+ND));
	Double_t N3s_2 = 1./(sigma3S_2*(NC+ND));

//set value for cases{{{
	Double_t U1S_t1_val;
	Double_t U1S_t2_val;
	Double_t U2S_t1_val;
	Double_t U2S_t2_val;
	Double_t U3S_t1_val;
	Double_t U3S_t2_val;

	if(U1S_t1 >= -absAlpha) U1S_t1_val = exp(-U1S_t1*U1S_t1/2.);
	else U1S_t1_val = a/TMath::Power(b - U1S_t1, n);
	if(U1S_t2 >= -absAlpha) U1S_t2_val = exp(-U1S_t2*U1S_t2/2.);
	else U1S_t2_val = a/TMath::Power(b - U1S_t2, n);
	if(U2S_t1 >= -absAlpha) U2S_t1_val = exp(-U2S_t1*U2S_t1/2.);
	else U2S_t1_val = a/TMath::Power(b - U2S_t1, n);
	if(U2S_t2 >= -absAlpha) U2S_t2_val = exp(-U2S_t2*U2S_t2/2.);
	else U2S_t2_val = a/TMath::Power(b - U2S_t2, n);
	if(U3S_t1 >= -absAlpha) U3S_t1_val = exp(-U3S_t1*U3S_t1/2.);
	else U3S_t1_val = a/TMath::Power(b - U3S_t1, n);
	if(U3S_t2 >= -absAlpha) U3S_t2_val = exp(-U3S_t2*U3S_t2/2.);
	else U3S_t2_val = a/TMath::Power(b - U3S_t2, n);
//}}}

//final upsilon value{{{
	Double_t Sigtot = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val ) 
						+ N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val ) 
						+ N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Sig1S = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val );
	Double_t Sig2S = N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val );
	Double_t Sig3S = N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Bkgtot = N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
//}}}

//return value{{{
	return c1s*( Sig1S/(Sigtot+Bkgtot) ) + c2s*( Sig2S/(Sigtot+Bkgtot) ) + c3s*( Sig3S/(Sigtot+Bkgtot) ) + 
			cbkg*( TMath::Exp((emean-x[0])/esigma) + ec0 )*(1-Sigtot/(Sigtot+Bkgtot));
//}}}
}
//}}}

//exp function bkg{{{
Double_t expbkg(Double_t* x, Double_t* par)
{
	Double_t cbkg = par[0];
	Double_t emean = par[1];
	Double_t esigma = par[2];
	Double_t ec0 = par[3];

	return cbkg*( TMath::Exp((emean-x[0])/esigma) + ec0 );
}
//}}}

//totalvn pol3 bkg Upsilon 123S{{{
Double_t Totalvnpol3U123S(Double_t* x, Double_t* par)
{
//define basic variables{{{
	Double_t N1 = par[0];
	Double_t N2 = par[1];
	Double_t N3 = par[2];
	Double_t N4 = par[3];
	Double_t mean = par[4];
	Double_t sigma = par[5];
	Double_t alpha = par[6];
	Double_t n = par[7];
	Double_t ratio = par[8];
	Double_t frac = par[9];
	Double_t Bkgmean = par[10];
	Double_t Bkgsigma = par[11];
	Double_t Bkgp0 = par[12];
	Double_t c1s = par[13];
	Double_t c2s = par[14];
	Double_t c3s = par[15];
	Double_t c1 = par[16];
	Double_t c2 = par[17];
	Double_t c3 = par[18];
	Double_t c4 = par[19];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;
//}}}

	//t2 > t1
	Double_t U1S_t1 = (x[0]-mean)/sigma;
	Double_t U1S_t2 = (x[0]-mean)/sigma1S_2;
	Double_t U2S_t1 = (x[0]-mean2)/sigma2S_1;
	Double_t U2S_t2 = (x[0]-mean2)/sigma2S_2;
	Double_t U3S_t1 = (x[0]-mean3)/sigma3S_1;
	Double_t U3S_t2 = (x[0]-mean3)/sigma3S_2;
	if (alpha < 0)
	{
		U1S_t1 = -U1S_t1;
		U1S_t2 = -U1S_t2;
		U2S_t1 = -U2S_t1;
		U2S_t2 = -U2S_t2;
		U3S_t1 = -U3S_t1;
		U3S_t2 = -U3S_t2;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;
	Double_t NC = n/absAlpha*1/(n-1)*exp(-absAlpha*absAlpha/2.);
	Double_t ND = TMath::Sqrt(TMath::Pi()/2.)*(1+TMath::Erf(absAlpha/TMath::Sqrt(2)));
	Double_t N1s_1 = 1./(sigma*(NC+ND));
	Double_t N1s_2 = 1./(sigma1S_2*(NC+ND));
	Double_t N2s_1 = 1./(sigma2S_1*(NC+ND));
	Double_t N2s_2 = 1./(sigma2S_2*(NC+ND));
	Double_t N3s_1 = 1./(sigma3S_1*(NC+ND));
	Double_t N3s_2 = 1./(sigma3S_2*(NC+ND));

//set value for cases{{{
	Double_t U1S_t1_val;
	Double_t U1S_t2_val;
	Double_t U2S_t1_val;
	Double_t U2S_t2_val;
	Double_t U3S_t1_val;
	Double_t U3S_t2_val;

	if(U1S_t1 >= -absAlpha) U1S_t1_val = exp(-U1S_t1*U1S_t1/2.);
	else U1S_t1_val = a/TMath::Power(b - U1S_t1, n);
	if(U1S_t2 >= -absAlpha) U1S_t2_val = exp(-U1S_t2*U1S_t2/2.);
	else U1S_t2_val = a/TMath::Power(b - U1S_t2, n);
	if(U2S_t1 >= -absAlpha) U2S_t1_val = exp(-U2S_t1*U2S_t1/2.);
	else U2S_t1_val = a/TMath::Power(b - U2S_t1, n);
	if(U2S_t2 >= -absAlpha) U2S_t2_val = exp(-U2S_t2*U2S_t2/2.);
	else U2S_t2_val = a/TMath::Power(b - U2S_t2, n);
	if(U3S_t1 >= -absAlpha) U3S_t1_val = exp(-U3S_t1*U3S_t1/2.);
	else U3S_t1_val = a/TMath::Power(b - U3S_t1, n);
	if(U3S_t2 >= -absAlpha) U3S_t2_val = exp(-U3S_t2*U3S_t2/2.);
	else U3S_t2_val = a/TMath::Power(b - U3S_t2, n);
//}}}

//final upsilon value{{{
	Double_t Sigtot = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val )
						+ N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val )
						+ N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Sig1S = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val );
	Double_t Sig2S = N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val );
	Double_t Sig3S = N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Bkgtot = N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
//}}}

//return value{{{
	return c1s*( Sig1S/(Sigtot+Bkgtot) ) + c2s*( Sig2S/(Sigtot+Bkgtot) ) + c3s*( Sig3S/(Sigtot+Bkgtot) )
			+ ( c1*x[0]*x[0]*x[0]+c2*x[0]*x[0]+c3*x[0]+c4 )*(1-Sigtot/(Sigtot+Bkgtot));
//}}}
}
//}}}

//pol3 bkg{{{
Double_t pol3bkg(Double_t* x, Double_t* par)
{
	Double_t c1 = par[0];
	Double_t c2 = par[1];
	Double_t c3 = par[2];
	Double_t c4 = par[3];

	return c1*x[0]*x[0]*x[0]+c2*x[0]*x[0]+c3*x[0]+c4;
}
//}}}

//totalvn pol2 bkg Upsilon 123S{{{
Double_t Totalvnpol2U123S(Double_t* x, Double_t* par)
{
//define basic variables{{{
	Double_t N1 = par[0];
	Double_t N2 = par[1];
	Double_t N3 = par[2];
	Double_t N4 = par[3];
	Double_t mean = par[4];
	Double_t sigma = par[5];
	Double_t alpha = par[6];
	Double_t n = par[7];
	Double_t ratio = par[8];
	Double_t frac = par[9];
	Double_t Bkgmean = par[10];
	Double_t Bkgsigma = par[11];
	Double_t Bkgp0 = par[12];
	Double_t c1s = par[13];
	Double_t c2s = par[14];
	Double_t c3s = par[15];
	Double_t c1 = par[16];
	Double_t c2 = par[17];
	Double_t c3 = par[18];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;
//}}}

	//t2 > t1
	Double_t U1S_t1 = (x[0]-mean)/sigma;
	Double_t U1S_t2 = (x[0]-mean)/sigma1S_2;
	Double_t U2S_t1 = (x[0]-mean2)/sigma2S_1;
	Double_t U2S_t2 = (x[0]-mean2)/sigma2S_2;
	Double_t U3S_t1 = (x[0]-mean3)/sigma3S_1;
	Double_t U3S_t2 = (x[0]-mean3)/sigma3S_2;
	if (alpha < 0)
	{
		U1S_t1 = -U1S_t1;
		U1S_t2 = -U1S_t2;
		U2S_t1 = -U2S_t1;
		U2S_t2 = -U2S_t2;
		U3S_t1 = -U3S_t1;
		U3S_t2 = -U3S_t2;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;
	Double_t NC = n/absAlpha*1/(n-1)*exp(-absAlpha*absAlpha/2.);
	Double_t ND = TMath::Sqrt(TMath::Pi()/2.)*(1+TMath::Erf(absAlpha/TMath::Sqrt(2)));
	Double_t N1s_1 = 1./(sigma*(NC+ND));
	Double_t N1s_2 = 1./(sigma1S_2*(NC+ND));
	Double_t N2s_1 = 1./(sigma2S_1*(NC+ND));
	Double_t N2s_2 = 1./(sigma2S_2*(NC+ND));
	Double_t N3s_1 = 1./(sigma3S_1*(NC+ND));
	Double_t N3s_2 = 1./(sigma3S_2*(NC+ND));

//set value for cases{{{
	Double_t U1S_t1_val;
	Double_t U1S_t2_val;
	Double_t U2S_t1_val;
	Double_t U2S_t2_val;
	Double_t U3S_t1_val;
	Double_t U3S_t2_val;

	if(U1S_t1 >= -absAlpha) U1S_t1_val = exp(-U1S_t1*U1S_t1/2.);
	else U1S_t1_val = a/TMath::Power(b - U1S_t1, n);
	if(U1S_t2 >= -absAlpha) U1S_t2_val = exp(-U1S_t2*U1S_t2/2.);
	else U1S_t2_val = a/TMath::Power(b - U1S_t2, n);
	if(U2S_t1 >= -absAlpha) U2S_t1_val = exp(-U2S_t1*U2S_t1/2.);
	else U2S_t1_val = a/TMath::Power(b - U2S_t1, n);
	if(U2S_t2 >= -absAlpha) U2S_t2_val = exp(-U2S_t2*U2S_t2/2.);
	else U2S_t2_val = a/TMath::Power(b - U2S_t2, n);
	if(U3S_t1 >= -absAlpha) U3S_t1_val = exp(-U3S_t1*U3S_t1/2.);
	else U3S_t1_val = a/TMath::Power(b - U3S_t1, n);
	if(U3S_t2 >= -absAlpha) U3S_t2_val = exp(-U3S_t2*U3S_t2/2.);
	else U3S_t2_val = a/TMath::Power(b - U3S_t2, n);
//}}}

//final upsilon value{{{
	Double_t Sigtot = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val )
						+ N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val )
						+ N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Sig1S = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val );
	Double_t Sig2S = N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val );
	Double_t Sig3S = N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Bkgtot = N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
//}}}

//return value{{{
	return c1s*( Sig1S/(Sigtot+Bkgtot) ) + c2s*( Sig2S/(Sigtot+Bkgtot) ) + c3s*( Sig3S/(Sigtot+Bkgtot) )
			+ ( c1*x[0]*x[0]+c2*x[0]+c3 )*( 1-Sigtot/(Sigtot+Bkgtot) );
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

//totalvn pol1 bkg Upsilon 123S{{{
Double_t Totalvnpol1U123S(Double_t* x, Double_t* par)
{
//define basic variables{{{
	Double_t N1 = par[0];
	Double_t N2 = par[1];
	Double_t N3 = par[2];
	Double_t N4 = par[3];
	Double_t mean = par[4];
	Double_t sigma = par[5];
	Double_t alpha = par[6];
	Double_t n = par[7];
	Double_t ratio = par[8];
	Double_t frac = par[9];
	Double_t Bkgmean = par[10];
	Double_t Bkgsigma = par[11];
	Double_t Bkgp0 = par[12];
	Double_t c1s = par[13];
	Double_t c2s = par[14];
	Double_t c3s = par[15];
	Double_t c1 = par[16];
	Double_t c2 = par[17];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;
//}}}

	//t2 > t1
	Double_t U1S_t1 = (x[0]-mean)/sigma;
	Double_t U1S_t2 = (x[0]-mean)/sigma1S_2;
	Double_t U2S_t1 = (x[0]-mean2)/sigma2S_1;
	Double_t U2S_t2 = (x[0]-mean2)/sigma2S_2;
	Double_t U3S_t1 = (x[0]-mean3)/sigma3S_1;
	Double_t U3S_t2 = (x[0]-mean3)/sigma3S_2;
	if (alpha < 0)
	{
		U1S_t1 = -U1S_t1;
		U1S_t2 = -U1S_t2;
		U2S_t1 = -U2S_t1;
		U2S_t2 = -U2S_t2;
		U3S_t1 = -U3S_t1;
		U3S_t2 = -U3S_t2;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;
	Double_t NC = n/absAlpha*1/(n-1)*exp(-absAlpha*absAlpha/2.);
	Double_t ND = TMath::Sqrt(TMath::Pi()/2.)*(1+TMath::Erf(absAlpha/TMath::Sqrt(2)));
	Double_t N1s_1 = 1./(sigma*(NC+ND));
	Double_t N1s_2 = 1./(sigma1S_2*(NC+ND));
	Double_t N2s_1 = 1./(sigma2S_1*(NC+ND));
	Double_t N2s_2 = 1./(sigma2S_2*(NC+ND));
	Double_t N3s_1 = 1./(sigma3S_1*(NC+ND));
	Double_t N3s_2 = 1./(sigma3S_2*(NC+ND));

//set value for cases{{{
	Double_t U1S_t1_val;
	Double_t U1S_t2_val;
	Double_t U2S_t1_val;
	Double_t U2S_t2_val;
	Double_t U3S_t1_val;
	Double_t U3S_t2_val;

	if(U1S_t1 >= -absAlpha) U1S_t1_val = exp(-U1S_t1*U1S_t1/2.);
	else U1S_t1_val = a/TMath::Power(b - U1S_t1, n);
	if(U1S_t2 >= -absAlpha) U1S_t2_val = exp(-U1S_t2*U1S_t2/2.);
	else U1S_t2_val = a/TMath::Power(b - U1S_t2, n);
	if(U2S_t1 >= -absAlpha) U2S_t1_val = exp(-U2S_t1*U2S_t1/2.);
	else U2S_t1_val = a/TMath::Power(b - U2S_t1, n);
	if(U2S_t2 >= -absAlpha) U2S_t2_val = exp(-U2S_t2*U2S_t2/2.);
	else U2S_t2_val = a/TMath::Power(b - U2S_t2, n);
	if(U3S_t1 >= -absAlpha) U3S_t1_val = exp(-U3S_t1*U3S_t1/2.);
	else U3S_t1_val = a/TMath::Power(b - U3S_t1, n);
	if(U3S_t2 >= -absAlpha) U3S_t2_val = exp(-U3S_t2*U3S_t2/2.);
	else U3S_t2_val = a/TMath::Power(b - U3S_t2, n);
//}}}

//final upsilon value{{{
	Double_t Sigtot = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val )
						+ N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val )
						+ N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Sig1S = N1*( frac*N1s_1*U1S_t1_val + (1-frac)*N1s_2*U1S_t2_val );
	Double_t Sig2S = N2*( frac*N2s_1*U2S_t1_val + (1-frac)*N2s_2*U2S_t2_val );
	Double_t Sig3S = N3*( frac*N3s_1*U3S_t1_val + (1-frac)*N3s_2*U3S_t2_val );
	Double_t Bkgtot = N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
//}}}

//return value{{{
	return c1s*( Sig1S/(Sigtot+Bkgtot) ) + c2s*( Sig2S/(Sigtot+Bkgtot) ) + c3s*( Sig3S/(Sigtot+Bkgtot) )
			+ ( c1*x[0]+c2 )*(1-Sigtot/(Sigtot+Bkgtot));
//}}}
}
//}}}

//pol1 bkg{{{
Double_t pol1bkg(Double_t* x, Double_t* par)
{
	Double_t c1 = par[0];
	Double_t c2 = par[1];

	return c1*x[0]+c2;
}
//}}}

//}}}

void SimultaneousFitData(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Int_t bkgN = 0, const Int_t AwayN = 1, const Bool_t isfine = true, const TString version = "v13", const TString MupT = "4", const bool Weight = true)
{
	SetStyle();
	gStyle->SetOptFit(0000);
	const Double_t RangeMin = 8.;
	const Double_t RangeMax = 14.;

//set fitting condition name{{{
	TString bkgF;
	if(bkgN == 0) bkgF = "exp";
	else if(bkgN == 1) bkgF = "pol1";
	else if(bkgN == 2) bkgF = "pol2";
	else if(bkgN == 3) bkgF = "pol3";
	else if(bkgN == 4) bkgF = "erf";
	else
	{
		cout << "out of background list" << endl;
		return;
	}
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
	fout = new TFile(Form("V2Dist/V2File/%s/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_Data_%s_MupT%s_weight%o%s.root", version.Data(), multMin, multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Away.Data(), Fine.Data(), version.Data(), MupT.Data(), Weight, Ffit.Data()), "RECREATE");
	fout->cd();

	TF1* fyieldtot[pt_narr-1];
	TF1* fvntot[pt_narr-1];
	Double_t v2_1s[pt_narr-1];
	Double_t v2_1sE[pt_narr-1];
	Double_t v2_2s[pt_narr-1];
	Double_t v2_2sE[pt_narr-1];
	Double_t v2_3s[pt_narr-1];
	Double_t v2_3sE[pt_narr-1];
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
	//hist->SetMinimum(-0.05);
	//hist->SetMaximum(0.3);
	//hist->SetMinimum(-0.35);//for 110~300
	//hist->SetMaximum(0.35);//for 110~300
	hist->SetMinimum(-0.35);//for 0~40
	hist->SetMaximum(2.5);//for 0~40
//}}}

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
//Get yield distribution{{{
		TFile* fyield = new TFile(Form("../SkimmedFiles/Yield/Yield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Data_%s_weight%o_MupT%s.root", multMin, multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), version.Data(), Weight, MupT.Data()), "READ");
		TH1D* hyield = (TH1D*) fyield->Get(Form("hmass"));
		hyield->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
		hyield->GetYaxis()->SetTitle("Entries");
		FormTH1Marker(hyield, 0, 0, 1.4);

		c1[ipt]->cd(1);
		hyield->Draw();
		cout << "mass hist: " << hyield << endl;
//}}}

//Get fitting parameter{{{
		string char1, char2, char3, char4, char5, char6, char7, char8;
		string char9, char10, char11, char12, char13, char14, char15; 
		string char16, char17, char18, char19, char20, char21, char22; 
		string char23, char24, char25, char26, char27, char28;
		Double_t var1, var2, var3, var4, var5, var6, var7, var8, var9;
		Double_t var10, var11, var12, var13, var14, var15, var16, var17;
		Double_t var18, var19, var20, var21, var22, var23, var24, var25;
		Double_t var26, var27, var28;

		ifstream in1;
		in1.open(Form("../SkimmedFiles/Parameter/Result_parameters_mult_%d-%d_pt_%d-%d_rap_%d-%d_Data_%s_weight%o_MupT%s.txt", multMin, multMax, (int)(10*ptBinsArr[ipt]), (int)(10*ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), version.Data(), Weight, MupT.Data()));
		if(in1.is_open())
		{
			in1 >> char1 >> char2 >> char3 >> char4 >> char5 >> char6 >> 
					char7 >> char8 >> char9 >> char10 >> char11 >> char12; 
			in1 >> var1 >> var2 >> var3 >> var4 >> var5 >> var6 >> 
					var7 >> var8 >> var9 >> var10 >> var11 >> var12;
			in1 >> char13 >> char14 >> char15 >> char16 >> char17 >> 
					char18 >> char19 >> char20;
			in1 >> var13 >> var14 >> var15 >> var16 >> var17 >> var18 >> 
					var19 >> var20;
			in1 >> char21 >> char22 >> char23 >> char24 >> char25 >> char26 >>
					char27 >> char28;
			in1 >> var21 >> var22 >> var23 >> var24 >> var25 >> var26 >>
					var27 >> var28;
		}
		in1.close();

		cout << "input mass fit value: " << var13 << endl;

		Double_t bpar1, bpar2, bpar3, bpar4, bpar5;
		ifstream in2;
		in2.open(Form("Parameter/v2_bkg_%s_par_mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_weight%o_MupT%s.txt", bkgF.Data(), multMin, multMax, (int)(10*ptBinsArr[ipt]), (int)(10*ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), Weight, MupT.Data()));
		if(in2.is_open())
		{
			in2 >> bpar1 >> bpar2 >> bpar3 >> bpar4 >> bpar5;
		}
		in2.close();

		cout << "input v2 fit value: " << bpar1 << endl;
//}}}

//Get vn distribution{{{
		TFile* fvn;
		fvn = new TFile(Form("../SubtractTrk/V2File/%s/v2_sig_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_MupT%s_weight%o%s.root", version.Data(), multMin, multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Weight, Ffit.Data()), "READ");

		TGraphErrors* gvn;
		if(isfine == true) gvn = (TGraphErrors*) fvn->Get(Form("gv2_Away%s_fine", Away.Data()));
		else gvn = (TGraphErrors*) fvn->Get(Form("gv2_Away%s_coarse", Away.Data()));
		c1[ipt]->cd(2);
		cout << "v2 hist: " << gvn << endl;
//		gvn->Draw();
//}}}

//define function for simultaneous fitting{{{
		TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), TotalYield, RangeMin, RangeMax, 13);
		TF1* fvn_simul;

		if(bkgN == 0) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), TotalvnexpU123S, RangeMin, RangeMax, 20);
		else if(bkgN == 1) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Totalvnpol1U123S, RangeMin, RangeMax, 18);
		else if(bkgN == 2) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Totalvnpol2U123S, RangeMin, RangeMax, 19);
		else if(bkgN == 3) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Totalvnpol3U123S, RangeMin, RangeMax, 20);
		else if(bkgN == 4) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), TotalvnerfU123S, RangeMin, RangeMax, 20);
		else
		{
			cout << "Out of background function list" << endl;
			return;
		}

		//fvn_simul = new TF1(Form("fvn_simul_%d", ipt), "[13]*x+[14]", RangeMin, RangeMax);
		//fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Sample, RangeMin, RangeMax, 15);
//		fvn_simul->Draw();
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
		//par0[1] = 2S const
		//par0[2] = 3S const
		//par0[3] = Erf const
		//par0[4] = 1S mean
		//par0[5] = 1S sigma
		//par0[6] = alpha
		//par0[7] = n
		//par0[8] = ratio
		//par0[9] = two crystal ball fraction
		//par0[10] = Erf mean
		//par0[11] = Erf sigma
		//par0[12] = Erf p0
		//par0[13] = 1s signal v2 component
		//par0[14] = 2s signal v2 component
		//par0[15] = 3s signal v2 component
		//par0[16~] = background v2 components

		const Int_t Npar = 22;
		Double_t par0[Npar];
		par0[0] = var21/10.;
		par0[1] = var22/10.;
		par0[2] = var23/10.;
		par0[3] = var24/10.;
		par0[4] = var13;
		par0[5] = var14;
		par0[6] = var16;
		par0[7] = var17;
		par0[8] = var3/var2;
		par0[9] = var15;
		par0[10] = var18;
		par0[11] = var19;
		par0[12] = var20;
		par0[13] = 0.001;
		par0[14] = 0.001;
		par0[15] = 0.001;
		par0[16] = bpar1;
		par0[17] = bpar2;
		par0[18] = bpar3;
		par0[19] = bpar4;
//}}}

//fit{{{

//combined function condition{{{
		c1[ipt]->cd(2);
		hist->Draw();
		fitter.Config().SetParamsSettings(Npar, par0);
		fitter.Config().ParSettings(4).Fix();
		fitter.Config().ParSettings(5).Fix();
		fitter.Config().ParSettings(6).Fix();
		fitter.Config().ParSettings(7).Fix();
		fitter.Config().ParSettings(8).Fix();
		fitter.Config().ParSettings(9).Fix();
		fitter.Config().ParSettings(10).Fix();
		fitter.Config().ParSettings(11).Fix();
		fitter.Config().ParSettings(12).Fix();
		//fitter.Config().ParSettings(10).SetLimits(0, 20);
		//fitter.Config().ParSettings(11).SetLimits(0, 40);
		//fitter.Config().ParSettings(12).SetLimits(0, 100);
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

		TF1* fyield_bkg = new TF1(Form("fyield_bkg_%d", ipt), "[0]*( TMath::Exp(-x/[3])*(TMath::Erf((x-[1])/(TMath::Sqrt(2)*[2]))+1)/2. )", RangeMin, RangeMax);
		fyield_bkg->FixParameter(0, fyield_simul->GetParameter(3));
		fyield_bkg->FixParameter(1, fyield_simul->GetParameter(10));
		fyield_bkg->FixParameter(2, fyield_simul->GetParameter(11));
		fyield_bkg->FixParameter(3, fyield_simul->GetParameter(12));

		fyield_bkg->SetLineColor(kBlue);
		fyield_bkg->SetLineWidth(1);
		hyield->GetListOfFunctions()->Add(fyield_bkg);
//}}}

//vn fitting result{{{
		fvn_simul->SetFitResult(result, iparvn);
		fvn_simul->SetRange(vnrange().first, vnrange().second);
		fvn_simul->SetLineColor(2);

		TF1* fvn_bkg;
		if(bkgN == 0)
		{
			fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), expbkg, RangeMin, RangeMax, 4);
			fvn_bkg->FixParameter(0, fvn_simul->GetParameter(16));
			fvn_bkg->FixParameter(1, fvn_simul->GetParameter(17));
			fvn_bkg->FixParameter(2, fvn_simul->GetParameter(18));
			fvn_bkg->FixParameter(3, fvn_simul->GetParameter(19));
		}
		else if(bkgN == 1)
		{
			fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), pol1bkg, RangeMin, RangeMax, 2);
			fvn_bkg->FixParameter(0, fvn_simul->GetParameter(16));
			fvn_bkg->FixParameter(1, fvn_simul->GetParameter(17));
		}
		else if(bkgN == 2)
		{
			fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), pol2bkg, RangeMin, RangeMax, 3);
			fvn_bkg->FixParameter(0, fvn_simul->GetParameter(16));
			fvn_bkg->FixParameter(1, fvn_simul->GetParameter(17));
			fvn_bkg->FixParameter(2, fvn_simul->GetParameter(18));
		}
		else if(bkgN == 3)
		{
			fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), pol3bkg, RangeMin, RangeMax, 4);
			fvn_bkg->FixParameter(0, fvn_simul->GetParameter(16));
			fvn_bkg->FixParameter(1, fvn_simul->GetParameter(17));
			fvn_bkg->FixParameter(2, fvn_simul->GetParameter(18));
			fvn_bkg->FixParameter(3, fvn_simul->GetParameter(19));
		}
		else if(bkgN == 4)
		{
			fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), erfbkg, RangeMin, RangeMax, 4);
			fvn_bkg->FixParameter(0, fvn_simul->GetParameter(16));
			fvn_bkg->FixParameter(1, fvn_simul->GetParameter(17));
			fvn_bkg->FixParameter(1, fvn_simul->GetParameter(18));
			fvn_bkg->FixParameter(1, fvn_simul->GetParameter(19));
		}
		else
		{
			cout << "Out of background function list" << endl;
			return;
		}

		c1[ipt]->cd(2);
		hist->SetMaximum(1.0);
		fvn_bkg->SetLineColor(kMagenta);
		fvn_bkg->SetLineWidth(1);

		gvn->GetListOfFunctions()->Add(fvn_simul);
		gvn->GetListOfFunctions()->Add(fvn_bkg);
		gvn->SetTitle("");
		gvn->SetMarkerSize(0.8);
		gvn->SetLineWidth(1);
		gvn->Draw("PESAME");

		FILE* ftxt;
		ftxt = fopen(Form("Parameter/Obv2_bkg_%s_par_mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_weight%o_MupT%s.txt", bkgF.Data(), multMin, multMax, (int)(ptBinsArr[ipt]*10), (int)(ptBinsArr[ipt+1]*10), (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), Weight, MupT.Data()), "w");
		if(ftxt != NULL)
		{
			fprintf(ftxt, "%f   %f   %f   %f \n", fvn_simul->GetParameter(16), fvn_simul->GetParameter(17), fvn_simul->GetParameter(18), fvn_simul->GetParameter(19));
		}
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

		v2_1s[ipt] = fvn_simul->GetParameter(13);
		v2_1sE[ipt] = fvn_simul->GetParError(13);
		v2_2s[ipt] = fvn_simul->GetParameter(14);
		v2_2sE[ipt] = fvn_simul->GetParError(14);
		v2_3s[ipt] = fvn_simul->GetParameter(15);
		v2_3sE[ipt] = fvn_simul->GetParError(15);

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
		lt1->DrawLatex(0.52, 0.83, Form("p_{T}^{#mu} < %.1f GeV/c", MupTCut));
		lt1->DrawLatex(0.52, 0.78, Form("%d #leq p_{T}^{#varUpsilon} < %d GeV/c", (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1]));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.52,0.73, Form("0.3 #leq p_{T}^{trk} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.52,0.73, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.52, 0.68, "|#Delta#eta^{trk}| > 1.0");
		lt1->DrawLatex(0.52, 0.63, Form("Chi2/ndf = %.f/%d", Chi2Yield, NdfYield));

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
		lt1->DrawLatex(0.5, 0.38, Form("Chi2/ndf = %.f/%d", Chi2v2, Ndfv2));
//}}}

	}

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		c1[ipt]->SaveAs(Form("V2Dist/SigV2/%s/MupT%s/Away%s/Combined_fit_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_Data_%s_MupT%s_weight%o%s.pdf", version.Data(), MupT.Data(), Away.Data(), multMin, multMax, (int)(ptBinsArr[ipt]*10), (int)(ptBinsArr[ipt+1]*10), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Away.Data(), Fine.Data(), version.Data(), MupT.Data(), Weight, Ffit.Data()));
	}

	TGraphErrors* v2_1splot = new TGraphErrors(pt_narr-1, pt, v2_1s, 0, v2_1sE);
	v2_1splot->SetTitle("");
	v2_1splot->SetName("v2_1s_vs_pt");
	TGraphErrors* v2_2splot = new TGraphErrors(pt_narr-1, pt, v2_2s, 0, v2_2sE);
	v2_2splot->SetTitle("");
	v2_2splot->SetName("v2_2s_vs_pt");
	TGraphErrors* v2_3splot = new TGraphErrors(pt_narr-1, pt, v2_3s, 0, v2_3sE);
	v2_3splot->SetTitle("");
	v2_3splot->SetName("v2_3s_vs_pt");

	v2_1splot->Write();
	v2_2splot->Write();
	v2_3splot->Write();
}
