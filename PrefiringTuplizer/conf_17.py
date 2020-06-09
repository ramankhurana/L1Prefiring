import FWCore.ParameterSet.Config as cms


from Configuration.StandardSequences.Eras import eras
process = cms.Process("L1PrefiringAnalyzerTPGANALYSIS",eras.Run2_2018)
#process = cms.Process("L1PrefiringAnalyzerTPGANALYSIS")

process.load("FWCore.MessageService.MessageLogger_cfi")


process.load("SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_readDBOffline_cff")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = '102X_dataRun2_Prompt_v4'

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')


process.load('EventFilter.L1TRawToDigi.gtStage2Digis_cfi')




process.GlobalTag.toGet = cms.VPSet(
    cms.PSet(record = cms.string("EcalTPGLinearizationConstRcd"),
         ),
    cms.PSet(record = cms.string("EcalTPGPedestalsRcd"), 
         )
)

# ECAL Unpacker
process.load("EventFilter.EcalRawToDigi.EcalUnpackerMapping_cfi")
process.load("EventFilter.EcalRawToDigi.EcalUnpackerData_cfi")

process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')


process.load('L1Trigger.Configuration.L1TReco_cff')

process.load('Configuration.EventContent.EventContent_cff')



process.raw2digi_step = cms.Path(process.RawToDigi)
process.endjob_step = cms.EndPath(process.endOfProcess)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step)


from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAW
#,L1TEventSetupForHF1x1TPs  this last one is not in the release

#call to customisation function L1TReEmulFromRAW imported from L1Trigger.Configuration.customiseReEmul
#process = L1TReEmulFromRAW(process)
from EventFilter.L1TRawToDigi.caloStage2Digis_cfi import caloStage2Digis
process.rawCaloStage2Digis = caloStage2Digis.clone()
process.rawCaloStage2Digis.InputLabel = cms.InputTag('rawDataCollector')

process.ecalTriggerPrimitiveDigis = cms.EDProducer("EcalTrigPrimProducer",
   InstanceEB = cms.string('ebDigis'),
   InstanceEE = cms.string('eeDigis'),
   Label = cms.string('ecalDigis'),
   BarrelOnly = cms.bool(False),
   Famos = cms.bool(False),
   TcpOutput = cms.bool(False),
   Debug = cms.bool(False),
   binOfMaximum = cms.int32(6), ## optional from release 200 on, from 1-10

)










process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring(
                                #'file:/eos/cms/store/group/phys_exotica/monoHiggs/ecalV1/CRAB_PrivateMC/EPlus_EMinus_ParticleGun_Pt100GeV_OnlyEndcapV2_Digi/step2_0ns.root'
                                'file:/eos/cms/store/group/phys_exotica/monoHiggs/ecalV1/CRAB_PrivateMC/EPlus_EMinus_ParticleGun_Pt100GeV_OnlyEndcapV2_Digi/step2_TIME.root',
                            #'file:/afs/cern.ch/work/k/khurana/L1Prefiring/EDAnalyzer/CMSSW_10_2_1/src/L1Prefiring/EventGeenration/step2_default.root'
                                #'file:/afs/cern.ch/work/k/khurana/L1Prefiring/EDAnalyzer/CMSSW_10_2_1/src/L1Prefiring/EventGeneration/rootfiles/step2_p17_singleEle.root'
                                #'file:/tmp/khurana/test.root' on lkxplus 791
                                #'file:/afs/cern.ch/user/t/theofil/public/preFiring/step2_m17ns.root'
                                #'file:/tmp/00464706-0339-E811-88D8-1866DAEA6C40.root' ## 2017
                                #'/store/data/Run2017F/ZeroBias2/RAW-RECO/05Apr2018-v1/30000/00464706-0339-E811-88D8-1866DAEA6C40.root'
                                #'/store/data/Run2018B/HLTPhysics2/RAW/v1/000/318/581/00000/1E3AA296-7578-E811-A283-FA163E0E994B.root'
                                #'/store/data/Run2018D/ZeroBias/RAW/v1/000/324/725/00000/38CB8BDB-53A8-9643-A7A1-623BC3992B15.root'
                                #'/store/data/Run2018D/ZeroBias1/RAW-RECO/LogError-PromptReco-v2/000/324/725/00000/FB50455E-C060-EF43-AB31-733A66A2E6E4.root'
                                #'file:/afs/cern.ch/work/d/dekumar/public/002BD245-0290-EE4B-878A-EF1D2B234239.root'
                                #'/store/data/Run2018D/ZeroBias1/RAW/v1/000/324/725/00000/FB291977-2570-0148-AE34-55E450AF3B90.root'
                                #'file:/tmp/FB291977-2570-0148-AE34-55E450AF3B90.root'
                                
                                #'root://xrootd-cmsa.infn.it//store/data/Run2018D/ZeroBias1/RAW/v1/000/324/725/00000/FB291977-2570-0148-AE34-55E450AF3B90.root',
                                #'root://xrootd-cms.infn.it//store/data/Run2018D/ZeroBias1/RAW/v1/000/324/725/00000/6471EDD7-A659-B84D-B763-6E399723E5FA.root',
                                #'root://xrootd-cms.infn.it//store/data/Run2018D/ZeroBias1/RAW/v1/000/324/725/00000/3FBCF4C6-6C3A-964B-A293-7D19BE669C3B.root',
                                #'root://xrootd-cms.infn.it//store/data/Run2018D/ZeroBias1/RAW/v1/000/324/725/00000/C6FA421E-1628-E847-A092-851B296C1421.root',
                                #'root://xrootd-cms.infn.it//store/data/Run2018D/ZeroBias1/RAW/v1/000/324/725/00000/CC483B27-C8E3-DF45-9C53-D969F9CAB3A1.root',
                                #'root://xrootd-cms.infn.it//store/data/Run2018D/ZeroBias1/RAW/v1/000/324/725/00000/01BF44F6-4157-9649-BBC1-C69EABB42B98.root'
                                #'file:/tmp/khurana/FB291977-2570-0148-AE34-55E450AF3B90.root'

                            )
                        )

process.tuplizer = cms.EDAnalyzer('PrefiringTuplizer',
                                  ugtProducer = cms.InputTag("gtStage2Digis"),
                                  TPEmulatorCollection =  cms.InputTag("ecalTriggerPrimitiveDigis",""),
                                  useAlgoDecision = cms.untracked.string("initial"),
                                  firstBXInTrainAlgo = cms.untracked.string("L1_FirstCollisionInTrain"),
                                  lastBXInTrainAlgo = cms.untracked.string("L1_LastCollisionInTrain"),
                                  isoBXAlgo = cms.untracked.string("L1_IsolatedBunch"),
                                  TPCollection = cms.InputTag("ecalDigis","EcalTriggerPrimitives"),
                                  ## for data 
                                  #stage2CaloLayer2EGammaProducer = cms.InputTag("gtStage2Digis","EGamma"),
                                  ## for mc 
                                  stage2CaloLayer2EGammaProducer = cms.InputTag("hltGtStage2Digis","EGamma"),
                                  
                                  ## for data
                                  #EBdigis      = cms.InputTag("selectDigi","selectedEcalEBDigiCollection"),
                                  #EEdigis      = cms.InputTag("selectDigi","selectedEcalEEDigiCollection")
                                  
                                  ## for mc
                                  EBdigis      = cms.InputTag("simEcalDigis","ebDigis"),
                                  EEdigis      = cms.InputTag("simEcalDigis","eeDigis"),
                                  genparticles = cms.InputTag("genParticles")
)



process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('Histo_L1Prefiring_TIME.root')
                                   #fileName = cms.string('Histo_L1Prefiring_0ns_FixLabel.root')
                                  )


#process.makedigis = cms.Path()

process.p = cms.Path(process.L1Reco*
                     process.gtStage2Digis*
                     process.ecalTriggerPrimitiveDigis*
                     process.tuplizer
                 )


process.schedule.append(process.p)
