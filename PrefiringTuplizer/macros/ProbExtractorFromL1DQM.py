##-------##----------##--------##
## This macro uses the 2d histograms which is in the output of the PrefiringEDAnalzyer 
## The binconcent of the histogram in the endcap is used to get the pre-firing prob 
## Author: Raman Khurana
## Date:   21-11-2019
##-------##----------##--------##

import os 
import sys 
from ROOT import TFile
#import PlotTemplates as pltmpls 

import argparse

#filepath="/eos/cms/store/user/khurana//ZeroBias2/crab_prefiringanalysis2017_V4/191104_114219/0000/Merged_ZeroBias2017.root"


##-------##--------##-----------##
##   argument parser 
##-------##--------##-----------##

usage = "run the script using python -i full/path/to/root/file "
parser = argparse.ArgumentParser(description=usage)
parser.add_argument("-i", "--inputfile",  dest="inputfile",default="")
parser.add_argument("-T", "--time",  dest="time",default="-100",type=int)
parser.add_argument("-d", "--isDavidRootFile",  action="store_true", dest="isDavidRootFile")



args = parser.parse_args()

filepath=args.inputfile

if filepath=="": 
    print "provide input file name with full path"
    sys.exit()

##-------##--------##-----------##
##   default values 
##-------##--------##-----------##
y1low=1
y1hi=18

y2low=53
y2hi=68

xbxm1=2
xbx0=3




'''
function to get the sum of binconent of given bins defined by fixed X and range of Y 
'''
def GetIntegral(h2, xbin, ylow, yhi):
    integral_=0.
    for i in range (1,18+1):
        integral_ = integral_ + h2.GetBinContent(xbin, i)
    return integral_
        
    



'''
using the getbincontent sum, calculate the prob 
'''

def GetProb(h_iso):
    integral_iso_m1 = GetIntegral(h_iso, xbxm1, y1low, y1hi) + GetIntegral(h_iso, xbxm1, y2low, y2hi)
    
    integral_iso_0  = GetIntegral(h_iso, xbx0, y1low, y1hi) + GetIntegral(h_iso, xbx0, y2low, y2hi)
    
    probability_ = integral_iso_m1 / (integral_iso_m1 + integral_iso_0 )
    return probability_

f = TFile(filepath)

## default
h_iso = f.Get("ieta_vs_idx_L1Iso")
h_noniso = f.Get("ieta_vs_idx_L1NonIso")

if args.isDavidRootFile:
    if args.time < 0:
        time_ = 'm'+str(abs(int(args.time))) 
    if args.time > 0:
        time_ = 'p'+str(abs(int(args.time))) 
    if args.time == 0:
        time_ = str(abs(int(args.time))) 
        
    histname='egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_'+ time_
    
    h_iso = f.Get(histname)
    h_noniso = f.Get(histname)
    
#print "probability for filepath is :"
print  args.time, GetProb(h_iso), GetProb(h_noniso)


