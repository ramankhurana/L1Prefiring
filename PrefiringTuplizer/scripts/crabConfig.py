from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'prefiringanalysis2017_V2'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'conf.py'
config.JobType.allowUndistributedCMSSW=True

config.Data.inputDataset = '/ZeroBias2/Run2017F-05Apr2018-v1/RAW-RECO'

#config.Data.inputDataset = '/ZeroBias1/Run2018D-v1/RAW'


config.Data.inputDBS = 'global'
#config.Data.splitting = 'Automatic'

config.JobType.maxJobRuntimeMin = 2600 
#config.JobType.numCores    = 4
config.JobType.maxMemoryMB = 2500
config.JobType.outputFiles = ['Histo_L1Prefiring.root']
#config.Data.inputDataset = '/ZeroBias8/Run2018D-v1/RAW'
#config.Data.inputDBS = 'global'


##config.Data.runRange = '324725' # 2018 run


config.Data.runRange = '306425' # 2017 run

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
#config.Data.ignoreLocality  = True


#config.Data.splitting = 'LumiBased'
#config.Data.unitsPerJob = 1
#config.Data.lumiMask = 'lumi_2017.txt'  #'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Prompt/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt'
#config.Data.runRange = '306425' # '193093-194075'

#config.Data.outLFNDirBase = '/store/user/k/khurana/'
config.Data.publication = False

#config.Data.outputDatasetTag = 'CRAB3_tutorial_May2015_Data_analysis'

config.Site.storageSite = 'T2_CH_CERN'

#config.Site.blacklist = ['T1_UK_RAL']
