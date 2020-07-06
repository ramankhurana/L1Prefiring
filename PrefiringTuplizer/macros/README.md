# Instructions to make pre-firing probability plots
-----------------------------------------------------------------------------------------------------------------------------------------------
Following is the set of instructions to make pre-firing probability plot for different cases. The instructions here describe the cases when we use:

 * For 2017 Full readout data
 * For 2018 Full readout data
 * For 2018 Phase scan data 
 * For simulation 
 * For Gap-Flag see the gap-flag dir 

Everthing is done in same macro L1Prefiring.C and controlled mostly by boolean switches except simulation setup which need some uncommenting of the code. 

-----------------------------------------------------------------------------------------------------------------------------------------------
## For 2017 Full readout data 


Boolean setting in L1Prefiring.C: 

bool is2017    = true;
bool timescan_ = false;
bool isdata    = true;  

Change the dirname where you want to save the .root files 
TString outputdir = ""; 


run the shell script for 5 cutvalues, 2,4,6,8,10  using 

source run_2017FR.sh  ## this will create one rootfile with histograms for each cut value: in the outputdir 

All the plots can be saved in PDF using (the path of rootfile has to be saved in a text file and chnaged in this file. Year flag has to be 2017=True): 

python PlotSaver_May14.py

all the related functions to perform the plotting etc are located in the PlotTemplates.py. The probability values are dumped into text file for several ring and total. This can be converted into rootfile and then saved into pdf using:
python textgraph.py

To make the plot (pdf) comparing the probability graphs use: 
python compareProb_all.py


-----------------------------------------------------------------------------------------------------------------------------------------------
## For 2018 Full readout data 

It is similar to 2017 just change the boolean setting and rest of the steps remain same. 

bool is2017    = false;
bool timescan_ = false;
bool isdata    = true;


-----------------------------------------------------------------------------------------------------------------------------------------------
## For 2018 Phase scan data
bool is2017    = true; ## this is June 2018 phase scan data but words with 2017 boolean, it is little tricky to chnage it now, so just be careful with this switch 
bool timescan_ = true;
bool isdata    = true;

The L1Prefiring.C function has to be changed 
use

void L1Prefiring(int threshold=2, int lumi1=0, int lumi2=999999,TString timeshiftoutput="_plus8_", TString inputcutval="p8ns")

instead of 

void L1Prefiring(int threshold=2,TString timeshiftoutput="_plus8_", TString inputcutval="p8ns", int lumi1=0, int lumi2=999999)                                                                            

Once done ready to run the full scan 

source run_timescan.sh


-----------------------------------------------------------------------------------------------------------------------------------------------
## For Simulation use:

Boolean setting in L1Prefiring.C: 

bool is2017    = true;
bool timescan_ = true;
bool isdata    = false;  

All the code relevant for simulation is commented by default, because the branchs are not present in the tuples for data. In order to run for simulation uncomment all the code under 
/*
if (!isdata) {
..;
}
*/ 

This is the dirty way to keep everything in same file 


