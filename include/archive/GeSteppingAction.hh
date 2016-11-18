///////////////////////////////////
///  Class: GeSteppingAction
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#ifndef GeSteppingAction_h
#define GeSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <fstream> 
#include "G4DecayTable.hh"

using namespace std;

class GeDetectorConstruction;
class GeTrackingAction;
class GeEventAction;
class GePrimaryGeneratorAction;
class G4Step;

class GeSteppingAction : public G4UserSteppingAction
{
  public:
   GeSteppingAction(GeDetectorConstruction* myDC,GeEventAction*ev,GePrimaryGeneratorAction*PGA);
   virtual ~GeSteppingAction(){OutRes.close();}
				    
   virtual void UserSteppingAction(const G4Step*);
    
  private:
   G4int HowFlags;
   GeDetectorConstruction* myDetector;
   GeEventAction*eventAction;
   ofstream OutRes;
	GePrimaryGeneratorAction*PrimGenAct;

    G4double InitEn, Escint0, Escint0l, Escint1, Escint1l, Escint2, Escint2l, Escint3, Escint3l, EGeDet;
    G4bool scint0,scint1,scint2,scint3,ged,inF;
  G4int evtr;
  double Sc0, Sc1, Sc2, Sc3, E0;
};
#endif
