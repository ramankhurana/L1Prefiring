from ROOT import TGraph, TFile, TGraphAsymmErrors
from array import array
import os


inputstring_ = ['2017'] #zbp
xbin_ = 2
ybin_ = 2

postfix_="_"+str(xbin_)+"_"+str(ybin_)

dirname="timescanOutput/"

filenames=['timescanOutput/Prob_2017data_FrontTrain_cutval_DQMHist.txt']
#filenames=['timescanOutput/Prob_2017data_FrontTrain_cutval_DQMHistDavid.txt']

for filename in filenames:
    #filename = 'probability_scan_ADC_Ring.txt'
    
    f = open(filename,"r").readlines()
    firstLine = f.pop(0) #removes the first line

    
    adc_        =  array('f')
    adc_1       =  array('f')
    adc_2       =  array('f')
    adc_3       =  array('f')
    adc_4       =  array('f')
    
    prob        =  array('f')
    prob_e      =  array('f')
    
    prob_26     =  array('f')
    prob_e_26   =  array('f')
    
    prob_27     =  array('f')
    prob_e_27   =  array('f')
    
    prob_28     =  array('f')
    prob_e_28   =  array('f')

    prob_29     =  array('f')
    prob_e_29   =  array('f')
    
    errx        =  array('f')
    

    for line in f:
        adc_.append(      float(  line.rstrip().split()[0]))
        adc_1.append(      float(  line.rstrip().split()[0]) + 0.1)
        adc_2.append(      float(  line.rstrip().split()[0]) + 0.2)
        adc_3.append(      float(  line.rstrip().split()[0]) + 0.3)
        adc_4.append(      float(  line.rstrip().split()[0]) + 0.4)

        prob.append(      float(  line.rstrip().split()[1]) )
        #prob_e.append(    float(  line.rstrip().split()[2]) )
        
        prob_26.append(   float(  line.rstrip().split()[2]) )
        #prob_e_26.append( float(  line.rstrip().split()[4]) )
        
        
        errx.append(0.0)
        
    #adc_1 = [i+0.1 for i in adc_]
    #adc_2 = [i+0.2 for i in adc_]
    #adc_3 = [i+0.3 for i in adc_]
    #adc_4 = [i+0.4 for i in adc_]

    print adc_1
    
    g_prob_     = TGraphAsymmErrors(int(len(adc_)),   adc_,   prob,     errx, errx, errx,   errx    )   ;  g_prob_.SetName("iso_")
    g_prob_26_  = TGraphAsymmErrors(int(len(adc_1)),   adc_1,   prob_26,  errx, errx, errx, errx )   ;  g_prob_26_.SetName("noniso_")


        
    f1 = TFile(filename.replace('.txt','.root'), 'RECREATE')
    
    g_prob_.Write()
    g_prob_26_.Write()
    f1.Close()



