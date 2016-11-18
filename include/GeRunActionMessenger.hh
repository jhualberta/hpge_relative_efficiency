
#ifndef GeRunActionMessenger_h
#define GeRunActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class GeRunAction;
class G4UIcmdWithAString;

class GeRunActionMessenger: public G4UImessenger
{
  public:
    GeRunActionMessenger(GeRunAction*);
   ~GeRunActionMessenger();

    void SetNewValue(G4UIcommand*, G4String);

  private:
    GeRunAction* r_action;
    G4UIcmdWithAString* fNameCmd;
    G4UIcmdWithAString* fSourceFileCmd;

};

#endif
