///////////////////////////////////
///  Class: GePrimaryGeneratorAction
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#ifndef GeStackingAction_H
#define GeStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "G4ThreeVector.hh"

class G4Track;

class GeStackingAction : public G4UserStackingAction
{
  public:
   GeStackingAction();
   virtual ~GeStackingAction();

  public:
   virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
};

#endif
