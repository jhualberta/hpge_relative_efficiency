///////////////////////////////////
///  Class: GePrimaryGeneratorAction
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#ifndef GeVisManager_h
#define GeVisManager_h 1

#ifdef G4VIS_USE

#include "G4VisManager.hh"

class GeVisManager: public G4VisManager 
{
  public:
   GeVisManager ();
  ~GeVisManager(){G4cout<<"VisManager deleted."<< G4endl;};
  private:
   void RegisterGraphicsSystems ();
};

#endif
#endif
