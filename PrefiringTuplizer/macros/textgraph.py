from ROOT import TGraph, TFile, TGraphAsymmErrors
from array import array
import os


inputstring_ = ['2017'] #zbp
xbin_ = 2
ybin_ = 2

postfix_="_"+str(xbin_)+"_"+str(ybin_)


filenames=['probability_2017_2_2.txt','probability_scan_ADC_Ring.txt']

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
        prob_e.append(    float(  line.rstrip().split()[2]) )
        
        prob_26.append(   float(  line.rstrip().split()[3]) )
        prob_e_26.append( float(  line.rstrip().split()[4]) )
        
        prob_27.append(   float(  line.rstrip().split()[5]) )
        prob_e_27.append( float(  line.rstrip().split()[6]) )
        
        prob_28.append(   float(  line.rstrip().split()[7]) )
        prob_e_28.append( float(  line.rstrip().split()[8]) )
        
        prob_29.append(   float(  line.rstrip().split()[9]) )
        prob_e_29.append( float(  line.rstrip().split()[10]) )
        
        errx.append(0.0)
        
    #adc_1 = [i+0.1 for i in adc_]
    #adc_2 = [i+0.2 for i in adc_]
    #adc_3 = [i+0.3 for i in adc_]
    #adc_4 = [i+0.4 for i in adc_]

    print adc_1
    
    g_prob_     = TGraphAsymmErrors(int(len(adc_)),   adc_,   prob,     errx, errx, prob_e,    prob_e    )   ;  g_prob_.SetName("prob_")
    g_prob_26_  = TGraphAsymmErrors(int(len(adc_1)),   adc_1,   prob_26,  errx, errx, prob_e_26, prob_e_26 )   ;  g_prob_26_.SetName("prob_26_")
    g_prob_27_  = TGraphAsymmErrors(int(len(adc_)),   adc_2,   prob_27,  errx, errx, prob_e_27, prob_e_27 )   ;  g_prob_27_.SetName("prob_27_")
    g_prob_28_  = TGraphAsymmErrors(int(len(adc_)),   adc_3,   prob_28,  errx, errx, prob_e_28, prob_e_28 )   ;  g_prob_28_.SetName("prob_28_")
    g_prob_29_  = TGraphAsymmErrors(int(len(adc_)),   adc_4,   prob_29,  errx, errx, prob_e_29, prob_e_29 )   ;  g_prob_29_.SetName("prob_29_")


        
    f1 = TFile('prob_graphs_'+filename.replace('.txt','.root'), 'RECREATE')
    
    g_prob_.Write()
    g_prob_26_.Write()
    g_prob_27_.Write()
    g_prob_28_.Write()
    g_prob_29_.Write()
    
    f1.Close()



