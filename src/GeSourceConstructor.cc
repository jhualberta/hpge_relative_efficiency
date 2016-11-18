
#include "GeSourceConstructor.hh"
#include "GeDetectorConstruction.hh"

#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Color.hh"
#include "G4Torus.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Polycone.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"

GeSourceConstructor* GeSourceConstructor::instance = 0;

GeSourceConstructor* GeSourceConstructor::getInstance()
{
  if (instance == 0) instance = new GeSourceConstructor();
  return instance;
}

GeSourceConstructor::GeSourceConstructor()
{
// Inititalize values as needed
}

GeSourceConstructor::~GeSourceConstructor() {
// Delete values as needed
}

void GeSourceConstructor::ConstructSource(G4String sourceName) 
{

  #include "GeDetectorMaterials.icc"   // Material definition 
  
  //Get a pointer to the mother volume for the source "physiDetBox"
  GeDetectorConstruction* det = (GeDetectorConstruction*)
  G4RunManager::GetRunManager()->GetUserDetectorConstruction();
    
  G4VPhysicalVolume* physiDetBox = det->GetDetBox();
  
  // Get the pointer to the User Interface manager (used to pass along source commands)
  G4UImanager* UI = G4UImanager::GetUIpointer();  
   
  G4NistManager* man = G4NistManager::Instance();
  
  // ---------------------------------------
  // Shared visuzlization attributes
  // ---------------------------------------
  
  G4VisAttributes * grayAndSolid  = new G4VisAttributes(G4Colour(0.1,0.5,0.8,0.75));
  G4VisAttributes * redAndSolid   = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));
  G4VisAttributes * blueAndSolid  = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));
  G4VisAttributes * yellowAndSolid= new G4VisAttributes(G4Colour(1.0,1.0,0.0,0.5));  

  grayAndSolid->SetVisibility(true);    
  redAndSolid->SetVisibility(true);    
  blueAndSolid->SetVisibility(true);  
  yellowAndSolid->SetVisibility(true);
 
  grayAndSolid->SetForceSolid(true);  
  redAndSolid->SetForceSolid(true);        
  blueAndSolid->SetForceSolid(true);
  yellowAndSolid->SetForceSolid(true);  
 
  // ---------------------------------------
  // End of shared attributes
  // ---------------------------------------
  
  
  // Vector which points to the centre of the top of the Ge detector end cap
  // Can be used to position the sample geometry more easily.
  G4ThreeVector sourceVectorOffset = G4ThreeVector(0., 0., (7.5*25.4/2.)+1.5);
  
  if (sourceName == "C_Clamp") {  // **************************
   
    //----------------------------------------------------------------
    // C-Clamp geometry definition
    //----------------------------------------------------------------
  
    //C-Clamp variables
    G4double fClampWidth = 25.4*mm;
    G4double fClampHeight = 25.4*mm;
    G4double fClampLength = 50.8*mm;
    G4double fClampHoleRadius = 3.*mm;
    G4double fClampHoleOffset = 12.7*mm;
    G4double fClampGapLength = 38.1*mm;
    G4double fClampGapHeight = 8.89*mm;
    G4double fClampGapOffset = 6.35*mm;
    // Long axis of clamp is set along the X
  
    //Create the subraction solid from 2 box elements
    G4Box* solidClampBulk = new G4Box("solidClampBulk", fClampLength/2., fClampWidth/2., fClampHeight/2.);
    //Cut volume set larger than required to not have overlapping cut edges and create
    //errors in future visualization, solid still accurate
    G4Box* solidClampCut = new G4Box("solidClampCut", fClampGapLength, fClampWidth, fClampGapHeight/2.);

    //Create the intermediate bulk solid
    G4VSolid* solidClampInter = new G4SubtractionSolid("solidClampInter", solidClampBulk, solidClampCut, 0, G4ThreeVector(fClampLength/2., 0., -fClampHeight/2. + fClampGapOffset + fClampGapHeight/2.));
  
    //Cut volume for screw hole again set a bit larger than needed (1mm) to prevent errors
    G4Tubs* solidClampScrewHole = new G4Tubs("solidClampScrewHole", 0, fClampHoleRadius, (fClampHeight-fClampGapOffset-fClampGapHeight+1.*mm)/2.,0,twopi);
  
    G4VSolid* solidCClamp = new G4SubtractionSolid("solidCClamp", solidClampInter, solidClampScrewHole, 0, G4ThreeVector(fClampLength/2. - fClampHoleOffset,0,fClampHeight/2. - (fClampHeight-fClampGapOffset-fClampGapHeight+1.*mm)/2.));
    
    G4LogicalVolume* logicCClamp = new G4LogicalVolume(solidCClamp, ClampMaterial, "logicCClamp", 0,0,0);
  
    // Taken from Logan's sample holder, modified to postion clamp right on top of detector
    G4double sampleOffset = (7.5*25.4/2.)+1.5 -10+fClampHeight/2.;
    
    G4VPhysicalVolume* physiCClamp = new G4PVPlacement(0, G4ThreeVector(0,0,sampleOffset), "physiCClamp", logicCClamp, physiDetBox, false, 0);
  
    // End C-Clamp geometry definition
  
    //----------------------------------------------------------------
    // C-Clamp visualization attributes
    //----------------------------------------------------------------
  
    logicCClamp->SetVisAttributes(grayAndSolid);

    // End C-Clamp vis attributes
    
    //----------------------------------------------------------------
    // C-Clamp source distribution
    //----------------------------------------------------------------
   
    // Volume type
    UI->ApplyCommand("/gps/pos/type Volume");
    UI->ApplyCommand("/gps/pos/shape Para");
  
    // Halfx of clamp
    std::ostringstream osstringx;
    osstringx << (fClampLength/2.)/mm;
    G4String halfx = osstringx.str();
    UI->ApplyCommand("/gps/pos/halfx "+halfx+" mm");   
   
    // Halfy of clamp
    std::ostringstream osstringy;
    osstringy << (fClampWidth/2.)/mm;
    G4String halfy = osstringy.str();
    UI->ApplyCommand("/gps/pos/halfy "+halfy+" mm");   
   
    // Halfz of clamp
    std::ostringstream osstringz;
    osstringz << (fClampHeight/2.)/mm;
    G4String halfz = osstringz.str();
    UI->ApplyCommand("/gps/pos/halfz "+halfz+" mm");
    
    // Centre of source
    std::ostringstream osstringzpos;
    osstringzpos << sampleOffset/mm;
    G4String zpos = osstringzpos.str();
    UI->ApplyCommand("/gps/pos/centre 0. 0. "+zpos+" mm");
   
    // Confine the source to the volume defined
    UI->ApplyCommand("/gps/pos/confine physiCClamp");
   
  } // End C-Clamp statements ****************************
  else if (sourceName == "Co60_Vial") { // **************************
  
    //--------------------------------
    // Vial geometry defintion (composed of multiple solids)
    //--------------------------------
  
    // Volume to hold sample - smallest dimensions possible, offset equal to its
    // half-length in Z plus the half-length of the most external GEDet part
    G4double sampleR = 10.85*mm;
    G4double sampleZ = 59.85*mm;
    //The Al endcap has a half-Z of 7.5*25.4/2.+1.5 ... not sure why, but it's 
    //  hard-coded, above
    G4double sampleOffset = (7.5*25.4/2.)+1.5 -10+sampleZ/2.;
    G4Tubs* solidSample = new G4Tubs("Sample",0.,sampleR,sampleZ/2.,0.,2.*M_PI);
    //NitrogenMaterial should really be Air, which is WorldMaterial... 2 instances
    G4LogicalVolume* logicSample = new G4LogicalVolume(solidSample,NitrogenMaterial,"SampleLV",0,0,0);
    G4VPhysicalVolume* physiSample = new G4PVPlacement(0, G4ThreeVector(0.,0.,sampleOffset), "SamplePV", logicSample, physiDetBox, false, 0);

    // Outer plastic container 
    G4double wallThickness = 1.05*mm;
    G4double outerRI = 6.60*mm;
    G4double outerRO = outerRI+wallThickness;
    G4double outerZ = 48.75*mm;
    G4double outerOffset = -1.*(sampleZ-outerZ)/2.;
    G4Tubs* solidSampleOuterContainer = new G4Tubs("SampleOuterContainer",outerRI,outerRO,outerZ/2.,0.,2.*M_PI);
    G4LogicalVolume* logicSampleOuterContainer = new G4LogicalVolume(solidSampleOuterContainer,Polypropylene,"SampleOuterContainerLV",0,0,0);
    G4VPhysicalVolume* physiSampleOuterContainer = new G4PVPlacement(0, G4ThreeVector(0.,0.,outerOffset), "SampleOuterContainerPV", logicSampleOuterContainer, physiSample, false, 0);

    // Lid on top of container - solid plastic by assumption
    G4double lidR = sampleR;
    G4double lidZ = sampleZ-outerZ;
    G4double lidOffset = (sampleZ-lidZ)/2.;
    G4Tubs* solidSampleLid = new G4Tubs("SampleLid",0.,lidR,lidZ/2.,0.,2.*M_PI);
    G4LogicalVolume* logicSampleLid = new G4LogicalVolume(solidSampleLid,Polypropylene,"SampleLidLV",0,0,0);
    G4VPhysicalVolume* physiSampleLid = new G4PVPlacement(0, G4ThreeVector(0.,0.,lidOffset), "SampleLidPV", logicSampleLid, physiSample, false, 0);

    // Container has an internal conical bottom, with a gap between it and outer
    // plastic tube
    G4double innerConeZ = 7.32*mm;
    G4double innerInset = 1.40*mm;
    G4double innerOffset = -1.*(sampleZ/2. - innerInset);
    const G4int numZPlanes = 3;
    G4double zz[numZPlanes] = {0.,innerConeZ,outerZ-innerInset};//-wallThickness};
    G4double rInner[numZPlanes] = {0.,0.,0.};
    G4double rOuter[numZPlanes] = {0.,outerRI,outerRI};
    G4Polycone* solidSampleInnerContainer = new G4Polycone("SampleInnerContainer",0.,2.*M_PI,numZPlanes,zz,rInner,rOuter);
    G4LogicalVolume* logicSampleInnerContainer = new G4LogicalVolume(solidSampleInnerContainer,Polypropylene,"SampleInnerContainerLV",0,0,0);
    G4VPhysicalVolume* physiSampleInnerContainer = new G4PVPlacement(0, G4ThreeVector(0.,0.,innerOffset), "SampleInnerContainerPV", logicSampleInnerContainer, /*physiSampleOuterContainter, */ physiSample, false, 0);

    // Fill the plastic cone with air, inset by the wall thickness
    zz[2] = outerZ-innerInset-wallThickness;
    G4Polycone* solidSampleInnerAir = new G4Polycone("SampleInnerAir",0.,2*M_PI,numZPlanes,zz,rInner,rOuter);
    G4LogicalVolume* logicSampleInnerAir = new G4LogicalVolume(solidSampleInnerAir,Air,"SampleInnerAirLV",0,0,0);
    G4VPhysicalVolume* physiSampleInnerAir = new G4PVPlacement(0, G4ThreeVector(0.,0.,wallThickness), "SampleInnerAirPV", logicSampleInnerAir, physiSampleInnerContainer, false, 0);

    // Set the liquid into the air gap we just created. The liquid is 1mL
    G4double sourceVolume = 5000.*mm3;
    G4double sourceZ = (sourceVolume/pow(outerRI,2)/M_PI)+2.*innerConeZ/3.;
    G4double sourceOffset = -1.*(outerZ-innerInset-wallThickness-sourceZ)/2.;
    zz[2] = sourceZ;
    G4Polycone* solidSampleInnerSource = new G4Polycone("SampleInnerSource",0.,2.*M_PI,numZPlanes,zz,rInner,rOuter);
    G4LogicalVolume* logicSampleInnerSource = new G4LogicalVolume(solidSampleInnerSource,LCo60,"SampleInnerSourceLV",0,0,0);
    G4VPhysicalVolume* physiSampleInnerSource = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), "SampleInnerSourcePV", logicSampleInnerSource, physiSampleInnerAir, false, 0);

    // End vial geometry definition
    
    //--------------------------------
    // Vial vizualization attributes
    //--------------------------------
        
    logicSampleOuterContainer->SetVisAttributes(redAndSolid);
    logicSampleInnerContainer->SetVisAttributes(redAndSolid);
    logicSampleLid->SetVisAttributes(redAndSolid);
    logicSampleInnerSource->SetVisAttributes(yellowAndSolid);
    logicSampleInnerAir->SetVisAttributes(blueAndSolid);
    
    // End vial vis attributes
    
    //----------------------------------------------------------------
    // Vial source distribution
    //----------------------------------------------------------------
    
    // Volume type
    UI->ApplyCommand("/gps/pos/type Volume");
    UI->ApplyCommand("/gps/pos/shape Cylinder");
  
    // Radius of clamp
    std::ostringstream osstringr;
    osstringr << outerRI/mm;
    G4String rad = osstringr.str();
    UI->ApplyCommand("/gps/pos/radius "+rad+" mm");   
   
    // Halfz of clamp
    std::ostringstream osstringz;
    osstringz << (outerZ-innerInset)/mm;
    G4String halfz = osstringz.str();
    UI->ApplyCommand("/gps/pos/halfz "+halfz+" mm");   
    
    // Centre of source
    std::ostringstream osstringzpos;
    osstringzpos << (96.7*mm + innerOffset + wallThickness + outerZ-innerInset)/mm;
    G4String zpos = osstringzpos.str();
    UI->ApplyCommand("/gps/pos/centre 0. 0. "+zpos+" mm");
   
    // Confine the source to the volume defined
    UI->ApplyCommand("/gps/pos/confine SampleInnerSourcePV");
    
  
  }  // End vial statements **************************  
  else if (sourceName == "Piezo3") {
  
    // Custom material defined for piezo speakers
    // Performed since acutal material and geometry isn't well known
    // Only serves to get an estimate of the relative efficiency
    G4int ncomponents;
    G4double density;
    G4Material* PiezoMatter = new G4Material("PiezoMatter", density= 3.04*g/cm3, ncomponents=2);
    PiezoMatter->AddElement(elAl, fractionmass=0.5);
    PiezoMatter->AddElement(elC, fractionmass=0.5);
    
    // Simpliefied as the addition of 3 small rectangular boxes as a source geometry
    // placed in a small pyramid (top is rotated 90 degrees to others)
    //                      **************** 
    //                  ***********  ***********
    // On top of the detector
    
    // Piezo speaker variables
    G4double piezoLength = 30.*mm;
    G4double piezoWidth = 20.*mm;
    G4double piezoHeight = 1.4*mm;
    
    G4RotationMatrix piezoRot;
    piezoRot.rotateZ(pi/2.);
    
    G4Transform3D placement1 = G4Transform3D(piezoRot, G4ThreeVector(-piezoWidth/2., 0., -piezoHeight));
    G4Transform3D placement2 = G4Transform3D(piezoRot, G4ThreeVector(piezoWidth/2., 0., -piezoHeight));
    
    //--------------------------------
    // Piezo speaker geoemtry (centered relative to the top speaker)
    //--------------------------------
    
    G4Box* solidSpeaker = new G4Box("solidSpeaker", piezoLength/2., piezoWidth/2., piezoHeight/2.);
    G4VSolid* solid2Speakers = new G4UnionSolid("solid2Speakers", solidSpeaker, solidSpeaker, placement1);
    G4VSolid* solidPiezo = new G4UnionSolid("solidPiezo", solid2Speakers, solidSpeaker, placement2);
    
    G4LogicalVolume* logicPiezo = new G4LogicalVolume(solidPiezo,PiezoMatter,"logicPiezo",0,0,0);
    
    G4double sampleOffset = (7.5*25.4/2.)+1.5 -10+piezoHeight*3./2.;
    
    G4VPhysicalVolume* physiPiezo = new G4PVPlacement(0, G4ThreeVector(0.,0.,sampleOffset), "physiPiezo", logicPiezo, physiDetBox, false, 0);
  
    //--------------------------------
    // Piezo speaker vizualization attributes
    //--------------------------------
        
    logicPiezo->SetVisAttributes(grayAndSolid);
    
    //----------------------------------------------------------------
    // Peizo speaker source distribution
    //----------------------------------------------------------------
   
    // Declared as a box that confines all of the volumes
    
    // Volume type
    UI->ApplyCommand("/gps/pos/type Volume");
    UI->ApplyCommand("/gps/pos/shape Para");
  
    // Halfx of clamp
    std::ostringstream osstringx;
    osstringx << (piezoWidth)/mm;
    G4String halfx = osstringx.str();
    UI->ApplyCommand("/gps/pos/halfx "+halfx+" mm");   
   
    // Halfy of clamp
    std::ostringstream osstringy;
    osstringy << (piezoLength/2.)/mm;
    G4String halfy = osstringy.str();
    UI->ApplyCommand("/gps/pos/halfy "+halfy+" mm");
   
    // Halfz of clamp
    std::ostringstream osstringz;
    osstringz << (piezoHeight)/mm;
    G4String halfz = osstringz.str();
    UI->ApplyCommand("/gps/pos/halfz "+halfz+" mm");
    
    // Centre of source
    std::ostringstream osstringzpos;
    osstringzpos << (sampleOffset - piezoHeight/2.)/mm;
    G4String zpos = osstringzpos.str();
    UI->ApplyCommand("/gps/pos/centre 0. 0. "+zpos+" mm");
   
    // Confine the source to the volume defined
    UI->ApplyCommand("/gps/pos/confine physiPiezo");
    
  }
  else if (sourceName == "Al_Neutron") {
    
    // Dimensions
    G4double alHalfz = 15.6*mm;
    G4double alRadius = 100.*mm;
  
    G4double pillHalfz = 3.*mm;
    G4double pillRadius =1.5*mm;
    G4double pillInnerHalfz = 1.5*mm;
    G4double pillInnerRadius = 0.75*mm; 

    //--------------------------------
    // Al + neutron source geometry
    //--------------------------------    
      
    // Volumes
    G4Tubs* solidAl = new G4Tubs("solidAl", 0., alRadius, alHalfz, 0, twopi);
    G4LogicalVolume* logicAl = new G4LogicalVolume(solidAl, AlDiskMaterial, "logicAl",0,0,0);
  
    G4double sampleOffset = (7.5*25.4/2.)+1.5 -10+alHalfz;
  
    G4VPhysicalVolume* physiAl = new G4PVPlacement(0, G4ThreeVector(0.,0.,sampleOffset), "physiAl", logicAl, physiDetBox, false, 0);

    // Pill that houses the neutron source
    G4Tubs* solidOuterPill = new G4Tubs("solidOuterPill", 0., pillRadius, pillHalfz, 0, twopi);
    G4Tubs* solidInnerPill = new G4Tubs("solidInnerPill", 0., pillInnerRadius, pillInnerHalfz, 0, twopi); 
    
    G4VSolid* solidPillShell = new G4SubtractionSolid("solidPillShell", solidOuterPill, solidInnerPill, 0,G4ThreeVector(0));
    
    G4LogicalVolume* logicPillShell = new G4LogicalVolume(solidPillShell, PillMaterial, "logicPillShell",0,0,0);   
    G4VPhysicalVolume* physiPillShell = new G4PVPlacement(0, G4ThreeVector(0.,0.,sampleOffset + alHalfz + pillHalfz), "physiPillShell", logicPillShell, physiDetBox, false, 0);

    G4LogicalVolume* logicAmBe = new G4LogicalVolume(solidInnerPill, AmBeMaterial, "logicAmBe",0,0,0);   
    G4VPhysicalVolume* physiAmBe = new G4PVPlacement(0, G4ThreeVector(0.,0.,sampleOffset + alHalfz + pillHalfz), "physiAmBe", logicAmBe, physiDetBox, false, 0);    
        
    //--------------------------------
    // Al + neutron source vizualization attributes
    //--------------------------------
         
    logicAl->SetVisAttributes(grayAndSolid);
    logicPillShell->SetVisAttributes(blueAndSolid);
    logicAmBe->SetVisAttributes(grayAndSolid);
    
    //----------------------------------------------------------------
    // Al + neutron source distribution
    //----------------------------------------------------------------
            
    // Volume type
    UI->ApplyCommand("/gps/pos/type Volume");
    UI->ApplyCommand("/gps/pos/shape Cylinder");
  
    // Radius of source
    std::ostringstream osstringr;
    osstringr << pillInnerRadius/mm;
    G4String rad = osstringr.str();
    UI->ApplyCommand("/gps/pos/radius "+rad+" mm");   
   
    // Halfz of source
    std::ostringstream osstringz;
    osstringz << (pillInnerHalfz)/mm;
    G4String halfz = osstringz.str();
    UI->ApplyCommand("/gps/pos/halfz "+halfz+" mm");   
    
    // Centre of source
    std::ostringstream osstringzpos;
    osstringzpos << (sampleOffset + alHalfz + pillHalfz)/mm;
    G4String zpos = osstringzpos.str();
    UI->ApplyCommand("/gps/pos/centre 0. 0. "+zpos+" mm");
   
    // Confine the source to the volume defined
    UI->ApplyCommand("/gps/pos/confine physiAmBe");
    
  }
  else if (sourceName == "Nalgene") {


    // Values I don't know... Things are positioned relative to the z-coordinate of
    // the top of the endcap and are placed in the logical volume motherLog, both
    // of which need to be filled in here.
    double zCentreOfEndcap = (7.5*25.4/2.)+1.5;
 //   double motherLog = logicalVolumeOfMother;

    // Set some values for the geometry, as measured by Steve (with some minor
    // adjustments)
    double containerThickness = 1.63 * mm;
    double containerBodyInnerRadius = 21.68 * mm;
    double containerHeight = 42.56 * mm;
    double containerInset = 1.84 * mm;
    double lidOuterRadius = 28.615 * mm;
    double lidHeight = 15.5 * mm;
    double lidThickness = 2.51 * mm;

    double waterVolume = 15000. * mm3; // About 15 mL
    double waterDepth = waterVolume/pi/pow(containerBodyInnerRadius,2);

    // Grab the materials from the materials database
    G4NistManager* man = G4NistManager::Instance();
    G4Material* containerMaterial = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
    G4Material* waterMaterial = man->FindOrBuildMaterial("G4_WATER");

    // A null rotation matrix for later use
    G4RotationMatrix *noRotation = new G4RotationMatrix();

    // Make the container out of the union of walls and lid
    G4VSolid* containerBody = new G4Tubs("containerBody",containerBodyInnerRadius,
                                    containerBodyInnerRadius+containerThickness,
                                    containerHeight/2.0,0.0,twopi);
    G4VSolid* containerBase = new G4Tubs("containerBase",0.0,
                                    containerBodyInnerRadius,
                                    containerThickness/2.0,0.0,twopi);
    G4VSolid* containerLid = new G4Tubs("containerLid",0.0,lidOuterRadius,
                                    lidThickness/2.0,0.0,twopi);
    G4VSolid* containerThread = new G4Tubs("containerThread",
                                    containerBodyInnerRadius+containerThickness,
                                    lidOuterRadius,lidHeight/2.0,0.0,twopi);

    // Here is the union
    G4VSolid *container = new G4UnionSolid("container",containerBody,containerBase,
                                    noRotation,G4ThreeVector(0.0,0.0,
                                    containerInset+(containerThickness-
                                    containerHeight)/2.0));
    container = new G4UnionSolid("container",container,containerLid,noRotation,
                                    G4ThreeVector(0.0,0.0,(containerHeight+
                                    lidThickness)/2.0));
    container = new G4UnionSolid("container",container,containerThread,noRotation,
                                    G4ThreeVector(0.0,0.0,lidThickness+
                                    (containerHeight-lidHeight)/2.0));

    G4LogicalVolume* containerLog = new G4LogicalVolume(container,containerMaterial,
                                    "containerLog");
    G4ThreeVector containerPos(0.0,0.0,zCentreOfEndcap+containerHeight/2.0);
    G4Transform3D containerTransform(*noRotation,containerPos);

    // Actually place the physical volume for the container
    new G4PVPlacement(0, containerPos,"containerPhys",containerLog,physiDetBox,false,0);

    // Make the water volume
    G4VSolid *water = new G4Tubs("water",0.0,containerBodyInnerRadius,
                                    waterDepth/2.0,0.0,twopi);
    G4LogicalVolume *waterLog = new G4LogicalVolume(water,waterMaterial,"waterLog");
    G4ThreeVector waterPos(0.0,0.0,zCentreOfEndcap+containerInset+containerThickness                                   +waterDepth/2.0);
    G4Transform3D waterTransform(*noRotation,waterPos);
    new G4PVPlacement(0, waterPos,"waterPhys", waterLog ,physiDetBox,false,0); 
    
    //--------------------------------
    // Nalgene vizualization attributes
    //--------------------------------
         
    containerLog->SetVisAttributes(grayAndSolid);
    waterLog->SetVisAttributes(blueAndSolid);

    //----------------------------------------------------------------
    // Nalgene source distribution
    //----------------------------------------------------------------
            
    // Volume type
    UI->ApplyCommand("/gps/pos/type Volume");
    UI->ApplyCommand("/gps/pos/shape Cylinder");
  
    // Radius of source
    std::ostringstream osstringr;
    osstringr << containerBodyInnerRadius/mm;
    G4String rad = osstringr.str();
    UI->ApplyCommand("/gps/pos/radius "+rad+" mm");   
   
    // Halfz of source
    std::ostringstream osstringz;
    osstringz << (waterDepth/2.)/mm;
    G4String halfz = osstringz.str();
    UI->ApplyCommand("/gps/pos/halfz "+halfz+" mm");   
    
    // Centre of source
    std::ostringstream osstringzpos;
    osstringzpos << (waterPos.z())/mm;
    G4String zpos = osstringzpos.str();
    UI->ApplyCommand("/gps/pos/centre 0. 0. "+zpos+" mm");
   
    // Confine the source to the volume defined
    UI->ApplyCommand("/gps/pos/confine waterPhys");    
    
  }
  else if (sourceName == "Deap_Fibre") {
   
    G4NistManager* man = G4NistManager::Instance();    

    // Define materials not in NIST
    G4double density;
    G4int ncomponents;
    G4double fractionmass;    

    // Fibre total mass = 17.76g made of approximately acrylic
    density = (17.76/24.3123)*g/cm3;
    
    G4cout<<"Density g/cm3: "<<density/(g/cm3)<<G4endl;
    
    G4double fibreOD = 79.4*mm;
    G4double fibreID = 55.2*mm;
    G4double fibreXSDiam = (fibreOD - fibreID)/2.;
    
    G4double sweptR = fibreID/2. + (fibreOD - fibreID)/4.;

    G4double sampleOffset = (7.5*25.4/2.)+1.5 -10;    
    
    G4Element* O = man->FindOrBuildElement("O");
    G4Element* H = man->FindOrBuildElement("H");
    G4Element* C = man->FindOrBuildElement("C");
    
    G4Material* FibreMatter = new G4Material("FibreMatter", density, ncomponents=3);
    FibreMatter->AddElement(H, fractionmass=0.080538);
    FibreMatter->AddElement(C, fractionmass=0.599848);
    FibreMatter->AddElement(O, fractionmass=0.319614); 
    
    G4VSolid* solidFibre = new G4Torus("solidTorus", 0., fibreXSDiam/2., sweptR, 0, twopi);

    // Calculate the effective density
  //  G4cout<<"Cubic cm volume: "<<solidFibre->GetCubicVolume()/cm3<<G4endl;  
    // Yields 24.3123 cm3
    
    G4LogicalVolume* logicFibre = new G4LogicalVolume(solidFibre, FibreMatter, "logicFibre",0,0,0);   
    G4VPhysicalVolume* physiFibre = new G4PVPlacement(0, G4ThreeVector(0.,0.,sampleOffset + fibreXSDiam/2.), "physiFibre", logicFibre, physiDetBox, false, 0);    
      
    logicFibre->SetVisAttributes(grayAndSolid);
    
    // Volume type
    UI->ApplyCommand("/gps/pos/type Volume");
    UI->ApplyCommand("/gps/pos/shape Cylinder");
  
    // Radius of source
    std::ostringstream osstringr;
    osstringr << (fibreOD/2.)/mm;
    G4String rad = osstringr.str();
    UI->ApplyCommand("/gps/pos/radius "+rad+" mm");   
   
    // Halfz of source
    std::ostringstream osstringz;
    osstringz << (fibreXSDiam/2.)/mm;
    G4String halfz = osstringz.str();
    UI->ApplyCommand("/gps/pos/halfz "+halfz+" mm");   
    
    // Centre of source
    std::ostringstream osstringzpos;
    osstringzpos << (sampleOffset + fibreXSDiam/2.)/mm;
    G4String zpos = osstringzpos.str();
    UI->ApplyCommand("/gps/pos/centre 0. 0. "+zpos+" mm");
   
    // Confine the source to the volume defined
    UI->ApplyCommand("/gps/pos/confine physiFibre");        
    
    
  }
  else if (sourceName == "PICO_Flange") {
    
    G4Material* Quartz = man->FindOrBuildMaterial("G4_GLASS_PLATE");
    G4Colour FlangeColour(250./255.,250./255.,185./255.,0.5);

    G4double fcentreToEndCap = (7.5*25.4/2.)+1.5;
 
    // A null rotation matrix for later use
    G4RotationMatrix *noRotation = new G4RotationMatrix();    
    
    G4double flangeInnerRadius = 45.0*mm;
    G4double flangeOuterRadius = 62.05*mm;
    G4double flangeThickness = 30.2*mm;
    G4double flangeTopInnerRadius = 45.15*mm;
    G4double flangeTopOuterRadius = 47.95*mm;
    G4double flangeTopThickness = 7.9*mm;
    G4VisAttributes* FlangeVisAtt = new G4VisAttributes(FlangeColour);

    G4Tubs *solidFlangeBottom = new G4Tubs("solidFlangeBottom",flangeInnerRadius,
                                     flangeOuterRadius,flangeThickness/2.,
                                     0.,twopi);
    G4Tubs *solidFlangeTop = new G4Tubs("solidFlangeTop",flangeTopInnerRadius,
                                     flangeTopOuterRadius,flangeTopThickness/2.,
                                     0.,twopi);
    
    G4VSolid *solidFlange = new G4UnionSolid("solidFlange",solidFlangeBottom,solidFlangeTop,
                                    noRotation,G4ThreeVector(0.0,0.0,flangeThickness/2.+flangeTopThickness/2.));
    G4LogicalVolume *logicFlange = new G4LogicalVolume(solidFlange,Quartz,
                                     "logicFlange");
    G4ThreeVector posFlange = G4ThreeVector(0.,0.,
                                     fcentreToEndCap+flangeThickness/2.);
    new G4PVPlacement(0,posFlange,"physiFlange",logicFlange,physiDetBox,false,0);
    logicFlange->SetVisAttributes(FlangeVisAtt);


  //  G4LogicalVolume *logicFlangeTop = new G4LogicalVolume(solidFlangeTop,Quartz,
                               //      "logicFlangeTop");
   // G4ThreeVector posFlangeTop = posFlange+G4ThreeVector(0.,0.,
                               //      (flangeThickness+flangeTopThickness)/2.);
   // new G4PVPlacement(0,posFlangeTop,"physiFlangeTop", logicFlangeTop,physiDetBox,
                               //      false,0);
   // logicFlangeTop->SetVisAttributes(FlangeVisAtt);
    
        // Volume type
    UI->ApplyCommand("/gps/pos/type Volume");
    UI->ApplyCommand("/gps/pos/shape Cylinder");
  
    // Radius of source
    std::ostringstream osstringr;
    osstringr << (flangeOuterRadius)/mm;
    G4String rad = osstringr.str();
    UI->ApplyCommand("/gps/pos/radius "+rad+" mm");   
   
    // Halfz of source
    std::ostringstream osstringz;
    osstringz << (flangeThickness/2. + flangeTopThickness/2.)/mm;
    G4String halfz = osstringz.str();
    UI->ApplyCommand("/gps/pos/halfz "+halfz+" mm");   
    
    // Centre of source
    std::ostringstream osstringzpos;
    osstringzpos << (fcentreToEndCap + flangeThickness/2. + flangeTopThickness/2.)/mm;
    G4String zpos = osstringzpos.str();
    UI->ApplyCommand("/gps/pos/centre 0. 0. "+zpos+" mm");
   
    // Confine the source to the volume defined
    UI->ApplyCommand("/gps/pos/confine physiFlange");   
  
  }
  else if (sourceName == "Marinelli") {

    G4Material* ContainerMatter = man->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Material* SampleMatter = man->FindOrBuildMaterial("G4_WATER");
    
    G4double sampleOffset = (7.5*25.4/2.)+1.5 -10;     
    // Gas Marinelli
  double fConTopHoleRadius = 105./2.*mm; 
  double fConBottomHoleRadius = 105./2.*mm; 
  double fConTotalBottomRadius = 190./2.*mm; 
 
  double fConTopThickness = 2.5*mm;
  
  // Modified as the the picture of dissected beaker, kink appears to be equivalent to the thickness
  // Therefore this is the bottom radius + the thickness
  double fConTotalTopRadius = fConTotalBottomRadius + 1.5*mm;

  double fConHoleDepth = 100.*mm; 
  double fConThickness = 2.5*mm; 

  // fConHeight/2. - fConHoleDepth/2. - fConThickness/2. needs to be 101.*mm/2.
  // Therefore Height = HoleDepth + Thickness + 101.mm
  
  double fConHeight = fConHoleDepth + fConThickness + 75.*mm;
  
  //--------------------------------------------------------
  //  Container
  //--------------------------------------------------------

  G4ThreeVector positionContainer = G4ThreeVector(0.,0.,sampleOffset + fConThickness/2.);

  G4Tubs* solidConHoleTop = new G4Tubs("solidConHoleTop", 0., fConTopHoleRadius + fConThickness, fConTopThickness/2., 0, twopi);

  G4LogicalVolume *logicConHoleTop = new G4LogicalVolume(solidConHoleTop, ContainerMatter,"logicConHoleTop");
  G4VPhysicalVolume* physiConHoleTop = new G4PVPlacement(0,positionContainer + G4ThreeVector(0.,0.,fConTopThickness/2. - fConThickness/2.), "physiConHoleTop",logicConHoleTop,physiDetBox,false,0);

  G4Cons* solidConHoleWall = new G4Cons("solidConHoleWall", fConBottomHoleRadius, fConBottomHoleRadius + fConThickness, fConTopHoleRadius, fConTopHoleRadius + fConThickness, fConHoleDepth/2. - fConThickness/2., 0, twopi);

  G4LogicalVolume *logicConHoleWall = new G4LogicalVolume(solidConHoleWall, ContainerMatter,"logicConHoleWall");
  G4VPhysicalVolume* physiConHoleWall = new G4PVPlacement(0,positionContainer + G4ThreeVector(0.,0., - fConHoleDepth/2.), "physiConHoleWall",logicConHoleWall,physiDetBox,false,0);

  G4Tubs* solidConBottom = new G4Tubs("solidConBottom", fConBottomHoleRadius, fConTotalBottomRadius, fConThickness/2., 0, twopi);

  G4LogicalVolume *logicConBottom = new G4LogicalVolume(solidConBottom, ContainerMatter,"logicConBottom");
  G4VPhysicalVolume* physiConBottom = new G4PVPlacement(0,positionContainer + G4ThreeVector(0.,0., - fConHoleDepth), "physiConBottom",logicConBottom,physiDetBox,false,0);

  G4Tubs* solidConBottomWall = new G4Tubs("solidConBottomWall", fConTotalBottomRadius - fConThickness, fConTotalBottomRadius, fConHoleDepth/2. - fConThickness/2., 0, twopi);

  G4LogicalVolume *logicConBottomWall = new G4LogicalVolume(solidConBottomWall, ContainerMatter,"logicConBottomWall");
  G4VPhysicalVolume* physiConBottomWall = new G4PVPlacement(0,positionContainer + G4ThreeVector(0.,0., - fConHoleDepth/2.), "physiConBottomWall",logicConBottomWall,physiDetBox,false,0);

  G4Tubs* solidConTopWall = new G4Tubs("solidConTopWall", fConTotalTopRadius - fConThickness, fConTotalTopRadius, fConHeight/2. - fConHoleDepth/2., 0, twopi);

  G4LogicalVolume *logicConTopWall = new G4LogicalVolume(solidConTopWall, ContainerMatter,"logicConTopWall");
  G4VPhysicalVolume* physiConTopWall = new G4PVPlacement(0,positionContainer + G4ThreeVector(0.,0., - fConThickness/2. + fConHeight/2. - fConHoleDepth/2.), "physiConTopWall",logicConTopWall,physiDetBox,false,0);

  G4Tubs* solidConWallConnector = new G4Tubs("solidConWallConnector", fConTotalBottomRadius - fConThickness, fConTotalTopRadius - fConThickness, fConThickness/2., 0, twopi);

  G4LogicalVolume *logicConWallConnector = new G4LogicalVolume(solidConWallConnector, ContainerMatter,"logicConWallConnector");
  G4VPhysicalVolume* physiConWallConnector = new G4PVPlacement(0,positionContainer, "physiConWallConnector",logicConWallConnector,physiDetBox,false,0);

  //--------------------------------------------------------
  //  Sample (Air within the container)
  //--------------------------------------------------------

  G4double downFromTop = 1.*cm; // From top lip to water level
  
  G4Tubs* solidSampleRing = new G4Tubs("solidSampleRing", fConTopHoleRadius + fConThickness, fConTotalBottomRadius - fConThickness, fConThickness/2., 0, twopi); 
  G4Cons* solidSampleCone = new G4Cons("solidSampleCone", fConBottomHoleRadius + fConThickness, fConTotalBottomRadius - fConThickness, fConTopHoleRadius + fConThickness, fConTotalBottomRadius - fConThickness, fConHoleDepth/2. - fConThickness/2., 0, twopi);
  G4Tubs* solidSampleCyl = new G4Tubs("solidSampleCyl", 0., fConTotalTopRadius - fConThickness, fConHeight/2. - fConHoleDepth/2. - fConThickness/2. - downFromTop/2., 0, twopi);

  G4VSolid* solidSampleHalf = new G4UnionSolid("solidSampleHalf", solidSampleRing, solidSampleCone, 0, G4ThreeVector(0.,0., - fConHoleDepth/2.));
  G4VSolid* solidSample = new G4UnionSolid("solidSample", solidSampleHalf, solidSampleCyl, 0, G4ThreeVector(0.,0., fConHeight/2. - fConHoleDepth/2. - downFromTop/2.));

  G4LogicalVolume *logicSample = new G4LogicalVolume(solidSample, SampleMatter,"logicSample");
  G4VPhysicalVolume* physiSample = new G4PVPlacement(0,positionContainer, "physiSample",logicSample,physiDetBox,false,0);

  G4cout<<"\n\n>>>>>>>>>>>>>>>>> Volume of sample: "<<solidSample->GetCubicVolume()/cm3<<" cm^3\n\n"<<G4endl;
  
  logicConHoleTop->SetVisAttributes(grayAndSolid);
  logicConHoleWall->SetVisAttributes(grayAndSolid);
  logicConBottom->SetVisAttributes(grayAndSolid);
  logicConBottomWall->SetVisAttributes(grayAndSolid);
  logicConWallConnector->SetVisAttributes(grayAndSolid);
  logicConTopWall->SetVisAttributes(grayAndSolid);
  logicSample->SetVisAttributes(blueAndSolid);

    // Volume type
  UI->ApplyCommand("/gps/pos/type Volume");
  UI->ApplyCommand("/gps/pos/shape Cylinder");
  
    std::ostringstream osstring1;
//  osstring1 << positionContainer.z()/mm;
  osstring1 << (positionContainer.z() + G4ThreeVector(0.,0., - fConThickness/2. + fConHeight/2. - fConHoleDepth/2.).z())/mm;
  G4String zpos = osstring1.str();
  UI->ApplyCommand("/gps/pos/centre 0. 0. "+zpos+" mm");

  // Radius of source
  std::ostringstream osstring2;
  osstring2 << fConTotalTopRadius/mm;
  G4String radius = osstring2.str();
  UI->ApplyCommand("/gps/pos/radius "+radius+" mm");
//  UI->ApplyCommand("/gps/pos/radius 38.2 mm");

  // Halfz of source
  std::ostringstream osstring3;
  osstring3 << (fConHeight/2.)/mm;
  G4String halfz = osstring3.str();
  UI->ApplyCommand("/gps/pos/halfz "+halfz+" mm");
//  UI->ApplyCommand("/gps/pos/halfz 50. mm");

  // Confine the source to the volume defined
  UI->ApplyCommand("/gps/pos/confine physiSample");
  
  }
  else { // **************************
  // Default geoemtry is a point source centered at the top of the detector
  // Volume type
  UI->ApplyCommand("/gps/pos/type Point");
  
  // Centre of source (offset 2 mm for Logan's request, change back after)
  UI->ApplyCommand("/gps/pos/centre 2. 0. 96.7 mm"); 
   
  } // End default statements
  
}
