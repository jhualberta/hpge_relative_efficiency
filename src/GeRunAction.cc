
#include "GeRunAction.hh"
#include "GeRunActionMessenger.hh"
#include "GeAnalysis.hh"
#include "GeSteppingAction.hh"

#include "G4RunManager.hh"

#include "G4Run.hh"
#include "G4ios.hh"
#include "globals.hh"

// Includes for writing to text file
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

GeRunAction::GeRunAction()
{
  // Initialize the default file name
  fileName = "hist";
  
  // Initialize the default source file generator flag
  sourceFileFlag = "false";

  // Create the messenger for this class
  runMessenger = new GeRunActionMessenger(this);
}

GeRunAction::~GeRunAction()
{
  delete runMessenger;
}

void GeRunAction::BeginOfRunAction(const G4Run* aRun)
{

  // Creation of the analysis manager
  GeAnalysis* analysis = GeAnalysis::getInstance();
  analysis->BeginOfRun();

  G4int RunN = aRun->GetRunID();
  G4cout << "*** Run : " << (RunN+1) << " *************************" << G4endl;
  
  if (RunN == 0 && sourceFileFlag == "true") {
    // Delete the old source file and replace it with and empty file with the headers written in
    ofstream fout;

    fileName = "PointSource_Reference";
    G4String fName = fileName + ".txt";
    
    // Forced into the new output directory
    fName = "output/" + fName;

    fout.open(fName, ios::out);
    if(!fout.fail()) {

      fout<<"Energy(keV) Produced Counts"<<endl;

      fout.close();

    }
  
  }
  else if (RunN == 0 && sourceFileFlag == "false") {
    // Delete the output file and replace it with and empty file with the headers written in (using specfied naming scheme this time)
    ofstream fout;

    G4String fName = fileName + ".txt";
    
    // Forced into the new output directory
    fName = "output/" + fName;

    fout.open(fName, ios::out);
    if(!fout.fail()) {

      fout<<"Energy(keV) Relative_Efficiency"<<endl;

      fout.close();

    }
  
  }
  // Else nothing needed as files would get overwritten between runs
  
  // Create the name for the root output file based on the file name given and
  // the current run number
  std::ostringstream osstringn;
  osstringn << (RunN+1);
  G4String runNum = osstringn.str();
  rootName = fileName + "_" + runNum + ".root";

  G4cout<<rootName<<G4endl;
  
  // Execure the code to initialize the root files in SteppingAction
  // Pass along the current root file name to the class
  GeSteppingAction* step = (GeSteppingAction*)
  G4RunManager::GetRunManager()->GetUserSteppingAction();  
  step->InitializeRootFiles(rootName);
  
}

void GeRunAction::EndOfRunAction(const G4Run* )
{
  // Close the analysis manager
  GeAnalysis* analysis = GeAnalysis::getInstance();
  analysis->EndOfRun();
  
    // Execure the code to clear the root files in SteppingAction
  GeSteppingAction* step = (GeSteppingAction*)
  G4RunManager::GetRunManager()->GetUserSteppingAction();
  step->ClearRootFiles();
  
}

