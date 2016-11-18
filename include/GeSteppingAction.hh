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
#include "TTree.h"
#include "TFile.h"

using namespace std;

class GeDetectorConstruction;
class GeTrackingAction;
class GeEventAction;
class GePrimaryGeneratorAction;

class GeSteppingAction : public G4UserSteppingAction
{
  public:
   GeSteppingAction(GeDetectorConstruction* myDC,GeEventAction*ev,GePrimaryGeneratorAction*PGA);
  virtual ~GeSteppingAction();
				    
   virtual void UserSteppingAction(const G4Step*);
  
  // Functions added to be called from run action 
  void InitializeRootFiles(G4String fName);
  void ClearRootFiles();
    
  private:
  G4int HowFlags;
  GeDetectorConstruction* myDetector;
  GeEventAction*eventAction;
   ofstream OutRes;
	GePrimaryGeneratorAction*PrimGenAct;

    G4double InitEn, Escint0, Escint1, Escint2, Escint3, Escint4, Escint5, EGeDet, EGeDetSm;
    G4bool scint0,scint1,scint2,scint3, scint4, scint5,ged,inF;

  G4int evtr;
  //  double Sc0, Sc1, Sc2, Sc3, 
  double E0;

  TTree *getree;
  TFile *gefyle;

};
#endif
