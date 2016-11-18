///////////////////////////////////
///  Class: GePrimaryGeneratorAction
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#ifndef GePrimaryGeneratorAction_h
#define GePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh" 
#include "G4ThreeVector.hh"
#include <fstream>

using namespace std;

class GeDetectorConstruction;
class G4ParticleGun;
class G4Event;
class GePrimaryGeneratorMessenger;
class RandGeneral;
class G4ParticleDefinition;
class G4GeneralParticleSource;

class GePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
   GePrimaryGeneratorAction(GeDetectorConstruction*);
   ~GePrimaryGeneratorAction();

   void GeneratePrimaries(G4Event* anEvent);
   void SetRndmEnergyFlag(G4String val)   { rndmEnergyFlag = val;}
   void SetRndmEnergyType(G4double val)   { rndmEnergyType = val;}
   void SetRndmPositionFlag(G4String val) { rndmPositionFlag = val;}
   void SetRndmPositionType(G4String val) { rndmPositionType = val;}
   void SetRndmAngleFlag(G4String val)    { rndmAngleFlag = val;} 
   void SetAngle(G4double val)            {theAngle = val;}
   void SetFilename(G4String name) {sOutFilename = name;};
  //G4ThreeVector Get0Postion();
  //G4double Get0Energy();
  G4String*GetFilename() {return &sOutFilename;};

  private:
   static const G4String fgkDefaultParticleName;
   static const G4double fgkDefaultEnergy;
   GeDetectorConstruction* GeDetector;  //pointer to the geometry 
   G4String sOutFilename;
   G4GeneralParticleSource* fGeneralParticleSource;
    
  protected:
   G4double theAngle;
   G4ThreeVector *mom;
   GePrimaryGeneratorMessenger* gunMessenger; // messenger of this class
   G4String rndmEnergyFlag;                   // flags for a random  
   G4double rndmEnergyType;                   // 
   G4String rndmPositionType;                 //
   G4String rndmPositionFlag;                 //        
   G4String rndmAngleFlag;                    //
};
#endif
