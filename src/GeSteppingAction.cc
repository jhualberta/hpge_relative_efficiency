//////////////////////////////////
///  Class: GeSteppingAction
///  autor: Aleksandra Bialek 
///////////////////////////////////   

#include "GeSteppingAction.hh"
#include "GeDetectorConstruction.hh"
#include "G4SteppingManager.hh"
#include "GeEventAction.hh"
#include "GePrimaryGeneratorAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"

#include "GeAnalysis.hh"

#include "TROOT.h"
#include "TFile.h"

#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/RandGauss.h"

using namespace CLHEP;

NonRandomEngine eng;
RandGauss dist (eng);

GeSteppingAction::GeSteppingAction(GeDetectorConstruction* myDC,GeEventAction*ev,
GePrimaryGeneratorAction*PGA)
:myDetector(myDC),eventAction(ev),PrimGenAct(PGA)
{ 
  

}

GeSteppingAction::~GeSteppingAction(){

}

// Functions which are called from RunAction at the beginning and end of each run
// These functions create and clear the root output files between runs
// Were previously in the constructor and destructor functions (just simply moved)
void GeSteppingAction::InitializeRootFiles(G4String fName)
{

  // Forced into the new output directory
  fName = "output/" + fName;

  EGeDet=EGeDetSm=0;
  scint0=scint1=scint2=scint3=scint4=scint5=false;
  ged=inF=false;
  InitEn=Escint0=Escint1=Escint2=Escint3=Escint4=Escint5=-1.;

 // gefyle = new TFile(PGA->GetFilename()->data(),"recreate");
 // G4cout << " Opened file: '" << PGA->GetFilename()->data()<<"'" << endl;
  gefyle = new TFile(fName,"recreate");
  G4cout << " Opened file: '" <<fName<<"'" << endl;
  getree = new TTree("T","T");
  getree->Branch("InitEn",&InitEn,"InitEn/D");
  getree->Branch("Escint0",&Escint0,"Escint0/D");
  getree->Branch("Escint1",&Escint1,"Escint1/D");
  getree->Branch("Escint2",&Escint2,"Escint2/D");
  getree->Branch("Escint3",&Escint3,"Escint3/D");
  getree->Branch("Escint4",&Escint4,"Escint4/D");
  getree->Branch("Escint5",&Escint5,"Escint5/D");
  getree->Branch("EGeDet",&EGeDet,"EGeDet/D");
  getree->Branch("EGeDetSm",&EGeDetSm,"EGeDetSm/D");


}

void GeSteppingAction::ClearRootFiles()
{
  G4cout << " End of Run (writing files...) " << G4endl;
  if (gefyle != 0){
    getree->Write();
    gefyle->Close();
    delete gefyle;
    gefyle = 0;
    getree = 0;
  }
}

//######################################################
void GeSteppingAction::UserSteppingAction(const G4Step* aStep)
{

  if (aStep->GetTrack()->GetTrackID()==1){
     ged=inF=false;
     
     //     if (EGeDet>0 && aStep->GetTrack()->GetParticleDefinition()->GetParticleType()=="photon")
     if (EGeDet>0||scint0||scint1||scint2||scint3||scint4||scint5){

       // Smearing code; applys a resolution function of a * sqrt ( E ) + b * E + c
       double a = 0.00503738, b = 0.000175094, c = 0.482116; // from a fit to data
       EGeDetSm += dist.shoot (0, (a * sqrt (EGeDetSm*1000.) + b * EGeDetSm*1000. + c) / 1000.);

       getree->Fill();
       //       G4cout << E0/MeV << " " << EGeDet << " " << aStep->GetTotalEnergyDeposit()/MeV<< " " << aStep->GetTrack()->GetTrackID()<< " " <<
       //       	 aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;       
     
       // Added data storage to local simulation for automatic efficiency calculation
       GeAnalysis* analysis = GeAnalysis::getInstance();
       analysis->InsertEnergyGe(EGeDet*1000);
       // End addition
      
     
     }
     
     

     
     EGeDet   = 0;
     EGeDetSm = 0;
     InitEn=Escint0=Escint1=Escint2=Escint3=Escint4=Escint5=0.;
     scint0=scint1=scint2=scint3=scint4=scint5=false;
     //     Sc0=Sc1=Sc2=Sc3=E0=-2.;
  }
  //       G4cout << E0/MeV << " " << EGeDet << " " << aStep->GetTotalEnergyDeposit()/MeV<< " " << aStep->GetTrack()->GetTrackID()<< " " <<
  //       	 aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;       

  G4StepPoint* prePoint = aStep->GetPreStepPoint();
  G4StepPoint* endPoint = aStep->GetPostStepPoint();

  if (endPoint->GetPhysicalVolume()!=NULL){
     G4String preV, postV;
 
     preV =prePoint->GetPhysicalVolume()->GetName();
     postV=endPoint->GetPhysicalVolume()->GetName();
     //     G4cout << "DEBUG:  "<< preV << " " << postV << " " << aStep->GetTotalEnergyDeposit()<< " " <<aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl; 
   
     if (postV=="BSCPVO" && preV=="BSCPVO"){ // Bottom tank scintillator
        Escint0+=aStep->GetTotalEnergyDeposit()/GeV;
        scint0=true;
     }
     if (postV=="TSCPVO" && preV=="TSCPVO"){ // Top tank scintillator
        Escint1+=aStep->GetTotalEnergyDeposit()/GeV;
        scint1=true;
     }
     if (postV=="BTSCPVO" && preV=="BTSCPVO"){ // Back top tank scintillator
        Escint2+=aStep->GetTotalEnergyDeposit()/GeV;
        scint2=true;
     }
     if (postV=="BBSCPVO" && preV=="BBSCPVO"){ // Back bottom tank scintillator
        scint3=true;
     }
     if (postV=="LBSCPVO" && preV=="LBSCPVO"){ // Left bottom tank scintillator
        Escint3+=aStep->GetTotalEnergyDeposit()/GeV;
        scint3=true;
     }
     if (postV=="FTSCPVO" && preV=="FTSCPVO"){ // Front top tank scintillator
        Escint4+=aStep->GetTotalEnergyDeposit()/GeV;
        scint4=true;
     }
     if (postV=="FBSCPVO" && preV=="FBSCPVO"){ // Front bottom tank scintillator
        Escint4+=aStep->GetTotalEnergyDeposit()/GeV;
        scint4=true;
     }
     if (postV=="RTSCPVO" && preV=="RTSCPVO"){ // Right top tank scintillator
        Escint5+=aStep->GetTotalEnergyDeposit()/GeV;
        scint5=true;
     }
     if (postV=="RBSCPVO" && preV=="RBSCPVO"){ // right bottom tank scintillator
        Escint5+=aStep->GetTotalEnergyDeposit()/GeV;
        scint5=true;
     }
     if (postV=="GeDet" && preV == "GeDet"){
       EGeDet   += aStep->GetTotalEnergyDeposit();
       EGeDetSm += aStep->GetTotalEnergyDeposit();
	 //prePoint->GetTotalEnergy()-endPoint->GetTotalEnergy();
       //	G4cout << " Energy deposit: " << EGeDet << endl;
       //       G4cout << " Total energy1: " << prePoint->GetTotalEnergy() << " " << endPoint->GetTotalEnergy();
	ged=true;
	
     }
     //trigger condition:
     //     if ((scint0 || scint1 || scint2) && (scint1 || scint2 || scint3) && ged && !inF){  
     // if (ged ){  
     //   InitEn=G4double(PrimGenAct->Get0Energy()/GeV);
     //}
  }

}
