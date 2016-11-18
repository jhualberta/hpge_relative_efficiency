//////////////////////////////////
///  Class: GePrimaryGeneratorMessenger
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#include "GePrimaryGeneratorMessenger.hh"

#include "GePrimaryGeneratorAction.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

GePrimaryGeneratorMessenger::GePrimaryGeneratorMessenger(GePrimaryGeneratorAction* GeGun)
:GeAction(GeGun)
{ 
  RndmPositionCmd = new G4UIcmdWithAString("/gun/PositionRandom",this);
  RndmPositionCmd->SetGuidance("Shoot randomly the incident particle.");
  RndmPositionCmd->SetGuidance("  Choice : on(default), off");
  RndmPositionCmd->SetParameterName("choice",true);
  RndmPositionCmd->SetDefaultValue("on");
  RndmPositionCmd->SetCandidates("on off");
  RndmPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  RndmPositionType = new G4UIcmdWithAString("/gun/PositionRandomType",this);
  RndmPositionType->SetGuidance("Type of generator.");
  RndmPositionType->SetGuidance("Choice: top(default), beam, linear");
  RndmPositionType->SetParameterName("choice",true);
  RndmPositionType->SetDefaultValue("top");
  RndmPositionType->SetCandidates("linear beam top");
  RndmPositionType->AvailableForStates(G4State_PreInit,G4State_Idle);
//  ENERGY FLAGS
  RndmEnergyCmd = new G4UIcmdWithAString("/gun/EnergyRandom",this);
  RndmEnergyCmd->SetGuidance("Shoot randomly energy of the particle.");
  RndmEnergyCmd->SetGuidance("  Choice : on(default), off");
  RndmEnergyCmd->SetParameterName("choice",true);
  RndmEnergyCmd->SetDefaultValue("off");
  RndmEnergyCmd->SetCandidates("on off");
  RndmEnergyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  RndmEnergyType = new G4UIcmdWithADoubleAndUnit("/gun/Energy",this);
  RndmEnergyType->SetGuidance("Energy of the particle");
  RndmEnergyType->SetParameterName("Energy",false,false);
  RndmEnergyType->SetDefaultUnit("MeV");
  RndmEnergyType->SetUnitCategory("Energy");
  RndmEnergyType->AvailableForStates(G4State_PreInit,G4State_Idle);
// ANGLE FLAG
  RndmAngleCmd = new G4UIcmdWithAString("/gun/MomentumRandom",this);
  RndmAngleCmd->SetGuidance("Shoot randomly momentum of the particle.");
  RndmAngleCmd->SetGuidance("  Choice : off(default), on");
  RndmAngleCmd->SetParameterName("choice",true);
  RndmAngleCmd->SetDefaultValue("off");
  RndmAngleCmd->SetCandidates("on off");
  RndmAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
//Angle value 
  
  AngleCmd = new G4UIcmdWithADouble("/gun/Angle",this);
  AngleCmd->SetGuidance("Set angle of particle's momentum.");
  AngleCmd->SetGuidance("  Choice : off(default), on");
  AngleCmd->SetParameterName("choice",true);
  AngleCmd->SetDefaultValue(1.);
  AngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  OutFileNameCmd = new G4UIcmdWithAString("/gun/rootfilename",this);
  OutFileNameCmd->SetGuidance("Output file name.");
  OutFileNameCmd->SetParameterName("Filename",false,false);
  OutFileNameCmd->SetDefaultValue("default_root_file.root");
  OutFileNameCmd->AvailableForStates(G4State_PreInit);

}
//######################################################
GePrimaryGeneratorMessenger::~GePrimaryGeneratorMessenger()
{
  delete RndmPositionCmd;
  delete RndmPositionType;
  delete RndmEnergyCmd;
  delete RndmEnergyType;
  delete RndmAngleCmd;
  delete OutFileNameCmd;

}
//######################################################
void GePrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  if(command == RndmPositionCmd )     {GeAction->SetRndmPositionFlag(newValue);}
  else if(command == RndmPositionType){GeAction->SetRndmPositionType(newValue);}
  else if(command == RndmEnergyCmd )  {GeAction->SetRndmEnergyFlag(newValue);}
  else if(command == RndmEnergyType)  {GeAction->SetRndmEnergyType(RndmEnergyType->GetNewDoubleValue(newValue) );}
  else if(command == RndmAngleCmd)    {GeAction->SetRndmAngleFlag(newValue);}
  else if(command == AngleCmd)        {GeAction->SetAngle(AngleCmd->GetNewDoubleValue(newValue)*(pi/180));}
  else if(command == OutFileNameCmd)  {GeAction->SetFilename(newValue);}

}
