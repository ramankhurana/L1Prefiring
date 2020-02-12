#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>

//void phaseMonitoring(int tcc=-1, int zoom = -1, int maxData, int ref = -1)
void phaseMonitoring(int tcc=-1, int zoom = -1, int maxData = 10, int ref = -1)
{
  int refbx[108] ;
  for (int tccId=1 ; tccId<=108 ; tccId++) {
    if (ref>-1) refbx[tccId-1] = 3469;//3483; //ref ; //modif-alex 
    else {
      if (tccId>36 && tccId<73) refbx[tccId-1] = 1500;//1513; //1503 ; // => nominal
      else refbx[tccId-1] = 3469;//3483; //3484 ; //modif-alex
    }
  }//loop tccId 

  bool debug = true;
  bool draw  = true;

  int maxNstripsV[109];
  for(int imax=0; imax<109; ++imax) maxNstripsV[imax] = 0;
  maxNstripsV[1] = 42;
  maxNstripsV[2] = 40;
  maxNstripsV[3] = 41;
  maxNstripsV[4] = 40;
  maxNstripsV[5] = 41;
  maxNstripsV[6] = 41;
  maxNstripsV[7] = 40;
  maxNstripsV[8] = 41;
  maxNstripsV[9] = 40;
  maxNstripsV[10] = 42;
  maxNstripsV[11] = 40;
  maxNstripsV[12] = 41;
  maxNstripsV[13] = 40;
  maxNstripsV[14] = 41;
  maxNstripsV[15] = 41;
  maxNstripsV[16] = 40;
  maxNstripsV[17] = 41;
  maxNstripsV[18] = 40;
  maxNstripsV[19] = 46;
  maxNstripsV[20] = 39;
  maxNstripsV[21] = 41;
  maxNstripsV[22] = 40;
  maxNstripsV[23] = 41;
  maxNstripsV[24] = 41;
  maxNstripsV[25] = 40;
  maxNstripsV[26] = 41;
  maxNstripsV[27] = 39;
  maxNstripsV[28] = 46;
  maxNstripsV[29] = 39;
  maxNstripsV[30] = 41;
  maxNstripsV[31] = 40;
  maxNstripsV[32] = 41;
  maxNstripsV[33] = 41;
  maxNstripsV[34] = 40;
  maxNstripsV[35] = 41;
  maxNstripsV[36] = 39;

  maxNstripsV[73] = 46; 
  maxNstripsV[74] = 39; 
  maxNstripsV[75] = 41; 
  maxNstripsV[76] = 40; 
  maxNstripsV[77] = 41; 
  maxNstripsV[78] = 41; 
  maxNstripsV[79] = 40; 
  maxNstripsV[80] = 41; 
  maxNstripsV[81] = 39; 
  maxNstripsV[82] = 46; 
  maxNstripsV[83] = 39; 
  maxNstripsV[84] = 41; 
  maxNstripsV[85] = 40; 
  maxNstripsV[86] = 41; 
  maxNstripsV[87] = 41; 
  maxNstripsV[88] = 40; 
  maxNstripsV[89] = 41; 
  maxNstripsV[90] = 39; 
  maxNstripsV[91] = 42; 
  maxNstripsV[92] = 40; 
  maxNstripsV[93] = 41; 
  maxNstripsV[94] = 40; 
  maxNstripsV[95] = 41; 
  maxNstripsV[96] = 41; 
  maxNstripsV[97] = 40; 
  maxNstripsV[98] = 41; 
  maxNstripsV[99] = 40; 
  maxNstripsV[100] = 42;
  maxNstripsV[101] = 40; 
  maxNstripsV[102] = 41; 
  maxNstripsV[103] = 40; 
  maxNstripsV[104] = 41; 
  maxNstripsV[105] = 41; 
  maxNstripsV[106] = 40; 
  maxNstripsV[107] = 41; 
  maxNstripsV[108] = 40; 

  std::string TimingDelays_EB_ = "Delays_EB.txt";
  std::string TimingDelays_EE_ = "Delays_EE.txt";
  std::string TimingPhases_EB_ = "Phases_EB.txt";
  std::string TimingPhases_EE_ = "Phases_EE.txt";



  std::cout << "INFO: READING timing files" << std::endl;
  std::ifstream delay_eb(TimingDelays_EB_.c_str()); 
  if(!delay_eb) std::cout << "ERROR: File " << TimingDelays_EB_.c_str() << " could not be opened" << std::endl;
  std::ifstream delay_ee(TimingDelays_EE_.c_str());
  if(!delay_ee) std::cout << "ERROR: File " << TimingDelays_EE_.c_str() << " could not be opened" << std::endl;
  std::ifstream phase_eb(TimingPhases_EB_.c_str());
  if(!phase_eb) std::cout << "ERROR: File " << TimingPhases_EB_.c_str() << " could not be opened" << std::endl;
  std::ifstream phase_ee(TimingPhases_EE_.c_str());
  if(!phase_ee) std::cout << "ERROR: File " << TimingPhases_EE_.c_str() << " could not be opened" << std::endl;
  
  cout << "DELAYS EB" << endl;

  char buf[1024];
  //READING DELAYS EB
  delay_eb.getline(buf,sizeof(buf),'\n');
  while( delay_eb ) {
    std::stringstream sin(buf);
    int tcc_file; 
    sin >> tcc_file;
    cout << tcc_file << " ";
    for(unsigned int ideb=0; ideb<68; ++ideb){
      int time_delay = -1;
      sin >> time_delay;
      cout << time_delay << " ";
    } cout << endl;

    delay_eb.getline(buf,sizeof(buf),'\n');
  }//loop delay file EB
  //delay_eb.close();

  cout << "PHASE EB" << endl;

  //READING PHASES EB
  phase_eb.getline(buf,sizeof(buf),'\n');
  while( phase_eb ) {
    std::stringstream sin(buf);
    int tcc_file;
    sin >> tcc_file;
    cout << tcc_file << " ";
    for(unsigned int ipeb=0; ipeb<68; ++ipeb){
      int time_phase = -1;
      sin >> time_phase;
      cout << time_phase << " ";
    } cout << endl;

    phase_eb.getline(buf,sizeof(buf),'\n');
  }//loop phase file EB
  //phase_eb.close();

  //READING DELAYS EE//------------------------------------------------
  cout << "DELAYS EE" << endl;
  delay_ee.getline(buf,sizeof(buf),'\n');
  while( delay_ee ) {
    std::stringstream sin(buf);
    int tcc_file; 
    sin >> tcc_file;
    cout << tcc_file << " "; 
    for(unsigned int idee=0; idee<48; ++idee){
      int time_delay = -1;
      sin >> time_delay;
      cout << time_delay << " ";
    } cout << endl;
    
    delay_ee.getline(buf,sizeof(buf),'\n');
  }//loop delay file EE
  //delay_ee.close();

  cout << "PHASES EE" << endl;
  //READING PHASES EE
  phase_ee.getline(buf,sizeof(buf),'\n');
  while( phase_ee ) {
    std::stringstream sin(buf);
    int tcc_file;
    sin >> tcc_file;
    cout << tcc_file << " ";
    for(unsigned int ipee=0; ipee<48; ++ipee){
      int time_phase = -1;
      sin >> time_phase;
      cout << time_phase << " ";
    } cout << endl;

    phase_ee.getline(buf,sizeof(buf),'\n');
  }//loop phase file EE
  //phase_ee.close();

  cout << endl; 

  ofstream myfile_ebd("Delays_EB_modif.txt") ;
  ofstream myfile_eed("Delays_EE_modif.txt") ;
  ofstream myfile_ebp("Phases_EB_modif.txt") ;
  ofstream myfile_eep("Phases_EE_modif.txt") ;
  ofstream mytest("mytest.txt") ;
  ofstream log_error("log_error.txt") ;

  string sdata ;
  string message; //modif-alex 
  unsigned int data ;
  int bxFirstArray[108][68] ;
  TH2F * h2Gap[108] ;
  TH1F * hcount[108] ;

  for (int tccId=1 ; tccId<=108 ; tccId++)
    {
      h2Gap[tccId-1] = 0 ;
      if (tcc>0 && tcc != tccId) continue ;
      stringstream h2name ;
      h2name<<"h_"<<tccId ;      
      h2Gap[tccId-1] = (TH2F *) gROOT->Get(h2name.str().c_str()) ;
      if (h2Gap[tccId-1] == 0) h2Gap[tccId-1] = new TH2F(h2name.str().c_str(), h2name.str().c_str(), 68, 1, 69, 3564,0,3564) ;
      if (tccId<37 || tccId>72) h2Gap[tccId-1]->GetXaxis()->SetRangeUser(1,49) ;
      stringstream countname ;
      countname<<"c_"<<tccId ;
      hcount[tccId-1] = (TH1F *) gROOT->Get(countname.str().c_str()) ;
      if (hcount[tccId-1] == 0) hcount[tccId-1] = new TH1F(countname.str().c_str(), countname.str().c_str(), 1, 0, 1) ;
    }

  for (int tccId=1 ; tccId<=108 ; tccId++) {

    if (tcc>0 && tcc != tccId) continue ;
    //if (tcc>36) continue; //only EEM 

    // get files
    ifstream in;      
    stringstream name ;
    //name<<"/nfshome0/ecalpro/TPG-Log/tcc_"<<tccId<<".txt" ;
    // name<<"/Users/azabi/Desktop/TRIGGER/TPG-Log/tcc_"<< tccId<<".txt" ;  
    name<<"tcc_"<<tccId<<".txt" ;
    if(debug) cout << "OPENING File =" << name.str() << endl;
    in.open(name.str().c_str());
    
    if (in.is_open()) {

      int count = 0 ;
      bool treat ;

      while (!in.eof()) {
	if(debug) cout << "Now count==" <<dec<< " "<<count << endl; //modif-alex 
	count++ ;

	if(count > maxData) break; //modif-alex 
	in >>dec>> sdata ; if(debug) cout << "SDATA=" << sdata << endl; //modif-alex 
	if (sdata == "") {if(debug) cout << "breaking here, end of file" << endl; break ;} // avoid last line
	int line = atoi(sdata.c_str()) ;
	if (line == 0) {if(debug) cout << "breaking here, no data to read" << endl; break ;} 

	int lastCall = hcount[tccId-1]->GetBinContent(1) ;
	treat = false ;
	if(debug) cout << "line=" <<dec<< line << " lastCall=" <<dec<< lastCall << endl; //modif-alex 
	if (line > lastCall) treat = true ;
	else if(debug) cout << "ERROR: not reading any longer, older entry" << endl; //modif-alex 
	if (treat) {
	  hcount[tccId-1]->SetBinContent(1,float(line)) ;
	  if(debug) cout<<dec<<lastCall<<endl ;
	}

	if (tccId>36 && tccId<73) {
	  // 2 more lines in EB for TTCRx phase measured and set
	  in >> sdata >> dec >> data ;
	  in >> sdata >> dec >> data ;
	}
	//in >> sdata ; //modif-alex 
	int chMax = 69 ;
	//if (tccId<37 || tccId>72)  chMax = 49 ; //modif-alex 
	
	int maxNstrips = 68;
	if(tccId==1) maxNstrips = 42;
	if(tccId==2) maxNstrips = 40;
	if(tccId==3) maxNstrips = 41;
	if(tccId==4) maxNstrips = 40;
	if(tccId==5) maxNstrips = 41;
	if(tccId==6) maxNstrips = 41;
	if(tccId==7) maxNstrips = 40;
	if(tccId==8) maxNstrips = 41;
	if(tccId==9) maxNstrips = 40;
	if(tccId==10) maxNstrips = 42;
	if(tccId==11) maxNstrips = 40;
	if(tccId==12) maxNstrips = 41;
	if(tccId==13) maxNstrips = 40;
	if(tccId==14) maxNstrips = 41;
	if(tccId==15) maxNstrips = 41;
	if(tccId==16) maxNstrips = 40;
	if(tccId==17) maxNstrips = 41;
	if(tccId==18) maxNstrips = 40;
	if(tccId==19) maxNstrips = 46;
	if(tccId==20) maxNstrips = 39;
	if(tccId==21) maxNstrips = 41;
	if(tccId==22) maxNstrips = 40;
	if(tccId==23) maxNstrips = 41;
	if(tccId==24) maxNstrips = 41;
	if(tccId==25) maxNstrips = 40;
	if(tccId==26) maxNstrips = 41;
	if(tccId==27) maxNstrips = 39;
	if(tccId==28) maxNstrips = 46;
	if(tccId==29) maxNstrips = 39;
	if(tccId==30) maxNstrips = 41;
	if(tccId==31) maxNstrips = 40;
	if(tccId==32) maxNstrips = 41;
	if(tccId==33) maxNstrips = 41;
	if(tccId==34) maxNstrips = 40;
	if(tccId==35) maxNstrips = 41;
	if(tccId==36) maxNstrips = 39;

	if(tccId==73) maxNstrips = 46; 
	if(tccId==74) maxNstrips = 39; 
	if(tccId==75) maxNstrips = 41; 
	if(tccId==76) maxNstrips = 40; 
	if(tccId==77) maxNstrips = 41; 
	if(tccId==78) maxNstrips = 41; 
	if(tccId==79) maxNstrips = 40; 
	if(tccId==80) maxNstrips = 41; 
	if(tccId==81) maxNstrips = 39; 
	if(tccId==82) maxNstrips = 46; 
	if(tccId==83) maxNstrips = 39; 
	if(tccId==84) maxNstrips = 41; 
	if(tccId==85) maxNstrips = 40; 
	if(tccId==86) maxNstrips = 41; 
	if(tccId==87) maxNstrips = 41; 
	if(tccId==88) maxNstrips = 40; 
	if(tccId==89) maxNstrips = 41; 
	if(tccId==90) maxNstrips = 39; 
	if(tccId==91) maxNstrips = 42; 
	if(tccId==92) maxNstrips = 40; 
	if(tccId==93) maxNstrips = 41; 
	if(tccId==94) maxNstrips = 40; 
	if(tccId==95) maxNstrips = 41; 
	if(tccId==96) maxNstrips = 41; 
	if(tccId==97) maxNstrips = 40; 
	if(tccId==98) maxNstrips = 41; 
	if(tccId==99) maxNstrips = 40; 
	if(tccId==100) maxNstrips = 42;
	if(tccId==101) maxNstrips = 40; 
	if(tccId==102) maxNstrips = 41; 
	if(tccId==103) maxNstrips = 40; 
	if(tccId==104) maxNstrips = 41; 
	if(tccId==105) maxNstrips = 41; 
	if(tccId==106) maxNstrips = 40; 
	if(tccId==107) maxNstrips = 41; 
	if(tccId==108) maxNstrips = 40; 

	if(debug) cout << "TCCID=" << tccId << " Number of channels=" << maxNstrips << endl;

	if (tccId<37 || tccId>72)  chMax = maxNstrips+1 ;

	for (int ch=1 ; ch<chMax ; ch++) {
	  in >> hex >> data;
	  if(debug) cout << "reading data for channel= "<<dec<< ch << " " <<hex<<data << endl; //modif-alex 
	  unsigned int bxFirst = ((data >> 16) & 0xfff) ;
	  unsigned int bxLast = (data & 0xfff) ;
	  unsigned int bxLastExpected = bxFirst + 119 ;
	  if(debug) cout <<dec<< "bxFirst="<<bxFirst << " bxLast=" << bxLast << " bxLastExpected=" << bxLastExpected << endl; //modif-alex  
	  if (bxLastExpected >= 3564) bxLastExpected -= 3564 ;
	  if (treat) {
	    //if (bxLastExpected != bxLast) cout<<"ERROR gap length is not 119: tccId="<<tccId
	    //			      <<", channel="<<ch<<", bxFirst="
	    //			      <<bxFirst<<", bxLast="<<bxLast<<", bxLastExpected="<<bxLastExpected<<endl ;
	    //if (bxFirst != bxFirstArray[tccId-1][ch-1] && count>1) {
	    //cout<<"ERROR bxFirst differs from before: tccId="<<tccId
	    //  <<", channel="<<ch<<", bxFirst="
	    //  <<bxFirst<<", bxFirst before="<<bxFirstArray[tccId-1][ch-1]<<endl ;
	    //}
	    h2Gap[tccId-1]->Fill(float(ch), float(bxFirst)) ;
	  }
	  bxFirstArray[tccId-1][ch-1] = bxFirst ;
	}//loop channels
	in >> message;
	if(debug) cout << "Message " << message;
	in >> message;
	if(debug) cout << " " << message << endl;

      }//looping on file
    }//file exist  
  } //loop tccId

  TCanvas * canvEEm ;
  TCanvas * canvEEp ;
  TCanvas * canvEB ;
  TCanvas * canv ; 
  if (tcc<0 && draw) {
    canvEEm = new TCanvas("canvEEm","canvEEm",900,900) ;
    canvEEm->Divide(6,6) ;
    canvEEp = new TCanvas("canvEEp","canvEEp",900,900) ;
    canvEEp->Divide(6,6) ;
    canvEB = new TCanvas("canvEB","canvEB",900,900) ;
    canvEB->Divide(6,6) ;
  }
  
  if (tcc>0) {
    if (zoom>0) h2Gap[tcc-1]->GetYaxis()->SetRangeUser(refbx[tcc-1]-zoom, refbx[tcc-1]+zoom) ;
    else h2Gap[tcc-1]->GetYaxis()->SetRangeUser(0, 3564) ;

    int ref = -1 ;
    int val ;
    for (int bin=1 ; bin<69 ; bin++) {
      val = h2Gap[tcc-1]->GetBinContent(bin,refbx[tcc-1]+1) ;
      //val = h2Gap[tcc-1]->GetBinContent(bin,3484) ; //modif-alex
      if(debug) cout<< "Histo h2Gap content channel=" <<dec<< bin << " value=" << val << endl; //modif-alex 
      if (val > ref) ref = val ;
    }
    
    if(debug) cout << "Ref=" <<dec<< ref << " BxRef=" <<dec<< refbx[tcc-1]+1 << endl;

    TH2F * herror = new TH2F("herror", "herror", 68, 1, 69, 3564,0,3564) ;

    mytest<<tcc;

    for (int bin=1 ; bin<69 ; bin++) {

      //modifying the delays 
      int timedelayb = 1;
      int timedelaya = 1;
      bool modified_delay = false;
      int movebx = 0;

      val = h2Gap[tcc-1]->GetBinContent(bin,refbx[tcc-1]+1) ;
      bool mask(true) ;
      for (int bx = 0 ; bx < 3564 ; bx++) if (h2Gap[tcc-1]->GetBinContent(bin,bx+1) > 0) mask = false ;
      if (val != ref && !mask) { herror->SetBinContent(bin, refbx[tcc-1]+1, 1) ;
	log_error << "ERROR TCCID=" <<dec<< tcc << " channel==" << bin<< endl ;
	cout << "ERROR TCCID=" <<dec<< tcc << " channel==" << bin << endl;

	//modif-alex 01/06/2015 
	int bxm1 = h2Gap[tcc-1]->GetBinContent(bin,refbx[tcc-1]) ;
	int bxp1 = h2Gap[tcc-1]->GetBinContent(bin,refbx[tcc-1]+2) ;
	log_error << "Values around the central BX " << bxm1 << " "  << bxp1<< endl ; 
	cout << "Values around the central BX " << bxm1 << " "  << bxp1 << endl; 

	//int movebx = 0;
	if(bxm1 > val) {cout << "should move by +1 " << refbx[tcc-1]+1 << endl; movebx =  1;
	log_error << "should move by +1 " << refbx[tcc-1]+1<< endl; }
	if(bxp1 > val) {cout << "should move by -1 " << refbx[tcc-1]+1 << endl; movebx = -1;
	 log_error << "should move by -1 " << refbx[tcc-1]+1<< endl;}

	bool change_phase = false;
	if(val != 0)
	  if(abs(ref-bxm1) !=0 || abs(ref-bxp1) !=0)
	    {log_error << "phase problem with channel = " << bin << endl; change_phase = true;
		cout << "phase problem with channel = " << bin<< endl;}

      }//error

      //PRODUCING NEW DELAY FILES 
      delay_ee.clear();
      delay_ee.seekg (0, ios::beg);
      delay_ee.getline(buf,sizeof(buf),'\n');
      while( delay_ee ) {
	std::stringstream sin(buf);
	int tcc_loop;
	sin >> tcc_loop;

	for(unsigned int idee=0; idee<maxNstripsV[tcc]; ++idee){
	  int time_delay = -1;
	  sin >> time_delay;
	  timedelayb = time_delay;
	  if(tcc_loop == tcc) { 
	    if( (idee+1) == bin ) {
	      cout << "---------------------------TCC=" << tcc_loop << " " << tcc << " channel=" 
		   << idee+1 << " time_delay=" << time_delay << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl; 
	      time_delay = time_delay + movebx;
	      if(time_delay<0) time_delay = 0;
	      if(time_delay>4) time_delay = 4;
	      if(timedelayb != time_delay)
		{log_error << "TCC=" << tcc << " bin=" << bin 
		     << " time_delay_before=" << timedelayb 
		     << " time_delay="        << time_delay<< endl ; 
		cout << "TCC=" << tcc << " bin=" << bin 
		     << " time_delay_before=" << timedelayb 
		     << " time_delay="        << time_delay << endl; }
	      timedelaya = time_delay;
	    }//TT
	  }//TCC
	}//loop channel
	delay_ee.getline(buf,sizeof(buf),'\n');
      }//loop delay file EE
    
      if(bin <= 48)
	mytest <<" "<< timedelaya; 

    }//loop towers

    mytest<<"\n" ;
	
    herror->SetMarkerColor(kRed) ;
    herror->SetMarkerStyle(20) ;
    h2Gap[tcc-1]->Draw("text") ;
    herror->Draw("same") ;
  }
  else {

    for (int tccId=1 ; tccId<=108 ; tccId++) {

      cout << "-------------------------------- LOOKING AT TCC=" << tccId << " ----------------------------------------------" << endl; 
      //if (tccId<73) continue ;

      if (zoom>0) h2Gap[tccId-1]->GetYaxis()->SetRangeUser(refbx[tccId-1]-zoom, refbx[tccId-1]+zoom) ;
      else h2Gap[tccId-1]->GetYaxis()->SetRangeUser(0, 3564) ;

      int ref = -1 ;
      int val ;
      for (int bin=1 ; bin<69 ; bin++) {
	val = h2Gap[tccId-1]->GetBinContent(bin,refbx[tccId-1]+1) ;
	if (val > ref) ref = val ;
      }
      
      //cout << "++++++++++reference found " << ref << endl; 
      
      //updating file                                                                                                                                                                                            
      if(tccId>=37 && tccId<73){ //barrel                                                                                                                                                                        
	myfile_ebd<<tccId;
	myfile_ebp<<tccId;}
      else {//endcap                                                                                                                                                                                              
	myfile_eed << tccId;
	myfile_eep << tccId;}
 
      TH2F * herror = new TH2F("herror", "herror", 68, 1, 69, 3564,0,3564) ;
      for (int bin=1 ; bin<69 ; bin++) { //loop on all channels 

	//modifying the delays                                                                                                                                                                          
	int timedelayb = 1;
	int timedelaya = 1;
	int timephaseb = 1;
	int timephasea = 1;

	bool modified_delay = false;
	bool change_phase   = false;
	int  movebx = 0;

	val = h2Gap[tccId-1]->GetBinContent(bin,refbx[tccId-1]+1) ;
	bool mask(true) ;
	for (int bx = 0 ; bx < 3564 ; bx++) if (h2Gap[tccId-1]->GetBinContent(bin,bx+1) > 0) mask = false ;
	if (val != ref && !mask) {
	  herror->SetBinContent(bin, refbx[tccId-1]+1, 1) ;

	  cout<<"error TCC="<<tccId<<" channel="<<bin<<endl ;
	  log_error <<"error TCC="<<tccId<<" channel="<<bin<< endl ;

	  //modif-alex 01/06/2015

	  int bxm1 = h2Gap[tccId-1]->GetBinContent(bin,refbx[tccId-1]) ;
	  int bxp1 = h2Gap[tccId-1]->GetBinContent(bin,refbx[tccId-1]+2) ;
	  cout << "Values around the central BX " << bxm1 << " "  << bxp1 << endl;
	  log_error << "Values around the central BX " << bxm1 << " "  << bxp1<< endl;

	  if(bxm1 > val) {cout << "should move by +1 " << refbx[tccId-1]+1 << endl; movebx =  1;  modified_delay = true;
	  log_error << "should move by +1 " << refbx[tccId-1]+1<< endl;}
	  if(bxp1 > val) {cout << "should move by -1 " << refbx[tccId-1]+1 << endl; movebx = -1;  modified_delay = true;
	  log_error << "should move by -1 " << refbx[tccId-1]+1<< endl;}

	  if(val != 0)
	    if(abs(ref-bxm1) !=0 || abs(ref-bxp1) !=0)
	      {cout << "phase problem with channel = " << bin << endl; change_phase = true;
	      log_error << "phase problem with channel = " << bin<< endl;}
	}//error

        //PRODUCING NEW DELAY FILES FOR THE BARREL -------------------------------------
        delay_eb.clear();
        delay_eb.seekg (0, ios::beg);
        delay_eb.getline(buf,sizeof(buf),'\n');
        while( delay_eb ) {
	  std::stringstream sin(buf);
          int tcc_loop;
          sin >> tcc_loop;
          for(unsigned int ideb=0; ideb<69; ++ideb){
            int time_delay = -1;
            sin >> time_delay;
            timedelayb = time_delay;
            if(tcc_loop == tccId) {
              if( (ideb+1) == bin ) {
                if(debug) cout << "---------------------------------TCC="
			       << tcc_loop << " " << tccId << " channel="
			       << ideb+1 << " time_delay=" << time_delay
			       << "+++++++++++++++++++++++++++++++++++++" << endl;
                time_delay = time_delay + movebx;
                if(time_delay<0) time_delay = 0;
                if(time_delay>4) time_delay = 4;
                if(timedelayb != time_delay)
                  {log_error << "TCC=" << tccId << " bin=" << bin
                       << " time_delay_before=" << timedelayb
                       << " time_delay="        << time_delay<< endl;
                  cout << "TCC=" << tccId << " bin=" << bin
                       << " time_delay_before=" << timedelayb
                       << " time_delay="        << time_delay
                       << endl;}
                timedelaya = time_delay;
                //timedelaya = timedelayb;
              }//TT
            }//TCC
          }//loop channel
          delay_eb.getline(buf,sizeof(buf),'\n');
        }//loop on delays EB 

        //PRODUCING NEW PHASE FILES FOR THE BARREL -------------------------------------
        phase_eb.clear();
        phase_eb.seekg (0, ios::beg);
        phase_eb.getline(buf,sizeof(buf),'\n');
        while( phase_eb ) {
	  std::stringstream sin(buf);
          int tcc_loop;
          sin >> tcc_loop;
          for(unsigned int ipeb=0; ipeb<69; ++ipeb){
            int time_phase = -1;
            sin >> time_phase;
            timephaseb = time_phase;
            if(tcc_loop == tccId) {
              if( (ipeb+1) == bin ) {
                if(debug) cout << "******************************** TCC="
                               << tcc_loop << " " << tccId << " channel="
                               << ipeb+1 << " time_phase=" << time_phase
                               << "*************************************" << endl;
                if(change_phase && !modified_delay){ if(debug) cout << "changing phase" << endl;  
		  //if(modified_delay){ if(debug) cout << "changing phase" << endl;  
		  if(time_phase==0) time_phase = 1;
		  else if(time_phase==1) time_phase = 0;
		  if(debug) cout << timephaseb << " ----" << time_phase << endl; 
		}//switch phase
                if(timephaseb != time_phase)
                  {log_error << "TCC=" << tccId << " bin=" << bin
                       << " time_phase_before=" << timephaseb
                       << " time_phase="        << time_phase
                       << endl;
                  cout << "TCC=" << tccId << " bin=" << bin
                       << " time_phase_before=" << timephaseb
                       << " time_phase="        << time_phase
                       << endl;}
                timephasea = time_phase;
                //timephasea = timephaseb;
              }//TT
            }//TCC
          }//loop channel
          phase_eb.getline(buf,sizeof(buf),'\n');
        }//loop on phases EB                        
	
	//PRODUCING NEW DELAY FILES FOR THE ENDCAP -------------------------------------
	delay_ee.clear();
	delay_ee.seekg (0, ios::beg);
	delay_ee.getline(buf,sizeof(buf),'\n');
	while( delay_ee ) {
	  std::stringstream sin(buf);
	  int tcc_loop;
	  sin >> tcc_loop;
	  for(unsigned int idee=0; idee<maxNstripsV[tccId]; ++idee){
	    int time_delay = -1;
	    sin >> time_delay;
	    timedelayb = time_delay;
	    if(tcc_loop == tccId) {
	      if( (idee+1) == bin ) {
		if(debug) cout << "---------------------------TCC=" 
			       << tcc_loop << " " << tccId << " channel="
			       << idee+1 << " time_delay=" << time_delay 
			       << "+++++++++++++++++++++++++++++++++++++++" << endl;
		time_delay = time_delay + movebx;
		if(time_delay<0) time_delay = 0;
		if(time_delay>4) time_delay = 4;
		if(timedelayb != time_delay)
		  {log_error << "TCC=" << tccId << " bin=" << bin
		       << " time_delay_before=" << timedelayb
		       << " time_delay="        << time_delay 
		       << endl;
		  cout << "TCC=" << tccId << " bin=" << bin
		       << " time_delay_before=" << timedelayb
		       << " time_delay="        << time_delay 
		       << endl;}
		timedelaya = time_delay;
		//timedelaya = timedelayb;
	      }//TT
	    }//TCC
	  }//loop channel
	  delay_ee.getline(buf,sizeof(buf),'\n');
	}//loop on delays EE 


        //PRODUCING NEW PHASE FILES FOR THE ENDCAP  -------------------------------------
        phase_ee.clear();
        phase_ee.seekg (0, ios::beg);
        phase_ee.getline(buf,sizeof(buf),'\n');
        while( phase_ee ) {
	  std::stringstream sin(buf);
          int tcc_loop;
          sin >> tcc_loop;
          for(unsigned int ipee=0; ipee<69; ++ipee){
            int time_phase = -1;
            sin >> time_phase;
            timephaseb = time_phase;
            if(tcc_loop == tccId) {
              if( (ipee+1) == bin ) {
                if(debug) cout << "******************************** TCC="
                               << tcc_loop << " " << tccId << " channel="
                               << ipee+1 << " time_phase=" << time_phase
                               << "*************************************" << endl;
                if(change_phase && !modified_delay) {
		  //if(modified_delay) {
                  if(time_phase==0) time_phase = 1;
                  else if(time_phase==1) time_phase = 0;
                }//switch phase
                if(timephaseb != time_phase)
                  {log_error << "TCC=" << tccId << " bin=" << bin
                       << " time_phase_before=" << timephaseb
                       << " time_phase="        << time_phase
                       << endl;
                  cout << "TCC=" << tccId << " bin=" << bin
                       << " time_phase_before=" << timephaseb
                       << " time_phase="        << time_phase
                       << endl;}
		timephasea = time_phase;
		//timephasea = timephaseb;
              }//TT
            }//TCC
          }//loop channel
          phase_ee.getline(buf,sizeof(buf),'\n');
        }//loop on phases EE

	//updating file 
	if(tccId>=37 && tccId<73){ //barrel  
	  if(bin <= 68) {
	    myfile_ebd <<" "<< timedelaya;
	    myfile_ebp <<" "<< timephasea;}
	  if(bin==68){
	    myfile_ebd <<" ";
	    //myfile_ebp <<" ";
	  }
	} else //endcap
	  if(bin <= 48){
            myfile_eed <<" "<< timedelaya;
            myfile_eep <<" "<< timephasea;}
	
      }//loop channels

      if(tccId>=37 && tccId<73) //barrel                                                                                                                                                                         
	{ myfile_ebd<<"\n" ;
	  myfile_ebp<<"\n" ;}
      else //endcap
	{ myfile_eed<<"\n" ; 
	  myfile_eep<<"\n" ;}

      if(draw){ // DRAWING PLOTS 
      
	if (tccId<37) canv = canvEEm ;
	else if (tccId>=37 && tccId<73) canv = canvEB ;
	else canv = canvEEp ;
	int pad = (tccId%36) ;
	if (pad == 0) pad = 36 ;
	canv->cd(pad) ;
	
	herror->SetMarkerColor(kRed) ;
	herror->SetMarkerStyle(20) ;
	h2Gap[tccId-1]->Draw("text") ;
	herror->DrawCopy("same") ;
	canv->Update() ;
	delete herror ;

      }//drawing plots 

    }//loop TCCs     
  }//show all TCCs

  myfile_ebd.close();
  myfile_ebp.close();
  myfile_eed.close();
  myfile_eep.close();
  mytest.close();
  delay_eb.close();
  delay_ee.close();
  phase_eb.close();
  phase_ee.close();
  log_error.close();
  if(tcc<0) { //option only for all TCCs
    TFile * file = new TFile("gapFlag.root","RECREATE") ;
    for (int tccId=1 ; tccId<=108 ; tccId++) {
      h2Gap[tccId-1]->Write() ;
    }
    file->Close() ;
  }// modif-alex

}


