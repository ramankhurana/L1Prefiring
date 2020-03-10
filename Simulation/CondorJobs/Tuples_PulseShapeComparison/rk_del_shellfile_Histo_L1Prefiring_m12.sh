#!/bin/sh

#### FRAMEWORK SANDBOX SETUP ####
# Load cmssw_setup function
export SCRAM_ARCH=slc7_amd64_gcc700

#source ./cmssw_setup.sh

# Setup CMSSW Base
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh

# Download sandbox
#wget --no-check-certificate "http://stash.osgconnect.net/+ptiwari/sandbox-CMSSW_8_0_26_patch1-76efecd.tar.bz2"

# Setup framework from sandbox
#cmssw_setup sandbox-CMSSW_10_3_0-4cef61e.tar.bz2

echo "now entering cmssw"

scramv1 project CMSSW_10_2_1
#cd $CMSSW_BASE/src
cd CMSSW_10_2_1/src
eval `scramv1 runtime -sh`
#cmsenv
cd ../../

export X509_USER_PROXY=$1
voms-proxy-info -all
voms-proxy-info -all -file $1

echo "cmssw set up done "
ls -ltr 
python PulseShapeComparison.py  --inputfile /eos/cms/store/user/khurana/ECALPrivate/Tuples/Histo_L1Prefiring_m12.root --outputfile /eos/cms/store/user/khurana/ECALPrivate/CSVFiles/Histo_L1Prefiring_m12.csv



#xrdcp -f "$2" root://eoscms.cern.ch//eos/cms/store/group/phys_exotica/bbMET/ECAL/"$2"
