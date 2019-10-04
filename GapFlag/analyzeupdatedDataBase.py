import pandas as pd
import sys
import matplotlib.pyplot as plt
from root_pandas import read_root, to_root 
from ROOT import TTree, TH2F, TFile, gStyle
sys.path.append('/afs/cern.ch/work/k/khurana/EXOANALYSIS/CMSSW_9_4_13/src/ExoPieUtils/plottools')
import canvasLib as canvasL
import latexLib as latexL


def makeplotsFromDatabase(filename, latextext):
    df = pd.read_csv(filename,sep=" ",names=["tcc", "tower", "stripInTower", "TCCch", "delay", "phase"])
    
    rootfilename = filename.replace(".dat_out.txt", ".root")
    
    df.to_root(rootfilename)
    
    f = TFile(rootfilename,"READ")
    
    t = f.Get("my_ttree")
    
    ###
    h2_noweight = TH2F("h2_noweight", "h2_noweight", 120, 0,120, 80,0,80)
    c = canvasL.EPCanvas2DLongXColz()
    gStyle.SetPalette(1)
    t.Draw("TCCch:tcc>>h2_noweight","","goff")
    h2_noweight.Draw("colz")
    latexL.EPLatex(latextext)
    histname=h2_noweight.GetName()+"_"+latextext.replace(" ", "_")+"_"+(filename.replace("gapflag_database/","")).replace(".dat_out.txt",".pdf")
    c.SaveAs("plots/"+histname)
    
    
    ### 
    h2_phase = TH2F("h2_phase", "h2_phase", 120, 0,120, 80,0,80)
    c = canvasL.EPCanvas2DLongXColz()
    gStyle.SetPalette(1)
    t.Draw("TCCch:tcc>>h2_phase","1*phase","goff")
    h2_phase.Draw("colz")
    latexL.EPLatex(latextext)
    histname=h2_phase.GetName()+"_"+latextext.replace(" ", "_")+"_"+(filename.replace("gapflag_database/","")).replace(".dat_out.txt",".pdf")
    c.SaveAs("plots/"+histname)


    ### 
    h2_delay = TH2F("h2_delay", "h2_delay", 120, 0,120, 80,0,80)
    c = canvasL.EPCanvas2DLongXColz()
    gStyle.SetPalette(1)
    t.Draw("TCCch:tcc>>h2_delay","1*delay","goff")
    h2_delay.Draw("colz")
    latexL.EPLatex(latextext)
    histname=h2_delay.GetName()+"_"+latextext.replace(" ", "_")+"_"+(filename.replace("gapflag_database/","")).replace(".dat_out.txt",".pdf")
    c.SaveAs("plots/"+histname)

    f_out = TFile("databaseHist.root","UPDATE")
    f_out.cd()
    postfix=latextext.replace(" ", "_")
    n1 = h2_noweight.GetName() + "_" + postfix
    n2 = h2_phase.GetName() + "_" + postfix
    n3 = h2_delay.GetName() + "_" + postfix
    
    h2_noweight.SetName(n1) 
    h2_noweight.Write()
    
    h2_phase.SetName(n2)
    h2_phase.Write()
    
    h2_delay.SetName(n3)
    h2_delay.Write()
    
    f_out.Close()
    
    
    return 0



#dbFileList=["TIM_DATA_CONF_ID_1039.dat_out.txt", "TIM_DATA_CONF_ID_1090.dat.txt", "TIM_DATA_CONF_ID_1192.dat.txt", "TIM_DATA_CONF_ID_1269.dat.txt", "TIM_DATA_CONF_ID_287.dat.txt", "TIM_DATA_CONF_ID_473.dat.txt", "TIM_DATA_CONF_ID_651.dat.txt", "TIM_DATA_CONF_ID_711.dat.txt", "TIM_DATA_CONF_ID_756.dat.txt", "TIM_DATA_CONF_ID_945.dat.txt"]
dbFileList = ["TIM_DATA_CONF_ID_287.dat_out.txt", "TIM_DATA_CONF_ID_473.dat_out.txt", "TIM_DATA_CONF_ID_651.dat_out.txt", "TIM_DATA_CONF_ID_711.dat_out.txt", "TIM_DATA_CONF_ID_756.dat_out.txt", "TIM_DATA_CONF_ID_945.dat_out.txt", "TIM_DATA_CONF_ID_1039.dat_out.txt", "TIM_DATA_CONF_ID_1090.dat_out.txt", "TIM_DATA_CONF_ID_1192.dat_out.txt", "TIM_DATA_CONF_ID_1269.dat_out.txt"]

year_ = ["Feb 2011", "Mar 2012", "Dec 2012", "Jun 2015", "Oct 2015", "Nov 2016", "Oct 2017", "Mar 2018", "Sep 2018", "Dec 2018"]

dbFileList = ["gapflag_database/" + i for i in dbFileList]

idx=0
for filename in dbFileList:
    makeplotsFromDatabase(filename, year_[idx]) 
    
    idx=idx+1

