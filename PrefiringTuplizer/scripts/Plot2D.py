import os 
import sys 
import ROOT 

c = ROOT.TCanvas()
#c.Draw()
#lxplus728
fin = ROOT.TFile("/eos/cms/store/user/khurana/ZeroBias2/crab_prefiringanalysis2017_V1/190510_225110/0000/Merged_2017.root")

h2 = fin.Get("tuplizer/ibx_vs_ieta_NonIso")
print type(h2)
print h2.Integral()
h2.Draw("COLZ")


c.SaveAs("ibx_vs_ieta_NonIso.pdf")
