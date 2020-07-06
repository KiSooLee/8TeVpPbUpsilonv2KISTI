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

void ZYAM(const Int_t multMin = 110, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v19", const bool Weight = false, const TString MupT = "3p5", const Bool_t Fine = true)
{
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fileDIR = mainDIR + Form("/File");
	TString plotDIR = mainDIR + Form("/Plots/%s", version.Data());

	void * dirf = gSystem->OpenDirectory(fileDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);

	void * dirp = gSystem->OpenDirectory(plotDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(plotDIR.Data(), kTRUE);
//}}}

	TString PorB[2] = {"peak", "bkg"};
	TString Band[2] = {"short", "2"};
	TString BandName[2] = {"short", "long"};
	TString ForC;
	if(Fine) ForC = "fine";
	else ForC = "coarse";

//fitting range{{{
//{{peak_short, peak_long}, {bkg_short, bkg_long}}

//110~300{{{
/*
	//110~300, 0~4 GeV fine
	const Double_t fitmin[2][2] = {{-1.0, 1.2}, {-1.0, 1.2}};
	const Double_t fitmax[2][2] = {{1.0, 2.4}, {1.0, 2.1}};
*/
/*
	//110~300, 0~4 GeV coarse
	const Double_t fitmin[2][2] = {{-1.0, 1.3}, {-1.0, 1.3}};
	const Double_t fitmax[2][2] = {{1.0, 2.6}, {1.0, 2.4}};
*/
/*
	//110~300, 4~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 0.8}, {-0.6, 1.8}};
	const Double_t fitmax[2][2] = {{0.5, 1.7}, {0.6, 2.1}};
*/
/*
	//110~300, 4~7 GeV coarse
	const Double_t fitmin[2][2] = {{-1.0, 1.0}, {-1.0, 0.6}};
	const Double_t fitmax[2][2] = {{1.0, 1.8}, {1.0, 1.4}};
*/
/*
	//110~300, 7~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 0.8}, {0.9, 1.6}};
	const Double_t fitmax[2][2] = {{1.5, 1.6}, {2.1, 1.9}};
*/
/*
	//110~300, 7~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.0}, {0.5, 1.2}};
	const Double_t fitmax[2][2] = {{2.5, 2.0}, {2.2, 2.4}};
*/
/*
	//110~300, 10~30 GeV fine
	const Double_t fitmin[2][2] = {{0.5, 1.2}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{2.1, 1.8}, {2.2, 1.9}};
*/
/*
	//110~300, 10~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.5}, {0.5, 0.5}};
	const Double_t fitmax[2][2] = {{2.2, 1.5}, {2.3, 1.5}};
*/
//}}}

//0~40{{{
/*
	//0~40, 0~4 GeV fine
	const Double_t fitmin[2][2] = {{-1.0, -1.0}, {-0.2, 0.0}};
	const Double_t fitmax[2][2] = {{1.0, 1.0}, {0.8, 1.2}};
*/
/*
	//0~40, 0~4 GeV coarse 
	const Double_t fitmin[2][2] = {{-1.0, -1.0}, {-1.0, 0.0}};
	const Double_t fitmax[2][2] = {{1.0, 1.0}, {0.0, 1.2}};
*/
/*
	//0~40, 4~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 0.2}, {-1.0, -0.5}};
	const Double_t fitmax[2][2] = {{0.8, 1.4}, {1.0, 0.4}};
*/
/*
	//0~40, 4~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, 0.2}, {-1.0, -0.5}};
	const Double_t fitmax[2][2] = {{0.8, 1.4}, {1.0, 0.4}};
*/
/*
	//0~40, 7~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 0.5}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {1.5, 0.4}};
*/
/*
	//0~40, 7~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 0.5}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {1.5, 0.4}};
*/
/*
	//0~40, 10~30 GeV fine
	const Double_t fitmin[2][2] = {{0.5, 0.3}, {0.6, 0.5}};
	const Double_t fitmax[2][2] = {{2.5, 1.5}, {2.0, 1.5}};
*/
/*
	//0~40, 10~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.3}, {0.6, 0.5}};
	const Double_t fitmax[2][2] = {{2.5, 1.5}, {2.0, 1.5}};
*/
//}}}

//0~45{{{
/*
	//0~45, 0~4 GeV fine
	const Double_t fitmin[2][2] = {{-1.0, -1.0}, {-0.4, 0.0}};
	const Double_t fitmax[2][2] = {{1.0, 1.0}, {0.8, 1.2}};
*/
/*
	//0~45, 0~4 GeV coarse 
	const Double_t fitmin[2][2] = {{-1.0, -1.0}, {-1.0, 0.0}};
	const Double_t fitmax[2][2] = {{1.0, 1.0}, {0.0, 1.2}};
*/
/*
	//0~45, 4~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, -0.1}, {-1.0, -0.5}};
	const Double_t fitmax[2][2] = {{0.4, 1.4}, {1.0, 0.4}};
*/
/*
	//0~45, 4~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, -0.1}, {-1.0, -0.5}};
	const Double_t fitmax[2][2] = {{0.8, 1.4}, {1.0, 0.4}};
*/
/*
	//0~45, 7~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 0.5}, {0.5, -0.8}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {2.2, 0.2}};
*/
/*
	//0~45, 7~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.2, 0.4}};
*/
//}}}

//0~50{{{
/*
	//0~50, 0~4 GeV fine
	const Double_t fitmin[2][2] = {{-0.3, 1.4}, {-0.9, 0.8}};
	const Double_t fitmax[2][2] = {{0.3, 1.9}, {0.5, 1.3}};
*/
/*
	//0~50, 0~4 GeV coarse 
	const Double_t fitmin[2][2] = {{-0.2, 1.0}, {-0.5, 1.3}};
	const Double_t fitmax[2][2] = {{0.9, 2.0}, {1.0, 2.2}};
*/
/*
	//0~50, 4~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 0.2}, {-0.5, 1.4}};
	const Double_t fitmax[2][2] = {{0.5, 1.2}, {0.5, 1.8}};
*/
/*
	//0~50, 4~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, 1.3}, {-1.0, 1.3}};
	const Double_t fitmax[2][2] = {{0.8, 2.2}, {1.0, 2.2}};
*/
/*
	//0~50, 7~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 0.7}, {1.0, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {2.2, 1.8}};
*/
/*
	//0~50, 7~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 1.7}, {1.0, 0.6}};
	const Double_t fitmax[2][2] = {{2.2, 2.6}, {2.2, 2.0}};
*/
/*
	//0~50, 10~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.6}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{2.2, 2.1}, {2.2, 2.0}};
*/
/*
	//0~50, 10~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 1.7}, {0.7, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 2.5}, {2.5, 2.2}};
*/
//}}}

//0~55{{{
/*
	//0~45, 0~4 GeV fine
	const Double_t fitmin[2][2] = {{-1.0, -1.0}, {-0.1, 0.0}};
	const Double_t fitmax[2][2] = {{1.0, 1.0}, {0.4, 1.2}};
*/
/*
	//0~45, 0~4 GeV coarse 
	const Double_t fitmin[2][2] = {{-1.0, -1.0}, {-1.0, 0.0}};
	const Double_t fitmax[2][2] = {{1.0, 1.0}, {0.0, 1.2}};
*/
/*
	//0~45, 4~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 0.0}, {-1.0, -0.5}};
	const Double_t fitmax[2][2] = {{0.3, 1.0}, {1.0, 0.4}};
*/
/*
	//0~45, 4~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, -0.5}, {-1.0, -0.5}};
	const Double_t fitmax[2][2] = {{0.8, 1.4}, {1.0, 0.4}};
*/
/*
	//0~45, 7~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 0.2}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {2.0, 0.4}};
*/
/*
	//0~45, 7~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 0.2}, {1.0, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {2.2, 0.4}};
*/
//}}}

//0~60{{{
/*
	//0~45, 0~4 GeV fine
	const Double_t fitmin[2][2] = {{-1.0, -1.0}, {-0.3, 0.0}};
	const Double_t fitmax[2][2] = {{1.0, 1.0}, {0.6, 1.2}};
*/
/*
	//0~45, 0~4 GeV coarse 
	const Double_t fitmin[2][2] = {{-1.0, -1.0}, {-1.0, 0.0}};
	const Double_t fitmax[2][2] = {{1.0, 1.0}, {1.0, 1.2}};
*/
/*
	//0~45, 4~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 0.2}, {-1.0, -0.5}};
	const Double_t fitmax[2][2] = {{0.8, 1.0}, {1.0, 0.4}};
*/
/*
	//0~45, 4~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, -0.2}, {-1.0, -0.5}};
	const Double_t fitmax[2][2] = {{0.8, 1.4}, {1.0, 0.4}};
*/
/*
	//0~45, 7~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 0.2}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {1.5, 0.4}};
*/
/*
	//0~45, 7~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 0.2}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {1.8, 0.4}};
*/
//}}}

//110~300 fine pt bin{{{
/*
	//5~6 GeV fine
	const Double_t fitmin[2][2] = {{-0.7, 1.5}, {-0.5, 1.0}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.4}};
*/
/*
	//5~6 GeV coarse 
	const Double_t fitmin[2][2] = {{-0.7, 1.0}, {-0.5, 0.5}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.5}};
*/
/*
	//6~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 0.0}, {-0.5, 0.3}};
	const Double_t fitmax[2][2] = {{0.8, 0.8}, {0.5, 1.5}};
*/
/*
	//6~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, -0.2}, {-0.5, 0.0}};
	const Double_t fitmax[2][2] = {{0.5, 1.0}, {0.5, 1.2}};
*/
/*
	//7~8 GeV fine
	const Double_t fitmin[2][2] = {{0.8, 0.4}, {1.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.3, 1.0}, {1.9, 1.5}};
*/
/*
	//7~8 GeV coarse
	const Double_t fitmin[2][2] = {{-0.2, 0.2}, {0.8, -0.6}};
	const Double_t fitmax[2][2] = {{0.7, 2.2}, {2.2, 1.5}};
*/
/*
	//8~9 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 1.4}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {1.8, 1.8}};
*/
/*
	//8~9 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {1.8, 2.2}};
*/
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.7}, {0.5, 1.1}};
	const Double_t fitmax[2][2] = {{1.2, 2.3}, {1.8, 1.7}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.5, 1.4}, {2.2, 0.4}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.7}};
	const Double_t fitmax[2][2] = {{1.8, 1.4}, {2.4, 1.2}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 1.0}};
	const Double_t fitmax[2][2] = {{2.0, 1.4}, {2.2, 2.0}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.5}, {2.2, 1.5}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 0.8}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {1.8, 0.4}};
*/
//}}}

//110~300 fine pt bin extend mass{{{
/*
	//5~6 GeV fine
	const Double_t fitmin[2][2] = {{-0.7, 1.5}, {-0.5, 1.0}};
	const Double_t fitmax[2][2] = {{0.9, 2.5}, {0.7, 1.4}};
*/
/*
	//5~6 GeV coarse 
	const Double_t fitmin[2][2] = {{-0.7, 1.0}, {-0.5, 0.5}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.5}};
*/
/*
	//6~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 0.0}, {-0.5, 0.3}};
	const Double_t fitmax[2][2] = {{0.8, 0.8}, {0.5, 1.5}};
*/
/*
	//6~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, -0.2}, {-0.5, 0.0}};
	const Double_t fitmax[2][2] = {{0.5, 1.0}, {0.5, 1.2}};
*/
/*
	//7~8 GeV fine
	const Double_t fitmin[2][2] = {{0.8, 0.4}, {1.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.3, 1.0}, {1.9, 1.5}};
*/
/*
	//7~8 GeV coarse
	const Double_t fitmin[2][2] = {{-0.2, 1.0}, {0.8, -0.6}};
	const Double_t fitmax[2][2] = {{0.7, 2.2}, {2.2, 1.5}};
*/
/*
	//8~9 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 0.8}, {0.5, 1.4}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {1.8, 1.8}};
*/
/*
	//8~9 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {1.8, 2.2}};
*/
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.7}, {0.5, 1.1}};
	const Double_t fitmax[2][2] = {{1.2, 2.3}, {1.8, 1.7}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.3}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.5, 2.3}, {2.2, 0.4}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.7}};
	const Double_t fitmax[2][2] = {{1.8, 1.4}, {2.4, 1.2}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 1.0}};
	const Double_t fitmax[2][2] = {{2.0, 1.4}, {2.2, 2.0}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.5}, {2.2, 1.5}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 0.8}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {1.8, 0.4}};
*/
//}}}

//0~50 fine pt bin{{{
/*
	//5~6 GeV fine
	const Double_t fitmin[2][2] = {{-0.7, 1.5}, {-0.5, 1.0}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.4}};
*/
/*
	//5~6 GeV coarse 
	const Double_t fitmin[2][2] = {{-0.7, 0.2}, {-0.5, 0.5}};
	const Double_t fitmax[2][2] = {{0.9, 1.1}, {0.7, 1.5}};
*/
/*
	//6~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.8, 1.5}, {-0.5, -1.0}};
	const Double_t fitmax[2][2] = {{0.8, 2.2}, {0.5, 1.5}};
*/
/*
	//6~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, 0.2}, {-0.5, 1.3}};
	const Double_t fitmax[2][2] = {{1.0, 1.5}, {0.5, 2.2}};
*/
/*
	//7~8 GeV fine
	const Double_t fitmin[2][2] = {{0.8, -0.8}, {1.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.3, 0.8}, {1.9, 1.5}};
*/
/*
	//7~8 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.5}, {0.8, -0.6}};
	const Double_t fitmax[2][2] = {{2.0, 1.5}, {2.2, 1.5}};
*/
/*
	//8~9 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 1.0}, {1.0, 1.4}};
	const Double_t fitmax[2][2] = {{0.5, 1.8}, {2.2, 1.8}};
*/
/*
	//8~9 GeV coarse
	const Double_t fitmin[2][2] = {{1.5, 1.0}, {1.0, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {2.0, 2.2}};
*/
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.2}, {0.5, 1.1}};
	const Double_t fitmax[2][2] = {{1.2, 2.2}, {1.8, 1.7}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.8, 1.4}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{2.2, 2.2}, {2.4, 1.0}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, 0.8}, {0.5, 0.8}};
	const Double_t fitmax[2][2] = {{1.8, 1.8}, {2.4, 1.6}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{1.4, 0.2}, {1.0, 1.4}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {2.7, 2.2}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, 1.4}, {0.5, 1.4}};
	const Double_t fitmax[2][2] = {{1.6, 1.8}, {2.2, 2.4}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.6}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{1.7, 2.4}, {1.8, 2.2}};
*/
//}}}

//0~50 fine pt bin extend mass{{{
/*
	//5~6 GeV fine
	const Double_t fitmin[2][2] = {{-0.7, 1.5}, {-0.5, 0.8}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.4}};
*/
/*
	//5~6 GeV coarse 
	const Double_t fitmin[2][2] = {{-0.7, 1.3}, {-0.5, 0.5}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.5}};
*/
/*
	//6~7 GeV fine
	const Double_t fitmin[2][2] = {{-1.0, 0.7}, {-0.5, 0.0}};
	const Double_t fitmax[2][2] = {{1.0, 1.3}, {0.5, 1.5}};
*/
/*
	//6~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, 0.4}, {-0.5, 0.0}};
	const Double_t fitmax[2][2] = {{0.5, 1.5}, {0.5, 1.2}};
*/
/*
	//7~8 GeV fine
	const Double_t fitmin[2][2] = {{0.8, 0.7}, {1.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.3, 1.3}, {1.9, 1.3}};
*/
/*
	//7~8 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.5}, {0.8, -0.6}};
	const Double_t fitmax[2][2] = {{2.0, 1.5}, {2.2, 1.5}};
*/
/*
	//8~9 GeV fine
	const Double_t fitmin[2][2] = {{1.3, 1.5}, {1.0, 1.4}};
	const Double_t fitmax[2][2] = {{2.4, 2.2}, {2.2, 1.8}};
*/
/*
	//8~9 GeV coarse
	const Double_t fitmin[2][2] = {{1.3, 1.0}, {1.0, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 2.2}, {2.2, 2.2}};
*/
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.5}, {0.5, 1.1}};
	const Double_t fitmax[2][2] = {{1.2, 2.0}, {1.8, 1.7}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.3}, {0.5, 1.0}};
	const Double_t fitmax[2][2] = {{2.0, 2.0}, {2.5, 1.8}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {2.5, 2.2}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{1.7, 2.5}, {1.8, 2.2}};
*/
//}}}

//0~40 fine pt bin{{{
/*
	//5~6 GeV fine
	const Double_t fitmin[2][2] = {{-1.3, 1.5}, {-0.5, 0.8}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.4}};
*/
/*
	//5~6 GeV coarse 
	const Double_t fitmin[2][2] = {{-1.3, 1.5}, {-0.5, 0.8}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.4}};
*/
/*
	//6~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.3, 0.5}, {-0.5, 1.4}};
	const Double_t fitmax[2][2] = {{1.3, 1.5}, {0.5, 2.2}};
*/
/*
	//6~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, 0.4}, {-0.5, 0.0}};
	const Double_t fitmax[2][2] = {{0.5, 1.5}, {0.5, 1.2}};
*/
/*
	//7~8 GeV fine
	const Double_t fitmin[2][2] = {{0.6, 1.2}, {1.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.3, 2.0}, {1.9, 1.3}};
*/
/*
	//7~8 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.5}, {1.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.5, 2.5}, {2.5, 1.5}};
*/
/*
	//8~9 GeV fine
	const Double_t fitmin[2][2] = {{1.3, 1.5}, {1.0, 1.4}};
	const Double_t fitmax[2][2] = {{2.4, 2.2}, {2.2, 1.8}};
*/
/*
	//8~9 GeV coarse
	const Double_t fitmin[2][2] = {{1.3, 1.0}, {1.0, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 2.2}, {2.2, 2.2}};
*/
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.5}, {1.4, 1.2}};
	const Double_t fitmax[2][2] = {{1.2, 2.0}, {2.6, 2.4}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.3}, {0.5, 1.0}};
	const Double_t fitmax[2][2] = {{2.0, 2.0}, {2.5, 1.8}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.6}, {2.4, 1.6}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {2.5, 2.2}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{1.7, 2.5}, {1.8, 2.2}};
*/
//}}}

//0~40 fine pt bin extend mass{{{
/*
	//5~6 GeV fine
	const Double_t fitmin[2][2] = {{-0.7, 1.5}, {-0.5, 0.8}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.4}};
*/
/*
	//5~6 GeV coarse 
	const Double_t fitmin[2][2] = {{-0.7, 1.3}, {-0.5, 0.5}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.5}};
*/
/*
	//6~7 GeV fine
	const Double_t fitmin[2][2] = {{0.2, 0.7}, {-0.5, 0.0}};
	const Double_t fitmax[2][2] = {{1.3, 1.3}, {0.5, 1.5}};
*/
/*
	//6~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, 0.4}, {-0.5, 0.0}};
	const Double_t fitmax[2][2] = {{0.5, 1.5}, {0.5, 1.2}};
*/
/*
	//7~8 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {1.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.3, 1.3}, {1.9, 1.3}};
*/
/*
	//7~8 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -0.5}, {1.5, -1.0}};
	const Double_t fitmax[2][2] = {{1.5, 1.0}, {2.5, 1.5}};
*/
/*
	//8~9 GeV fine
	const Double_t fitmin[2][2] = {{1.3, 1.5}, {1.0, 1.4}};
	const Double_t fitmax[2][2] = {{2.4, 2.2}, {2.2, 1.8}};
*/
/*
	//8~9 GeV coarse
	const Double_t fitmin[2][2] = {{1.3, 1.0}, {1.0, 0.5}};
	const Double_t fitmax[2][2] = {{2.2, 2.2}, {2.2, 2.2}};
*/
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{1.0, 1.5}, {1.2, 1.1}};
	const Double_t fitmax[2][2] = {{1.8, 2.0}, {2.4, 2.4}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.3}, {0.5, 1.0}};
	const Double_t fitmax[2][2] = {{2.0, 2.0}, {2.5, 1.8}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {2.5, 2.2}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{1.7, 2.5}, {1.8, 2.2}};
*/
//}}}

//90~300 fine pt bin{{{
/*
	//5~6 GeV fine
	const Double_t fitmin[2][2] = {{-0.7, 1.5}, {-0.5, -1.0}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.4}};
*/
/*
	//5~6 GeV coarse 
	const Double_t fitmin[2][2] = {{-0.7, 1.0}, {-0.5, 0.5}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.5}};
*/
/*
	//6~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 0.0}, {-0.5, 0.3}};
	const Double_t fitmax[2][2] = {{0.8, 0.8}, {0.5, 1.5}};
*/
/*
	//6~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, -0.4}, {-0.5, 0.0}};
	const Double_t fitmax[2][2] = {{0.5, 1.2}, {0.5, 1.4}};
*/
/*
	//7~8 GeV fine
	const Double_t fitmin[2][2] = {{0.8, 0.2}, {1.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.3, 2.0}, {1.9, 1.5}};
*/
/*
	//7~8 GeV coarse
	const Double_t fitmin[2][2] = {{-0.2, 0.2}, {0.8, -0.6}};
	const Double_t fitmax[2][2] = {{0.7, 2.2}, {2.2, 1.5}};
*/
/*
	//8~9 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {1.0, 1.4}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {2.0, 1.8}};
*/
/*
	//8~9 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {1.8, 2.2}};
*/
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.4}, {0.5, 0.0}};
	const Double_t fitmax[2][2] = {{1.2, 2.3}, {1.8, 1.7}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.4}, {2.2, 0.4}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.7}};
	const Double_t fitmax[2][2] = {{1.8, 1.4}, {2.4, 1.2}};
*/

	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.2}, {0.5, 1.0}};
	const Double_t fitmax[2][2] = {{2.0, 1.4}, {2.2, 2.0}};

/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.5}, {2.2, 1.5}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 0.8}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {2.4, 0.4}};
*/
//}}}

//90~300 fine pt bin extend mass{{{
/*
	//5~6 GeV fine
	const Double_t fitmin[2][2] = {{-0.7, 1.5}, {-0.5, -1.0}};
	const Double_t fitmax[2][2] = {{0.9, 2.4}, {0.7, 1.4}};
*/
/*
	//5~6 GeV coarse 
	const Double_t fitmin[2][2] = {{-0.7, 1.0}, {-0.5, 0.5}};
	const Double_t fitmax[2][2] = {{0.9, 2.2}, {0.7, 1.5}};
*/
/*
	//6~7 GeV fine
	const Double_t fitmin[2][2] = {{-0.5, 0.0}, {-0.5, 0.3}};
	const Double_t fitmax[2][2] = {{0.8, 0.8}, {0.5, 1.5}};
*/
/*
	//6~7 GeV coarse
	const Double_t fitmin[2][2] = {{-0.5, -0.2}, {-0.5, 0.0}};
	const Double_t fitmax[2][2] = {{0.5, 1.0}, {0.5, 1.4}};
*/
/*
	//7~8 GeV fine
	const Double_t fitmin[2][2] = {{0.8, 0.4}, {1.5, -0.6}};
	const Double_t fitmax[2][2] = {{1.3, 1.0}, {1.9, 1.5}};
*/
/*
	//7~8 GeV coarse
	const Double_t fitmin[2][2] = {{1.2, 0.2}, {0.8, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 2.2}, {2.2, 1.5}};
*/
/*
	//8~9 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.5}, {1.0, 1.4}};
	const Double_t fitmax[2][2] = {{2.2, 2.4}, {2.0, 1.8}};
*/
/*
	//8~9 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {1.8, 2.2}};
*/
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.7, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{1.2, 1.0}, {1.8, 1.0}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.4, 1.4}, {2.2, 0.4}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.7}};
	const Double_t fitmax[2][2] = {{1.8, 1.4}, {2.4, 1.2}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 1.0}};
	const Double_t fitmax[2][2] = {{2.0, 1.4}, {2.2, 2.0}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.5}, {2.2, 1.5}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, 0.8}, {0.5, -0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {2.4, 0.4}};
*/
//}}}

//}}}

	Double_t JYield[2][2];
	Double_t JYieldEE[2][2];

//Define histogram{{{
	TCanvas* c1[2];
	TCanvas* c2[2];
	TCanvas* c3[2];
	TH1D* h1[2][2];
	TH1D* h1_ZYAM[2][2];
	TH1D* hJYield[2][2];
	for(Int_t isl = 0; isl < 2; isl++)
	{
		c1[isl] = new TCanvas(Form("c1_%d", isl), "", 0, 0, 600, 300);
		c2[isl] = new TCanvas(Form("c2_%d", isl), "", 0, 0, 600, 300);
		c3[isl] = new TCanvas(Form("c3_%d", isl), "", 0, 0, 600, 300);
		c1[isl]->Divide(2, 1);
		c2[isl]->Divide(2, 1);
		c3[isl]->Divide(2, 1);
		for(Int_t ipb = 0; ipb < 2; ipb++)
		{
			hJYield[ipb][isl] = new TH1D(Form("hJYield_%s_%s", PorB[ipb].Data(), BandName[isl].Data()), "", 1, 0, 1);
		}
	}
//}}}

	TFile* fin[2];
	for(Int_t ipb = 0; ipb < 2; ipb++)//peak & background loop
	{
		fin[ipb] = new TFile(Form("../Projection/CorrDist/CorrFiles/%s/MupT%s/dphi_distribution_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_weight%o_MupT%s_%s.root", version.Data(), MupT.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), Weight, MupT.Data(), PorB[ipb].Data()), "READ");
		for(Int_t isl = 0; isl < 2; isl++)//short & long range loop
		{
			h1[ipb][isl] = (TH1D*) fin[ipb]->Get(Form("hRatioRecoDeltaPhi%s_%s", Band[isl].Data(), ForC.Data()));
			h1[ipb][isl]->SetName(Form("h_%s_%s", PorB[ipb].Data(), BandName[isl].Data()));
			h1[ipb][isl]->GetYaxis()->SetTitle("#frac{1}{N_{trig}}#frac{dN^{pair}}{d#Delta#phi}");
			h1[ipb][isl]->GetYaxis()->SetTitleSize(0.045);
			h1_ZYAM[ipb][isl] = (TH1D*) h1[ipb][isl]->Clone(Form("hZYAM_%s_%s", PorB[ipb].Data(), BandName[isl].Data()));
			h1_ZYAM[ipb][isl]->Reset();
			h1_ZYAM[ipb][isl]->GetYaxis()->SetTitle("#frac{1}{N_{trig}}#frac{dN^{pair}}{d#Delta#phi}-C_{ZYAM}");
			h1_ZYAM[ipb][isl]->GetYaxis()->SetTitleSize(0.045);
			TF1* f1 = new TF1(Form("f_%d_%d", ipb, isl), "[0]*x*x+[1]*x+[2]", fitmin[ipb][isl], fitmax[ipb][isl]);
			f1->SetLineColor(kRed);
			f1->SetParameter(0, 10);

			c1[isl]->cd(ipb+1);
			h1[ipb][isl]->SetMaximum(h1[ipb][isl]->GetMaximum()*1.05);
			h1[ipb][isl]->Draw();
			h1[ipb][isl]->Fit(Form("f_%d_%d", ipb, isl), "ML", "", fitmin[ipb][isl], fitmax[ipb][isl]);

			TLatex* lt1 = new TLatex();
			FormLatex(lt1, 12, 0.04);
			lt1->DrawLatex(0.16, 0.83, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
			if(isl == 0) lt1->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| < 1"));
			else lt1->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| > 2"));
			lt1->DrawLatex(0.16, 0.73, Form("%d #leq p_{T} < %d", (int)ptMin, (int)ptMax));
			if(ipb == 0) lt1->DrawLatex(0.16, 0.68, Form("Peak region"));
			else lt1->DrawLatex(0.16, 0.68, Form("Background region"));

			Double_t Min = f1->GetMinimum(fitmin[ipb][isl], fitmax[ipb][isl]);

			for(Int_t ibin = 0; ibin < h1[ipb][isl]->GetNbinsX(); ibin++)
			{
				Double_t vals = h1[ipb][isl]->GetBinContent(ibin+1);
				Double_t Evals = h1[ipb][isl]->GetBinError(ibin+1);
				h1_ZYAM[ipb][isl]->SetBinContent(ibin+1, vals-Min);
				h1_ZYAM[ipb][isl]->SetBinError(ibin+1, Evals);
				if( (Fine && (ibin >= 1 && ibin < 14) ) || (!Fine && (ibin >= 1 && ibin < 7)) )
				{
					JYield[ipb][isl] += h1_ZYAM[ipb][isl]->GetBinContent(ibin+1);
					JYieldEE[ipb][isl] += TMath::Power(h1_ZYAM[ipb][isl]->GetBinError(ibin+1), 2);
				}
			}
			c2[isl]->cd(ipb+1);
			h1_ZYAM[ipb][isl]->SetMaximum(h1_ZYAM[ipb][isl]->GetMaximum()*2);
			h1_ZYAM[ipb][isl]->Draw();
			SetLine(1, -1.45, 0, 4.45, 0, 0, 3);

			TLatex* lt2 = new TLatex();
			FormLatex(lt2, 12, 0.04);
			lt2->DrawLatex(0.16, 0.83, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
			if(isl == 0) lt2->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| < 1"));
			else lt2->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| > 2"));
			lt2->DrawLatex(0.16, 0.73, Form("%d #leq p_{T} < %d", (int)ptMin, (int)ptMax));
			if(ipb == 0) lt2->DrawLatex(0.16, 0.68, Form("Peak region"));
			else lt2->DrawLatex(0.16, 0.68, Form("Background region"));

			c3[isl]->cd(ipb+1);
			hJYield[ipb][isl]->SetBinContent(1, JYield[ipb][isl]);
			hJYield[ipb][isl]->SetBinError(1, TMath::Sqrt(JYieldEE[ipb][isl]));
			hJYield[ipb][isl]->SetMinimum(0);
			hJYield[ipb][isl]->Draw("pe");

			TLatex* lt3 = new TLatex();
			FormLatex(lt3, 12, 0.04);
			lt3->DrawLatex(0.55, 0.40, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
			if(isl == 0) lt3->DrawLatex(0.55, 0.35, Form("|#Delta#eta| < 1"));
			else lt3->DrawLatex(0.55, 0.35, Form("|#Delta#eta| > 2"));
			lt3->DrawLatex(0.55, 0.30, Form("%d #leq p_{T} < %d", (int)ptMin, (int)ptMax));
			if(ipb == 0) lt3->DrawLatex(0.55, 0.25, Form("Peak region"));
			else lt3->DrawLatex(0.55, 0.25, Form("Background region"));
			lt3->DrawLatex(0.55, 0.20, Form("%.2f #pm  %.2f", JYield[ipb][isl], TMath::Sqrt(JYieldEE[ipb][isl])));
		}
	}
	for(Int_t isl = 0; isl < 2; isl++)
	{
		c1[isl]->SaveAs(Form("Plots/%s/Before_ZYAM_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_Weight%o_%s_%s.pdf", version.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Weight, BandName[isl].Data(), ForC.Data()));
		c2[isl]->SaveAs(Form("Plots/%s/After_ZYAM_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_Weight%o_%s_%s.pdf", version.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Weight, BandName[isl].Data(), ForC.Data()));
		c3[isl]->SaveAs(Form("Plots/%s/JetYield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_Weight%o_%s_%s.pdf", version.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Weight, BandName[isl].Data(), ForC.Data()));
	}

	TFile* fout = new TFile(Form("File/Sideband_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_MupT%s_Weight%o_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), MupT.Data(), Weight, ForC.Data()), "RECREATE");
	fout->cd();
	for(Int_t ipb = 0; ipb < 2; ipb++)
	{
		for(Int_t isl = 0; isl < 2; isl++)
		{
			h1[ipb][isl]->Write();
			h1_ZYAM[ipb][isl]->Write();
			hJYield[ipb][isl]->Write();
		}
	}
	fout->Close();
}
