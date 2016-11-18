//////////////////////////////////
///  Class: GeDet
///  autor: Aleksandra Bialek 
///////////////////////////////////   

#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#ifdef G4VIS_USE
#include "GeVisManager.hh"
#endif
#include "GeDetectorConstruction.hh"
#include "GePhysicsList.hh"
#include "GePrimaryGeneratorAction.hh"
#include "GeEventAction.hh" 
#include "GeSteppingAction.hh"
#include "GeTrackingAction.hh"
#include "GeStackingAction.hh"
#include "GeRunAction.hh"
#include <sys/stat.h>
#include <G4UItcsh.hh>

int main(int argc, char *argv[])
{
  G4cout << "Number of argument: " << argc << G4endl;
  time_t start_time = time(NULL);
  pid_t pid = getpid();
  long seed = -1;
  srand (time (NULL));
  G4long mySeed = rand() % 1000000;
  if (seed == -1) seed = start_time ^ (pid << 16);
 // CLHEP::HepRandom::setTheSeed(seed);
  CLHEP::HepRandom::setTheSeed(mySeed);
  
  G4String fileName, command ="/control/execute ";

  G4cout << "Number of argument: " << argc << G4endl;
  if (argc>4) {
    G4cout << "Usage: GeDet [geometry_data_file] [run_macro_file]" << G4endl
	        << "Default files are: geom.g4mac run.mac" << G4endl;
    exit(1);
  }
 
  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();

  UI->ApplyCommand("/run/verbose 0");
  UI->ApplyCommand("/event/verbose 0");
  UI->ApplyCommand("/tracking/verbose 0");

  // set mandatory initialization classes
  GeDetectorConstruction* detector = new GeDetectorConstruction;
  runManager->SetUserInitialization(detector);
  
  G4cout << "Number of argument: " << argc << G4endl;
  (argc>1) ? fileName = argv[1]:fileName = "geom.g4mac";    
  {
    struct stat fileData;
    if(stat(fileName, &fileData)==-1)
      perror (fileName), exit(1);
    UI->ApplyCommand(command+fileName);
  }

  G4VUserPhysicsList* physics = new GePhysicsList;
  runManager->SetUserInitialization(physics);
   
#ifdef G4VIS_USE
  // Visualization
  G4VisManager* visManager = new GeVisManager;
  visManager->Initialize();
#endif

  // set mandatory user action class
  GePrimaryGeneratorAction* PrimGenAct=new GePrimaryGeneratorAction(detector);
  runManager->SetUserAction(PrimGenAct);

  if (argc>3)
    UI->ApplyCommand("/gun/rootfilename "+G4String(argv[3]));
  else 
    UI->ApplyCommand("/gun/rootfilename "+ G4String("OutFile.root"));
 
  GeEventAction* eventAction = new GeEventAction;
  runManager->SetUserAction(eventAction);
  
  GeSteppingAction*step = new GeSteppingAction(detector,eventAction,PrimGenAct);
  runManager->SetUserAction(step);  
  eventAction->SetStep(step);
  
  GeTrackingAction*beamTracking = new GeTrackingAction(step,detector);
  runManager->SetUserAction(beamTracking); 

  runManager->SetUserAction(new GeStackingAction);

  runManager->SetUserAction(new GeRunAction);
  
  if (argc==3 || argc==4) {
    fileName = argv[2];
    UI->ApplyCommand(command+fileName);     
  }
  else  UI->ApplyCommand("/control/execute run.mac");  

  G4UIsession * session = new G4UIterminal(new G4UItcsh);
  session->SessionStart();
  delete session;

  // job termination
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
  return 0;
}


