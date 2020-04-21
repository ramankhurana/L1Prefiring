from pandas import  DataFrame, concat, Series, read_csv
from ROOT import TCanvas, TColor, TGaxis, TH1F, TPad, TFile, TGraphAsymmErrors,TLatex,TLine,gStyle,TLegend,gROOT, TF1, TGraph, TMath, TGaxis
import sys
import ROOT
sys.path.append('../PrefiringTuplizer/macros/')
from PlotTemplates import myCanvas1D, ExtraText, SetCMSAxis, drawenergy1D, SetLegend

gStyle.SetLegendBorderSize(0)
gROOT.SetBatch(1)

''' Fit tutorila using 
http://www.nbi.dk/~petersen/Teaching/Stat2013/Week1/RootIntro.py
'''

from array import array
def fitAlphaBeta(x, par):
    trise = par[0];
    tmax  = par[1];
    a     = par[2];
    amp   = par[3];

    term1 = (x[0] - (tmax - trise)) /(trise+0.001);
    term2 = (x[0] - tmax)/(trise+0.001);
    
    pi = 3.14;
    f = 0;
    
    if( x[0] > (tmax - trise) ):
        f = amp * pow( term1, a) * TMath.Exp(-a*term2);
    else:
        f = 0;
        
    return f





f = TFile("profiles.root","UPDATE")
def PrintTProfileData(csvfilename):
    histname = csvfilename.replace(".csv","")
    
    h = TH1F(histname, histname, 10,0.5,10.5)

    print "-----------------------------------------------------------------------------------------"
    print "  CSV_file_name                             bin_number  mean     rms "
    df = read_csv(csvfilename)
    df_out=DataFrame(columns=['adc'])
    
    for adc in zip(df.adc):
        adcList =  adc[0].replace("[","").replace("]","").split(",")
        ## this will create a new dataframe which has only adc values as a list. 
        df_out= df_out.append({'adc':adcList}, ignore_index=True)
        
    mean_adc=[]
    rms_adc=[]
    for i in range(0,10):
        '''
        df_out['adc'] : this will give the set of 10 values for each row
        df_out['adc'].str[i] : this will give you ith column from the list. 
        df_out['adc'].str[i]).astype(float) : since we read from a text file, 
        it is a string, we convert it into a float. For each row this is extracted and 
        a array/vector/series is formed. so all the information for each row for the the ith element in the ADC list is present here. 
        ((df_out['adc'].str[i]).astype(float)).mean(): take  the mean of ith datasamples 
        '''
        print csvfilename, i, ((df_out['adc'].str[i]).astype(float)).mean(), ((df_out['adc'].str[i]).astype(float)).std()
        h.SetBinContent(i+1,((df_out['adc'].str[i]).astype(float)).mean())
        #h.SetBinError(i+i,((df_out['adc'].str[i]).astype(float)).std())
        h.SetBinError(i+1,0.)
        
        #mean_adc.append(((df_out['adc'].str[i]).astype(float)).mean())
        #rms_adc.append(((df_out['adc'].str[i]).astype(float)).std())
    #mean_adc=[imean / max(mean_adc) for imean in mean_adc]
    #rms_adc =[irms / max(mean_adc) for irms in rms_adc]
    
    #for i in range(0,10):
        #h.SetBinContent(i+1,mean_adc[i])
        #h.SetBinError(i+i,rms_adc[i])
    
    f.cd()
    h.Write()
        
        


''' following code is for drawing the histogram overlay for three cases ''' 

def getLegend():
    legend=TLegend(.10,.79,.47,.89)
    legend.SetTextSize(0.038)
    legend.SetFillStyle(0)

    return legend

def getLatex():
    latex =  TLatex()
    latex.SetNDC();
    latex.SetTextSize(0.04);
    latex.SetTextAlign(31);
    latex.SetTextAlign(11);
    return latex

def SetCanvas():

    # CMS inputs                                                                                                                                                                                            
    # -------------                                                                                                                                                                                         
    H_ref = 1000;
    W_ref = 1000;
    W = W_ref
    H  = H_ref

    T = 0.08*H_ref
    B = 0.21*H_ref
    L = 0.12*W_ref
    R = 0.08*W_ref
    # --------------                                                                                                                                                                                        

    c1 = TCanvas("c2","c2",0,0,2000,1500)
    c1.SetFillColor(0)
    c1.SetBorderMode(0)
    c1.SetFrameFillStyle(0)
    c1.SetFrameBorderMode(0)
    c1.SetLeftMargin( L/W )
    c1.SetRightMargin( R/W )
    c1.SetTopMargin( T/H )
    c1.SetBottomMargin( B/H )
    c1.SetTickx(0)
    #c1.SetTicky(0)
    c1.SetTickx(1)
    c1.SetTicky(1)
    c1.SetGridy()
    c1.SetGridx()
    #c1.SetLogy(1)                                                                                                                                                                                          
    return c1

def Histplot():

     leg=SetLegend()
     latex=getLatex()
     #c=SetCanvas()
     c=myCanvas1D()
     c.SetTicky(1)
     f=TFile('profiles.root')

     hist1 = f.Get('SelectedDataFrames_Histo_L1Prefiring_p17ns')
     hist2 = f.Get('SelectedDataFrames_Histo_L1Prefiring_m17ns')
     hist3 = f.Get('SelectedDataFrames_Histo_L1Prefiring_0ns')
     # histogram_base = TH1F("histogram_base", "", 1000, 0, 1000.)
     
     
     for i in range(1,11): hist1.SetBinContent(i, (hist1.GetBinContent(i)-200.)) 
     for i in range(1,11): hist2.SetBinContent(i,(hist2.GetBinContent(i)-200.)) 
     for i in range(1,11): hist3.SetBinContent(i,(hist3.GetBinContent(i)-200.))

     den1 = hist1.GetBinContent(5)
     den2 = hist2.GetBinContent(7)
     den3 = hist3.GetBinContent(6)
     
     print "den1, den2, den3: ",den1, den2, den3
     for i in range(1,11): hist1.SetBinContent(i, (hist1.GetBinContent(i)/ den1)) 
     for i in range(1,11): hist2.SetBinContent(i,(hist2.GetBinContent(i) / den2)) 
     for i in range(1,11): hist3.SetBinContent(i,(hist3.GetBinContent(i) / den3))

     for i in range(1,11): 
         if hist1.GetBinContent(i) < 0.: hist1.SetBinContent(i, 0.0)
     for i in range(1,11):
         if hist2.GetBinContent(i) < 0.: hist2.SetBinContent(i,0.0) 
     for i in range(1,11): 
         if hist3.GetBinContent(i) < 0.: hist3.SetBinContent(i,0.0)
     
     for i in range(1,11): print hist1.GetBinContent(i), hist2.GetBinContent(i), hist3.GetBinContent(i)
          
     
     ##-------------------------------------------------------------------------------------------------------------
     
     
     Ndata = 10
     x3  = array( 'f', [0.0]*Ndata ) 
     y3  = array( 'f', [0.0]*Ndata ) 
     for i in range(0,10):
         
         x3[i] = i+1
         y3[i] = hist3.GetBinContent(i+1)
     print x3, y3
     
     Graph_3 = TGraph(Ndata, x3, y3)
     
     
     Graph_3.SetMarkerStyle(20)
     Graph_3.SetLineWidth(1)
     Graph_3.SetMarkerColor(2)
     
     Graph_3 = SetCMSAxis(Graph_3,yoffset=1.1)
     #Graph_3.GetXaxis().SetRangeUser(-5,5)
     Graph_3.GetXaxis().SetTitle("bunch crossing (25 ns)")
     Graph_3.GetYaxis().SetTitle("<ADC>")
     #Graph_3.GetXaxis().SetTickSize(0.1)
     
     for i in range(1,11,1):
         binIndex = Graph_3.GetXaxis().FindBin(i)
         print "binindex = ",binIndex
         #Graph_3.GetXaxis().SetBinLabel(binIndex,"%d"% (i-6))
         Graph_3.GetXaxis().SetNdivisions(511)
         label_ = str(i-6)
         #Graph_3.GetXaxis().ChangeLabel(i,0,0.057,4,1,42, label_ )
         Graph_3.GetXaxis().ChangeLabel(i,-1,0.057,-1,-1,-1, label_)
         Graph_3.GetXaxis().SetLabelOffset(0.012)
         

         
     ROOT.gPad.Modified()
     ROOT.gPad.Update()
     
        
         #Graph_3.
     
     Graph_3.Draw("AP")                  
     
     func_3 = TF1 ("fitf3" ,fitAlphaBeta, 1, 10, 4)
     func_3.SetLineColor(2)
     
     
     func_3.SetParLimits(0,1,5);
     func_3.SetParLimits(1,4,6.5 );
     
     func_3.SetParLimits(2,0,5 );
     func_3.SetParLimits(3,0.8,1.2);
     c.SetTicky(1)
     
     
     Graph_3.Fit("fitf3")
     #####

     Ndata = 10
     x1  = array( 'f', [0.0]*Ndata ) 
     y1  = array( 'f', [0.0]*Ndata ) 
     for i in range(0,10):
         
         x1[i] = i+1
         y1[i] = hist1.GetBinContent(i+1)
     print x1, y1
     
     Graph_1 = TGraph(Ndata, x1, y1)
     
     
     Graph_1.SetMarkerStyle(20)
     Graph_1.SetLineWidth(1)
     Graph_1.SetMarkerColor(1)
     Graph_1.Draw("Psame")                  
     
     func_1 = TF1 ("fitf1" ,fitAlphaBeta, 1, 10, 4)
     func_1.SetLineColor(1)
     func_1.SetParLimits(0,2,4);
     func_1.SetParLimits(1,4,7 );
     func_1.SetParLimits(2,0,4 );
     func_1.SetParLimits(3,0.99,1.01);
     
     Graph_1.Fit("fitf1")
     #####


     Ndata = 10
     x2  = array( 'f', [0.0]*Ndata ) 
     y2  = array( 'f', [0.0]*Ndata ) 
     for i in range(0,10):
         
         x2[i] = i+1
         y2[i] = hist2.GetBinContent(i+1)
     print x2, y2
     
     Graph_2 = TGraph(Ndata, x2, y2)
     
     
     Graph_2.SetMarkerStyle(20)
     Graph_2.SetLineWidth(1)
     Graph_2.SetMarkerColor(4)
     Graph_2.Draw("Psame")                  
     
     func_2 = TF1 ("fitf2" ,fitAlphaBeta, 1, 10, 4)
     func_2.SetLineColor(4)
     func_2.SetParLimits(0,3,5);
     func_2.SetParLimits(1,5,8 );
     func_2.SetParLimits(2,0,5 );
     func_2.SetParLimits(3,0.8,1.2);
     
     Graph_2.Fit("fitf2")
     
     #axis1 =  TGaxis(0.,0.,11.,0.,-5,4, 511,"");
     #axis1.SetLabelSize(0)
     #axis1.Draw()

     ##--------------------------------------------------------------------------------------------------------------
     
     
     '''
     hist3.SetMarkerColor(2)
     hist3.SetLineColor(2)
     hist3.SetMarkerSize(0.5*2)
     hist3.SetMaximum(1.2)
     hist3.SetMarkerStyle(20)
     hist3 = SetCMSAxis(hist3,yoffset=1.1)
     hist3.GetXaxis().SetTitle("time sample")
     hist3.GetYaxis().SetTitle("<ADC>")
     hist3.Draw('P')
     
     

     hist2.SetMarkerColor(4)
     hist2.SetLineColor(4)
     hist2.SetMarkerSize(0.5*2)
     hist2.SetMarkerStyle(20)
     hist2.Draw('Psame')

     
     hist1.SetStats(0)
     hist1.GetXaxis().SetTitle("time sample")
     hist1.GetYaxis().SetTitle("<ADC>")
     hist1.SetMarkerColor(1)
     hist1.SetLineColor(1)
     hist1.SetMarkerStyle(20)
     hist1.SetMarkerSize(0.5*2)
     hist1.Draw('Psame')

     
     '''
     
     '''
     hist3_1 = TH1F("hist3_1", "hist3_1", 7,3.5,10.5)
     for i in range(1,8): hist3_1.SetBinContent(i,hist3.GetBinContent(i+3))
     hist3_1.SetTitle("")
     hist3_1.SetStats(0)
     hist3_1.SetMaximum(650)
     hist3_1.GetXaxis().SetTitle("time sample")
     hist3_1.GetYaxis().SetTitle("<ADC>")
     hist3_1.SetMarkerColor(2)
     hist3_1.SetLineColor(2)
     hist3_1.SetMarkerStyle(20)
     hist3_1.SetMarkerSize(0.5*2)
     #hist3_1 = SetCMSAxis(hist3_1,yoffset=1.1)
     hist3_1.Draw('PCsame')
     


     hist3_2 = TH1F("hist3_2", "hist3_2", 3,0.5,3.5)
     for i in range(1,4): hist3_2.SetBinContent(i,hist3.GetBinContent(i))
     hist3_2.SetTitle("")
     hist3_2.SetStats(0)
     hist3_2.SetMaximum(650)
     hist3_2.GetXaxis().SetTitle("time sample")
     hist3_2.GetYaxis().SetTitle("<ADC>")
     hist3_2.SetMarkerColor(2)
     hist3_2.SetLineColor(2)
     hist3_2.SetMarkerStyle(20)
     hist3_2.SetMarkerSize(0.5*2)
     #hist3_2 = SetCMSAxis(hist3_2,yoffset=1.1)
     hist3_2.Draw('Psame')
     '''

     
     
     '''
     hist2_1 = TH1F("hist2_1", "hist2_1", 7,3.5,10.5)
     for i in range(1,8): hist2_1.SetBinContent(i,hist2.GetBinContent(i+3))
     hist2_1.SetMarkerColor(4)
     hist2_1.SetLineColor(4)
     hist2_1.SetMarkerSize(0.5*2)
     hist2_1.SetMarkerStyle(20)
     hist2_1.Draw('PCsame')

     hist2_2 = TH1F("hist2_2", "hist2_2", 4,0.5,4.5)
     for i in range(1,8): hist2_2.SetBinContent(i,hist2.GetBinContent(i))
     hist2_2.SetMarkerColor(4)
     hist2_2.SetLineColor(4)
     hist2_2.SetMarkerSize(0.5*2)
     hist2_2.SetMarkerStyle(20)
     hist2_2.Draw('PCsame')
     '''
     
     

     
     '''
     hist1_1 = TH1F("hist1_1", "hist1_1", 8,2.5,10.5)
     for i in range(1,9): hist1_1.SetBinContent(i,hist1.GetBinContent(i+2))
     hist1_1.SetTitle("")
     hist1_1.SetStats(0)
     hist1_1.SetMaximum(650)
     hist1_1.GetXaxis().SetTitle("time sample")
     hist1_1.GetYaxis().SetTitle("<ADC>")
     hist1_1.SetMarkerColor(1)
     hist1_1.SetLineColor(1)
     hist1_1.SetMarkerStyle(20)
     hist1_1.SetMarkerSize(0.5*2)
     #hist1_1 = SetCMSAxis(hist1_1,yoffset=1.1)
     hist1_1.Draw('PCsame')
     


     hist1_2 = TH1F("hist1_2", "hist1_2", 3,0.5,3.5)
     for i in range(1,4): hist1_2.SetBinContent(i,hist1.GetBinContent(i))
     hist1_2.SetTitle("")
     hist1_2.SetStats(0)
     hist1_2.SetMaximum(650)
     hist1_2.GetXaxis().SetTitle("time sample")
     hist1_2.GetYaxis().SetTitle("<ADC>")
     hist1_2.SetMarkerColor(1)
     hist1_2.SetLineColor(1)
     hist1_2.SetMarkerStyle(20)
     hist1_2.SetMarkerSize(0.5*2)
     #hist1_2 = SetCMSAxis(hist1_2,yoffset=1.1)
     hist1_2.Draw('PCsame')
     
     '''

     pt = drawenergy1D(True,text_="Simulation Work in progress",data=False)
     for ipt in pt: ipt.Draw()
     leg.AddEntry(Graph_2,'+17 ns','PC')
     leg.AddEntry(Graph_3,'0 ns','PC')
     leg.AddEntry(Graph_1,'-17 ns','PC')
     leg.Draw()
     ExtraText("ECAL",0.225,0.65)
     ExtraText("Endcaps",0.20,0.6)

     #
     # txt = 'Path: HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned'
     # texcms = AddText(txt)
     # texcms.Draw("same")
     #
     c.SaveAs('pulseshapeShift.pdf')




if __name__ == "__main__":
    PrintTProfileData("SelectedDataFrames_Histo_L1Prefiring_p17ns.csv")
    PrintTProfileData("SelectedDataFrames_Histo_L1Prefiring_m17ns.csv")
    PrintTProfileData("SelectedDataFrames_Histo_L1Prefiring_0ns.csv")
    
    f.Close()
    Histplot()
    import os
    os.system("cp pulseshapeShift.pdf /afs/cern.ch/work/k/khurana/public/AnalysisStuff/ECAL/Plots2017_FrontTrain/")
