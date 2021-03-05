#ifndef LLPAnalysis_H
#define LLPAnalysis_H

#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Generation
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"



// Jets
#include "DataFormats/JetReco/interface/GenJet.h"


// STDLIB
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

// ROOT
#include "TLorentzVector.h"
#include "TTree.h"
#include "TFile.h"


class LLPAnalysis : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit LLPAnalysis(const edm::ParameterSet&);
      ~LLPAnalysis();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void analyzeGenParticles(edm::Event const& e);

      edm::ParameterSet parameters;
      std::string output_filename;

      int LLP_id;
      int mother_id;

      //
      // --- Tokens and Handles
      //


      // MC truth
      edm::EDGetTokenT<edm::View<reco::GenParticle> >  GenParticleToken_;
      edm::Handle<edm::View<reco::GenParticle> > GenParticleCollection_;


      //
      // --- Variables used
      //

      // Event info
      Int_t eventId = 0;
      Int_t luminosityBlock = 0;
      Int_t run = 0;

      // HLT
      bool Flag_HLT_IsoMu24 = false;

      // Branch 1
      Float_t mother1_pt;
      Float_t mother1_eta;
      Float_t mother1_phi;
      Float_t mother1_vx;
      Float_t mother1_vy;
      Float_t mother1_vz;

     
      Float_t LLP1_pt;
      Float_t LLP1_eta;
      Float_t LLP1_phi;
      Float_t LLP1_vx;
      Float_t LLP1_vy;
      Float_t LLP1_vz;
      Float_t LLP1_beta;
      Float_t LLP1_Llab;
      Float_t LLP1_Lprop;
      Float_t LLP1_tlab;
      Float_t LLP1_tprop;

      Float_t LLP2_pt;
      Float_t LLP2_eta;
      Float_t LLP2_phi;
      Float_t LLP2_vx;
      Float_t LLP2_vy;
      Float_t LLP2_vz;
      Float_t LLP2_beta;
      Float_t LLP2_Llab;
      Float_t LLP2_Lprop;
      Float_t LLP2_tlab;
      Float_t LLP2_tprop;

      // Output definition
      TFile *file_out;
      TTree *tree_out;

};

#endif






