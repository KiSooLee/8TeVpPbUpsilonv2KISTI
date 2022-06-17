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

void ZYAM(const Int_t multMin = 110, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, const TString version = "v19", const Bool_t isAccRW = true, const Bool_t isEffRW = true, const Int_t isTnP = 0, const TString MupT = "3p5", const Bool_t Fine = true)
{
	SetStyle();

//Define names{{{
	TString PorB[2] = {"peak", "bkg"};
	TString Band[2] = {"short", "2"};
	TString BandName[2] = {"short", "long"};
	TString ForC;
	if(Fine) ForC = "fine";
	else ForC = "coarse";
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
	TString SysDir;
	if( isAccRW && isEffRW && (isTnP == 0) ) SysDir = "Nominal";
	else if( !isAccRW && isEffRW && (isTnP == 0) ) SysDir = "SysAcc";
	else if( isAccRW && !isEffRW && (isTnP == 0) ) SysDir = "SysEff";
	else if( isAccRW && isEffRW && (isTnP != 0) ) SysDir = "SysTnP";
	else
	{
		cout << "There is no such option" << endl;
		return;
	}
//}}}

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

//fitting range{{{
//{{peak_short, peak_long}, {bkg_short, bkg_long}}

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
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.4}};
	const Double_t fitmax[2][2] = {{2.4, 1.4}, {2.2, 1.6}};
*/
/*
	//9~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.7}};
	const Double_t fitmax[2][2] = {{1.8, 1.4}, {2.4, 1.2}};
*/
/*
	//9~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 1.0}};
	const Double_t fitmax[2][2] = {{2.0, 1.4}, {2.2, 2.0}};
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
	const Double_t fitmin[2][2] = {{0.7, 0.8}, {0.5, 0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {2.4, 1.6}};
*/
/*
	//15~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.0}, {0.5, 0.6}};
	const Double_t fitmax[2][2] = {{2.2, 1.5}, {2.2, 1.5}};
*/
/*
	//15~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.7, -1.0}, {0.5, -1.5}};
	const Double_t fitmax[2][2] = {{2.2, 1.8}, {2.4, 1.5}};
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
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.0, 2.5}, {2.5, 2.5}};
*/
/*
	//9~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//9~12 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 2.2}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{1.5, 0.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 2.2}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{1.7, 1.2}, {2.5, 1.2}};
*/
/*
	//15~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.8, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 1.2}, {2.5, 1.2}};
*/
//}}}

//90~300 fine pt bin extend mass v59{{{
/*
	//11~13 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//11~13 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 2.2}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//13~17 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//13~17 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{1.7, 1.2}, {2.5, 1.2}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.2}, {0.5, -1.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {2.5, 1.2}};
*/
/*
	//17~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//17~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.0}, {0.8, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.0}, {0.5, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
//}}}

//0~50 fine pt bin extend mass v60{{{
/*
	//11~13 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//11~13 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 2.2}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 1.2}};
*/
/*
	//13~17 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//13~17 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{1.7, 1.2}, {2.5, 1.2}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {3.0, 1.2}};
*/
/*
	//17~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//17~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.0}, {0.8, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.3}, {0.0, 0.2}};
	const Double_t fitmax[2][2] = {{1.8, 1.5}, {1.8, 1.2}};
*/
//}}}

//90~300 fine pt bin extend mass v61{{{
/*
	//13~16 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//13~16 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//13~17 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//13~17 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{1.7, 1.2}, {2.5, 1.2}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.2}, {0.5, -1.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {2.5, 1.2}};
*/
/*
	//17~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//17~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.0}, {0.8, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.0}, {0.5, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
//}}}

//0~50 fine pt bin extend mass v62{{{
/*
	//11~13 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//11~13 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.2}, {0.5, 1.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 2.2}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 1.2}};
*/
/*
	//13~17 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//13~17 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{1.7, 1.2}, {2.5, 1.2}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {3.0, 1.2}};
*/
/*
	//17~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//17~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.0}, {0.8, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.3}, {0.0, 0.2}};
	const Double_t fitmax[2][2] = {{1.8, 1.5}, {1.8, 1.2}};
*/
//}}}

//90~300 fine pt bin extend mass v65{{{
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -0.8}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.2}, {2.5, 1.0}};
*/
/*
	//10~11 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~11 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//11~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//11~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.2}, {0.5, -1.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {2.5, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.5}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
//}}}

//0~50 fine pt bin extend mass v66{{{
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -0.2}, {0.5, -0.3}};
	const Double_t fitmax[2][2] = {{2.3, 0.8}, {2.5, 0.8}};
*/
/*
	//10~11 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~11 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 1.2}};
*/
/*
	//11~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//11~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 1.2}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {3.0, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.2, -0.2}};
	const Double_t fitmax[2][2] = {{1.8, 1.5}, {1.7, 1.2}};
*/
//}}}

//90~300 fine pt bin extend mass v67{{{
/*
	//11~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//11~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.2}, {0.5, -1.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {2.5, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.0}, {0.5, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
//}}}

//0~50 fine pt bin extend mass v68{{{
/*
	//11~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//11~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.3}};
	const Double_t fitmax[2][2] = {{2.3, 1.4}, {2.5, 1.2}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {3.0, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.3}, {1.7, 0.2}};
	const Double_t fitmax[2][2] = {{1.8, 1.5}, {2.8, 1.2}};
*/
//}}}

//70~300 fine pt bin extend mass v75{{{
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -0.5}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//10~11 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~11 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//11~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//11~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.2}, {0.5, -1.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {2.2, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.0}, {0.5, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
//}}}

//70~300 new pt bin v81{{{
/*
	//9~10 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -0.5}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.2}, {0.5, -1.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {2.2, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 1.0}, {0.5, 0.2}};
	const Double_t fitmax[2][2] = {{2.4, 2.0}, {2.5, 1.2}};
*/
//}}}

//0~50 new pt bin v82{{{
/*
	//11~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.3}};
	const Double_t fitmax[2][2] = {{1.8, 1.4}, {2.5, 1.2}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, -0.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {3.0, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.3}, {1.7, 0.2}};
	const Double_t fitmax[2][2] = {{1.8, 1.5}, {2.8, 1.2}};
*/
//}}}

//70~300 new pt bin v86{{{
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//10~12 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.6, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.5, 1.0}};
*/
/*
	//12~15 GeV fine
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{1.4, -1.0}, {1.0, -1.0}};
	const Double_t fitmax[2][2] = {{2.3, 1.0}, {2.2, 1.0}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.2}, {0.5, -1.2}};
	const Double_t fitmax[2][2] = {{1.5, 1.2}, {2.5, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{1.3, 1.0}, {0.5, 0.2}};
	const Double_t fitmax[2][2] = {{2.2, 2.0}, {3.0, 1.2}};
*/
//}}}

//0~50 new pt bin v87{{{
/*
	//9~10 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//10~12 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.3}};
	const Double_t fitmax[2][2] = {{2.0, 1.4}, {2.5, 1.2}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.9, -0.2}};
	const Double_t fitmax[2][2] = {{2.2, 1.2}, {1.8, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.3}, {1.7, 0.2}};
	const Double_t fitmax[2][2] = {{2.6, 1.5}, {2.8, 1.2}};
*/
/*
	//12~30 GeV coarse
	const Double_t fitmin[2][2] = {{0.5, 0.3}, {1.7, 0.2}};
	const Double_t fitmax[2][2] = {{2.6, 1.5}, {2.8, 1.2}};
*/
//}}}

//mult scan pT 12~30 GeV v96{{{
/*
	//mult 70~90 coarse
	const Double_t fitmin[2][2] = {{1.5, -1.0}, {1.0, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//mult 90~120 coarse
	const Double_t fitmin[2][2] = {{0.5, -1.0}, {0.5, -1.0}};
	const Double_t fitmax[2][2] = {{2.2, 1.0}, {2.4, 1.0}};
*/
/*
	//mult 120~300 coarse
	const Double_t fitmin[2][2] = {{0.5, 0.2}, {0.5, 0.3}};
	const Double_t fitmax[2][2] = {{2.0, 1.4}, {2.5, 1.2}};
*/
//}}}

//0~35 new pt bin v97{{{
/*
	//12~15 GeV coarse
	const Double_t fitmin[2][2] = {{-1.5, 0.2}, {0.5, 0.3}};
	const Double_t fitmax[2][2] = {{-0.5, 1.4}, {2.5, 1.2}};
*/
/*
	//15~20 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//15~20 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.2}, {0.9, -0.2}};
	const Double_t fitmax[2][2] = {{2.0, 1.2}, {1.8, 1.2}};
*/
/*
	//20~30 GeV fine
	const Double_t fitmin[2][2] = {{0.7, 1.3}, {0.5, 1.5}};
	const Double_t fitmax[2][2] = {{1.5, 2.0}, {2.2, 2.5}};
*/
/*
	//20~30 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.3}, {0.5, 0.2}};
	const Double_t fitmax[2][2] = {{1.8, 1.5}, {2.0, 1.2}};
*/

	//12~30 GeV coarse
	const Double_t fitmin[2][2] = {{1.0, 0.3}, {1.0, 0.2}};
	const Double_t fitmax[2][2] = {{1.8, 1.5}, {1.8, 1.2}};

//}}}

//}}}

	Double_t JYield[2][2];
	Double_t JYieldE2[2][2];

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
		fin[ipb] = new TFile(Form("../Projection/CorrDist/CorrFiles/%s/MupT%s/%s/dphi_distribution_Reco_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_Data_%s_Acc%o_Eff%o_TnP%s_MupT%s_%s.root", version.Data(), MupT.Data(), SysDir.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), isAccRW, isEffRW, TnPs.Data(), MupT.Data(), PorB[ipb].Data()), "READ");

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

//event info{{{
			TLatex* lt1 = new TLatex();
			FormLatex(lt1, 12, 0.04);
			lt1->DrawLatex(0.16, 0.83, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
			if(isl == 0) lt1->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| < 1"));
			else lt1->DrawLatex(0.16, 0.78, Form("#Upsilon-h^{#pm}, |#Delta#eta| > 2"));
			lt1->DrawLatex(0.16, 0.73, Form("%d #leq p^{#Upsilon}_{T} < %d", (int)ptMin, (int)ptMax));
			if(ipb == 0) lt1->DrawLatex(0.16, 0.68, Form("Peak region"));
			else lt1->DrawLatex(0.16, 0.68, Form("Background region"));
//}}}

			Double_t Min = f1->GetMinimum(fitmin[ipb][isl], fitmax[ipb][isl]);

			for(Int_t ibin = 0; ibin < h1[ipb][isl]->GetNbinsX(); ibin++)
			{
				Double_t vals = h1[ipb][isl]->GetBinContent(ibin+1);
				Double_t Evals = h1[ipb][isl]->GetBinError(ibin+1);
				h1_ZYAM[ipb][isl]->SetBinContent(ibin+1, vals-Min);
				h1_ZYAM[ipb][isl]->SetBinError(ibin+1, Evals);

				if( (Fine && (ibin >= 1 && ibin < 14) ) || (!Fine && (ibin >= 1 && ibin < 7)) )
				{
					if(h1_ZYAM[ipb][isl]->GetBinContent(ibin+1) > 0) JYield[ipb][isl] += h1_ZYAM[ipb][isl]->GetBinContent(ibin+1);
					else JYield[ipb][isl] += 0;
					JYieldE2[ipb][isl] += h1_ZYAM[ipb][isl]->GetBinError(ibin+1)*h1_ZYAM[ipb][isl]->GetBinError(ibin+1);
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
			lt2->DrawLatex(0.16, 0.73, Form("%d #leq p^{#Upsilon}_{T} < %d", (int)ptMin, (int)ptMax));
			if(ipb == 0) lt2->DrawLatex(0.16, 0.68, Form("Peak region"));
			else lt2->DrawLatex(0.16, 0.68, Form("Background region"));

			c3[isl]->cd(ipb+1);
			hJYield[ipb][isl]->SetBinContent(1, JYield[ipb][isl]);
			hJYield[ipb][isl]->SetBinError(1, TMath::Sqrt(JYieldE2[ipb][isl]));
			hJYield[ipb][isl]->SetMinimum(0);
			hJYield[ipb][isl]->Draw("pe");

			TLatex* lt3 = new TLatex();
			FormLatex(lt3, 12, 0.04);
			lt3->DrawLatex(0.55, 0.40, Form("%d #leq N^{offline}_{trk} < %d", multMin, multMax));
			if(isl == 0) lt3->DrawLatex(0.55, 0.35, Form("|#Delta#eta| < 1"));
			else lt3->DrawLatex(0.55, 0.35, Form("|#Delta#eta| > 2"));
			lt3->DrawLatex(0.55, 0.30, Form("%d #leq p^{#Upsilon}_{T} < %d", (int)ptMin, (int)ptMax));
			if(ipb == 0) lt3->DrawLatex(0.55, 0.25, Form("Peak region"));
			else lt3->DrawLatex(0.55, 0.25, Form("Background region"));
			lt3->DrawLatex(0.55, 0.20, Form("%.2f #pm  %.2f", JYield[ipb][isl], TMath::Sqrt(JYieldE2[ipb][isl])));
		}
	}
	for(Int_t isl = 0; isl < 2; isl++)
	{
		c1[isl]->SaveAs(Form("Plots/%s/Before_ZYAM_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_Acc%o_Eff%o_TnP%s_MupT%s_%s_%s.pdf", version.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), isAccRW, isEffRW, TnPs.Data(), MupT.Data(), BandName[isl].Data(), ForC.Data()));
		c2[isl]->SaveAs(Form("Plots/%s/After_ZYAM_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_Acc%o_Eff%o_TnP%s_MupT%s_%s_%s.pdf", version.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), isAccRW, isEffRW, TnPs.Data(), MupT.Data(), BandName[isl].Data(), ForC.Data()));
		c3[isl]->SaveAs(Form("Plots/%s/JetYield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_Acc%o_Eff%o_TnP%s_MupT%s_%s_%s.pdf", version.Data(), multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), isAccRW, isEffRW, TnPs.Data(), MupT.Data(), BandName[isl].Data(), ForC.Data()));
	}

	TFile* fout;
	fout = new TFile(Form("File/Sideband_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_Acc%o_Eff%o_TnP%s_MupT%s_%s.root", multMin, multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), isAccRW, isEffRW, TnPs.Data(), MupT.Data(), ForC.Data()), "RECREATE");
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
