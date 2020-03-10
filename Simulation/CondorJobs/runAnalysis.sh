#!/bin/sh

#### FRAMEWORK SANDBOX SETUP ####
# Load cmssw_setup function
export SCRAM_ARCH=slc7_amd64_gcc820

#source cmssw_setup.sh

# Setup CMSSW Base
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh

# Download sandbox
#wget --no-check-certificate "http://stash.osgconnect.net/+ptiwari/sandbox-CMSSW_8_0_26_patch1-76efecd.tar.bz2"

# Setup framework from sandbox
#cmssw_setup sandbox-CMSSW_10_3_0-4cef61e.tar.bz2

cd $CMSSW_BASE
cmsenv
#cd ../../
export X509_USER_PROXY=$1
voms-proxy-info -all
voms-proxy-info -all -file $1

python PulseShapeComparison.py

xrdcp -f "$2" root://eoscms.cern.ch//eos/cms/store/group/phys_exotica/bbMET/ECAL/"$2"; do 

