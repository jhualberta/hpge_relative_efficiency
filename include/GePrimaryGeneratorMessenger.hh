///////////////////////////////////
///  Class: GePrimaryGeneratorMessenger
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#ifndef GePrimaryGeneratorMessenger_h
#define GePrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"
#include "G4UIcmdWithAString.hh"

class GePrimaryGeneratorAction;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;

class GePrimaryGeneratorMessenger: public G4UImessenger
{
  public:
   GePrimaryGeneratorMessenger(GePrimaryGeneratorAction*);
   ~GePrimaryGeneratorMessenger();
    
   void SetNewValue(G4UIcommand*, G4String);
    
  private:
   GePrimaryGeneratorAction*  GeAction; 
   G4UIcmdWithADouble*		   AngleCmd;    
   G4UIcmdWithAString*        RndmEnergyCmd;
   G4UIcmdWithADoubleAndUnit* RndmEnergyType;
   G4UIcmdWithAString*        RndmPositionCmd;
   G4UIcmdWithAString*		   RndmPositionType;
   G4UIcmdWithAString*        RndmAngleCmd;
  G4UIcmdWithAString* OutFileNameCmd;

};

#endif

