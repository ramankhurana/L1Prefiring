from PlotTemplates import * 
from ROOT import TFile

## This code runs only for one cut value at once. 
## the cut value can be changed via commandline 
## possible cutvalues are: 2, 4, 6, 8, 10 

import argparse
usage = "run the script using python -c threshold "
parser = argparse.ArgumentParser(description=usage)

parser.add_argument("-c", "--cutval",  dest="cutval", type=int, default=2)
parser.add_argument("-g", "--creategraphs",  action="store_true", dest="creategraphs")
parser.add_argument("-o", "--overlay",  action="store_true", dest="overlay")
parser.add_argument("-m", "--saveMatrix", action="store_true", dest="saveMatrix")

parser.add_argument("-CompareWithDavid", "--CompareWithDavid", action="store_true", dest="CompareWithDavid")

parser.add_argument("-a", "--axis",  dest="axis",default="Y")


args = parser.parse_args()

cutval = str(int(args.cutval))


axis_N=args.axis


def nsd(x):
    return ('{0:1.3g}'.format(x))


## prepare all inputs here

## to be changed for every time 


def CreateGraphs():
    ## will remain almost fixed and hence hardcoded 
    timestep=[-12,-8,-7,-6,-5,-4,0,4,8,12,15,17,18,19,20]
    #timestep=[-12,-8,-4,0,4,8,12]
    timestepstr=["m12","m8","m7","m6", "m5", "m4","nosign0","p4","p8","p12","p15","p17","p18","p19","p20"]
    templaterootstring = 'MC_PhaseShift//PrefiringRateEE_data_FrontTrain__FullReadOut_TIME_cutval_CUT.root' ## template .root file name 
    ratefilename_ = (((templaterootstring.replace("TIME_","")).replace(".root","_"+axis_N+".txt")).replace("PrefiringRateEE","Rate")).replace("CUT",str(cutval))  ## output .txt file with Rate (2,2) matrix
    probfilename_ = ratefilename_.replace("Rate","Prob")  ## output .txt file with Prob
    timescanfilenames=ratefilename_.replace("Rate","rootfilesList")  ## text file which will contain name of input .root file 
    
    ## x and y bin for rate (for normalised histogram)
    xbin_ = 2
    ybin_ = 2
    txtfile = ''
    
    print ratefilename_, probfilename_, timescanfilenames
    
    ##----------##-------------##------------##-------------##-------------##--------------##
    ## create the list of .root files for a given cut value and all time shift values. 
    ##----------##-------------##------------##-------------##-------------##--------------##
    timefilelist=[]
    ftxt=open(timescanfilenames,"w")
    
    for itime in timestep:
        time_=""
        if itime <0: time_="minus"+str(abs(itime))
        if itime ==0: time_="nosign0"
        if itime >0: time_="plus"+str(itime)
        rootfilename_ = (templaterootstring.replace("TIME",time_)).replace("CUT",cutval)
        towrite_  = str(itime) + " " + rootfilename_+" \n"
        ftxt.write(towrite_)
        print time_, cutval, rootfilename_
    ftxt.close()
    
    
    
    ## extract the probability and rate and write them to .txt file
    filename= timescanfilenames
    postfix_="_"+str(xbin_)+"_"+str(ybin_)
    txtfile = ratefilename_
    
    
    
    prefire_prob_=[]
    prefire_prob_e_=[]
    prefire_prob_26_=[]
    prefire_prob_26_e_=[]
    prefire_prob_27_=[]
    prefire_prob_27_e_=[]
    prefire_prob_28_=[]
    prefire_prob_28_e_=[]
    prefire_prob_29_=[]
    prefire_prob_29_e_=[]
    
    outfile = open(txtfile,'w')
    outfile.write("adc prob_t prob_t_e prob_26 prob_26_e prob_27 prob_27_e prob_28 prob_28_e prob_29 prob_29_e \n")
    ielement = 0
    for ifile in open(filename):
        inputfile =  ifile.rstrip('\n').split()[1]
        adcCut    =  ifile.rstrip('\n').split()[0]
        
        tfile_ = TFile(inputfile,'READ')
        

        
        print "reading rootfile", inputfile
        ##-----------
        h2 = tfile_.Get('egidx_ttidx_NonIso_dr_')
        
        
        ## this is to save the 2d normalised matrix histogram for each point. 
        if args.saveMatrix:
            os.system("mkdir plotsSim/matrixN")
            os.system("mkdir plotsSim/matrix")
            
            #saveNormalised2DWithTProfile(tfile_, "2018","plotsSim/matrixN/",  "egidx_ttidx_NonIso_dr_", "bunch crossing index for e-#gamma candidates", "emulator TP index", timestepstr[ielement], False,  cutval+"_"+axis_N)
            saveNormalised2DWithTProfile(tfile_, "2018","plotsSim/matrixN/",  "egidx_ttidx_NonIso_dr_", "bunch crossing index for e-#gamma candidates", "emulator TP index", cutval+"_"+timestepstr[ielement], False,  axis_N)
            savePDF(tfile_, "2018","plotsSim/matrix/",  "egidx_ttidx_NonIso_dr_", "bunch crossing index for e-#gamma candidates", "emulator TP index", timestepstr[ielement]+"_"+ cutval+"_"+axis_N) ## no need to send axis_N as this is not normalised plot
            savePDF(tfile_, "simulation","plotsSim/matrix/",  "idx_vs_ieta_ETP16_IDXAny", "i#eta", "index of max emul energy", timestepstr[ielement]+"_"+ cutval+"_"+axis_N) ## no need to send axis_N as this is not normalised plot
        ielement = ielement +1 
        
        print "------",h2.Integral()
        prefire_prob_.append(NormalizedPrefiringProbability(h2,axis_N)[0])
        prefire_prob_e_.append(NormalizedPrefiringProbability(h2,axis_N)[1])
        
        h2 = NormalizeYAxis(h2,axis_N)
        prob = h2.GetBinContent(xbin_,ybin_)
        prob_e = h2.GetBinError(xbin_,ybin_)
        
        ##-----------
        h2_26 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_26')
        prefire_prob_26_.append(NormalizedPrefiringProbability(h2_26,axis_N)[0])
        prefire_prob_26_e_.append(NormalizedPrefiringProbability(h2_26,axis_N)[1])
        
        h2_26 = NormalizeYAxis(h2_26,axis_N)
        prob_26 = h2_26.GetBinContent(xbin_,ybin_)
        prob_26_e = h2_26.GetBinError(xbin_,ybin_)
        
        ##-----------
        h2_27 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_27')
        prefire_prob_27_.append(NormalizedPrefiringProbability(h2_27,axis_N)[0])
        prefire_prob_27_e_.append(NormalizedPrefiringProbability(h2_27,axis_N)[1])
        
        h2_27 = NormalizeYAxis(h2_27,axis_N)
        prob_27 = h2_27.GetBinContent(xbin_,ybin_)
        prob_27_e = h2_27.GetBinError(xbin_,ybin_)
        print "prob_27_e =", prob_27_e
    
        ##-----------
        h2_28 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_28')
        prefire_prob_28_.append(NormalizedPrefiringProbability(h2_28,axis_N)[0])
        prefire_prob_28_e_.append(NormalizedPrefiringProbability(h2_28,axis_N)[1])
        
        h2_28 = NormalizeYAxis(h2_28,axis_N)
        prob_28 = h2_28.GetBinContent(xbin_,ybin_)
        prob_28_e = h2_28.GetBinError(xbin_,ybin_)
        
        ##-----------
        h2_29 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_29')
        print "h2_29   --- ", h2_29.Integral()
        prefire_prob_29_.append(NormalizedPrefiringProbability(h2_29,axis_N)[0])
        prefire_prob_29_e_.append(NormalizedPrefiringProbability(h2_29,axis_N)[1])
    
    
        h2_29 = NormalizeYAxis(h2_29,axis_N)
        prob_29  = h2_29.GetBinContent(xbin_,ybin_)
        prob_29_e = h2_29.GetBinError(xbin_,ybin_)
        
        towrite = str(adcCut)+' '+str(nsd(prob))+' '+str(nsd(prob_e))+' '+str(nsd(prob_26))+' '+str(nsd(prob_26_e))+' '+str(nsd(prob_27))+' '+str(nsd(prob_27_e))+' '+str(nsd(prob_28))+' '+str(nsd(prob_28_e))+' '+str(nsd(prob_29))+' '+str(nsd(prob_29_e))+'\n'
        print "to write ", towrite
        outfile.write(towrite)
        #h2_28 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_28')
        print ifile
        
    
    outfile.close()
    print "-----------------------------pre fire prob------------"
    print "total = ",prefire_prob_, len(prefire_prob_)
    print "ring 26 = ", prefire_prob_26_, len(prefire_prob_26_)
    print "ring 27 = ", prefire_prob_27_, len(prefire_prob_27_)
    print "ring 28 = ", prefire_prob_28_,len(prefire_prob_28_)
    
    
    adc=timestep
    probfile = open(probfilename_,"w")
    
    probfile.write("adc prob_t prob_t_e prob_26 prob_26_e prob_27 prob_27_e prob_28 prob_28_e prob_29 prob_29_e \n")
    
    print "length of prefire_prob_", len(prefire_prob_), len(adc)
    
    for iele in range(0,len(prefire_prob_)):
        writethis_ = str(adc[iele]) + " " + str(nsd(prefire_prob_[iele])) +" " + str(nsd(prefire_prob_e_[iele])) +" " +  str(nsd(prefire_prob_26_[iele])) + " " + str(nsd(prefire_prob_26_e_[iele])) + " " + str(nsd(prefire_prob_27_[iele])) + " " +  str(nsd(prefire_prob_27_e_[iele])) + " " +str(nsd(prefire_prob_28_[iele])) + " " +  str(nsd(prefire_prob_28_e_[iele])) + " " +str(nsd(prefire_prob_29_[iele])) + " " +str(nsd(prefire_prob_29_e_[iele])) +"\n"
        probfile.write(writethis_)
    
    probfile.close()
    
        
        
    
    
    
    
    ##----------##-------------##------------##-------------##-------------##--------------##
    ## convert the .txt files into TGraphs for plotting later on 
    ##----------##-------------##------------##-------------##-------------##--------------##
    
    TextToGraphTimeScan(probfilename_)
    TextToGraphTimeScan(ratefilename_)
    



def Pseudo_CreateGraphs():
    ## will remain almost fixed and hence hardcoded 
    timestep=[-12,-8,-7,-6,-5,-4,0,4,8,12,15,17,18,19,20]
    #timestep=[-12,-8,-4,0,4,8,12]
    timestepstr=["m12","m8","m7","m6", "m5", "m4","nosign0","p4","p8","p12","p15","p17","p18","p19","p20"]
    templaterootstring = 'MC_PhaseShift//PrefiringRateEE_data_FrontTrain__FullReadOut_TIME_cutval_CUT.root' ## template .root file name 
    ratefilename_ = (((templaterootstring.replace("TIME_","")).replace(".root","_"+axis_N+".txt")).replace("PrefiringRateEE","Pseudo_Rate")).replace("CUT",str(cutval))  ## output .txt file with Rate (2,2) matrix
    probfilename_ = ratefilename_.replace("Rate","Prob")  ## output .txt file with Prob
    timescanfilenames=ratefilename_.replace("Rate","rootfilesList")  ## text file which will contain name of input .root file 
    
    ## x and y bin for rate (for normalised histogram)
    xbin_ = 2
    ybin_ = 2
    txtfile = ''
    
    print ratefilename_, probfilename_, timescanfilenames
    
    ##----------##-------------##------------##-------------##-------------##--------------##
    ## create the list of .root files for a given cut value and all time shift values. 
    ##----------##-------------##------------##-------------##-------------##--------------##
    timefilelist=[]
    ftxt=open(timescanfilenames,"w")
    
    for itime in timestep:
        time_=""
        if itime <0: time_="minus"+str(abs(itime))
        if itime ==0: time_="nosign0"
        if itime >0: time_="plus"+str(itime)
        rootfilename_ = (templaterootstring.replace("TIME",time_)).replace("CUT",cutval)
        towrite_  = str(itime) + " " + rootfilename_+" \n"
        ftxt.write(towrite_)
        print time_, cutval, rootfilename_
    ftxt.close()
    
    
    
    ## extract the probability and rate and write them to .txt file
    filename= timescanfilenames
    postfix_="_"+str(xbin_)+"_"+str(ybin_)
    txtfile = ratefilename_
    
    
    
    prefire_prob_=[]
    prefire_prob_e_=[]
    prefire_prob_26_=[]
    prefire_prob_26_e_=[]
    prefire_prob_27_=[]
    prefire_prob_27_e_=[]
    prefire_prob_28_=[]
    prefire_prob_28_e_=[]
    prefire_prob_29_=[]
    prefire_prob_29_e_=[]
    
    outfile = open(txtfile,'w')
    outfile.write("adc prob_t prob_t_e \n")#prob_26 prob_26_e prob_27 prob_27_e prob_28 prob_28_e prob_29 prob_29_e \n")
    ielement = 0
    for ifile in open(filename):
        inputfile =  ifile.rstrip('\n').split()[1]
        adcCut    =  ifile.rstrip('\n').split()[0]
        
        tfile_ = TFile(inputfile,'READ')
        

        
        print "reading rootfile", inputfile
        ##-----------
        h2 = tfile_.Get('pseudo_egidx_ttidx_NonIso_')
        
        
        ## this is to save the 2d normalised matrix histogram for each point. 
        if args.saveMatrix:
            os.system("mkdir plotsSim/matrixN")
            os.system("mkdir plotsSim/matrix")
            
            saveNormalised2DWithTProfile(tfile_, "2018","plotsSim/matrixN/",  "pseudo_egidx_ttidx_NonIso_", "e-#gamma candidate BX index", "TP BX index", cutval+"_"+timestepstr[ielement], False,  axis_N)
            savePDF(tfile_, "2018","plotsSim/matrix/",  "pseudo_egidx_ttidx_NonIso_", "e-#gamma candidates BX index", "TP BX index", timestepstr[ielement]+"_"+ cutval+"_"+axis_N) ## no need to send axis_N as this is not normalised plot
            
        ielement = ielement +1 
        
        print "------",h2.Integral()
        prefire_prob_.append(NormalizedPrefiringProbability(h2,axis_N)[0])
        prefire_prob_e_.append(NormalizedPrefiringProbability(h2,axis_N)[1])
        
        h2 = NormalizeYAxis(h2,axis_N)
        prob = h2.GetBinContent(xbin_,ybin_)
        prob_e = h2.GetBinError(xbin_,ybin_)
        
        towrite = str(adcCut)+' '+str(nsd(prob))+' '+str(nsd(prob_e))+'\n '
        print "to write ", towrite
        outfile.write(towrite)
        print ifile
        
    
    outfile.close()
    print "-----------------------------pre fire prob------------"
    print "total = ",prefire_prob_, len(prefire_prob_)
    
    adc=timestep
    probfile = open(probfilename_,"w")
    
    probfile.write("adc prob_t prob_t_e  \n")
    
    print "length of prefire_prob_", len(prefire_prob_), len(adc)
    
    for iele in range(0,len(prefire_prob_)):
        writethis_ = str(adc[iele]) + " " + str(nsd(prefire_prob_[iele])) +" " + str(nsd(prefire_prob_e_[iele])) +"\n"
        probfile.write(writethis_)
    
    probfile.close()
    
    
    
    
    ##----------##-------------##------------##-------------##-------------##--------------##
    ## convert the .txt files into TGraphs for plotting later on 
    ##----------##-------------##------------##-------------##-------------##--------------##
    
    PseudoTextToGraphTimeScan(probfilename_)
    PseudoTextToGraphTimeScan(ratefilename_)
    



################ main function ###########################################################################################

#if args.saveMatrix: 
#    SaveMatrix()


if args.creategraphs:
    CreateGraphs()
    print "calling Pseudo_CreateGraphs ----------------------------------------------------------------------------------------------------------------------------------------------------"
    Pseudo_CreateGraphs()

if args.overlay:
    from OverlappingPlots import DrawOverlap
    
    ## overlay rate plots 
    dirname = "MC_PhaseShift/"
    files=['Rate_data_FrontTrain__FullReadOut_cutval_2.root', 'Rate_data_FrontTrain__FullReadOut_cutval_4.root', 'Rate_data_FrontTrain__FullReadOut_cutval_6.root', 'Rate_data_FrontTrain__FullReadOut_cutval_8.root']
    
    files=[dirname+ifile for ifile in files]
    files = [ ifile.replace(".root", "_"+axis_N+".root")   for ifile in files]
    
    print files
    
    legend=['>1 GeV', '>2 GeV', '>3 GeV', '>4 GeV', '>5 GeV' ]
    
    
    xtitle='time offset (in ns)'
    ytitle="true pre-firing rate"
    histoname1=['prob_']
    os.system('mkdir -p plotsSim/Graphs')
    files  = [ifile.replace("Rate_","Prob_")for ifile in files]
    DrawOverlap(files,histoname1,[xtitle,ytitle],legend,'plotsSim/Graphs/timescan_rate_summary_allrings_'+axis_N,[0,1],[200,1000])


    ## overlay prob plots 
    
    
    xtitle='time offset (in ns)'
    ytitle="pre-firing probability"
    histoname1=['prob_']
    legendpos=[0.53, 0.13, 0.93, 0.39]
    x__= 0.6
    y__=0.4
    
    if axis_N=="Y":  
        legendpos=[0.53, 0.13, 0.93, 0.39]
        x__= 0.6
        y__=0.4
    if axis_N=="X":
        #legendpos=[0.35, 0.63, 0.73, 0.83]
        #x__= 0.4
        #y__=0.85
        legendpos=[0.53, 0.13, 0.93, 0.39]
        x__= 0.6
        y__=0.4
        

    DrawOverlap(files,histoname1,[xtitle,ytitle],legend,'plotsSim/Graphs/timescan_prob_summary_allrings_'+axis_N,[0,1],[200,1000], text_="Simulation", x_=x__, y_=y__, legendloc=legendpos)
    
    Pseudo_files = [i.replace("Prob_","Pseudo_Prob_") for i in files]
    DrawOverlap(Pseudo_files,histoname1,[xtitle,ytitle],legend,'plotsSim/Graphs/timescan_pseudo_prob_summary_allrings_'+axis_N,[0,1],[200,1000], text_="Simulation", x_=x__, y_=y__, legendloc=legendpos)

    os.system("rm -rf  /afs/cern.ch/work/k/khurana/public/AnalysisStuff/ECAL/plotsSim/")
    os.system("cp -r plotsSim/ /afs/cern.ch/work/k/khurana/public/AnalysisStuff/ECAL/")



if args.CompareWithDavid:
    from OverlappingPlots import DrawOverlap
    
    ## overlay rate plots 
    dirname = "timescanOutput/"
    files=['Prob_2017data_FrontTrain_cutval_DQMHistDavid.root','Prob_2017data_FrontTrain_cutval_DQMHist.root']
    files=[dirname+ifile for ifile in files]
    
    legend=['From David', 'From Raman']
    
    
    xtitle='time offset (in ns)'
    ytitle="true pre-firing rate"
    histoname1=['noniso_']
    os.system('mkdir -p plotsSim/Graphs')
    DrawOverlap(files,histoname1,[xtitle,ytitle],legend,'plotsSim/Graphs/timescan_ProbComparison_L1TDQM',[0,1],[200,1000])

