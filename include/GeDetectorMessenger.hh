///////////////////////////////////
///  Class: GeDetectorMessenger
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////   

#ifndef GeDetectorMessenger_h
#define GeDetectorMessenger_h 1

#include "globals.hh"	
#include "G4UImessenger.hh"

class GeDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;

class GeDetectorMessenger: public G4UImessenger
{
  public:
   GeDetectorMessenger(GeDetectorConstruction * myDet);
   ~GeDetectorMessenger();
    
   void SetNewValue(G4UIcommand * command, G4String newValues);
  
  private:
   GeDetectorConstruction* myDetector;
    
   G4UIdirectory*             mydetDir;
   G4UIdirectory*             scintillatorDir;
   G4UIdirectory*             PbBoxDir;  
   G4UIdirectory*             PbBrickDir;  
   
   G4UIcmdWithAString* SourceNameCmd;
    
   G4UIcmdWithADoubleAndUnit* PbBoxThicknessCmd;  
   G4UIcmdWithADoubleAndUnit* PbBoxLengthCmd;  
   G4UIcmdWithADoubleAndUnit* PbBoxHeightCmd;  

   G4UIcmdWithADoubleAndUnit* PbBrickThickness1Cmd; 
   G4UIcmdWithADoubleAndUnit* PbBrickThickness2Cmd;  
   G4UIcmdWithADoubleAndUnit* PbBrickHeightCmd;  
   G4UIcmdWithADoubleAndUnit* PbBrickLengthCmd;  

   G4UIcmdWithADoubleAndUnit* CuBoxThicknessCmd;  
   G4UIcmdWithADoubleAndUnit* CuBoxHeightCmd;  
   G4UIcmdWithADoubleAndUnit* CuBoxLengthCmd; 
 
   G4UIcmdWithADoubleAndUnit* DetBoxThicknessCmd;  
   G4UIcmdWithADoubleAndUnit* DetBoxHeightCmd;  
   G4UIcmdWithADoubleAndUnit* DetBoxLengthCmd;  

   G4UIcmdWithADoubleAndUnit* GeDetHeightCmd;  
   G4UIcmdWithADoubleAndUnit* GeDetRadiusCmd; 
   
   G4UIcmdWithADoubleAndUnit* ScintLengthCmd;  
   G4UIcmdWithADoubleAndUnit* ScintLength2Cmd;
   G4UIcmdWithADoubleAndUnit* ScintLength3Cmd;  

   G4UIcmdWithADoubleAndUnit* ScintHeightCmd;  
   G4UIcmdWithADoubleAndUnit* ScintHeight2Cmd; 
   G4UIcmdWithADoubleAndUnit* ScintHeight3Cmd;  

   G4UIcmdWithADoubleAndUnit* ScintThicknessCmd;      
   G4UIcmdWithADoubleAndUnit* ScintThickness2Cmd;  
   G4UIcmdWithADoubleAndUnit* ScintThickness3Cmd;  
  
};

#endif

