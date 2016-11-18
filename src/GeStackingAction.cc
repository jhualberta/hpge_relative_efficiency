//////////////////////////////////
///  Class: GeStackingAction
///  autor: Aleksandra Bialek 
///////////////////////////////////

#include "GeStackingAction.hh"
#include "GeAnalysis.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ios.hh"

GeStackingAction::GeStackingAction()
{ 
}
//######################################################
GeStackingAction::~GeStackingAction()
{
}
//######################################################
G4ClassificationOfNewTrack 
GeStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

  if(aTrack->GetDefinition()==G4Gamma::GammaDefinition()) { 
    if(aTrack->GetKineticEnergy() > 1.*keV) {
   
      // Record the gamma ray energy if it is a primary track
      if(aTrack->GetTrackID()==1) {
          
	GeAnalysis* analysis = GeAnalysis::getInstance();
        analysis->InsertEnergyGammaRay(aTrack->GetKineticEnergy()/keV);

      }

    }
  }


  G4ClassificationOfNewTrack classification = fUrgent;
  //  if((aTrack->GetParentID()!=0)) {classification = fKill;}    
  return classification;
}
