import os
import sys 
from ROOT import * 


def savegraph(rootfilename, name, ymax=10.0):
    
    
    gStyle.SetOptTitle(0)
    gStyle.SetOptStat(0)
    gROOT.SetBatch(1)
    
    c = TCanvas("c","c",850, 700)
    c.SetLogy(1)
    c.SetLeftMargin(0.12)
    c.SetRightMargin(0.06)
    c.SetBottomMargin(0.10)
    c.SetTopMargin(0.08)
    c.SetGridx(1)
    c.SetGridy(1)
    xbin_ = 2
    ybin_ = 2

    postfix_="_"+str(xbin_)+"_"+str(ybin_)
    
    f = TFile(rootfilename,"read")
    
    
    g_prob_ =  f.Get("prob_")
    g_prob_.SetMarkerStyle(20)
    g_prob_.SetMarkerColor(kBlue)
    g_prob_.SetMarkerSize(1.2)
    g_prob_.SetLineWidth(2)
    g_prob_.SetFillColor(kBlue-9)
    g_prob_.SetLineColor(kBlue-9)
    g_prob_.SetLineColor(kBlue)
    #g_prob_.SetLineStyle(2)
    g_prob_.GetXaxis().SetRangeUser(-10,10)
    g_prob_.GetYaxis().SetRangeUser(0.00001,ymax)
    g_prob_.GetXaxis().SetTitle("time offset (in ns)");
    g_prob_.GetXaxis().SetTitleOffset(1.2)
    g_prob_.GetYaxis().SetTitleSize(0.05)
    g_prob_.GetYaxis().SetTitleFont(42)
    g_prob_.GetYaxis().SetTitle("pre-firing probability"); 
    g_prob_.GetYaxis().SetTitleOffset(1.0)
    g_prob_.GetYaxis().SetNdivisions(505);
    g_prob_.GetXaxis().SetNdivisions(505);
    g_prob_.GetXaxis().SetMoreLogLabels()
    g_prob_.GetXaxis().SetNoExponent(1)
    #g_prob_.Draw("ACP 3")
    g_prob_.Draw("APL")


    g_prob_26_ =  f.Get("prob_26_")
    g_prob_26_.SetMarkerStyle(21)
    g_prob_26_.SetMarkerColor(kCyan+3)
    g_prob_26_.SetMarkerSize(1.2)
    g_prob_26_.SetLineWidth(3)
    g_prob_26_.SetFillColor(kCyan+3)
    g_prob_26_.SetLineColor(kCyan+3)
    g_prob_26_.SetLineColor(kCyan+3)
    g_prob_26_.SetLineStyle(2)
    g_prob_26_.GetXaxis().SetRangeUser(-10,10)
    g_prob_26_.GetYaxis().SetRangeUser(0.00001,ymax)
    g_prob_26_.GetXaxis().SetTitle("time offset (in ns)");
    g_prob_26_.GetXaxis().SetTitleOffset(1.2)
    g_prob_26_.GetYaxis().SetTitleSize(0.05)
    g_prob_26_.GetYaxis().SetTitleFont(42)
    g_prob_26_.GetYaxis().SetTitle("pre-firing probability"); 
    g_prob_26_.GetYaxis().SetTitleOffset(1.0)
    g_prob_26_.GetYaxis().SetNdivisions(505);
    g_prob_26_.GetXaxis().SetNdivisions(505);
    g_prob_26_.GetXaxis().SetMoreLogLabels()
    g_prob_26_.GetXaxis().SetNoExponent(1)
    #g_prob_26_.Draw("ACP 3")
    g_prob_26_.Draw("PLsame")
    
    

    g_prob_27_ =  f.Get("prob_27_")
    g_prob_27_.SetMarkerStyle(22)
    g_prob_27_.SetMarkerColor(kBlack)
    g_prob_27_.SetMarkerSize(1.2)
    g_prob_27_.SetLineWidth(3)
    g_prob_27_.SetFillColor(kBlack)
    g_prob_27_.SetLineColor(kBlack)
    g_prob_27_.SetLineColor(kBlack)
    g_prob_27_.SetLineStyle(2)
    g_prob_27_.GetXaxis().SetRangeUser(-10,10)
    g_prob_27_.GetYaxis().SetRangeUser(0.00001,ymax)
    g_prob_27_.GetXaxis().SetTitle("time offset (in ns)");
    g_prob_27_.GetXaxis().SetTitleOffset(1.2)
    g_prob_27_.GetYaxis().SetTitleSize(0.05)
    g_prob_27_.GetYaxis().SetTitleFont(42)
    g_prob_27_.GetYaxis().SetTitle("pre-firing probability"); 
    g_prob_27_.GetYaxis().SetTitleOffset(1.0)
    g_prob_27_.GetYaxis().SetNdivisions(505);
    g_prob_27_.GetXaxis().SetNdivisions(505);
    g_prob_27_.GetXaxis().SetMoreLogLabels()
    g_prob_27_.GetXaxis().SetNoExponent(1)
    #g_prob_27_.Draw("ACP 3")
    g_prob_27_.Draw("PLsame")
    



    
    g_prob_28_ =  f.Get("prob_28_")
    g_prob_28_.SetMarkerStyle(22)
    g_prob_28_.SetMarkerColor(kRed)
    g_prob_28_.SetMarkerSize(1.2)
    g_prob_28_.SetLineWidth(3)
    g_prob_28_.SetFillColor(kRed)
    g_prob_28_.SetLineColor(kRed)
    g_prob_28_.SetLineColor(kRed)
    g_prob_28_.SetLineStyle(2)
    g_prob_28_.GetXaxis().SetRangeUser(-10,10)
    g_prob_28_.GetYaxis().SetRangeUser(0.00001,ymax)
    g_prob_28_.GetXaxis().SetTitle("time offset (in ns)");
    g_prob_28_.GetXaxis().SetTitleOffset(1.2)
    g_prob_28_.GetYaxis().SetTitleSize(0.05)
    g_prob_28_.GetYaxis().SetTitleFont(42)
    g_prob_28_.GetYaxis().SetTitle("pre-firing probability"); 
    g_prob_28_.GetYaxis().SetTitleOffset(1.0)
    g_prob_28_.GetYaxis().SetNdivisions(505);
    g_prob_28_.GetXaxis().SetNdivisions(505);
    g_prob_28_.GetXaxis().SetMoreLogLabels()
    g_prob_28_.GetXaxis().SetNoExponent(1)
    #g_prob_28_.Draw("ACP 3")
    g_prob_28_.Draw("PLsame")
    
    
    

    
    g_prob_29_ =  f.Get("prob_29_")
    g_prob_29_.SetMarkerStyle(22)
    g_prob_29_.SetMarkerColor(22)
    g_prob_29_.SetMarkerSize(1.2)
    g_prob_29_.SetLineWidth(3)
    g_prob_29_.SetFillColor(22)
    g_prob_29_.SetLineColor(22)
    g_prob_29_.SetLineColor(22)
    g_prob_29_.SetLineStyle(2)
    g_prob_29_.GetXaxis().SetRangeUser(-10,10)
    g_prob_29_.GetYaxis().SetRangeUser(0.00001,ymax)
    g_prob_29_.GetXaxis().SetTitle("time offset (in ns)");
    g_prob_29_.GetXaxis().SetTitleOffset(1.2)
    g_prob_29_.GetYaxis().SetTitleSize(0.05)
    g_prob_29_.GetYaxis().SetTitleFont(42)
    g_prob_29_.GetYaxis().SetTitle("pre-firing probability"); 
    g_prob_29_.GetYaxis().SetTitleOffset(1.0)
    g_prob_29_.GetYaxis().SetNdivisions(505);
    g_prob_29_.GetXaxis().SetNdivisions(505);
    g_prob_29_.GetXaxis().SetMoreLogLabels()
    g_prob_29_.GetXaxis().SetNoExponent(1)
    g_prob_29_.Draw("PLsame")
    
    
    

    leg = TLegend(.50, .731, .90, .890);
    if ybin_==2: leg = TLegend(.20, .731, .60, .890);
    if ybin_==3: leg = TLegend(.50, .331, .90, .530);
    
    leg.SetFillColor(0);
    #leg.SetShadowColor(0);
    leg.SetTextFont(42);
    leg.SetTextSize(0.023);
    leg.SetBorderSize(0);
    leg.SetNColumns(2);
    
    leg.AddEntry(g_prob_, "EE all #eta rings", "P");
    leg.AddEntry(g_prob_26_, "#eta ring 17-26", "P");
    leg.AddEntry(g_prob_27_, "#eta ring 27", "P");
    leg.AddEntry(g_prob_28_, "#eta ring 28", "P");
    leg.AddEntry(g_prob_29_, "#eta ring 27-28", "P");
    
    leg.Draw("same")
    

    
    latex =  TLatex();
    latex.SetNDC();
    latex.SetTextSize(0.04);
    latex.SetTextAlign(31);
    latex.SetTextAlign(11);
    latex.DrawLatex(0.14, 0.93, "CMS Internal               phase scan (2018)");
    
    c.SaveAs(name+".png")
    c.SaveAs(name+".pdf")
    
    

rootfilename = ["timescanOutput/Prob_2017data_FrontTrain_cutval_10.root", "timescanOutput/Prob_2017data_FrontTrain_cutval_2.root", "timescanOutput/Prob_2017data_FrontTrain_cutval_4.root", "timescanOutput/Prob_2017data_FrontTrain_cutval_6.root", "timescanOutput/Prob_2017data_FrontTrain_cutval_8.root"]
pdfname = [(ir.replace(".root","")).replace("timescanOutput/","timescanOutput/plots/") for ir in rootfilename]
ymax=[0.3, 1.0]
for i in range(len(rootfilename)):
    savegraph(rootfilename[i],pdfname[i])
