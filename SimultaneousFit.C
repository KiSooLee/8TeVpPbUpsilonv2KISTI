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

/*
//Yield fitting function{{{
Double_t YieldFunc(TF1* f1, TF1* f2, TF1* f3, Double_t* x, Double_t* p)
{
	return p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) + TMath::Exp(-x[0]/p[5])*(TMath::Erf((x[0]-p[3])/(TMath::Sqrt(2)*p[4]))+1)*0.5;
}
//}}}
*/

//vn fitting function{{{
/*
Double_t vnFunc(TF1* f1, TF1* f2, TF1* f3, Double_t* x, Double_t* p)
{
	return p[6]*( p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) )/( p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) + TMath::Exp(-x[0]/p[5])*(TMath::Erf((x[0]-p[3])/(TMath::Sqrt(2)*p[4]))+1)*0.5 ) + (p[7]+p[8]*x[0])*( 1 - ( p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) )/( p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) + TMath::Exp(-x[0]/p[5])*(TMath::Erf((x[0]-p[3])/(TMath::Sqrt(2)*p[4]))+1)*0.5 ) );
}
*/
/*
Double_t vnFunc(TF1* f1, Double_t* x, Double_t* p)
{
	return p[6]*( p[0]*f1->Eval(x[0]) )/( p[0]*f1->Eval(x[0]) + TMath::Exp(-x[0]/p[5])*(TMath::Erf((x[0]-p[3])/(TMath::Sqrt(2)*p[4]))+1)*0.5 ) + (p[7]+p[8]*x[0])*( 1 - ( p[0]*f1->Eval(x[0]) + p[2]*f2->Eval(x[0]) + p[3]*f3->Eval(x[0]) )/( p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) + TMath::Exp(-x[0]/p[5])*(TMath::Erf((x[0]-p[3])/(TMath::Sqrt(2)*p[4]))+1)*0.5 ) );
}
*/
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
	Double_t t1_1S = (x[0]-mean)/sigma;
	Double_t t2_1S = (x[0]-mean)/sigma1_2;
	Double_t t1_2S = (x[0]-mean2)/sigma2_1;
	Double_t t2_2S = (x[0]-mean2)/sigma2_2;
	Double_t t1_3S = (x[0]-mean3)/sigma3_1;
	Double_t t2_3S = (x[0]-mean3)/sigma3_2;
	if (alpha < 0)
	{
		t1_1S = -t1_1S;
		t2_1S = -t2_1S;
		t1_2S = -t1_2S;
		t2_2S = -t2_2S;
		t1_3S = -t1_3S;
		t2_3S = -t2_3S;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;

	if(t1_3S >= -absAlpha)
	{
		return N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( exp(-t1_3S*t1_3S/2.) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(t1_3S < -absAlpha && t2_3S >= -absAlpha)
	{
		return N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(t2_3S < -absAlpha && t1_2S >= -absAlpha)
	{
		return N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(t1_2S < -absAlpha && t2_2S >= -absAlpha)
	{
		return N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(t2_2S < -absAlpha && t1_1S >= -absAlpha)
	{
		return N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else if(t1_1S < -absAlpha && t1_2S >= -absAlpha)
	{
		return N1*( a/TMath::Power(b - t1_1S, n) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
	else
	{
		return N1*( a/TMath::Power(b - t1_1S, n) + frac*a/TMath::Power(b - t2_1S, n) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. );
	}
}
//}}}
/*
//totalvn{{{
Double_t Totalvn(Double_t* x, Double_t* par)
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
	Double_t e = par[15];
	Double_t mean2 = mean*U2S_mass/U1S_mass;
	Double_t mean3 = mean*U3S_mass/U1S_mass;
	Double_t sigma1_2 = sigma*ratio;
	Double_t sigma2_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3_2 = sigma*ratio*U3S_mass/U1S_mass;

	//t2 > t1
	Double_t t1_1S = (x[0]-mean)/sigma;
	Double_t t2_1S = (x[0]-mean)/sigma1_2;
	Double_t t1_2S = (x[0]-mean2)/sigma2_1;
	Double_t t2_2S = (x[0]-mean2)/sigma2_2;
	Double_t t1_3S = (x[0]-mean3)/sigma3_1;
	Double_t t2_3S = (x[0]-mean3)/sigma3_2;
	if (alpha < 0)
	{
		t1_1S = -t1_1S;
		t2_1S = -t2_1S;
		t1_2S = -t1_2S;
		t2_2S = -t2_2S;
		t1_3S = -t1_3S;
		t2_3S = -t2_3S;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;

	if(t1_3S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( exp(-t1_3S*t1_3S/2.) + frac*exp(-t2_3S*t2_3S/2.) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( exp(-t1_3S*t1_3S/2.) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ (d+e*x[0])*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( exp(-t1_3S*t1_3S/2.) + frac*exp(-t2_3S*t2_3S/2.) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( exp(-t1_3S*t1_3S/2.) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t1_3S < -absAlpha && t2_3S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*exp(-t2_3S*t2_3S/2.) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ (d+e*x[0])*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*exp(-t2_3S*t2_3S/2.) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t2_3S < -absAlpha && t1_2S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ (d+e*x[0])*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t1_2S < -absAlpha && t2_2S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ (d+e*x[0])*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t2_2S < -absAlpha && t1_1S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ (d+e*x[0])*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t1_1S < -absAlpha && t1_2S >= -absAlpha)
	{
//{{{
		return c*( N1*( a/TMath::Power(b - t1_1S, n) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( a/TMath::Power(b - t1_1S, n) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ (d+e*x[0])*( 1 - ( N1*( a/TMath::Power(b - t1_1S, n) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( a/TMath::Power(b - t1_1S, n) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else
	{
//{{{
		return c*( N1*( a/TMath::Power(b - t1_1S, n) + frac*a/TMath::Power(b - t2_1S, n) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( a/TMath::Power(b - t1_1S, n) + frac*a/TMath::Power(b - t2_1S, n) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ (d+e*x[0])*( 1 - ( N1*( a/TMath::Power(b - t1_1S, n) + frac*a/TMath::Power(b - t2_1S, n) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( a/TMath::Power(b - t1_1S, n) + frac*a/TMath::Power(b - t2_1S, n) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
}
//}}}
*/
//totalvn{{{
Double_t Totalvn(Double_t* x, Double_t* par)
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
	Double_t sigma1_2 = sigma*ratio;
	Double_t sigma2_1 = sigma*U2S_mass/U1S_mass;
	Double_t sigma2_2 = sigma*ratio*U2S_mass/U1S_mass;
	Double_t sigma3_1 = sigma*U3S_mass/U1S_mass;
	Double_t sigma3_2 = sigma*ratio*U3S_mass/U1S_mass;

	//t2 > t1
	Double_t t1_1S = (x[0]-mean)/sigma;
	Double_t t2_1S = (x[0]-mean)/sigma1_2;
	Double_t t1_2S = (x[0]-mean2)/sigma2_1;
	Double_t t2_2S = (x[0]-mean2)/sigma2_2;
	Double_t t1_3S = (x[0]-mean3)/sigma3_1;
	Double_t t2_3S = (x[0]-mean3)/sigma3_2;
	if (alpha < 0)
	{
		t1_1S = -t1_1S;
		t2_1S = -t2_1S;
		t1_2S = -t1_2S;
		t2_2S = -t2_2S;
		t1_3S = -t1_3S;
		t2_3S = -t2_3S;
	}

	Double_t absAlpha = fabs((Double_t)alpha);
	Double_t a = TMath::Power(n/absAlpha,n)*exp(-absAlpha*absAlpha/2.);
	Double_t b = n/absAlpha - absAlpha;

	if(t1_3S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( exp(-t1_3S*t1_3S/2.) + frac*exp(-t2_3S*t2_3S/2.) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( exp(-t1_3S*t1_3S/2.) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( exp(-t1_3S*t1_3S/2.) + frac*exp(-t2_3S*t2_3S/2.) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( exp(-t1_3S*t1_3S/2.) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t1_3S < -absAlpha && t2_3S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*exp(-t2_3S*t2_3S/2.) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*exp(-t2_3S*t2_3S/2.) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*exp(-t2_3S*t2_3S/2.) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t2_3S < -absAlpha && t1_2S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( exp(-t1_2S*t1_2S/2.) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t1_2S < -absAlpha && t2_2S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*exp(-t2_2S*t2_2S/2.) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t2_2S < -absAlpha && t1_1S >= -absAlpha)
	{
//{{{
		return c*( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( exp(-t1_1S*t1_1S/2.) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else if(t1_1S < -absAlpha && t2_1S >= -absAlpha)
	{
//{{{
		return c*( N1*( a/TMath::Power(b - t1_1S, n) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( a/TMath::Power(b - t1_1S, n) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( a/TMath::Power(b - t1_1S, n) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( a/TMath::Power(b - t1_1S, n) + frac*exp(-t2_1S*t2_1S/2.) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
	else
	{
//{{{
		return c*( N1*( a/TMath::Power(b - t1_1S, n) + frac*a/TMath::Power(b - t2_1S, n) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( a/TMath::Power(b - t1_1S, n) + frac*a/TMath::Power(b - t2_1S, n) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) )
				+ ( d*TMath::Exp(-x[0]/ep)*(TMath::Erf((x[0]-em)/(TMath::Sqrt(2)*es))+1)/2. )
				*( 1 - ( N1*( a/TMath::Power(b - t1_1S, n) + frac*a/TMath::Power(b - t2_1S, n) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) ) )/
				( N1*( a/TMath::Power(b - t1_1S, n) + frac*a/TMath::Power(b - t2_1S, n) )
				+ N2*( a/TMath::Power(b - t1_2S, n) + frac*a/TMath::Power(b - t2_2S, n) )
				+ N3*( a/TMath::Power(b - t1_3S, n) + frac*a/TMath::Power(b - t2_3S, n) )
				+ N4*( TMath::Exp(-x[0]/Bkgp0)*(TMath::Erf((x[0]-Bkgmean)/(TMath::Sqrt(2)*Bkgsigma))+1)/2. ) ) );
//}}}
	}
}
//}}}

//}}}

void SimultaneousFit(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const Int_t maxF = 2, TString version = "v13")
{
	SetStyle();
	gStyle->SetOptFit(0000);

	TFile* fout;
	if(maxF == 2) fout = new TFile(Form("CorrDist/CorrFiles/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "RECREATE");
	else if(maxF == 3) fout = new TFile(Form("CorrDist/CorrFiles/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_tra_%s.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "RECREATE");
	else
	{
		cout << "No such Fourier value" << endl;
		break;
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
	hist->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
	hist->GetYaxis()->SetTitle("v_{2}");
	hist->SetMinimum(-0.1);
	hist->SetMaximum(0.1);
//}}}

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
//Get yield distribution{{{
		TFile* fyield = new TFile(Form("SkimmedFiles/Yield/Yield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_%s.root", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), version.Data() ), "READ");
		TH1D* hyield = (TH1D*) fyield->Get(Form("hmass"));
		hyield->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
		hyield->GetYaxis()->SetTitle("Entries");
/*
		TF1* tf1S = (TF1*) fyield->Get(Form("twoCB1S"));
		TF1* tf2S = (TF1*) fyield->Get(Form("twoCB2S"));
		TF1* tf3S = (TF1*) fyield->Get(Form("twoCB3S"));
		TF1* tf1SC = (TF1*) tf1S->Clone("tf1SC");
		TF1* tf2SC = (TF1*) tf2S->Clone("tf2SC");
		TF1* tf3SC = (TF1*) tf3S->Clone("tf3SC");
		gROOT->GetListOfFunctions()->Add(tf1SC);
		gROOT->GetListOfFunctions()->Add(tf2SC);
		gROOT->GetListOfFunctions()->Add(tf3SC);

		//tf1SC->Print();
		//tf2SC->Print();
		//tf3SC->Print();

		//tf1S->SetTitle("tf1S");
		//tf2S->SetTitle("tf2S");
		//tf3S->SetTitle("tf3S");
*/
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

		ifstream in;
		in.open(Form("SkimmedFiles/Parameter/Result_parameters_mult_%d-%d_pt_%d-%d_rap_%d-%d_%s.txt", (int)multMin, (int)multMax, (int)(10*ptBinsArr[ipt]), (int)(10*ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), version.Data()));
		if(in.is_open())
		{
			in >> char1 >> char2 >> char3 >> char4 >> char5 >> char6 >> 
					char7 >> char8 >> char9 >> char10 >> char11 >> char12; 
			in >> var1 >> var2 >> var3 >> var4 >> var5 >> var6 >> 
					var7 >> var8 >> var9 >> var10 >> var11 >> var12;
			in >> char13 >> char14 >> char15 >> char16 >> char17 >> 
					char18 >> char19 >> char20;
			in >> var13 >> var14 >> var15 >> var16 >> var17 >> var18 >> 
					var19 >> var20;
			in >> char21 >> char22 >> char23 >> char24 >> char25 >> char26 >>
					char27 >> char28;
			in >> var21 >> var22 >> var23 >> var24 >> var25 >> var26 >>
					var27 >> var28;
		}
		in.close();
//}}}

//Get vn distribution{{{
		TFile* fvn;
		if(maxF == 2) fvn = new TFile(Form("CorrDist/CorrFiles/v2_dist_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.root", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "READ");
		else if(maxF == 3) fvn = new TFile(Form("CorrDist/CorrFiles/v2_dist_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_tra_%s.root", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "READ");
		else
		{
			cout << "No such Fourier value" << endl;
			break;
		}
		TGraphErrors* gvn_1fine = (TGraphErrors*) fvn->Get("gv2_1fine");
		TGraphErrors* gvn_1coarse = (TGraphErrors*) fvn->Get("gv2_1coarse");
		TGraphErrors* gvn_1p5fine = (TGraphErrors*) fvn->Get("gv2_1p5fine");
		TGraphErrors* gvn_1p5coarse = (TGraphErrors*) fvn->Get("gv2_1p5coarse");
		TGraphErrors* gvn_2fine = (TGraphErrors*) fvn->Get("gv2_2fine");
		TGraphErrors* gvn_2coarse = (TGraphErrors*) fvn->Get("gv2_2coarse");

		c1[ipt]->cd(2);
		//gvn_1fine->Draw();
//}}}

		//fit function for yield
//{{{
/*
//define individual crystalball function{{{
		TF1* f1S1 = new TF1("f1S1", "ROOT::Math::crystalball_function(x, var21, var22, var14, var13)", 8, 14);
		TF1* f1S2 = new TF1("f1S2", "ROOT::Math::crystalball_function(x, var21, var22, var15, var13)", 8, 14);
		TF1* f2S1 = new TF1("f2S1", "ROOT::Math::crystalball_function(x, var21, var22, var16, var13*U2S_mass/U1S_mass)", 8, 14);
		TF1* f2S2 = new TF1("f2S2", "ROOT::Math::crystalball_function(x, var21, var22, var17, var13*U2S_mass/U1S_mass)", 8, 14);
		TF1* f3S1 = new TF1("f3S1", "ROOT::Math::crystalball_function(x, var21, var22, var18, var13*U3S_mass/U1S_mass)", 8, 14);
		TF1* f3S2 = new TF1("f3S2", "ROOT::Math::crystalball_function(x, var21, var22, var19, var13*U3S_mass/U1S_mass)", 8, 14);
//}}}

		TF1* fbkg = new TF1("fbkg", "TMath::Exp(-x/[0])*(TMath::Erf((x-[1])/(TMath::Sqrt(2)*[2]))+1)*0.5", );
		fbkg->SetParameter(0, var25);
		fbkg->SetParameter(1, var23);
		fbkg->SetParameter(2, var24);
*/
//}}}

		//parameters
		//p0 = mean
		//p1 = sigma1
		//fit function for yield
//{{{
		//TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), "[13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)) + TMath::Exp(-x/[12])*(TMath::Erf((x-[10])/(TMath::Sqrt(2)*[11]))+1)*0.5", 8, 14);
//}}}

/*
//{{{
		auto Addfyield = [&](Double_t* x, Double_t* p)->Double_t
		{
			return YieldFunc(tf1SC, tf2SC, tf3SC, x, p);
		};
		TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), Addfyield, 8, 14, 6);

		auto Addfvn = [&](Double_t* x, Double_t* p)->Double_t
		{
			return vnFunc(tf1SC, tf2SC, tf3SC, x, p);
		};
		TF1* fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Addfvn, 8, 14, 9);
//}}}
*/

//{{{
		//TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), "[0]*(tf1SC) + [1]*(tf2SC) + [2]*(tf3SC) + TMath::Exp(-x/[5])*(TMath::Erf((x-[3])/(TMath::Sqrt(2)*[4]))+1)*0.5", 8, 14);
		//TF1* fvn_simul = new TF1(Form("fyield_simul_%d", ipt), "[6]*([0]*(tf1SC)+[1]*(tf2SC)+[2]*(tf3SC))/([0]*(tf1SC)+[1]*(tf2SC)+[2]*(tf3SC) + TMath::Exp(-x/[5])*(TMath::Erf((x-[3])/(TMath::Sqrt(2)*[4]))+1)*0.5) + ([7]+[8]*x)*(1 - ([0]*(tf1SC)+[2]*(tf2SC)+[3]*(tf3SC))/([0]*(tf1SC)+[1]*(tf2SC)+[2]*(tf3SC) + TMath::Exp(-x/[5])*(TMath::Erf((x-[3])/(TMath::Sqrt(2)*[4]))+1)*0.5))", 8, 14);
		//TF1* fvn_simul = new TF1(Form("fvn_simul_%d", ipt), "[16]*([13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)))/([13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)) + TMath::Exp(-x/[12])*(TMath::Erf((x-[10])/(TMath::Sqrt(2)*[11]))+1)*0.5) + ([17]+[18]*x)*(([13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)))/([13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)) + TMath::Exp(-x/[12])*(TMath::Erf((x-[10])/(TMath::Sqrt(2)*[11]))+1)*0.5))", 8, 14);
//}}}
		//fit function for v2
//{{{
		//TF1* fvn_simul = new TF1(Form("fvn_simul_%d", ipt), "[&](Double_t* x, Double_t* p){return p[5]*(p[0]*(p[4]*f1S1(x)+(1-p[4])*f1S2(x))+p[1]*(p[4]*f2S1(x)+(1-p[4])*f2S2(x))+p[2]*(p[4]*f3S1(x)+(1-p[4])*f3S2(x)))/(p[0]*(p[4]*f1S1(x)+(1-p[4])*f1S2(x))+p[1]*(p[4]*f2S1(x)+(1-p[4])*f2S2(x))+p[2]*(p[4]*f3S1(x)+(1-p[4])*f3S2(x))+p[3]*fbkg) + (p[6]+p[7]*x)*(1 - (p[0]*(p[4]*f1S1(x)+(1-p[4])*f1S2(x))+p[1]*(p[4]*f2S1(x)+(1-p[4])*f2S2(x))+p[2]*(p[4]*f3S1(x)+(1-p[4])*f3S2(x)))/(p[0]*(p[4]*f1S1(x)+(1-p[4])*f1S2(x))+p[1]*(p[4]*f2S1(x)+(1-p[4])*f2S2(x))+p[2]*(p[4]*f3S1(x)+(1-p[4])*f3S2(x))+p[3]*fbkg));}", 8, 14);
//}}}

		TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), TotalYield, 8, 14, 13);
		//TF1* fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Totalvn, 8, 14, 16);
		TF1* fvn_simul = new TF1(Form("fvn_simul_%d", ipt), Totalvn, 8, 14, 18);


//combine functions{{{
		fyield_simul->SetLineColor(2);
		fyield_simul->SetLineWidth(1);

		fvn_simul->SetLineColor(2);
		fvn_simul->SetLineWidth(1);

		ROOT::Math::WrappedMultiTF1 wmass(*fyield_simul, 1);
		ROOT::Math::WrappedMultiTF1 wvn(*fvn_simul, 1);

		ROOT::Fit::DataOptions opt;
		ROOT::Fit::DataRange massrange;

		massrange.SetRange(8, 16);
		ROOT::Fit::BinData datamass(opt, massrange);
		ROOT::Fit::FillData(datamass, hyield);

		ROOT::Fit::DataRange vnrange;
		vnrange.SetRange(8, 16);
		ROOT::Fit::BinData datavn(opt, vnrange);
		ROOT::Fit::FillData(datavn, gvn_1fine);

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
		//par0[3] = Erf mean
		//par0[4] = Erf sigma
		//par0[5] = Erf p0
		//par0[6] = sig ratio
		//par0[7] = linear b
		//par0[8] = linear a

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
		par0[14] = 0.10;
		//par0[15] = 0.1;

		par0[15] = 8.;
		par0[16] = 1.;
		par0[17] = 10.;

//}}}

//fit{{{
		c1[ipt]->cd(2);
		hist->Draw();
		fitter.Config().SetParamsSettings(Npar, par0);
		fitter.Config().ParSettings(4).Fix();
		fitter.Config().ParSettings(5).Fix();
		fitter.Config().ParSettings(6).Fix();
		fitter.Config().ParSettings(7).Fix();
		fitter.Config().ParSettings(8).Fix();
		fitter.Config().ParSettings(9).Fix();
		fitter.Config().ParSettings(10).SetLimits(0, 20);
		fitter.Config().ParSettings(11).SetLimits(0, 40);
		fitter.Config().ParSettings(12).SetLimits(0, 100);
		fitter.Config().MinimizerOptions().SetPrintLevel(0);
		fitter.Config().SetMinimizer("Minuit2","Migrad");

		fitter.FitFCN(Npar, globalChi2, 0, datamass.Size()+datavn.Size(), true);
		ROOT::Fit::FitResult result = fitter.Result();
		result.Print(std::cout);

		fyield_simul->SetFitResult(result, iparmass);
		fyield_simul->SetRange(massrange().first, massrange().second);
		fyield_simul->SetLineColor(kRed);
		hyield->GetListOfFunctions()->Add(fyield_simul);
		TF1* fyield_bkg = new TF1(Form("fyield_bkg_%d", ipt), "[0]*( TMath::Exp(-x/[3])*(TMath::Erf((x-[1])/(TMath::Sqrt(2)*[2]))+1)/2. )", 8, 14);
		fyield_bkg->FixParameter(0, fyield_simul->GetParameter(3));
		fyield_bkg->FixParameter(1, fyield_simul->GetParameter(10));
		fyield_bkg->FixParameter(2, fyield_simul->GetParameter(11));
		fyield_bkg->FixParameter(3, fyield_simul->GetParameter(12));
		fyield_bkg->SetLineColor(kMagenta);
		fyield_bkg->SetLineWidth(1);
		hyield->GetListOfFunctions()->Add(fyield_bkg);

		fvn_simul->SetFitResult(result, iparvn);
		fvn_simul->SetRange(vnrange().first, vnrange().second);
		fvn_simul->SetLineColor(2);

		TF1* fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), "[0]+[1]*x", 8, 14);
		fvn_bkg->FixParameter(0, fvn_simul->GetParameter(14));
		fvn_bkg->FixParameter(1, fvn_simul->GetParameter(15));

/*
		TF1* fvn_bkg = new TF1(Form("fvn_bkg_%d", ipt), "[0]*( TMath::Exp(-x/[3])*(TMath::Erf((x-[1])/(TMath::Sqrt(2)*[2]))+1)/2. )", 8, 14);
		fvn_bkg->FixParameter(0, fvn_simul->GetParameter(14));
		fvn_bkg->FixParameter(1, fvn_simul->GetParameter(15));
		fvn_bkg->FixParameter(2, fvn_simul->GetParameter(16));
		fvn_bkg->FixParameter(3, fvn_simul->GetParameter(17));
*/
		fvn_bkg->SetLineColor(kMagenta);
		fvn_bkg->SetLineWidth(1);

		gvn_1fine->GetListOfFunctions()->Add(fvn_simul);
		gvn_1fine->GetListOfFunctions()->Add(fvn_bkg);
		gvn_1fine->SetTitle("");
		gvn_1fine->SetMarkerSize(0.8);
		gvn_1fine->SetLineWidth(1);
		gvn_1fine->Draw("PESAME");
//}}}

//store individual function{{{
		fout->cd();

		fvntot[ipt] = (TF1*) fvn_simul->Clone();
		fvntot[ipt]->SetName(Form("vnfit_pt%d", ipt));
		fvntot[ipt]->Write();

		fyieldtot[ipt] = (TF1*) fyield_simul->Clone();
		fyieldtot[ipt]->SetName(Form("massfit_pt%d", ipt));
		fyieldtot[ipt]->Write();

		v2[ipt] = fvn_simul->GetParameter(13);
		v2e[ipt] = fvn_simul->GetParError(13);
		v2_bkg[ipt] = fvn_simul->GetParameter(14) + fvn_simul->GetParameter(14) * U1S_mass;
		a[ipt] = fvn_simul->GetParameter(14);
		b[ipt] = fvn_simul->GetParameter(15);

/*
		TF1* fvn_bkg = new TF1(Form("fvn_bkg_%d", 1), "([0]+[1]*x)", 8, 14);
		fvn_bkg->FixParameter(0, b[ipt]);
		fvn_bkg->FixParameter(1, a[ipt]);
		fvn_bkg->SetName(Form("fvnbkg_%d", ipt));
		fvn_bkg->Write();
*/
//}}}

//get Chi2{{{
		Double_t xmass[200];
		Double_t pullmass[200];

		Float_t Chi2 = 0;
		Int_t ndf = (14-8)/0.3 - 8;

		for(Int_t ibin = 0; ibin < hyield->GetNbinsX(); ibin++)
		{
			xmass[ibin] = hyield->GetBinCenter(ibin);
			pullmass[ibin] = (hyield->GetBinContent(ibin) - fyield_simul->Eval(xmass[ibin]))/hyield->GetBinError(ibin);
			if(fabs(pullmass[ibin]) < 5)
			{
				Chi2 += pullmass[ibin]*pullmass[ibin];
			}
		}

		Double_t xv2[200];
		Double_t pullv2[200];
		Double_t v2y[200];

		Float_t Chi2v2 = 0;
		Int_t ndfv2 = 8-2;

		for(Int_t ibin = 0; ibin < gvn_1fine->GetN(); ibin++)
		{
			gvn_1fine->GetPoint(ibin, xv2[ibin], v2y[ibin]);
			pullv2[ibin] = (v2y[ibin] - fvn_simul->Eval(xv2[ibin]))/gvn_1fine->GetErrorY(ibin);
			if(fabs(pullv2[ibin]) < 100)
			{
				Chi2v2 += pullv2[ibin]*pullv2[ibin];
			}
		}
//}}}
	}

	for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
	{
		cout << "pt" << ipt << ", a: " << a[ipt] << ", b: " << b[ipt] << endl;
		//c1[ipt]->SaveAs(Form("CorrDist/V2Dist/Combine_fit_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_pol1_%s.pdf", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]*10), (int)(ptBinsArr[ipt+1]*10), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
		c1[ipt]->SaveAs(Form("CorrDist/V2Dist/Combine_fit_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_Erf_%s.pdf", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]*10), (int)(ptBinsArr[ipt+1]*10), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
	}

	TGraphErrors* v2plot = new TGraphErrors(pt_narr-1, pt, v2, 0, v2e);
	v2plot->SetTitle("");
	TGraphErrors* v2bkgplot = new TGraphErrors(pt_narr-1, pt, v2_bkg, 0, 0);

	v2plot->SetName("v2vspt");
	v2bkgplot->SetName("v2bkgvspt");

	v2plot->Write();
	v2bkgplot->Write();
//}}}
}
