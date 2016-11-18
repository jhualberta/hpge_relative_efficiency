//////////////////////////////////
///  Class:    GePhysicsList
///  Author:   Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///            Lee Pavelich Summer 2013
///////////////////////////////////

#include "GePrimaryGeneratorAction.hh"
#include "GeDetectorConstruction.hh"
#include "GePrimaryGeneratorMessenger.hh" 
#include "CLHEP/Random/RandExponential.h"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "globals.hh"
#include "G4UImanager.hh"

#include "G4GeneralParticleSource.hh"

using namespace CLHEP;

const G4String GePrimaryGeneratorAction::fgkDefaultParticleName = "gamma";
const G4double GePrimaryGeneratorAction::fgkDefaultEnergy       = 1*MeV;

GePrimaryGeneratorAction::GePrimaryGeneratorAction(GeDetectorConstruction* GeDC)
  :GeDetector(GeDC), 
  fGeneralParticleSource(0)
{
  fGeneralParticleSource  = new G4GeneralParticleSource(); 
  //create a messenger for this class
  gunMessenger = new GePrimaryGeneratorMessenger(this);
  
}
//######################################################
GePrimaryGeneratorAction::~GePrimaryGeneratorAction()
{
  delete fGeneralParticleSource;
}
//######################################################
void GePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // this function is called at the begining of event
  
  // Get the pointer to the User Interface manager
  G4UImanager* UI = G4UImanager::GetUIpointer();
  
  if (rndmAngleFlag == "on") {
    // Produce a random direction	
  
//    UI->ApplyCommand("/gps/particle gamma");

    // Create a random direction (uniform distribution in solid angle)
    G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
    G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    G4double ux = sinTheta*std::cos(phi),
             uy = sinTheta*std::sin(phi),
             uz = cosTheta;

    std::ostringstream osstring2;
    osstring2 << ux;
    G4String dx = osstring2.str();

    std::ostringstream osstring3;
    osstring3 << uy;
    G4String dy = osstring3.str();

    std::ostringstream osstring4;
    osstring4 << uz;
    G4String dz = osstring4.str();

    UI->ApplyCommand("/gps/direction "+dx+" "+dy+" "+dz);

    // Generate the event
    fGeneralParticleSource->GeneratePrimaryVertex(anEvent);	
    
  }
  else {
  
    // Generate the event
    fGeneralParticleSource->GeneratePrimaryVertex(anEvent);	
  
  }
	
	 

}
