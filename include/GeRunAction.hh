
#ifndef GeRunAction_h
#define GeRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class GeRunActionMessenger;

class GeRunAction : public G4UserRunAction
{
  public:
    GeRunAction();
   ~GeRunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

    void SetFileName(G4String fName) { fileName = fName; };
    G4String GetFileName() { return fileName; };
    void SetSourceFileFlag(G4String flag) { sourceFileFlag = flag; };
    G4String GetSourceFileFlag() { return sourceFileFlag; };
    void SetRootName(G4String name) { rootName = name; };
    G4String GetRootName() { return rootName; };
    
  private:

  GeRunActionMessenger* runMessenger;
  
  G4String fileName;
  G4String rootName;
  G4String sourceFileFlag;

};

#endif
