import os 
from ROOT import TH1F, TH2F, TFile, gStyle
import sys
sys.path.append('/afs/cern.ch/work/k/khurana/EXOANALYSIS/CMSSW_9_4_13/src/ExoPieUtils/plottools')
import canvasLib as canvasL
import latexLib as latexL
inputdir="gapflagStudies/"

june18=True

rootfiles=[]
timeshift=[]

if june18:
    era_="june"
    Era="June"
    timeshift=[-6, -4, -2, 0, 2, 4, 6]

if not june18:
    era_="sept"
    Era="Sept"
    timeshift=[-5, -4, -3, -2, -1, 0, 1, 2, 3]

timeshifts=[str(itime).replace("-","m") if itime < 0 else  "p"+str(itime)for itime in timeshift]
timeshifts=[itime.replace("p0","0") for itime in timeshifts]

rootfiles=["gapFlag_ts_"+era_+"_2018_"+ itime + "ns.root" for itime in timeshifts]

print rootfiles


rootfilename=[inputdir+ifile for ifile in rootfiles]



debug_ = False
ref_bx_EB = 1501
ref_bx_EE = 3470
y_total   = 10


rootfout = TFile("gapFlag_errorFrac.root","UPDATE")

def PlotGapFlagErrorSummary(filename,histname):
    
    histname     =  histname.replace("gapFlag","gapFlag_errorFrac")
    histnameprob = "prob_"+histname
    h1 = TH1F(histnameprob, histnameprob, 108,0.5,108.5)
    h2 = TH2F(histname,histname,108,0.5,108.5, 70, 0.5, 70.5)
    isbarrel = True
    fin = TFile(filename)
    for ih in range(1,109):
        hin_name = ("h_"+str(ih))
        hin = fin.Get(hin_name)
        if ((ih > 36) and (ih < 73)): isbarrel =  True
        if ((ih <= 36) or (ih >= 73)): isbarrel = False
        
        if ( debug_ and isbarrel): print "inside barrel", ih
        if (debug_ and (not isbarrel)): print "inside endcap", ih
        
        
        off_sum = 0.0  ## count the number of enteries which are not in reference BX. This will be helpful to get the pre-firing prob for a given TCC.
        xy_total = 0.0 
        for ibinX in range(1,hin.GetNbinsX()+1):
            y_sum = 0.0
            for ibinY in range(1,hin.GetNbinsY()+1):
                #if hin.GetBinContent(ibinX, ibinY) > 0: print "bin content: ", ibinX, ibinY, hin.GetBinContent(ibinX, ibinY)
                ''' just skip if it is reference ''' 
                if  (not isbarrel) and (ibinY == ref_bx_EE): continue 
                if  (isbarrel) and (ibinY == ref_bx_EB): continue 
                
                ''' sum the content other than refernce bx '''
                y_sum = y_sum + hin.GetBinContent(ibinX, ibinY)
            off_sum = off_sum + y_sum
            xy_total = xy_total + y_total ## this is basically the integral of the 2d histogram.
            ## err frac calculated after summing over Y loop 
            err_frac = y_sum / y_total 
            tcc_prob = off_sum / xy_total 
            
            if debug_: print "err_frac for ",ibinX, " is: ",err_frac
            if err_frac > 0.0: 
                print ih, ibinX, err_frac
                h2.SetBinContent(ih, ibinX, err_frac)

            h1.SetBinContent(ih,tcc_prob)
                
    return [h2,h1]

def SaveSummary():
    for ifile in range(len(rootfilename)): 
        print "--------- calling summary for ", rootfilename[ifile]
        h_out = PlotGapFlagErrorSummary(rootfilename[ifile], rootfiles[ifile].replace(".root",""))
        rootfout.cd()
        for ih in h_out: ih.Write()


def PDFSummary(histname):
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
        



## to save summary plots in the rootfile 
SaveSummary()


print "going to sleep for 60 sec"
os.system("sleep 60")
## to save summmary plots in pdf format 



os.system("mkdir plots")


allhistnames=["gapFlag_errorFrac_ts_"+era_+"_2018_"+ itime +"ns" for itime in timeshifts]

for ih in allhistnames:
    PDFSummary(ih)




## to save the final result in pdf form, use the histogram from rootfile, hardcoded names, 

probhistnames=["prob_gapFlag_errorFrac_ts_"+era_+"_2018_"+itime+"ns" for itime in timeshifts]


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


h_final_prob_EB = TH1F("h_final_prob_EB", "h_final_prob_EB", nbins, xlow_, xhi_)
h_final_prob_EE = TH1F("h_final_prob_EE", "h_final_prob_EE", nbins, xlow_, xhi_)


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



c = canvasL.EPCanvas(1)

import histLib  as histL 
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
h_final_prob_EB = histL.Set1DHistParameters(h_final_prob_EB, [0.0001, 10, 20, 1.10, 2, 1])
h_final_prob_EB.Draw("PC")
h_final_prob_EB.GetXaxis().SetTitle("time shift (ns)")
h_final_prob_EB.GetYaxis().SetTitle("mis-firing probability")
latexText="Gap Flag data                                     "+Era+" 2018"
latexL.EPLatex(latexText)

latexL.EPLatex("EB (probability averaged over all TCCs)", 0.25, 0.80 )
pdfname=h_final_prob_EB.GetName()
c.SaveAs("plots/"+Era+pdfname+".pdf")



