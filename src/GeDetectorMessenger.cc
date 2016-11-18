///////////////////////////////////
///  Class: GeDetectorMessenger
///  autor: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///////////////////////////////////

#include "GeDetectorMessenger.hh"
#include "GeDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ThreeVector.hh"

GeDetectorMessenger::GeDetectorMessenger(GeDetectorConstruction * myDet)
:myDetector(myDet)
{ 
  mydetDir = new G4UIdirectory("/mydet/");
  mydetDir->SetGuidance("Detector control.");
  
  SourceNameCmd = new G4UIcmdWithAString("/mydet/sourceName", this);
  SourceNameCmd->SetGuidance("Name of source geometry to use.");
  SourceNameCmd->SetParameterName("Name", false);  
  SourceNameCmd->AvailableForStates(G4State_PreInit);
  
  scintillatorDir = new G4UIdirectory("/mydet/scintillator/");
  scintillatorDir->SetGuidance("Scintillator control.");
	
  PbBoxDir = new G4UIdirectory("/mydet/PbBox/");
  PbBoxDir->SetGuidance("Lead box control.");

  PbBrickDir = new G4UIdirectory("/mydet/PbBrick/");
  PbBrickDir->SetGuidance("Lead brick control.");

  PbBoxThicknessCmd = new G4UIcmdWithADoubleAndUnit("/mydet/PbBox/thickness",this);
  PbBoxThicknessCmd->SetGuidance("Pb box thickness.");
  PbBoxThicknessCmd->SetParameterName("Distance",false,false);
  PbBoxThicknessCmd->SetDefaultUnit("mm");
  PbBoxThicknessCmd->SetUnitCategory("Length");
  PbBoxThicknessCmd->AvailableForStates(G4State_PreInit);

  PbBoxLengthCmd = new G4UIcmdWithADoubleAndUnit("/mydet/PbBox/length",this);
  PbBoxLengthCmd->SetGuidance("Width of the Pb bricks box.");
  PbBoxLengthCmd->SetParameterName("Distance",false,false);
  PbBoxLengthCmd->SetDefaultUnit("mm");
  PbBoxLengthCmd->SetUnitCategory("Length");
  PbBoxLengthCmd->AvailableForStates(G4State_PreInit);

  PbBoxHeightCmd = new G4UIcmdWithADoubleAndUnit("/mydet/PbBox/height",this);
  PbBoxHeightCmd->SetGuidance("Height of the Pb bricks box.");
  PbBoxHeightCmd->SetParameterName("Distance",false,false);
  PbBoxHeightCmd->SetDefaultUnit("mm");
  PbBoxHeightCmd->SetUnitCategory("Length");
  PbBoxHeightCmd->AvailableForStates(G4State_PreInit);
	
  PbBrickThickness1Cmd = new G4UIcmdWithADoubleAndUnit("/mydet/PbBrick/thickness1",this);
  PbBrickThickness1Cmd->SetGuidance("Pb brick thickness.");
  PbBrickThickness1Cmd->SetParameterName("Distance",false,false);
  PbBrickThickness1Cmd->SetDefaultUnit("mm");
  PbBrickThickness1Cmd->SetUnitCategory("Length");
  PbBrickThickness1Cmd->AvailableForStates(G4State_PreInit);
  
  PbBrickThickness2Cmd = new G4UIcmdWithADoubleAndUnit("/mydet/PbBrick/thickness2",this);
  PbBrickThickness2Cmd->SetGuidance("Pb brick thickness.");
  PbBrickThickness2Cmd->SetParameterName("Distance",false,false);
  PbBrickThickness2Cmd->SetDefaultUnit("mm");
  PbBrickThickness2Cmd->SetUnitCategory("Length");
  PbBrickThickness2Cmd->AvailableForStates(G4State_PreInit);

  PbBrickHeightCmd = new G4UIcmdWithADoubleAndUnit("/mydet/PbBrick/height",this);
  PbBrickHeightCmd->SetGuidance("Height of the Pb bricks.");
  PbBrickHeightCmd->SetParameterName("Distance",false,false);
  PbBrickHeightCmd->SetDefaultUnit("mm");
  PbBrickHeightCmd->SetUnitCategory("Length");
  PbBrickHeightCmd->AvailableForStates(G4State_PreInit);
	
  PbBrickLengthCmd = new G4UIcmdWithADoubleAndUnit("/mydet/PbBrick/length",this);
  PbBrickLengthCmd->SetGuidance("Length of the Pb bricks.");
  PbBrickLengthCmd->SetParameterName("Distance",false,false);
  PbBrickLengthCmd->SetDefaultUnit("mm");
  PbBrickLengthCmd->SetUnitCategory("Length");
  PbBrickLengthCmd->AvailableForStates(G4State_PreInit);
	
  CuBoxThicknessCmd = new G4UIcmdWithADoubleAndUnit("/mydet/CuBox/thickness",this);
  CuBoxThicknessCmd->SetGuidance("cooper box (GeDet) thickness.");
  CuBoxThicknessCmd->SetParameterName("Distance",false,false);
  CuBoxThicknessCmd->SetDefaultUnit("mm");
  CuBoxThicknessCmd->SetUnitCategory("Length");
  CuBoxThicknessCmd->AvailableForStates(G4State_PreInit);

  CuBoxHeightCmd = new G4UIcmdWithADoubleAndUnit("/mydet/CuBox/height",this);
  CuBoxHeightCmd->SetGuidance("cooper box (GeDet) Height.");
  CuBoxHeightCmd->SetParameterName("Distance",false,false);
  CuBoxHeightCmd->SetDefaultUnit("mm");
  CuBoxHeightCmd->SetUnitCategory("Length");
  CuBoxHeightCmd->AvailableForStates(G4State_PreInit);
   
  CuBoxLengthCmd = new G4UIcmdWithADoubleAndUnit("/mydet/CuBox/length",this);
  CuBoxLengthCmd->SetGuidance("cooper boc (GeDet) Length.");
  CuBoxLengthCmd->SetParameterName("Distance",false,false);
  CuBoxLengthCmd->SetDefaultUnit("mm");
  CuBoxLengthCmd->SetUnitCategory("Length");
  CuBoxLengthCmd->AvailableForStates(G4State_PreInit);

  DetBoxThicknessCmd = new G4UIcmdWithADoubleAndUnit("/mydet/DetBox/thickness",this);
  DetBoxThicknessCmd->SetGuidance("det box (GeDet) thickness.");
  DetBoxThicknessCmd->SetParameterName("Distance",false,false);
  DetBoxThicknessCmd->SetDefaultUnit("mm");
  DetBoxThicknessCmd->SetUnitCategory("Length");
  DetBoxThicknessCmd->AvailableForStates(G4State_PreInit);

  DetBoxHeightCmd = new G4UIcmdWithADoubleAndUnit("/mydet/DetBox/height",this);
  DetBoxHeightCmd->SetGuidance("det box (GeDet) Height.");
  DetBoxHeightCmd->SetParameterName("Distance",false,false);
  DetBoxHeightCmd->SetDefaultUnit("mm");
  DetBoxHeightCmd->SetUnitCategory("Length");
  DetBoxHeightCmd->AvailableForStates(G4State_PreInit);
   
  DetBoxLengthCmd = new G4UIcmdWithADoubleAndUnit("/mydet/DetBox/length",this);
  DetBoxLengthCmd->SetGuidance("det box (GeDet) Length.");
  DetBoxLengthCmd->SetParameterName("Distance",false,false);
  DetBoxLengthCmd->SetDefaultUnit("mm");
  DetBoxLengthCmd->SetUnitCategory("Length");
  DetBoxLengthCmd->AvailableForStates(G4State_PreInit);

  GeDetRadiusCmd = new G4UIcmdWithADoubleAndUnit("/mydet/GeDet/radius",this);
  GeDetRadiusCmd->SetGuidance("germanium det radius.");
  GeDetRadiusCmd->SetParameterName("Distance",false,false);
  GeDetRadiusCmd->SetDefaultUnit("mm");
  GeDetRadiusCmd->SetUnitCategory("Length");
  GeDetRadiusCmd->AvailableForStates(G4State_PreInit);

  GeDetHeightCmd = new G4UIcmdWithADoubleAndUnit("/mydet/GeDet/height",this);
  GeDetHeightCmd->SetGuidance("germanium det height.");
  GeDetHeightCmd->SetParameterName("Distance",false,false);
  GeDetHeightCmd->SetDefaultUnit("mm");
  GeDetHeightCmd->SetUnitCategory("Length");
  GeDetHeightCmd->AvailableForStates(G4State_PreInit);
    
  ScintLengthCmd = new G4UIcmdWithADoubleAndUnit("/mydet/scintillator/width",this);
  ScintLengthCmd->SetGuidance("Set full scintillator's width.");
  ScintLengthCmd->SetParameterName("Length",false,false);
  ScintLengthCmd->SetDefaultUnit("mm");
  ScintLengthCmd->SetUnitCategory("Length");
  ScintLengthCmd->AvailableForStates(G4State_PreInit);

  ScintHeightCmd = new G4UIcmdWithADoubleAndUnit("/mydet/scintillator/height",this);
  ScintHeightCmd->SetGuidance("Set full scintillator's height.");
  ScintHeightCmd->SetParameterName("Height",false,false);
  ScintHeightCmd->SetDefaultUnit("mm");
  ScintHeightCmd->SetUnitCategory("Length");
  ScintHeightCmd->AvailableForStates(G4State_PreInit);  

  ScintThicknessCmd = new G4UIcmdWithADoubleAndUnit("/mydet/scintillator/thickness",this);
  ScintThicknessCmd->SetGuidance("Set full scintillator's thickness.");
  ScintThicknessCmd->SetParameterName("Thickness",false,false);
  ScintThicknessCmd->SetDefaultUnit("mm");
  ScintThicknessCmd->SetUnitCategory("Length");
  ScintThicknessCmd->AvailableForStates(G4State_PreInit);


}
//######################################################
GeDetectorMessenger::~GeDetectorMessenger()
{
  //  G4cout << "Deleting GeDetecotrMessenger" << G4endl;
  
  delete SourceNameCmd;
  //  delete MatCmd;
  delete PbBoxHeightCmd;
  delete PbBoxLengthCmd;
  delete PbBoxThicknessCmd;

  delete PbBrickHeightCmd;
  delete PbBrickLengthCmd;
  delete PbBrickThickness1Cmd;
  delete PbBrickThickness2Cmd;

  delete CuBoxHeightCmd;
  delete CuBoxLengthCmd;
  delete CuBoxThicknessCmd;

  delete DetBoxHeightCmd;
  delete DetBoxLengthCmd;
  delete DetBoxThicknessCmd;

  delete GeDetHeightCmd;
  delete GeDetRadiusCmd;
  
  delete ScintLengthCmd;  
  //  delete ScintLength2Cmd;  
  //  delete ScintLength3Cmd;  
  delete ScintHeightCmd;  
  //  delete ScintHeight2Cmd;  
  //  delete ScintHeight3Cmd;  
  delete ScintThicknessCmd;    
  //  delete ScintThickness2Cmd;  
  //  delete ScintThickness3Cmd;

  delete scintillatorDir;
  delete mydetDir;
  delete PbBoxDir;
  delete PbBrickDir;
}
//######################################################
void GeDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValues)
{ 
  
  if (command==SourceNameCmd)
                myDetector->SetSourceName(newValues);
  //  Pb brick box
  else if (command==PbBoxThicknessCmd)
		myDetector->SetPbBoxThickness(PbBoxThicknessCmd->GetNewDoubleValue(newValues));
  else if(command==PbBoxLengthCmd)
      myDetector->SetPbBoxLength(PbBoxLengthCmd->GetNewDoubleValue(newValues));
  else if(command==PbBoxHeightCmd)
		myDetector->SetPbBoxHeight(PbBoxHeightCmd->GetNewDoubleValue(newValues));

	//  Pb bricks 
	else if(command==PbBrickThickness1Cmd)
		myDetector->SetPbBrickThickness1(PbBrickThickness1Cmd->GetNewDoubleValue(newValues));
   else if(command==PbBrickThickness2Cmd)
      myDetector->SetPbBrickThickness2(PbBrickThickness2Cmd->GetNewDoubleValue(newValues));
	else if(command==PbBrickHeightCmd)
		myDetector->SetPbBrickHeight(PbBrickHeightCmd->GetNewDoubleValue(newValues));
	else if(command==PbBrickLengthCmd)
		myDetector->SetPbBrickLength(PbBrickLengthCmd->GetNewDoubleValue(newValues));

   //  CuBox 
   else if(command==CuBoxThicknessCmd)
      myDetector->SetCuBoxThickness(CuBoxThicknessCmd->GetNewDoubleValue(newValues));
   else if(command==CuBoxHeightCmd)
      myDetector->SetCuBoxHeight(CuBoxHeightCmd->GetNewDoubleValue(newValues));
   else if(command==CuBoxLengthCmd)
      myDetector->SetCuBoxLength(CuBoxLengthCmd->GetNewDoubleValue(newValues));

   //  DetBox 
   else if(command==DetBoxThicknessCmd)
      myDetector->SetDetBoxThickness(DetBoxThicknessCmd->GetNewDoubleValue(newValues));
   else if(command==DetBoxHeightCmd)
      myDetector->SetDetBoxHeight(DetBoxHeightCmd->GetNewDoubleValue(newValues));
   else if(command==DetBoxLengthCmd)
      myDetector->SetDetBoxLength(DetBoxLengthCmd->GetNewDoubleValue(newValues));

   //  GeDet 
   else if(command==GeDetRadiusCmd)
      myDetector->SetGeDetRadius(GeDetRadiusCmd->GetNewDoubleValue(newValues));
   else if(command==GeDetHeightCmd)
      myDetector->SetGeDetHeight(GeDetHeightCmd->GetNewDoubleValue(newValues));

}

