from PlotTemplates import * 
from ROOT import TFile



    

'''
This is the final function which will receive inputs and call all the relevant functions to make the plots. Input needed: 
 * filename
 * cutvalue used to fill the histograms. 
'''

def nsd(x):
    return ('{0:1.3g}'.format(x))
    
def SavePlotsForOneCutValue(filename, cutval, year_):
    year_2017 = year_
    defaultvalues = setdefaults(year_2017, filename)

    finput = defaultvalues[0]
    outputdir = defaultvalues[1] + "/CutVal_" + str(cutval) + "_ADC"
    year   = defaultvalues[2]
    print year_2017, year, defaultvalues[2], outputdir


    os.system("mkdir -p "+outputdir)
    os.system('mkdir '+outputdir+"/pdf")
    os.system('mkdir '+outputdir+"/png")
    os.system('mkdir '+outputdir+"/pdflog")
    os.system('mkdir '+outputdir+"/pnglog")


    saveNormalised2DWithTProfile(finput,year, outputdir, 'egidx_ttidx_Iso_dr_',  "bunch crossing index for e-#gamma candidates", "emulator TP index","Y")
    saveNormalised2DWithTProfile(finput,year, outputdir, 'egidx_ttidx_Iso_de_',  "bunch crossing index for e-#gamma candidates", "emulator TP index","Y")
    saveNormalised2DWithTProfile(finput,year, outputdir, 'egidx_ttidx_NonIso_dr_',  "bunch crossing index for e-#gamma candidates", "emulator TP index","Y")

    return 0


# In[39]:


## set default values 
def SavePlotsForOneCutValue1D(filename, cutval, year_):
    year_2017 = year_
    defaultvalues = setdefaults(year_2017, filename)

    finput = defaultvalues[0]
    outputdir = defaultvalues[1] + "/CutVal_" + str(cutval) + "_ADC"
    year   = defaultvalues[2]
    print year_2017, year, defaultvalues[2], outputdir


    os.system("mkdir -p "+outputdir)
    os.system('mkdir '+outputdir+"/pdf")
    os.system('mkdir '+outputdir+"/png")
    os.system('mkdir '+outputdir+"/pdflog")
    os.system('mkdir '+outputdir+"/pnglog")    
    
    
    
    savePDF1D(finput,year, outputdir, 'detaIso_',  "#Delta i#eta^{Iso}", "# of events")
    savePDF1D(finput,year, outputdir, 'dphiIso_',  "#Delta i#phi^{Iso}", "# of events")
    savePDF1D(finput,year, outputdir, 'detaNonIso_',  "#Delta i#eta^{Non-Iso}", "# of events")
    savePDF1D(finput,year, outputdir, 'dphiNonIso_',  "#Delta i#phi^{Non-Iso}", "# of events")
    savePDF1D(finput,year, outputdir, 'drMin_Iso_',  "#Delta iR^{Iso}", "# of events")
    savePDF1D(finput,year, outputdir, 'drMin_NonIso_',  "#Delta iR^{Non-Iso}", "# of events")
    return 0


# This is equivalent to main of the code: It send all the details to the function so that plots can be saved. Define all the global parameters here which will then move around in the code. 
# 
# For future: 
# * convert it into main,
# * save everything in a single object so that things go easily when calling functions, 
# 


def FileInfo(year_2017_):
    cutval=[]
    filenames=[]
    inputfiles = ''
    
    if year_2017_ == True:
        inputfiles = 'files2017_November.txt'
    if year_2017_ == False:
        inputfiles = 'files2018.txt'
        
    for ifile in open(inputfiles):
        cut = ifile.rstrip("\n").split(" ")[0]
        file_ = ifile.rstrip("\n").split(" ")[1]


        cutval.append(cut)
        filenames.append(file_)
        
    return cutval,filenames, inputfiles


# * This small cell has the information about the rootfiles, which can be used for 1d and 2d plots later on. 

year_2017_ = True
cutval,filenames,inputfiles=FileInfo(year_2017_)


# * all 1D plots which need to be shown in overlay form are defined here. 


files=[]

for idx, ifile in enumerate(filenames):
    files.append(ROOT.TFile(ifile,"READ"))
    
legend=['ADC>2','ADC>4','ADC>8']

histname='detaIso_'
dirname=''
if year_2017_ == True: dirname = 'Plots2017_FrontTrain'
if year_2017_ == False: dirname = 'Plots2018_FrontTrain'

#OverLay1D(files, dirname, histname, "#Delta i#ieta^{Iso}", "# of events", legend,year_2017_)















## ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

''' 

probability dumps, convert the 2d plots into .txt files. 

'''

timestep=[-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6]
cutval = "10"
templaterootstring = 'timescanOutput/PrefiringRateEE_2017data_FrontTrain_TIME_cutval_CUT.root'
ratefilename_ = (((templaterootstring.replace("TIME_","")).replace(".root",".txt")).replace("PrefiringRateEE","Rate")).replace("CUT",str(cutval))
probfilename_ = ratefilename_.replace("Rate","Prob")
timescanfilenames=ratefilename_.replace("Rate","rootfilesList")

print ratefilename_, probfilename_, timescanfilenames
print probfilename_

timefilelist=[]
ftxt=open(timescanfilenames,"w")

for itime in timestep:
    time_=""
    if itime <0: time_="minus"+str(abs(itime))
    if itime ==0: time_="nosign0"
    if itime >0: time_="plus"+str(itime)
    rootfilename_ = (templaterootstring.replace("TIME",time_)).replace("CUT",cutval)
    towrite_  = str(itime) + " " + rootfilename_+" \n"
    ftxt.write(towrite_)
    print time_, cutval, rootfilename_

ftxt.close()


txtfile = ''
xbin_ = 2
ybin_ = 2


#is2017 = year_2017_
#filename= inputfiles
#postfix_="_"+str(xbin_)+"_"+str(ybin_)
#if is2017: txtfile = 'probability_2017'+postfix_+'.txt'
#if not is2017: txtfile = 'probability_2018'+postfix_+'.txt'





is2017 = year_2017_
filename= timescanfilenames
postfix_="_"+str(xbin_)+"_"+str(ybin_)
txtfile = ratefilename_




print "file name = ",txtfile
prefire_prob_=[]
prefire_prob_e_=[]

prefire_prob_26_=[]
prefire_prob_26_e_=[]
prefire_prob_27_=[]
prefire_prob_27_e_=[]
prefire_prob_28_=[]
prefire_prob_28_e_=[]
prefire_prob_29_=[]
prefire_prob_29_e_=[]





outfile = open(txtfile,'w')
outfile.write("adc prob_t prob_t_e prob_26 prob_26_e prob_27 prob_27_e prob_28 prob_28_e prob_29 prob_29_e \n")
for ifile in open(filename):
    inputfile =  ifile.rstrip('\n').split()[1]
    adcCut    =  ifile.rstrip('\n').split()[0]
    
    tfile_ = TFile(inputfile,'READ')
    
    axis_N="X"
    
    print "reading rootfile", inputfile
    ##-----------
    h2 = tfile_.Get('egidx_ttidx_NonIso_dr_')
    print "------",h2.Integral()
    prefire_prob_.append(NormalizedPrefiringProbability(h2,axis_N)[0])
    prefire_prob_e_.append(NormalizedPrefiringProbability(h2,axis_N)[1])
    
    h2 = NormalizeYAxis(h2,axis_N)
    prob = h2.GetBinContent(xbin_,ybin_)
    prob_e = h2.GetBinError(xbin_,ybin_)
    
    ##-----------
    h2_26 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_26')
    prefire_prob_26_.append(NormalizedPrefiringProbability(h2_26,axis_N)[0])
    prefire_prob_26_e_.append(NormalizedPrefiringProbability(h2_26,axis_N)[1])
    
    h2_26 = NormalizeYAxis(h2_26,axis_N)
    prob_26 = h2_26.GetBinContent(xbin_,ybin_)
    prob_26_e = h2_26.GetBinError(xbin_,ybin_)
    
    ##-----------
    h2_27 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_27')
    prefire_prob_27_.append(NormalizedPrefiringProbability(h2_27,axis_N)[0])
    prefire_prob_27_e_.append(NormalizedPrefiringProbability(h2_27,axis_N)[1])
    
    h2_27 = NormalizeYAxis(h2_27,axis_N)
    prob_27 = h2_27.GetBinContent(xbin_,ybin_)
    prob_27_e = h2_27.GetBinError(xbin_,ybin_)
    print "prob_27_e =", prob_27_e

    ##-----------
    h2_28 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_28')
    prefire_prob_28_.append(NormalizedPrefiringProbability(h2_28,axis_N)[0])
    prefire_prob_28_e_.append(NormalizedPrefiringProbability(h2_28,axis_N)[1])
    
    h2_28 = NormalizeYAxis(h2_28,axis_N)
    prob_28 = h2_28.GetBinContent(xbin_,ybin_)
    prob_28_e = h2_28.GetBinError(xbin_,ybin_)
    
    ##-----------
    h2_29 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_29')
    print "h2_29   --- ", h2_29.Integral()
    prefire_prob_29_.append(NormalizedPrefiringProbability(h2_29,axis_N)[0])
    prefire_prob_29_e_.append(NormalizedPrefiringProbability(h2_29,axis_N)[1])


    h2_29 = NormalizeYAxis(h2_29,axis_N)
    prob_29  = h2_29.GetBinContent(xbin_,ybin_)
    prob_29_e = h2_29.GetBinError(xbin_,ybin_)
    
    towrite = str(adcCut)+' '+str(nsd(prob))+' '+str(nsd(prob_e))+' '+str(nsd(prob_26))+' '+str(nsd(prob_26_e))+' '+str(nsd(prob_27))+' '+str(nsd(prob_27_e))+' '+str(nsd(prob_28))+' '+str(nsd(prob_28_e))+' '+str(nsd(prob_29))+' '+str(nsd(prob_29_e))+'\n'
    print "to write ", towrite
    outfile.write(towrite)
    #h2_28 = tfile_.Get('egidx_ttidx_NonIso_dr_bin_28')
    print ifile
    

outfile.close()
print "-----------------------------pre fire prob------------"
print "total = ",prefire_prob_, len(prefire_prob_)
print "ring 26 = ", prefire_prob_26_, len(prefire_prob_26_)
print "ring 27 = ", prefire_prob_27_, len(prefire_prob_27_)
print "ring 28 = ", prefire_prob_28_,len(prefire_prob_28_)


adc=timestep
probfile = open(probfilename_,"w")

probfile.write("adc prob_t prob_t_e prob_26 prob_26_e prob_27 prob_27_e prob_28 prob_28_e prob_29 prob_29_e \n")

print "length of prefire_prob_", len(prefire_prob_), len(adc)

for iele in range(0,len(prefire_prob_)):
    writethis_ = str(adc[iele]) + " " + str(nsd(prefire_prob_[iele])) +" " + str(nsd(prefire_prob_e_[iele])) +" " +  str(nsd(prefire_prob_26_[iele])) + " " + str(nsd(prefire_prob_26_e_[iele])) + " " + str(nsd(prefire_prob_27_[iele])) + " " +  str(nsd(prefire_prob_27_e_[iele])) + " " +str(nsd(prefire_prob_28_[iele])) + " " +  str(nsd(prefire_prob_28_e_[iele])) + " " +str(nsd(prefire_prob_29_[iele])) + " " +str(nsd(prefire_prob_29_e_[iele])) +"\n"
    probfile.write(writethis_)

probfile.close()

    
