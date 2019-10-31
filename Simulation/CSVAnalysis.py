from pandas import  DataFrame, concat, Series, read_csv
from ROOT import TCanvas, TColor, TGaxis, TH1F, TPad, TFile, TGraphAsymmErrors,TLatex,TLine,gStyle,TLegend,gROOT

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
        h.SetBinError(i+i,((df_out['adc'].str[i]).astype(float)).std())
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
    c1.SetTicky(0)
    c1.SetTickx(1)
    c1.SetTicky(1)
    c1.SetGridy()
    c1.SetGridx()
    #c1.SetLogy(1)                                                                                                                                                                                          
    return c1

def Histplot():


     leg=getLegend()
     latex=getLatex()
     c=SetCanvas()
     f=TFile('profiles.root')

     hist1 = f.Get('SelectedDataFrames_Histo_L1Prefiring_p17ns')
     hist2 = f.Get('SelectedDataFrames_Histo_L1Prefiring_m17ns')
     hist3 = f.Get('SelectedDataFrames_Histo_L1Prefiring_0ns')
     # histogram_base = TH1F("histogram_base", "", 1000, 0, 1000.)
     hist1.SetTitle("")
     hist1.SetStats(0)
     
          
     
     #histogram_base.SetMinimum(0.0)
     #hist1.SetMaximum(1.2)
     
     hist1.GetXaxis().SetTitle("time sample")
     hist1.GetYaxis().SetTitle("<ADC>")
     
     hist1.SetMarkerColor(1)
     hist1.SetLineColor(1)
     
     hist2.SetMarkerColor(4)
     hist2.SetLineColor(4)
     
     hist3.SetMarkerColor(2)
     hist3.SetLineColor(2)
     
     hist1.SetMarkerSize(2)
     hist2.SetMarkerSize(2)
     hist3.SetMarkerSize(2)
     
     hist1.SetMarkerStyle(20)
     hist2.SetMarkerStyle(20)
     hist3.SetMarkerStyle(20)
     
     hist1.Draw('E')
     hist2.Draw('Esame')
     hist3.Draw('Esame')


     leg.AddEntry(hist3,'0 ns','L')
     leg.AddEntry(hist2,'-17 ns','L')
     leg.AddEntry(hist1,'+17 ns','L')
     leg.Draw()
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
