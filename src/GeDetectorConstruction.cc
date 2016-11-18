//////////////////////////////////
///  Class: GeDetectorConstruction
///  author: Aleksandra Bialek 
///  Modified: Spencer Axani May 2012
///////////////////////////////////   
#include "GeDetectorConstruction.hh"
#include "GeDetectorMessenger.hh"
//LOGAN: I think these are for the geometry via external text file, so no need
//#include "G4tgbVolumeMgr.hh"
//#include "G4tgrMessenger.hh"
//#include "G4tgrMessenger.hh"
#include "GeSourceConstructor.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"


#include "G4LogicalVolume.hh"
#include "G4GeometryManager.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4ios.hh"
#include <vector>
#include "G4Polycone.hh"

#ifndef min
#define min(x,y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x,y) ((x) > (y) ? (x) : (y))
#endif
using namespace std;

GeDetectorConstruction::GeDetectorConstruction()
  :Epsilon(0*fermi), solidWorld(NULL), logicWorld(NULL), physiWorld(NULL), solidRoom(NULL), logicRoom(NULL), physiRoom(NULL)
{
  fCuBoxHeight=0.; fCuBoxLength=0.; fCuBoxThickness=0.;
  fPbBoxHeight=0.; fPbBoxLength=0.; fPbBoxThickness=0.;
  fGeDetHeight=0.; fGeDetRadius=0.; 
  
  detectorMessenger = new GeDetectorMessenger(this);
//LOGAN: Again, no need
  //messenger = new G4tgrMessenger;
}
//######################################################
GeDetectorConstruction::~GeDetectorConstruction()
{
  delete detectorMessenger;
//LOGAN: Again...
  //delete messenger;
}
//##############################################################
G4VPhysicalVolume* GeDetectorConstruction::Construct()
{
  #include "GeDetectorMaterials.icc"   // Material definition 


  G4double hPbBoxHeight	      = fPbBoxHeight	   * 0.5;
  G4double hPbBoxLength	      = fPbBoxLength       * 0.5;
  G4double hPbBoxThickness    = fPbBoxThickness    * 0.5;

  G4double hCuBoxHeight       = fCuBoxHeight       * 0.5;
  G4double hCuBoxThickness    = fCuBoxThickness    * 0.5;
  G4double hCuBoxLength       = fCuBoxLength       * 0.5;

  G4double hDetBoxHeight      = fDetBoxHeight      * 0.5;
  G4double hDetBoxThickness   = fDetBoxThickness   * 0.5;
  G4double hDetBoxLength      = fDetBoxLength      * 0.5; 
  
  G4double hGeDetHeight       = fGeDetHeight       * 0.5;
  G4double hGeDetRadius       = fGeDetRadius;


  

  //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
  //------------------------------ 
  // World
  //------------------------------ 
  solidWorld= new G4Box("World",900,900,900);
  logicWorld= new G4LogicalVolume(solidWorld, VacMaterial, "World");
  physiWorld= new G4PVPlacement(0,               // rotation
                                 G4ThreeVector(), // at (0,0,0)
 	                         "WorldPV",       // its name
				 logicWorld,      // its logical volume
                                 0,               // its mother  volume
                                 false,
                                 0);              // no field specific to volume

  //------------------------------ 
  // Room
  //------------------------------ 
  solidRoom = new G4Box("Room",800,800,800);
  logicRoom = new G4LogicalVolume(solidRoom,VacMaterial,"RoomLV",0,0,0);
  physiRoom = new G4PVPlacement(0,
                                G4ThreeVector(),
                                "RoomPV",
                                logicRoom,
                                physiWorld,
                                false,
                                0);

    
    //------------------------------ 
    // Front Bottom SS Tank
    //------------------------------ 
    solidFBSSO = new G4Box("FBSS outer",381,25.4,304.8);
    logicFBSSO = new G4LogicalVolume(solidFBSSO,SSMaterial,"FBSSLVO",0,0,0); 
    physiFBSSO = new G4PVPlacement(0,
				   G4ThreeVector(0,406.4,-127),
                                 "FBSSPVO",
                                 logicFBSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    //------------------------------ 
    // Front Top SS tank
    //------------------------------ 
    solidFTSSO = new G4Box("FTSS outer",381,25.4,127);
    logicFTSSO = new G4LogicalVolume(solidFTSSO,SSMaterial,"FTSSLVO",0,0,0);
    physiFTSSO = new G4PVPlacement(0,
				   G4ThreeVector(0,406.4,304.8),
                                 "FTSSPVO",
                                 logicFTSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    //------------------------------ 
    // Right Bottom SS tank
    //------------------------------ 
    solidRBSSO = new G4Box("FBSS outer",25.4,381,304.8);
    logicRBSSO = new G4LogicalVolume(solidRBSSO,SSMaterial,"RBSSLVO",0,0,0);
    physiRBSSO = new G4PVPlacement(0,
				   G4ThreeVector(406.4,0,-127),
                                 "RBSSPVO",
                                 logicRBSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    //------------------------------ 
    // Right Top SS Tank
    //------------------------------ 
    solidRTSSO = new G4Box("RTSS outer",25.4,381,127);
    logicRTSSO = new G4LogicalVolume(solidRTSSO,SSMaterial,"RTSSLVO",0,0,0);
    physiRTSSO = new G4PVPlacement(0,
				   G4ThreeVector(406.4,0,304.8),
                                 "RTSSPVO",
                                 logicRTSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    //------------------------------ 
    // Left Bottom SS tank
    //------------------------------ 
    solidLBSSO = new G4Box("LBSS outer",25.4,381,304.8);
    logicLBSSO = new G4LogicalVolume(solidLBSSO,SSMaterial,"LBSSLVO",0,0,0); 
    physiLBSSO = new G4PVPlacement(0,
                                 G4ThreeVector(-406.4,0,-127),
                                 "LBSSPVO",
                                 logicLBSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    //------------------------------ 
    // Left Top SS tank
    //------------------------------ 
    solidLTSSO = new G4Box("LTSS outer",25.4,381,127);
    logicLTSSO = new G4LogicalVolume(solidLTSSO,SSMaterial,"LTSSLVO",0,0,0);
    physiLTSSO = new G4PVPlacement(0,
                                 G4ThreeVector(-406.4,0,304.8),
                                 "LTSSPVO",
                                 logicLTSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    
    //------------------------------ 
    // Back bottom SS tank
    //------------------------------ 
    solidBBSSO = new G4Box("BBSS outer",381,25.4,304.8);
    logicBBSSO = new G4LogicalVolume(solidBBSSO,SSMaterial,"BBSSLVO",0,0,0);
    physiBBSSO = new G4PVPlacement(0,
                                 G4ThreeVector(0,-406.4,-127),
                                 "BBSSPVO",
                                 logicBBSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    //------------------------------ 
    // Back Top SS tank
    //------------------------------ 
    solidBTSSO = new G4Box("BTSS outer",381,25.4,127);
    logicBTSSO = new G4LogicalVolume(solidBTSSO,SSMaterial,"BTSSLVO",0,0,0);
    physiBTSSO = new G4PVPlacement(0,
                                 G4ThreeVector(0,-406.4,304.8),
                                 "BTSSPVO",
                                 logicBTSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    //------------------------------ 
    // Top SS tank
    //------------------------------ 
    solidTSSO = new G4Box("TSS outer",381,381,25.4);
    logicTSSO = new G4LogicalVolume(solidTSSO,SSMaterial,"TSSLVO",0,0,0);
    physiTSSO = new G4PVPlacement(0,
                                 G4ThreeVector(0,0,457.2),
                                 "TSSPVO",
                                 logicTSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    //------------------------------ 
    // Bottom SS Tank
    //------------------------------ 
    solidBSSO = new G4Box("BSS outer",381,381,25.4);
    logicBSSO = new G4LogicalVolume(solidBSSO,SSMaterial,"BSSLVO",0,0,0);
    physiBSSO = new G4PVPlacement(0,
                                 G4ThreeVector(0,0,-457.2),
                                 "BSSPVO",
                                 logicBSSO,
                                 physiRoom,
                                 false,
                                 0);
    
    ////////////////////////////////////////////////////////////////////////////
    //------------------------------ 
    // Front Bottom scintillator Tank
    //------------------------------ 
    solidFBSCO = new G4Box("FBSC outer",373.1,23.9,303.3);
    logicFBSCO = new G4LogicalVolume(solidFBSCO,ScintMaterial,"FBSCLVO",0,0,0); 
    physiFBSCO = new G4PVPlacement(0,
                                   G4ThreeVector(),
                                   "FBSCPVO",
                                   logicFBSCO,
                                   physiFBSSO,
                                   false,
                                   0);
    
    //------------------------------ 
    // Front Top scintillator tank
    //------------------------------ 
    solidFTSCO = new G4Box("FTSC outer",373.1,23.9,125.5);
    logicFTSCO = new G4LogicalVolume(solidFTSCO,ScintMaterial,"FTSCLVO",0,0,0);
    physiFTSCO = new G4PVPlacement(0,
                                   G4ThreeVector(),
                                   "FTSCPVO",
                                   logicFTSCO,
                                   physiFTSSO,
                                   false,
                                   0);
    
    //------------------------------ 
    // Right Bottom scintillator tank
    //------------------------------ 
    solidRBSCO = new G4Box("FBSC outer",23.9,373.1,303.3);
    logicRBSCO = new G4LogicalVolume(solidRBSCO,ScintMaterial,"RBSCLVO",0,0,0);
    physiRBSCO = new G4PVPlacement(0,
                                   G4ThreeVector(),
                                   "RBSCPVO",
                                   logicRBSCO,
                                   physiRBSSO,
                                   false,
                                   0);
    
    //------------------------------ 
    // Right Top scintillator Tank
    //------------------------------ 
    solidRTSCO = new G4Box("RTSC outer",23.9,373.1,125.5);
    logicRTSCO = new G4LogicalVolume(solidRTSCO,ScintMaterial,"RTSCLVO",0,0,0);
    physiRTSCO = new G4PVPlacement(0,
                                   G4ThreeVector(),
                                   "RTSCPVO",
                                   logicRTSCO,
                                   physiRTSSO,
                                   false,
                                   0);
    
    //------------------------------ 
    // Left Bottom scintillator tank
    //------------------------------ 
    solidLBSCO = new G4Box("LBSC outer",23.9,373.1,303.3);
    logicLBSCO = new G4LogicalVolume(solidLBSCO,SSMaterial,"LBSCLVO",0,0,0);
    physiLBSCO = new G4PVPlacement(0,
                                   G4ThreeVector(),
                                   "LBSCPVO",
                                   logicLBSCO,
                                   physiLBSSO,
                                   false,
                                   0);
    
    //------------------------------ 
    // Left Top scintillator tank
    //------------------------------ 
    solidLTSCO = new G4Box("LTSC outer",23.9,373.1,125.5);
    logicLTSCO = new G4LogicalVolume(solidLTSCO,ScintMaterial,"LTSCLVO",0,0,0);
    physiLTSCO = new G4PVPlacement(0,
                                   G4ThreeVector(),
                                   "LTSCPVO",
                                   logicLTSCO,
                                   physiLTSSO,
                                   false,
                                   0);
    
    //------------------------------ 
    // Back bottom scintillator tank
    //------------------------------ 
    solidBBSCO = new G4Box("BBSC outer",373.1,23.9,303.3);
    logicBBSCO = new G4LogicalVolume(solidBBSCO,ScintMaterial,"BBSCLVO",0,0,0);
    physiBBSCO = new G4PVPlacement(0,
                                   G4ThreeVector(),
                                   "BBSCPVO",
                                   logicBBSCO,
                                   physiBBSSO,
                                   false,
                                   0);
    
    //------------------------------ 
    // Back Top scintillator tank
    //------------------------------ 
    solidBTSCO = new G4Box("BTSC outer",373.1,23.9,125.5);
    logicBTSCO = new G4LogicalVolume(solidBTSCO,ScintMaterial,"BTSCLVO",0,0,0);
    physiBTSCO = new G4PVPlacement(0,
                                   G4ThreeVector(),
                                   "BTSCPVO",
                                   logicBTSCO,
                                   physiBTSSO,
                                   false,
                                   0);
    
    //------------------------------ 
    // Top scintillator tank
    //------------------------------ 
    solidTSCO = new G4Box("TSC outer",373.1,373.1,23.9);
    logicTSCO = new G4LogicalVolume(solidTSCO,ScintMaterial,"TSCLVO",0,0,0);
    physiTSCO = new G4PVPlacement(0,
                                  G4ThreeVector(),
                                  "TSCPVO",
                                  logicTSCO,
                                  physiTSSO,
                                  false,
                                  0);
    
    
    //------------------------------ 
    // Bottom scintillator Tank
    //------------------------------ 
    solidBSCO = new G4Box("BSC outer",373.1,373.1,23.9);
    logicBSCO = new G4LogicalVolume(solidBSCO,ScintMaterial,"BSCLVO",0,0,0);
    physiBSCO = new G4PVPlacement(0,
                                  G4ThreeVector(),
                                  "BSCPVO",
                                  logicBSCO,
                                  physiBSSO,
                                  false,
                                  0);
    
    //////////////////////////////////////////////////////////////////////////////////////////////
  //--------------------------------
  // Lead bricks box
  //--------------------------------
  solidPbBox  = new G4Box("PbBox",hPbBoxLength,hPbBoxHeight,hPbBoxThickness);
  logicPbBox  = new G4LogicalVolume(solidPbBox,PbBoxMaterial,"PbBoxLV",0,0,0);
  physiPbBox  = new G4PVPlacement(0,
                                  G4ThreeVector(),
                                  "PbBoxPV",
                                  logicPbBox,
                                  physiRoom,
                                  false,
                                  0);

 //--------------------------------
  //  Copper Box
  //--------------------------------
  solidCuBox = new G4Box("CuPlate",hCuBoxLength,hCuBoxThickness,hCuBoxHeight);
  logicCuBox = new G4LogicalVolume(solidCuBox,CuBoxMaterial,"CuBoxLV",0,0,0);
  physiCuBox = new G4PVPlacement(0,               
                                 G4ThreeVector(0,0,0),
                                 "CuBoxPV",     
                                 logicCuBox,  
                                 physiPbBox,
                                 false,
                                 0);   

  //--------------------------------
  // Stainless Steal Support Plate
  //--------------------------------
  G4RotationMatrix *rotD = new G4RotationMatrix;
  rotD->rotateX(M_PI/2);
  solidSSBox = new G4Box("SSplate",hPbBoxLength,hPbBoxHeight,3);
  logicSSBox = new G4LogicalVolume(solidSSBox,SSMaterial,"SSplateLV",0,0,0);
  physiSSBox = new G4PVPlacement(0,               
                                 G4ThreeVector(0,0,hCuBoxHeight+3),
                                 "SSPlatePV",     
                                 logicSSBox,  
                                 physiPbBox,
                                 false,
                                 0);   



  //--------------------------------
  // Detector box
  //--------------------------------
  G4RotationMatrix *rotC = new G4RotationMatrix;
  rotC->rotateX(M_PI/2);
  solidDetBox = new G4Box("DetBox",hDetBoxLength,hDetBoxHeight,hDetBoxThickness);
  logicDetBox = new G4LogicalVolume(solidDetBox,NitrogenMaterial,"DetBoxLV",0,0,0);
  physiDetBox = new G4PVPlacement(0,
                                  G4ThreeVector(0,0,0),
                                  "DetBox",
                                  logicDetBox,
                                  physiCuBox,
                                  false,
                                  0);
 

  //--------------------------------
  //GeDetEndcap 
  //-------------------------------- 
  solidGeDetF = new G4Tubs("GeDetF",0,(2.0*25.4),7.5*25.4/2.0+1.5,0, 2*M_PI );
  logicGeDetF = new G4LogicalVolume(solidGeDetF,GeDetFMaterial,"GeDetFLV",0,0,0);
  physiGeDetF = new G4PVPlacement(0,
                                  G4ThreeVector(0,0,-10),
                                  "GeDetF",
                                  logicGeDetF,
                                  physiDetBox,
                                  false,
                                  0); 

  //--------------------------------
  // 5MM vacuum surrounding
  //--------------------------------
  solidGeDetFVac = new G4Tubs("GeDetFVac",0,2.0*25.4-1.5,7.5*25.4/2.0,0, 2*M_PI );
  logicGeDetFVac = new G4LogicalVolume(solidGeDetFVac,VacMaterial,"GeDetFVac",0,0,0);
  physiGeDetFVac = new G4PVPlacement(0,
                                       G4ThreeVector(0,0,0), 
                                       "GeDetFVac",
                                       logicGeDetFVac,
                                       physiGeDetF,
                                       false,
                                       0);

  //--------------------------------
  //Crystal Holder
  //--------------------------------
  solidGeDetHolder = new G4Tubs("GeDetHolder",hGeDetRadius,hGeDetRadius+0.76,hGeDetHeight+12.5,0, 2*M_PI );
  logicGeDetHolder = new G4LogicalVolume(solidGeDetHolder,GeDetFMaterial,"GeDetDLVHolder",0,0,0);
  physiGeDetHolder = new G4PVPlacement(0,
                                 G4ThreeVector(0,0,32.46),
                                 "GeDetHolder",
                                 logicGeDetHolder,
                                 physiGeDetFVac,
                                 false,
                                 0);

  //--------------------------------
  //Crystal Holder base
  //--------------------------------
  solidGeDetHolderbase = new G4Tubs("GeDetHolderbase",0,hGeDetRadius+.76,3.2,0, 2*M_PI );
  logicGeDetHolderbase = new G4LogicalVolume(solidGeDetHolderbase,GeDetFMaterial,"GeDetDLVHolderbase",0,0,0);
  physiGeDetHolderbase = new G4PVPlacement(0,
					   G4ThreeVector(0,0,-26.69),
                                 "GeDetHolderbase",
                                 logicGeDetHolderbase,
                                 physiGeDetFVac,
                                 false,
                                 0);
  
  //--------------------------------
  //Crystal Holder Top Ring
  //--------------------------------
  solidGeDetTRing = new G4Tubs("GeDetTRing",hGeDetRadius+.76,hGeDetRadius+2.6,4.3,0, 2*M_PI );
  logicGeDetTRing = new G4LogicalVolume(solidGeDetTRing,GeDetFMaterial,"GeDetTRing",0,0,0);
  physiGeDetTRing = new G4PVPlacement(0,
					   G4ThreeVector(0,0,55),
                                 "GeDetTRing",
                                 logicGeDetTRing,
                                 physiGeDetFVac,
                                 false,
                                 0);

  //--------------------------------
  //Crystal Holder Bottom Ring
  //--------------------------------
  solidGeDetBRing = new G4Tubs("GeDetBRing",hGeDetRadius+.76,hGeDetRadius+2.6,4.3,0, 2*M_PI );
  logicGeDetBRing = new G4LogicalVolume(solidGeDetBRing,GeDetFMaterial,"GeDetBRing",0,0,0);
  physiGeDetBRing = new G4PVPlacement(0,
					   G4ThreeVector(0,0,20),
                                 "GeDetBRing",
                                 logicGeDetBRing,
                                 physiGeDetFVac,
                                 false,
                                 0);

  //----------------------------------
  //Crystal Holder IR Window (plastic)
  //----------------------------------
  solidGeDetIR = new G4Tubs("GeDetIR",0,hGeDetRadius+0.76,0.49,0, 2*M_PI );
  logicGeDetIR = new G4LogicalVolume(solidGeDetIR,GeDetFMaterial,"GeDetDLVIR",0,0,0);
  physiGeDetIR = new G4PVPlacement(0,
					   G4ThreeVector(0,0,89.63),
                                 "GeDetIR",
                                 logicGeDetIR,
                                 physiGeDetFVac,
                                 false,
                                 0);
  
  //--------------------------------
  //Crystal Holder base stem
  //--------------------------------
  solidGeDetHolderstem = new G4Tubs("GeDetHolderstem",0,hGeDetRadius/2,15,0, 2*M_PI );
  logicGeDetHolderstem = new G4LogicalVolume(solidGeDetHolderstem,GeDetFMaterial,"GeDetDLVHolderstem",0,0,0);
  physiGeDetHolderstem = new G4PVPlacement(0,
					   G4ThreeVector(0,0,-43.29),
                                 "GeDetHolderstem",
                                 logicGeDetHolderstem,
                                 physiGeDetFVac,
                                 false,
                                 0);

  //--------------------------------
  //GeDet depletion Layer
  //--------------------------------
  solidGeDetD = new G4Tubs("GeDetD",0.,hGeDetRadius,hGeDetHeight,0, 2*M_PI );
  logicGeDetD = new G4LogicalVolume(solidGeDetD,GeDetMaterial,"GeDetDLV",0,0,0);
  physiGeDetD = new G4PVPlacement(0,
                                 G4ThreeVector(0,0,43.7),
                                 "GeDetD",
                                 logicGeDetD,
                                 physiGeDetFVac,
                                 false,
                                 0);

  //--------------------------------
  //GeDet
  //--------------------------------

  solidGeDet = new G4Tubs("GeDet",0.,hGeDetRadius-1,hGeDetHeight-1,0, 2*M_PI );
  logicGeDet = new G4LogicalVolume(solidGeDet,GeDetMaterial,"GeDetLV",0,0,0);
  physiGeDet = new G4PVPlacement(0,
                                 G4ThreeVector(0,0,0),
                                 "GeDet",
                                 logicGeDet,
                                 physiGeDetD,
                                 false,
                                 0);

  //--------------------------------
  // Inside Electrode
  //--------------------------------
  solidGeDetElect = new G4Tubs("GeDetElectrode",0.,4.5,49.795,0, 2*M_PI );
    logicGeDetElect = new G4LogicalVolume(solidGeDetElect,GeDetFMaterial,"GeDetElectLV",0,0,0);
    physiGeDetElect = new G4PVPlacement(0,
					G4ThreeVector(0,0,-20.345),
                                      "GeDetElectPV",
                                      logicGeDetElect,
                                      physiGeDet,
                                      false,
                                      0);   
				      
  // Call the external source volume constructor
  GeSourceConstructor* source = GeSourceConstructor::getInstance();
  source->ConstructSource(fSourceName);

				     

					   
  // An attempt to put in geometry through an external text file... not sure
  // how to get it to work, exactly.
  /*Include an external geometry for the sample
  G4String filename = "sample.txt";
  G4tgbVolumeMgr* volmgr = G4tgbVolumeMgr::GetInstance();
  volmgr->AddTextFile(filename);

  G4LogicalVolume* logicSample = G4tgbVolumeMgr::GetInstance()->FindG4LogVol("sample",0);
  if(logicSample){
    physiGeDetSample = new G4PVPlacement(0,
                                         G4ThreeVector(0,0,0), //
                                         "GeDetSample",
                                         logicSample,
                                         physiGeDet, //? What is mother?
                                         false,
                                         0);
  }
  else{
    G4Exception("GeDetectorConstruction::Construct()","InvalidGeometry",JustWarning, "No sample geometry specified: run default geometry");
  }
*/

  //--------- Visualization attributes -------------------------------
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  logicRoom->SetVisAttributes (G4VisAttributes::Invisible);

  G4VisAttributes * greenAndWire  = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.5));
  G4VisAttributes * greenAndSolid = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.5));
  G4VisAttributes * cyanAndWire   = new G4VisAttributes(G4Colour(0.0,1.0,1.0,0.5));
  G4VisAttributes * cyan2AndWire  = new G4VisAttributes(G4Colour(0.0,0.5,1.0,0.5));
  G4VisAttributes * cyanAndSolid  = new G4VisAttributes(G4Colour(0.0,1.0,1.0,0.5));
  G4VisAttributes * redAndSolid   = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));
  G4VisAttributes * blueAndSolid  = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));
  G4VisAttributes * blueAndWire   = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));
  G4VisAttributes * whiteAndWire  = new G4VisAttributes(G4Colour(1.0,1.0,1.0,0.5));
  G4VisAttributes * yellowAndSolid= new G4VisAttributes(G4Colour(1.0,1.0,0.0,0.5));  
  G4VisAttributes * yellowAndWire = new G4VisAttributes(G4Colour(1.0,1.0,0.0,0.5));
  G4VisAttributes * orangeAndWire = new G4VisAttributes(G4Colour(1.0,0.75,0.0,0.5));
  G4VisAttributes * redAndWire    = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));
  G4VisAttributes * grayAndWire   = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.5));
  G4VisAttributes * Invisible = new G4VisAttributes(G4Colour(0,0,0,0));

 G4VisAttributes * grayAndSolid  = new G4VisAttributes(G4Colour(0.1,0.5,0.8,0.75));

  redAndSolid   ->SetVisibility(true);    blueAndSolid->SetVisibility(true);  
  yellowAndSolid->SetVisibility(true);    greenAndWire->SetVisibility(true);
  greenAndSolid ->SetVisibility(true);    cyanAndWire ->SetVisibility(true);
  orangeAndWire ->SetVisibility(true);    redAndWire  ->SetVisibility(true);  
  grayAndWire   ->SetVisibility(true);    grayAndSolid->SetVisibility(true);
  whiteAndWire  ->SetVisibility(true);    
       
  greenAndSolid ->SetForceSolid(true);     redAndSolid ->SetForceSolid(true);        
  blueAndSolid  ->SetForceSolid(true);     cyanAndSolid->SetForceSolid(true);   
  yellowAndSolid->SetForceSolid(true);     grayAndSolid->SetForceSolid(false);
       
  yellowAndWire->SetForceWireframe(true);  greenAndWire->SetForceWireframe(true);   
  cyanAndWire  ->SetForceWireframe(true);  cyan2AndWire->SetForceWireframe(true);    
  grayAndWire  ->SetForceWireframe(true);  redAndWire  ->SetForceWireframe(true); 
  whiteAndWire ->SetForceWireframe(true);  blueAndWire ->SetForceWireframe(true);
  
  logicWorld           ->SetVisAttributes(Invisible);
  logicRoom            ->SetVisAttributes(Invisible);
  logicPbBox           ->SetVisAttributes(grayAndWire); 
  logicDetBox          ->SetVisAttributes(yellowAndWire);
  logicCuBox           ->SetVisAttributes(yellowAndWire);
  logicGeDetF          ->SetVisAttributes(whiteAndWire);
  logicGeDetD          ->SetVisAttributes(greenAndSolid);
  logicGeDet           ->SetVisAttributes(blueAndSolid);
  logicGeDetFVac       ->SetVisAttributes(yellowAndWire);
  logicGeDetElect      ->SetVisAttributes(whiteAndWire);
  logicGeDetHolder     ->SetVisAttributes(redAndWire);
  logicGeDetHolderbase ->SetVisAttributes(redAndWire);
  logicGeDetHolderstem ->SetVisAttributes(redAndWire);
  logicGeDetTRing      ->SetVisAttributes(redAndWire);
  logicGeDetBRing      ->SetVisAttributes(redAndWire);
    logicFBSCO           ->SetVisAttributes(blueAndWire);
    logicFTSCO           ->SetVisAttributes(blueAndWire);
    logicRBSCO           ->SetVisAttributes(blueAndWire);
    logicRTSCO           ->SetVisAttributes(blueAndWire);
    logicLBSCO           ->SetVisAttributes(blueAndWire);
    logicLTSCO           ->SetVisAttributes(blueAndWire);
    logicBBSCO           ->SetVisAttributes(blueAndWire);
    logicBTSCO           ->SetVisAttributes(blueAndWire);
    logicBSCO           ->SetVisAttributes(blueAndWire);
    logicTSCO           ->SetVisAttributes(blueAndWire);
  logicSSBox           ->SetVisAttributes(cyanAndWire);

  return physiWorld;
}

