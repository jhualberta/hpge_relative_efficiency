///////////////////////////////////
///  Class: GePhysicsList
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#ifndef GePhysicsList_h
#define GePhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class GePhysicsList: public G4VUserPhysicsList
{
  public:
   GePhysicsList();
   ~GePhysicsList();

  public:
   // Construct particle and physics
   void ConstructParticle();
   void ConstructProcess();
   void SetCuts();
   
  private:
   // these methods Construct particles 
   void ConstructBosons();
   void ConstructLeptons();
   void ConstructMesons();
   void ConstructBaryons();

   // these methods Construct physics processes and register them
   void ConstructGeneral();
   void ConstructEM();
  
   G4double cutForGamma;
   G4double cutForElectron;
   G4double cutForPositron;
   G4double currentDefaultCut;
  
};

#endif
