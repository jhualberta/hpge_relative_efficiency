//////////////////////////////////
///  Class: GeTrackingAction
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#include "GeTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "GeSteppingAction.hh"
#include "GeDetectorConstruction.hh"

void GeTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  
#if 0
  fpTrackingManager->SetStoreTrajectory(true);
#endif
}
//######################################################
void GeTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{

}
