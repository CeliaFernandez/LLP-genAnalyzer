import FWCore.ParameterSet.Config as cms

LLPAnalysis = cms.EDAnalyzer('LLPAnalysis',

    nameOfOutput           = cms.string('output.root'),

    theGenEventInfoProduct = cms.InputTag("generator"),

    EventInfo              = cms.InputTag("generator"),
    RunInfo                = cms.InputTag("generator"),
    BeamSpot               = cms.InputTag("offlineBeamSpot"),

    PVCollection           = cms.InputTag("offlineSlimmedPrimaryVertices"),

    GenParticleCollection  = cms.InputTag("genParticles"),


    #
    # // Specific model configuration
    #

    LLP_id        = cms.double(9000006),
    mother_id  = cms.double(25) 

)


