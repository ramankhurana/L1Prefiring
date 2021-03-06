# In this at the end of fitlatexlevector I am putting the dirname
# so loop over n-1 files and n will give the name of the output dir.

# In legend also the n element will give the name for the ratio plot y axis label.
#edited by Monika Mittal 
#Script for ratio plot 
import sys

import ROOT 
ROOT.gROOT.SetBatch(True)
sys.argv.append( '-b-' )


from ROOT import TFile, TH1F, gDirectory, TCanvas, TPad, TProfile,TGraph, TGraphAsymmErrors
from ROOT import TH1D, TH1, TH1I
from ROOT import gStyle
from ROOT import gROOT
from ROOT import TStyle
from ROOT import TLegend
from ROOT import TMath
from ROOT import TPaveText
from ROOT import TLatex

import os
colors=[1,2,4,5,8,9,11,41,46,30,12,28,20,32]
markerStyle=[23,21,22,20,24,25,26,27,28,29,20,21,22,23]            
linestyle=[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]


def DrawOverlap(fileVec, histVec, titleVec,legendtext,pngname,logstatus=[0,0],xRange=[-99999,99999,1],text_="",x_=0.5,y_=0.5,legendloc=[0.53, 0.13, 0.93, 0.39]):

    gStyle.SetOptTitle(0)
    gStyle.SetOptStat(0)
    #gStyle.SetTitleOffset(1.1,"Y");
    #gStyle.SetTitleOffset(0.9,"X");
    gStyle.SetLineWidth(3)
    gStyle.SetFrameLineWidth(3); 

    i=0

    histList_=[]
    histList=[]
    histList1=[]
    maximum=[]
    
    ## Legend    
    legpos = legendloc
    leg = TLegend(legpos[0], legpos[1],legpos[2],legpos[3])
    leg.SetBorderSize(0)
    leg.SetNColumns(2)
    leg.SetLineColor(1)
    leg.SetLineStyle(1)
    leg.SetLineWidth(1)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetTextFont(42)
    leg.SetTextSize(0.049)
    
    from PlotTemplates import myCanvas1D
    c=myCanvas1D()
    c.SetLogy(logstatus[1])
    c.SetLogx(logstatus[0])
    #c.SetBottomMargin(0.15)
    #c.SetLeftMargin(0.15)
    
    #c1_2 = TPad("c1_2","newpad",0.04,0.13,1,0.994)
    #c1_2.Draw()

    
    print ("you have provided "+str(len(fileVec))+" files and "+str(len(histVec))+" histograms to make a overlapping plot" )
    print "opening rootfiles"
    c.cd()
    #c1_2.SetBottomMargin(0.013)
    #c1_2.SetLogy(logstatus[1])
    #c1_2.SetLogx(logstatus[0])
    
    
    #c1_2.cd()
    ii=0    
    inputfile={}
    print str(fileVec[(len(fileVec)-1)])

    for ifile_ in range(len(fileVec)):
        print ("opening file  "+fileVec[ifile_])
        inputfile[ifile_] = TFile( fileVec[ifile_] )
        print "fetching histograms"
        for ihisto_ in range(len(histVec)):
            print ("printing histo "+str(histVec[ihisto_]))
            histo = inputfile[ifile_].Get(histVec[ihisto_])
            #status_ = type(histo) is TGraphAsymmErrors
            histList.append(histo)
            # for ratio plot as they should nt be normalize 
            histList1.append(histo)
            #print histList[ii].Integral()
            #histList[ii].Rebin(xRange[2])
            #histList[ii].Scale(1.0/histList[ii].Integral())
            maximum.append(histList[ii].GetMaximum())
            maximum.sort()
            ii=ii+1

    print histList
    for ih in range(len(histList)):
        tt = type(histList[ih])
        if logstatus[1] is 1 :
            histList[ih].SetMaximum(100) #1.4 for log
            histList[ih].SetMinimum(0.00001) #1.4 for log
        if logstatus[1] is 0 :
            histList[ih].SetMaximum(1.4) #1.4 for log
            histList[ih].SetMinimum(0.001) #1.4 for log
#        print "graph_status =" ,(tt is TGraphAsymmErrors)
#        print "hist status =", (tt is TH1D) or (tt is TH1F)
        if ih == 0 :      
            if tt is TGraphAsymmErrors : 
                histList[ih].Draw("APL")
            if (tt is TH1D) or (tt is TH1F) or (tt is TH1) or (tt is TH1I) :
                histList[ih].Draw("hist")   
        if ih > 0 :
            #histList[ih].SetLineWidth(2)
            if tt is TGraphAsymmErrors : 
                histList[ih].Draw("PL same")
            if (tt is TH1D) or (tt is TH1F) or (tt is TH1) or (tt is TH1I) :
                histList[ih].Draw("hist same")   

        if tt is TGraphAsymmErrors :
            histList[ih].SetMaximum(10) 
            histList[ih].SetMarkerColor(colors[ih])
            histList[ih].SetLineColor(colors[ih])
            histList[ih].SetMarkerStyle(markerStyle[ih])
            histList[ih].SetMarkerSize(1)
            leg.AddEntry(histList[ih],legendtext[ih],"PL")
        if (tt is TH1D) or (tt is TH1F) or (tt is TH1) or (tt is TH1I) :
            histList[ih].SetLineStyle(linestyle[ih])
            histList[ih].SetLineColor(colors[ih])
            histList[ih].SetLineWidth(3)
            leg.AddEntry(histList[ih],legendtext[ih],"L")
        histList[ih].GetYaxis().SetTitle(titleVec[1])
        histList[ih].GetYaxis().SetTitleSize(0.052)
        histList[ih].GetYaxis().SetTitleOffset(1.08)
        histList[ih].GetYaxis().SetLabelSize(.052)
        histList[ih].GetXaxis().SetRangeUser(xRange[0],xRange[1])
        histList[ih].GetXaxis().SetLabelSize(0.052);
        histList[ih].GetXaxis().SetTitle(titleVec[0])
        histList[ih].GetXaxis().SetLabelSize(0.052)
        histList[ih].GetXaxis().SetTitleSize(0.052)
        histList[ih].GetXaxis().SetTitleOffset(1.14)
        #histList[ih].GetXaxis().SetTickLength(0.07)
        histList[ih].GetXaxis().SetNdivisions(508)
        from PlotTemplates import SetCMSAxis
        histList[ih] = SetCMSAxis(histList[ih], 1.0, 1.15)
        #histList[ih].GetXaxis().SetMoreLogLabels(); 
        #histList[ih].GetXaxis().SetNoExponent();
        #histList[ih].GetTGaxis().SetMaxDigits(3);

        i=i+1
    '''
    pt = TPaveText(0.0877181,0.9,0.9580537,0.96,"brNDC")
    pt.SetBorderSize(0)
    pt.SetTextAlign(12)
    pt.SetFillStyle(0)
    pt.SetTextFont(22)
    pt.SetTextSize(0.046)
    text = pt.AddText(0.2,0.5,"CMS Internal")
    '''
    from PlotTemplates import drawenergy1D
    pt_ = drawenergy1D(False)
    for ipt in pt_: ipt.Draw()

    '''
    if len(text_) >0:
        ltx = TLatex()
        ltx.SetTextFont(42)
        ltx.SetTextSize(0.049)
        #text_f = "#font[42]{Phase Scan}"
        ltx.DrawTextNDC(x_,y_,text_)
    '''
    
    from PlotTemplates import ExtraText
    text_ex  = ExtraText(text_,x_,y_)
    text_ex.Draw()
    
    ExtraText("ECAL Endcaps",0.4,0.85)
    ltx_ = TLatex()
    ltx_.SetTextFont(42)
    ltx_.SetTextSize(0.049)
    ltx_.DrawLatexNDC(0.32,0.81,"L1 e-#gamma object p_{T} > 10 GeV")


    #text_ex.Draw()
    #pt = TPaveText(0.0877181,0.9,0.9580537,0.96,"brNDC")
    #text = pt.AddText(0.65,0.5,"Phase Scan data #sqrt{s} = 13 TeV (2018)")
    #pt.Draw()
   
    

    #    t2a = TPaveText(0.0877181,0.81,0.9580537,0.89,"brNDC")
    #    t2a.SetBorderSize(0)
    #    t2a.SetFillStyle(0)
    #    t2a.SetTextSize(0.040) 
    #    t2a.SetTextAlign(12)
    #    t2a.SetTextFont(62)
    #    histolabel1= str(fileVec[(len(fileVec)-1)])
    #    text1 = t2a.AddText(0.06,0.5,"CMS Internal") 
    #    t2a.Draw()
    leg.SetHeader("Matched TP energy")
    leg.Draw()
#
#    c.cd()
    outputdirname = './'
    histname=outputdirname+pngname 
    c.SaveAs(histname+'.png')
    c.SaveAs(histname+'.pdf')
#    outputname = 'cp  -r '+ outputdirname +' /afs/hep.wisc.edu/home/khurana/public_html/'
#    os.system(outputname) 
    



####print "calling the plotter"
####files=['Rate_2017data_FrontTrain_cutval_2.root','Rate_2017data_FrontTrain_cutval_4.root','Rate_2017data_FrontTrain_cutval_6.root','Rate_2017data_FrontTrain_cutval_8.root','Rate_2017data_FrontTrain_cutval_10.root']
####legend=['>2ADC', '>4ADC', '>6ADC', '>8ADC', '>10ADC' ]
####
####
####ytitle='time offset (in ns)'
####
####histoname1=['prob_']
####DrawOverlap(files,histoname1,["pre-firing probability",ytitle],legend,'timescan_rate_summary_allrings',[0,1],[200,1000])
#####DrawOverlap(files,histoname2,['E_{T}^{Miss}[GeV]',ytitle],legend,'SR_TT_abc')
####
