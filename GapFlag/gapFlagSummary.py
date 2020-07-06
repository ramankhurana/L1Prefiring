import os 
from ROOT import TH1F, TH2F, TFile, gStyle
import sys
import numpy
sys.path.append('/afs/cern.ch/work/k/khurana/EXOANALYSIS/CMSSW_9_4_13/src/ExoPieUtils/plottools')
import canvasLib as canvasL
import latexLib as latexL
import pandas
inputdir="gapflagStudies/"

june18=True
jan2020=True
rootfiles=[]
timeshift=[]

#if june18:
if not june18:
    era_="june"
    Era="June"
    timeshift=[-6, -4, -2, 0, 2, 4, 6]

if not june18:
    era_="sept"
    Era="Sept"
    timeshift=[-5, -4, -3, -2, -1, 0, 1, 2, 3]

if jan2020:
    era_='jan'
    Era='Jan'
    timeshift=[-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12]


#gapFlag_ts_jan_2020_m01ns.root

timeshifts=[str(itime).replace("-","m") if itime < 0 else  "p"+str(itime)for itime in timeshift]
timeshifts=[itime.replace("p0","0") for itime in timeshifts]

rootfiles=["gapFlag_ts_"+era_+"_2020_"+ itime + "ns.root" for itime in timeshifts]

print rootfiles


rootfilename=[inputdir+ifile for ifile in rootfiles]

print rootfilename


debug_ = False
ref_bx_EB = 1501 ## earlier it was 1501 for 2018 data
ref_bx_EE = 3470## earlier it was 3470 for 2018 data

#y_total   = 40


rootfout = TFile("gapFlag_errorFrac.root","UPDATE")



ybinMax = []
for i in range(109): ybinMax.append(68)


df_ecalParam = pandas.read_csv("EcalTPGParam_merged.csv",delimiter=" ")

def whichRing(tcc, tccCh):
    df_ring_skim = df_ecalParam[ (df_ecalParam['tcc']==tcc)& (df_ecalParam['TCCch']==tccCh) ]
    if len(numpy.array(df_ring_skim.eta_ring))>0:
        return numpy.array(df_ring_skim.eta_ring)[0]

df_ecalParam_barrel = pandas.read_csv("EcalTPGParam_forGapFlag_barrel.csv",delimiter=" ")

def whichTCCslot(tcc, tccCh):
    df_skim = df_ecalParam_barrel[ (df_ecalParam_barrel['tcc']==tcc)& (df_ecalParam_barrel['TCCch']==tccCh) ]
    if len(numpy.array(df_skim.TCCslot))>0:
        return numpy.array(df_skim.TCCslot)[0]


def whichCrate(tcc, tccCh):
    df_skim = df_ecalParam_barrel[ (df_ecalParam_barrel['tcc']==tcc)& (df_ecalParam_barrel['TCCch']==tccCh) ]
    if len(numpy.array(df_skim.crate))>0:
        return numpy.array(df_skim.crate)[0]



def PlotGapFlagErrorSummary(filename,histname, time):
    
    allprobfile=open("allptobfile_"+histname+".csv","w")
    allprobfile.write("tcc TCCch eta_ring prob time \n")

    allprobfile_barrel=open("allptobfile_barrel_"+histname+".csv","w")
    allprobfile_barrel.write("tcc TCCch TCCslot crate prob time \n")

    histname     =  histname.replace("gapFlag","gapFlag_errorFrac")
    histnameprob = "prob_"+histname
    h1 = TH1F(histnameprob, histnameprob, 108,0.5,108.5)
    h2 = TH2F(histname,histname,108,0.5,108.5, 70, 0.5, 70.5)
    isbarrel = True
    fin = TFile(filename)
    for ih in range(37,109):
        hin_name = ("h_"+str(ih))
        hin = fin.Get(hin_name)
        if ((ih > 36) and (ih < 73)): isbarrel =  True
        if ((ih <= 36) or (ih >= 73)): isbarrel = False
        
        if ( debug_ and isbarrel): print "inside barrel", ih
        if (debug_ and (not isbarrel)): print "inside endcap", ih
        
        
        off_sum = 0.0  ## count the number of enteries which are not in reference BX. This will be helpful to get the pre-firing prob for a given TCC.
        xy_total = 0.0 
        allprobfile_list=[]
        allprobfile_list_barrel=[]
        for ibinX in range(1,hin.GetNbinsX()+1):
        #for ibinX in range(1,43):
            y_sum = 0.0
            binRlo = 0
            binRhi = 4500 
            if isbarrel: 
                binRlo = 1480
                binRhi = 1520

            if not isbarrel: 
                binRlo = 3450
                binRhi = 3490


            #for ibinY in range(1,hin.GetNbinsY()+1):
            y_total = 0.0 
            for ibinY in range(binRlo, binRhi+1):
                y_total = y_total + hin.GetBinContent(ibinX, ibinY)
                #if hin.GetBinContent(ibinX, ibinY) > 0: print "bin content: ", ibinX, ibinY, hin.GetBinContent(ibinX, ibinY)
                ''' just skip if it is reference ''' 
                if  (not isbarrel) and (ibinY == ref_bx_EE): continue 
                if  (isbarrel) and (ibinY == ref_bx_EB): continue 
                
                ''' sum the content other than refernce bx '''
                y_sum = y_sum + hin.GetBinContent(ibinX, ibinY)
                if ih==100: print "ih, ibinX, ibinY",ih, ibinX, ibinY, hin.GetBinContent(ibinX, ibinY)
                
            off_sum = off_sum + y_sum
            xy_total = xy_total + y_total ## this is basically the integral of the 2d histogram.
            ## err frac calculated after summing over Y loop 
            err_frac = 0.0
            if y_total > 0: err_frac = y_sum / y_total 
            allprobfiletext=""
            if not isbarrel:
                allprobfiletext = str(ih) + " " + str(ibinX) + " " + str(whichRing(ih, ibinX)) + " " + str(err_frac) + " " + str(time)
                if whichRing(ih, ibinX) == None: continue 
                allprobfile_list.append(allprobfiletext)

            if isbarrel:
                TCCslot = whichTCCslot(ih, ibinX)
                crate   = whichCrate(ih, ibinX)
                allprobfiletext = str(ih) + " " + str(ibinX) + " " + str(TCCslot) + " " + str(crate)+ " "+str(err_frac) + " " + str(time)
                #if whichRing(ih, ibinX) == None: continue 
                allprobfile_list_barrel.append(allprobfiletext)

            if debug_: print "err_frac for ",ibinX, " is: ",err_frac
            if err_frac > 0.0: 
                #print ih, ibinX, err_frac
                h2.SetBinContent(ih, ibinX, err_frac)
                
                
        print "ih, off_sum, xy_total: ", ih, off_sum, xy_total
        tcc_prob = off_sum / xy_total 
        #print 'err_frac, tcc_prob: ', err_frac, tcc_prob
        h1.SetBinContent(ih,tcc_prob)
        for iline in allprobfile_list:
            allprobfile.write(iline+"\n")
        for iline in allprobfile_list_barrel:
            allprobfile_barrel.write(iline+"\n")
    return [h2,h1]

def SaveSummary():
    for ifile in range(len(rootfilename)): 
        print "--------- calling summary for ", rootfilename[ifile]
        h_out = PlotGapFlagErrorSummary(rootfilename[ifile], rootfiles[ifile].replace(".root",""), timeshift[ifile])
        print "PlotGapFlagErrorSummary work is now finished"
        rootfout.cd()
        for ih in h_out: ih.Write()


def PDFSummary(histname, timeid):
    print "histo", histname
    c = canvasL.EPCanvas2DLongXColz()
    gStyle.SetPalette(1)
    fin = TFile("gapFlag_errorFrac.root","READ")
    h2 = fin.Get(histname)
    h2.Draw("colz")
    h2.GetXaxis().SetTitle("TCC Id")
    h2.GetYaxis().SetTitle("Channel #")
    
    latextext="Gap Flag data                                            "+Era+" 2018"
    latexL.EPLatex(latextext)
    
    latexL.EPLatex(timeid, 0.48, 0.8)
    
    c.SaveAs("plots/"+histname+".pdf")
    print "will work here"



def MisFireProbability(probf,ihname):
    prob_EB=0.0
    prob_EE=0.0
    n_EB=0
    n_EE=0
    h_prob_tcc_ = probf.Get(ihname)
    for ibinX in range(1,h_prob_tcc_.GetNbinsX()+1):
        if ((ibinX > 36) and (ibinX < 73)): 
            isbarrel =  True
            prob_EB = prob_EB + h_prob_tcc_.GetBinContent(ibinX)
            n_EB=n_EB+1
            
        if ((ibinX <= 36) or (ibinX >= 73)): 
            isbarrel = False
            prob_EE = prob_EE + h_prob_tcc_.GetBinContent(ibinX)
            n_EE=n_EE+1
        
    #print n_EB, n_EE, prob_EB, prob_EE
    avg_prob_EB = prob_EB/n_EB
    avg_prob_EE = prob_EE/n_EE
    
    return [avg_prob_EB,avg_prob_EE]
        

import histLib  as histL


def SaveTimeSummary(histogram, axistitle, histparam, time):
    c = canvasL.EPCanvas(0)
    hist = histL.Set1DHistParameters(histogram,histparam)    
    hist.GetXaxis().SetTitle(axistitle[0])
    hist.GetYaxis().SetTitle(axistitle[1])
    hist.Draw("HIST")
    print "saving pdf for ",hist.GetName()
    
    latexText=time
    latexL.EPLatex(latexText, 0.25, 0.80)
    c.SaveAs("plots/"+Era+hist.GetName()+".pdf")
    
    
print "------- Now calling save sumnmary ------ "

## to save summary plots in the rootfile 
SaveSummary()


print "going to sleep for 5 sec"
os.system("sleep 5")
## to save summmary plots in pdf format 



os.system("mkdir plots")


allhistnames=["gapFlag_errorFrac_ts_"+era_+"_2020_"+ itime +"ns" for itime in timeshifts]

print "allhistnames: ",allhistnames

print "------- Now calling save sumnmary in PDF files ------ "

index_=0
for ih in allhistnames:
    c = canvasL.EPCanvas(1)
    print "now saving: ",ih, timeshifts[index_]
    PDFSummary(ih, timeshifts[index_])
    index_=index_+1



## to save the final result in pdf form, use the histogram from rootfile, hardcoded names, 

#probhistnames=["prob_gapFlag_errorFrac_ts_"+era_+"_2018_"+itime+"ns" for itime in timeshifts]
probhistnames=["prob_gapFlag_errorFrac_ts_"+era_+"_2020_"+itime+"ns" for itime in timeshifts]


probrootfilename = "gapFlag_errorFrac.root" 


xlow_ = -7
xhi_  =  7
nbins=7

if june18: 
    nbins=7
    xlow_ = -7
    xhi_  =  7
if not june18: 
    nbins=9
    xlow_ = -5.5
    xhi_  =  3.5

if jan2020: 
    nbins=25
    xlow_ = -12.5
    xhi_ = 12.5

h_final_prob_EB = TH1F("h_final_prob_EB", "h_final_prob_EB", nbins, xlow_, xhi_)
h_final_prob_EE = TH1F("h_final_prob_EE", "h_final_prob_EE", nbins, xlow_, xhi_)


print "------- Now calling save probability summary ------ "

probf = TFile(probrootfilename)
ibin=1
for ihname in probhistnames:
    misfire_prob = MisFireProbability(probf, ihname)
    print "getting avg prob for", ihname, misfire_prob
    h_final_prob_EB.SetBinContent(ibin,misfire_prob[0])
    h_final_prob_EE.SetBinContent(ibin,misfire_prob[1])
    fout = TFile("gapFlag_probvstiming.root","RECREATE")
    fout.cd()
    
    ibin=ibin+1


h_final_prob_EB.Write()
h_final_prob_EE.Write()






import histLib  as histL 

## printing the 1-d summary plots for EE and EB
c = canvasL.EPCanvas(1)

#import histLib  as histL
## ENDCAP
h_final_prob_EE = histL.Set1DHistParameters(h_final_prob_EE, [0.0001, 10, 20, 1.10, 2, 1])
h_final_prob_EE.Draw("PC")
h_final_prob_EE.GetXaxis().SetTitle("time shift (ns)")
h_final_prob_EE.GetYaxis().SetTitle("mis-firing probability")
latexText="Gap Flag data                                    "+Era+" 2018"
latexL.EPLatex(latexText)

latexL.EPLatex("EE (probability averaged over all TCCs)", 0.25, 0.80 )
pdfname=h_final_prob_EE.GetName()
c.SaveAs("plots/"+Era+pdfname+".pdf")

## BARREL
h_final_prob_EB = histL.Set1DHistParameters(h_final_prob_EB, [0.00001, 10, 20, 1.10, 2, 1])
h_final_prob_EB.Draw("PC")
h_final_prob_EB.GetXaxis().SetTitle("time shift (ns)")
h_final_prob_EB.GetYaxis().SetTitle("mis-firing probability")
latexText="Gap Flag data                                     "+Era+" 2018"
latexL.EPLatex(latexText)

latexL.EPLatex("EB (probability averaged over all TCCs)", 0.25, 0.80 )
pdfname=h_final_prob_EB.GetName()
c.SaveAs("plots/"+Era+pdfname+".pdf")




## printing 1-d summary plot, one for each time shift point. all TCC in same plots, summed over all the channels in a given TCC. 
fsummary = TFile("gapFlag_errorFrac.root")
histname_time = "prob_gapFlag_errorFrac_ts_jan_2020_TIMEns"

for itime in timeshifts:
    print histname_time.replace("TIME",itime)
        
    h_time = fsummary.Get(histname_time.replace("TIME",itime))
    
    SaveTimeSummary(h_time, ["TCC #","mis-firing probability"], [0.0,1.1,20, 1.10, 2, 1], itime)
