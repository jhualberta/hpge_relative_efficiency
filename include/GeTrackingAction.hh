///////////////////////////////////
///  Class: GeTrackingAction
///  autor: Aleksandra Bialek
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#ifndef GeTrackingAction_h
#define GeTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"
using namespace std;

class GeSteppingAction;
class GeDetectorConstruction;

class GeTrackingAction : public G4UserTrackingAction 
{
  public:
   GeTrackingAction(GeSteppingAction*step, GeDetectorConstruction*detector){Step=step;myDetector=detector;};
   virtual ~GeTrackingAction(){};
   
   virtual void PreUserTrackingAction(const G4Track*);
   virtual void PostUserTrackingAction(const G4Track*);

  private:
   GeSteppingAction*Step;
   GeDetectorConstruction*myDetector;
};
#endif
