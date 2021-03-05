#include "Analysis/LLP-genAnalyzer/src/LLPAnalysis.h"

////////
//////// -- Constructor
////////
LLPAnalysis::LLPAnalysis(const edm::ParameterSet& iConfig)
{
   usesResource("TFileService");

   parameters = iConfig;

   GenParticleToken_ = consumes<edm::View<reco::GenParticle> >  (parameters.getParameter<edm::InputTag>("GenParticleCollection"));

}



////////
//////// -- Destructor
////////
LLPAnalysis::~LLPAnalysis()
{

}

////////
//////// -- BeginJob
////////
void LLPAnalysis::beginJob()
{
  std::cout << "Begin Job" << std::endl;

  LLP_id = parameters.getParameter<double>("LLP_id");
  mother_id = parameters.getParameter<double>("mother_id");


  output_filename = parameters.getParameter<std::string>("nameOfOutput");
  file_out = new TFile(output_filename.c_str(), "RECREATE");

  tree_out = new TTree("Events", "Events"); // declaration

  //
  // -- Set the output TTree branches
  //
  
  tree_out->Branch("eventId", &eventId, "eventId/I");
  tree_out->Branch("luminosityBlock", &luminosityBlock, "luminosityBlock/I");
  tree_out->Branch("run", &run, "run/I");

  tree_out->Branch("LLP1_pt", &LLP1_pt, "LLP1_pt/F");
  tree_out->Branch("LLP1_eta", &LLP1_eta, "LLP1_eta/F");
  tree_out->Branch("LLP1_phi", &LLP1_phi, "LLP1_phi/F");
  tree_out->Branch("LLP1_vx", &LLP1_vx, "LLP1_vx/F");
  tree_out->Branch("LLP1_vy", &LLP1_vy, "LLP1_vy/F");
  tree_out->Branch("LLP1_vz", &LLP1_vz, "LLP1_vz/F");
  tree_out->Branch("LLP1_Llab", &LLP1_Llab, "LLP1_Llab/F");
  tree_out->Branch("LLP1_beta", &LLP1_beta, "LLP1_beta/F");
  tree_out->Branch("LLP1_Lprop", &LLP1_Lprop, "LLP1_Lprop/F");
  tree_out->Branch("LLP1_tlab", &LLP1_tlab, "LLP1_tlab/F");

  tree_out->Branch("LLP2_pt", &LLP2_pt, "LLP2_pt/F");
  tree_out->Branch("LLP2_eta", &LLP2_eta, "LLP2_eta/F");
  tree_out->Branch("LLP2_phi", &LLP2_phi, "LLP2_phi/F");
  tree_out->Branch("LLP2_vx", &LLP2_vx, "LLP2_vx/F");
  tree_out->Branch("LLP2_vy", &LLP2_vy, "LLP2_vy/F");
  tree_out->Branch("LLP2_vz", &LLP2_vz, "LLP2_vz/F");
  tree_out->Branch("LLP2_Llab", &LLP2_Llab, "LLP2_Llab/F");
  tree_out->Branch("LLP2_beta", &LLP2_beta, "LLP2_beta/F");
  tree_out->Branch("LLP2_Lprop", &LLP2_Lprop, "LLP2_Lprop/F");
  tree_out->Branch("LLP2_tlab", &LLP2_tlab, "LLP2_tlab/F");

}

////////
//////// -- EndJob
////////
void LLPAnalysis::endJob()
{
  std::cout << "End Job" << std::endl;

  file_out->cd();
  tree_out->Write();
  file_out->Close();

}


////////
//////// -- fillDescriptions
////////
void LLPAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


////////
//////// -- Analyze
////////
void LLPAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   bool ValidGenParticles = iEvent.getByToken(GenParticleToken_, GenParticleCollection_);
   if (!ValidGenParticles) { return; }


   //
   // -- Init the variables
   //    Class variables values are kept from one event to the next so it is
   //    necessary to set all values to zero before moving
   //

   // -> Event info
   eventId = 0;
   luminosityBlock = 0;
   run = 0;

   mother1_pt = 0.0; 
   mother1_eta = 0.0; 
   mother1_phi = 0.0; 
   mother1_vx = 0.0; 
   mother1_vy = 0.0; 
   mother1_vz = 0.0; 

   LLP1_pt = 0.0; 
   LLP1_eta = 0.0; 
   LLP1_phi = 0.0; 
   LLP1_vx = 0.0; 
   LLP1_vy = 0.0; 
   LLP1_vz = 0.0; 
   LLP1_beta = 0.0; 
   LLP1_Llab = 0.0; 
   LLP1_Lprop = 0.0; 
   LLP1_tlab = 0.0; 
   LLP1_tprop = 0.0; 

   LLP2_pt = 0.0; 
   LLP2_eta = 0.0; 
   LLP2_phi = 0.0; 
   LLP2_vx = 0.0; 
   LLP2_vy = 0.0; 
   LLP2_vz = 0.0; 
   LLP2_beta = 0.0; 
   LLP2_Llab = 0.0; 
   LLP2_Lprop = 0.0; 
   LLP2_tlab = 0.0; 
   LLP2_tprop = 0.0; 


   //
   // -- Pre-analysis
   //

   // -> Event info
   eventId = iEvent.id().event();
   luminosityBlock = iEvent.id().luminosityBlock();
   run = iEvent.id().run();



   //
   // -- Main analysis
   //


   // Locate LLP's
   std::vector<int> iLLP;

   for(size_t i = 0; i < GenParticleCollection_->size(); i++) {

      const reco::GenParticle &genparticle = (*GenParticleCollection_)[i];

      if (  abs(genparticle.pdgId()) == LLP_id  && abs(genparticle.mother()->pdgId()) == mother_id) {
         iLLP.push_back(i);
      }
   }

   // Sort by LLP pt
   std::sort( std::begin(iLLP), std::end(iLLP), [&](int i1, int i2){ return GenParticleCollection_->at(i1).pt() > GenParticleCollection_->at(i2).pt(); });

   const reco::GenParticle &LLP1 = (*GenParticleCollection_)[iLLP.at(0)];
   const reco::GenParticle &LLP2 = (*GenParticleCollection_)[iLLP.at(1)];

   Float_t vx_end;
   Float_t vy_end;
   Float_t vz_end;

   // -> Branch 1

   LLP1_pt = LLP1.pt();
   LLP1_eta = LLP1.eta();
   LLP1_phi = LLP1.phi();
   LLP1_vx = LLP1.vx();
   LLP1_vy = LLP1.vy();
   LLP1_vz = LLP1.vz();
   LLP1_beta = LLP1.p()/LLP1.energy();

   std::vector<int> ilep1;

   for (size_t i = 0; i < LLP1.numberOfDaughters(); i++) {

      const reco::Candidate *daughter = LLP1.daughter(i);
      if ( abs(daughter->pdgId()) != 11 and abs(daughter->pdgId()) != 13) { continue; }
      ilep1.push_back(i);

   } 

   std::sort( std::begin(ilep1), std::end(ilep1), [&](int i1, int i2){ return LLP1.daughter(i1)->pt() > LLP1.daughter(i2)->pt(); });

   vx_end = LLP1.daughter(0)->vx();
   vy_end = LLP1.daughter(0)->vy();
   vz_end = LLP1.daughter(0)->vz();

   LLP1_Llab = sqrt( (vx_end - LLP1_vx)*(vx_end - LLP1_vx) + (vy_end - LLP1_vy)*(vy_end - LLP1_vy) + (vz_end - LLP1_vz)*(vz_end - LLP1_vz) );
   LLP1_tlab = LLP1_Llab / (LLP1_beta * 3e10);
   LLP1_Lprop = sqrt(1 - LLP1_beta*LLP1_beta) * LLP1_Llab;


   // -> Branch 2

   LLP2_pt = LLP2.pt();
   LLP2_eta = LLP2.eta();
   LLP2_phi = LLP2.phi();
   LLP2_vx = LLP2.vx();
   LLP2_vy = LLP2.vy();
   LLP2_vz = LLP2.vz();
   LLP2_beta = LLP2.p()/LLP2.energy();

   std::vector<int> ilep2;

   for (size_t i = 0; i < LLP2.numberOfDaughters(); i++) {

      const reco::Candidate *daughter = LLP2.daughter(i);
      if ( abs(daughter->pdgId()) != 11 and abs(daughter->pdgId()) != 13) { continue; }
      ilep2.push_back(i);

   } 

   std::sort( std::begin(ilep2), std::end(ilep2), [&](int i1, int i2){ return LLP2.daughter(i1)->pt() > LLP2.daughter(i2)->pt(); });

   vx_end = LLP2.daughter(0)->vx();
   vy_end = LLP2.daughter(0)->vy();
   vz_end = LLP2.daughter(0)->vz();

   LLP2_Llab = sqrt( (vx_end - LLP2_vx)*(vx_end - LLP2_vx) + (vy_end - LLP2_vy)*(vy_end - LLP2_vy) + (vz_end - LLP2_vz)*(vz_end - LLP2_vz) );
   LLP2_tlab = LLP2_Llab / (LLP2_beta * 3e10);
   LLP2_Lprop = sqrt(1 - LLP2_beta*LLP2_beta) * LLP2_Llab;


   // -> MC truth:
   //analyzeGenParticles(iEvent);

   // -> Fill the TTree

   tree_out->Fill();

}



