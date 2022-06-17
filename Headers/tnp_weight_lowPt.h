#ifndef tnp_weight_h
#define tnp_weight_h

#include "TMath.h"


// IN THIS FILE YOU WILL FIND:
// ++++++++++++++


// - TrkM:    ///// DO NOT USE  
//	(tnp_weight_trkM_ppb)
//   * idx = 0: nominal
//   * idx = -11: stat variation,  +1 sigma
//   * idx = -12: stat variation,  -1 sigma
//   * idx = -13: syst variation,  +1 sigma
//   * idx = -14: syst variation,  -1 sigma
//
//      (tnp_weight_trkM_eta)
//   * idx = 0: nominal


// - MuID: (Note: there are two options)
//
//	- starting from tracker muon probes.
//	- the syst. unc. includes the difference from starting with general tracks.
//	(tnp_weight_muid_from_tm_ppb)
//   * idx = 0: binned, nominal
//   * idx = -11: binned, stat up
//   * idx = -12: binned, stat down
//   * idx = -13: binned, syst up
//   * idx = -14: binned, syst down
//
//	- starting from general track probes.
//	- the syst. unc. includes the difference from starting with tracker muons.
//	(tnp_weight_muid_from_gt_ppb)
//   * idx = 0: binned, nominal
//   * idx = -11: binned, stat up
//   * idx = -12: binned, stat down
//   * idx = -13: binned, syst up
//   * idx = -14: binned, syst down


// - Trigger: 
//	(tnp_weight_trg_ppb)
//   * idx = 0: nominal
//   * idx = -11: stat variation,  +1 sigma
//   * idx = -12: stat variation,  -1 sigma
//   * idx = -13: syst variation,  +1 sigma
//   * idx = -14: syst variation,  -1 sigma


// THE INDIVIDUAL SFs
// ++++++++++++++++++
double tnp_weight_trkM_ppb(double pt, double eta, int idx = 0); //not needed now
double tnp_weight_muid_from_tm_ppb(double pt, double eta, int idx = 0);
double tnp_weight_muid_from_gt_ppb(double pt, double eta, int idx = 0);
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




///////////////////////////////////////////////////
//               M U I D      P P b              //
///////////////////////////////////////////////////

double tnp_weight_muid_from_tm_ppb(double pt, double eta, int idx) 
{
  double num=1.0, den=0.0;  //intentionally 0, so if asked for a corrections outside defined range, it returns NaN instead of 1

  // MC
  if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) den = 0.980686;
    else if (pt <= 4.3) den = 0.977053;
    else if (pt <= 4.8) den = 0.984234;
    else if (pt <= 5.5) den = 0.986057;
    else if (pt <= 6.5) den = 0.988873;
    else if (pt <= 9.5) den = 0.990574;
    else if (pt <= 13) den = 0.991222;
    else if (pt <= 25) den = 0.993725;
  }
  else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) den = 0.978075;
    else if (pt <= 4.3) den = 0.977022;
    else if (pt <= 4.8) den = 0.980481;
    else if (pt <= 5.5) den = 0.984118;
    else if (pt <= 6.5) den = 0.985001;
    else if (pt <= 9.5) den = 0.987524;
    else if (pt <= 13) den = 0.989992;
    else if (pt <= 25) den = 0.991419;
  }
  else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) den = 0.933851;
    else if (pt <= 2.5) den = 0.973857;
    else if (pt <= 3.3) den = 0.990994;
    else if (pt <= 4.3) den = 0.988505;
    else if (pt <= 5.5) den = 0.991213;
    else if (pt <= 6.5) den = 0.992654;
    else if (pt <= 9.5) den = 0.993181;
    else if (pt <= 13) den = 0.993302;
    else if (pt <= 25) den = 0.993919;
  }
  else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) den = 0.945507;
    else if (pt <= 1.9) den = 0.966632;
    else if (pt <= 2.5) den = 0.988519;
    else if (pt <= 3.3) den = 0.995559;
    else if (pt <= 4.8) den = 0.997657;
    else if (pt <= 6.5) den = 0.997708;
    else if (pt <= 9.5) den = 0.997544;
    else if (pt <= 25) den = 0.997464;
  }
  else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) den = 0.953999;
    else if (pt <= 1.9) den = 0.979258;
    else if (pt <= 2.5) den = 0.991765;
    else if (pt <= 3.3) den = 0.994563;
    else if (pt <= 4.8) den = 0.996016;
    else if (pt <= 6.5) den = 0.995161;
    else if (pt <= 9.5) den = 0.99642;
    else if (pt <= 25) den = 0.997426;
  }

  // data
  if (idx == -10) { // nominal
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.975837;
    else if (pt <= 4.3) num = 0.978958;
    else if (pt <= 4.8) num = 0.984149;
    else if (pt <= 5.5) num = 0.986286;
    else if (pt <= 6.5) num = 0.987535;
    else if (pt <= 9.5) num = 0.988965;
    else if (pt <= 13) num = 0.991972;
    else if (pt <= 25) num = 0.991382;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.973491;
    else if (pt <= 4.3) num = 0.977965;
    else if (pt <= 4.8) num = 0.976335;
    else if (pt <= 5.5) num = 0.988008;
    else if (pt <= 6.5) num = 0.989575;
    else if (pt <= 9.5) num = 0.990985;
    else if (pt <= 13) num = 0.991244;
    else if (pt <= 25) num = 0.988707;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.893867;
    else if (pt <= 2.5) num = 0.978111;
    else if (pt <= 3.3) num = 0.995851;
    else if (pt <= 4.3) num = 0.991299;
    else if (pt <= 5.5) num = 0.992035;
    else if (pt <= 6.5) num = 0.99449;
    else if (pt <= 9.5) num = 0.992;
    else if (pt <= 13) num = 0.991844;
    else if (pt <= 25) num = 0.995781;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.944717;
    else if (pt <= 1.9) num = 0.949624;
    else if (pt <= 2.5) num = 0.954654;
    else if (pt <= 3.3) num = 0.982356;
    else if (pt <= 4.8) num = 1;
    else if (pt <= 6.5) num = 0.994002;
    else if (pt <= 9.5) num = 0.997266;
    else if (pt <= 25) num = 1;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.9474;
    else if (pt <= 1.9) num = 0.971973;
    else if (pt <= 2.5) num = 0.999645;
    else if (pt <= 3.3) num = 0.995336;
    else if (pt <= 4.8) num = 0.995355;
    else if (pt <= 6.5) num = 0.999999;
    else if (pt <= 9.5) num = 0.998147;
    else if (pt <= 25) num = 1;
    }
  }
  else if (idx == -11) { // stat up
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.976934;
    else if (pt <= 4.3) num = 0.979994;
    else if (pt <= 4.8) num = 0.985191;
    else if (pt <= 5.5) num = 0.987228;
    else if (pt <= 6.5) num = 0.988463;
    else if (pt <= 9.5) num = 0.989732;
    else if (pt <= 13) num = 0.993163;
    else if (pt <= 25) num = 0.99301;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.975305;
    else if (pt <= 4.3) num = 0.979704;
    else if (pt <= 4.8) num = 0.978425;
    else if (pt <= 5.5) num = 0.989554;
    else if (pt <= 6.5) num = 0.991092;
    else if (pt <= 9.5) num = 0.992218;
    else if (pt <= 13) num = 0.993403;
    else if (pt <= 25) num = 0.991853;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.910695;
    else if (pt <= 2.5) num = 0.985128;
    else if (pt <= 3.3) num = 0.997505;
    else if (pt <= 4.3) num = 0.992489;
    else if (pt <= 5.5) num = 0.993287;
    else if (pt <= 6.5) num = 0.996077;
    else if (pt <= 9.5) num = 0.993344;
    else if (pt <= 13) num = 0.994032;
    else if (pt <= 25) num = 0.998681;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.960473;
    else if (pt <= 1.9) num = 0.957915;
    else if (pt <= 2.5) num = 0.961807;
    else if (pt <= 3.3) num = 0.98831;
    else if (pt <= 4.8) num = 1;
    else if (pt <= 6.5) num = 0.998323;
    else if (pt <= 9.5) num = 1;
    else if (pt <= 25) num = 1;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.960706;
    else if (pt <= 1.9) num = 0.984726;
    else if (pt <= 2.5) num = 1;
    else if (pt <= 3.3) num = 1;
    else if (pt <= 4.8) num = 1;
    else if (pt <= 6.5) num = 1;
    else if (pt <= 9.5) num = 1;
    else if (pt <= 25) num = 1;
    }
  }
  else if (idx == -12) { // stat down
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.974717;
    else if (pt <= 4.3) num = 0.9779;
    else if (pt <= 4.8) num = 0.983079;
    else if (pt <= 5.5) num = 0.985316;
    else if (pt <= 6.5) num = 0.986576;
    else if (pt <= 9.5) num = 0.988177;
    else if (pt <= 13) num = 0.990713;
    else if (pt <= 25) num = 0.98965;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.971626;
    else if (pt <= 4.3) num = 0.976176;
    else if (pt <= 4.8) num = 0.974178;
    else if (pt <= 5.5) num = 0.986392;
    else if (pt <= 6.5) num = 0.987946;
    else if (pt <= 9.5) num = 0.9897;
    else if (pt <= 13) num = 0.988931;
    else if (pt <= 25) num = 0.985316;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.877373;
    else if (pt <= 2.5) num = 0.971155;
    else if (pt <= 3.3) num = 0.994163;
    else if (pt <= 4.3) num = 0.990098;
    else if (pt <= 5.5) num = 0.990777;
    else if (pt <= 6.5) num = 0.992848;
    else if (pt <= 9.5) num = 0.990615;
    else if (pt <= 13) num = 0.989532;
    else if (pt <= 25) num = 0.99266;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.929058;
    else if (pt <= 1.9) num = 0.941363;
    else if (pt <= 2.5) num = 0.947523;
    else if (pt <= 3.3) num = 0.976305;
    else if (pt <= 4.8) num = 0.997512;
    else if (pt <= 6.5) num = 0.989686;
    else if (pt <= 9.5) num = 0.992729;
    else if (pt <= 25) num = 0.998114;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.93473;
    else if (pt <= 1.9) num = 0.959551;
    else if (pt <= 2.5) num = 0.988348;
    else if (pt <= 3.3) num = 0.986372;
    else if (pt <= 4.8) num = 0.988683;
    else if (pt <= 6.5) num = 0.994846;
    else if (pt <= 9.5) num = 0.989809;
    else if (pt <= 25) num = 0.995349;
    }
  }
  /*if (idx == -13) { // TnP fit syst up
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.97623;
    else if (pt <= 4.3) num = 0.979354;
    else if (pt <= 4.8) num = 0.984523;
    else if (pt <= 5.5) num = 0.986604;
    else if (pt <= 6.5) num = 0.987806;
    else if (pt <= 9.5) num = 0.989231;
    else if (pt <= 13) num = 0.992255;
    else if (pt <= 25) num = 0.991674;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.97379;
    else if (pt <= 4.3) num = 0.97838;
    else if (pt <= 4.8) num = 0.97677;
    else if (pt <= 5.5) num = 0.988493;
    else if (pt <= 6.5) num = 0.990065;
    else if (pt <= 9.5) num = 0.991371;
    else if (pt <= 13) num = 0.991502;
    else if (pt <= 25) num = 0.988915;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.956071;
    else if (pt <= 2.5) num = 0.984199;
    else if (pt <= 3.3) num = 0.999842;
    else if (pt <= 4.3) num = 0.993427;
    else if (pt <= 5.5) num = 0.993139;
    else if (pt <= 6.5) num = 0.995022;
    else if (pt <= 9.5) num = 0.992277;
    else if (pt <= 13) num = 0.992177;
    else if (pt <= 25) num = 0.996156;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.981789;
    else if (pt <= 1.9) num = 0.959144;
    else if (pt <= 2.5) num = 0.958808;
    else if (pt <= 3.3) num = 0.983599;
    else if (pt <= 4.8) num = 1.00087;
    else if (pt <= 6.5) num = 0.995318;
    else if (pt <= 9.5) num = 0.998385;
    else if (pt <= 25) num = 1.00037;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.978262;
    else if (pt <= 1.9) num = 0.97805;
    else if (pt <= 2.5) num = 1.00469;
    else if (pt <= 3.3) num = 0.999661;
    else if (pt <= 4.8) num = 0.999456;
    else if (pt <= 6.5) num = 1.00308;
    else if (pt <= 9.5) num = 0.999173;
    else if (pt <= 25) num = 1;
    }
  }
  else if (idx == -14) { // TnP fit syst down
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.975444;
    else if (pt <= 4.3) num = 0.978562;
    else if (pt <= 4.8) num = 0.983775;
    else if (pt <= 5.5) num = 0.985968;
    else if (pt <= 6.5) num = 0.987265;
    else if (pt <= 9.5) num = 0.9887;
    else if (pt <= 13) num = 0.99169;
    else if (pt <= 25) num = 0.991091;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.973192;
    else if (pt <= 4.3) num = 0.977551;
    else if (pt <= 4.8) num = 0.975899;
    else if (pt <= 5.5) num = 0.987522;
    else if (pt <= 6.5) num = 0.989085;
    else if (pt <= 9.5) num = 0.990598;
    else if (pt <= 13) num = 0.990987;
    else if (pt <= 25) num = 0.988499;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.831663;
    else if (pt <= 2.5) num = 0.972023;
    else if (pt <= 3.3) num = 0.99186;
    else if (pt <= 4.3) num = 0.989172;
    else if (pt <= 5.5) num = 0.990932;
    else if (pt <= 6.5) num = 0.993957;
    else if (pt <= 9.5) num = 0.991723;
    else if (pt <= 13) num = 0.991511;
    else if (pt <= 25) num = 0.995406;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.907644;
    else if (pt <= 1.9) num = 0.940103;
    else if (pt <= 2.5) num = 0.950501;
    else if (pt <= 3.3) num = 0.981114;
    else if (pt <= 4.8) num = 0.999127;
    else if (pt <= 6.5) num = 0.992685;
    else if (pt <= 9.5) num = 0.996146;
    else if (pt <= 25) num = 0.999626;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.916538;
    else if (pt <= 1.9) num = 0.965897;
    else if (pt <= 2.5) num = 0.994602;
    else if (pt <= 3.3) num = 0.99101;
    else if (pt <= 4.8) num = 0.991253;
    else if (pt <= 6.5) num = 0.996923;
    else if (pt <= 9.5) num = 0.997121;
    else if (pt <= 25) num = 1;
    }
  }*/
  else if (idx == -13) { // TnP fit syst up
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
    if (pt > 3.3 && pt <= 3.8) num = 1.0503;
    else if (pt > 3.8 && pt <= 4.3) num = 0.981988;
    else if (pt > 4.3 && pt <= 4.8) num = 0.992007;
    else if (pt > 4.8 && pt <= 5.5) num = 0.99053;
    else if (pt > 5.5 && pt <= 6.5) num = 0.989002;
    else if (pt > 6.5 && pt <= 9.5) num = 0.996982;
    else if (pt > 9.5 && pt <= 13) num = 0.996777;
    else if (pt > 13 && pt <= 25) num = 1.00311;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) {
    if (pt > 3.3 && pt <= 3.8) num = 0.987069;
    else if (pt > 3.8 && pt <= 4.3) num = 0.980541;
    else if (pt > 4.3 && pt <= 4.8) num = 0.98088;
    else if (pt > 4.8 && pt <= 5.5) num = 0.996859;
    else if (pt > 5.5 && pt <= 6.5) num = 1.00548;
    else if (pt > 6.5 && pt <= 9.5) num = 1.00529;
    else if (pt > 9.5 && pt <= 13) num = 0.993194;
    else if (pt > 13 && pt <= 25) num = 0.993462;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) {
    if (pt > 1.2 && pt <= 1.9) num = 1.05174;
    else if (pt > 1.9 && pt <= 2.5) num = 1.01482;
    else if (pt > 2.5 && pt <= 3.3) num = 1.01936;
    else if (pt > 3.3 && pt <= 4.3) num = 1.00056;
    else if (pt > 4.3 && pt <= 5.5) num = 0.997446;
    else if (pt > 5.5 && pt <= 6.5) num = 1.01523;
    else if (pt > 6.5 && pt <= 9.5) num = 1.00226;
    else if (pt > 9.5 && pt <= 13) num = 0.997151;
    else if (pt > 13 && pt <= 25) num = 1.01032;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) {
    if (pt > 0.8 && pt <= 1.3) num = 1.12092;
    else if (pt > 1.3 && pt <= 1.9) num = 1.00815;
    else if (pt > 1.9 && pt <= 2.5) num = 0.958995;
    else if (pt > 2.5 && pt <= 3.3) num = 0.984327;
    else if (pt > 3.3 && pt <= 4.8) num = 1.01401;
    else if (pt > 4.8 && pt <= 6.5) num = 0.999521;
    else if (pt > 6.5 && pt <= 9.5) num = 0.999052;
    else if (pt > 9.5 && pt <= 25) num = 1.00795;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) {
    if (pt > 0.8 && pt <= 1.3) num = 1.05235;
    else if (pt > 1.3 && pt <= 1.9) num = 1.02464;
    else if (pt > 1.9 && pt <= 2.5) num = 1.03245;
    else if (pt > 2.5 && pt <= 3.3) num = 1.02162;
    else if (pt > 3.3 && pt <= 4.8) num = 1.0023;
    else if (pt > 4.8 && pt <= 6.5) num = 1.00315;
    else if (pt > 6.5 && pt <= 9.5) num = 1.01121;
    else if (pt > 9.5 && pt <= 25) num = 1.00532;
    }
  }
  else if (idx == -14) { // TnP fit syst down
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
    if (pt > 3.3 && pt <= 3.8) num = 0.901369;
    else if (pt > 3.8 && pt <= 4.3) num = 0.975928;
    else if (pt > 4.3 && pt <= 4.8) num = 0.976291;
    else if (pt > 4.8 && pt <= 5.5) num = 0.982042;
    else if (pt > 5.5 && pt <= 6.5) num = 0.986069;
    else if (pt > 6.5 && pt <= 9.5) num = 0.980948;
    else if (pt > 9.5 && pt <= 13) num = 0.987167;
    else if (pt > 13 && pt <= 25) num = 0.979649;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) {
    if (pt > 3.3 && pt <= 3.8) num = 0.959913;
    else if (pt > 3.8 && pt <= 4.3) num = 0.975389;
    else if (pt > 4.3 && pt <= 4.8) num = 0.97179;
    else if (pt > 4.8 && pt <= 5.5) num = 0.979157;
    else if (pt > 5.5 && pt <= 6.5) num = 0.973669;
    else if (pt > 6.5 && pt <= 9.5) num = 0.976678;
    else if (pt > 9.5 && pt <= 13) num = 0.989294;
    else if (pt > 13 && pt <= 25) num = 0.983952;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) {
    if (pt > 1.2 && pt <= 1.9) num = 0.735994;
    else if (pt > 1.9 && pt <= 2.5) num = 0.941403;
    else if (pt > 2.5 && pt <= 3.3) num = 0.97234;
    else if (pt > 3.3 && pt <= 4.3) num = 0.982036;
    else if (pt > 4.3 && pt <= 5.5) num = 0.986624;
    else if (pt > 5.5 && pt <= 6.5) num = 0.973746;
    else if (pt > 6.5 && pt <= 9.5) num = 0.981743;
    else if (pt > 9.5 && pt <= 13) num = 0.986537;
    else if (pt > 13 && pt <= 25) num = 0.981238;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) {
    if (pt > 0.8 && pt <= 1.3) num = 0.768517;
    else if (pt > 1.3 && pt <= 1.9) num = 0.891094;
    else if (pt > 1.9 && pt <= 2.5) num = 0.950314;
    else if (pt > 2.5 && pt <= 3.3) num = 0.980385;
    else if (pt > 3.3 && pt <= 4.8) num = 0.985992;
    else if (pt > 4.8 && pt <= 6.5) num = 0.988483;
    else if (pt > 6.5 && pt <= 9.5) num = 0.99548;
    else if (pt > 9.5 && pt <= 25) num = 0.992046;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) {
    if (pt > 0.8 && pt <= 1.3) num = 0.842447;
    else if (pt > 1.3 && pt <= 1.9) num = 0.919303;
    else if (pt > 1.9 && pt <= 2.5) num = 0.966838;
    else if (pt > 2.5 && pt <= 3.3) num = 0.969056;
    else if (pt > 3.3 && pt <= 4.8) num = 0.988411;
    else if (pt > 4.8 && pt <= 6.5) num = 0.996857;
    else if (pt > 6.5 && pt <= 9.5) num = 0.985081;
    else if (pt > 9.5 && pt <= 25) num = 0.994675;
    }
  }
  return (num/den);
}

double tnp_weight_muid_from_gt_ppb(double pt, double eta, int idx) 
{
  double num=1.0, den=0.0;  //intentionally 0, so if asked for a corrections outside defined range, it returns NaN instead of 1

  // MC
  if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) den = 0.735228;
    else if (pt <= 4.3) den = 0.913824;
    else if (pt <= 4.8) den = 0.962282;
    else if (pt <= 5.5) den = 0.976624;
    else if (pt <= 6.5) den = 0.986233;
    else if (pt <= 9.5) den = 0.989341;
    else if (pt <= 13) den = 0.988557;
    else if (pt <= 25) den = 0.990642;
  }
  else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) den = 0.74997;
    else if (pt <= 4.3) den = 0.942656;
    else if (pt <= 4.8) den = 0.969536;
    else if (pt <= 5.5) den = 0.979158;
    else if (pt <= 6.5) den = 0.983761;
    else if (pt <= 9.5) den = 0.985909;
    else if (pt <= 13) den = 0.988763;
    else if (pt <= 25) den = 0.987282;
  }
  else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) den = 0.750443;
    else if (pt <= 2.5) den = 0.785866;
    else if (pt <= 3.3) den = 0.929194;
    else if (pt <= 4.3) den = 0.964449;
    else if (pt <= 5.5) den = 0.983257;
    else if (pt <= 6.5) den = 0.989873;
    else if (pt <= 9.5) den = 0.991802;
    else if (pt <= 13) den = 0.993836;
    else if (pt <= 25) den = 0.993645;
  }
  else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) den = 0.715964;
    else if (pt <= 1.9) den = 0.862301;
    else if (pt <= 2.5) den = 0.969408;
    else if (pt <= 3.3) den = 0.992414;
    else if (pt <= 4.8) den = 0.996659;
    else if (pt <= 6.5) den = 0.997054;
    else if (pt <= 9.5) den = 0.996824;
    else if (pt <= 25) den = 0.996505;
  }
  else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) den = 0.636735;
    else if (pt <= 1.9) den = 0.931838;
    else if (pt <= 2.5) den = 0.981195;
    else if (pt <= 3.3) den = 0.992437;
    else if (pt <= 4.8) den = 0.994233;
    else if (pt <= 6.5) den = 0.995678;
    else if (pt <= 9.5) den = 0.996339;
    else if (pt <= 25) den = 0.996812;
  }

  // data
  if (idx == -10) { // nominal
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.787421;
    else if (pt <= 4.3) num = 0.912796;
    else if (pt <= 4.8) num = 0.954525;
    else if (pt <= 5.5) num = 0.972659;
    else if (pt <= 6.5) num = 0.986336;
    else if (pt <= 9.5) num = 0.979731;
    else if (pt <= 13) num = 0.994089;
    else if (pt <= 25) num = 0.999999;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.756864;
    else if (pt <= 4.3) num = 0.941113;
    else if (pt <= 4.8) num = 0.960963;
    else if (pt <= 5.5) num = 0.974235;
    else if (pt <= 6.5) num = 0.972451;
    else if (pt <= 9.5) num = 0.975086;
    else if (pt <= 13) num = 0.991944;
    else if (pt <= 25) num = 0.989312;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.601708;
    else if (pt <= 2.5) num = 0.760087;
    else if (pt <= 3.3) num = 0.912023;
    else if (pt <= 4.3) num = 0.958379;
    else if (pt <= 5.5) num = 0.978818;
    else if (pt <= 6.5) num = 0.971025;
    else if (pt <= 9.5) num = 0.980384;
    else if (pt <= 13) num = 0.987078;
    else if (pt <= 25) num = 0.980972;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.584929;
    else if (pt <= 1.9) num = 0.795611;
    else if (pt <= 2.5) num = 0.934962;
    else if (pt <= 3.3) num = 0.980778;
    else if (pt <= 4.8) num = 0.985033;
    else if (pt <= 6.5) num = 0.987994;
    else if (pt <= 9.5) num = 0.997937;
    else if (pt <= 25) num = 0.991101;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.565378;
    else if (pt <= 1.9) num = 0.875121;
    else if (pt <= 2.5) num = 0.956919;
    else if (pt <= 3.3) num = 0.967342;
    else if (pt <= 4.8) num = 0.999166;
    else if (pt <= 6.5) num = 0.999877;
    else if (pt <= 9.5) num = 0.985041;
    else if (pt <= 25) num = 0.994063;
    }
  }
  else if (idx == -11) { // stat up
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.794567;
    else if (pt <= 4.3) num = 0.920089;
    else if (pt <= 4.8) num = 0.961943;
    else if (pt <= 5.5) num = 0.97914;
    else if (pt <= 6.5) num = 0.991759;
    else if (pt <= 9.5) num = 0.984294;
    else if (pt <= 13) num = 0.997625;
    else if (pt <= 25) num = 1;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.769775;
    else if (pt <= 4.3) num = 0.95577;
    else if (pt <= 4.8) num = 0.972527;
    else if (pt <= 5.5) num = 0.985572;
    else if (pt <= 6.5) num = 0.982669;
    else if (pt <= 9.5) num = 0.982623;
    else if (pt <= 13) num = 0.997697;
    else if (pt <= 25) num = 0.99902;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.763388;
    else if (pt <= 2.5) num = 0.813375;
    else if (pt <= 3.3) num = 0.926365;
    else if (pt <= 4.3) num = 0.96934;
    else if (pt <= 5.5) num = 0.986824;
    else if (pt <= 6.5) num = 0.981565;
    else if (pt <= 9.5) num = 0.988208;
    else if (pt <= 13) num = 0.994233;
    else if (pt <= 25) num = 0.994254;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.607853;
    else if (pt <= 1.9) num = 0.857312;
    else if (pt <= 2.5) num = 0.97162;
    else if (pt <= 3.3) num = 0.990243;
    else if (pt <= 4.8) num = 0.991935;
    else if (pt <= 6.5) num = 0.995231;
    else if (pt <= 9.5) num = 1;
    else if (pt <= 25) num = 0.997957;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.592198;
    else if (pt <= 1.9) num = 0.93141;
    else if (pt <= 2.5) num = 0.976296;
    else if (pt <= 3.3) num = 0.986423;
    else if (pt <= 4.8) num = 1;
    else if (pt <= 6.5) num = 1;
    else if (pt <= 9.5) num = 0.995927;
    else if (pt <= 25) num = 0.999999;
    }
  }
  else if (idx == -12) { // stat down
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.780428;
    else if (pt <= 4.3) num = 0.90557;
    else if (pt <= 4.8) num = 0.947139;
    else if (pt <= 5.5) num = 0.966034;
    else if (pt <= 6.5) num = 0.980194;
    else if (pt <= 9.5) num = 0.975137;
    else if (pt <= 13) num = 0.987096;
    else if (pt <= 25) num = 0.993309;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.74457;
    else if (pt <= 4.3) num = 0.926963;
    else if (pt <= 4.8) num = 0.946239;
    else if (pt <= 5.5) num = 0.961295;
    else if (pt <= 6.5) num = 0.960711;
    else if (pt <= 9.5) num = 0.967117;
    else if (pt <= 13) num = 0.980092;
    else if (pt <= 25) num = 0.975016;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.580589;
    else if (pt <= 2.5) num = 0.740724;
    else if (pt <= 3.3) num = 0.900235;
    else if (pt <= 4.3) num = 0.947688;
    else if (pt <= 5.5) num = 0.969394;
    else if (pt <= 6.5) num = 0.958748;
    else if (pt <= 9.5) num = 0.970751;
    else if (pt <= 13) num = 0.978703;
    else if (pt <= 25) num = 0.960943;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.570259;
    else if (pt <= 1.9) num = 0.769939;
    else if (pt <= 2.5) num = 0.91913;
    else if (pt <= 3.3) num = 0.971293;
    else if (pt <= 4.8) num = 0.975729;
    else if (pt <= 6.5) num = 0.979439;
    else if (pt <= 9.5) num = 0.990268;
    else if (pt <= 25) num = 0.983273;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.545086;
    else if (pt <= 1.9) num = 0.845859;
    else if (pt <= 2.5) num = 0.925402;
    else if (pt <= 3.3) num = 0.947;
    else if (pt <= 4.8) num = 0.985216;
    else if (pt <= 6.5) num = 0.988129;
    else if (pt <= 9.5) num = 0.968793;
    else if (pt <= 25) num = 0.975186;
    }
  }
  if (idx == -13) { // TnP fit syst up
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.975861;
    else if (pt <= 4.3) num = 0.973373;
    else if (pt <= 4.8) num = 0.985632;
    else if (pt <= 5.5) num = 0.98595;
    else if (pt <= 6.5) num = 0.993531;
    else if (pt <= 9.5) num = 0.985732;
    else if (pt <= 13) num = 0.998986;
    else if (pt <= 25) num = 1.00289;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.97355;
    else if (pt <= 4.3) num = 0.956711;
    else if (pt <= 4.8) num = 0.976561;
    else if (pt <= 5.5) num = 0.989838;
    else if (pt <= 6.5) num = 0.988066;
    else if (pt <= 9.5) num = 0.987354;
    else if (pt <= 13) num = 0.997235;
    else if (pt <= 25) num = 0.990428;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.893973;
    else if (pt <= 2.5) num = 0.937025;
    else if (pt <= 3.3) num = 0.99885;
    else if (pt <= 4.3) num = 0.991538;
    else if (pt <= 5.5) num = 0.994943;
    else if (pt <= 6.5) num = 0.985351;
    else if (pt <= 9.5) num = 0.994899;
    else if (pt <= 13) num = 0.999225;
    else if (pt <= 25) num = 0.987122;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.950781;
    else if (pt <= 1.9) num = 0.831687;
    else if (pt <= 2.5) num = 0.957659;
    else if (pt <= 3.3) num = 0.994745;
    else if (pt <= 4.8) num = 0.994066;
    else if (pt <= 6.5) num = 0.994238;
    else if (pt <= 9.5) num = 1.0027;
    else if (pt <= 25) num = 0.993894;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.972663;
    else if (pt <= 1.9) num = 0.967036;
    else if (pt <= 2.5) num = 1.00893;
    else if (pt <= 3.3) num = 0.991683;
    else if (pt <= 4.8) num = 1.00848;
    else if (pt <= 6.5) num = 1.00626;
    else if (pt <= 9.5) num = 0.994095;
    else if (pt <= 25) num = 1.00426;
    }
  }
  else if (idx == -14) { // TnP fit syst down
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.598981;
    else if (pt <= 4.3) num = 0.852219;
    else if (pt <= 4.8) num = 0.923419;
    else if (pt <= 5.5) num = 0.959368;
    else if (pt <= 6.5) num = 0.979141;
    else if (pt <= 9.5) num = 0.973729;
    else if (pt <= 13) num = 0.989193;
    else if (pt <= 25) num = 0.997112;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.8) num = 0.540178;
    else if (pt <= 4.3) num = 0.925515;
    else if (pt <= 4.8) num = 0.945365;
    else if (pt <= 5.5) num = 0.958632;
    else if (pt <= 6.5) num = 0.956836;
    else if (pt <= 9.5) num = 0.962818;
    else if (pt <= 13) num = 0.986653;
    else if (pt <= 25) num = 0.988195;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 1.2 && pt <= 1.9) num = 0.309444;
    else if (pt <= 2.5) num = 0.583148;
    else if (pt <= 3.3) num = 0.825197;
    else if (pt <= 4.3) num = 0.925221;
    else if (pt <= 5.5) num = 0.962694;
    else if (pt <= 6.5) num = 0.956698;
    else if (pt <= 9.5) num = 0.965869;
    else if (pt <= 13) num = 0.974931;
    else if (pt <= 25) num = 0.974822;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.219077;
    else if (pt <= 1.9) num = 0.759535;
    else if (pt <= 2.5) num = 0.912264;
    else if (pt <= 3.3) num = 0.966811;
    else if (pt <= 4.8) num = 0.975999;
    else if (pt <= 6.5) num = 0.981751;
    else if (pt <= 9.5) num = 0.99317;
    else if (pt <= 25) num = 0.988307;
    }
    else if (fabs(eta) > 2 && fabs(eta) <= 2.4) { 
    if (pt > 0.8 && pt <= 1.3) num = 0.158094;
    else if (pt <= 1.9) num = 0.783207;
    else if (pt <= 2.5) num = 0.904907;
    else if (pt <= 3.3) num = 0.943;
    else if (pt <= 4.8) num = 0.989852;
    else if (pt <= 6.5) num = 0.993498;
    else if (pt <= 9.5) num = 0.975987;
    else if (pt <= 25) num = 0.983864;
    }
  }
  return (num/den);
}


///////////////////////////////////////////////////
//                 T R G    P P b                //
///////////////////////////////////////////////////


double tnp_weight_trg_ppb(double pt, double eta, int idx)
{
  double num=1.0, den=0.0;  //intentionally 0, so if asked for a corrections outside defined range, it returns NaN instead of 1

  // MC
  if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.6) den = 0.498068;
    else if (pt <= 3.9) den = 0.665326;
    else if (pt <= 4.3) den = 0.801422;
    else if (pt <= 4.8) den = 0.882357;
    else if (pt <= 5.5) den = 0.915164;
    else if (pt <= 6.5) den = 0.940823;
    else if (pt <= 9.5) den = 0.957717;
    else if (pt <= 13) den = 0.956779;
    else if (pt <= 18) den = 0.956963;
    else if (pt <= 25) den = 0.955274;
    else if (pt <= 50) den = 0.961237;
  }
  else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.6) den = 0.585367;
    else if (pt <= 3.9) den = 0.843002;
    else if (pt <= 4.3) den = 0.954434;
    else if (pt <= 4.8) den = 0.980751;
    else if (pt <= 5.5) den = 0.9864;
    else if (pt <= 6.5) den = 0.986081;
    else if (pt <= 9.5) den = 0.985115;
    else if (pt <= 13) den = 0.985537;
    else if (pt <= 18) den = 0.9814;
    else if (pt <= 25) den = 0.988194;
    else if (pt <= 50) den = 0.990348;
  }
  else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 2.5 && pt <= 2.7) den = 0.486399;
    else if (pt <= 3) den = 0.647036;
    else if (pt <= 3.3) den = 0.685391;
    else if (pt <= 3.6) den = 0.742304;
    else if (pt <= 4.3) den = 0.895588;
    else if (pt <= 5.5) den = 0.959236;
    else if (pt <= 6.5) den = 0.974368;
    else if (pt <= 9.5) den = 0.977107;
    else if (pt <= 13) den = 0.981514;
    else if (pt <= 25) den = 0.981903;
    else if (pt <= 50) den = 0.970746;
  }
  else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) { 
    if (pt > 1.3 && pt <= 1.9) den = 0.647988;
    else if (pt <= 2.2) den = 0.638017;
    else if (pt <= 2.5) den = 0.691752;
    else if (pt <= 2.9) den = 0.799388;
    else if (pt <= 3.3) den = 0.875286;
    else if (pt <= 4.5) den = 0.910258;
    else if (pt <= 9.5) den = 0.92422;
    else if (pt <= 13) den = 0.912018;
    else if (pt <= 35) den = 0.895858;
  }
  else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
    if (pt > 1.3 && pt <= 1.6) den = 0.456236;
    else if (pt <= 1.9) den = 0.76488;
    else if (pt <= 2.2) den = 0.872688;
    else if (pt <= 2.5) den = 0.912441;
    else if (pt <= 2.9) den = 0.929277;
    else if (pt <= 3.3) den = 0.937497;
    else if (pt <= 5.5) den = 0.942556;
    else if (pt <= 9.5) den = 0.939298;
    else if (pt <= 25) den = 0.916146;
  }

  // data
  if (idx == -10) { // nominal
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.523939;
    else if (pt <= 3.9) num = 0.67532;
    else if (pt <= 4.3) num = 0.806761;
    else if (pt <= 4.8) num = 0.886755;
    else if (pt <= 5.5) num = 0.929742;
    else if (pt <= 6.5) num = 0.941357;
    else if (pt <= 9.5) num = 0.940734;
    else if (pt <= 13) num = 0.933826;
    else if (pt <= 18) num = 0.934464;
    else if (pt <= 25) num = 0.929954;
    else if (pt <= 50) num = 0.953814;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.711238;
    else if (pt <= 3.9) num = 0.922777;
    else if (pt <= 4.3) num = 0.971317;
    else if (pt <= 4.8) num = 0.982646;
    else if (pt <= 5.5) num = 0.983165;
    else if (pt <= 6.5) num = 0.98195;
    else if (pt <= 9.5) num = 0.985107;
    else if (pt <= 13) num = 0.974124;
    else if (pt <= 18) num = 0.976469;
    else if (pt <= 25) num = 0.985798;
    else if (pt <= 50) num = 0.91472;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 2.5 && pt <= 2.7) num = 0.606477;
    else if (pt <= 3) num = 0.761733;
    else if (pt <= 3.3) num = 0.739364;
    else if (pt <= 3.6) num = 0.797563;
    else if (pt <= 4.3) num = 0.907741;
    else if (pt <= 5.5) num = 0.96245;
    else if (pt <= 6.5) num = 0.97815;
    else if (pt <= 9.5) num = 0.982544;
    else if (pt <= 13) num = 0.989167;
    else if (pt <= 25) num = 0.992298;
    else if (pt <= 50) num = 0.99004;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) { 
    if (pt > 1.3 && pt <= 1.9) num = 0.781448;
    else if (pt <= 2.2) num = 0.73067;
    else if (pt <= 2.5) num = 0.751013;
    else if (pt <= 2.9) num = 0.842671;
    else if (pt <= 3.3) num = 0.898161;
    else if (pt <= 4.5) num = 0.924753;
    else if (pt <= 9.5) num = 0.928099;
    else if (pt <= 13) num = 0.909673;
    else if (pt <= 35) num = 0.898301;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
    if (pt > 1.3 && pt <= 1.6) num = 0.617192;
    else if (pt <= 1.9) num = 0.855515;
    else if (pt <= 2.2) num = 0.92013;
    else if (pt <= 2.5) num = 0.928044;
    else if (pt <= 2.9) num = 0.944568;
    else if (pt <= 3.3) num = 0.956424;
    else if (pt <= 5.5) num = 0.961812;
    else if (pt <= 9.5) num = 0.97431;
    else if (pt <= 25) num = 0.942885;
    }
  }
  else if (idx == -11) { // stat up
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.530192;
    else if (pt <= 3.9) num = 0.680789;
    else if (pt <= 4.3) num = 0.811059;
    else if (pt <= 4.8) num = 0.890229;
    else if (pt <= 5.5) num = 0.932531;
    else if (pt <= 6.5) num = 0.943994;
    else if (pt <= 9.5) num = 0.943113;
    else if (pt <= 13) num = 0.938161;
    else if (pt <= 18) num = 0.941124;
    else if (pt <= 25) num = 0.940848;
    else if (pt <= 50) num = 0.968546;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.719247;
    else if (pt <= 3.9) num = 0.927461;
    else if (pt <= 4.3) num = 0.973911;
    else if (pt <= 4.8) num = 0.984725;
    else if (pt <= 5.5) num = 1;
    else if (pt <= 6.5) num = 0.984179;
    else if (pt <= 9.5) num = 0.986879;
    else if (pt <= 13) num = 0.978025;
    else if (pt <= 18) num = 0.982309;
    else if (pt <= 25) num = 0.993256;
    else if (pt <= 50) num = 0.94268;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 2.5 && pt <= 2.7) num = 0.625542;
    else if (pt <= 3) num = 0.769487;
    else if (pt <= 3.3) num = 0.745565;
    else if (pt <= 3.6) num = 0.802812;
    else if (pt <= 4.3) num = 0.910638;
    else if (pt <= 5.5) num = 0.964356;
    else if (pt <= 6.5) num = 0.980247;
    else if (pt <= 9.5) num = 0.984237;
    else if (pt <= 13) num = 0.991725;
    else if (pt <= 25) num = 0.995731;
    else if (pt <= 50) num = 1;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) { 
    if (pt > 1.3 && pt <= 1.9) num = 0.790415;
    else if (pt <= 2.2) num = 0.736167;
    else if (pt <= 2.5) num = 0.755813;
    else if (pt <= 2.9) num = 0.846866;
    else if (pt <= 3.3) num = 0.902072;
    else if (pt <= 4.5) num = 0.927033;
    else if (pt <= 9.5) num = 0.930081;
    else if (pt <= 13) num = 0.916129;
    else if (pt <= 35) num = 0.908293;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
    if (pt > 1.3 && pt <= 1.6) num = 0.624073;
    else if (pt <= 1.9) num = 0.861542;
    else if (pt <= 2.2) num = 0.924871;
    else if (pt <= 2.5) num = 0.932757;
    else if (pt <= 2.9) num = 0.948301;
    else if (pt <= 3.3) num = 0.960283;
    else if (pt <= 5.5) num = 0.964;
    else if (pt <= 9.5) num = 0.977171;
    else if (pt <= 25) num = 0.951336;
    }
  }
  else if (idx == -12) { // stat down
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.517684;
    else if (pt <= 3.9) num = 0.669822;
    else if (pt <= 4.3) num = 0.80242;
    else if (pt <= 4.8) num = 0.883235;
    else if (pt <= 5.5) num = 0.926888;
    else if (pt <= 6.5) num = 0.93865;
    else if (pt <= 9.5) num = 0.938305;
    else if (pt <= 13) num = 0.929328;
    else if (pt <= 18) num = 0.927396;
    else if (pt <= 25) num = 0.917961;
    else if (pt <= 50) num = 0.936118;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.703156;
    else if (pt <= 3.9) num = 0.91794;
    else if (pt <= 4.3) num = 0.968583;
    else if (pt <= 4.8) num = 0.980435;
    else if (pt <= 5.5) num = 0.980952;
    else if (pt <= 6.5) num = 0.979566;
    else if (pt <= 9.5) num = 0.983191;
    else if (pt <= 13) num = 0.969814;
    else if (pt <= 18) num = 0.969587;
    else if (pt <= 25) num = 0.975028;
    else if (pt <= 50) num = 0.879835;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 2.5 && pt <= 2.7) num = 0.587404;
    else if (pt <= 3) num = 0.753943;
    else if (pt <= 3.3) num = 0.733111;
    else if (pt <= 3.6) num = 0.792241;
    else if (pt <= 4.3) num = 0.904801;
    else if (pt <= 5.5) num = 0.960493;
    else if (pt <= 6.5) num = 0.975932;
    else if (pt <= 9.5) num = 0.980749;
    else if (pt <= 13) num = 0.986295;
    else if (pt <= 25) num = 0.988537;
    else if (pt <= 50) num = 0.97044;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) { 
    if (pt > 1.3 && pt <= 1.9) num = 0.772429;
    else if (pt <= 2.2) num = 0.725156;
    else if (pt <= 2.5) num = 0.746199;
    else if (pt <= 2.9) num = 0.838421;
    else if (pt <= 3.3) num = 0.89418;
    else if (pt <= 4.5) num = 0.924753;
    else if (pt <= 9.5) num = 0.926097;
    else if (pt <= 13) num = 0.903;
    else if (pt <= 35) num = 0.887906;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
    if (pt > 1.3 && pt <= 1.6) num = 0.610301;
    else if (pt <= 1.9) num = 0.849087;
    else if (pt <= 2.2) num = 0.915301;
    else if (pt <= 2.5) num = 0.923204;
    else if (pt <= 2.9) num = 0.940748;
    else if (pt <= 3.3) num = 0.952424;
    else if (pt <= 5.5) num = 0.959571;
    else if (pt <= 9.5) num = 0.971302;
    else if (pt <= 25) num = 0.933877;
    }
  }
  if (idx == -13) { // TnP fit syst up
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.553963;
    else if (pt <= 3.9) num = 0.675448;
    else if (pt <= 4.3) num = 0.806888;
    else if (pt <= 4.8) num = 0.886898;
    else if (pt <= 5.5) num = 0.929916;
    else if (pt <= 6.5) num = 0.94155;
    else if (pt <= 9.5) num = 0.940995;
    else if (pt <= 13) num = 0.934225;
    else if (pt <= 18) num = 0.934952;
    else if (pt <= 25) num = 0.930467;
    else if (pt <= 50) num = 0.954328;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.738593;
    else if (pt <= 3.9) num = 0.923218;
    else if (pt <= 4.3) num = 0.971746;
    else if (pt <= 4.8) num = 0.983071;
    else if (pt <= 5.5) num = 0.983528;
    else if (pt <= 6.5) num = 0.982131;
    else if (pt <= 9.5) num = 0.985204;
    else if (pt <= 13) num = 0.974444;
    else if (pt <= 18) num = 0.977164;
    else if (pt <= 25) num = 0.986666;
    else if (pt <= 50) num = 0.915349;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 2.5 && pt <= 2.7) num = 0.624347;
    else if (pt <= 3) num = 0.780535;
    else if (pt <= 3.3) num = 0.750691;
    else if (pt <= 3.6) num = 0.801551;
    else if (pt <= 4.3) num = 0.90835;
    else if (pt <= 5.5) num = 0.962662;
    else if (pt <= 6.5) num = 0.978321;
    else if (pt <= 9.5) num = 0.982912;
    else if (pt <= 13) num = 0.990236;
    else if (pt <= 25) num = 0.994219;
    else if (pt <= 50) num = 0.992301;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) { 
    if (pt > 1.3 && pt <= 1.9) num = 0.794062;
    else if (pt <= 2.2) num = 0.762669;
    else if (pt <= 2.5) num = 0.774073;
    else if (pt <= 2.9) num = 0.852773;
    else if (pt <= 3.3) num = 0.900618;
    else if (pt <= 4.5) num = 0.925938;
    else if (pt <= 9.5) num = 0.929573;
    else if (pt <= 13) num = 0.911703;
    else if (pt <= 35) num = 0.900555;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
    if (pt > 1.3 && pt <= 1.6) num = 0.65096;
    else if (pt <= 1.9) num = 0.859331;
    else if (pt <= 2.2) num = 0.923698;
    else if (pt <= 2.5) num = 0.93098;
    else if (pt <= 2.9) num = 0.94645;
    else if (pt <= 3.3) num = 0.957451;
    else if (pt <= 5.5) num = 0.962386;
    else if (pt <= 9.5) num = 0.974691;
    else if (pt <= 25) num = 0.943125;
    }
  }
  else if (idx == -14) { // TnP fit syst down
    if (fabs(eta) > 0 && fabs(eta) <= 0.8) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.493916;
    else if (pt <= 3.9) num = 0.675193;
    else if (pt <= 4.3) num = 0.806634;
    else if (pt <= 4.8) num = 0.886612;
    else if (pt <= 5.5) num = 0.929568;
    else if (pt <= 6.5) num = 0.941165;
    else if (pt <= 9.5) num = 0.940473;
    else if (pt <= 13) num = 0.933428;
    else if (pt <= 18) num = 0.933977;
    else if (pt <= 25) num = 0.92944;
    else if (pt <= 50) num = 0.953301;
    }
    else if (fabs(eta) > 0.8 && fabs(eta) <= 1.1) { 
    if (pt > 3.3 && pt <= 3.6) num = 0.683884;
    else if (pt <= 3.9) num = 0.922335;
    else if (pt <= 4.3) num = 0.970888;
    else if (pt <= 4.8) num = 0.982222;
    else if (pt <= 5.5) num = 0.982802;
    else if (pt <= 6.5) num = 0.981768;
    else if (pt <= 9.5) num = 0.98501;
    else if (pt <= 13) num = 0.973803;
    else if (pt <= 18) num = 0.975774;
    else if (pt <= 25) num = 0.98493;
    else if (pt <= 50) num = 0.91409;
    }
    else if (fabs(eta) > 1.1 && fabs(eta) <= 1.5) { 
    if (pt > 2.5 && pt <= 2.7) num = 0.588606;
    else if (pt <= 3) num = 0.742931;
    else if (pt <= 3.3) num = 0.728036;
    else if (pt <= 3.6) num = 0.793576;
    else if (pt <= 4.3) num = 0.907132;
    else if (pt <= 5.5) num = 0.962238;
    else if (pt <= 6.5) num = 0.97798;
    else if (pt <= 9.5) num = 0.982175;
    else if (pt <= 13) num = 0.988098;
    else if (pt <= 25) num = 0.990377;
    else if (pt <= 50) num = 0.987779;
    }
    else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) { 
    if (pt > 1.3 && pt <= 1.9) num = 0.768833;
    else if (pt <= 2.2) num = 0.698672;
    else if (pt <= 2.5) num = 0.727953;
    else if (pt <= 2.9) num = 0.832569;
    else if (pt <= 3.3) num = 0.895704;
    else if (pt <= 4.5) num = 0.923568;
    else if (pt <= 9.5) num = 0.926626;
    else if (pt <= 13) num = 0.907642;
    else if (pt <= 35) num = 0.896046;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
    if (pt > 1.3 && pt <= 1.6) num = 0.583423;
    else if (pt <= 1.9) num = 0.8517;
    else if (pt <= 2.2) num = 0.916562;
    else if (pt <= 2.5) num = 0.925108;
    else if (pt <= 2.9) num = 0.942686;
    else if (pt <= 3.3) num = 0.955398;
    else if (pt <= 5.5) num = 0.961238;
    else if (pt <= 9.5) num = 0.97393;
    else if (pt <= 25) num = 0.942645;
    }
  }
  return (num/den);
}

#endif //#ifndef tnp_weight_h
