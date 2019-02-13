//Headers{{{
#include <TROOT.h>
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

#include "Upsilon.h"
#include "Style_Upv2.h"
//}}}

//external function{{{

//Chi2 calculation{{{
Int_t iparmass[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
//Int_t iparvn[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
Int_t iparvn[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

struct GlobalChi2_width
{
	GlobalChi2_width(ROOT::Math::IMultiGenFunction & f1,
						ROOT::Math::IMultiGenFunction & f2):
	fChi2_1(&f1), fChi2_2(&f2) {}

	Double_t operator() (const double *par) const
	{
		Double_t p1[13];
		for(Int_t i = 0; i < 13; i++) p1[i] = par[iparmass[i]];
		Double_t p2[18];
		for(Int_t i = 0; i < 18; i++) p2[i] = par[iparvn[i]];
		return (*fChi2_1)(p1) + (*fChi2_2)(p2);
	}
	const ROOT::Math::IMultiGenFunction * fChi2_1;
	const ROOT::Math::IMultiGenFunction * fChi2_2;
};
//}}}

//totalYield{{{
Double_t TotalYield(Double_t* x, Double_t* par)
{
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
	Double_t sigma1_2 = sigma*ratio;
	Double_t sigma2_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3_2 = sigma*ratio*U3S_mass/U1S_mass;

	//t2 > t1
	Double_t U1S_t1 = (x[0]-mean)/sigma;
	Double_t U1S_t2 = (x[0]-mean)/sigma1_2;
	Double_t U2S_t1 = (x[0]-mean2)/sigma2_1;
	Double_t U2S_t2 = (x[0]-mean2)/sigma2_2;
	Double_t U3S_t1 = (x[0]-mean3)/sigma3_1;
	Double_t U3S_t2 = (x[0]-mean3)/sigma3_2;
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

	if(U3S_t1 >= -absAlpha)
	{
		return N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( exp(-U3S_t1*U3S_t1/2.) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(U3S_t1 < -absAlpha && U3S_t2 >= -absAlpha)
	{
		return N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(U3S_t2 < -absAlpha && U2S_t1 >= -absAlpha)
	{
		return N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(U2S_t1 < -absAlpha && U2S_t2 >= -absAlpha)
	{
		return N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(U2S_t2 < -absAlpha && U1S_t1 >= -absAlpha)
	{
		return N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(U1S_t1 < -absAlpha && U2S_t1 >= -absAlpha)
	{
		return N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else
	{
		return N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
}
//}}}

//totalvn exp bkg Upsilon 1S{{{
Double_t TotalvnexpU1S(Double_t* x, Double_t* par)
{
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
	Double_t c = par[13];
	Double_t d = par[14];
	Double_t em = par[15];
	Double_t es = par[16];
	Double_t ep = par[17];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;

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

	if(U1S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U1S_t1 <= -absAlpha && U1S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
}
//}}}

//totalvn exp bkg Upsilon 12S{{{
Double_t TotalvnexpU12S(Double_t* x, Double_t* par)
{
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
	Double_t c = par[13];
	Double_t d = par[14];
	Double_t em = par[15];
	Double_t es = par[16];
	Double_t ep = par[17];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;

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

	if(U2S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U2S_t1 <= -absAlpha && U2S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U2S_t2 <= -absAlpha && U1S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U1S_t1 <= -absAlpha && U1S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
}
//}}}

//totalvn exp bkg Upsilon 123S{{{
Double_t TotalvnexpU123S(Double_t* x, Double_t* par)
{
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
	Double_t c = par[13];
	Double_t d = par[14];
	Double_t em = par[15];
	Double_t es = par[16];
	Double_t ep = par[17];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;

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

	if(U3S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( exp(-U3S_t1*U3S_t1/2.) + frac*exp(-U3S_t2*U3S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( exp(-U3S_t1*U3S_t1/2.) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( exp(-U3S_t1*U3S_t1/2.) + frac*exp(-U3S_t2*U3S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( exp(-U3S_t1*U3S_t1/2.) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U3S_t1 <= -absAlpha && U3S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*exp(-U3S_t2*U3S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*exp(-U3S_t2*U3S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U3S_t2 <= -absAlpha && U2S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U2S_t1 <= -absAlpha && U2S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U2S_t2 <= -absAlpha && U1S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U1S_t1 <= -absAlpha && U1S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
}
//}}}

//exp bkg{{{
Double_t expbkg(Double_t* x, Double_t* par)
{
	Double_t d = par[0];
	Double_t em = par[1];
	Double_t es = par[2];
	Double_t ep = par[3];

	return d*(TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2.);
}
//}}}

//totalvn pol2 bkg Upsilon 1S{{{
Double_t Totalvnpol2U1S(Double_t* x, Double_t* par)
{
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
	Double_t c = par[13];
	Double_t c1 = par[14];
	Double_t c2 = par[15];
	Double_t c3 = par[16];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;

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

	if(U1S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U1S_t1 <= -absAlpha && U1S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
}
//}}}

//totalvn pol2 bkg Upsilon 12S{{{
Double_t Totalvnpol2U12S(Double_t* x, Double_t* par)
{
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
	Double_t c = par[13];
	Double_t c1 = par[14];
	Double_t c2 = par[15];
	Double_t c3 = par[16];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;

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

	if(U2S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U2S_t1 <= -absAlpha && U2S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U2S_t2 <= -absAlpha && U1S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U1S_t1 <= -absAlpha && U1S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
}
//}}}

//totalvn pol2 bkg Upsilon 123S{{{
Double_t Totalvnpol2U123S(Double_t* x, Double_t* par)
{
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
	Double_t c = par[13];
	Double_t c1 = par[14];
	Double_t c2 = par[15];
	Double_t c3 = par[16];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1S_2 = sigma*ratio;
	Double_t sigma2S_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2S_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3S_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3S_2 = sigma*ratio*U3S_mass/U1S_mass;

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

	if(U3S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( exp(-U3S_t1*U3S_t1/2.) + frac*exp(-U3S_t2*U3S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( exp(-U3S_t1*U3S_t1/2.) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( exp(-U3S_t1*U3S_t1/2.) + frac*exp(-U3S_t2*U3S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( exp(-U3S_t1*U3S_t1/2.) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U3S_t1 <= -absAlpha && U3S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*exp(-U3S_t2*U3S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*exp(-U3S_t2*U3S_t2/2.) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*exp(-U3S_t2*U3S_t2/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U3S_t2 <= -absAlpha && U2S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( exp(-U2S_t1*U2S_t1/2.) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U2S_t1 <= -absAlpha && U2S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*exp(-U2S_t2*U2S_t2/2.) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U2S_t2 <= -absAlpha && U1S_t1 > -absAlpha)
	{
//{{{
		return c*( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( exp(-U1S_t1*U1S_t1/2.) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(U1S_t1 <= -absAlpha && U1S_t2 > -absAlpha)
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*exp(-U1S_t2*U1S_t2/2.) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else
	{
//{{{
		return c*( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( c1*x[0]*x[0]+c2*x[0]+c3 )
				*( 1 - ( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) ) )/
				( N1*( a/TMath::Power(b - U1S_t1, n) + frac*a/TMath::Power(b - U1S_t2, n) )
				+ N2*( a/TMath::Power(b - U2S_t1, n) + frac*a/TMath::Power(b - U2S_t2, n) )
				+ N3*( a/TMath::Power(b - U3S_t1, n) + frac*a/TMath::Power(b - U3S_t2, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
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

void SimultaneousFit(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, const Int_t bkgN = 0, const Int_t NU = 1, const Int_t detacut = 1, const Bool_t isfine = true, TString version = "v13")
{
	SetStyle();
	gStyle->SetOptFit(0000);

//set fitting condition name{{{
	TString bkgF;
	if(bkgN == 0) bkgF = "exp";
	else if(bkgN == 1) bkgF = "pol2";
	else
	{
		cout << "out of background list" << endl;
		return;
	}
	TString Ups;
	if(NU == 1) Ups = "1S";
	else if(NU == 2) Ups = "12S";
	else if(NU == 3) Ups = "123S";
	else
	{
		cout << "No such generation in this analysis" << endl;
		return;
	}
	TString DEC;
	if(detacut == 1) DEC = "eta1";
	else if(detacut == 2) DEC = "eta1p5";
	else if(detacut == 3) DEC = "eta2";
	else
	{
		cout << "out of delta eta cut range list" << endl;
		return;
	}
	TString Fine;
	if(isfine == true) Fine = "fine";
	else Fine = "coarse";
//}}}

	TFile* fout;
	if(maxF == 2) fout = new TFile(Form("CorrDist/CorrFiles/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_%s.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data(), version.Data()), "RECREATE");
	else if(maxF == 3) fout = new TFile(Form("CorrDist/CorrFiles/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_tra_%s_%s_%s_%s_%s.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data(), version.Data()), "RECREATE");
	else
	{
		cout << "No such Fourier value in this analysis" << endl;
		return;
	}
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
	TH1D* hist = new TH1D("hist", "", 20, 8, 14);
	FormTH1Marker(hist, 0, 0, 1.4);
	hist->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
	hist->GetYaxis()->SetTitle("v_{2}");
	hist->SetMinimum(-0.05);
	hist->SetMaximum(0.05);
//}}}

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
//Get yield distribution{{{
		TFile* fyield = new TFile(Form("SkimmedFiles/Yield/Yield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_%s.root", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), version.Data() ), "READ");
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
		string char23, char24, char25, char26, char27, char28;
		Double_t var1, var2, var3, var4, var5, var6, var7, var8, var9;
		Double_t var10, var11, var12, var13, var14, var15, var16, var17;
		Double_t var18, var19, var20, var21, var22, var23, var24, var25;
		Double_t var26, var27, var28;

		ifstream in1;
		in1.open(Form("SkimmedFiles/Parameter/Result_parameters_mult_%d-%d_pt_%d-%d_rap_%d-%d_%s.txt", (int)multMin, (int)multMax, (int)(10*ptBinsArr[ipt]), (int)(10*ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), version.Data()));
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

		Double_t bpar1, bpar2, bpar3, bpar4, bpar5;
		ifstream in2;
		in2.open(Form("SkimmedFiles/Parameter/v2_bkg_par_mult_%d-%d_pt_%d-%d_rap_%d-%d_%s_%s.txt", (int)multMin, (int)multMax, (int)(10*ptBinsArr[ipt]), (int)(10*ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), bkgF.Data(), version.Data()));
		if(in2.is_open())
		{
			in2 >> bpar1 >> bpar2 >> bpar3 >> bpar4 >> bpar5;
		}
		in2.close();
//}}}

//Get vn distribution{{{
		TFile* fvn;
		if(maxF == 2) fvn = new TFile(Form("CorrDist/CorrFiles/v2_dist_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.root", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "READ");
		else if(maxF == 3) fvn = new TFile(Form("CorrDist/CorrFiles/v2_dist_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_tra_%s.root", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "READ");
		else
		{
			cout << "No such Fourier value in this analysis" << endl;
			return;
		}

		TGraphErrors* gvn;
		if(detacut == 1)
		{
			if(isfine == true) gvn = (TGraphErrors*) fvn->Get("gv2_1fine");
			else gvn = (TGraphErrors*) fvn->Get("gv2_1coarse");
		}
		else if(detacut == 2)
		{
			if(isfine == true) gvn = (TGraphErrors*) fvn->Get("gv2_1p5fine");
			else gvn = (TGraphErrors*) fvn->Get("gv2_1p5coarse");
		}
		else if(detacut == 3)
		{
			if(isfine == true) gvn = (TGraphErrors*) fvn->Get("gv2_2fine");
			else gvn = (TGraphErrors*) fvn->Get("gv2_2coarse");
		}

		c1[ipt]->cd(2);
//}}}

//define function for simultaneous fitting{{{
		TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), TotalYield, 8, 14, 13);
		TF1* fvn_simul;
		if(bkgN == 0)
		{
			if(NU == 1) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), TotalvnexpU1S, 8, 14, 18);
			else if(NU == 2) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), TotalvnexpU12S, 8, 14, 18);
			else if(NU == 3) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), TotalvnexpU123S, 8, 14, 18);
			else
			{
				cout << "No such Upsilon generation in this analysis" << endl;
				return;
			}
		}
		else if(bkgN == 1)
		{
			if(NU == 1) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Totalvnpol2U1S, 8, 14, 17);
			else if(NU == 2) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Totalvnpol2U12S, 8, 14, 17);
			else if(NU == 3) fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Totalvnpol2U123S, 8, 14, 17);
			else
			{
				cout << "No such Upsilon generation in this analysis" << endl;
				return;
			}
		}
		else
		{
			cout << "Out of background function list" << endl;
			return;
		}
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

		massrange.SetRange(8, 14);
		ROOT::Fit::BinData datamass(opt, massrange);
		ROOT::Fit::FillData(datamass, hyield);

		ROOT::Fit::DataRange vnrange;
		vnrange.SetRange(8, 14);
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
		//par0[13] = signal v2 component
		//par0[14~] = background v2 components

		const Int_t Npar = 18;
		Double_t par0[Npar];
/*
		par0[0] = var21/var25;
		par0[1] = var22/var26;
		par0[2] = var23/var27;
		par0[3] = var24/var28;
*/
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
		par0[13] = 0.01;
		par0[14] = bpar1;
		par0[15] = bpar2;
		par0[16] = bpar3;
		par0[17] = bpar4;
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

		TF1* fyield_bkg = new TF1(Form("fyield_bkg_%d", ipt), "[0]*( TMath::Exp(-x/[3])*(TMath::Erf((x-[1])/(TMath::Sqrt(2)*[2]))+1)/2. )", 8, 14);
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
			fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), expbkg, 8, 14, 4);
			fvn_bkg->FixParameter(0, fvn_simul->GetParameter(14));
			fvn_bkg->FixParameter(1, fvn_simul->GetParameter(15));
			fvn_bkg->FixParameter(2, fvn_simul->GetParameter(16));
			fvn_bkg->FixParameter(3, fvn_simul->GetParameter(17));
		}
		else if(bkgN == 1)
		{
			fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), pol2bkg, 8, 14, 3);
			fvn_bkg->FixParameter(0, fvn_simul->GetParameter(14));
			fvn_bkg->FixParameter(1, fvn_simul->GetParameter(15));
			fvn_bkg->FixParameter(2, fvn_simul->GetParameter(16));
		}
		else
		{
			cout << "Out of background function list" << endl;
			return;
		}

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

		v2[ipt] = fvn_simul->GetParameter(13);
		v2e[ipt] = fvn_simul->GetParError(13);
		//v2_bkg[ipt] = fvn_simul->GetParameter(14) + fvn_simul->GetParameter(14) * U1S_mass;

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
		lt1->DrawLatex(0.42, 0.9, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", multMin));
		lt1->DrawLatex(0.42, 0.85, Form("%d < p_{T}^{#varUpsilon} < %d GeV/c", (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1]));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.42,0.8, Form("0.3 < p_{T}^{trk} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.42,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.42,0.75, "|#Delta#eta^{trk}| > 1.0");
		lt1->DrawLatex(0.42, 0.7, Form("Chi2/ndf = %.f/%d", Chi2Yield, NdfYield));

		Double_t xv2[200];
		Double_t pullv2[200];
		Double_t v2y[200];

		Float_t Chi2v2 = 0;
		Int_t Ndfv2 = mass_narr-1-fvn_simul->GetNpar()+(3-NU);

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
		if(maxF == 2) c1[ipt]->SaveAs(Form("CorrDist/V2Dist/Combine_fit_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%s_%s_%s_%s.pdf", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]*10), (int)(ptBinsArr[ipt+1]*10), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data(), version.Data()));
		else if(maxF == 3) c1[ipt]->SaveAs(Form("CorrDist/V2Dist/Combine_fit_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_tra_%s_%s_%s_%s_%s.pdf", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]*10), (int)(ptBinsArr[ipt+1]*10), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, bkgF.Data(), Ups.Data(), DEC.Data(), Fine.Data(), version.Data()));
		else
		{
			cout << "No such Fourier value in this analysis" << endl;
			return;
		}
	}

	TGraphErrors* v2plot = new TGraphErrors(pt_narr-1, pt, v2, 0, v2e);
	v2plot->SetTitle("");
//	TGraphErrors* v2bkgplot = new TGraphErrors(pt_narr-1, pt, v2_bkg, 0, 0);

	v2plot->SetName("v2vspt");
//	v2bkgplot->SetName("v2bkgvspt");

	v2plot->Write();
//	v2bkgplot->Write();
}
