import os 
timelist=['m5ns','m6ns','m7ns']
#timelist=['m4ns','m12ns','p12ns','p4ns','0ns','m8ns','p8ns']
#timelist=['m8ns']

inputconfig = open('conf_17.py','r').read()

filename = 'conf_TIME.py'

for itime in timelist:
    inputconfig_r = inputconfig.replace("TIME",itime)
    filename_r = filename.replace("TIME",itime)
    fout = open(filename_r,'w')
    print itime
    fout.write(inputconfig_r)
    fout.close()
    
    os.system('cmsRun '+filename_r)
    
    #os.system('rm '+filename_r)
    
