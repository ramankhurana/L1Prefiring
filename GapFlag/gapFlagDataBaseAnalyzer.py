#!/usr/bin/env python

# * This notebook reads : 
#   - database file with delay and phase information for each TCC and Tower ID. 
#   - lookup tables prepared from ECALTPGTree 
#   - use look up tables to get the TCC channel id for each TCC and Tower ID. 
#      - Tower ID and TCC Channel are same in Barrel but in ENDCAP this is very different. 
#      - therefore this kind of lookup table is neeed when we want to see the 2d plots similar to the gap flag measurement. 
#      


import pandas as pd
import matplotlib.pyplot as plt
import sys, optparse, argparse


usage = "follow the .py file"
parser = argparse.ArgumentParser(description=usage)
parser.add_argument("-i", "--inputfile",  dest="inputfile",default="myfiles.txt")
args = parser.parse_args()

infile = args.inputfile #"gapflag_database/TIM_DATA_CONF_ID_1039.dat.txt"


# This is the syntax to make one dim histograms very quickly to see some errors in the tree or skimmed files, etc. 
# 
#for iy in df.columns:
#    hist=df.hist(column=iy,bins=10)
    


# Open a text file which will have all the needed columns of the database text files. 

outfile = infile.replace(".txt","_out.txt")
textf_out  = open(outfile, 'w')



def ListToText(idList):
    idText=""
    counter=0
    for i in idList:
        if counter<(len(idList)-1):
            idText = idText + str(i) + " "
        if counter==(len(idList)-1):
            idText = idText + str(i) 
        counter=counter+1
    return (idText+"\n")



def GetTowerIDInfo(tcc, tower, strip):
    #print "bug line has id =", tcc, tower, strip
    df_tpg = pd.read_csv("gapflag_database/EcalTPGParam.csv", sep=" ")#, header=None, names=["tcc",  "tower",  "stripInTower",  "TCCch"])
    #print "read the dataframe"
    #print df_tpg
    int_strip = int(strip)
    full_id=[]
    for dftcc, dftower, dfstripInTower, dfTCCch  in zip(df_tpg.tcc,df_tpg.tower,df_tpg.stripInTower,df_tpg.TCCch ):
        if int_strip < 0:
            if (int(tcc)==int(dftcc)) and (int(tower)==int(dftower)):
                #print (dftcc, dftower, dfstripInTower, dfTCCch)
                #full_id=str(dftcc)+" "+str(dftower)+" "+str(dfstripInTower)+" "+str(dfTCCch)
                full_id=[str(dftcc), str(dftower), str(dfstripInTower), str(dfTCCch)]
        if int_strip >=0:
            #print (dftcc, dftower, dfstripInTower, dfTCCch)
            if (int(tcc)==int(dftcc)) and (int(tower)==int(dftower)) and (int(strip)==int(dfstripInTower)):
                #print (dftcc, dftower, dfstripInTower, dfTCCch)
                full_id=[str(dftcc), str(dftower), str(dfstripInTower), str(dfTCCch)]
                #tcc_tower_strip = str(int(tcc)) + " " + str(int(tower))
                #id_=tcc_tower_strip
    return full_id




df = pd.read_csv(infile, sep=" ")#header=None, names=["TIM_CONF_ID", "LOGIC_ID", "TIME_PAR1", "TIME_PAR2"])

counter = 0
for lid, t1, t2 in zip(df.LOGIC_ID, df.TIME_PAR1, df.TIME_PAR2):
    print counter 
    counter = counter + 1
    ## EB condition 
    if "1220" in str(lid):
        if (str(lid).split("1220")[0]==''):
            eb_id_tmp = list(str(lid).split("1220")[1])
            ## adding one additional variable so that the number of rown in each column are same for EB and EE. 
            
            ## constructing the first three columns
            eb_id = [str(eb_id_tmp[0])+str(eb_id_tmp[1]), str(eb_id_tmp[4])+str(eb_id_tmp[5]), "-1"]
            
            ## getting the TCC channel corresponding to this det id.
            eb_id = GetTowerIDInfo(eb_id[0], eb_id[1], eb_id[2])
            
            ## append the timing information  delay (in 25 ns units) and phase (in 12.5 ns units).
            eb_id.append(t1)
            eb_id.append(t2)
            print ListToText(eb_id)
            textf_out.write(ListToText(eb_id))
    
    ## EE condition 
    if "2140" in str(lid):
        if (str(lid).split("2140")[0]==''):
            ee_id_tmp = list(str(str(lid).split("2140")[1]))
            
            ## constructing the first three columns 
            ee_id = [ee_id_tmp[0]+ee_id_tmp[1]+ee_id_tmp[2], ee_id_tmp[3]+ ee_id_tmp[4], ee_id_tmp[5]]
            
            ## getting the TCC channel corresponding to this det id.
            ee_id = GetTowerIDInfo(ee_id[0], ee_id[1], ee_id[2])
            
            ## append the timing information  delay (in 25 ns units) and phase (in 12.5 ns units). 
            ee_id.append(t1)
            ee_id.append(t2)
            
            textf_out.write(ListToText(ee_id))
            # print (myline)

textf_out.close()



print "out file already written"

##df.plot(kind='line',x="TIME_PAR1",y='number',ax=plt.gca())


# - following snippet is to make the 2d plot X-axis: TCC ID and Y axis: TCC channel ID 
# - done for the .text file just produced using the database file and the .root file. 
# - header of the output is "tcc tower stripInTower TCCch" 

# In[ ]:

