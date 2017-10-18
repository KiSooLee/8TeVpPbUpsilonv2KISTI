//Headers{{{
#include <TROOT.h>
#include <TTree.h>
#include <TString.h>
#include <TClonesArray.h>
//}}}

//Basic info{{{

//v1{{{
Double_t multBinsArr[] = {0, 1500};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 500};
//}}}

/*
//v2{{{
Double_t multBinsArr[] = {0, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 2.0, 4.0, 6.0, 9.0, 12.0, 30.0};
//}}}
*/
/*
//v3{{{
Double_t multBinsArr[] = {0, 50, 80, 110, 150, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 30};
//}}}
*/
/*
//v4{{{
Double_t multBinsArr[] = {0, 300};
Double_t rapBinsArr[] = {0.0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4};
Double_t ptBinsArr[] = {0, 30};
//}}}
*/

const Int_t rap_narr = sizeof(rapBinsArr)/sizeof(double);
const Int_t pt_narr = sizeof(ptBinsArr)/sizeof(double);
const Int_t mult_narr = sizeof(multBinsArr)/sizeof(double);
const Int_t Netabin = 33;
const Int_t Nphibin = 33;

const Int_t Numbin[10] = {0, 5000000, 10000000, 15000000, 20000000,
								25000000, 30000000, 35000000, 40000000, 45000000};

const Double_t U1S_mass = 9.460;
const Double_t U2S_mass = 10.023;
const Double_t U3S_mass = 10.355;
const Double_t U1S_sigma = 0.00026;
const Double_t U2S_sigma = 0.00031;
const Double_t U3S_sigma = 0.0005;
const Double_t peakFactor = 2.;
const Double_t sideFactor = 2.;
//}}}

class DiMuon
{
//{{{
	public:

	UInt_t eventNb, LS;
	Double_t zVtx, dphi, deta;
	Double_t mass, y, pt, phi;
	Double_t mupl_eta, mupl_pt, mupl_phi;
	Double_t mumi_eta, mumi_pt, mumi_phi;
	Double_t trk_eta, trk_pt, trk_phi;
	Double_t weight;
	Double_t mult;
	Int_t Ntrg, Nass;
	TClonesArray* Vec_trg;
	TClonesArray* Vec_ass;

	void clear()
	{
		eventNb = -99; LS = -99; zVtx = -99; dphi = -99, deta = -99;
		mass = -99; y = -99; pt = -99; phi = -99;
		mupl_eta = -99; mupl_pt = -99; mupl_phi = -99;
		mumi_eta = -99; mumi_pt = -99; mumi_phi = -99;
		trk_eta = -99; trk_pt = -99; trk_phi = -99;
		weight = -99; mult = -99;
		Ntrg = -99; Nass = -99;
		Vec_trg->Clear();
		Vec_ass->Clear();
	}

	void BuildBranch(TTree* tout)
	{
		tout->Branch("eventNb", &eventNb);
		tout->Branch("LS", &LS);
		tout->Branch("zVtx", &zVtx);
		tout->Branch("dphi", &dphi);
		tout->Branch("deta", &deta);
		tout->Branch("mass", &mass);
		tout->Branch("y", &y);
		tout->Branch("pt", &pt);
		tout->Branch("phi", &phi);
		tout->Branch("mupl_eta", &mupl_eta);
		tout->Branch("mupl_pt", &mupl_pt);
		tout->Branch("mupl_phi", &mupl_phi);
		tout->Branch("mumi_eta", &mumi_eta);
		tout->Branch("mumi_pt", &mumi_pt);
		tout->Branch("mumi_phi", &mumi_phi);
		tout->Branch("trk_eta", &trk_eta);
		tout->Branch("trk_pt", &trk_pt);
		tout->Branch("trk_phi", &trk_phi);
		tout->Branch("weight", &weight);
		tout->Branch("mult", &mult);
		tout->Branch("Ntrg", &Ntrg);
		tout->Branch("Nass", &Nass);
		Vec_trg = new TClonesArray("TLorentzVector", 250);
		Vec_ass = new TClonesArray("TLorentzVector", 1500);
		tout->Branch("Vec_trg", "TClonesArray", &Vec_trg, 32000, 0);
		tout->Branch("Vec_ass", "TClonesArray", &Vec_ass, 32000, 0);
	}
//}}}
};
