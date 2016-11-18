
#include "GeRunActionMessenger.hh"
#include "GeRunAction.hh"

#include "G4UIcmdWithAString.hh"

GeRunActionMessenger::GeRunActionMessenger(GeRunAction* run):
  r_action(run)
{

  fNameCmd = new G4UIcmdWithAString("/analysis/fileName", this);
  fNameCmd->SetGuidance("Print the simulation data to root files.");
  fNameCmd->SetParameterName("choice",true);
  fNameCmd->SetDefaultValue("hist");
  fNameCmd->AvailableForStates(G4State_PreInit);
  
  fSourceFileCmd = new G4UIcmdWithAString("/analysis/genSourceFile", this);
  fSourceFileCmd->SetGuidance("Replace the point source efficiency file.");
  fSourceFileCmd->SetParameterName("flag",true);
  fSourceFileCmd->SetDefaultValue("false");
  fSourceFileCmd->AvailableForStates(G4State_PreInit);

}

GeRunActionMessenger::~GeRunActionMessenger()
{
  delete fNameCmd;
}

void GeRunActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{

  if (command == fNameCmd)
    { r_action->SetFileName(newValue); }
  else if (command == fSourceFileCmd)
    { r_action->SetSourceFileFlag(newValue); }

}