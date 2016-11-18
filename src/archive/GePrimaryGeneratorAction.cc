//////////////////////////////////
///  Class: GePhysicsList
///  autor: Aleksandra Bialek 
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

using namespace CLHEP;

GePrimaryGeneratorAction::GePrimaryGeneratorAction(GeDetectorConstruction* GeDC)
:GeDetector(GeDC)
{
  rndmPositionFlag="on";
  rndmPositionType="top";
  rndmEnergyFlag="on";
  rndmEnergyType=-1;
  rndmAngleFlag="off";

  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
  
  //create a messenger for this class
  gunMessenger = new GePrimaryGeneratorMessenger(this);
  
  mom = new G4ThreeVector(0.,0.,1.);
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  particle = particleTable->FindParticle(particleName="e-");
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  particleGun->SetParticleEnergy(1*MeV);
  G4double Zposition = 0.*mm;
  G4double Xposition = 0.*mm;
  G4double Yposition = 600.*mm;
  particleGun->SetParticlePosition(G4ThreeVector(Xposition,Yposition,Zposition));
  G4ThreeVector pos = particleGun->GetParticlePosition();
}
//######################################################
GePrimaryGeneratorAction::~GePrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
  delete mom;
}
//######################################################
G4ThreeVector GePrimaryGeneratorAction::Get0Postion()
{
  return particleGun->GetParticlePosition();
}
//######################################################
G4double GePrimaryGeneratorAction::Get0Energy()
{
  return particleGun->GetParticleEnergy();
}
//######################################################
void GePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double Energy=-1.;    
  G4double z0 = 0., x0 = 0., y0 = 0.;
  G4double phi;

  if (rndmPositionFlag == "on"){
	  if (rndmPositionType == "top"){
		  G4double const Z0=-550, Z1=550;
		  G4double const Y0=585,  Y1=695;
		  G4double const X0=-550.,X1=550.;

		  z0 = (Z1-Z0)*G4UniformRand()+Z0;//rand pseudo number 
		  y0 = (Y1-Y0)*G4UniformRand()+Y0;//rand pseudo number 
		  x0 = (X1-X0)*G4UniformRand()+X0;
	  }
	  else{ 
		  G4cout<<"Unexpected type of randomize of position!"<<G4endl;
		  exit(-1);
	  }
     particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));  		
  } 
  
  if (rndmEnergyFlag == "on"){
     double mean=10*GeV;
     Energy=RandExponential::shoot(mean)+G4RandGauss::shoot(5,1);
	  particleGun->SetParticleEnergy(Energy);
  }
  else{
     Energy=rndmEnergyType;
     particleGun->SetParticleEnergy(Energy);
  }

  if (rndmAngleFlag == "on"){
     G4double DeltaAngle=theAngle;
	  G4double Theta = DeltaAngle*G4UniformRand();
     phi = G4UniformRand()*(2*pi);

     mom->setX(sin(Theta)*cos(phi));
     mom->setY(-(cos(Theta)));
     mom->setZ((sin(Theta)*sin(phi)));
	  particleGun->SetParticleMomentumDirection(*mom);
  }
  else{
    phi = G4UniformRand()*(2*pi);
    G4double Theta = pi * G4UniformRand();
    mom->setX(sin(Theta)*cos(phi));
    mom->setY(-(cos(Theta)));
    mom->setZ((sin(Theta)*sin(phi)));
    particleGun->SetParticleMomentumDirection(*mom);
  }

  particleGun->GeneratePrimaryVertex(anEvent);
}
