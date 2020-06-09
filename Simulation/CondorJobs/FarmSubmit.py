import os 
import sys 
import getpass as gp
import argparse
##-----------------------------------------------------------------------------------------------
## Author: Raman Khurana 
## Date  : Mon 09 Mar 2020 01:08:32 
## Note  : First version of the script to automate the condor job submission
## usage : python FarmSubmit.py --proxypathtmp /tmp/x509up_u55959 --outformat .csv --mainsrc PulseShapeComparison.py
##-----------------------------------------------------------------------------------------------


'''
 split a string into a python list, this is to extract the initial of the username 
'''
def strsplit(word):
    return [char for char in word]

## pre-requiste: set the proxy and provide proxy path to this script: voms-proxy-init --voms cms --valid 192:00



usage = "python FarmSubmit.py --proxypathtmp /tmp/x509up --inputdir path_to_all_files_to_run_on --outputdir path_where_all_output_will_be_saved -outformat .csv"
parser = argparse.ArgumentParser(description=usage)
parser.add_argument("-proxypathtmp", "--proxypathtmp",  dest="proxypathtmp",default="/tmp/x509up")
parser.add_argument("-inputdir", "--inputdir",  dest="inputdir",default="/eos/cms/store/user/khurana/ECAL/SimulationTuples/simulation_tuples_Eta_2p0_to_2p5")
parser.add_argument("-outputdir", "--outputdir",  dest="outputdir",default="/eos/cms/store/user/khurana/ECALPrivate/CSVFiles_Eta_2p0_to_2p5")
parser.add_argument("-outformat","--outformat", dest="outformat", default=".root")
parser.add_argument("-mainsrc","--mainsrc", dest="mainsrc", default="")

args = parser.parse_args()

INPUTDIR=args.inputdir
OUTPUTDIR=args.outputdir
SUBFILE="template.sub"
SHELLFILE="run_main.sh"


SUBMITDIR=INPUTDIR.split("/")[-1]+"_"+args.mainsrc.split(".")[0]
os.system('mkdir '+SUBMITDIR)
os.system('cp '+args.mainsrc +' '+SUBMITDIR)

## define all constants 
USERNAME = gp.getuser() 
USERNAMEINITIAL= strsplit(USERNAME)[0]
HOMEPRIVATE="/afs/cern.ch/user/USERNAMEINITIAL/USERNAME/private/"
PROXYPATH = HOMEPRIVATE.replace("USERNAMEINITIAL", USERNAMEINITIAL)
PROXYPATH = PROXYPATH.replace("USERNAME",USERNAME)
PROXYTEMPPATH=args.proxypathtmp
FULLPROXYPATH=PROXYPATH + "/x509up"
os.system('cp '+PROXYTEMPPATH +" " + FULLPROXYPATH)


''' 
convert the input dirpath into a list of .root files in that directory, and use the same directory structure for output as for input to be consistent. 
'''
def GetRootFileList():
    os.system('find '+INPUTDIR+' -name *root > root.log')
    rootfileList = [ifile.rstrip() for ifile in open('root.log')]
    os.system('rm root.log')
    return rootfileList 

''' return the path where output file will be saved, format changing is done at this step ''' 
def GetOutputFilePath(rootfilepathlist):
    return [(ifile.replace(INPUTDIR,OUTPUTDIR)).replace(".root", args.outformat) for ifile in rootfilepathlist]


shellfile = open(SHELLFILE, "r"); shellfiledata = shellfile.read(); shellfile.close()
subfile = open(SUBFILE, "r"); subfiledata = subfile.read(); subfile.close()

def PrepareSubmissionFile(shellfilename, input_, output_):
    
    newshellfilename = SUBMITDIR+'/rk_del_shellfile_'+input_.split("/")[-1].replace(".root",".sh")
    newsubfilename   = SUBMITDIR+'/rk_del_subfile_'+input_.split("/")[-1].replace(".root",".sub")
    
    newshellfiledata = (shellfiledata.replace("INPUTFILENAME",input_)).replace("OUTPUTFILENAME",output_)
    f = open(newshellfilename,'w') ;    f.write(newshellfiledata);     f.close()
    
    
    newsubfiledata =  (subfiledata.replace("SHELLFILENAME",newshellfilename.replace(SUBMITDIR+'/',"")))
    newsubfiledata = newsubfiledata.replace("PROXYPATH",PROXYPATH)
    fsub = open(newsubfilename,'w') ;    fsub.write(newsubfiledata);     fsub.close()
    
    return [newshellfilename,newsubfilename]


def SubmitCondor(subfile):
    presentpath = os.getcwd()
    os.chdir(presentpath+'/'+SUBMITDIR)
    os.system('condor_submit '+subfile)
    os.chdir(presentpath)

rootfilepathlist=GetRootFileList()
outoutfilepathlist=GetOutputFilePath(rootfilepathlist)
print rootfilepathlist
print GetOutputFilePath(rootfilepathlist)
print INPUTDIR, OUTPUTDIR


i=0
for ifile in rootfilepathlist:
    print "submit job for ",rootfilepathlist[i],".................."
    cond_file_list = PrepareSubmissionFile(".sh", rootfilepathlist[i], outoutfilepathlist[i])
    SubmitCondor(cond_file_list[1].replace(SUBMITDIR+"/",""))
    i = i+1

