#!/usr/bin/env python
# coding: utf-8

# In[1]:


import os 
import sys 
from ROOT import TH2, TFile 
import time 
import math 

is2017 = True 
filename = ''

if is2017: filename = 'files2017.txt'
if not is2017: filename = 'files2018.txt'

def NormalizeYAxis(h2,axis_N="Y"):
    h2_new = h2.Clone()
    h2_new.SetDirectory(0)
    TH2.AddDirectory(0)
    
    if axis_N == "Y":
        for ibx in range(1, h2.GetNbinsX()+1):
            verticalsum = 0.0 
            for iby in range(1, h2.GetNbinsY()+1):
                verticalsum = verticalsum + h2.GetBinContent(ibx, iby)
                #print 'old bin content = ',ibx, iby,  h2.GetBinContent(ibx, iby)
            
            # once the sum is calculated this has to be used to scaling each bin content in the X bin i.e. 
            # divide each bin content by verticalsum 
            # following is outside the for loop of iby, create another loop for the Y axis. 
            for iby_ in range (1, h2.GetNbinsY()+1):
                new_content = 0.0 
                old_content = h2.GetBinContent(ibx, iby_)
                # safety check to avoid divide by zero. 
                if verticalsum != 0: new_content = old_content / verticalsum
                h2_new.SetBinContent(ibx, iby_, new_content)

                
                
                ## error calculation  
                error_ = 0.0 
                if verticalsum !=0:
                    delta_a  = math.sqrt(verticalsum) / verticalsum 
                    delta_b = 0.0
                    
                    if old_content > 0.0: delta_b  = math.sqrt(old_content) / old_content
                    error_ =  new_content * (delta_a + delta_b)
                h2_new.SetBinError(ibx,iby_, error_)
                h2_new.SetDirectory(0)
                TH2.AddDirectory(0)
                

                
             
    if axis_N == "X":
        for iby in range(1, h2.GetNbinsY()+1):
            verticalsum = 0.0 
            for ibx in range(1, h2.GetNbinsX()+1):
                verticalsum = verticalsum + h2.GetBinContent(ibx, iby)
                #print 'old bin content = ',ibx, iby,  h2.GetBinContent(ibx, iby)

            ## same as above but now normalised over X
            for ibx_ in range (1, h2.GetNbinsX()+1):
                new_content = 0.0 
                old_content = h2.GetBinContent(ibx_, iby)
                # safety check to avoid divide by zero. 
                if verticalsum != 0: new_content = old_content / verticalsum
                h2_new.SetBinContent(ibx_, iby, new_content)


    return h2_new


def NormalizedPrefiringProbability(h2,axis_N="Y"):
    h2_new = h2.Clone()
    h2_new.SetDirectory(0)
    TH2.AddDirectory(0)
    
    Vsum_=[]
    if axis_N == "Y":
        for ibx in range(1, h2.GetNbinsX()+1):
            verticalsum = 0.0 
            for iby in range(1, h2.GetNbinsY()+1):
                verticalsum = verticalsum + h2.GetBinContent(ibx, iby)
                #print 'old bin content = ',ibx, iby,  h2.GetBinContent(ibx, iby)
            Vsum_.append(verticalsum)
            
    print "Vsum =", Vsum_
    prob_ = Vsum_[1]/(Vsum_[1]+Vsum_[2]) 
    print "prob = ", prob_
    return prob_ 


txtfile = ''

xbin_ = 2
ybin_ = 3

postfix_="_"+str(xbin_)+"_"+str(ybin_)
if is2017: txtfile = 'probability_2017'+postfix_+'.txt'
if not is2017: txtfile = 'probability_2018'+postfix_+'.txt'

print "file name = ",txtfile
prefire_prob_=[]
prefire_prob_26_=[]
prefire_prob_27_=[]
prefire_prob_28_=[]
prefire_prob_29_=[]





outfile = open(txtfile,'w')
for ifile in open(filename):
    inputfile =  ifile.rstrip('\n').split()[1]
    adcCut    =  ifile.rstrip('\n').split()[0]
    
    tfile_ = TFile(inputfile,'READ')
    
    h2 = tfile_.Get('egidx_ttidx_NonIso_dr_')
    prefire_prob_.append(NormalizedPrefiringProbability(h2))
    
    h2 = NormalizeYAxis(h2,'Y')
    prob = h2.GetBinContent(xbin_,ybin_)
    prob_e = h2.GetBinError(xbin_,ybin_)
    
    h2_26 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_26')
    prefire_prob_26_.append(NormalizedPrefiringProbability(h2_26))
    
    h2_26 = NormalizeYAxis(h2_26,'Y')
    prob_26 = h2_26.GetBinContent(xbin_,ybin_)
    prob_26_e = h2_26.GetBinError(xbin_,ybin_)
    
    h2_27 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_27')
    #prefire_prob_27_.append(NormalizedPrefiringProbability(h2_27))
    
    h2_27 = NormalizeYAxis(h2_27,'Y')
    prob_27 = h2_27.GetBinContent(xbin_,ybin_)
    prob_27_e = h2_27.GetBinError(xbin_,ybin_)
    
    h2_28 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_28')
    #prefire_prob_28_.append(NormalizedPrefiringProbability(h2_28))
    
    h2_28 = NormalizeYAxis(h2_28,'Y')
    prob_28 = h2_28.GetBinContent(xbin_,ybin_)
    prob_28_e = h2_28.GetBinError(xbin_,ybin_)

    h2_29 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_29')
    prefire_prob_29_.append(NormalizedPrefiringProbability(h2_29))


    
    towrite = str(adcCut)+' '+str(prob)+' '+str(prob_e)+' '+str(prob_26)+' '+str(prob_26_e)+' '+str(prob_27)+' '+str(prob_27_e)+' '+str(prob_28)+' '+str(prob_28_e)+'\n'
    print "to write ", towrite
    outfile.write(towrite)
    #h2_28 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_28')
    print ifile
    

outfile.close()
print "-----------------------------pre fire prob------------"
print "total = ",prefire_prob_
print "ring 26 = ", prefire_prob_26_
print "ring 27 = ", prefire_prob_27_
print "ring 28 = ", prefire_prob_28_


adc=[2,4,6,8,10]

probfile = open("probability_scan_ADC_Ring.txt","w")
for iele in range(0,len(prefire_prob_)):
    writethis_ = str(adc[iele]) + " " + str(prefire_prob_[iele]) + " " +  str(prefire_prob_26_[iele]) + " " +  str(prefire_prob_27_[iele]) + " " +  str(prefire_prob_28_[iele]) + " " +  str(prefire_prob_29_[iele]) "\n"
     
#    writethis_ = str(adc[iele]) + " " + str(prefire_prob_[iele]) + " " +  str(prefire_prob_26_[iele]) + " " +  str(prefire_prob_29_[iele]) + "\n"
    print "write = ", writethis_

    probfile.write(writethis_)
probfile.close()

    

'''


import numpy as np

import pandas as pd

data = pd.read_csv('probability_scan_ADC_Ring.txt', sep=" ", header=None)
data.columns = ["adc", "All","R26","R27","R28"]

#print data['adc']
#print data['prob']
import numpy as np
import matplotlib.pyplot as plt

plt.plot(data['adc'], data['All'],"r+", label="all rings")
plt.plot(data['adc'], data['R26'],"b^", label="ring <27")
plt.plot(data['adc'], data['R27'],"go", label="ring 27")
plt.plot(data['adc'], data['R28'],"m*",label="ring 28")
plt.legend(loc='upper right')

plt.show()
plt.savefig("temp.pdf")
'''
