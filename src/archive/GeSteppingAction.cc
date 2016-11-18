//////////////////////////////////
///  Class: GeSteppingAction
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////   

#include "GeSteppingAction.hh"
#include "GeDetectorConstruction.hh"
#include "G4SteppingManager.hh"
#include "GeEventAction.hh"
#include "GePrimaryGeneratorAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"

std::ofstream makefilefull("/hepusers/rpavelic/work/geant_work/fulldata.txt");
std::ofstream makefile("/hepusers/rpavelic/work/geant_work/data.txt");
G4double energysum = 0;
G4int iter = 0;

GeSteppingAction::GeSteppingAction(GeDetectorConstruction* myDC,GeEventAction*ev,
GePrimaryGeneratorAction*PGA)
:myDetector(myDC),eventAction(ev),PrimGenAct(PGA)
{ 
  G4cout<<"Open ReadPipe..."<<G4endl;
  OutRes.open("outres.dat",ios::out),
  OutRes.setf(ios::scientific);
  G4cout<<"Done..."<<G4endl;
  EGeDet=0;
  scint0=scint1=scint2=scint3=false;
  ged=inF=false;
  InitEn=Escint0=Escint1=Escint2=Escint3=-1.;
}
//######################################################
void GeSteppingAction::UserSteppingAction(const G4Step* aStep)
{
  if (aStep->GetTrack()->GetCurrentStepNumber()==1){
     scint0=scint1=scint2=scint3=false;
     ged=inF=false;
     InitEn=Escint0=Escint1=Escint2=Escint3=-1.;
     
     //     if (EGeDet>0 && aStep->GetTrack()->GetParticleDefinition()->GetParticleType()=="photon")
     if (EGeDet>0)
       OutRes<<E0<<" "<<Sc0<<" "<<Sc1<<" "<<Sc2<<" "<<Sc3<<" "<<EGeDet<<endl; 
       
     EGeDet = 0;
     if (iter > 0 && energysum > 0) makefile << std::setw(15) << energysum << endl;
     energysum = 0;
     Sc0=Sc1=Sc2=Sc3=E0=-2.;
  }

  iter++;


  G4Track*     track    = aStep->GetTrack();
  G4StepPoint* prePoint = NULL;
  G4StepPoint* endPoint = NULL;
  G4String     preV, postV;
  G4int        parentID;
  G4double     trackID ;
  G4String     process;
  G4int        stepNum; 
  // G4double    x = (prePoint->GetPosition().x() + endPoint->GetPosition().x()) * 0.5;
  // G4double    vel = (prePoint->GetVelocity() + endPoint->GetVelocity()) * 0.5;
  G4String     material;
  G4String     name;
 // G4double     edep = aStep->GetTotalEnergyDeposit();
  G4double     edep2;
  G4double     postenergy;
  G4double     preenergy;
  G4double     energydiff;
  

  //if (parentID == 0)
  //if (endPoint->GetPhysicalVolume() != NULL) 
 // if (track->GetNextVolume() != NULL && track->GetVolume() != NULL)
  if (track->GetNextVolume() == NULL)
     {
        prePoint = aStep->GetPreStepPoint();
        endPoint = aStep->GetPostStepPoint();
        postenergy = endPoint->GetTotalEnergy();
        edep2 = prePoint->GetTotalEnergy()-endPoint->GetTotalEnergy();
        parentID = aStep->GetTrack()->GetParentID();
        trackID  = aStep->GetTrack()->GetTrackID();
        process  = endPoint->GetProcessDefinedStep()->GetProcessName();
        stepNum  = aStep->GetTrack()->GetCurrentStepNumber();
        name = aStep->GetTrack()->GetDefinition()->GetParticleName();
        material = prePoint->GetMaterial()->GetName();
        preenergy = prePoint->GetTotalEnergy();
        energydiff = preenergy - postenergy;
	
	makefilefull
	  << std::setw(5)  << trackID
	  << std::setw(15) << stepNum
	  << std::setw(10) << name
	  << std::setw(20) << process
	  << std::setw(20) << material
	  << std::setw(15) << preenergy/MeV
	  << std::setw(15) << postenergy/MeV
	  << std::setw(15) << energydiff/MeV
	  //<< std::setw(15) << energysum/MeV
	  << std::endl;

	
	if (material == "Germanium" && process != "Transportation" && name == "gamma" /*&& trackID == 1*/)
	{
	  makefile
	    << std::setw(15) << trackID
	    << std::setw(15) << stepNum
	    << std::setw(15) << name
	    << std::setw(15) << process
	    << std::setw(15) << material
	    << std::setw(15) << preenergy/MeV
	    << std::setw(15) << postenergy/MeV
	    << std::setw(15) << edep2/MeV  //just plain edep doesn't work ATM
	    << std::endl;
	}
	

    }
  else {track->SetTrackStatus(fStopAndKill); }
  


/*
  if (endPoint != NULL){
  //if (endPoint->GetPhysicalVolume()!=NULL){
    
 
     preV =prePoint->GetPhysicalVolume()->GetName();
     postV=endPoint->GetPhysicalVolume()->GetName();
   
     if (postV=="Scintillator_0" && preV!="Scintillator_0"){
        Escint0=aStep->GetTrack()->GetKineticEnergy()/GeV;
     }
     if (postV!="Scintillator_0" && preV=="Scintillator_0"){    
        Escint0l=aStep->GetTrack()->GetKineticEnergy()/GeV;
        scint0=true;
     }
     if (postV=="GeDet" ){//&& preV!= "GeDet"){
       EGeDet+=prePoint->GetTotalEnergy()-endPoint->GetTotalEnergy();
       //	G4cout << " Energy deposit: " << EGeDet << endl;
       //       G4cout << " Total energy1: " << prePoint->GetTotalEnergy() << " " << endPoint->GetTotalEnergy();
	ged=true;
	
     }
     //     if (postV!="GeDet" && EGeDet>0)
     //ged=true;
     if (postV=="Scintillator_1" && preV!="Scintillator_1"){
        Escint1=aStep->GetTrack()->GetKineticEnergy()/GeV;
     }
     if (postV!="Scintillator_1" && preV=="Scintillator_1"){
        Escint1l=aStep->GetTrack()->GetKineticEnergy()/GeV;
        scint1=true;
     }
     if (postV=="Scintillator_2" && preV!="Scintillator_2"){
        Escint2=aStep->GetTrack()->GetKineticEnergy()/GeV;
     }
     if (postV!="Scintillator_2" && preV=="Scintillator_2"){
        Escint2l=aStep->GetTrack()->GetKineticEnergy()/GeV;
        scint2=true;
     }
     if (postV=="Scintillator_3" && preV!="Scintillator_3"){
        Escint3=aStep->GetTrack()->GetKineticEnergy()/GeV;
     }
     if (postV!="Scintillator_3" && preV=="Scintillator_3"){
        Escint3l=aStep->GetTrack()->GetKineticEnergy()/GeV;
        scint3=true;
     } 

     //trigger condition:
     //     if ((scint0 || scint1 || scint2) && (scint1 || scint2 || scint3) && ged && !inF){  
     if (ged ){  

       Sc0=Escint0-Escint0l; 
       Sc1=Escint1-Escint1l; 
       Sc2=Escint2-Escint2l; 
       //        Sc3=Escint3-Escint3l; 
       // E0=G4double(PrimGenAct->Get0Energy()/GeV);
       
	// OutRes<<E0<<" "<<Sc0<<" "<<Sc1<<" "<<Sc2<<" "<<Sc3<<" "<<EGeDet<<endl; 
	//        inF=true;
     }
  }*/

 
}
