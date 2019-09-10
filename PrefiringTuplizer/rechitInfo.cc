#include "DPGTask/SpikeStudy/interface/rechitInfo.h"

rechitInfo::rechitInfo(std::string name, TTree* tree, bool debug, const pset& iConfig):baseTree(name,tree,debug){
  if(debug) std::cout<<"in rechit constructor"<<std::endl;
  EBDigiLabel_               = iConfig.getUntrackedParameter<edm::InputTag> ("EBDigiLabel_");
  fillNoiseInfo_             = iConfig.getUntrackedParameter<bool> ("fillNoiseInfo_");
  fillDigiInfo_              = iConfig.getUntrackedParameter<bool> ("fillDigiInfo_");
  fillUncalibInfo_           = iConfig.getUntrackedParameter<bool> ("fillUncalibInfo_");

  fillTPInfo_                = iConfig.getUntrackedParameter<bool> ("fillTPInfo_");
  TPDigisLabel_              = iConfig.getUntrackedParameter<edm::InputTag> ("TPDigisLabel_");

  fillAPDInfo_               = iConfig.getUntrackedParameter<bool> ("fillAPDInfo_");
  apdDigiLabel_              = iConfig.getUntrackedParameter<edm::InputTag> ("apdDigiLabel_");
  SetBranches(name);
  
  if(debug) std::cout<<"in rechit constructor: calling SetBrances()"<<std::endl;  
}

rechitInfo::~rechitInfo(){
  delete tree_;
}

void rechitInfo::Fill(const edm::Event& iEvent, const edm::EventSetup& iSetup, std::string name, edm::InputTag rechitBLabel_, edm::InputTag urechitBLabel_){

  if(debug_)  std::cout<<"Method::"<<name<<std::endl; 
  Clear();
  if(debug_)  std::cout<<"getting rechit info"<<std::endl;


  edm::Handle<EcalTrigPrimDigiCollection> Orig_TPs;
  if(fillTPInfo_)
    {
      iEvent.getByLabel(TPDigisLabel_,Orig_TPs);
      if(not iEvent.getByLabel(TPDigisLabel_,Orig_TPs)){
	std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<<TPDigisLabel_<<std::endl; 
	exit(0);
      }
    }

  edm::ESHandle<EcalPedestals> ecalped;
  iSetup.get<EcalPedestalsRcd>().get(ecalped);
  const EcalPedestals* eped=ecalped.product();
    
  edm::Handle<EBDigiCollection>  EBdigis;
  if(fillDigiInfo_){
    iEvent.getByLabel(EBDigiLabel_,EBdigis);
    if(not iEvent.getByLabel(EBDigiLabel_,EBdigis)){
      std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<<EBDigiLabel_<<std::endl; 
      exit(0);
    }
  }
  
  edm::Handle<EBDigiCollection>  APDdigis;
  
  if(fillAPDInfo_)
    {
      iEvent.getByLabel(apdDigiLabel_,APDdigis);
      if(not iEvent.getByLabel(apdDigiLabel_,APDdigis)){
	std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<<"simEcalUnsuppressedDigis:APD"<<std::endl; 
	exit(0);
      }    
    }
  
  edm::Handle<EcalRecHitCollection> Brechit;//barrel
  iEvent.getByLabel(rechitBLabel_,Brechit);
  if(not iEvent.getByLabel(rechitBLabel_,Brechit)){
    std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<<rechitBLabel_<<std::endl; 
    exit(0);
  }    
  const EcalRecHitCollection & rechits = *Brechit;

  edm::Handle<EcalUncalibratedRecHitCollection> Uncalib_Brechit;
  if(fillUncalibInfo_) 
    {
      iEvent.getByLabel(urechitBLabel_, Uncalib_Brechit);
      if(not iEvent.getByLabel(urechitBLabel_, Uncalib_Brechit)){
	std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<<urechitBLabel_<<std::endl; 
	exit(0);
      }
    }




  if(debug_)  std::cout<<"got all the handles"<<std::endl;
  
  int ihit = 0;
  for ( EcalRecHitCollection::const_iterator hitItr = Brechit->begin(); hitItr != Brechit->end(); ++hitItr ) {
    ihit++;
    EBDetId detId  = (EBDetId)(hitItr->id());
    Rechit_energy.push_back((float) hitItr->energy());
    //std::cout<<"ihit:\t"<<ihit<<"Energy:"<<hitItr->energy()<<std::endl;
    Rechit_et.push_back(recHitApproxEt(hitItr->id(), rechits));
    Rechit_time.push_back((float)   hitItr->time());
    
    Rechit_ifkWeird.push_back((bool)    hitItr->checkFlag(EcalRecHit::kWeird));
    Rechit_ifkDiWeird.push_back((bool)  hitItr->checkFlag(EcalRecHit::kDiWeird));
    Rechit_ifkOOT.push_back((bool)      hitItr->checkFlag(EcalRecHit::kOutOfTime));
    Rechit_ifkGood.push_back((bool)     hitItr->checkFlag(EcalRecHit::kGood));
    Rechit_ifnearCrack.push_back((bool) EBDetId::isNextToBoundary(detId));
    Rechit_e4e1.push_back((float)       e4e1   (detId, rechits));
    Rechit_swissCross.push_back((float) swissCross(detId, rechits));
    Rechit_e6e2.push_back((float)       Gete6e2(detId, rechits));
    Rechit_ieta.push_back((int) detId.ieta());
    Rechit_iphi.push_back((int) detId.iphi());
    
    
    const EcalTrigTowerDetId towid= detId.tower();
    //std::cout<<"TT iD:"<<towid<<"\t tower ieta:"<< towid.ieta()<< "\t tower iphi:"<< towid.iphi()<<"\t ieta:"<< detId.ieta() << "\t iphi:"<< detId.iphi()<<std::endl;
    
    Rechit_TT_ieta.push_back((int) towid.ieta());
    Rechit_TT_iphi.push_back((int) towid.iphi());

    
    if(fillUncalibInfo_)
      {
	for (EcalUncalibratedRecHitCollection::const_iterator uhitItr = Uncalib_Brechit->begin(); uhitItr != Uncalib_Brechit->end(); ++uhitItr) {
	  EcalUncalibratedRecHit uhit    = (*uhitItr);
	  EBDetId det                    = uhit.id();
	  if (det!=detId) continue;   /// here "detId" is the detid of a specific EB rechit - this performs the matching of rechits and uncalibrated rechits
	  URechit_amplitude.push_back(uhitItr->amplitude());
	  URechit_amplitudeError.push_back(uhitItr->amplitudeError());
	  URechit_pedestal.push_back(uhitItr->pedestal());
	  URechit_jitter.push_back(uhitItr->jitter());
	  URechit_chi2.push_back(uhitItr->chi2());
	  for (int i=0;i<10;i++) 
	    URechit_ootamplitude.push_back(uhitItr->outOfTimeAmplitude(i));
	}
      }
	
    if(fillNoiseInfo_){
      const EcalPedestals::Item *aped=0;
      int hashedid= detId.hashedIndex();
      aped=&eped->barrel(hashedid);
      Rechit_pedrms_g12.push_back((float)aped->rms_x12);
    }
    
    if(fillDigiInfo_){
      EBDigiCollection::const_iterator digiItrEB1= EBdigis->begin();
      while(digiItrEB1 != EBdigis->end() && digiItrEB1->id() != hitItr->id())
	digiItrEB1++;
      
      if (digiItrEB1 != EBdigis->end()) {
	EBDataFrame df(*digiItrEB1);
	for(int i=0; i<10;++i)
	  Rechit_adc.push_back(df.sample(i).adc());
	
      }
    }
    
    if(fillTPInfo_)
      {
	int TT_index = -1;
	int TT_Et = -1; 
	int TT_ttFlag = -1; 
	
	EcalTrigPrimDigiCollection::const_iterator TP = Orig_TPs->begin();
	while(TP != Orig_TPs->end() && TP->id() != towid)
	  { TP++; 
	    TT_index++; 
	  }
	
	bool is_L1_spike = false;
	if(TP!=Orig_TPs->end()){
	  is_L1_spike = (bool) TP->sFGVB();
	  
	  //////////////////////////////////
	  ///Compressed Et:   the trigger primitive transverse energy
	  ///in ADC counts.  1 ADC count = 0.5 GeV, so 4 ADC counts is 2 GeV Et
	  ///ttFlag       :  1=Zero suppressed, 3=Full readout, 0 = ? 
	  ///////////////////////////////////
	  TT_Et = TP->compressedEt();
	  
	  TT_ttFlag = TP->ttFlag();
	  //std::cout<<"TP info for this rechit:"<<std::endl;
	  //  std::cout << std::fixed;
	  
	  //     std::cout<<std::setw(20)<<"size:"<<TP->size()<<std::setw(20)<<"sampleOfInterest:"<<TP->sampleOfInterest()
	  //	       <<std::setw(20)<< "compressedEt:"<<TP->compressedEt()<<std::setw(20)<<"fineGrain:"<<TP->fineGrain()
	  //	       <<std::setw(20)<<"ttFlag:"<<TP->ttFlag() <<std::setw(20)<<"sFGVB:"<<TP->sFGVB()
	  //	       <<std::endl;
	  
	  //std::cout<<std::setw(20)<<TP->size()<<std::setw(20)<<TP->sampleOfInterest()
	  //       <<std::setw(20)<<TP->compressedEt()<<std::setw(20)<<TP->fineGrain()
	  //       <<std::setw(20)<<TP->ttFlag() <<std::setw(20)<<TP->sFGVB()
	  //       <<std::endl;
	  
	  TT_index++;
	}
	Rechit_is_L1_spike.push_back(is_L1_spike);
	Rechit_TT_index.push_back(TT_index);
	Rechit_TT_Et.push_back(TT_Et);
	Rechit_TT_ttFlag.push_back(TT_ttFlag);
      }
    
    if(fillAPDInfo_)
      {
	bool is_spike = false;
	bool is_spike_50_counts = false;
	bool is_spike_100_counts = false;
	
	EBDigiCollection::const_iterator digiItrEB= APDdigis->begin();
	while(digiItrEB != APDdigis->end() && digiItrEB->id() != hitItr->id())
	  {
	    digiItrEB++;
	  }
	
	if (digiItrEB != APDdigis->end()) {
	  is_spike = true; 
	  
	  if(debug_ && hitItr->energy()>2.)
	    {
	      std::cout<<"matching APD digi found for this rechit:"<<std::endl;
	      std::cout<<"rechit ieta, iphi :"<< detId.ieta() << "\t "<< detId.iphi()<<std::endl;
	      std::cout<<"its information from APD digi collection"<<std::endl;
	    }
	  EBDataFrame df(*digiItrEB);
	  for(int i=0; i<10;++i)
	    {
	      if(hitItr->energy()>2.&& debug_)
		std::cout<<i+1<<"\t "<< df.sample(i).gainId()<<"\t"<<df.sample(i).adc()<< std::endl;
	      if (df.sample(i).adc()>250 || df.sample(i).gainId()!=1) {
		is_spike_50_counts=true;
	      }
	      if (df.sample(i).adc()>300 || df.sample(i).gainId()!=1) {
		is_spike_100_counts=true;
	      }
	    }
	}
	
	Rechit_is_spike.push_back(is_spike);
	Rechit_is_spike_50_counts.push_back(is_spike_50_counts);
	Rechit_is_spike_100_counts.push_back(is_spike_100_counts);
	
	if (is_spike && hitItr->energy()>2. && debug_)
	  {
	    EBDigiCollection::const_iterator digiItrEB1 = EBdigis->begin();
	    while(digiItrEB1 != EBdigis->end() && digiItrEB1->id() != hitItr->id())
	      {
		digiItrEB1++;
	      }
	    
	    if (digiItrEB1 != EBdigis->end()) {
	      std::cout<<"its information from EBdigi collection"<<std::endl;
	      EBDataFrame df1(*digiItrEB1);
	      for(int i=0; i<10;++i)
		{
		  std::cout<<i+1<<"\t "<< df1.sample(i).gainId()<<"\t"<<df1.sample(i).adc()<< std::endl;
		}
	    }
	  }
	/*
	  if(is_spike_50_counts  && swissCross(detId, rechits) < 0.8  && fabs(hitItr->time())<12.5 && hitItr->energy() > 10. )
	  {
	  std::cout<<"found interesting spike with swissCross:" << swissCross(detId, rechits)<< " and e1: " << hitItr->energy()<< std::endl;
	  std::cout<<" time, ieta, iphi, TT ieta , TT iphi:" <<hitItr->time()<<"\t"
	  <<detId.ieta()<<"\t"<< detId.iphi()<<"\t"<< detId.tower_ieta()<< "\t"<< detId.tower_iphi()<<std::endl; 
	  
	  std::cout<<"TT info: "<<std::endl;
	  PrintTTInfo(detId.tower_ieta(), detId.tower_iphi(), rechits);
	  
	  std::cout<<"4 Neighbours: "<<std::endl;
	  
	  float en = -1; 
	  EBDetId det;
	  std::vector<DetId> ret;
	  if ( detId.subdetId() == EcalBarrel) {
	  if( en < recHitE(EBDetId::offsetBy( detId,   1, 0 ) ,rechits)) 
	  {
	  en = recHitE(EBDetId::offsetBy( detId,   1, 0 ), rechits);
	  det = (EBDetId) EBDetId::offsetBy( detId,   1, 0 );
	  }
	  std::cout<<"1,0 , energy, time, ieta, iphi, TT ieta , TT iphi:: "<<recHitE(EBDetId::offsetBy( detId,   1, 0 ) ,rechits)<<"\t"
	  << recHitT(EBDetId::offsetBy( detId,   1, 0 ) ,rechits)<<"\t"
	  << ((EBDetId) EBDetId::offsetBy( detId,   1, 0 )).ieta()<<"\t"<< ((EBDetId) EBDetId::offsetBy( detId,   1, 0 )).iphi()<<"\t"
	  << ((EBDetId) EBDetId::offsetBy( detId,   1, 0 )).tower_ieta()<< "\t"<< ((EBDetId) EBDetId::offsetBy( detId,   1, 0 )).tower_iphi()<<std::endl;
	  if( en < recHitE(EBDetId::offsetBy( detId,   -1, 0 ) ,rechits)) 
	  {
	  en = recHitE(EBDetId::offsetBy( detId,   -1, 0 ), rechits);
	  det = (EBDetId) EBDetId::offsetBy( detId,   -1, 0 );
	  }
	  std::cout<<"-1,0, energy, time, ieta, iphi, TT ieta , TT iphi:: "<<recHitE(EBDetId::offsetBy( detId,  -1, 0 ) ,rechits)<<"\t"
	  << recHitT(EBDetId::offsetBy( detId,   -1, 0 ) ,rechits)<<"\t"
	  << ((EBDetId) EBDetId::offsetBy( detId,   -1, 0 )).ieta()<<"\t"<< ((EBDetId) EBDetId::offsetBy( detId,   -1, 0 )).iphi()<<"\t"
	  << ((EBDetId) EBDetId::offsetBy( detId,   -1, 0 )).tower_ieta()<< "\t"<< ((EBDetId) EBDetId::offsetBy( detId,   -1, 0 )).tower_iphi()<<std::endl;
	  if( en < recHitE(EBDetId::offsetBy( detId,   0, 1 ) ,rechits)) 
	  {
	  en = recHitE(EBDetId::offsetBy( detId,   0, 1 ), rechits) ;
	  det = (EBDetId) EBDetId::offsetBy( detId,   0, 1 );
	  }
	  
	  std::cout<<"0,1 , energy, time, ieta, iphi, TT ieta , TT iphi:: "<<recHitE(EBDetId::offsetBy( detId,   0, 1 ) ,rechits)<<"\t"
	  << recHitT(EBDetId::offsetBy( detId,   0, 1 ) ,rechits)<<"\t"
	  << ((EBDetId) EBDetId::offsetBy( detId,   0, 1 )).ieta()<<"\t"<< ((EBDetId) EBDetId::offsetBy( detId,   0, 1 )).iphi()<<"\t"
	  << ((EBDetId) EBDetId::offsetBy( detId,   0, 1 )).tower_ieta()<< "\t"<< ((EBDetId) EBDetId::offsetBy( detId,   0, 1 )).tower_iphi()<<std::endl;
	  
	  if( en < recHitE(EBDetId::offsetBy( detId,   0, -1 ) ,rechits)) 
	  {
	  en = recHitE(EBDetId::offsetBy( detId,   0, -1 ), rechits);
	  det = (EBDetId) EBDetId::offsetBy( detId,   0, -1 );
	  }
	  std::cout<<"0,-1, energy, time, ieta, iphi, TT ieta , TT iphi:: "<<recHitE(EBDetId::offsetBy( detId,   0, -1) ,rechits)<<"\t"
	  << recHitT(EBDetId::offsetBy( detId,   0, -1 ) ,rechits)<<"\t"
	  << ((EBDetId) EBDetId::offsetBy( detId,   0, -1 )).ieta()<<"\t"<< ((EBDetId) EBDetId::offsetBy( detId,   0, -1 )).iphi()<<"\t"
	  << ((EBDetId) EBDetId::offsetBy( detId,   0, -1 )).tower_ieta()<< "\t"<< ((EBDetId) EBDetId::offsetBy( detId,   0, -1 )).tower_iphi()<<std::endl;
	  
	  }
	  
	  if (det.tower_ieta() != detId.tower_ieta() || det.tower_iphi() != detId.tower_iphi())
	  {
	  std::cout<< "if hit is next TT, TT info of that"<<std::endl; 
	  PrintTTInfo(det.tower_ieta(), det.tower_iphi(), rechits);
	  }
	  }*/
      }
  }
  if(debug_)    std::cout<<"got rechit info"<<std::endl;
}




void rechitInfo::SetBranches(std::string name ){
  if(debug_)    std::cout<<"setting branches: calling AddBranch of baseTree"<<std::endl;
  AddBranch(&Rechit_energy          ,"Rechit"+name+"_energy");
  AddBranch(&Rechit_et              ,"Rechit"+name+"_et");
  AddBranch(&Rechit_time            ,"Rechit"+name+"_time");
  AddBranch(&Rechit_ifkWeird        ,"Rechit"+name+"_ifkWeird");
  AddBranch(&Rechit_ifkGood         ,"Rechit"+name+"_ifkGood");
  AddBranch(&Rechit_ifkDiWeird      ,"Rechit"+name+"_ifkDiWeird");
  AddBranch(&Rechit_ifkOOT          ,"Rechit"+name+"_ifkOOT");
  AddBranch(&Rechit_ifnearCrack     ,"Rechit"+name+"_ifnearCrack");
  AddBranch(&Rechit_e4e1            ,"Rechit"+name+"_e4e1");
  AddBranch(&Rechit_swissCross      ,"Rechit"+name+"_swissCross");
  AddBranch(&Rechit_e6e2            ,"Rechit"+name+"_e6e2");
  AddBranch(&Rechit_ieta            ,"Rechit"+name+"_ieta");
  AddBranch(&Rechit_iphi            ,"Rechit"+name+"_iphi");
  AddBranch(&Rechit_TT_ieta         ,"Rechit"+name+"_TT_ieta");
  AddBranch(&Rechit_TT_iphi         ,"Rechit"+name+"_TT_iphi");
  if(fillNoiseInfo_){ 
    AddBranch(&Rechit_pedrms_g12      ,"Rechit"+name+"_pedrms_g12");
    //  AddBranch(&Rechit_ped             ,"Rechit"+name+"_ped");
    AddBranch(&Rechit_adc             ,"Rechit"+name+"_adc");
  }
  if(fillTPInfo_){
    AddBranch(&Rechit_is_L1_spike     ,"Rechit"+name+"_is_L1_spike");
    AddBranch(&Rechit_TT_index        ,"Rechit"+name+"_TT_index");
    AddBranch(&Rechit_TT_Et           ,"Rechit"+name+"_TT_Et");
    AddBranch(&Rechit_TT_ttFlag       ,"Rechit"+name+"_TT_ttFlag");
  }
  if(fillAPDInfo_){
    AddBranch(&Rechit_is_spike            ,"Rechit"+name+"_is_spike");
    AddBranch(&Rechit_is_spike_50_counts  ,"Rechit"+name+"_is_spike_50_counts");
    AddBranch(&Rechit_is_spike_100_counts ,"Rechit"+name+"__is_spike_100_counts");
  }
  
  if(fillUncalibInfo_)
    {
      AddBranch(&URechit_amplitude            ,"URechit"+name+"_amplitude");
      AddBranch(&URechit_amplitudeError       ,"URechit"+name+"_amplitudeError");
      AddBranch(&URechit_pedestal             ,"URechit"+name+"_pedestal");
      AddBranch(&URechit_jitter               ,"URechit"+name+"_jitter");
      AddBranch(&URechit_chi2                 ,"URechit"+name+"_chi2");
      AddBranch(&URechit_ootamplitude         ,"URechit"+name+"_ootamplitude");
    }

  if(debug_)    std::cout<<"set branches"<<std::endl;
}

void rechitInfo::Clear(){
  if(debug_)std::cout<<"clearing Rechit info"<<std::endl;

  Rechit_energy.clear();
  Rechit_et.clear();
  Rechit_time.clear();
  Rechit_ifkWeird.clear();
  Rechit_ifkDiWeird.clear();
  Rechit_ifkOOT.clear();
  Rechit_ifkGood.clear();
  Rechit_ifnearCrack.clear();
  Rechit_e4e1.clear();
  Rechit_swissCross.clear();
  Rechit_e6e2.clear();
  Rechit_ieta.clear();
  Rechit_iphi.clear();
  Rechit_TT_ieta.clear();
  Rechit_TT_iphi.clear();
  if(fillNoiseInfo_){
    Rechit_pedrms_g12.clear();
    //Rechit_ped.clear();
    Rechit_adc.clear();
  }
  if(fillTPInfo_){
    Rechit_is_L1_spike.clear();
    Rechit_TT_index.clear();
    Rechit_TT_Et.clear();
    Rechit_TT_ttFlag.clear();
  }
  if(fillAPDInfo_){
    Rechit_is_spike.clear();
    Rechit_is_spike_50_counts.clear();
    Rechit_is_spike_100_counts.clear();
  }

  if(fillUncalibInfo_)
    {
      URechit_amplitude.clear();
      URechit_amplitudeError.clear();
      URechit_pedestal.clear();
      URechit_jitter.clear();
      URechit_chi2.clear();
      URechit_ootamplitude.clear();
    }
 if(debug_) std::cout<<"cleared"<<std::endl;
}

