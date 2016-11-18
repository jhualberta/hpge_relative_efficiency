//////////////////////////////////
///  Class: GeEventAction
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////   

#include "GeEventAction.hh"
#include "GeSteppingAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"

//######################################################
GeEventAction::GeEventAction()
{
}
//######################################################
GeEventAction::~GeEventAction()
{
}
//######################################################
void GeEventAction::BeginOfEventAction(const G4Event* evt)
{
  Event = evt->GetEventID();
}
//######################################################
void GeEventAction::EndOfEventAction(const G4Event* evt)
{
  static G4int counter=0;
  G4int event_id = evt->GetEventID();
  if (counter==10) {
     counter=0;
     G4cout << "\r>>> Event " << event_id ;//<< G4endl;
     fflush(stdout);
     //  G4cout << "    " << n_trajectories 
     //         << " trajectories stored in this event." << G4endl;
  }
  counter++;
}








