from pandas import  DataFrame, concat, Series, read_csv
from ROOT import TCanvas, TColor, TGaxis, TH1F, TPad, TFile, TGraphAsymmErrors,TLatex,TLine,gStyle,TLegend,gROOT
import sys
sys.path.append('../PrefiringTuplizer/macros/')
from PlotTemplates import myCanvas1D, ExtraText, SetCMSAxis, drawenergy1D, SetLegend

gStyle.SetLegendBorderSize(0)
gROOT.SetBatch(1)


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
    #c1.SetTickx(0)
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
     f=TFile('profiles.root')

     hist1 = f.Get('SelectedDataFrames_Histo_L1Prefiring_p17ns')
     hist2 = f.Get('SelectedDataFrames_Histo_L1Prefiring_m17ns')
     hist3 = f.Get('SelectedDataFrames_Histo_L1Prefiring_0ns')
     # histogram_base = TH1F("histogram_base", "", 1000, 0, 1000.)
     
     
     
     
     
     hist3.SetMarkerColor(2)
     hist3.SetLineColor(2)
     hist3.SetMarkerSize(0.5*2)
     hist3.SetMarkerStyle(20)
     hist3 = SetCMSAxis(hist3,yoffset=1.1)
     hist3.GetXaxis().SetTitle("time sample")
     hist3.GetYaxis().SetTitle("<ADC>")
     hist3.Draw('CP')
     

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
     


     pt = drawenergy1D(True,text_="Simulation",data=False)
     for ipt in pt: ipt.Draw()
     leg.AddEntry(hist2_1,'-17 ns','PC')
     leg.AddEntry(hist3,'0 ns','PC')
     leg.AddEntry(hist1_1,'+17 ns','PC')
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
