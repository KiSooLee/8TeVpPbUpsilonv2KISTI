#ifndef tnp_weight_h
#define tnp_weight_h

#include "TMath.h"

// IN THIS FILE YOU WILL FIND:
// ++++++++++++++

// - TrkM: 
//	(tnp_weight_trkM_ppb)
//   * idx = 0: nominal
//   * idx = -11: stat variation,  +1 sigma
//   * idx = -12: stat variation,  -1 sigma
//   * idx = -13: syst variation,  +1 sigma
//   * idx = -14: syst variation,  -1 sigma
//
//      (tnp_weight_trkM_eta)
//   * idx = 0: nominal

// - MuID: 
//	(tnp_weight_muid_ppb)
//   * idx = 0: binned, nominal
//   * idx = -11: binned, stat up
//   * idx = -12: binned, stat down
//   * idx = -13: binned, syst up
//   * idx = -14: binned, syst down
//
// (tnp_weight_muid_nTrack)  - data correction based on the number of tracks in the event (integrated value = 1). It is for a single muon, for dimuons it would need to be squared
//   * idx = 0: binned, nominal
//   * idx = -11: binned, stat up
//   * idx = -12: binned, stat down

// - Trigger: 
//	(tnp_weight_trg_ppb)
//   * idx = 0: nominal
//   * idx = -11: stat variation,  +1 sigma
//   * idx = -12: stat variation,  -1 sigma
//   * idx = -13: syst variation,  +1 sigma
//   * idx = -14: syst variation,  -1 sigma

// THE INDIVIDUAL SFs
// ++++++++++++++++++
double tnp_weight_trkM_ppb(double pt, double eta, int idx = 0);
double tnp_weight_trkM_eta(double eta, int idx = 0);
double tnp_weight_muid_ppb(double pt, double eta, int idx = 0);
double tnp_weight_muid_nTrack(int nTrack, int idx = 0); //
double tnp_weight_trg_ppb(double pt, double eta, int idx = 0);



///////////////////////////////////////////////////
//                 T r k M    P P b                //
///////////////////////////////////////////////////
double tnp_weight_trkM_ppb(double pt, double eta, int idx)
{
  double num=1.0, den=0.0;  //intentionaly 0, so if asked for a corrections outside defined range, it returns NaN instead of 1

  //versus pt in bins of abseta
  // MC
  if (fabs(eta) > 0 && fabs(eta) <= 1) { 
    if (pt > 3.3 && pt <= 4.5) den = 0.828172;
    else if (pt <= 6.5) den = 0.989967;
    else if (pt <= 8) den = 0.995977;
    else if (pt <= 14) den = 0.996413;
    else if (pt <= 25) den = 0.997164;
  }
  else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 3.3) den = 0.784932;
    else if (pt <= 6.5) den = 0.96759;
    else if (pt <= 8) den = 0.997175;
    else if (pt <= 14) den = 0.998082;
    else if (pt <= 25) den = 0.997508;
  }
  else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 3.3) den = 0.875976;
    else if (pt <= 6.5) den = 0.996701;
    else if (pt <= 10.5) den = 0.999353;
    else if (pt <= 25) den = 0.9994;
  }
  else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 3.3) den = 0.784331;
    else if (pt <= 6.5) den = 0.997418;
    else if (pt <= 10.5) den = 0.99895;
    else if (pt <= 25) den = 0.998834;
  }

  // data
  if (idx == 0) { // nominal
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.854987;
      else if (pt <= 6.5) num = 0.984073;
      else if (pt <= 8) num = 0.983683;
      else if (pt <= 14) num = 0.995065;
      else if (pt <= 25) num = 1;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
      if (pt > 1.2 && pt <= 3.3) num = 0.738779;
      else if (pt <= 6.5) num = 0.972902;
      else if (pt <= 8) num = 0.964183;
      else if (pt <= 14) num = 0.99998;
      else if (pt <= 25) num = 0.962675;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.863469;
      else if (pt <= 6.5) num = 0.992568;
      else if (pt <= 10.5) num = 0.999296;
      else if (pt <= 25) num = 0.999996;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.668745;
      else if (pt <= 6.5) num = 0.998159;
      else if (pt <= 10.5) num = 0.999997;
      else if (pt <= 25) num = 0.983567;
    }
  }
  else if (idx == -11) { // stat up
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.859493;
      else if (pt <= 6.5) num = 0.987713;
      else if (pt <= 8) num = 0.992502;
      else if (pt <= 14) num = 0.998501;
      else if (pt <= 25) num = 1.00011;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
      if (pt > 1.2 && pt <= 3.3) num = 0.750961;
      else if (pt <= 6.5) num = 0.98076;
      else if (pt <= 8) num = 0.977418;
      else if (pt <= 14) num = 1.0007;
      else if (pt <= 25) num = 0.981704;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.864507;
      else if (pt <= 6.5) num = 0.996854;
      else if (pt <= 10.5) num = 0.999869;
      else if (pt <= 25) num = 1.00075;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.674617;
      else if (pt <= 6.5) num = 0.999223;
      else if (pt <= 10.5) num = 1.00035;
      else if (pt <= 25) num = 0.996075;
    }
  }
  else if (idx == -12) { // stat down
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.850466;
      else if (pt <= 6.5) num = 0.980108;
      else if (pt <= 8) num = 0.969642;
      else if (pt <= 14) num = 0.989608;
      else if (pt <= 25) num = 0.981821;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
      if (pt > 1.2 && pt <= 3.3) num = 0.734002;
      else if (pt <= 6.5) num = 0.9653;
      else if (pt <= 8) num = 0.943677;
      else if (pt <= 14) num = 0.999247;
      else if (pt <= 25) num = 0.905647;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.862443;
      else if (pt <= 6.5) num = 0.989147;
      else if (pt <= 10.5) num = 0.989864;
      else if (pt <= 25) num = 0.999241;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.66278;
      else if (pt <= 6.5) num = 0.987237;
      else if (pt <= 10.5) num = 0.999645;
      else if (pt <= 25) num = 0.966846;
    }
  }
  if (idx == -13) { // TnP fit syst up
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.860158;
      else if (pt <= 6.5) num = 0.991169;
      else if (pt <= 8) num = 0.990779;
      else if (pt <= 14) num = 1.00039;
      else if (pt <= 25) num = 1.00177;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
      if (pt > 1.2 && pt <= 3.3) num = 0.763945;
      else if (pt <= 6.5) num = 0.987012;
      else if (pt <= 8) num = 0.973985;
      else if (pt <= 14) num = 1.00687;
      else if (pt <= 25) num = 0.967144;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.89529;
      else if (pt <= 6.5) num = 0.997346;
      else if (pt <= 10.5) num = 1.00366;
      else if (pt <= 25) num = 1.00276;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.74809;
      else if (pt <= 6.5) num = 1.00562;
      else if (pt <= 10.5) num = 1.00746;
      else if (pt <= 25) num = 0.991028;
    }
  }
  else if (idx == -14) { // TnP fit syst down
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.849815;
      else if (pt <= 6.5) num = 0.976977;
      else if (pt <= 8) num = 0.976587;
      else if (pt <= 14) num = 0.989743;
      else if (pt <= 25) num = 0.998226;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
      if (pt > 1.2 && pt <= 3.3) num = 0.713612;
      else if (pt <= 6.5) num = 0.958792;
      else if (pt <= 8) num = 0.954381;
      else if (pt <= 14) num = 0.99309;
      else if (pt <= 25) num = 0.958206;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.831648;
      else if (pt <= 6.5) num = 0.98779;
      else if (pt <= 10.5) num = 0.99493;
      else if (pt <= 25) num = 0.997235;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
      if (pt > 0.8 && pt <= 3.3) num = 0.589399;
      else if (pt <= 6.5) num = 0.990698;
      else if (pt <= 10.5) num = 0.992536;
      else if (pt <= 25) num = 0.976106;
    }
  }
  return (num/den);
}

double tnp_weight_trkM_eta(double eta, int idx)
{
  double num=1.0, den=0.0;  //intentionaly 0, so if asked for a corrections outside defined range, it returns NaN instead of 1

  //versus eta
  // MC
  if (eta >= -2.4 && eta <= -2) den = 0.80172;
  else if (eta > -2 && eta <= -1.5) den = 0.89553;
  else if (eta > -1.5 && eta <= -1) den = 0.873239;
  else if (eta > -1 && eta <= -0.5) den = 0.932599;
  else if (eta > -0.5 && eta <= 0) den = 0.911417;
  else if (eta > 0 && eta <= 0.5) den = 0.904444;
  else if (eta > 0.5 && eta <= 1) den = 0.931976;
  else if (eta > 1 && eta <= 1.5) den = 0.879465;
  else if (eta > 1.5 && eta <= 2) den = 0.895665;
  else if (eta > 2 && eta <= 2.4) den = 0.806029;

  // data
  // nominal
  if (eta >= -2.4 && eta <= -2) den = 0.698431;
  else if (eta > -2 && eta <= -1.5) den = 0.925182;
  else if (eta > -1.5 && eta <= -1) den = 0.87917;
  else if (eta > -1 && eta <= -0.5) den = 0.948257;
  else if (eta > -0.5 && eta <= 0) den = 0.930047;
  else if (eta > 0 && eta <= 0.5) den = 0.919776;
  else if (eta > 0.5 && eta <= 1) den = 0.930647;
  else if (eta > 1 && eta <= 1.5) den = 0.862745;
  else if (eta > 1.5 && eta <= 2) den = 0.885517;
  else if (eta > 2 && eta <= 2.4) den = 0.778149;

  return (num/den);
}



///////////////////////////////////////////////////
//               M U I D      P P b              //
///////////////////////////////////////////////////
double tnp_weight_muid_ppb(double pt, double eta, int idx) 
{
  double num=1.0, den=0.0;  //intentionaly 0, so if asked for a corrections outside defined range, it returns NaN instead of 1

  // MC
  if (fabs(eta) > 0 && fabs(eta) <= 1) { 
    if (pt > 3.3 && pt <= 4.5) den = 0.813088;
    else if (pt <= 6.5) den = 0.97996;
    else if (pt <= 8) den = 0.989381;
    else if (pt <= 14) den = 0.989807;
    else if (pt <= 25) den = 0.992734;
  }
  else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 3.3) den = 0.76572;
    else if (pt <= 6.5) den = 0.958087;
    else if (pt <= 8) den = 0.990633;
    else if (pt <= 14) den = 0.993665;
    else if (pt <= 25) den = 0.991818;
  }
  else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 3.3) den = 0.850281;
    else if (pt <= 6.5) den = 0.997059;
    else if (pt <= 10.5) den = 0.997393;
    else if (pt <= 25) den = 0.99688;
  }
  else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 3.3) den = 0.765348;
    else if (pt <= 6.5) den = 0.996991;
    else if (pt <= 10.5) den = 0.999424;
    else if (pt <= 25) den = 0.998493;
  }

  // data
  if (idx == -10) { // nominal
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
    if (pt > 3.3 && pt <= 4.5) num = 0.845598;
    else if (pt <= 6.5) num = 0.967603;
    else if (pt <= 8) num = 0.977268;
    else if (pt <= 14) num = 0.991168;
    else if (pt <= 25) num = 0.997561;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 3.3) num = 0.719255;
    else if (pt <= 6.5) num = 0.950386;
    else if (pt <= 8) num = 0.967113;
    else if (pt <= 14) num = 0.990789;
    else if (pt <= 25) num = 0.955171;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.80888;
    else if (pt <= 6.5) num = 0.978908;
    else if (pt <= 10.5) num = 0.997962;
    else if (pt <= 25) num = 0.981748;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.716081;
    else if (pt <= 6.5) num = 0.993333;
    else if (pt <= 10.5) num = 0.973856;
    else if (pt <= 25) num = 0.988481;
    }
  }
  else if (idx == -11) { // stat up
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
    if (pt > 3.3 && pt <= 4.5) num = 0.850747;
    else if (pt <= 6.5) num = 0.972063;
    else if (pt <= 8) num = 0.983056;
    else if (pt <= 14) num = 0.994197;
    else if (pt <= 25) num = 0.998493;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 3.3) num = 0.731066;
    else if (pt <= 6.5) num = 0.957375;
    else if (pt <= 8) num = 0.975936;
    else if (pt <= 14) num = 0.991082;
    else if (pt <= 25) num = 0.959674;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.822019;
    else if (pt <= 6.5) num = 0.986292;
    else if (pt <= 10.5) num = 0.998626;
    else if (pt <= 25) num = 0.98304;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.733741;
    else if (pt <= 6.5) num = 0.994591;
    else if (pt <= 10.5) num = 0.986658;
    else if (pt <= 25) num = 0.994845;
    }
  }
  else if (idx == -12) { // stat down
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
    if (pt > 3.3 && pt <= 4.5) num = 0.840527;
    else if (pt <= 6.5) num = 0.963157;
    else if (pt <= 8) num = 0.971026;
    else if (pt <= 14) num = 0.985514;
    else if (pt <= 25) num = 0.989119;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 3.3) num = 0.708015;
    else if (pt <= 6.5) num = 0.943544;
    else if (pt <= 8) num = 0.954372;
    else if (pt <= 14) num = 0.987202;
    else if (pt <= 25) num = 0.937987;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.79668;
    else if (pt <= 6.5) num = 0.970357;
    else if (pt <= 10.5) num = 0.990297;
    else if (pt <= 25) num = 0.972344;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.708918;
    else if (pt <= 6.5) num = 0.983331;
    else if (pt <= 10.5) num = 0.953605;
    else if (pt <= 25) num = 0.957406;
    }
  }
  if (idx == -13) { // TnP fit syst up
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
    if (pt > 3.3 && pt <= 4.5) num = 0.845598;
    else if (pt <= 6.5) num = 0.967603;
    else if (pt <= 8) num = 0.977268;
    else if (pt <= 14) num = 0.991168;
    else if (pt <= 25) num = 0.997561;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 3.3) num = 0.719255;
    else if (pt <= 6.5) num = 0.950386;
    else if (pt <= 8) num = 0.967113;
    else if (pt <= 14) num = 0.990789;
    else if (pt <= 25) num = 0.955171;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.80888;
    else if (pt <= 6.5) num = 0.978908;
    else if (pt <= 10.5) num = 0.997962;
    else if (pt <= 25) num = 0.981748;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.716081;
    else if (pt <= 6.5) num = 0.993333;
    else if (pt <= 10.5) num = 0.973856;
    else if (pt <= 25) num = 0.988481;
    }
  }
  else if (idx == -14) { // TnP fit syst down
    if (fabs(eta) > 0 && fabs(eta) <= 1) { 
    if (pt > 3.3 && pt <= 4.5) num = 0.845598;
    else if (pt <= 6.5) num = 0.967603;
    else if (pt <= 8) num = 0.977268;
    else if (pt <= 14) num = 0.991168;
    else if (pt <= 25) num = 0.997561;
    }
    else if (fabs(eta) > 1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 3.3) num = 0.719255;
    else if (pt <= 6.5) num = 0.950386;
    else if (pt <= 8) num = 0.967113;
    else if (pt <= 14) num = 0.990789;
    else if (pt <= 25) num = 0.955171;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.80888;
    else if (pt <= 6.5) num = 0.978908;
    else if (pt <= 10.5) num = 0.997962;
    else if (pt <= 25) num = 0.981748;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 3.3) num = 0.716081;
    else if (pt <= 6.5) num = 0.993333;
    else if (pt <= 10.5) num = 0.973856;
    else if (pt <= 25) num = 0.988481;
    }
  }
  return (num/den);
}

/*double tnp_weight_muid_ppb(double pt, double eta, int idx) {
	double x = pt;

	double num = 1.0, den = 0.0;  //intentionaly 0, so if asked for a corrections outside defined range, it returns NaN instead of 1

	// MC
	if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
		if (pt > 3.3 && pt <= 4.5) den = 0.980292;
		else if (pt <= 5.5) den = 0.988652;
		else if (pt <= 6.5) den = 0.991186;
		else if (pt <= 8) den = 0.99211;
		else if (pt <= 10.5) den = 0.993282;
		else if (pt <= 14) den = 0.993677;
		else if (pt <= 18) den = 0.993716;
		else if (pt < 9999) den = 0.989668;
	}
	else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
		if (pt > 1.1 && pt <= 3.3) den = 0.972175;
		else if (pt <= 4.5) den = 0.986112;
		else if (pt <= 5.5) den = 0.989617;
		else if (pt <= 6.5) den = 0.992082;
		else if (pt <= 8) den = 0.993391;
		else if (pt <= 10.5) den = 0.993456;
		else if (pt <= 14) den = 0.996085;
		else if (pt <= 18) den = 0.994577;
		else if (pt < 9999) den = 0.994608;
	}
	else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
		if (pt > 0.8 && pt <= 2) den = 0.973474;
		else if (pt <= 3.5) den = 0.994106;
		else if (pt <= 4.5) den = 0.997574;
		else if (pt <= 6.5) den = 0.99761;
		else if (pt <= 10) den = 0.998036;
		else if (pt <= 14) den = 0.997462;
		else if (pt < 9999) den = 0.997858;
	}
	else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
		if (pt > 0.8 && pt <= 2) den = 0.975377;
		else if (pt <= 3.5) den = 0.992559;
		else if (pt <= 5.5) den = 0.994019;
		else if (pt <= 12) den = 0.995517;
		else if (pt < 9999) den = 1;
	}

	// data
	if (idx == 0) { // nominal
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.978123;
			else if (pt <= 5.5) num = 0.985305;
			else if (pt <= 6.5) num = 0.98696;
			else if (pt <= 8) num = 0.98821;
			else if (pt <= 10.5) num = 0.989972;
			else if (pt <= 14) num = 0.991429;
			else if (pt <= 18) num = 0.990797;
			else if (pt < 9999) num = 0.991848;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.973117;
			else if (pt <= 4.5) num = 0.984226;
			else if (pt <= 5.5) num = 0.988538;
			else if (pt <= 6.5) num = 0.991459;
			else if (pt <= 8) num = 0.991702;
			else if (pt <= 10.5) num = 0.990132;
			else if (pt <= 14) num = 0.992181;
			else if (pt <= 18) num = 0.992159;
			else if (pt < 9999) num = 0.992774;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.944705;
			else if (pt <= 3.5) num = 0.977526;
			else if (pt <= 4.5) num = 1;
			else if (pt <= 6.5) num = 0.99665;
			else if (pt <= 10) num = 1;
			else if (pt <= 14) num = 1;
			else if (pt < 9999) num = 1;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.942625;
			else if (pt <= 3.5) num = 0.979907;
			else if (pt <= 5.5) num = 0.987211;
			else if (pt <= 12) num = 0.997746;
			else if (pt < 9999) num = 0.999999;
		}
	}
	else if (idx == -11) { // stat up
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.978818;
			else if (pt <= 5.5) num = 0.986103;
			else if (pt <= 6.5) num = 0.987913;
			else if (pt <= 8) num = 0.989186;
			else if (pt <= 10.5) num = 0.991042;
			else if (pt <= 14) num = 0.992865;
			else if (pt <= 18) num = 0.993177;
			else if (pt < 9999) num = 0.995012;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.976812;
			else if (pt <= 4.5) num = 0.985077;
			else if (pt <= 5.5) num = 0.989537;
			else if (pt <= 6.5) num = 0.99261;
			else if (pt <= 8) num = 0.992858;
			else if (pt <= 10.5) num = 0.991484;
			else if (pt <= 14) num = 0.993958;
			else if (pt <= 18) num = 0.995099;
			else if (pt < 9999) num = 0.997159;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.951165;
			else if (pt <= 3.5) num = 0.982042;
			else if (pt <= 4.5) num = 1.00035;
			else if (pt <= 6.5) num = 1;
			else if (pt <= 10) num = 1;
			else if (pt <= 14) num = 1;
			else if (pt < 9999) num = 1;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.952285;
			else if (pt <= 3.5) num = 0.988946;
			else if (pt <= 5.5) num = 0.995206;
			else if (pt <= 12) num = 1;
			else if (pt < 9999) num = 1.01117;
		}
	}
	else if (idx == -12) { // stat down
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.977419;
			else if (pt <= 5.5) num = 0.984489;
			else if (pt <= 6.5) num = 0.985978;
			else if (pt <= 8) num = 0.987201;
			else if (pt <= 10.5) num = 0.988857;
			else if (pt <= 14) num = 0.989906;
			else if (pt <= 18) num = 0.988245;
			else if (pt < 9999) num = 0.988349;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.96944;
			else if (pt <= 4.5) num = 0.983372;
			else if (pt <= 5.5) num = 0.987528;
			else if (pt <= 6.5) num = 0.99028;
			else if (pt <= 8) num = 0.990514;
			else if (pt <= 10.5) num = 0.988733;
			else if (pt <= 14) num = 0.990321;
			else if (pt <= 18) num = 0.988999;
			else if (pt < 9999) num = 0.987986;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.938956;
			else if (pt <= 3.5) num = 0.97301;
			else if (pt <= 4.5) num = 0.999653;
			else if (pt <= 6.5) num = 0.992216;
			else if (pt <= 10) num = 0.997602;
			else if (pt <= 14) num = 0.99683;
			else if (pt < 9999) num = 0.996159;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.930772;
			else if (pt <= 3.5) num = 0.971151;
			else if (pt <= 5.5) num = 0.979352;
			else if (pt <= 12) num = 0.9896;
			else if (pt < 9999) num = 0.988826;
		}
	}
	if (idx == -13) { // TnP fit syst up
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.978613;
			else if (pt <= 5.5) num = 0.985822;
			else if (pt <= 6.5) num = 0.987338;
			else if (pt <= 8) num = 0.988535;
			else if (pt <= 10.5) num = 0.990339;
			else if (pt <= 14) num = 0.991878;
			else if (pt <= 18) num = 0.991286;
			else if (pt < 9999) num = 0.992211;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.98176;
			else if (pt <= 4.5) num = 0.985291;
			else if (pt <= 5.5) num = 0.98949;
			else if (pt <= 6.5) num = 0.992347;
			else if (pt <= 8) num = 0.992573;
			else if (pt <= 10.5) num = 0.99101;
			else if (pt <= 14) num = 0.993075;
			else if (pt <= 18) num = 0.993063;
			else if (pt < 9999) num = 0.993638;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.949066;
			else if (pt <= 3.5) num = 0.979764;
			else if (pt <= 4.5) num = 1.0019;
			else if (pt <= 6.5) num = 0.99765;
			else if (pt <= 10) num = 1.00022;
			else if (pt <= 14) num = 1;
			else if (pt < 9999) num = 1;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.964941;
			else if (pt <= 3.5) num = 0.985622;
			else if (pt <= 5.5) num = 0.99152;
			else if (pt <= 12) num = 1.00001;
			else if (pt < 9999) num = 1.00055;
		}
	}
	else if (idx == -14) { // TnP fit syst down
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.977633;
			else if (pt <= 5.5) num = 0.984787;
			else if (pt <= 6.5) num = 0.986582;
			else if (pt <= 8) num = 0.987885;
			else if (pt <= 10.5) num = 0.989604;
			else if (pt <= 14) num = 0.99098;
			else if (pt <= 18) num = 0.990308;
			else if (pt < 9999) num = 0.991485;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.964475;
			else if (pt <= 4.5) num = 0.98316;
			else if (pt <= 5.5) num = 0.987586;
			else if (pt <= 6.5) num = 0.990572;
			else if (pt <= 8) num = 0.99083;
			else if (pt <= 10.5) num = 0.989254;
			else if (pt <= 14) num = 0.991287;
			else if (pt <= 18) num = 0.991256;
			else if (pt < 9999) num = 0.991909;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.940343;
			else if (pt <= 3.5) num = 0.975288;
			else if (pt <= 4.5) num = 0.998101;
			else if (pt <= 6.5) num = 0.99565;
			else if (pt <= 10) num = 0.999779;
			else if (pt <= 14) num = 1;
			else if (pt < 9999) num = 1;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.920309;
			else if (pt <= 3.5) num = 0.974193;
			else if (pt <= 5.5) num = 0.982901;
			else if (pt <= 12) num = 0.995479;
			else if (pt < 9999) num = 0.999448;
		}
	}
	return (num / den);
}

////////////////// N   T R A C K    ///////////////

double tnp_weight_muid_nTrack(int nTrack, int idx)
{
	if (idx == 0) {
		if (nTrack <= 35) return 1.00907;
		else if (nTrack <= 60) return 1.00433;
		else if (nTrack <= 90) return 0.999192;
		else if (nTrack <= 120) return 0.999982;
		else if (nTrack <= 155) return 0.996984;
		else if (nTrack <= 190) return 0.987001;
		else return 1.00127;
	}
	if (idx == -11) {
		if (nTrack <= 35) return 1.01043;
		else if (nTrack <= 60) return 1.00533;
		else if (nTrack <= 90) return 1.00028;
		else if (nTrack <= 120) return 1.00201;
		else if (nTrack <= 155) return 1.00084;
		else if (nTrack <= 190) return 0.995623;
		else return 1.02132;
	}
	if (idx == -12) {
		if (nTrack <= 35) return 1.00773;
		else if (nTrack <= 60) return 1.00332;
		else if (nTrack <= 90) return 0.99811;
		else if (nTrack <= 120) return 0.997972;
		else if (nTrack <= 155) return 0.99318;
		else if (nTrack <= 190) return 0.978575;
		else return 0.981994;
	}
	return -1; //default return for bad idx
}*/



///////////////////////////////////////////////////
//                 T R G    P P b                //
///////////////////////////////////////////////////


double tnp_weight_trg_ppb(double pt, double eta, int idx)
{
  double num=1.0, den=0.0;  //intentionaly 0, so if asked for a corrections outside defined range, it returns NaN instead of 1

  // MC
  if (fabs(eta) > 0 && fabs(eta) <= 0.9) { 
    if (pt > 3.3 && pt <= 4.5) den = 0.715416;
    else if (pt <= 5.5) den = 0.914315;
    else if (pt <= 7) den = 0.946779;
    else if (pt <= 9.5) den = 0.959295;
    else if (pt <= 13) den = 0.956631;
    else if (pt <= 18) den = 0.942065;
    else if (pt <= 25) den = 0.923169;
    else if (pt <= 35) den = 0.934265;
    else if (pt <= 50) den = 0.92179;
  }
  else if (fabs(eta) > 0.9 && fabs(eta) <= 1.2) { 
    if (pt > 3.3 && pt <= 4.5) den = 0.797148;
    else if (pt <= 5.5) den = 0.990003;
    else if (pt <= 7) den = 0.992797;
    else if (pt <= 9.5) den = 0.994399;
    else if (pt <= 13) den = 0.995945;
    else if (pt <= 18) den = 0.988519;
    else if (pt <= 25) den = 0.983467;
    else if (pt <= 35) den = 0.965063;
    else if (pt <= 50) den = 0.985891;
  }
  else if (fabs(eta) > 1.2 && fabs(eta) <= 1.6) { 
    if (pt > 2.2 && pt <= 3) den = 0.419801;
    else if (pt <= 4.5) den = 0.823984;
    else if (pt <= 6.5) den = 0.951777;
    else if (pt <= 10) den = 0.963024;
    else if (pt <= 14) den = 0.965916;
    else if (pt <= 25) den = 0.959984;
    else if (pt <= 35) den = 0.944979;
    else if (pt <= 50) den = 0.945456;
  }
  else if (fabs(eta) > 1.6 && fabs(eta) <= 2.1) { 
    if (pt > 1.6 && pt <= 2.2) den = 0.616688;
    else if (pt <= 3) den = 0.795546;
    else if (pt <= 4.5) den = 0.91678;
    else if (pt <= 8) den = 0.920914;
    else if (pt <= 14) den = 0.900374;
    else if (pt <= 25) den = 0.854198;
    else if (pt <= 50) den = 0.836884;
  }
  else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
    if (pt > 1.3 && pt <= 1.6) den = 0.470736;
    else if (pt <= 2.2) den = 0.804351;
    else if (pt <= 3) den = 0.91407;
    else if (pt <= 5.5) den = 0.935357;
    else if (pt <= 12) den = 0.930796;
    else if (pt <= 25) den = 0.884993;
    else if (pt <= 50) den = 0.855078;
  }

  // data
  if (idx == 0) { // nominal
    if (fabs(eta) > 0 && fabs(eta) <= 0.9) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.718429;
      else if (pt <= 5.5) num = 0.921994;
      else if (pt <= 7) num = 0.940028;
      else if (pt <= 9.5) num = 0.940515;
      else if (pt <= 13) num = 0.936412;
      else if (pt <= 18) num = 0.913907;
      else if (pt <= 25) num = 0.893973;
      else if (pt <= 35) num = 0.882136;
      else if (pt <= 50) num = 0.883324;
    }
    else if (fabs(eta) > 0.9 && fabs(eta) <= 1.2) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.885708;
      else if (pt <= 5.5) num = 0.990556;
      else if (pt <= 7) num = 0.994184;
      else if (pt <= 9.5) num = 0.991996;
      else if (pt <= 13) num = 0.995224;
      else if (pt <= 18) num = 0.987769;
      else if (pt <= 25) num = 0.974292;
      else if (pt <= 35) num = 0.934944;
      else if (pt <= 50) num = 0.946611;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 1.6) { 
      if (pt > 2.2 && pt <= 3) num = 0.521198;
      else if (pt <= 4.5) num = 0.849;
      else if (pt <= 6.5) num = 0.96056;
      else if (pt <= 10) num = 0.969339;
      else if (pt <= 14) num = 0.972008;
      else if (pt <= 25) num = 0.973261;
      else if (pt <= 35) num = 0.960692;
      else if (pt <= 50) num = 0.91337;
    }
    else if (fabs(eta) > 1.6 && fabs(eta) <= 2.1) { 
      if (pt > 1.6 && pt <= 2.2) num = 0.684707;
      else if (pt <= 3) num = 0.816278;
      else if (pt <= 4.5) num = 0.908258;
      else if (pt <= 8) num = 0.906016;
      else if (pt <= 14) num = 0.885768;
      else if (pt <= 25) num = 0.861695;
      else if (pt <= 50) num = 0.807972;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 1.3 && pt <= 1.6) num = 0.596021;
      else if (pt <= 2.2) num = 0.865222;
      else if (pt <= 3) num = 0.928704;
      else if (pt <= 5.5) num = 0.948319;
      else if (pt <= 12) num = 0.951024;
      else if (pt <= 25) num = 0.905403;
      else if (pt <= 50) num = 0.751944;
    }
  }
  else if (idx == -11) { // stat up
    if (fabs(eta) > 0 && fabs(eta) <= 0.9) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.720127;
      else if (pt <= 5.5) num = 0.923386;
      else if (pt <= 7) num = 0.941371;
      else if (pt <= 9.5) num = 0.942089;
      else if (pt <= 13) num = 0.938711;
      else if (pt <= 18) num = 0.917832;
      else if (pt <= 25) num = 0.900844;
      else if (pt <= 35) num = 0.894419;
      else if (pt <= 50) num = 0.904105;
    }
    else if (fabs(eta) > 0.9 && fabs(eta) <= 1.2) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.887754;
      else if (pt <= 5.5) num = 0.991488;
      else if (pt <= 7) num = 0.994969;
      else if (pt <= 9.5) num = 0.99298;
      else if (pt <= 13) num = 0.996328;
      else if (pt <= 18) num = 0.990382;
      else if (pt <= 25) num = 1;
      else if (pt <= 35) num = 0.95136;
      else if (pt <= 50) num = 0.968864;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 1.6) { 
      if (pt > 2.2 && pt <= 3) num = 0.524077;
      else if (pt <= 4.5) num = 0.850728;
      else if (pt <= 6.5) num = 0.961841;
      else if (pt <= 10) num = 0.970871;
      else if (pt <= 14) num = 0.974644;
      else if (pt <= 25) num = 0.977027;
      else if (pt <= 35) num = 0.972207;
      else if (pt <= 50) num = 0.944911;
    }
    else if (fabs(eta) > 1.6 && fabs(eta) <= 2.1) { 
      if (pt > 1.6 && pt <= 2.2) num = 0.688302;
      else if (pt <= 3) num = 0.818528;
      else if (pt <= 4.5) num = 0.909871;
      else if (pt <= 8) num = 0.90777;
      else if (pt <= 14) num = 0.88936;
      else if (pt <= 25) num = 0.870578;
      else if (pt <= 50) num = 0.835254;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 1.3 && pt <= 1.6) num = 0.60151;
      else if (pt <= 2.2) num = 0.868549;
      else if (pt <= 3) num = 0.93108;
      else if (pt <= 5.5) num = 0.949987;
      else if (pt <= 12) num = 0.953617;
      else if (pt <= 25) num = 0.915019;
      else if (pt <= 50) num = 0.842972;
    }
  }
  else if (idx == -12) { // stat down
    if (fabs(eta) > 0 && fabs(eta) <= 0.9) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.716711;
      else if (pt <= 5.5) num = 0.920586;
      else if (pt <= 7) num = 0.938667;
      else if (pt <= 9.5) num = 0.938917;
      else if (pt <= 13) num = 0.934065;
      else if (pt <= 18) num = 0.909881;
      else if (pt <= 25) num = 0.886855;
      else if (pt <= 35) num = 0.869172;
      else if (pt <= 50) num = 0.86038;
    }
    else if (fabs(eta) > 0.9 && fabs(eta) <= 1.2) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.883645;
      else if (pt <= 5.5) num = 0.989584;
      else if (pt <= 7) num = 0.9934;
      else if (pt <= 9.5) num = 0.990935;
      else if (pt <= 13) num = 0.993954;
      else if (pt <= 18) num = 0.984773;
      else if (pt <= 25) num = 0.966908;
      else if (pt <= 35) num = 0.916603;
      else if (pt <= 50) num = 0.916029;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 1.6) { 
      if (pt > 2.2 && pt <= 3) num = 0.518337;
      else if (pt <= 4.5) num = 0.847264;
      else if (pt <= 6.5) num = 0.959257;
      else if (pt <= 10) num = 0.967767;
      else if (pt <= 14) num = 0.969227;
      else if (pt <= 25) num = 0.969198;
      else if (pt <= 35) num = 0.9467;
      else if (pt <= 50) num = 0.873367;
    }
    else if (fabs(eta) > 1.6 && fabs(eta) <= 2.1) { 
      if (pt > 1.6 && pt <= 2.2) num = 0.681104;
      else if (pt <= 3) num = 0.814019;
      else if (pt <= 4.5) num = 0.908258;
      else if (pt <= 8) num = 0.90425;
      else if (pt <= 14) num = 0.882127;
      else if (pt <= 25) num = 0.852572;
      else if (pt <= 50) num = 0.779374;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 1.3 && pt <= 1.6) num = 0.590535;
      else if (pt <= 2.2) num = 0.861858;
      else if (pt <= 3) num = 0.92629;
      else if (pt <= 5.5) num = 0.946635;
      else if (pt <= 12) num = 0.948372;
      else if (pt <= 25) num = 0.895353;
      else if (pt <= 50) num = 0.677999;
    }
  }
  if (idx == -13) { // TnP fit syst up
    if (fabs(eta) > 0 && fabs(eta) <= 0.9) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.718588;
      else if (pt <= 5.5) num = 0.922126;
      else if (pt <= 7) num = 0.940199;
      else if (pt <= 9.5) num = 0.940714;
      else if (pt <= 13) num = 0.936624;
      else if (pt <= 18) num = 0.914144;
      else if (pt <= 25) num = 0.89441;
      else if (pt <= 35) num = 0.882908;
      else if (pt <= 50) num = 0.884255;
    }
    else if (fabs(eta) > 0.9 && fabs(eta) <= 1.2) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.886374;
      else if (pt <= 5.5) num = 0.990666;
      else if (pt <= 7) num = 0.994288;
      else if (pt <= 9.5) num = 0.992104;
      else if (pt <= 13) num = 0.995363;
      else if (pt <= 18) num = 0.987955;
      else if (pt <= 25) num = 0.974963;
      else if (pt <= 35) num = 0.936499;
      else if (pt <= 50) num = 0.948594;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 1.6) { 
      if (pt > 2.2 && pt <= 3) num = 0.521832;
      else if (pt <= 4.5) num = 0.849255;
      else if (pt <= 6.5) num = 0.960815;
      else if (pt <= 10) num = 0.969595;
      else if (pt <= 14) num = 0.9723;
      else if (pt <= 25) num = 0.973913;
      else if (pt <= 35) num = 0.961954;
      else if (pt <= 50) num = 0.91492;
    }
    else if (fabs(eta) > 1.6 && fabs(eta) <= 2.1) { 
      if (pt > 1.6 && pt <= 2.2) num = 0.689397;
      else if (pt <= 3) num = 0.820294;
      else if (pt <= 4.5) num = 0.910651;
      else if (pt <= 8) num = 0.907799;
      else if (pt <= 14) num = 0.887653;
      else if (pt <= 25) num = 0.86381;
      else if (pt <= 50) num = 0.810186;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 1.3 && pt <= 1.6) num = 0.598604;
      else if (pt <= 2.2) num = 0.866656;
      else if (pt <= 3) num = 0.929481;
      else if (pt <= 5.5) num = 0.949008;
      else if (pt <= 12) num = 0.95239;
      else if (pt <= 25) num = 0.90769;
      else if (pt <= 50) num = 0.754614;
    }
  }
  else if (idx == -14) { // TnP fit syst down
    if (fabs(eta) > 0 && fabs(eta) <= 0.9) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.718269;
      else if (pt <= 5.5) num = 0.921862;
      else if (pt <= 7) num = 0.939857;
      else if (pt <= 9.5) num = 0.940315;
      else if (pt <= 13) num = 0.9362;
      else if (pt <= 18) num = 0.91367;
      else if (pt <= 25) num = 0.893536;
      else if (pt <= 35) num = 0.881363;
      else if (pt <= 50) num = 0.882393;
    }
    else if (fabs(eta) > 0.9 && fabs(eta) <= 1.2) { 
      if (pt > 3.3 && pt <= 4.5) num = 0.885041;
      else if (pt <= 5.5) num = 0.990446;
      else if (pt <= 7) num = 0.994081;
      else if (pt <= 9.5) num = 0.991888;
      else if (pt <= 13) num = 0.995085;
      else if (pt <= 18) num = 0.987582;
      else if (pt <= 25) num = 0.973621;
      else if (pt <= 35) num = 0.933389;
      else if (pt <= 50) num = 0.944628;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 1.6) { 
      if (pt > 2.2 && pt <= 3) num = 0.520565;
      else if (pt <= 4.5) num = 0.848745;
      else if (pt <= 6.5) num = 0.960305;
      else if (pt <= 10) num = 0.969084;
      else if (pt <= 14) num = 0.971717;
      else if (pt <= 25) num = 0.97261;
      else if (pt <= 35) num = 0.959429;
      else if (pt <= 50) num = 0.91182;
    }
    else if (fabs(eta) > 1.6 && fabs(eta) <= 2.1) { 
      if (pt > 1.6 && pt <= 2.2) num = 0.680018;
      else if (pt <= 3) num = 0.812262;
      else if (pt <= 4.5) num = 0.905865;
      else if (pt <= 8) num = 0.904234;
      else if (pt <= 14) num = 0.883883;
      else if (pt <= 25) num = 0.85958;
      else if (pt <= 50) num = 0.805759;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 1.3 && pt <= 1.6) num = 0.593439;
      else if (pt <= 2.2) num = 0.863788;
      else if (pt <= 3) num = 0.927928;
      else if (pt <= 5.5) num = 0.947629;
      else if (pt <= 12) num = 0.949657;
      else if (pt <= 25) num = 0.903116;
      else if (pt <= 50) num = 0.749274;
    }
  }
  return (num/den);
}

#endif //#ifndef tnp_weight_h
