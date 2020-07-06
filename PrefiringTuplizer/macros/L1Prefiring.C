#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
#include <bits/stdc++.h> 

#include <vector>

#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TProfile2D.h>
#include <TSystem.h>
#include <TLorentzVector.h>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

/*
 Author: Raman Khurana

This macro works in three modes: 
1. when we use full readout data as input
2. when we use time scan data as input 
3. when we use simulation as input
*/



using  namespace std;

// DONT FORGET TO CHANGE THE INPUT FILE NAME
bool is2017    = true;
bool timescan_ = true;
// ---------------- following parameters only for MC -------------------------------------
bool isdata    = false;  // when running on the simulation samples it should be false. 
//TString timeshiftoutput = "_minus12_"; // need to set for mc only 
//TString inputcutval = "m12ns";
// ----------------------------------------------------------------------------------------
TString outputdir = "MC_PhaseShift/"; 


bool debug__ = false; 
TString dataset   = "";
struct TowerVariables{

  int   eta;
  int   phi;
  int   idx;
  int   energy;
  int   tpenergy;
  
};

struct EGVariables{
  bool iso;
  int eta;
  int phi;
  int idx;
  int energy;
  float pt;

};

struct MatchedTowers{
  float de;
  int itower;
  int iegcand;
  int dr;
  float pttower;
  float ptcand;
  int etatower;
  int etacand;
  int towerbx;
  int egbx;
  
};
struct EcalTPGVariables
{
   
  // event variables
  UInt_t runNb ;
  ULong64_t evtNb ;
  UInt_t bxNb ;
  UInt_t lumiBlock ;
  ULong64_t orbitNb ;
  double timeStamp ; 
  
  /*
  UInt_t nbOfActiveTriggers ;
  UInt_t nbOfActiveTriggersBX ;
  

  int activeTriggers[128] ;
  int activeTriggersBX[128] ;
   
  int activeTechTriggers[64] ;
  UInt_t nbOfActiveTechTriggers ;
  */
  // tower variables
  UInt_t nbOfTowers ; //max 4032 EB+EE
  int ieta[4032] ;
  int iphi[4032] ;
  int nbOfXtals[4032] ;
  int rawTPData[4032] ;
  int rawTPEmul1[4032] ;
  int rawTPEmul2[4032] ;
  int rawTPEmul3[4032] ;
  int rawTPEmul4[4032] ;
  int rawTPEmul5[4032] ;
  int rawTPEmulttFlag1[4032] ;
  int rawTPEmulttFlag2[4032] ;
  int rawTPEmulttFlag3[4032] ;
  int rawTPEmulttFlag4[4032] ;
  int rawTPEmulttFlag5[4032] ;
  int rawTPEmulsFGVB1[4032] ;
  int rawTPEmulsFGVB2[4032] ;
  int rawTPEmulsFGVB3[4032] ;
  int rawTPEmulsFGVB4[4032] ;
  int rawTPEmulsFGVB5[4032] ;
  
  float eRec[4032] ;
  int crystNb[4032] ;
  int spike[4032] ;
  int sevlv[4032];
  int ttFlag[4032];
  int trig_tower_adc[4032], trig_tower_sFGVB[4032]; 

   
  /*
  UInt_t nMaskedRCT ;
  int iMaskedRCTeta[100] ;
  int iMaskedRCTphi[100] ;
  int iMaskedRCTcrate[100] ;
  */
  

  // new branches isolated and non isolated candidates, older ones are removed. 
  
  UInt_t          nbOfL1preNonisoCandsm2;
  Int_t           L1preNonisoIetam2[9]; 
  Int_t           L1preNonisoIphim2[9]; 
  Int_t           L1preNonisoEnergym2[9]; 
  Int_t           L1preNonisoPtm2[9]; 
  UInt_t          nbOfL1preIsoCandsm2;
  Int_t           L1preIsoIetam2[12];   
  Int_t           L1preIsoIphim2[12];   
  Int_t           L1preIsoEnergym2[12];   
  Int_t           L1preIsoPtm2[12];   
  UInt_t          nbOfL1preNonisoCandsm1;
  Int_t           L1preNonisoIetam1[10];
  Int_t           L1preNonisoIphim1[10];
  Int_t           L1preNonisoEnergym1[10];
  Int_t           L1preNonisoPtm1[10];
  UInt_t          nbOfL1preIsoCandsm1;
  Int_t           L1preIsoIetam1[12];   
  Int_t           L1preIsoIphim1[12];   
  Int_t           L1preIsoEnergym1[12];   
  Int_t           L1preIsoPtm1[12];   
  UInt_t          nbOfL1preNonisoCandszero;
  Int_t           L1preNonisoIetazero[10];
  Int_t           L1preNonisoIphizero[10];
  Int_t           L1preNonisoEnergyzero[10];
  Int_t           L1preNonisoPtzero[10];
  UInt_t          nbOfL1preIsoCandszero;
  Int_t           L1preIsoIetazero[12];   
  Int_t           L1preIsoIphizero[12];   
  Int_t           L1preIsoEnergyzero[12];   
  Int_t           L1preIsoPtzero[12];   
  UInt_t          nbOfL1preNonisoCandsp1;
  Int_t           L1preNonisoIetap1[9];   
  Int_t           L1preNonisoIphip1[9];   
  Int_t           L1preNonisoEnergyp1[9];   
  Int_t           L1preNonisoPtp1[9];   
  UInt_t          nbOfL1preIsoCandsp1;
  Int_t           L1preIsoIetap1[12];   
  Int_t           L1preIsoIphip1[12];   
  Int_t           L1preIsoEnergyp1[12];   
  Int_t           L1preIsoPtp1[12];   
  UInt_t          nbOfL1preNonisoCandsp2;
  Int_t           L1preNonisoIetap2[9]; 
  Int_t           L1preNonisoIphip2[9]; 
  Int_t           L1preNonisoEnergyp2[9]; 
  Int_t           L1preNonisoPtp2[9]; 
  UInt_t          nbOfL1preIsoCandsp2;
  Int_t           L1preIsoIetap2[12];   
  Int_t           L1preIsoIphip2[12];   
  Int_t           L1preIsoEnergyp2[12];   
  Int_t           L1preIsoPtp2[12];   

  // Gen Level information for MC samples 
  int                  nGenPar;
  Float_t   genParPx[2];
  Float_t   genParPy[2];
  Float_t   genParPz[2];
  Float_t   genParE[2];
  int     genParId[2];
  int     genParSt[2];
  int     genMomParId[2];
  
  
  
};

int etaToiEta(float eta){
  int sign =0;
  if (eta < 0) sign = -1;
  if (eta > 0) sign = +1;
  
  int ieta=0;
  if (fabs(eta) <1.566) ieta = 0; /// zero means barrel, i am not considering it yet so set it to zero 
  if (fabs(eta)>=1.566  && fabs(eta) <1.653) ieta = 19;
  if (fabs(eta)>=1.653  && fabs(eta) <1.740) ieta = 20;
  if (fabs(eta)>=1.74   && fabs(eta) <1.830) ieta = 21;
  if (fabs(eta)>=1.830  && fabs(eta) <1.930) ieta = 22;
  if (fabs(eta)>=1.930  && fabs(eta) <2.043) ieta = 23;
  if (fabs(eta)>=2.043  && fabs(eta) <2.172) ieta = 24;
  if (fabs(eta)>=2.172  && fabs(eta) <2.322) ieta = 25;
  if (fabs(eta)>=2.322  && fabs(eta) <2.500) ieta = 26;
  if (fabs(eta)>=2.500  && fabs(eta) <2.650) ieta = 27;
  if (fabs(eta)>=2.650  && fabs(eta) <3.000) ieta = 28;
  
  int signed_ieta = ieta * sign;
  return signed_ieta;
}


int phiToiPhi(float phi){

  float kPI = 3.14159265358979323846;
  if (phi>0) phi = phi;
  if (phi<0) phi = phi + 2*kPI;
  
  /*

  float kPI = 3.14159265358979323846;
  float kTWOPI = 2 * kPI;
  
  while (phi >= kPI) phi = phi - kTWOPI;
  while (phi < -kPI) phi = phi + kTWOPI;
  */
  int iphi = int(360*phi / (5.0*2*kPI) ) ;
  return iphi;
  
}



bool isMasked(std::vector<float> etaV, std::vector<float> phiV, float ieta, float iphi){
  bool maskedstatus = false; 
  for (int i = 0 ; i < int( phiV.size()); i++) {
    
    int a = (int) etaV[i];
    int b = (int) phiV[i];
 
      if ((ieta==a) && (iphi==b) ) {
	maskedstatus = true;
	break;
      }
    
    
  }
  return maskedstatus; 
}


void TowerVariablesShow(std::vector<TowerVariables> maxtowervec){
  for (auto i=0; i<maxtowervec.size(); i++) {
    std::cout<<" tower number "<<i
	     <<" ieta "<<maxtowervec[i].eta
	     <<" iphi "<<maxtowervec[i].phi
	     <<" energy "<<maxtowervec[i].energy
	     <<" index "<<maxtowervec[i].idx
	     <<" real energy "<<maxtowervec[i].tpenergy
	     <<std::endl;
    
  }
  
}




void EGVariablesShow(std::vector<EGVariables> candvec){
  for (auto i=0; i<candvec.size(); i++){
    std::cout<<" iso "<<candvec[i].iso
	     <<"           ieta "<<candvec[i].eta
	     <<" iphi "<<candvec[i].phi
	     <<" energy "<<candvec[i].energy
	     <<" index "<<candvec[i].idx
	     <<" ecal eta "<<int(  (28./63.)*candvec[i].eta) 
	     <<" ecal phi "<<(int(candvec[i].phi/2.)) + 1 
	     <<std::endl;
      
  }
  
}


int CalculateDeltaIEta(std::vector<EGVariables> candvec, std::vector<TowerVariables> maxtowervec){
  //std::cout<<" inside CalculateDeltaIEta"<<std::endl;
  std::vector<int> dietaVec;
  dietaVec.clear();
  //std::cout<<" size = "<<candvec.size()<<"  "<<maxtowervec.size()<<std::endl;
  
  for (int i =0; i<(int)candvec.size(); i++){
    for (int j = 0; j<(int)maxtowervec.size(); j++){
      
      // converted the candidate ieta to tower ieta, works, approximately. 
      int dieta = abs (int(  (28./63.)*candvec[i].eta) - maxtowervec[j].eta) ; 
      
      dietaVec.push_back(dieta);
  
      //std::cout<<" dieta = "<<dieta<<std::endl;
      
    }
  }
  
  // sorting after complete filling 
  //std::cout<<" now sorting a vector of size "<<dietaVec.size()<<std::endl;
  std::sort(dietaVec.begin(), dietaVec.end());
  int mindieta = dietaVec[0];
  //std::cout<<" returning mindieta = "<<mindieta<<std::endl;
  return mindieta;
}


int CalculateDeltaIPhi(std::vector<EGVariables> candvec, std::vector<TowerVariables> maxtowervec){
  //std::cout<<" inside CalculateDeltaIPhi"<<std::endl;
  
  std::vector<int> diphiVec;
  diphiVec.clear();
  
  for (auto i =0; i<candvec.size(); i++){
    for (auto j = 0; j<maxtowervec.size(); j++){
      
      // converted the candidate iphi to tower iphi, works, approximately. 
      int diphi = abs(  (int(candvec[i].phi/2.)+1) - maxtowervec[j].phi) ; 
      
      diphiVec.push_back(diphi);
      
    }
  }
  
  // sorting after complete filling 
  std::sort(diphiVec.begin(), diphiVec.end());
  int mindiphi = diphiVec[0];
  return mindiphi;
}



// it returns i index, j index and drmin value, eg bx index, tower bx index. One can cut on this and see the respective values of index
std::vector<int> CalculateDeltaIR(std::vector<EGVariables> candvec, std::vector<TowerVariables> maxtowervec){
  
  std::vector<int> dIR;
  dIR.clear();
  //std::cout<<" size = "<<candvec.size()<<"  "<<maxtowervec.size()<<std::endl;
  
  float drMin = 999.;
  int imin=-1;
  int jmin=-1;
  
  for (int i =0; i<(int)candvec.size(); i++){
    if (debug__) std::cout<<" inside the candidate loop "<<candvec[i].energy<<"  "<<candvec[i].eta<<"  "<<candvec[i].phi<<std::endl;
    for (int j = 0; j<(int)maxtowervec.size(); j++){
      if (debug__) std::cout<<" inside the max tower loop "<<maxtowervec[j].energy<<"  "<<maxtowervec[j].eta<<"  "<<maxtowervec[j].phi<<std::endl;
      // converted the candidate ieta to tower ieta, works, approximately. 
      int dieta = abs (int(  (28./63.)*candvec[i].eta) - maxtowervec[j].eta) ; 
      int diphi = abs(  (int(candvec[i].phi/2.)+1) - maxtowervec[j].phi) ;
      
      int dr = (dieta*dieta)  +   (diphi*diphi) ; 
      if (dr<drMin){
	drMin = (dr);
	imin = i;
	jmin = j;
      }
      
    }
  }
  
  dIR.push_back(imin);
  dIR.push_back(jmin);
  dIR.push_back(int(drMin));
  dIR.push_back(candvec[imin].idx);
  dIR.push_back(maxtowervec[jmin].idx);
  
  return dIR;
}





// it returns i index, j index and drmin value, eg bx index, tower bx index. One can cut on this and see the respective values of index
std::vector<int> PseudoCalculateDeltaIR(std::vector<EGVariables> candvec, std::vector<TowerVariables> maxtowervec){
  
  std::vector<int> dIR;
  dIR.clear();
  //std::cout<<" size = "<<candvec.size()<<"  "<<maxtowervec.size()<<std::endl;
  
  float drMin = 999.;
  int imin=-1;
  int jmin=-1;
  
  for (int i =0; i<(int)candvec.size(); i++){
    if (debug__) std::cout<<" inside the candidate loop "<<candvec[i].energy<<"  "<<candvec[i].eta<<"  "<<candvec[i].phi<<std::endl;
    for (int j = 0; j<(int)maxtowervec.size(); j++){
      if (debug__) std::cout<<" inside the max tower loop "<<maxtowervec[j].energy<<"  "<<maxtowervec[j].eta<<"  "<<maxtowervec[j].phi<<std::endl;
      // converted the candidate ieta to tower ieta, works, approximately. 
      int dieta = abs (int(candvec[i].eta) -   maxtowervec[j].eta) ; 
      int diphi = abs(  (int(candvec[i].phi)+1) - maxtowervec[j].phi) ;
      
      int dr = (dieta*dieta)  +   (diphi*diphi) ; 
      if (dr<drMin){
	drMin = (dr);
	imin = i;
	jmin = j;
      }
      
    }
  }
  
  dIR.push_back(imin);
  dIR.push_back(jmin);
  dIR.push_back(int(drMin));
  dIR.push_back(candvec[imin].idx);
  dIR.push_back(maxtowervec[jmin].idx);
  
  return dIR;
}



class mysort{
public:
  bool operator() (MatchedTowers m1, MatchedTowers m2){
    double Pt1 = m1.de;
    double Pt2 = m2.de;
    return Pt2 >= Pt1;
  }
};



std::vector<MatchedTowers> CalculateDE(EGVariables egcand, std::vector<TowerVariables> maxtowervec, int i){
  
  std::vector<MatchedTowers> dE;
  dE.clear();
  MatchedTowers mtowers;
  
  dE.clear();
  
  float drMin = 999.;
  int imin=-1;
  int jmin=-1;
  
  for (int j = 0; j<(int)maxtowervec.size(); j++){
    // converted the candidate ieta to tower ieta, works, approximately. 
    int dieta = abs (int(  (28./63.)*egcand.eta) - maxtowervec[j].eta) ; 
    int diphi = abs(  (int(egcand.phi/2.)+1) - maxtowervec[j].phi) ;
    int dr = int(sqrt(dieta*dieta)  +   (diphi*diphi)) ; 
    
    if (dr < 5 && egcand.pt >=0 ) {
      mtowers.de = egcand.pt/2.0 - maxtowervec[j].energy ; 
      mtowers.itower = j ;
      mtowers.iegcand = i ;
      mtowers.dr = dr;
      mtowers.pttower = maxtowervec[j].energy/2.0;
      mtowers.ptcand = egcand.pt ;
      mtowers.etatower = maxtowervec[j].eta ;
      mtowers.etacand = egcand.eta ;
      mtowers.towerbx=maxtowervec[j].idx;
      mtowers.egbx=egcand.idx;

      // this vector now has all the information about the tower which are within DR < 5 from the candidate 
      dE.push_back(mtowers);
    }
    
  }// for (int j = 0; j<(int)maxtowervec.size(); j++)

  
  return dE;
}

std::vector<float> MaskedCoordinate(int icol=1){
  std::vector<float> ietaV;
  ietaV.clear();
  string line;
  TString maskedfile;
  if (is2017 && isdata)  maskedfile = "masked_TT_all_2017.txt";
  if (!is2017 && isdata) maskedfile = "masked_TT_all_2018.txt";
  
  ifstream maskedTT (maskedfile);
  if (maskedTT.is_open()){
    while ( getline (maskedTT,line) ){
      
      std::stringstream ss(line);
      float a, b;
      ss >> a >> b;
      
      if (icol==1) ietaV.push_back(a);
      if (icol==2) ietaV.push_back(b);
      
    }
    
  }
  maskedTT.close();
  return ietaV;
}



TString getDataSetTiming(int lumi1, int lumi2){
  
  TString timeb_ = "_FullReadOut" ;
  // convert this into a function 
  if (  (lumi1 == 0  ) && (lumi2 ==  46)  )    timeb_ = "minus6";
  if (  (lumi1 == 49 ) && (lumi2 ==  87)  )    timeb_ = "minus5";
  if (  (lumi1 == 90 ) && (lumi2 == 111)  )    timeb_ = "minus4";
  if (  (lumi1 == 113) && (lumi2 == 131)  )    timeb_ = "minus3";
  if (  (lumi1 == 133) && (lumi2 == 158)  )    timeb_ = "minus2";
  if (  (lumi1 == 160) && (lumi2 == 186)  )    timeb_ = "minus1";
  if (  (lumi1 == 188) && (lumi2 == 219)  )    timeb_ = "nosign0";
  if (  (lumi1 == 221) && (lumi2 == 247)  )    timeb_ = "plus1";
  if (  (lumi1 == 250) && (lumi2 == 267)  )    timeb_ = "plus2";
  if (  (lumi1 == 269) && (lumi2 == 291)  )    timeb_ = "plus3";
  if (  (lumi1 == 293) && (lumi2 == 314)  )    timeb_ = "plus4";
  if (  (lumi1 == 316) && (lumi2 == 336)  )    timeb_ = "plus5";
  if (  (lumi1 == 338) && (lumi2 == 362)  )    timeb_ = "plus6";
  return timeb_;
  
}  
	



// This function is only for MC, it need the gen level information 
// it matches the gen level particle with closest TP and return the matched TP information
// index of TP is returned 
void GetGenMatchedTP(EcalTPGVariables & treeVars){
  

}

// similar to previous one, instead of just one TP you get a list of TPs which are around matched TP, 
// maximum of 9 TPs, one matched and 8 neighbouring to make (almost) a 3x3 matrix, 
// a vector of indices is returned 
void GetGenMatchedTPs(){

}

// DRTowerElectron checks that eta and phi are within +- 1 towers, so we will collect maximum of 9 towers to make the L1T candidate 
//   - in addition dphi can be +-2 
//   - if dphi is 72 it is set to 0 [think a bit this is correct, i couldn't find  a better way to do this]
bool DRTowerElectron(int eta1, int phi1, int eta2, int phi2){

  bool matched = false ;
  
  int deta = abs(eta1 - eta2) ;
  int dphi = abs(phi1 - phi2);
  if (dphi == 72) dphi = 0;
  if (  (deta<=1) && (dphi <=2) ) matched = true;
  return matched ;
}


void setBranchAddresses (TChain * chain, EcalTPGVariables & treeVars)
{
  chain->SetBranchAddress ("b_runNb",&treeVars.runNb) ; 
  chain->SetBranchAddress ("b_evtNb",&treeVars.evtNb) ; 
  chain->SetBranchAddress ("b_bxNb",&treeVars.bxNb) ; 
  chain->SetBranchAddress ("b_lumiBlock",&treeVars.lumiBlock) ;
  chain->SetBranchAddress ("b_orbitNb",&treeVars.orbitNb) ; 
  chain->SetBranchAddress ("b_timeStamp",&treeVars.timeStamp) ; 
  /*
  chain->SetBranchAddress ("nbOfActiveTriggers",&treeVars.nbOfActiveTriggers) ; 
  chain->SetBranchAddress ("activeTriggers",treeVars.activeTriggers) ; 
  chain->SetBranchAddress ("activeTriggersBX",treeVars.activeTriggersBX) ;
   
  chain->SetBranchAddress ("nbOfActiveTechTriggers",&treeVars.nbOfActiveTechTriggers) ; 
  chain->SetBranchAddress ("activeTechTriggers",treeVars.activeTechTriggers) ; 
  */
  chain->SetBranchAddress ("b_nbOfTowers",&treeVars.nbOfTowers) ; 
  chain->SetBranchAddress ("b_ieta",treeVars.ieta) ; 
  chain->SetBranchAddress ("b_iphi",treeVars.iphi) ; 
  chain->SetBranchAddress ("b_nbOfXtals",treeVars.nbOfXtals) ; 
  chain->SetBranchAddress ("b_rawTPData",treeVars.rawTPData) ; 
  chain->SetBranchAddress ("b_rawTPEmul1",treeVars.rawTPEmul1) ; 
  chain->SetBranchAddress ("b_rawTPEmul2",treeVars.rawTPEmul2) ; 
  chain->SetBranchAddress ("b_rawTPEmul3",treeVars.rawTPEmul3) ; 
  chain->SetBranchAddress ("b_rawTPEmul4",treeVars.rawTPEmul4) ; 
  chain->SetBranchAddress ("b_rawTPEmul5",treeVars.rawTPEmul5) ; 
  chain->SetBranchAddress ("b_eRec",treeVars.eRec) ; 
  chain->SetBranchAddress ("b_crystNb",treeVars.crystNb) ;
  chain->SetBranchAddress ("b_spike",treeVars.spike) ;
  chain->SetBranchAddress ("b_sevlv", treeVars.sevlv);
  chain->SetBranchAddress ("b_ttFlag", treeVars.ttFlag);
  chain->SetBranchAddress ("b_trig_tower_adc",treeVars.trig_tower_adc) ; 
  chain->SetBranchAddress ("b_trig_tower_sFGVB",treeVars.trig_tower_sFGVB) ; 
  chain->SetBranchAddress ("b_rawTPEmulsFGVB1",treeVars.rawTPEmulsFGVB1) ; 
  chain->SetBranchAddress ("b_rawTPEmulsFGVB2",treeVars.rawTPEmulsFGVB2) ; 
  chain->SetBranchAddress ("b_rawTPEmulsFGVB3",treeVars.rawTPEmulsFGVB3) ; 
  chain->SetBranchAddress ("b_rawTPEmulsFGVB4",treeVars.rawTPEmulsFGVB4) ; 
  chain->SetBranchAddress ("b_rawTPEmulsFGVB5",treeVars.rawTPEmulsFGVB5) ; 
  chain->SetBranchAddress ("b_rawTPEmulttFlag1",treeVars.rawTPEmulttFlag1) ; 
  chain->SetBranchAddress ("b_rawTPEmulttFlag2",treeVars.rawTPEmulttFlag2) ; 
  chain->SetBranchAddress ("b_rawTPEmulttFlag3",treeVars.rawTPEmulttFlag3) ; 
  chain->SetBranchAddress ("b_rawTPEmulttFlag4",treeVars.rawTPEmulttFlag4) ; 
  chain->SetBranchAddress ("b_rawTPEmulttFlag5",treeVars.rawTPEmulttFlag5) ; 


   
  /*
  chain->SetBranchAddress ("nMaskedRCT",&treeVars.nMaskedRCT); //
  chain->SetBranchAddress ("iMaskedRCTeta", treeVars.iMaskedRCTeta);//
  chain->SetBranchAddress ("iMaskedRCTcrate", treeVars.iMaskedRCTcrate);//
  chain->SetBranchAddress ("iMaskedRCTphi", treeVars.iMaskedRCTphi);//
  */
  
  // new variables 
  
  chain->SetBranchAddress("b_nonisocounterm2", &treeVars.nbOfL1preNonisoCandsm2);
  chain->SetBranchAddress("b_L1preNonisoIetam2", treeVars.L1preNonisoIetam2);
  chain->SetBranchAddress("b_L1preNonisoIphim2", treeVars.L1preNonisoIphim2);
  chain->SetBranchAddress("b_L1preNonisoPtm2", treeVars.L1preNonisoPtm2);
  chain->SetBranchAddress("b_L1preNonisoEnergym2", treeVars.L1preNonisoEnergym2);
  chain->SetBranchAddress("b_isocounterm2", &treeVars.nbOfL1preIsoCandsm2);
  chain->SetBranchAddress("b_L1preIsoIetam2", treeVars.L1preIsoIetam2);
  chain->SetBranchAddress("b_L1preIsoIphim2", treeVars.L1preIsoIphim2);
  chain->SetBranchAddress("b_L1preIsoEnergym2", treeVars.L1preIsoEnergym2);
  chain->SetBranchAddress("b_L1preIsoPtm2", treeVars.L1preIsoPtm2);
  
  chain->SetBranchAddress("b_nonisocounterm1", &treeVars.nbOfL1preNonisoCandsm1);
  chain->SetBranchAddress("b_L1preNonisoIetam1", treeVars.L1preNonisoIetam1);
  chain->SetBranchAddress("b_L1preNonisoIphim1", treeVars.L1preNonisoIphim1);
  chain->SetBranchAddress("b_L1preNonisoEnergym1", treeVars.L1preNonisoEnergym1);
  chain->SetBranchAddress("b_L1preNonisoPtm1", treeVars.L1preNonisoPtm1);
  chain->SetBranchAddress("b_isocounterm1", &treeVars.nbOfL1preIsoCandsm1);
  chain->SetBranchAddress("b_L1preIsoIetam1", treeVars.L1preIsoIetam1);
  chain->SetBranchAddress("b_L1preIsoIphim1", treeVars.L1preIsoIphim1);
  chain->SetBranchAddress("b_L1preIsoEnergym1", treeVars.L1preIsoEnergym1);
  chain->SetBranchAddress("b_L1preIsoPtm1", treeVars.L1preIsoPtm1);
  
  chain->SetBranchAddress("b_nonisocounterzero", &treeVars.nbOfL1preNonisoCandszero);
  chain->SetBranchAddress("b_L1preNonisoIetazero", treeVars.L1preNonisoIetazero);
  chain->SetBranchAddress("b_L1preNonisoIphizero", treeVars.L1preNonisoIphizero);
  chain->SetBranchAddress("b_L1preNonisoEnergyzero", treeVars.L1preNonisoEnergyzero);
  chain->SetBranchAddress("b_L1preNonisoPtzero", treeVars.L1preNonisoPtzero);
  chain->SetBranchAddress("b_isocounterzero", &treeVars.nbOfL1preIsoCandszero);
  chain->SetBranchAddress("b_L1preIsoIetazero", treeVars.L1preIsoIetazero);
  chain->SetBranchAddress("b_L1preIsoIphizero", treeVars.L1preIsoIphizero);
  chain->SetBranchAddress("b_L1preIsoEnergyzero", treeVars.L1preIsoEnergyzero);
  chain->SetBranchAddress("b_L1preIsoPtzero", treeVars.L1preIsoPtzero);
  
  chain->SetBranchAddress("b_nonisocounterp1", &treeVars.nbOfL1preNonisoCandsp1);
  chain->SetBranchAddress("b_L1preNonisoIetap1", treeVars.L1preNonisoIetap1);
  chain->SetBranchAddress("b_L1preNonisoIphip1", treeVars.L1preNonisoIphip1);
  chain->SetBranchAddress("b_L1preNonisoEnergyp1", treeVars.L1preNonisoEnergyp1);
  chain->SetBranchAddress("b_L1preNonisoPtp1", treeVars.L1preNonisoPtp1);
  chain->SetBranchAddress("b_isocounterp1", &treeVars.nbOfL1preIsoCandsp1);
  chain->SetBranchAddress("b_L1preIsoIetap1", treeVars.L1preIsoIetap1);
  chain->SetBranchAddress("b_L1preIsoIphip1", treeVars.L1preIsoIphip1);
  chain->SetBranchAddress("b_L1preIsoEnergyp1", treeVars.L1preIsoEnergyp1);
  chain->SetBranchAddress("b_L1preIsoPtp1", treeVars.L1preIsoPtp1);
  
  chain->SetBranchAddress("b_nonisocounterp2", &treeVars.nbOfL1preNonisoCandsp2);
  chain->SetBranchAddress("b_L1preNonisoIetap2", treeVars.L1preNonisoIetap2);
  chain->SetBranchAddress("b_L1preNonisoIphip2", treeVars.L1preNonisoIphip2);
  chain->SetBranchAddress("b_L1preNonisoEnergyp2", treeVars.L1preNonisoEnergyp2);
  chain->SetBranchAddress("b_L1preNonisoPtp2", treeVars.L1preNonisoPtp2);
  chain->SetBranchAddress("b_isocounterp2", &treeVars.nbOfL1preIsoCandsp2);
  chain->SetBranchAddress("b_L1preIsoIetap2", treeVars.L1preIsoIetap2);
  chain->SetBranchAddress("b_L1preIsoIphip2", treeVars.L1preIsoIphip2);
  chain->SetBranchAddress("b_L1preIsoEnergyp2", treeVars.L1preIsoEnergyp2);
  chain->SetBranchAddress("b_L1preIsoPtp2", treeVars.L1preIsoPtp2);

  // Read the gen level info branches 
  chain->SetBranchAddress("nGenPar_",&treeVars.nGenPar);
  chain->SetBranchAddress("genParPx_", treeVars.genParPx) ;
  chain->SetBranchAddress("genParPy_", treeVars.genParPy) ;
  chain->SetBranchAddress("genParPz_", treeVars.genParPz) ;
  chain->SetBranchAddress("genParE_", treeVars.genParE) ;
  chain->SetBranchAddress("genParId_", treeVars.genParId) ;
  chain->SetBranchAddress("genParSt_", treeVars.genParSt) ;
  chain->SetBranchAddress("genMomParId_", treeVars.genMomParId) ;
  
  /*
  chain->SetBranchAddress("", & , ) ; 
  chain->SetBranchAddress("", , ) ;
  
  */
  
}





int getEt(UInt_t val) {return (val&0xff) ;}

UInt_t getFg(UInt_t val) {return ((val&0x100)!=0) ;}

UInt_t getTtf(UInt_t val) {return ((val>>9)&0x7) ;}


///////  Main program /////////

//void tpgreader()
void L1Prefiring(int threshold=2,TString timeshiftoutput="_plus8_", TString inputcutval="p8ns", int lumi1=0, int lumi2=999999)
{  




  
  //std::cout<<" threshold = "<<threshold << std::endl;
  //std::cout<<" lumi1 = "<<lumi1<< "  lumi2 = "<<lumi2<<std::endl;
  
  TString datasettiming = getDataSetTiming(lumi1, lumi2);
  dataset = datasettiming;
  
  //std::cout<<" datasettiming = "<<datasettiming<<std::endl;
  time_t timer;
  double initial_t = time(&timer);
  

  TChain * chain ;
  
  if (is2017) chain =  new TChain ("tuplizer/prefiringTree") ;
  if (!is2017) chain =  new TChain ("tuplizer/prefiringTree") ;

  // input TPGTree file
  
  TString inputrootfile;
  //if (is2017)  inputrootfile = "/eos/cms/store/user/khurana//ZeroBias2/crab_prefiringanalysis2017_V1/190510_225110/0000/Merged_2017.root"; //2017 with prefiring
  
  if (is2017 && !timescan_ && isdata)  inputrootfile = "/eos/cms/store/user/khurana//ZeroBias2/crab_prefiringanalysis2017_V4/191104_114219/0000/Merged_ZeroBias2017.root";  // 2017 with prefiring after replacing the RANK var with Energy
  
  if (is2017 && timescan_ && isdata)  inputrootfile = "/eos/cms/store/group/phys_exotica/monoHiggs/ecal/Merged_FilesTimeScan/Merged_files/Merged_HLTPhysics_1_2_3_4.root"; // June 2018 Scan data 
  
  if (!is2017 && isdata) inputrootfile = "/eos/cms/store/user/khurana/ZeroBias1/crab_prefiringanalysis2018_V1/190509_091144/0000/Merged_2018.root";

  // for mc scan 
  if (!isdata) inputrootfile = "../simulation_tuples_Eta_2p0_to_2p5/Histo_L1Prefiring_"+inputcutval+".root";
  // for one mc sample
  //if (!isdata) inputrootfile = "../Histo_L1Prefiring_0ns.root";
  
  
  
  //std::cout<<" inputrootfile = "<<inputrootfile<<std::endl;
  chain->Add(inputrootfile);
  

  // if set to true: print debug info on matched and unmatched towers
  
  bool debug=false;

  // -- Gen Level Histogram and Pseudo L1T candidates information 
  TH1F* h_PL1T_nTowers_             = new TH1F("h_PL1T_nTowers_","h_PL1T_nTowers_;# of Towers; # of Events",11,-0.5,10.5);
  TH1F* h_PL1T_Energy0_             = new TH1F("h_PL1T_Energy0_", "h_PL1T_Energy0_;Pseudo L1T candidate Energy in emulator BX=1;  # of Events", 50,0,200);
  TH1F* h_PL1T_Energy1_             = new TH1F("h_PL1T_Energy1_", "h_PL1T_Energy1_;Pseudo L1T candidate Energy in emulator BX=2;  # of Events", 50,0,200);
  TH1F* h_PL1T_Energy2_             = new TH1F("h_PL1T_Energy2_", "h_PL1T_Energy2_;Pseudo L1T candidate Energy in emulator BX=3;  # of Events", 50,0,200);
  TH1F* h_PL1T_Energy3_             = new TH1F("h_PL1T_Energy3_", "h_PL1T_Energy3_;Pseudo L1T candidate Energy in emulator BX=4;  # of Events", 50,0,200);
  TH1F* h_PL1T_Energy4_             = new TH1F("h_PL1T_Energy4_", "h_PL1T_Energy4_;Pseudo L1T candidate Energy in emulator BX=5;  # of Events", 50,0,200);
  TH1F* h_PL1T_maxIndex_            = new TH1F("h_PL1T_maxIndex_","h_PL1T_maxIndex_;Index of max Emul energy; # of Events",5,0.5,5.5);

  
  // define output histograms
  
  TH2F* ieta_vs_iphi_TP             = new TH2F("ieta_vs_iphi_TP","ieta_vs_iphi_TP", 57,-28.5,28.5,72,0.5,72.5);
  TH2F* ieta_vs_iphi_ETP            = new TH2F("ieta_vs_iphi_ETP","ieta_vs_iphi_ETP", 57,-28.5,28.5,72,0.5,72.5);
  
  //57,-28.5,28.5
  TH2F* ieta_vs_iphi_TP_ETP         = new TH2F("ieta_vs_iphi_TP_ETP","ieta_vs_iphi_TP_ETP",57,-28.5,28.5,72,0.5,72.5);
  TH2F* ieta_vs_iphi_TP_ETP_INTIME  =  new TH2F("ieta_vs_iphi_TP_ETP_INTIME","ieta_vs_iphi_TP_ETP_INTIME",57,-28.5,28.5,72,0.5,72.5);
  TH2F* ieta_vs_iphi_TP_ETP_OUTTIME = new TH2F("ieta_vs_iphi_TP_ETP_OUTTIME","ieta_vs_iphi_TP_ETP_OUTTIME",57,-28.5,28.5,72,0.5,72.5);

  
  TH2F* ieta_vs_iphi_TP0            = new TH2F("ieta_vs_iphi_TP0","ieta_vs_iphi_TP0",57,-28.5,28.5,72,0.5,72.5);
  TH2F* ieta_vs_iphi_TP0_ETP        = new TH2F("ieta_vs_iphi_TP0_ETP","ieta_vs_iphi_TP0_ETP",57,-28.5,28.5,72,0.5,72.5);


  TH2F* ieta_vs_idx_TP_ETP          = new TH2F("ieta_vs_idx_TP_ETP","ieta_vs_idx_TP_ETP",11,17.5,28.5, 5, -0.5, 4.5); 
  TH2F* ieta_vs_idx_TP0             = new TH2F("ieta_vs_idx_TP0","ieta_vs_idx_TP0", 11,17.5,28.5 , 5, -0.5, 4.5);
  TH2F* ieta_vs_idx_TP0_ETP         = new TH2F("ieta_vs_idx_TP0_ETP","ieta_vs_idx_TP0_ETP", 11,17.5,28.5 , 5, -0.5, 4.5);
  
  
  TH2F* ieta_vs_iphi_TP16           = new TH2F("ieta_vs_iphi_TP16","ieta_vs_iphi_TP16", 57,-28.5,28.5,72,0.5,72.5);
  TH2F* ieta_vs_iphi_ETP16_IDX2     = new TH2F("ieta_vs_iphi_ETP16_IDX2","ieta_vs_iphi_ETP16_IDX2",57,-28.5,28.5,72,0.5,72.5);
  TH2F* ieta_vs_iphi_ETP16_IDXAny   = new TH2F("ieta_vs_iphi_ETP16_IDXAny","ieta_vs_iphi_ETP16_IDXAny",57,-28.5,28.5,72,0.5,72.5);
  
  TH1F* maxOfTPEmul_                = new TH1F("maxOfTPEmul_", "maxOfTPEmul_", 100, 0,200);
  
  TH2F* idx_vs_ieta_TP16           = new TH2F("idx_vs_ieta_TP16","idx_vs_ieta_TP16", 11,17.5,28.5,5, -0.5, 4.5 );
  TH2F* idx_vs_ieta_ETP16_IDX2     = new TH2F("idx_vs_ieta_ETP16_IDX2","idx_vs_ieta_ETP16_IDX2",11,17.5,28.5, 5, -0.5, 4.5);
  TH2F* idx_vs_ieta_ETP16_IDXAny   = new TH2F("idx_vs_ieta_ETP16_IDXAny","idx_vs_ieta_ETP16_IDXAny",11,17.5,28.5,5, -0.5, 4.5);

  
  TH2F* ieta_vs_idx_L1Iso    = new TH2F("ieta_vs_idx_L1Iso","ieta_vs_idx_L1Iso",5, 0.5, 5.5, 70, -70.5,70.5);
  TH2F* ieta_vs_idx_L1NonIso = new TH2F("ieta_vs_idx_L1NonIso","ieta_vs_idx_L1NonIso",5, 0.5, 5.5, 70, -70.5,70.5);

  TH2F* ieta_vs_idx_L1Iso_binFix      = new TH2F("ieta_vs_idx_L1Iso_binFix","ieta_vs_idx_L1Iso_binFix",5, 0.5, 5.5, 70, -70.5,70.5);
  TH2F* ieta_vs_idx_L1NonIso_binFix   = new TH2F("ieta_vs_idx_L1NonIso_binFix","ieta_vs_idx_L1NonIso_binFix",5, 0.5, 5.5, 70, -70.5,70.5);
  

  TH1F* idx_TP0                    = new TH1F("idx_TP0","idx_TP0_ETP",5, -0.5, 4.5);
  TH1F* idx_TP0_ETP                = new TH1F("idx_TP0_ETP","idx_TP0_ETP",5, -0.5, 4.5);
  
  
  TH1F* detaIso_         = new TH1F("detaIso_","detaIso_",20,0,20);
  TH1F* dphiIso_         = new TH1F("dphiIso_","dphiIso_",20,0,20);
  TH1F* detaNonIso_      = new TH1F("detaNonIso_","detaNonIso_",20,0,20);
  TH1F* dphiNonIso_      = new TH1F("dphiNonIso_","dphiNonIso_",20,0,20);
  
  TH2F* deta_dphi_Iso_   = new TH2F("deta_dphi_Iso_","deta_dphi_Iso_", 20,0,20,20,0,20);
  TH2F* deta_dphi_NonIso_   = new TH2F("deta_dphi_NonIso_","deta_dphi_NonIso_", 20,0,20,20,0,20);

  TH1F* drMin_Iso_               = new TH1F("drMin_Iso_","drMin_Iso_",10,0,10);
  TH1F* drMin_NonIso_            = new TH1F("drMin_NonIso_","drMin_NonIso_",10,0,10);
  
  // new histogram to get the probability in simulation 
  TH1F* ttidx_Iso_dr_         = new TH1F("ttidx_Iso_dr_","ttidx_Iso_dr_",5,-2.5,2.5);
  TH1F* ttidx_NonIso_dr_      = new TH1F("ttidx_NonIso_dr_","ttidx_Iso_dr_",5,-2.5,2.5);
  
  
  TH2F* egidx_ttidx_Iso_   = new TH2F("egidx_ttidx_Iso_","egidx_ttidx_Iso_", 5,-2.5,2.5,5,-2.5,2.5);
  TH2F* egidx_ttidx_Iso_dr_   = new TH2F("egidx_ttidx_Iso_dr_","egidx_ttidx_Iso_dr_", 5,-2.5,2.5,5,-2.5,2.5);
  TH2F* egidx_ttidx_Iso_de_   = new TH2F("egidx_ttidx_Iso_de_","egidx_ttidx_Iso_de_", 5,-2.5,2.5,5,-2.5,2.5);
  
  TH2F* egidx_ttidx_NonIso_   = new TH2F("egidx_ttidx_NonIso_","egidx_ttidx_NonIso_", 5,-2.5,2.5,5,-2.5,2.5);
  TH2F* egidx_ttidx_NonIso_dr_   = new TH2F("egidx_ttidx_NonIso_dr_","egidx_ttidx_NonIso_dr_", 5,-2.5,2.5,5,-2.5,2.5);
  TH2F* egidx_ttidx_NonIso_de_   = new TH2F("egidx_ttidx_NonIso_de_","egidx_ttidx_NonIso_de_", 5,-2.5,2.5,5,-2.5,2.5);

  
  TH2F* DE_vs_DR_Iso_              = new TH2F("DE_vs_DR_Iso_","DE_vs_DR_Iso_",100,-100,100, 10, 0,10 );
  TH2F* DEbyE_vs_DR_Iso_              = new TH2F("DEbyE_vs_DR_Iso_","DEbyE_vs_DR_Iso_",100,-1,10, 10, 0,10 );
  TH2F* DEbyE_c_vs_DR_Iso_              = new TH2F("DEbyE_c_vs_DR_Iso_","DEbyE_vs_DR_Iso_",100,-1,10, 10, 0,10 );
  TH2F* Etower_vs_Ecandidate_Iso_  = new TH2F("Etower_vs_Ecandidate_Iso_","Etower_vs_Ecandidate_Iso_",100,0,200, 100, 0,200);
  
  TH2F* pseudo_egidx_ttidx_NonIso_ = new TH2F("pseudo_egidx_ttidx_NonIso_","pseudo_egidx_ttidx_NonIso_", 5,-2.5,2.5,5,-2.5,2.5);
  
  //TH2F* egidx_ttidx_Iso_dr_eta_egamma_[3]; //  1.442-2.0, 2.0-2.5, 2.5-3.0 
  
  TH2F* egidx_ttidx_Iso_bin_[5];  
  TH2F* egidx_ttidx_Iso_dr_bin_[5];  
  TH2F* egidx_ttidx_NonIso_bin_[5];  
  TH2F* egidx_ttidx_NonIso_dr_bin_[5];
  // last bin is for 27+28 ring combined 

  /*
  for (int i=0; i<3; i++){
    TString postname;
    postname.Form("%d",i);
    egidx_ttidx_Iso_dr_eta_egamma_  = new TH2F("egidx_ttidx_Iso_dr_eta_egamma_"+postname,         "egidx_ttidx_Iso_dr_eta_egamma_",          5,-2.5,2.5,5,-2.5,2.5);;

  }
  */
  
  for (int i=0; i<5; i++){
    TString postname;
    postname.Form("%d",i+26);
    
    egidx_ttidx_Iso_bin_[i]          = new TH2F("egidx_ttidx_Iso_bin_"+postname,         "egidx_ttidx_Iso_bin_",          5,-2.5,2.5,5,-2.5,2.5);
    egidx_ttidx_Iso_dr_bin_[i]       = new TH2F("egidx_ttidx_Iso_dr_bin_"+postname,      "egidx_ttidx_Iso_dr_bin_",       5,-2.5,2.5,5,-2.5,2.5);
    egidx_ttidx_NonIso_bin_[i]       = new TH2F("egidx_ttidx_NonIso_bin_"+postname,      "egidx_ttidx_NonIso_bin_",       5,-2.5,2.5,5,-2.5,2.5);
    egidx_ttidx_NonIso_dr_bin_[i]    = new TH2F("egidx_ttidx_NonIso_dr_bin_"+postname,   "egidx_ttidx_NonIso_dr_bin_",    5,-2.5,2.5,5,-2.5,2.5);
  }
  
  
  TH1F* idx_TP0_vec[11];
  TH1F* idx_TP0_ETP_vec[11];
  

  

  
  //std::cout<<" histo defined "<<std::endl;

  


  for (int i=0; i<11; i++){
    TString postname;
    postname.Form("%d",i+18);
    std::cout<<" postname = "<<postname<<std::endl;
    idx_TP0_vec[i] = new TH1F("idx_TP0_vec_"+postname, "idx_TP0_vec_"+postname, 5, -0.5, 4.5);
    idx_TP0_ETP_vec[i] = new TH1F("idx_TP0_ETP_vec_"+postname, "idx_TP0_ETP_vec_"+postname, 5, -0.5, 4.5);
    
  }
  
  TH1F* ieta_TP_ETP_INTIME         = new TH1F("ieta_TP_ETP_INTIME","ieta_TP_ETP_INTIME",57,-28.5,28.5);
  TH1F* ieta_TP_ETP_OUTTIME        = new TH1F("ieta_TP_ETP_OUTTIME","ieta_TP_ETP_OUTTIME",57,-28.5,28.5);
  TH1F* ieta_TP0_ETP               = new TH1F("ieta_TP0_ETP","ieta_TP0_ETP",57,-28.5,28.5);
  TH1F* ieta_TP_ETP                = new TH1F("ieta_TP_ETP","ieta_TP_ETP",57,-28.5,28.5);
  TH1F* ieta_TP0                   = new TH1F("ieta_TP0","ieta_TP0",57,-28.5,28.5);

  

  // set branch addresses to read trees
  
  EcalTPGVariables treeVars ;
  setBranchAddresses (chain, treeVars) ;
   
  
  
  Int_t treeentries=chain->GetEntries();

  int count=0;
  int countsev=0;
  int countsev3=0;
  int countsev4=0;

  std::vector<float> etaV = MaskedCoordinate();
  std::vector<float> phiV = MaskedCoordinate();
  
  
  TowerVariables maxTower;
  std::vector<TowerVariables> maxTowerVector;

  TowerVariables Pseudo_maxTower;
  std::vector<TowerVariables> Pseudo_maxTowerVector;


  
  EGVariables egcandidateIso;
  EGVariables egcandidateNonIso;
  
  EGVariables Pseudo_egcandidateIso;
  EGVariables Pseudo_egcandidateNonIso;
  
  std::vector<EGVariables> egcandidateIsoVector;
  std::vector<EGVariables> egcandidateNonIsoVector;

  std::vector<EGVariables> Pseudo_egcandidateIsoVector;
  std::vector<EGVariables> Pseudo_egcandidateNonIsoVector;
  
  
  
  std::cout<<" treeentries = "<<treeentries<<std::endl;
  for (int entry = 0 ; entry < treeentries ; ++entry) {
    //if (entry <649) continue;
    
    maxTowerVector.clear();
    egcandidateIsoVector.clear();
    egcandidateNonIsoVector.clear();
    
    Pseudo_maxTowerVector.clear();
    Pseudo_egcandidateIsoVector.clear();
    Pseudo_egcandidateNonIsoVector.clear();
    
    
    //for (int entry = 15000 ; entry < 16000 ; ++entry) {
    
    chain->GetEntry (entry) ;
    
    if (entry%1000==0) cout << entry << " / " << treeentries
			    << " events processed" << endl;
    
    
    
    // accessing the gen level information for MC samples 
    if (debug__) std::cout<<" n gen particles  = "<<treeVars.nGenPar<<std::endl;
    chain->SetBranchAddress("genParPy_", treeVars.genParPy) ;
    chain->SetBranchAddress("genParPz_", treeVars.genParPz) ;
    chain->SetBranchAddress("genParE_", treeVars.genParE) ;
    chain->SetBranchAddress("genParId_", treeVars.genParId) ;
    chain->SetBranchAddress("genParSt_", treeVars.genParSt) ;
    chain->SetBranchAddress("genMomParId_", treeVars.genMomParId) ;

    if (debug__) std::cout<<" px 1 = "<<treeVars.genParPx[0]
			  <<"  "<<treeVars.genParPy[0]
			  <<"  "<<treeVars.genParPz[0]
			  <<"  "<<treeVars.genParE[0]
			  <<"  "<<treeVars.genParId[0]
			  <<"  "<<treeVars.genParSt[0]
			  <<"  "<<treeVars.genMomParId[0]
			  <<std::endl;


    
    bool goodBX = false;
    
    // this ensures that the lumi block is selected for given timing 
    
    if(treeVars.lumiBlock < lumi1) continue ;
    if(treeVars.lumiBlock > lumi2) continue ;
    //if ( !(  (treeVars.lumiBlock > lumi1) && (treeVars.lumiBlock < lumi2) ) ) continue ;
    
        
    	

    //std::cout<<"  ------------------------------------------------------------------------------------ ------------------------------------------------------------------------------------ \n"<<std::endl;
    
    //cout << "event number is " << entry << "  bxn is "<<treeVars.bxNb<<"\n" ;

    UInt_t runNb = treeVars.runNb;
    ULong64_t evtNb = treeVars.evtNb;
    UInt_t bxNb = treeVars.bxNb;;
    UInt_t lumiBlock = treeVars.lumiBlock;
    
    // these vars are for gen matching 
    //    - for first electron
    std::vector<int> tower_index1;
    float pseudo_L1T_sum1[5]={0.}; // it will store five values, one for each index
    tower_index1.clear();
    //   - for second electron 
    std::vector<int> tower_index2;
    float pseudo_L1T_sum2[5]={0.}; // it will store five values, one for each index
    tower_index2.clear();
    


    // gen matching vars ends here 

    
    
      for (UInt_t tower = 0 ; tower < treeVars.nbOfTowers ; tower++) {
      
      int ieta = treeVars.ieta[tower] ;
      int iphi = treeVars.iphi[tower] ;
      if (abs(ieta) <18) continue; 
      
      int tp = getEt(treeVars.rawTPData[tower]) ;
      int raw_spike = treeVars.trig_tower_sFGVB[tower];
      int ttflag=treeVars.ttFlag[tower];
      float erec_val=treeVars.eRec[tower];
      int severity_level=treeVars.sevlv[tower];
      int nxtals=treeVars.crystNb[tower];
      
      int emul[5] = {getEt(treeVars.rawTPEmul1[tower]),  
		     getEt(treeVars.rawTPEmul2[tower]),
		     getEt(treeVars.rawTPEmul3[tower]),
		     getEt(treeVars.rawTPEmul4[tower]),
		     getEt(treeVars.rawTPEmul5[tower])} ;
      int emulsFGVB[5] = {treeVars.rawTPEmulsFGVB1[tower],  
			  treeVars.rawTPEmulsFGVB2[tower],
			  treeVars.rawTPEmulsFGVB3[tower],
			  treeVars.rawTPEmulsFGVB4[tower],
			  treeVars.rawTPEmulsFGVB5[tower]} ;
      
      int emulTTF[5] = {treeVars.rawTPEmulttFlag1[tower],  
			    treeVars.rawTPEmulttFlag2[tower],
			treeVars.rawTPEmulttFlag3[tower],
			treeVars.rawTPEmulttFlag4[tower],
			treeVars.rawTPEmulttFlag5[tower]} ;
      
      
      
      int maxOfTPEmul = 0 ;
      int indexOfTPEmulMax = -1 ;
      int emulsfgvb=-1;
      int emulttf=-1;
      
      
      for (int i=0 ; i<5 ; i++) {
	if (emul[i]>maxOfTPEmul)
	  {
	    maxOfTPEmul = emul[i] ; 
	    indexOfTPEmulMax = i ;
	    emulsfgvb=emulsFGVB[i];
	    emulttf=emulTTF[i];
	  }
      }
        
      
      
      
      
      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      //--------------------------------------------    gen match related information is all here, gen matching with TPs, making pseudo L1T candidates ------------------------------------------
      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      
      // this piece of code assume that we will use e+ e- gun, without any PU. 
      // for generic code we need more dedicated algorithm 
      
      /* Algorithm for Pseudo L1T 

	 - match electron with the towers, 
	 - all matched towers index enter a index vector [can be used later if needed ]
	 - create 5 energy sum variables; sum1, sum2, sum3, sum4, sum5 [right now pt: incorrect ]
	 - when a matched tower is found in addition to pushing it to index vector add energy energy to the energy sum variable, 
	 - sum1 = sum1 + emul[0]
	 - These 5 energy values can now be used for L1T candidates 
	 - We can now check the max of the sum1, sum2, sum3, sum4, sum5, and the index where we get max of sum can be used for 2d plotting 
	 
      */

      if (maxOfTPEmul>0){
	TLorentzVector p41;
	TLorentzVector p42; 
	p41.SetPxPyPzE(treeVars.genParPx[0], treeVars.genParPy[0], treeVars.genParPz[0], treeVars.genParE[0]);
	p42.SetPxPyPzE(treeVars.genParPx[1], treeVars.genParPy[1], treeVars.genParPz[1], treeVars.genParE[1]);
	
	// DRTowerElectron checks that eta and phi are within +- 1 towers, so we will collect maximum of 9 towers to make the L1T candidate 
	//   - in addition dphi can be +-2 
	//   - if dphi is 72 it is set to 0 [think a bit this is correct, i couldn't find  a better way to do this]
	
	bool match1 = DRTowerElectron(ieta, iphi, etaToiEta(p41.Eta()), phiToiPhi(p41.Phi()) );
	bool match2 = DRTowerElectron(ieta, iphi, etaToiEta(p42.Eta()), phiToiPhi(p42.Phi()) );
	
	if (match1) {
	  tower_index1.push_back(tower);
	  pseudo_L1T_sum1[0] = pseudo_L1T_sum1[0] + emul[0];
	  pseudo_L1T_sum1[1] = pseudo_L1T_sum1[1] + emul[1];
	  pseudo_L1T_sum1[2] = pseudo_L1T_sum1[2] + emul[2];
	  pseudo_L1T_sum1[3] = pseudo_L1T_sum1[3] + emul[3];
	  pseudo_L1T_sum1[4] = pseudo_L1T_sum1[4] + emul[4];
	}
	
	if (match2) {
	  tower_index2.push_back(tower);
	  pseudo_L1T_sum2[0] = pseudo_L1T_sum2[0] + emul[0];
	  pseudo_L1T_sum2[1] = pseudo_L1T_sum2[1] + emul[1];
	  pseudo_L1T_sum2[2] = pseudo_L1T_sum2[2] + emul[2];
	  pseudo_L1T_sum2[3] = pseudo_L1T_sum2[3] + emul[3];
	  pseudo_L1T_sum2[4] = pseudo_L1T_sum2[4] + emul[4];
	}
	//int seed_tower = GetGenMatchedTP();
	if (maxOfTPEmul>0 && debug__) std::cout<<" tower number "<<tower
				    <<" index = "<<indexOfTPEmulMax
				    <<" eta = "<<ieta
				    <<" iphi = "<<iphi
				    <<" ele1 eta "<<etaToiEta(p41.Eta())
				    <<" ele1 phi  "<<phiToiPhi(p41.Phi())
				    <<" ele2 eta "<<etaToiEta(p42.Eta())
				    <<" ele2 phi  "<<phiToiPhi(p42.Phi())
				    <<" deta1, dphi1 = ("<<fabs(ieta - etaToiEta(p41.Eta()))<<", "<<fabs(iphi-phiToiPhi(p41.Phi()))<<")"
				    <<" deta2, dphi2 = ("<<fabs(ieta - etaToiEta(p42.Eta()))<<", "<<fabs(iphi-phiToiPhi(p42.Phi()))<<")"
				    <<" match 1, 2 = ("<<match1<<", "<<match2<<")"
				    <<std::endl;
	
      }//if (maxOfTPEmul>0){


      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      //--------------------------------------------    gen match related information ends here ------------------------------------------------------ ------------------------------------------
      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
          
      
      
      //if (tp > threshold) std::cout<<" tower number = "<<tower<<" with eta phi = "<<ieta <<"  "<<iphi <<"  "<<" and energy "<< tp << " emul max "<< maxOfTPEmul <<" at emul idx = "<<indexOfTPEmulMax<<std::endl;

      
      // get the masked towers.
      if (tp>0.0) ieta_vs_iphi_TP->Fill(ieta,iphi);
      if (maxOfTPEmul > 0.0) ieta_vs_iphi_ETP->Fill(ieta,iphi);
      // masked towers ends here. 
      
      // check if this is already tagged by COKE
      bool hasnoisyxtal  = false;
      if (is2017 && isdata) hasnoisyxtal = false;
      if (!is2017 && isdata ) hasnoisyxtal  = (ttflag >3) ; 

      // check if the TT is already masked. 
      bool masked_ = false;
      if (isdata) masked_ = isMasked(etaV, phiV, ieta, iphi);
      
      
      // skip the tower if this is msked or it is tagged by COKE as noisy. 
      if (masked_) continue;
      if (hasnoisyxtal) continue;
      
            
      // data TP has energy > threshold ADC
      if (tp>threshold){
	ieta_vs_iphi_TP16->Fill(ieta, iphi);
        idx_vs_ieta_TP16->Fill(ieta, indexOfTPEmulMax);

      }
      
      
      // emulated TP has energy > 16 ADC and it is in right bunch crossing 
      if(maxOfTPEmul>threshold && indexOfTPEmulMax==2){
	ieta_vs_iphi_ETP16_IDX2->Fill(ieta, iphi);
	idx_vs_ieta_ETP16_IDX2->Fill(ieta, indexOfTPEmulMax);
      }
      
      
      
      maxOfTPEmul_->Fill(maxOfTPEmul);
      // emiulated Tp has energy > 16 ADC and it can be in any bunch crossing. 
      if(maxOfTPEmul>threshold){
	ieta_vs_iphi_ETP16_IDXAny->Fill(ieta, iphi);
	idx_vs_ieta_ETP16_IDXAny->Fill(abs(ieta), indexOfTPEmulMax);
      }


      
      
      // denominator for condition 1 and 2 are same. The denominator for condition 3 is defined differently. 
      // I might have to change this  (ask David?) 
     

      // denominator seelction for 1 and 2
      if (tp>threshold && maxOfTPEmul>0){
	ieta_vs_iphi_TP_ETP->Fill(ieta, iphi);
	ieta_TP_ETP->Fill(ieta);

	
	//  this histogram will be compared with L1T real data. so that data and emulator is side by side. This is also used to make 2d corelation matrix after matching with the eg candidates .
	
	ieta_vs_idx_TP_ETP->Fill(abs(ieta), indexOfTPEmulMax);
	//std::cout<<" filling maxTower "
	//	 <<" "<<ieta
	//	 <<" "<<iphi
	//	 <<" "<<indexOfTPEmulMax
	//	 <<" "<<maxOfTPEmul
	//	 <<std::endl;
	// fill these towers in  avector so that they can be used later. 
	maxTower.eta = ieta;
	maxTower.phi = iphi; 
	maxTower.idx = indexOfTPEmulMax;
	maxTower.energy = maxOfTPEmul;
	maxTower.tpenergy = tp;
	
	//std::cout<<" energy debug === "<<maxOfTPEmul<<"  "<<ieta<<"  "<<iphi<<"  "<<std::endl;
      
	maxTowerVector.push_back(maxTower);
	//std::cout<<" denominator for the cond1 and cond2"<<std::endl;
	// condition 1: 
	// where both data and emulated TPs exist, and the emulated TP is in the correct bunch crossing
	if (tp>16 && maxOfTPEmul>0 && indexOfTPEmulMax==2){
	  ieta_vs_iphi_TP_ETP_INTIME->Fill(ieta, iphi);
	  ieta_TP_ETP_INTIME->Fill(ieta);
	  //std::cout<<" numerator for the cond1 and cond2"<<std::endl;
	}
	
	// condition 2: 
	// where both data and emulated TPs exist, but the emulated TP is in the wrong bunch crossing
	if (tp>threshold && maxOfTPEmul>0 && indexOfTPEmulMax!=2){
	  ieta_vs_iphi_TP_ETP_OUTTIME->Fill(ieta, iphi);
	  ieta_TP_ETP_OUTTIME->Fill(ieta);
	  //std::cout<<" numerator for the cond2"<<std::endl;
	}
      }// if (tp>16 && maxOfTPEmul>0){



      // for matching with Pseudo L1EG candidates 
      // we can't use the maxTowerVector because is has a condition that energy deposit in the intime bX should be > 0; tp > threshold which we don't want. 
      if (maxOfTPEmul > threshold){
	Pseudo_maxTower.eta = ieta;
	Pseudo_maxTower.phi = iphi; 
	Pseudo_maxTower.idx = indexOfTPEmulMax;
	Pseudo_maxTower.energy = maxOfTPEmul;
	Pseudo_maxTower.tpenergy = tp;
	Pseudo_maxTowerVector.push_back(Pseudo_maxTower);
      }// maxOfTPEmul > threshold 

      
      
      // denominator for condition 3: 
      if (tp==0  && !hasnoisyxtal ){
	//std::cout<<" this TT is masked "<<masked_<<" "<<ieta<<" " <<iphi<<" "<<std::endl;
	if (masked_) continue ;
	
	//
	idx_TP0->Fill(indexOfTPEmulMax);
	int ieta_index = abs(ieta) - 18;
	//std::cout<<" ieta, ieta_index "<< ieta<<"  "<<ieta_index<<std::endl;
	idx_TP0_vec[ieta_index]->Fill(indexOfTPEmulMax);
	
	ieta_vs_iphi_TP0->Fill(ieta, iphi);
	ieta_TP0->Fill(ieta) ;
	
	ieta_vs_idx_TP0->Fill(abs(ieta), indexOfTPEmulMax);
	// condition 3: 
	// where only an emulated TP exists  (here it will be necessary to remove towers that are masked)
	if ( tp==0 && maxOfTPEmul>threshold) {
	  
	  // 
	  ieta_vs_idx_TP0_ETP->Fill(abs(ieta), indexOfTPEmulMax);
	  
	  
	  //std::cout<<" TT flag = "<<ttflag<<std::endl;
	  
	  
	  ieta_vs_iphi_TP0_ETP->Fill(ieta, iphi);
	  idx_TP0_ETP->Fill(indexOfTPEmulMax);
	  
	  idx_TP0_ETP_vec[ieta_index]->Fill(indexOfTPEmulMax);
	  
	  ieta_TP0_ETP->Fill(ieta) ;
	  
	  //std::cout<<" numerator for the cond3"<<std::endl;

	}
      }//if (tp==0){
      
      
      
      // barrel: abs(ieta)  < 18
      // endcap: abs(ieta) >= 18 (10 TT on each side)
      
      
      }//for (UInt_t tower = 0 ; tower < treeVars.nbOfTowers ; tower++) {
    
      
      // After the Tower loop we can now print the Pseudo L1T variables just fulled 
      if (debug__) std::cout<<"for ele 1 n towers ="<<tower_index1.size()
			    <<"; L1T idx 1 "<<pseudo_L1T_sum1[0]
			    <<"; L1T idx 2 "<<pseudo_L1T_sum1[1]
			    <<"; L1T idx 3 "<<pseudo_L1T_sum1[2]
			    <<"; L1T idx 4 "<<pseudo_L1T_sum1[3]
			    <<"; L1T idx 5 "<<pseudo_L1T_sum1[4];
      
	  
	  
      for (int idx_=0; idx_<int(tower_index1.size());idx_++){
	if (debug__) std::cout<<" tower: "<<tower_index1[idx_]<<" ";
      }
      if (debug__) std::cout<<std::endl;

      if (debug__) std::cout<<"for ele 2 n towers ="<<tower_index2.size()
	       <<"; L1T idx 1 "<<pseudo_L1T_sum2[0]
	       <<"; L1T idx 2 "<<pseudo_L1T_sum2[1]
	       <<"; L1T idx 3 "<<pseudo_L1T_sum2[2]
	       <<"; L1T idx 4 "<<pseudo_L1T_sum2[3]
	       <<"; L1T idx 5 "<<pseudo_L1T_sum2[4];
		 
	  
	  
      for (int idx_=0; idx_<int(tower_index2.size());idx_++){
	if (debug__) std::cout<<" tower: "<<tower_index2[idx_]<<" ";
      }
      if (debug__)std::cout<<std::endl;

      // Fill the information to validate the Pseudo L1T candidates 
      // -- Number of towers used to make L1T candidates for both electrons in same histogram 
      h_PL1T_nTowers_->Fill(tower_index1.size());
      h_PL1T_nTowers_->Fill(tower_index2.size());
      // -- L1T energy in each BX for both electrons [for both electron in same histogram]
      h_PL1T_Energy0_->Fill(pseudo_L1T_sum1[0]);       h_PL1T_Energy0_->Fill(pseudo_L1T_sum2[0]);
      h_PL1T_Energy1_->Fill(pseudo_L1T_sum1[1]);       h_PL1T_Energy1_->Fill(pseudo_L1T_sum2[1]);
      h_PL1T_Energy2_->Fill(pseudo_L1T_sum1[2]);       h_PL1T_Energy2_->Fill(pseudo_L1T_sum2[2]);
      h_PL1T_Energy3_->Fill(pseudo_L1T_sum1[3]);       h_PL1T_Energy3_->Fill(pseudo_L1T_sum2[3]);
      h_PL1T_Energy4_->Fill(pseudo_L1T_sum1[4]);       h_PL1T_Energy4_->Fill(pseudo_L1T_sum2[4]);
      
      
      
      // -- Idx for max energy deposit 
      const int N = sizeof(pseudo_L1T_sum1) / sizeof(float);
      
      int max_idx1 = std::distance(pseudo_L1T_sum1, std::max_element(pseudo_L1T_sum1, pseudo_L1T_sum1+N) ) + 1; // +1 is done becuase by default index start from zero
      int max_idx2 = std::distance(pseudo_L1T_sum2, std::max_element(pseudo_L1T_sum2, pseudo_L1T_sum2+N) ) + 1;
      
      
      h_PL1T_maxIndex_->Fill(max_idx1);     h_PL1T_maxIndex_->Fill(max_idx2);
      
      // For 2d correlation plot of indices: Tower vs Pseudo L1 G candidate 
      // we have to fill it twice becuase we know there are 2 candidates 
      // filling everything in the non iso vector (no particular choice) 
      // we don't know if it is isolated or not, there is no definition as of now. 
      Pseudo_egcandidateNonIso.iso = false;
      Pseudo_egcandidateNonIso.eta = Pseudo_maxTowerVector[0].eta; // take the eta phi of tower with max energy and contributing to the L1 candidate 
      Pseudo_egcandidateNonIso.phi = Pseudo_maxTowerVector[0].phi; // but for now we set to -1 as it is likely not needed 
      Pseudo_egcandidateNonIso.idx = max_idx1; 
      Pseudo_egcandidateNonIso.energy = pseudo_L1T_sum1[max_idx1]; // assuming same value for energy and pt sum; 
      Pseudo_egcandidateNonIso.pt = pseudo_L1T_sum1[max_idx1]; // not correct but ok for zeroth order effect, given that eta phi of towers making the L1 egamma candidates are almost same,. 
      Pseudo_egcandidateNonIsoVector.push_back(Pseudo_egcandidateNonIso);
      

      Pseudo_egcandidateNonIso.iso = false;
      Pseudo_egcandidateNonIso.eta = Pseudo_maxTowerVector[0].eta; // take the eta phi of tower with max energy and contributing to the L1 candidate 
      Pseudo_egcandidateNonIso.phi = Pseudo_maxTowerVector[0].phi; // but for now we set to -1 as it is likely not needed 
      Pseudo_egcandidateNonIso.idx = max_idx2; 
      Pseudo_egcandidateNonIso.energy = pseudo_L1T_sum2[max_idx2]; // assuming same value for energy and pt sum; 
      Pseudo_egcandidateNonIso.pt = pseudo_L1T_sum2[max_idx2]; // not correct but ok for zeroth order effect, given that eta phi of towers making the L1 egamma candidates are almost same,. 
      Pseudo_egcandidateNonIsoVector.push_back(Pseudo_egcandidateNonIso);
      
      
      // Now the Pseudo_egcandidateNonIsoVector vector is ready 
      // loop over Pseudo_MaxTower vector and find the max energy tower 
      // check the index of this max energy tower  i_idx
      // check the max index of pseudo L1 candidate j_idx 
      // do the correlation plot of i_idx and j_idx 
      
      /*
      int pseudo_tower_emul_idxmax=-1;
      float maxenergy = 0;
      for (int itwr=0; itwr<(int)Pseudo_maxTowerVector.size(); itwr++){
	if (Pseudo_maxTowerVector[itwr].energy > maxenergy){
	  maxenergy = Pseudo_maxTowerVector[itwr].energy; 
	  pseudo_tower_emul_idxmax = itwr;
	}

      }
      
      pseudo_egidx_ttidx_NonIso_->Fill(  , Pseudo_maxTowerVector[pseudo_tower_emul_idxmax].idx-2);
      
      std::cout<<" index of the max emul tower  = "<<Pseudo_maxTowerVector[pseudo_tower_emul_idxmax].idx+1<<std::endl;
      */

    
      if (Pseudo_egcandidateNonIsoVector.size()>0 && Pseudo_maxTowerVector.size()>0){
	std::vector<int> pseudo_dirIso_ = PseudoCalculateDeltaIR(Pseudo_egcandidateNonIsoVector, Pseudo_maxTowerVector);
	pseudo_egidx_ttidx_NonIso_->Fill( pseudo_dirIso_[3]-3 , pseudo_dirIso_[4]-2);
      }
      
    // once the maxTowerVector is filled and loop over the towers is over one can print what ios inside 
    //TowerVariablesShow(maxTowerVector);
    
    // 1 refer to prefiring 
    // 2 refer to central bx
    // 3 refer to post firing 
    
    



    
    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // ---------------------Fill in all relevant information about the prefiring, postfiring, and intime bunches for both isolated and nonisolated e-gamma objects. -----------
    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    // prefiring isolated -2
    if (treeVars.nbOfL1preIsoCandsm2>0) {
      for (UInt_t iNL1preIsom2 = 0; iNL1preIsom2 < treeVars.nbOfL1preIsoCandsm2; iNL1preIsom2++) {
	if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsom2
		 <<" eta = "<<treeVars.L1preIsoIetam2[iNL1preIsom2]
		 <<" phi = "<<treeVars.L1preIsoIphim2[iNL1preIsom2]
		 <<" energy = "<<treeVars.L1preIsoEnergym2[iNL1preIsom2]
		 <<std::endl;
	ieta_vs_idx_L1Iso->Fill(1, treeVars.L1preIsoIetam2[iNL1preIsom2]);
	ieta_vs_idx_L1Iso_binFix->Fill(1, (63./28.)*treeVars.L1preIsoIetam2[iNL1preIsom2] );
	
	egcandidateIso.iso = true;
	egcandidateIso.eta = treeVars.L1preIsoIetam2[iNL1preIsom2];
	egcandidateIso.phi = treeVars.L1preIsoIphim2[iNL1preIsom2];
	egcandidateIso.idx = -2;
	egcandidateIso.energy = treeVars.L1preIsoEnergym2[iNL1preIsom2];
	egcandidateIso.pt = treeVars.L1preIsoPtm2[iNL1preIsom2];
	egcandidateIsoVector.push_back(egcandidateIso);
	
	
      }
    }

    if(treeVars.nbOfL1preIsoCandsm1>0){
      //std::cout<<" isolated     non isolated    = "<<treeVars.nbOfL1preIsoCandsm1<<"  "<<treeVars.nbOfL1preNonisoCandsm1<<std::endl;
	     
    }



    // prefiring isolated -1
    if (treeVars.nbOfL1preIsoCandsm1>0) {
      for (UInt_t iNL1preIsom1 = 0; iNL1preIsom1 < treeVars.nbOfL1preIsoCandsm1; iNL1preIsom1++) {
	if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsom1
		 <<" eta = "<<treeVars.L1preIsoIetam1[iNL1preIsom1]
		 <<" phi = "<<treeVars.L1preIsoIphim1[iNL1preIsom1]
		 <<" energy = "<<treeVars.L1preIsoEnergym1[iNL1preIsom1]
		 <<std::endl;
	ieta_vs_idx_L1Iso->Fill(2, treeVars.L1preIsoIetam1[iNL1preIsom1]);
	ieta_vs_idx_L1Iso_binFix->Fill(2, (63./28.)*treeVars.L1preIsoIetam1[iNL1preIsom1] );
	
	egcandidateIso.iso = true;
	egcandidateIso.eta = treeVars.L1preIsoIetam1[iNL1preIsom1];
	egcandidateIso.phi = treeVars.L1preIsoIphim1[iNL1preIsom1];
	egcandidateIso.idx = -1;
	egcandidateIso.energy = treeVars.L1preIsoEnergym1[iNL1preIsom1];
	egcandidateIso.pt = treeVars.L1preIsoPtm1[iNL1preIsom1];
	egcandidateIsoVector.push_back(egcandidateIso);
	
      }
    }



    // in time zero isolated 
    if (treeVars.nbOfL1preIsoCandszero>0) {
      for (UInt_t iNL1preIsozero = 0; iNL1preIsozero < treeVars.nbOfL1preIsoCandszero; iNL1preIsozero++) {
        if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsozero
		 <<" eta = "<<treeVars.L1preIsoIetazero[iNL1preIsozero]
		 <<" phi = "<<treeVars.L1preIsoIphizero[iNL1preIsozero]
		 <<" energy = "<<treeVars.L1preIsoEnergyzero[iNL1preIsozero]
		 <<std::endl;
	
	ieta_vs_idx_L1Iso->Fill(3, treeVars.L1preIsoIetazero[iNL1preIsozero]);
	ieta_vs_idx_L1Iso_binFix->Fill(3, (63./28.)*treeVars.L1preIsoIetazero[iNL1preIsozero] );
	
	egcandidateIso.iso = true;
	egcandidateIso.eta = treeVars.L1preIsoIetazero[iNL1preIsozero];
	egcandidateIso.phi = treeVars.L1preIsoIphizero[iNL1preIsozero];
	egcandidateIso.idx = 0;
	egcandidateIso.energy = treeVars.L1preIsoEnergyzero[iNL1preIsozero];
	egcandidateIso.pt = treeVars.L1preIsoPtzero[iNL1preIsozero];
	egcandidateIsoVector.push_back(egcandidateIso);
	  
      }
    }

    
    
    
    // postfiring isolated +1
    if (treeVars.nbOfL1preIsoCandsp1>0) {
      for (UInt_t iNL1preIsop1 = 0; iNL1preIsop1 < treeVars.nbOfL1preIsoCandsp1; iNL1preIsop1++) {
	if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsop1
		 <<" eta = "<<treeVars.L1preIsoIetap1[iNL1preIsop1]
		 <<" phi = "<<treeVars.L1preIsoIphip1[iNL1preIsop1]
		 <<" energy = "<<treeVars.L1preIsoEnergyp1[iNL1preIsop1]
		 <<std::endl;
	ieta_vs_idx_L1Iso->Fill(4, treeVars.L1preIsoIetap1[iNL1preIsop1]);
	ieta_vs_idx_L1Iso_binFix->Fill(4, (63./28.)*treeVars.L1preIsoIetap1[iNL1preIsop1] );
	
	egcandidateIso.iso = true;
	egcandidateIso.eta = treeVars.L1preIsoIetap1[iNL1preIsop1];
	egcandidateIso.phi = treeVars.L1preIsoIphip1[iNL1preIsop1];
	egcandidateIso.idx = 1;
	egcandidateIso.energy = treeVars.L1preIsoEnergyp1[iNL1preIsop1];
	egcandidateIso.pt = treeVars.L1preIsoPtp1[iNL1preIsop1];
	egcandidateIsoVector.push_back(egcandidateIso);
	
      }
    }
    

    // prefiring isolated +2
    if (treeVars.nbOfL1preIsoCandsp2>0) {
      for (UInt_t iNL1preIsop2 = 0; iNL1preIsop2 < treeVars.nbOfL1preIsoCandsp2; iNL1preIsop2++) {
	if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsop2
		 <<" eta = "<<treeVars.L1preIsoIetap2[iNL1preIsop2]
		 <<" phi = "<<treeVars.L1preIsoIphip2[iNL1preIsop2]
		 <<" energy = "<<treeVars.L1preIsoEnergyp2[iNL1preIsop2]
		 <<std::endl;
	ieta_vs_idx_L1Iso->Fill(5, treeVars.L1preIsoIetap2[iNL1preIsop2]);
	ieta_vs_idx_L1Iso_binFix->Fill(5, (63./28.)*treeVars.L1preIsoIetap2[iNL1preIsop2] );
	
	egcandidateIso.iso = true;
	egcandidateIso.eta = treeVars.L1preIsoIetap2[iNL1preIsop2];
	egcandidateIso.phi = treeVars.L1preIsoIphip2[iNL1preIsop2];
	egcandidateIso.idx = 2;
	egcandidateIso.energy = treeVars.L1preIsoEnergyp2[iNL1preIsop2];
	egcandidateIso.pt = treeVars.L1preIsoPtp2[iNL1preIsop2];
	egcandidateIsoVector.push_back(egcandidateIso);
      }
    }
    








    
    // ---------------------------------------------------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------------------------------------------------------------------------------------------------------------------
    // -----------------  NON Isolated -------------------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------------------------------------------------------------------------------------------------------------------
    // prefiring non isolated -2
    if (treeVars.nbOfL1preNonisoCandsm2>0) {
      for (UInt_t iNL1preIsom2 = 0; iNL1preIsom2 < treeVars.nbOfL1preNonisoCandsm2; iNL1preIsom2++) {
	if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsom2
		 <<" eta = "<<treeVars.L1preNonisoIetam2[iNL1preIsom2]
		 <<" phi = "<<treeVars.L1preNonisoIphim2[iNL1preIsom2]
		 <<" energy = "<<treeVars.L1preNonisoEnergym2[iNL1preIsom2]
		 <<std::endl;
	ieta_vs_idx_L1NonIso->Fill(1, treeVars.L1preNonisoIetam2[iNL1preIsom2]);
	ieta_vs_idx_L1NonIso_binFix->Fill(1, (63./28.)*treeVars.L1preNonisoIetam2[iNL1preIsom2]);
	
	egcandidateNonIso.iso = false;
	egcandidateNonIso.eta = treeVars.L1preNonisoIetam2[iNL1preIsom2];
	egcandidateNonIso.phi = treeVars.L1preNonisoIphim2[iNL1preIsom2];
	egcandidateNonIso.idx = -2;
	egcandidateNonIso.energy = treeVars.L1preNonisoEnergym2[iNL1preIsom2];
	egcandidateNonIso.pt = treeVars.L1preNonisoPtm2[iNL1preIsom2];
	egcandidateNonIsoVector.push_back(egcandidateNonIso);
	
      }
    }




    
    // prefiring non isolated -1
    if (treeVars.nbOfL1preNonisoCandsm1>0) {
      for (UInt_t iNL1preIsom1 = 0; iNL1preIsom1 < treeVars.nbOfL1preNonisoCandsm1; iNL1preIsom1++) {
	if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsom1
		 <<" eta = "<<treeVars.L1preNonisoIetam1[iNL1preIsom1]
		 <<" phi = "<<treeVars.L1preNonisoIphim1[iNL1preIsom1]
		 <<" energy = "<<treeVars.L1preNonisoEnergym1[iNL1preIsom1]
		 <<std::endl;
	ieta_vs_idx_L1NonIso->Fill(2, treeVars.L1preNonisoIetam1[iNL1preIsom1]);
	ieta_vs_idx_L1NonIso_binFix->Fill(2, (63./28.)*treeVars.L1preNonisoIetam1[iNL1preIsom1]);
	  
	egcandidateNonIso.iso = false;
	egcandidateNonIso.eta = treeVars.L1preNonisoIetam1[iNL1preIsom1];
	egcandidateNonIso.phi = treeVars.L1preNonisoIphim1[iNL1preIsom1];
	egcandidateNonIso.idx = -1;
	egcandidateNonIso.energy = treeVars.L1preNonisoEnergym1[iNL1preIsom1];
	egcandidateNonIso.pt = treeVars.L1preNonisoPtm1[iNL1preIsom1];
	egcandidateNonIsoVector.push_back(egcandidateNonIso);
	
      }
    }
    


    // in time zero non isolated
    if (treeVars.nbOfL1preNonisoCandszero>0) {
      for (UInt_t iNL1preIsozero = 0; iNL1preIsozero < treeVars.nbOfL1preNonisoCandszero; iNL1preIsozero++) {
	if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsozero
		 <<" eta = "<<treeVars.L1preNonisoIetazero[iNL1preIsozero]
		 <<" phi = "<<treeVars.L1preNonisoIphizero[iNL1preIsozero]
		 <<" energy = "<<treeVars.L1preNonisoEnergyzero[iNL1preIsozero]
		 <<std::endl;
	ieta_vs_idx_L1NonIso->Fill(3, treeVars.L1preNonisoIetazero[iNL1preIsozero]);
	ieta_vs_idx_L1NonIso_binFix->Fill(3, (63./28.)*treeVars.L1preNonisoIetazero[iNL1preIsozero]);
	
	egcandidateNonIso.iso = false;
	egcandidateNonIso.eta = treeVars.L1preNonisoIetazero[iNL1preIsozero];
	egcandidateNonIso.phi = treeVars.L1preNonisoIphizero[iNL1preIsozero];
	egcandidateNonIso.idx = 0;
	egcandidateNonIso.energy = treeVars.L1preNonisoEnergyzero[iNL1preIsozero];
	egcandidateNonIso.pt = treeVars.L1preNonisoPtzero[iNL1preIsozero];
	egcandidateNonIsoVector.push_back(egcandidateNonIso);
	
	
      }
    }
    
    
    // postfiring non isolated +1
    if (treeVars.nbOfL1preNonisoCandsp1>0) {
      for (UInt_t iNL1preIsop1 = 0; iNL1preIsop1 < treeVars.nbOfL1preNonisoCandsp1; iNL1preIsop1++) {
	if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsop1
		 <<" eta = "<<treeVars.L1preNonisoIetap1[iNL1preIsop1]
		 <<" phi = "<<treeVars.L1preNonisoIphip1[iNL1preIsop1]
		 <<" energy = "<<treeVars.L1preNonisoEnergyp1[iNL1preIsop1]
		 <<std::endl;
	ieta_vs_idx_L1NonIso->Fill(4, treeVars.L1preNonisoIetap1[iNL1preIsop1]);
	ieta_vs_idx_L1NonIso_binFix->Fill(4, (63./28.)*treeVars.L1preNonisoIetap1[iNL1preIsop1]);
	
	egcandidateNonIso.iso = false;
	egcandidateNonIso.eta = treeVars.L1preNonisoIetap1[iNL1preIsop1];
	egcandidateNonIso.phi = treeVars.L1preNonisoIphip1[iNL1preIsop1];
	egcandidateNonIso.idx = 1;
	egcandidateNonIso.energy = treeVars.L1preNonisoEnergyp1[iNL1preIsop1];
	egcandidateNonIso.pt = treeVars.L1preNonisoPtp1[iNL1preIsop1];
	egcandidateNonIsoVector.push_back(egcandidateNonIso);
	
	
      }
    }
    
    
    // postfiring non isolated +2
    if (treeVars.nbOfL1preNonisoCandsp2>0) {
      for (UInt_t iNL1preIsop2 = 0; iNL1preIsop2 < treeVars.nbOfL1preNonisoCandsp2; iNL1preIsop2++) {
	if(debug__) std::cout<<" Isolated pre EGamma cadidates number "<<iNL1preIsop2
		 <<" eta = "<<treeVars.L1preNonisoIetap2[iNL1preIsop2]
		 <<" phi = "<<treeVars.L1preNonisoIphip2[iNL1preIsop2]
		 <<" energy = "<<treeVars.L1preNonisoEnergyp2[iNL1preIsop2]
		 <<std::endl;
	ieta_vs_idx_L1NonIso->Fill(5, treeVars.L1preNonisoIetap2[iNL1preIsop2]);
	ieta_vs_idx_L1NonIso_binFix->Fill(5, (63./28.)*treeVars.L1preNonisoIetap2[iNL1preIsop2]);
	
	egcandidateNonIso.iso = false;
	egcandidateNonIso.eta = treeVars.L1preNonisoIetap2[iNL1preIsop2];
	egcandidateNonIso.phi = treeVars.L1preNonisoIphip2[iNL1preIsop2];
	egcandidateNonIso.idx = 2;
	egcandidateNonIso.energy = treeVars.L1preNonisoEnergyp2[iNL1preIsop2];
	egcandidateNonIso.pt = treeVars.L1preNonisoPtp2[iNL1preIsop2];
	egcandidateNonIsoVector.push_back(egcandidateNonIso);
	
      }
    }
    
    
    
    // once we have filled both iso and non iso vectors we can see what is inside
    //EGVariablesShow(egcandidateIsoVector);
    //EGVariablesShow(egcandidateNonIsoVector);
    
    
    // ---------------------- ---------------------- ---------------------- ---------------------- ---------------------- ----------------------
    // calculate the DR between eg candidates and TT 
    // in first iteration we match using delta ieta <= 5 && delta iphi <= 5 
    // this has to be tuned. 
    // ---------------------- ---------------------- ---------------------- ---------------------- ---------------------- ----------------------

    if(debug__) cout << entry << " / " << treeentries << " events processed" << endl;
    if(debug__) std::cout<<" sizecondition = "<<(egcandidateIsoVector.size() > 0  && maxTowerVector.size() > 0  )<<" "<<(egcandidateIsoVector.size() > 0) <<" "<<(maxTowerVector.size() > 0 )<<std::endl;
    if (egcandidateIsoVector.size() > 0  && maxTowerVector.size() > 0  ){
      
      int MinDeltaEtaIso    = CalculateDeltaIEta(egcandidateIsoVector, maxTowerVector);
      int MinDeltaPhiIso    = CalculateDeltaIPhi(egcandidateIsoVector, maxTowerVector);
      
      detaIso_->Fill(MinDeltaEtaIso);
      dphiIso_->Fill(MinDeltaPhiIso);
      deta_dphi_Iso_->Fill(MinDeltaEtaIso,MinDeltaPhiIso);
      
      
      // finding the min DR for each egamma candidate, so that one tower corresponding to the eg cadidate enter the histogram, earlier, we used only the best matched candidate.       
      for (int ieg=0; ieg<(int) egcandidateIsoVector.size(); ieg++){
	if (  ( int ( (28./63.) * abs(egcandidateIsoVector[ieg].eta) ) ) > 17 ){
	  
	  std::vector<MatchedTowers> dEIso_ = CalculateDE(egcandidateIsoVector[ieg], maxTowerVector, ieg);
	  std::sort(dEIso_.begin(), dEIso_.end(), mysort() );
	  for (int it=0; it < (int) dEIso_.size(); it++){
	    if (debug__) std::cout<<" matched towers has properties = "<<ieg
		     <<"  "<<dEIso_[it].de
		     <<"  "<<dEIso_[it].itower
		     <<"  "<<dEIso_[it].iegcand
		     <<"  "<<dEIso_[it].dr
		     <<"  "<<dEIso_[it].pttower
		     <<"  "<<dEIso_[it].ptcand
		     <<"  "<<dEIso_[it].etatower
		     <<"  "<<dEIso_[it].etacand
		     <<std::endl;
	    
	  }
	  
	  if (dEIso_.size()>0){
	    DEbyE_c_vs_DR_Iso_->Fill( (dEIso_[0].pttower/dEIso_[0].ptcand), dEIso_[0].dr);
	    egidx_ttidx_Iso_de_->Fill(dEIso_[0].egbx, dEIso_[0].towerbx-2);
	  }
	  
	}
      } // end of eg for loop     
      
      std::vector<int> dirIso_ = CalculateDeltaIR(egcandidateIsoVector, maxTowerVector);
      if (dirIso_[0] >= 0) {
	// perform this calculation for EE only (for now) 
	if (  ( int ( (28./63.) * abs(egcandidateIsoVector[dirIso_[0]].eta) ) ) > 17 ){
	  if (debug__) std::cout<<" isolated eta works"<<( int ( (28./63.) * abs(egcandidateIsoVector[dirIso_[0]].eta) )) << std::endl;
	  
	  // fill the delta R 
	  drMin_Iso_->Fill(dirIso_[2]);
	  
	  // fill the eg index vs trigger tower index, ideally they should be same
	  egidx_ttidx_Iso_->Fill(dirIso_[3], dirIso_[4]-2);
	  
	  // index scatter plot for endcap made in 3 bins 
	  if (abs(maxTowerVector[dirIso_[1]].eta) > 17 && abs(maxTowerVector[dirIso_[1]].eta) < 27)  egidx_ttidx_Iso_bin_[0]->Fill(dirIso_[3], dirIso_[4]-2);
	  if (abs(maxTowerVector[dirIso_[1]].eta) == 27)  egidx_ttidx_Iso_bin_[1]->Fill(dirIso_[3], dirIso_[4]-2);
	  if (abs(maxTowerVector[dirIso_[1]].eta) == 28)  egidx_ttidx_Iso_bin_[2]->Fill(dirIso_[3], dirIso_[4]-2);
	  if (abs(maxTowerVector[dirIso_[1]].eta) == 27 or abs(maxTowerVector[dirIso_[1]].eta) == 28)  egidx_ttidx_Iso_bin_[3]->Fill(dirIso_[3], dirIso_[4]-2);
	  if (abs(maxTowerVector[dirIso_[1]].eta) == 27 or abs(maxTowerVector[dirIso_[1]].eta) == 28 or abs(maxTowerVector[dirIso_[1]].eta) == 26 )  egidx_ttidx_Iso_bin_[4]->Fill(dirIso_[3], dirIso_[4]-2);
	  
	  
	  //for (int ii =0; ii< (int) dirIso_.size(); ii++)  std::cout<<" dirIso_ = "<<dirIso_[ii]<<std::endl;
	  
	  if (debug__) std::cout<<" E tower, E eg, DR, eg size, tower size ====== "<<maxTowerVector[dirIso_[1]].energy <<"  "<< egcandidateIsoVector[dirIso_[0]].energy << "   "<< dirIso_[2] << "   "   <<egcandidateIsoVector.size()<< "  "<<maxTowerVector.size()<<" phi egamma = "<<egcandidateIsoVector[dirIso_[0]].phi<< std::endl;
	  
	  // save DR vs DE to check if the DR matched are also matched in energy
	  if (maxTowerVector[dirIso_[1]].energy > 0 && egcandidateIsoVector[dirIso_[0]].energy > 0 ){
	    DE_vs_DR_Iso_->Fill( -((maxTowerVector[dirIso_[1]].energy/2.0) -  egcandidateIsoVector[dirIso_[0]].pt), int(sqrt(dirIso_[2])) );
	    DEbyE_vs_DR_Iso_->Fill( (maxTowerVector[dirIso_[1]].energy/2.0) / egcandidateIsoVector[dirIso_[0]].pt, int(sqrt(dirIso_[2])) );
	    Etower_vs_Ecandidate_Iso_->Fill(maxTowerVector[dirIso_[1]].energy/2.0, egcandidateIsoVector[dirIso_[0]].pt, int(sqrt(dirIso_[2]))  ); 
	    
	  }
	  
	  // fill the histopgrams for DR matched objects
	  if (dirIso_[2] < 7) {
	    egidx_ttidx_Iso_dr_->Fill(dirIso_[3], dirIso_[4]-2);
	    ttidx_Iso_dr_->Fill(dirIso_[4]-2);
	    //for (int ii=0; ii<3; ii++){
	    //if()
	    //	egidx_ttidx_Iso_dr_eta_egamma_[i]->Fill(dirIso_[3], dirIso_[4]-2);
	    //}
	    if (abs(maxTowerVector[dirIso_[1]].eta) > 17 && abs(maxTowerVector[dirIso_[1]].eta) < 27)  egidx_ttidx_Iso_dr_bin_[0]->Fill(dirIso_[3], dirIso_[4]-2);
	    if (abs(maxTowerVector[dirIso_[1]].eta) == 27)  egidx_ttidx_Iso_dr_bin_[1]->Fill(dirIso_[3], dirIso_[4]-2);
	    if (abs(maxTowerVector[dirIso_[1]].eta) == 28)  egidx_ttidx_Iso_dr_bin_[2]->Fill(dirIso_[3], dirIso_[4]-2);
	    if (abs(maxTowerVector[dirIso_[1]].eta) == 27 or abs(maxTowerVector[dirIso_[1]].eta) == 28)  egidx_ttidx_Iso_dr_bin_[3]->Fill(dirIso_[3], dirIso_[4]-2);
	    if (abs(maxTowerVector[dirIso_[1]].eta) == 27 or abs(maxTowerVector[dirIso_[1]].eta) == 28 or abs(maxTowerVector[dirIso_[1]].eta) == 26 )  egidx_ttidx_Iso_dr_bin_[4]->Fill(dirIso_[3], dirIso_[4]-2);
	  }
	}
      }// end of if (dirIso_[0] >= 0) {
    }
    
    // similar kind of plots for the non isolated objects
    if (egcandidateNonIsoVector.size() > 0  && maxTowerVector.size() > 0  ){

      int MinDeltaEtaNonIso = CalculateDeltaIEta(egcandidateNonIsoVector, maxTowerVector);
      int MinDeltaPhiNonIso = CalculateDeltaIPhi(egcandidateNonIsoVector, maxTowerVector);
      
      detaNonIso_->Fill(MinDeltaEtaNonIso);
      dphiNonIso_->Fill(MinDeltaPhiNonIso);
      deta_dphi_NonIso_->Fill(MinDeltaEtaNonIso,MinDeltaPhiNonIso);
    
    

      std::vector<int> dirNonIso_ = CalculateDeltaIR(egcandidateNonIsoVector, maxTowerVector); 
      
      if (dirNonIso_[0] >= 0){
	//std::cout<<" non iso eta = "<<abs(egcandidateNonIsoVector[dirNonIso_[0]].eta)<<"  "<<(int(28./63.*abs(egcandidateNonIsoVector[dirNonIso_[0]].eta))) <<std::endl;
	if ( ( int ( (28./63.) * abs(egcandidateNonIsoVector[dirNonIso_[0]].eta) ) ) > 17 ){
	  
	  drMin_NonIso_->Fill(dirNonIso_[2]);
	  egidx_ttidx_NonIso_->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	  
	  //std::cout<<"inside non isolated cands "<<std::endl;
	  
	  if (abs(maxTowerVector[dirNonIso_[1]].eta) > 17 && abs(maxTowerVector[dirNonIso_[1]].eta) < 27)  egidx_ttidx_NonIso_bin_[0]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	  if (abs(maxTowerVector[dirNonIso_[1]].eta) == 27)  egidx_ttidx_NonIso_bin_[1]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	  if (abs(maxTowerVector[dirNonIso_[1]].eta) == 28)  egidx_ttidx_NonIso_bin_[2]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	  if (abs(maxTowerVector[dirNonIso_[1]].eta) == 27 or abs(maxTowerVector[dirNonIso_[1]].eta) == 28)  egidx_ttidx_NonIso_bin_[3]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	  if (abs(maxTowerVector[dirNonIso_[1]].eta) == 27 or abs(maxTowerVector[dirNonIso_[1]].eta) == 28 or abs(maxTowerVector[dirNonIso_[1]].eta) == 26)  egidx_ttidx_NonIso_bin_[4]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	  
	  if (dirNonIso_[2] < 7) {
	    
	    egidx_ttidx_NonIso_dr_->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	    ttidx_NonIso_dr_->Fill(dirNonIso_[4]-2);

	    if (abs(maxTowerVector[dirNonIso_[1]].eta) > 17 && abs(maxTowerVector[dirNonIso_[1]].eta) < 27)  egidx_ttidx_NonIso_dr_bin_[0]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	    if (abs(maxTowerVector[dirNonIso_[1]].eta) == 27)  egidx_ttidx_NonIso_dr_bin_[1]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	    if (abs(maxTowerVector[dirNonIso_[1]].eta) == 28)  egidx_ttidx_NonIso_dr_bin_[2]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	    if (abs(maxTowerVector[dirNonIso_[1]].eta) == 27 or abs(maxTowerVector[dirNonIso_[1]].eta) == 28)  egidx_ttidx_NonIso_dr_bin_[3]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	    if (abs(maxTowerVector[dirNonIso_[1]].eta) == 27 or abs(maxTowerVector[dirNonIso_[1]].eta) == 28 or abs(maxTowerVector[dirNonIso_[1]].eta) == 26 )  egidx_ttidx_NonIso_dr_bin_[4]->Fill(dirNonIso_[3], dirNonIso_[4]-2);
	  }
	
	}
      }
      
    }
    
    //std::cout<< " \n \n ";
    
  }//for (int entry = 0 ; entry < treeentries ; ++entry) {
  
  TString outputfilename;
  TString cutval;
  cutval.Form("%d",threshold);
  TString datastr="data";
  if (!isdata)  TString datastr="mc";
  if (is2017 && isdata) outputfilename  = "PrefiringRateEE_2017"+datastr+"_FrontTrain_"+dataset+"_cutval_"+cutval+".root";
  if (!is2017 && isdata) outputfilename = "PrefiringRateEE_2018data_FrontTrain_"+dataset+"_cutval_"+cutval+".root";
  if (!isdata) outputfilename = "PrefiringRateEE_"+datastr+"_FrontTrain_"+dataset+timeshiftoutput+"cutval_"+cutval+".root";
  
  
  gSystem->Exec("mkdir -p "+outputdir);
  
  outputfilename = outputdir + outputfilename; 
  TFile fout(outputfilename,"RECREATE");
  fout.cd();
  
  //   -- Writing the gen level and Pseudo L1T candidate information 
  h_PL1T_nTowers_->Write();
  h_PL1T_Energy0_->Write();
  h_PL1T_Energy1_->Write();
  h_PL1T_Energy2_->Write();
  h_PL1T_Energy3_->Write();
  h_PL1T_Energy4_->Write();
  h_PL1T_maxIndex_->Write();

  

  ieta_vs_iphi_TP->Write();
  ieta_vs_iphi_ETP->Write();
  
  ieta_vs_idx_L1Iso->Write();
  ieta_vs_idx_L1NonIso->Write();

  ieta_vs_idx_L1Iso_binFix->Write();
  ieta_vs_idx_L1NonIso_binFix->Write();
  
  ieta_vs_iphi_TP_ETP->Write();
  ieta_vs_iphi_TP_ETP_INTIME->Write();
  ieta_vs_iphi_TP_ETP_OUTTIME->Write();
  
  ieta_vs_iphi_TP0->Write();
  ieta_vs_iphi_TP0_ETP->Write();
  
  
  ieta_vs_idx_TP_ETP->Write();
  ieta_vs_idx_TP0->Write();
  ieta_vs_idx_TP0_ETP->Write();

  ieta_vs_iphi_TP16->Write();
  ieta_vs_iphi_ETP16_IDX2->Write();
  ieta_vs_iphi_ETP16_IDXAny->Write();
  maxOfTPEmul_->Write();
  
  idx_vs_ieta_TP16->Write();
  idx_vs_ieta_ETP16_IDX2->Write();
  idx_vs_ieta_ETP16_IDXAny->Write();
  

  idx_TP0->Write();
  idx_TP0_ETP->Write();

  detaIso_->Write();
  dphiIso_->Write();
  detaNonIso_->Write();
  dphiNonIso_->Write();
  

  deta_dphi_Iso_->Write();
  deta_dphi_NonIso_->Write();
  
  egidx_ttidx_Iso_->Write();
  egidx_ttidx_NonIso_->Write();
  
  pseudo_egidx_ttidx_NonIso_->Write();
  
  egidx_ttidx_Iso_dr_->Write();
  egidx_ttidx_Iso_de_->Write();
  
  ttidx_Iso_dr_->Write();
  ttidx_NonIso_dr_->Write();
  
  egidx_ttidx_NonIso_dr_->Write();

  drMin_Iso_->Write();
  drMin_NonIso_->Write();
  
  DE_vs_DR_Iso_->Write();
  DEbyE_vs_DR_Iso_->Write();
  DEbyE_c_vs_DR_Iso_->Write();
  Etower_vs_Ecandidate_Iso_->Write();
  
  egidx_ttidx_Iso_bin_[0]->Write();
  egidx_ttidx_Iso_bin_[1]->Write();
  egidx_ttidx_Iso_bin_[2]->Write();
  egidx_ttidx_Iso_bin_[3]->Write();
  egidx_ttidx_Iso_bin_[4]->Write();

  egidx_ttidx_NonIso_bin_[0]->Write();
  egidx_ttidx_NonIso_bin_[1]->Write();
  egidx_ttidx_NonIso_bin_[2]->Write();
  egidx_ttidx_NonIso_bin_[3]->Write();
  egidx_ttidx_NonIso_bin_[4]->Write();

  egidx_ttidx_Iso_dr_bin_[0]->Write();
  egidx_ttidx_Iso_dr_bin_[1]->Write();
  egidx_ttidx_Iso_dr_bin_[2]->Write();
  egidx_ttidx_Iso_dr_bin_[3]->Write();
  egidx_ttidx_Iso_dr_bin_[4]->Write();

  egidx_ttidx_NonIso_dr_bin_[0]->Write();
  egidx_ttidx_NonIso_dr_bin_[1]->Write();
  egidx_ttidx_NonIso_dr_bin_[2]->Write();
  egidx_ttidx_NonIso_dr_bin_[3]->Write();
  egidx_ttidx_NonIso_dr_bin_[4]->Write();
  

  for (int i=0; i<11; i++){
    TString postname;
    postname.Form("%d",i+18);
    std::cout<<" postname = "<<postname<<std::endl;
    idx_TP0_vec[i]->Write();
    idx_TP0_ETP_vec[i]->Write();
    
  }



  //ieta_vs_idx_TP0->Write();
  //ieta_vs_idx_TP0_ETP->Write();
  
  // after writing the histograms, perform operations on them to extract fraction etc. 
  
  TH2F* frac_ieta_vs_iphi_TP_ETP_INTIME = ((TH2F*) fout.Get("ieta_vs_iphi_TP_ETP_INTIME"));
  frac_ieta_vs_iphi_TP_ETP_INTIME->SetName("frac_ieta_vs_iphi_TP_ETP_INTIME");//new TH2F("ieta_vs_iphi_TP_ETP_INTIME","ieta_vs_iphi_TP_ETP_INTIME",57,-28.5,28.5,72,0.5,72.5);
  frac_ieta_vs_iphi_TP_ETP_INTIME->Divide(ieta_vs_iphi_TP_ETP);
  frac_ieta_vs_iphi_TP_ETP_INTIME->Write();

  
  TH2F* frac_ieta_vs_iphi_TP_ETP_OUTTIME = (TH2F*) fout.Get("ieta_vs_iphi_TP_ETP_OUTTIME");
  frac_ieta_vs_iphi_TP_ETP_OUTTIME->SetName("frac_ieta_vs_iphi_TP_ETP_OUTTIME");
  frac_ieta_vs_iphi_TP_ETP_OUTTIME->Divide(ieta_vs_iphi_TP_ETP);
  frac_ieta_vs_iphi_TP_ETP_OUTTIME->Write();
  

  TH2F* frac_ieta_vs_iphi_TP0_ETP = (TH2F*) fout.Get("ieta_vs_iphi_TP0_ETP");
  frac_ieta_vs_iphi_TP0_ETP->SetName("frac_ieta_vs_iphi_TP0_ETP");
  frac_ieta_vs_iphi_TP0_ETP->Divide(ieta_vs_iphi_TP0);
  frac_ieta_vs_iphi_TP0_ETP->Write();
  

  TH1F* frac_idx_TP0_ETP = (TH1F*) fout.Get("idx_TP0_ETP");
  frac_idx_TP0_ETP->SetName("frac_idx_TP0_ETP");
  frac_idx_TP0_ETP->Divide(idx_TP0);
  frac_idx_TP0_ETP->Write();


  ieta_TP_ETP_INTIME->Write()  ;
  ieta_TP_ETP_OUTTIME->Write() ;
  ieta_TP0_ETP->Write()        ;
  ieta_TP_ETP->Write()         ;
  ieta_TP0->Write()            ;

  TH1F* frac_ieta_TP_ETP_INTIME = (TH1F*) fout.Get("ieta_TP_ETP_INTIME");
  frac_ieta_TP_ETP_INTIME->SetName("frac_ieta_TP_ETP_INTIME");
  frac_ieta_TP_ETP_INTIME->Divide(ieta_TP_ETP);
  frac_ieta_TP_ETP_INTIME->Write();


  TH1F* frac_ieta_TP_ETP_OUTTIME = (TH1F*) fout.Get("ieta_TP_ETP_OUTTIME");
  frac_ieta_TP_ETP_OUTTIME->SetName("frac_ieta_TP_ETP_OUTTIME");
  frac_ieta_TP_ETP_OUTTIME->Divide(ieta_TP_ETP);
  frac_ieta_TP_ETP_OUTTIME->Write();


  TH1F* frac_ieta_TP0_ETP = (TH1F*) fout.Get("ieta_TP0_ETP");
  frac_ieta_TP0_ETP->SetName("frac_ieta_TP0_ETP");
  frac_ieta_TP0_ETP->Divide(ieta_TP0);
  frac_ieta_TP0_ETP->Write();


  TH2F* frac_ieta_vs_iphi_TP16_DIV_ETP16_IDXAny = (TH2F*) fout.Get("ieta_vs_iphi_TP16");
  frac_ieta_vs_iphi_TP16_DIV_ETP16_IDXAny->SetName("frac_ieta_vs_iphi_TP16_DIV_ETP16_IDXAny");
  frac_ieta_vs_iphi_TP16_DIV_ETP16_IDXAny->Divide(ieta_vs_iphi_ETP16_IDXAny);
  frac_ieta_vs_iphi_TP16_DIV_ETP16_IDXAny->Write();

  TH2F* frac_ieta_vs_iphi_TP16_DIV_ETP16_IDX2 = (TH2F*) fout.Get("ieta_vs_iphi_TP16");
  frac_ieta_vs_iphi_TP16_DIV_ETP16_IDX2->SetName("frac_ieta_vs_iphi_TP16_DIV_ETP16_IDX2");
  frac_ieta_vs_iphi_TP16_DIV_ETP16_IDX2->Divide(ieta_vs_iphi_ETP16_IDX2);
  frac_ieta_vs_iphi_TP16_DIV_ETP16_IDX2->Write();


  TH2F* frac_idx_vs_ieta_TP16_DIV_ETP16_IDXAny = (TH2F*) fout.Get("idx_vs_ieta_TP16");
  frac_idx_vs_ieta_TP16_DIV_ETP16_IDXAny->SetName("frac_idx_vs_ieta_TP16_DIV_ETP16_IDXAny");
  frac_idx_vs_ieta_TP16_DIV_ETP16_IDXAny->Divide(idx_vs_ieta_ETP16_IDXAny);
  frac_idx_vs_ieta_TP16_DIV_ETP16_IDXAny->Write();
  
  TH2F* frac_idx_vs_ieta_TP16_DIV_ETP16_IDX2 = (TH2F*) fout.Get("idx_vs_ieta_TP16");
  frac_idx_vs_ieta_TP16_DIV_ETP16_IDX2->SetName("frac_idx_vs_ieta_TP16_DIV_ETP16_IDX2");
  frac_idx_vs_ieta_TP16_DIV_ETP16_IDX2->Divide(idx_vs_ieta_ETP16_IDX2);
  frac_idx_vs_ieta_TP16_DIV_ETP16_IDX2->Write();
  
  
  TH2F* frac_ieta_vs_idx_TP0_ETP_DIV_TP0 = (TH2F*) fout.Get("ieta_vs_idx_TP0_ETP");
  frac_ieta_vs_idx_TP0_ETP_DIV_TP0->SetName("frac_ieta_vs_idx_TP0_ETP_DIV_TP0");
  frac_ieta_vs_idx_TP0_ETP_DIV_TP0->Divide(ieta_vs_idx_TP0);
  frac_ieta_vs_idx_TP0_ETP_DIV_TP0->Write();
  
  
  fout.Close();

  double final_t = time(&timer);
  
  double seconds = -difftime(initial_t,final_t);
  std::cout<<" time used to run the macro (in seconds):" << seconds<<std::endl; 
  
  
}

