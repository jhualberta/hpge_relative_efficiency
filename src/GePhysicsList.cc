//////////////////////////////////
///  Class: GePhysicsList
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#include "GePhysicsList.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4IonConstructor.hh"
#include "G4ProcessManager.hh"
#include "G4RadioactiveDecay.hh"

GePhysicsList::GePhysicsList():  G4VUserPhysicsList()
{
 defaultCutValue = 1.0*mm;
 SetVerboseLevel(1);
}
//######################################################
GePhysicsList::~GePhysicsList()
{
}
//######################################################
void GePhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();  

}
//######################################################
void GePhysicsList::ConstructBosons()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();
}

//######################################################
void GePhysicsList::ConstructLeptons()
{
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

//######################################################
void GePhysicsList::ConstructMesons()
{
  //  mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4Eta::EtaDefinition();
  G4EtaPrime::EtaPrimeDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();
}

//######################################################
void GePhysicsList::ConstructBaryons()
{
  //  baryons
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
}

//######################################################
void GePhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructGeneral();
  G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
  radioactiveDecay->SetHLThreshold(-1.*s);
  radioactiveDecay->SetICM(true);
  radioactiveDecay->SetARM(false);
      
  G4ProcessManager* pmanager = G4GenericIon::GenericIon()->GetProcessManager();  
  pmanager->AddProcess(radioactiveDecay, 0, -1, 1);    
}
//######################################################
#include "G4ComptonScattering.hh"
#include "G4hPairProduction.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4hIonisation.hh"

void GePhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while ( (*theParticleIterator)() ){
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
    
        if (particleName == "gamma") {
           // gamma         
           pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
           pmanager->AddDiscreteProcess(new G4ComptonScattering);
           pmanager->AddDiscreteProcess(new G4GammaConversion);
        } 
        else if (particleName == "e-") {
           //electron
           pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
           pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
           pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);      
        } 
        else if (particleName == "e+") {
           //positron
           pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
           pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
           pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);
           pmanager->AddProcess(new G4eplusAnnihilation,  0,-1,4);
        } 
        else if ( particleName == "mu+" || particleName == "mu-"    ) {
           //muon  
           pmanager->AddProcess(new G4MuMultipleScattering,-1, 1,1);
           pmanager->AddProcess(new G4MuIonisation,      -1, 2,2);
           pmanager->AddProcess(new G4MuBremsstrahlung,  -1, 3,3);
           pmanager->AddProcess(new G4MuPairProduction,  -1, 4,4);       
        } 
        else if ((!particle->IsShortLived()) && 	       (particle->GetPDGCharge() != 0.0) && 	       (particle->GetParticleName() != "chargedgeantino")) {
           //all others charged particles except geantino
           pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
           pmanager->AddProcess(new G4hIonisation,       -1, 2,2); 
        }
  }
}

//######################################################
#include "G4Decay.hh"

void GePhysicsList::ConstructGeneral()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while ( (*theParticleIterator)() ){
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        if (theDecayProcess->IsApplicable(*particle)) { 
           pmanager ->AddProcess(theDecayProcess);
           // set ordering for PostStepDoIt and AtRestDoIt
           pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
           pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
        }
  }
}

//######################################################
void GePhysicsList::SetCuts()
{
//  if (verboseLevel >0){
     G4cout << "GePhysicsList::SetCuts:";
     G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
 // }
G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100.*eV, 100.*GeV);

   currentDefaultCut   = 100*um;
   cutForGamma         = currentDefaultCut;
   cutForElectron      = currentDefaultCut;
   cutForPositron      = currentDefaultCut;
   SetCutValue(cutForGamma, "gamma");
   SetCutValue(cutForElectron, "e-");
   SetCutValue(cutForPositron, "e+");
  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
  //
//   SetCutValue(defaultCutValue, "gamma");
//   SetCutValue(defaultCutValue, "e-");
//   SetCutValue(defaultCutValue, "e+");

  if (verboseLevel>0) DumpCutValuesTable();
}
