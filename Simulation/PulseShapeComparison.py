import os 
import sys 
from ROOT import TFile, TTree, TH1F, TH1D, TH1, TCanvas, TChain,TGraphAsymmErrors, TMath, TH2D, TLorentzVector, AddressOf, gROOT, TNamed
from root_pandas import read_root, to_root
from pandas import  DataFrame, concat, Series
import time


filespath="/eos/cms/store/user/khurana/ECAL/SimulationTuples/simulation_tuples_Eta_2p0_to_2p5/"

#filespath="../PrefiringTuplizer/Tuples/"
rootfilenae="Histo_L1Prefiring_p8ns.root"
#rootfilenae="Histo_L1Prefiring_m17ns.root"
#rootfilenae="Histo_L1Prefiring_p17ns.root"

#rootfilenae="Histo_L1Prefiring_FromPampa.root"

filename = filespath+"/"+rootfilenae

vars_ = ["b_ndataframe","b_nADC","b_index_df","b_index_ts","b_count_ADC"]


df_out= DataFrame(columns=['event','adc'])

ievent=0
for df in read_root(filename, 'tuplizer/prefiringTree', vars_, chunksize=1000):
    for  ndf, nadc, idx_df, idx_ts, adc  in zip(df.b_ndataframe, df.b_nADC, df.b_index_df, df.b_index_ts, df.b_count_ADC):
        print "event number =",ievent
        
        ## event processing 
        alltimeslices=[]
        for idf in range(ndf):
            #if ievent > 100: continue 
            #print "inside idf loop ---------"
            adc_timeslice=[]
            #print "entering iadc loop ---------"
            for iadc in range(nadc):
                if (idx_df[iadc] == idf) :
                    adc_timeslice.append(float(adc[iadc]))
                    #print "df_idx, ts_idx, idf, adc", idx_df[iadc], idx_ts[iadc], idf, adc[iadc]
                    if len(adc_timeslice)==10: 
                        if max( adc_timeslice) > 300:
                            df_out = df_out.append( {'event':int(ievent), 'adc':adc_timeslice}, ignore_index=True)
                            alltimeslices.append(adc_timeslice)
                            
                        break
        #print alltimeslices

        ievent=ievent+1
        

print df_out

outfile="SelectedDataFrames_"+rootfilenae.replace(".root","") + ".csv"

#df_out.to_root(outfile, key='seldf',mode='w'
df_out.to_csv(outfile, mode='w')
                            
