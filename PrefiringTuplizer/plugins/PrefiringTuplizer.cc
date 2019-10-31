// -*- C++ -*-v_
//
// Package:    L1Prefiring/PrefiringTuplizer
// Class:      PrefiringTuplizer
//
/**\class PrefiringTuplizer PrefiringTuplizer.cc L1Prefiring/PrefiringTuplizer/plugins/PrefiringTuplizer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Raman Khurana
//         Created:  Wed, 24 Apr 2019 08:53:01 GMT
//
//


// This has skimmed information about TPs needed for prefiring study and also the L1 Trigger DQM plots in order to validate the code. 
// L1T code works fine. 
// TPs work fine. 
// 


// system include files
#include <memory>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>
#include <string>
#include <TH2F.h> 
#include <TTree.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


#include "DataFormats/EcalDigi/interface/EcalTriggerPrimitiveDigi.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "DataFormats/EcalDigi/interface/EcalTriggerPrimitiveDigi.h"
#include "DataFormats/EcalRecHit/interface/EcalUncalibratedRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgoRcd.h"

#include "DataFormats/DetId/interface/DetId.h"

#include "Geometry/CaloTopology/interface/EcalTrigTowerConstituentsMap.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "Geometry/EcalMapping/interface/EcalElectronicsMapping.h"
#include "Geometry/EcalMapping/interface/EcalMappingRcd.h"


#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/EtSum.h"
#include "DataFormats/L1Trigger/interface/Tau.h"

#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "L1Trigger/L1TGlobal/interface/L1TGlobalUtil.h"


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "Geometry/CaloTopology/interface/EcalTrigTowerConstituentsMap.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"

class towerEner {
public:
  float eRec_ ;
  int crystNb_ ;
  int tpgEmul_[5] ;
  int tpgEmulFlag_[5] ;
  int tpgEmulsFGVB_[5] ;
  int tpgADC_;
  int iphi_, ieta_, nbXtal_, spike_ ;
  int twrADC, sFGVB, sevlv_, ttFlag_;
  int TCCid_, TowerInTCC_, strip_;
  towerEner()
    : eRec_(0),  crystNb_(0), tpgADC_(0),
      iphi_(-999), ieta_(-999), nbXtal_(0), spike_(0), twrADC(0), sFGVB(-999), sevlv_(0) , ttFlag_(0), TCCid_(0), TowerInTCC_(0), strip_(0)
  {
    for (int i=0 ; i<5 ; i ++) {
      tpgEmul_[i] = 0 ;
      tpgEmulFlag_[i]=0;
      tpgEmulsFGVB_[i]=0;
    }
  }
};

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.



class PrefiringTuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {


public:
  explicit PrefiringTuplizer(const edm::ParameterSet&);
  
  ~PrefiringTuplizer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  void beginRun(edm::Run const& iEvent, edm::EventSetup const&);

  //virtual void beginRun(const edm::Run&, const edm::EventSetup&) override;
  
  edm::EDGetTokenT<GlobalAlgBlkBxCollection> l1tStage2uGtProducer_; // input tag for L1 uGT DAQ readout record
  edm::EDGetTokenT<l1t::EGammaBxCollection> stage2CaloLayer2EGammaToken_;
  
  
  edm::EDGetTokenT<EcalTrigPrimDigiCollection> tpEmulatorCollection_ ;

  
  edm::EDGetTokenT<EcalTrigPrimDigiCollection> tpCollection_ ;
  
  edm::EDGetTokenT<EBDigiCollection> EBdigistoken_ ;
  edm::EDGetTokenT<EEDigiCollection> EEdigistoken_ ;
  
  
  std::string monitorDir_;
  
  // To get the algo bits corresponding to algo names
  std::shared_ptr<l1t::L1TGlobalUtil> gtUtil_;
  std::vector<double> egammaPtCuts_;


  
  // not all of the following are needed, clean later on 
  // For the timing histograms
  int algoBitFirstBxInTrain_;
  int algoBitLastBxInTrain_;
  int algoBitIsoBx_;
  const std::string algoNameFirstBxInTrain_;
  const std::string algoNameLastBxInTrain_;
  const std::string algoNameIsoBx_;
  //const unsigned int bxrange_; //this is the out bx range

  unsigned int useAlgoDecision_;
  edm::Service<TFileService> fs;

  // variables for branches 
  uint runNb ;
  ULong64_t evtNb ;
  uint bxNb ;
  //uint bxGT ;
  ULong64_t orbitNb ;
  uint lumiBlock ;
  double timeStamp ;
  
  uint nbOfActiveTriggers ;
  int activeTriggers[160] ;
  int activeTriggersBX[160] ;  // all triggers from gt even disabled                                                                                                                                      

  uint nbOfActiveTechTriggers ;
  int activeTechTriggers[64] ;
  
  // variables for pulse shape
  uint ndataframe;
  uint nADC;
  int index_df[14032];
  int index_ts[14032];
  int count_ADC[14032];
  
  
  
  uint nbOfTowers ; //max 4032 EB+EE                                                                                                                                                                      
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
  int crystNb[4032];
  int sevlv[4032];
  int spike[4032] ;
  int twrADC[4032];
  int sFGVB[4032];

  int ttFlag[4032];
  int TCCid[4032];
  int TowerInTCC[4032] ;
  int strip[4032];

  Int_t v_nonisocounterm2     ;
  Int_t v_nonisocounterm1     ;
  Int_t v_nonisocounterzero   ;
  Int_t v_nonisocounterp1     ;
  Int_t v_nonisocounterp2     ;

  Int_t v_isocounterm2     ;
  Int_t v_isocounterm1     ;
  Int_t v_isocounterzero   ;
  Int_t v_isocounterp1     ;
  Int_t v_isocounterp2     ;


  Int_t L1preIsoIetam2[10];
  Int_t L1preIsoIetam1[10];
  Int_t L1preIsoIetazero[10];
  Int_t L1preIsoIetap1[10];
  Int_t L1preIsoIetap2[10];

  Int_t L1preNonisoIetam2[10];
  Int_t L1preNonisoIetam1[10];
  Int_t L1preNonisoIetazero[10];
  Int_t L1preNonisoIetap1[10];
  Int_t L1preNonisoIetap2[10];

  Int_t L1preIsoIphim2[10];
  Int_t L1preIsoIphim1[10];
  Int_t L1preIsoIphizero[10];
  Int_t L1preIsoIphip1[10];
  Int_t L1preIsoIphip2[10];

  Int_t L1preNonisoIphim2[10];
  Int_t L1preNonisoIphim1[10];
  Int_t L1preNonisoIphizero[10];
  Int_t L1preNonisoIphip1[10];
  Int_t L1preNonisoIphip2[10];

  Int_t L1preIsoEnergym2[10];
  Int_t L1preIsoEnergym1[10];
  Int_t L1preIsoEnergyzero[10];
  Int_t L1preIsoEnergyp1[10];
  Int_t L1preIsoEnergyp2[10];

  Int_t L1preNonisoEnergym2[10];
  Int_t L1preNonisoEnergym1[10];
  Int_t L1preNonisoEnergyzero[10];
  Int_t L1preNonisoEnergyp1[10];
  Int_t L1preNonisoEnergyp2[10];

  // Define histograms 
  TH2F* ibx_vs_ieta_Iso;
  TH2F* ibx_vs_ieta_NonIso;
  TTree *prefiringTree;

  
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
PrefiringTuplizer::PrefiringTuplizer(const edm::ParameterSet& ps)
  :
  l1tStage2uGtProducer_(consumes<GlobalAlgBlkBxCollection>(ps.getParameter<edm::InputTag>("ugtProducer"))),
  gtUtil_(new l1t::L1TGlobalUtil(ps, consumesCollector(), *this, ps.getParameter<edm::InputTag>("ugtProducer"), ps.getParameter<edm::InputTag>("ugtProducer"))),
  algoNameFirstBxInTrain_(ps.getUntrackedParameter<std::string>("firstBXInTrainAlgo","")),
  algoNameLastBxInTrain_(ps.getUntrackedParameter<std::string>("lastBXInTrainAlgo","")),
  algoNameIsoBx_(ps.getUntrackedParameter<std::string>("isoBXAlgo","")),
  algoBitFirstBxInTrain_(-1),
  algoBitLastBxInTrain_(-1),
  algoBitIsoBx_(-1),
  stage2CaloLayer2EGammaToken_(consumes<l1t::EGammaBxCollection>(ps.getParameter<edm::InputTag>("stage2CaloLayer2EGammaProducer"))),
  tpEmulatorCollection_(consumes<EcalTrigPrimDigiCollection>(ps.getParameter<edm::InputTag>("TPEmulatorCollection"))),
  tpCollection_(consumes<EcalTrigPrimDigiCollection>(ps.getParameter<edm::InputTag>("TPCollection"))),
  EBdigistoken_(consumes<EBDigiCollection>(ps.getParameter<edm::InputTag>("EBdigis") )  ),
  EEdigistoken_(consumes<EEDigiCollection>(ps.getParameter<edm::InputTag>("EEdigis") )  )


{
  

      

  useAlgoDecision_ = 0;
  /*
  if (ps.getUntrackedParameter<std::string>("useAlgoDecision").find("final") == 0) {
    useAlgoDecision_ = 2;
  } else if (ps.getUntrackedParameter<std::string>("useAlgoDecision").find("intermediate") == 0) {
    useAlgoDecision_ = 1;
  } else {
    useAlgoDecision_ = 0;
  }
  */
  egammaPtCuts_.clear();
  egammaPtCuts_.push_back(10.0);
  //egammaPtCuts_.push_back(20.0);
  //egammaPtCuts_.push_back(30.0);

  
  //ibx_vs_ieta_Iso = new TH2F("ibx_vs_ieta_Iso","ibx_vs_ieta_Iso", 5, -2.5, 2.5, 70, -70, 70);
  //ibx_vs_ieta_NonIso = new TH2F("ibx_vs_ieta_NonIso","ibx_vs_ieta_NonIso", 5, -2.5, 2.5, 70, -70, 70);
  prefiringTree = fs->make<TTree>("prefiringTree","A ROOT tree to save information to understand prefiring");

  ibx_vs_ieta_Iso = fs->make<TH2F>("ibx_vs_ieta_Iso","ibx_vs_ieta_Iso", 5, -2.5, 2.5, 70, -70, 70);
  ibx_vs_ieta_NonIso = fs->make<TH2F>("ibx_vs_ieta_NonIso","ibx_vs_ieta_NonIso", 5, -2.5, 2.5, 70, -70, 70);



    
  /*
    C : a character string terminated by the 0 character
B : an 8 bit signed integer (Char_t)
b : an 8 bit unsigned integer (UChar_t)
S : a 16 bit signed integer (Short_t)
s : a 16 bit unsigned integer (UShort_t)
I : a 32 bit signed integer (Int_t)
i : a 32 bit unsigned integer (UInt_t)
F : a 32 bit floating point (Float_t)
f : a 24 bit floating point with truncated mantissa (Float16_t)
D : a 64 bit floating point (Double_t)
d : a 24 bit truncated floating point (Double32_t)
L : a 64 bit signed integer (Long64_t)
l : a 64 bit unsigned integer (ULong64_t)
O : [the letter o, not a zero] a boolean (Bool_t)
  */
  
  prefiringTree->Branch("b_runNb", &runNb ,"b_runNb/i");
  prefiringTree->Branch("b_evtNb", &evtNb ,"b_evtNb/L");
  prefiringTree->Branch("b_bxNb", &bxNb ,"b_bxNb/i");
  //prefiringTree->Branch("b_bxGT", &bxGT ,"b_bxGT/i");
  prefiringTree->Branch("b_orbitNb", &orbitNb ,"b_orbitNb/L");
  prefiringTree->Branch("b_lumiBlock", &lumiBlock ,"b_lumiBlock/i");
  prefiringTree->Branch("b_timeStamp", &timeStamp ,"b_timeStamp/i");
    
  
  
  // ADC counts for 10 samples when there is some significant energy deposit. 
  prefiringTree->Branch("b_ndataframe", &ndataframe ,"b_ndataframe/i");
  prefiringTree->Branch("b_nADC", &nADC ,"b_nADC/i");
  prefiringTree->Branch("b_index_df", index_df,"b_index_df[b_nADC]/I");
  prefiringTree->Branch("b_index_ts", index_ts,"b_index_ts[b_nADC]/I");
  prefiringTree->Branch("b_count_ADC", count_ADC,"b_count_ADC[b_nADC]/I");
  
  
  prefiringTree->Branch ("b_nbOfTowers",&nbOfTowers, "b_nbOfTowers/i");
  prefiringTree->Branch("b_ieta", ieta ,"b_ieta[b_nbOfTowers]/I");
  prefiringTree->Branch("b_iphi", iphi ,"b_iphi[b_nbOfTowers]/I");
  prefiringTree->Branch("b_nbOfXtals", nbOfXtals ,"b_nbOfXtals[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPData", rawTPData ,"b_rawTPData[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmul1", rawTPEmul1  ,"b_rawTPEmul1[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmul2", rawTPEmul2 ,"b_rawTPEmul2[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmul3", rawTPEmul3 ,"b_rawTPEmul3[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmul4", rawTPEmul4 ,"b_rawTPEmul4[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmul5", rawTPEmul5 ,"b_rawTPEmul5[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulttFlag1", rawTPEmulttFlag1 ,"b_rawTPEmulttFlag1[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulttFlag2", rawTPEmulttFlag2 ,"b_rawTPEmulttFlag2[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulttFlag3", rawTPEmulttFlag3 ,"b_rawTPEmulttFlag3[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulttFlag4", rawTPEmulttFlag4 ,"b_rawTPEmulttFlag4[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulttFlag5", rawTPEmulttFlag5 ,"b_rawTPEmulttFlag5[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulsFGVB1", rawTPEmulsFGVB1 ,"b_rawTPEmulsFGVB1[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulsFGVB2", rawTPEmulsFGVB2 ,"b_rawTPEmulsFGVB2[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulsFGVB3", rawTPEmulsFGVB3 ,"b_rawTPEmulsFGVB3[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulsFGVB4", rawTPEmulsFGVB4 ,"b_rawTPEmulsFGVB4[b_nbOfTowers]/I");
  prefiringTree->Branch("b_rawTPEmulsFGVB5", rawTPEmulsFGVB5 ,"b_rawTPEmulsFGVB5[b_nbOfTowers]/I");
  prefiringTree->Branch("b_eRec", eRec ,"b_eRec[b_nbOfTowers]/I");
  prefiringTree->Branch("b_crystNb", crystNb ,"b_crystNb[b_nbOfTowers]/I");
  prefiringTree->Branch("b_sevlv", sevlv ,"b_sevlv[b_nbOfTowers]/I");
  prefiringTree->Branch("b_spike", spike ,"b_spike[b_nbOfTowers]/I");
  prefiringTree->Branch("b_twrADC", twrADC ,"b_twrADC[b_nbOfTowers]/I");
  prefiringTree->Branch("b_sFGVB", sFGVB ,"b_sFGVB[b_nbOfTowers]/I");
  prefiringTree->Branch("b_ttFlag", ttFlag ,"b_ttFlag[b_nbOfTowers]/I");
  prefiringTree->Branch("b_TCCid", TCCid ,"b_TCCid[b_nbOfTowers]/I");
  prefiringTree->Branch("b_TowerInTCC", TowerInTCC ,"b_TowerInTCC[b_nbOfTowers]/I");
  prefiringTree->Branch("b_strip", strip ,"b_strip[b_nbOfTowers]/I");
  
  
  //counters 
  prefiringTree->Branch("b_nonisocounterm2", &v_nonisocounterm2, "b_nonisocounterm2/I");
  prefiringTree->Branch("b_nonisocounterm1", &v_nonisocounterm1, "b_nonisocounterm1/I");
  prefiringTree->Branch("b_nonisocounterzero", &v_nonisocounterzero, "b_nonisocounterzero/I");
  prefiringTree->Branch("b_nonisocounterp1", &v_nonisocounterp1, "b_nonisocounterp1/I");
  prefiringTree->Branch("b_nonisocounterp2", &v_nonisocounterp2, "b_nonisocounterp2/I");

  prefiringTree->Branch("b_isocounterm2", &v_isocounterm2, "b_isocounterm2/I");
  prefiringTree->Branch("b_isocounterm1", &v_isocounterm1, "b_isocounterm1/I");
  prefiringTree->Branch("b_isocounterzero", &v_isocounterzero, "b_isocounterzero/I");
  prefiringTree->Branch("b_isocounterp1", &v_isocounterp1, "b_isocounterp1/I");
  prefiringTree->Branch("b_isocounterp2", &v_isocounterp2, "b_isocounterp2/I");
  
  // isolated 
  prefiringTree->Branch("b_L1preIsoIetam2", L1preIsoIetam2 , "b_L1preIsoIetam2[b_isocounterm2]/I");
  prefiringTree->Branch("b_L1preIsoIetam1", L1preIsoIetam1 , "b_L1preIsoIetam1[b_isocounterm1]/I");
  prefiringTree->Branch("b_L1preIsoIetazero", L1preIsoIetazero , "b_L1preIsoIetazero[b_isocounterzero]/I");
  prefiringTree->Branch("b_L1preIsoIetap1", L1preIsoIetap1 , "b_L1preIsoIetap1[b_isocounterp1]/I");
  prefiringTree->Branch("b_L1preIsoIetap2", L1preIsoIetap2 , "b_L1preIsoIetap2[b_isocounterp2]/I");


  prefiringTree->Branch("b_L1preIsoIphim2", L1preIsoIphim2 , "b_L1preIsoIphim2[b_isocounterm2]/I");
  prefiringTree->Branch("b_L1preIsoIphim1", L1preIsoIphim1 , "b_L1preIsoIphim1[b_isocounterm1]/I");
  prefiringTree->Branch("b_L1preIsoIphizero", L1preIsoIphizero , "b_L1preIsoIphizero[b_isocounterzero]/I");
  prefiringTree->Branch("b_L1preIsoIphip1", L1preIsoIphip1 , "b_L1preIsoIphip1[b_isocounterp1]/I");
  prefiringTree->Branch("b_L1preIsoIphip2", L1preIsoIphip2 , "b_L1preIsoIphip2[b_isocounterp2]/I");

  prefiringTree->Branch("b_L1preIsoEnergym2", L1preIsoEnergym2 , "b_L1preIsoEnergym2[b_isocounterm2]/I");
  prefiringTree->Branch("b_L1preIsoEnergym1", L1preIsoEnergym1 , "b_L1preIsoEnergym1[b_isocounterm1]/I");
  prefiringTree->Branch("b_L1preIsoEnergyzero", L1preIsoEnergyzero , "b_L1preIsoEnergyzero[b_isocounterzero]/I");
  prefiringTree->Branch("b_L1preIsoEnergyp1", L1preIsoEnergyp1 , "b_L1preIsoEnergyp1[b_isocounterp1]/I");
  prefiringTree->Branch("b_L1preIsoEnergyp2", L1preIsoEnergyp2 , "b_L1preIsoEnergyp2[b_isocounterp2]/I");


  // non isolated 
  prefiringTree->Branch("b_L1preNonisoIetam2", L1preNonisoIetam2 , "b_L1preNonisoIetam2[b_nonisocounterm2]/I");
  prefiringTree->Branch("b_L1preNonisoIetam1", L1preNonisoIetam1 , "b_L1preNonisoIetam1[b_nonisocounterm1]/I");
  prefiringTree->Branch("b_L1preNonisoIetazero", L1preNonisoIetazero , "b_L1preNonisoIetazero[b_nonisocounterzero]/I");
  prefiringTree->Branch("b_L1preNonisoIetap1", L1preNonisoIetap1 , "b_L1preNonisoIetap1[b_nonisocounterp1]/I");
  prefiringTree->Branch("b_L1preNonisoIetap2", L1preNonisoIetap2 , "b_L1preNonisoIetap2[b_nonisocounterp2]/I");

  prefiringTree->Branch("b_L1preNonisoIphim2", L1preNonisoIphim2 , "b_L1preNonisoIphim2[b_nonisocounterm2]/I");
  prefiringTree->Branch("b_L1preNonisoIphim1", L1preNonisoIphim1 , "b_L1preNonisoIphim1[b_nonisocounterm1]/I");
  prefiringTree->Branch("b_L1preNonisoIphizero", L1preNonisoIphizero , "b_L1preNonisoIphizero[b_nonisocounterzero]/I");
  prefiringTree->Branch("b_L1preNonisoIphip1", L1preNonisoIphip1 , "b_L1preNonisoIphip1[b_nonisocounterp1]/I");
  prefiringTree->Branch("b_L1preNonisoIphip2", L1preNonisoIphip2 , "b_L1preNonisoIphip2[b_nonisocounterp2]/I");


  prefiringTree->Branch("b_L1preNonisoEnergym2", L1preNonisoEnergym2 , "b_L1preNonisoEnergym2[b_nonisocounterm2]/I");
  prefiringTree->Branch("b_L1preNonisoEnergym1", L1preNonisoEnergym1 , "b_L1preNonisoEnergym1[b_nonisocounterm2]/I");
  prefiringTree->Branch("b_L1preNonisoEnergyzero", L1preNonisoEnergyzero , "b_L1preNonisoEnergyzero[b_nonisocounterzero]/I");
  prefiringTree->Branch("b_L1preNonisoEnergyp1", L1preNonisoEnergyp1 , "b_L1preNonisoEnergyp1[b_nonisocounterp1]/I");
  prefiringTree->Branch("b_L1preNonisoEnergyp2", L1preNonisoEnergyp2 , "b_L1preNonisoEnergyp2[b_nonisocounterp2]/I");
  
  

  //prefiringTree->Branch("b_",  ,"b_[b_nbOfTowers]/I");
}


PrefiringTuplizer::~PrefiringTuplizer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
PrefiringTuplizer::analyze(const edm::Event& e, const edm::EventSetup& c)
{
   using namespace edm;

   
   for (int i=0; i<4032;i++){
     index_df[i] = -999;
     index_ts[i] = -999;
     count_ADC[i] = -999;
   }

   for (int i=0; i<10; i++){
     L1preIsoIetam2[i] = -999;
     L1preIsoIetam1[i] = -999;
     L1preIsoIetazero[i] = -999;
     L1preIsoIetap1[i] = -999;
     L1preIsoIetap2[i] = -999;
     
     L1preNonisoIetam2[i] = -999;
     L1preNonisoIetam1[i] = -999;
     L1preNonisoIetazero[i] = -999;
     L1preNonisoIetap1[i] = -999;
     L1preNonisoIetap2[i] = -999;
     
     L1preIsoIphim2[i] = -999;
     L1preIsoIphim1[i] = -999;
     L1preIsoIphizero[i] = -999;
     L1preIsoIphip1[i] = -999;
     L1preIsoIphip2[i] = -999;
     
     L1preNonisoIphim2[i] = -999;
     L1preNonisoIphim1[i] = -999;
     L1preNonisoIphizero[i] = -999;
     L1preNonisoIphip1[i] = -999;
     L1preNonisoIphip2[i] = -999;
     
     L1preIsoEnergym2[i] = -999;
     L1preIsoEnergym1[i] = -999;
     L1preIsoEnergyzero[i] = -999;
     L1preIsoEnergyp1[i] = -999;
     L1preIsoEnergyp2[i] = -999;

     L1preNonisoEnergym2[i] = -999;
     L1preNonisoEnergym1[i] = -999;
     L1preNonisoEnergyzero[i] = -999;
     L1preNonisoEnergyp1[i] = -999;
     L1preNonisoEnergyp2[i] = -999;
   }
   v_nonisocounterm2     = 0 ;
   v_nonisocounterm1     = 0 ;
   v_nonisocounterzero   = 0 ;
   v_nonisocounterp1     = 0 ;
   v_nonisocounterp2     = 0 ;
   
   v_isocounterm2     = 0 ;
   v_isocounterm1     = 0 ;
   v_isocounterzero   = 0 ;
   v_isocounterp1     = 0 ;
   v_isocounterp2     = 0 ;

   
   
    // this should be moved to begin run 
   // but where is begin run 
   // begin job does not have the event setup infp 
   // Get the trigger menu information
   gtUtil_->retrieveL1Setup(c);
   
   // Get the algo bits needed for the timing histograms
   if (!gtUtil_->getAlgBitFromName(algoNameFirstBxInTrain_, algoBitFirstBxInTrain_)) {
     edm::LogWarning("L1TObjectsTiming") << "Algo \"" << algoNameFirstBxInTrain_ << "\" not found in the trigger menu " << gtUtil_->gtTriggerMenuName() << ". Could not retrieve algo bit number.";
   }
   
   if (!gtUtil_->getAlgBitFromName(algoNameLastBxInTrain_, algoBitLastBxInTrain_)) {
     edm::LogWarning("L1TObjectsTiming") << "Algo \"" << algoNameLastBxInTrain_ << "\" not found in the trigger menu " << gtUtil_->gtTriggerMenuName() << ". Could not retrieve algo bit number.";
   }
   
   if (!gtUtil_->getAlgBitFromName(algoNameIsoBx_, algoBitIsoBx_)) {
     edm::LogWarning("L1TObjectsTiming") << "Algo \"" << algoNameIsoBx_ << "\" not found in the trigger menu " << gtUtil_->gtTriggerMenuName() << ". Could not retrieve algo bit number.";
   }
   
   // ------------------------------*----------------*-------------**********--------------------------------------------------------------------------------------------
   // ------------------------------*--------------*-*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------**********------***-----------------*------------------------------------------------------------------------------------------------

   
   
   // Open uGT readout record
   edm::Handle<GlobalAlgBlkBxCollection> uGtAlgs;
   e.getByToken(l1tStage2uGtProducer_, uGtAlgs);
   

   
   // EGamma Collection
   edm::Handle<l1t::EGammaBxCollection> EGammaBxCollection;
   e.getByToken(stage2CaloLayer2EGammaToken_, EGammaBxCollection);

   
     
   
   // Find out in which BX the first collision in train, isolated bunch, and last collision in train have fired.
   // In case of pre firing it will be in BX 1 or BX 2 and this will determine the BX shift that
   // will be applied to the timing histogram later.
   int bxShiftFirst = -999;
   int bxShiftIso = -999;
   int bxShiftLast = -999;
   for (int bx = uGtAlgs->getFirstBX(); bx <= uGtAlgs->getLastBX(); ++bx) {
     for (GlobalAlgBlkBxCollection::const_iterator itr = uGtAlgs->begin(bx); itr != uGtAlgs->end(bx); ++itr) {
       // first bunch in train
       if (algoBitFirstBxInTrain_ != -1) {
	 bool bit = false;
	 switch (useAlgoDecision_) {
	 case 0:
	   bit = itr->getAlgoDecisionInitial(algoBitFirstBxInTrain_);
	   break;
	 case 1:
	   bit = itr->getAlgoDecisionInterm(algoBitFirstBxInTrain_);
	   break;
	 case 2:
	   bit = itr->getAlgoDecisionFinal(algoBitFirstBxInTrain_);
	   break;
	 }
	 if (bit) {
	   bxShiftFirst = bx;
	 }
       }
       // last bunch in train
       if(algoBitLastBxInTrain_ != -1) {
	 bool bit = false;
	 switch (useAlgoDecision_) {
	 case 0:
	   bit = itr->getAlgoDecisionInitial(algoBitLastBxInTrain_);
	   break;
	 case 1:
	   bit = itr->getAlgoDecisionInterm(algoBitLastBxInTrain_);
	   break;
	 case 2:
	   bit = itr->getAlgoDecisionFinal(algoBitLastBxInTrain_);
	   break;
	 }
	 if (bit) {
	   bxShiftLast = bx;
	 }
       }
       // isolated bunch
       if (algoBitIsoBx_ != -1) {
	 bool bit = false;
	 switch (useAlgoDecision_) {
	 case 0:
	   bit = itr->getAlgoDecisionInitial(algoBitIsoBx_);
	   break;
	 case 1:
	   bit = itr->getAlgoDecisionInterm(algoBitIsoBx_);
	   break;
	 case 2:
	   bit = itr->getAlgoDecisionFinal(algoBitIsoBx_);
	   break;
	 }
	 if (bit) {
	   bxShiftIso = bx;
	 }
       }
     }
   }
   
   
   
   std::cout<<" bxShiftFirst = " << bxShiftFirst<< " "<<bxShiftIso<< " "<<bxShiftLast<<std::endl;
   
   // the following shifting is needed for following reason: 
   // we want to use only those events which comes as a result of the begining of the bunch train, each bunch train can have crossings multiple times. 
   // if the egamma triggering happended one bx before the begining of bunch train i.e. egamma trigger pre-fired then we need to correct for this effect. 
   // The data is written only once, for all the five bunch crossings. if the egamma trigger was prefired then (-1 bx) then everything needs to be translated. 
   
   
   std::cout<<" just before loop"<<std::endl;
   
   int nonisocounterm2    = 0 ;
   int nonisocounterm1    = 0 ;
   int nonisocounterzero  = 0 ;
   int nonisocounterp1    = 0 ;
   int nonisocounterp2    = 0 ;

   int isocounterm2    = 0 ;
   int isocounterm1    = 0 ;
   int isocounterzero  = 0 ;
   int isocounterp1    = 0 ;
   int isocounterp2    = 0 ;
   
   for (int itBX = std::max(EGammaBxCollection->getFirstBX(), EGammaBxCollection->getFirstBX() + bxShiftFirst); itBX <= std::min(EGammaBxCollection->getLastBX(), EGammaBxCollection->getLastBX() + bxShiftFirst); ++itBX) {
     std::cout<<"inside itBx" <<std::endl;
     
     int index = itBX - bxShiftFirst - uGtAlgs->getFirstBX();
     for (l1t::EGammaBxCollection::const_iterator egamma = EGammaBxCollection->begin(itBX); egamma != EGammaBxCollection->end(itBX); ++egamma) {
       std::cout<<"inside egamma" <<std::endl;
       
       
       for (size_t i = 0; i < egammaPtCuts_.size(); ++i) {
	 std::cout<<" for pt cut "<<egammaPtCuts_[i]<<"  "<<egamma->pt() << std::endl;
	 if (egamma->pt() >= egammaPtCuts_.at(i)) {
	   //if (index >= 0 and index < (int)egamma_eta_phi_firstbunch.size()) {
	   //denominator_egamma_firstbunch.at(i)->Fill(egamma->eta(), egamma->phi());
	   //egamma_eta_phi_firstbunch.at(i).at(index)->Fill(egamma->eta(), egamma->phi());
	   //}
	   
	   int bxNumberActual = itBX - bxShiftFirst;
	  	   
	   
	   std::cout<<" all candidates ="<<egamma->pt()<<" "<<egamma->hwPt()<<"  "<<egamma->energy()<<std::endl;
	   
	   if ((bool)egamma->hwIso()) {
	     std::cout<<" isolated bx, eta, counter "<<itBX - bxShiftFirst<<"  "<< egamma->hwEta()<<"  "<<isocounterp2<<std::endl;
	     ibx_vs_ieta_Iso->Fill(itBX - bxShiftFirst, egamma->hwEta() );

	     
	     
	     if (bxNumberActual == -2){ 
	       L1preIsoIetam2[isocounterm2] = egamma->hwEta();
	       L1preIsoIphim2[isocounterm2] = egamma->hwPhi();
	       L1preIsoEnergym2[isocounterm2] = egamma->energy();
	       isocounterm2++;
	     }
	     if (bxNumberActual == -1){ 
	       L1preIsoIetam1[isocounterm1] = egamma->hwEta();
	       L1preIsoIphim1[isocounterm1] = egamma->hwPhi();
	       L1preIsoEnergym1[isocounterm1] = egamma->energy();
	       isocounterm1++;
	     }
	     if (bxNumberActual ==  0){ 
	       L1preIsoIetazero[isocounterzero] = egamma->hwEta();
	       L1preIsoIphizero[isocounterzero] = egamma->hwPhi();
	       L1preIsoEnergyzero[isocounterzero] = egamma->energy();
	       isocounterzero++;
	     }
	     if (bxNumberActual ==  1){ 
	       L1preIsoIetap1[isocounterp1] = egamma->hwEta();
	       L1preIsoIphip1[isocounterp1] = egamma->hwPhi();
	       L1preIsoEnergyp1[isocounterp1] = egamma->energy();
	       isocounterp1++;
	     }
	     if (bxNumberActual ==  2){
	       L1preIsoIetap2[isocounterp2] = egamma->hwEta();
	       L1preIsoIphip2[isocounterp2] = egamma->hwPhi();
	       L1preIsoEnergyp2[isocounterp2] = egamma->energy();
	       isocounterp2++;
	     }
	   }// end of  if ((bool)egamma->hwIso()) {
	 

	   // ----------------------------------------------------------
	   // -------- non-isolated branches starts from here. ---------
	   // ----------------------------------------------------------
	   ibx_vs_ieta_NonIso->Fill(itBX - bxShiftFirst, egamma->hwEta());

	   std::cout<<" eta and hweta "<<egamma->hwEta() <<" "<<egamma->eta() <<std::endl;
	   
	   // non-isolated 
	   if (bxNumberActual == -2){ 
	     L1preNonisoIetam2[nonisocounterm2] = egamma->hwEta();
     	     L1preNonisoIphim2[nonisocounterm2] = egamma->hwPhi();
	     L1preNonisoEnergym2[nonisocounterm2] = egamma->energy();
	     nonisocounterm2++;
	   }
	   if (bxNumberActual == -1){ 
	     L1preNonisoIetam1[nonisocounterm1] = egamma->hwEta();
	     L1preNonisoIphim1[nonisocounterm1] = egamma->hwPhi();
	     L1preNonisoEnergym1[nonisocounterm1] = egamma->energy();
	     nonisocounterm1++;
	   }
	   if (bxNumberActual ==  0){ 
	     L1preNonisoIetazero[nonisocounterzero] = egamma->hwEta();
	     L1preNonisoIphizero[nonisocounterzero] = egamma->hwPhi();
	       L1preNonisoEnergyzero[nonisocounterzero] = egamma->energy();
	       nonisocounterzero++;
	   }
	   if (bxNumberActual ==  1){ 
	     L1preNonisoIetap1[nonisocounterp1] = egamma->hwEta();
	     L1preNonisoIphip1[nonisocounterp1] = egamma->hwPhi();
	     L1preNonisoEnergyp1[nonisocounterp1] = egamma->energy();
	     nonisocounterp1++;
	   }
	   if (bxNumberActual ==  2){
	     L1preNonisoIetap2[nonisocounterp2] = egamma->hwEta();
	     L1preNonisoIphip2[nonisocounterp2] = egamma->hwPhi();
	     L1preNonisoEnergyp2[nonisocounterp2] = egamma->energy();
	     nonisocounterp2++;
	   }

	   // fill all counters 
	   
	   v_nonisocounterm2  = nonisocounterm2    ;    
	   v_nonisocounterm1  = nonisocounterm1    ; 
	   v_nonisocounterzero  = nonisocounterzero; 
	   v_nonisocounterp1  = nonisocounterp1    ; 
	   v_nonisocounterp2  = nonisocounterp2    ; 

	   v_isocounterm2     = isocounterm2       ;
	   v_isocounterm1     = isocounterm1       ;
	   v_isocounterzero   = isocounterzero     ;
	   v_isocounterp1     = isocounterp1       ;
	   v_isocounterp2     = isocounterp2       ;

	   
	   	   
	 }
       }
     }
   }
   
   
   // for the last bunch crossing 
   /*


   for (int itBX = std::max(EGammaBxCollection->getFirstBX(), EGammaBxCollection->getFirstBX() + bxShiftLast); itBX <= std::min(EGammaBxCollection->getLastBX(), EGammaBxCollection->getLastBX() + bxShiftLast); ++itBX) {
     std::cout<<"inside itBx" <<std::endl;
     auto correctedBx = itBX - bxShiftLast;
     for (l1t::EGammaBxCollection::const_iterator egamma = EGammaBxCollection->begin(itBX); egamma != EGammaBxCollection->end(itBX); ++egamma) {
       std::cout<<"inside egamma" <<std::endl;
       for (size_t i = 0; i < egammaPtCuts_.size(); ++i) {
	 if (egamma->pt() >= egammaPtCuts_.at(i)) {
	   //if (correctedBx >= 0 and correctedBx < (int)egamma_eta_phi_lastbunch.size()) {
	     //denominator_egamma_lastbunch.at(i)->Fill(egamma->eta(), egamma->phi());
	     //egamma_eta_phi_lastbunch.at(i).at(correctedBx)->Fill(egamma->eta(), egamma->phi());
	   //}
	   if ((bool)egamma->hwIso()) {
	     std::cout<<" isolated "<<correctedBx<<"  "<< egamma->hwEta()<<std::endl;
	     //egamma_iso_bx_ieta_lastbunch.at(i)->Fill(correctedBx, egamma->hwEta());
	   }
	   //egamma_noniso_bx_ieta_lastbunch.at(i)->Fill(correctedBx, egamma->hwEta());
	   std::cout<<" non-isolated "<<correctedBx<<"  "<< egamma->hwEta()<<std::endl;
	   
	 }
       }
     }
   }

   */


   
   // ------------------------------------------**********----------***-------------------------------------------------------------------------
   // -----------------------------------------------*--------------*--***----------------------------------------------------------------------
   // -----------------------------------------------*--------------*----**---------------------------------------------------------------------
   // -----------------------------------------------*--------------*--***----------------------------------------------------------------------
   // -----------------------------------------------*--------------***-------------------------------------------------------------------------
   // -----------------------------------------------*--------------*---------------------------------------------------------------------------
   // -----------------------------------------------*--------------*---------------------------------------------------------------------------

   // ---------------------------------
   // event information 
   // ---------------------------------
   runNb = e.id().run() ;
   evtNb = e.id().event() ;
   bxNb = e.bunchCrossing() ;
   orbitNb = e.orbitNumber() ;
   lumiBlock = e.luminosityBlock();
   
   float startTime_ = 1461466500; //                                                                                                                                                                               
   unsigned int  timeStampLow = ( 0xFFFFFFFF & e.time().value() );
   unsigned int  timeStampHigh = ( e.time().value() >> 32 );

   double rawEventTime = ( double)(timeStampHigh)+((double )(timeStampLow)/1000000.);
   double eventTime = rawEventTime - startTime_; //Notice the subtraction of the "starttime"
   
   timeStamp =  eventTime;

   
   
   // -------------------------------
   //  TT information 
   // -------------------------------
   
   edm::Handle<EcalTrigPrimDigiCollection> tp;
   e.getByToken(tpCollection_,tp);
   //std::cout<<"TP collection size="<<tp.product()->size()<<std::endl ;
   
   map<EcalTrigTowerDetId, towerEner>::iterator itTT ;
   map<EcalTrigTowerDetId, towerEner> mapTower ;

   // pulseshape
   // EEDigiCollection                      "selectDigi"                "selectedEcalEEDigiCollection"   "RECO"
   // EBDigiCollection                      "selectDigi"                "selectedEcalEBDigiCollection"   "RECO"
   
   std::vector<int> Rechit_adc;
   Rechit_adc.clear();
   edm::Handle<EEDigiCollection>  EEdigis;
   if(true)     {
     e.getByToken(EEdigistoken_,EEdigis);
     if(not e.getByToken(EEdigistoken_,EEdigis)){
       std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<<"simEcalUnsuppressedDigis:APD"<<std::endl;
       exit(0);
     }
   }

   int j=0;
   int countNadc=0;
   for ( EEDigiCollection::const_iterator hitItr = EEdigis->begin(); hitItr != EEdigis->end(); ++hitItr ) {
     EEDataFrame df(*hitItr);
     
     for(int i=0; i<10;++i){
       std::cout<<" ADC count for EEDataFrame number = "<<j << "  sample number "<<i<<"  "<<df.sample(i).adc()<<std::endl;
       //Rechit_adc.push_back(df.sample(i).adc());
       index_df[countNadc] = j;
       index_ts[countNadc] = i;
       count_ADC[countNadc] = df.sample(i).adc();
       countNadc++;
       
     }
     j++;
     
   }
   
   ndataframe = j;
   nADC       = countNadc;
   
   /*
       uint ndataframe;
  uint nADC;
  uint index_df[4032];
  uint index_ts[4032];
  int count_ADC[4032];
   */
   
   // pulseshape setup ends here 


   for (unsigned int i=0;i<tp.product()->size();i++) {
     EcalTriggerPrimitiveDigi d = (*(tp.product()))[i];
     const EcalTrigTowerDetId TPtowid= d.id();
     towerEner tE ;
     //tE.TCCid_= theMapping_->TCCid(TPtowid);                                                                                                                                                           
     //tE.TowerInTCC_ = theMapping_->iTT(TPtowid);                                                                                                                                                       
     //      const EcalTriggerElectronicsId elId = theMapping_->getTriggerElectronicsId(id) ;                                                                                                            
     //tE.strip_ = 0;//elId.pseudoStripId() ;                                                                                                                                                            
     
     tE.iphi_ = TPtowid.iphi() ;
     tE.ieta_ = TPtowid.ieta() ;
     tE.ttFlag_ = d[0].ttFlag();
     tE.tpgADC_ = (d[0].raw()&0xfff) ;
     tE.twrADC = (d[0].raw()&0xff) ;
     tE.sFGVB = (d[0].sFGVB());
     mapTower[TPtowid] = tE ;
   }


   // -------------------------------
   //  emulator information 
   // -------------------------------
   edm::Handle<EcalTrigPrimDigiCollection> tpEmul ;
   e.getByToken(tpEmulatorCollection_, tpEmul);
   
   
   for (unsigned int i=0;i<tpEmul.product()->size();i++) {
     EcalTriggerPrimitiveDigi d = (*(tpEmul.product()))[i];
     const EcalTrigTowerDetId TPtowid= d.id();
     itTT = mapTower.find(TPtowid) ;
     if (itTT != mapTower.end())
       for (int j=0 ; j<5 ; j++) {
	 (itTT->second).tpgEmul_[j] = (d[j].raw()&0xfff) ;
	 (itTT->second).tpgEmulFlag_[j] = d[j].ttFlag();
	 (itTT->second).tpgEmulsFGVB_[j] = d[j].sFGVB();
       }
   }

   

   int towerNb = 0 ;
   for (itTT = mapTower.begin() ; itTT != mapTower.end() ; ++itTT) {

     // select only non zero towers                                                                                                                                                                      
     bool fill(true) ;
     bool nonZeroEmul(false) ;
     for (int i=0 ; i<5 ; i++) if (((itTT->second).tpgEmul_[i]&0xff) > 0) nonZeroEmul = true ;
     if ( true && ((itTT->second).tpgADC_&0xff) <= 0 && (!nonZeroEmul) ) fill = false ;
     if (fill) {
       if (false) std::cout<<"ieta="<<(itTT->second).ieta_<<" iphi "<<(itTT->second).iphi_<<" tp="<<((itTT->second).tpgADC_&0xff)<<" tpEmul=" ;
       if (false) for (int i=0 ; i<5 ; i++) std::cout<<((itTT->second).tpgEmul_[i]&0xff)<<" " ;
       // nxtal info is not copied from the tpganalyzer 
       //std::cout<<" nbXtal="<<(itTT->second).nbXtal_ ;
       if (false) std::cout<<std::endl ;
     }

     // fill everything in the ttree
     //      fill=true;                                                                                                                                                                                  
     if (fill) {
       ieta[towerNb] = (itTT->second).ieta_ ;
       iphi[towerNb] = (itTT->second).iphi_ ;
       nbOfXtals[towerNb] = (itTT->second).nbXtal_ ;
       rawTPData[towerNb] = (itTT->second).tpgADC_ ;
       rawTPEmul1[towerNb] = (itTT->second).tpgEmul_[0] ;
       rawTPEmul2[towerNb] = (itTT->second).tpgEmul_[1] ;
       rawTPEmul3[towerNb] = (itTT->second).tpgEmul_[2] ;
       rawTPEmul4[towerNb] = (itTT->second).tpgEmul_[3] ;
       rawTPEmul5[towerNb] = (itTT->second).tpgEmul_[4] ;
       rawTPEmulttFlag1[towerNb] = (itTT->second).tpgEmulFlag_[0] ;
       rawTPEmulttFlag2[towerNb] = (itTT->second).tpgEmulFlag_[1] ;
       rawTPEmulttFlag3[towerNb] = (itTT->second).tpgEmulFlag_[2] ;
       rawTPEmulttFlag4[towerNb] = (itTT->second).tpgEmulFlag_[3] ;
       rawTPEmulttFlag5[towerNb] = (itTT->second).tpgEmulFlag_[4] ;
       rawTPEmulsFGVB1[towerNb] = (itTT->second).tpgEmulsFGVB_[0] ;
       rawTPEmulsFGVB2[towerNb] = (itTT->second).tpgEmulsFGVB_[1] ;
       rawTPEmulsFGVB3[towerNb] = (itTT->second).tpgEmulsFGVB_[2] ;
       rawTPEmulsFGVB4[towerNb] = (itTT->second).tpgEmulsFGVB_[3] ;
       rawTPEmulsFGVB5[towerNb] = (itTT->second).tpgEmulsFGVB_[4] ;
       crystNb[towerNb] = (itTT->second).crystNb_ ;
       eRec[towerNb] = (itTT->second).eRec_ ;
       sevlv[towerNb] = (itTT->second).sevlv_ ;
       ttFlag[towerNb] = (itTT->second).ttFlag_ ;
       spike[towerNb] = (itTT->second).spike_ ;
       twrADC[towerNb] =  (itTT->second).twrADC;
       sFGVB[towerNb] =  (itTT->second).sFGVB;

       if (abs(ieta[towerNb])>17) {
	 unsigned int maxEmul = 0 ;
	 for (int i=0 ; i<5 ; i++) if (((itTT->second).tpgEmul_[i]&0xff) > maxEmul) maxEmul = ((itTT->second).tpgEmul_[i]&0xff) ;
       }
       towerNb++ ;
     }

   }

   nbOfTowers = towerNb ;

   prefiringTree->Fill();
   
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
PrefiringTuplizer::beginJob()
{
  
}

void PrefiringTuplizer::beginRun(const edm::Run& r, const edm::EventSetup& c) {

  
}



// ------------ method called once each job just after ending the event loop  ------------
void
PrefiringTuplizer::endJob()
{

  ibx_vs_ieta_Iso->Write();
  ibx_vs_ieta_NonIso->Write();
  
  prefiringTree->Write();
  
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PrefiringTuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  desc.addUntracked<std::string>("useAlgoDecision", "initial")->setComment("Which algo decision should be checked [initial, intermediate, final].");
  desc.addUntracked<std::vector<double>>("egammaPtCuts", {20., 10., 30.})->setComment("List if min egamman pT vaules");

    
  
  descriptions.addDefault(desc);
  
  
  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PrefiringTuplizer);

