import FWCore.ParameterSet.Config as cms
process = cms.Process("LLPAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.GlobalTag.globaltag = cms.string("94X_mcRun2_asymptotic_v3")

process.load("Analysis.LLP-genAnalyzer.LLPAnalysis_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(50)
)



process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    #'file:/afs/cern.ch/work/f/fernance/private/Long_Lived_Analysis/UL-MonteCarlo/Trials/HToSSTu4l_UL2016/CMSSW_10_6_20/src/EXO-RunIISummer20UL16wmLHEGEN-00001.root')
    'dbs://ggH_HToSSTo4l_MH-400_MS-150_ctauS-1_TuneCP5_13TeV-powheg-pythia8/fernance-private-RunIISummer20UL16wmGSAPV-da29244b6dc720b4797b2ce28460e6ee/USER')
)



## path definitions
process.p      = cms.Path(
    process.LLPAnalysis

)

