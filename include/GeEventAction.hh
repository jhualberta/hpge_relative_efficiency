///////////////////////////////////
///  Class: GeEventAction
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#ifndef GeEventAction_h
#define GeEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <fstream>

using namespace std;

class G4Event;
class GeSteppingAction;

class GeEventAction : public G4UserEventAction
{
  public:
   GeEventAction();
   ~GeEventAction();

  public:
   void BeginOfEventAction(const G4Event*);
   void EndOfEventAction(const G4Event*);
   void SetStep(GeSteppingAction*step){Step=step;};
   G4int GetEvent(){return Event;};
    
  private:
   GeSteppingAction*Step;
   G4double EnergyDep;
   G4int Event;
};

#endif
