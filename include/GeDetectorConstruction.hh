///////////////////////////////////
///  Class: GeDetectorConstruction
///  Author: Aleksandra Bialek 
///  Modified: Spencer Axani Summer 2012
///            Lee Pavelich Summer 2013
///////////////////////////////////
#ifndef GeDetectorConstruction_H
#define GeDetectorConstruction_H 1

class G4VPhysicalVolume;
class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4Material;
class GeDetectorMessenger;
class G4Polycone;

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class GeDetectorConstruction : public G4VUserDetectorConstruction
{
  private:
   const G4double Epsilon;

  public:
   GeDetectorConstruction();
   ~GeDetectorConstruction();

  public:
   G4VPhysicalVolume* Construct();
   G4double GetWorldFullLength()         {return  fWorldLength;};
   G4VPhysicalVolume*GetScintillator()   {return physiScintillator;};
   G4VPhysicalVolume*GetPbBox()          {return  physiPbBox;};
   G4VPhysicalVolume*GetCuBox()          {return  physiCuBox;};
   G4VPhysicalVolume*GetDetBox()         {return  physiDetBox;};
   G4VPhysicalVolume*GetGeDetF()         {return  physiGeDetF;};
   G4VPhysicalVolume*GetGeDetFtop()      {return  physiGeDetFtop;};
   G4VPhysicalVolume*GetGeDetFVac()      {return  physiGeDetFVac;};
   G4VPhysicalVolume*GetGeDetElect()     {return  physiGeDetElect;};
   G4VPhysicalVolume*GetGeDet()          {return  physiGeDet;};
   G4VPhysicalVolume*GetGeDetD()         {return  physiGeDetD;};
   G4VPhysicalVolume*GetGeDetSSplate()   {return  physiSSBox;};
   G4VPhysicalVolume*GetGeDetHolder()    {return  physiGeDetHolder;};
   G4VPhysicalVolume*GetGeDetTRing()     {return  physiGeDetTRing;};
   G4VPhysicalVolume*GetGeDetBRing()     {return  physiGeDetBRing;};
   G4VPhysicalVolume*GetGeDetHolderbase(){return  physiGeDetHolderbase;};
   G4VPhysicalVolume*GetGeDetHolderstem(){return  physiGeDetHolderstem;};
   G4VPhysicalVolume*GetGeDetFBSSO()        {return  physiFBSSO;};
   G4VPhysicalVolume*GetGeDetFTSSO()        {return  physiFTSSO;};
   G4VPhysicalVolume*GetGeDetRBSSO()        {return  physiRBSSO;};
   G4VPhysicalVolume*GetGeDetRTSSO()        {return  physiRTSSO;};
   G4VPhysicalVolume*GetGeDetLBSSO()        {return  physiLBSSO;};
   G4VPhysicalVolume*GetGeDetLTSSO()        {return  physiLTSSO;};
   G4VPhysicalVolume*GetGeDetBBSSO()        {return  physiBBSSO;};
   G4VPhysicalVolume*GetGeDetBTSSO()        {return  physiBTSSO;};
   G4VPhysicalVolume*GetGeDetBSSO()         {return  physiBSSO;};
   G4VPhysicalVolume*GetGeDetTSSO()         {return  physiTSSO;};
   G4VPhysicalVolume*GetGeDetFBSCO()        {return  physiFBSCO;};
   G4VPhysicalVolume*GetGeDetFTSCO()        {return  physiFTSCO;};
   G4VPhysicalVolume*GetGeDetRBSCO()        {return  physiRBSCO;};
   G4VPhysicalVolume*GetGeDetRTSCO()        {return  physiRTSCO;};
   G4VPhysicalVolume*GetGeDetLBSCO()        {return  physiLBSCO;};
   G4VPhysicalVolume*GetGeDetLTSCO()        {return  physiLTSCO;};
   G4VPhysicalVolume*GetGeDetBBSCO()        {return  physiBBSCO;};
   G4VPhysicalVolume*GetGeDetBTSCO()        {return  physiBTSCO;};
   G4VPhysicalVolume*GetGeDetBSCO()         {return  physiBSCO;};
   G4VPhysicalVolume*GetGeDetTSCO()         {return  physiTSCO;};
	
   //source
   G4VPhysicalVolume*CoSrc()		     {return  physiCoSrc;};
   
   //C-Clamp
 //  G4VPhysicalVolume*GetCClamp()	    {return physiCClamp;}

   void SetSourceName(G4String name) {fSourceName=name;}
   
   void SetPbBoxThickness(G4double thick)  {fPbBoxThickness=thick;}
   void SetPbBoxHeight(G4double height)    {fPbBoxHeight=height;}
   void SetPbBoxLength(G4double length)    {fPbBoxLength=length;}

   void SetPbBrickThickness1(G4double thick){fPbBrickThickness1=thick;}
   void SetPbBrickThickness2(G4double thick){fPbBrickThickness2=thick;}
   void SetPbBrickHeight(G4double height)   {fPbBrickHeight=height;}
   void SetPbBrickLength(G4double length)   {fPbBrickLength=length;}
   
   void SetCuBoxThickness(G4double thick) {fCuBoxThickness=thick;}
   void SetCuBoxHeight(G4double height)   {fCuBoxHeight=height;}
   void SetCuBoxLength(G4double length)   {fCuBoxLength=length;} 

   void SetDetBoxThickness(G4double thick) {fDetBoxThickness=thick;}
   void SetDetBoxHeight(G4double height)   {fDetBoxHeight=height;}
   void SetDetBoxLength(G4double length)   {fDetBoxLength=length;} 

   void SetGeDetHeight(G4double height)   {fGeDetHeight=height;}
   void SetGeDetRadius(G4double radius)   {fGeDetRadius=radius;} 
    
  private:

   G4Box*             solidWorld;    //pointer to the solid enveloppe 
   G4LogicalVolume*   logicWorld;    //pointer to the logical enveloppe
   G4VPhysicalVolume* physiWorld;    //pointer to the physical enveloppe
   G4double fullSizeWorld;           //full size of the enveloppe
   G4double fWorldLength;            // Full length of the world volume

   G4Box*             solidRoom;  
   G4LogicalVolume*   logicRoom;  
   G4VPhysicalVolume* physiRoom;  

   G4Box*             solidAir;  
   G4LogicalVolume*   logicAir;  
   G4VPhysicalVolume* physiAir;  

   G4Box*             solidFBSSO;  
   G4LogicalVolume*   logicFBSSO;  
   G4VPhysicalVolume* physiFBSSO; 

   G4Box*             solidFTSSO;  
   G4LogicalVolume*   logicFTSSO;  
   G4VPhysicalVolume* physiFTSSO; 

   G4Box*             solidRBSSO;  
   G4LogicalVolume*   logicRBSSO;  
   G4VPhysicalVolume* physiRBSSO; 

   G4Box*             solidRTSSO;  
   G4LogicalVolume*   logicRTSSO;  
   G4VPhysicalVolume* physiRTSSO; 

   G4Box*             solidLBSSO;  
   G4LogicalVolume*   logicLBSSO;  
   G4VPhysicalVolume* physiLBSSO; 

   G4Box*             solidLTSSO;  
   G4LogicalVolume*   logicLTSSO;  
   G4VPhysicalVolume* physiLTSSO; 

   G4Box*             solidBBSSO;  
   G4LogicalVolume*   logicBBSSO;  
   G4VPhysicalVolume* physiBBSSO; 


   G4Box*             solidBTSSO;  
   G4LogicalVolume*   logicBTSSO;  
   G4VPhysicalVolume* physiBTSSO; 

   G4Box*             solidBSSO;  
   G4LogicalVolume*   logicBSSO;  
   G4VPhysicalVolume* physiBSSO; 

   G4Box*             solidSSBox;  
   G4LogicalVolume*   logicSSBox;  
   G4VPhysicalVolume* physiSSBox; 

   G4Box*             solidTSSO;  
   G4LogicalVolume*   logicTSSO;  
   G4VPhysicalVolume* physiTSSO; 

   G4Box*             solidFBSCO;  
   G4LogicalVolume*   logicFBSCO;  
   G4VPhysicalVolume* physiFBSCO; 

   G4Box*             solidFTSCO;  
   G4LogicalVolume*   logicFTSCO;  
   G4VPhysicalVolume* physiFTSCO; 

   G4Box*             solidRBSCO;  
   G4LogicalVolume*   logicRBSCO;  
   G4VPhysicalVolume* physiRBSCO;
 
   G4Box*             solidRTSCO;  
   G4LogicalVolume*   logicRTSCO;  
   G4VPhysicalVolume* physiRTSCO; 

   G4Box*             solidLBSCO;  
   G4LogicalVolume*   logicLBSCO;  
   G4VPhysicalVolume* physiLBSCO; 

   G4Box*             solidLTSCO;  
   G4LogicalVolume*   logicLTSCO;  
   G4VPhysicalVolume* physiLTSCO; 

   G4Box*             solidBBSCO;  
   G4LogicalVolume*   logicBBSCO;  
   G4VPhysicalVolume* physiBBSCO; 

   G4Box*             solidBTSCO;  
   G4LogicalVolume*   logicBTSCO;  
   G4VPhysicalVolume* physiBTSCO; 

   G4Box*             solidTSCO;  
   G4LogicalVolume*   logicTSCO;  
   G4VPhysicalVolume* physiTSCO; 

   G4Box*             solidBSCO;  
   G4LogicalVolume*   logicBSCO;  
   G4VPhysicalVolume* physiBSCO;

   G4Box*             solidScintillator;  
   G4LogicalVolume*   logicScintillator;  
   G4VPhysicalVolume* physiScintillator; 

   G4Box*             solidPbBox;
   G4LogicalVolume*   logicPbBox;
   G4VPhysicalVolume* physiPbBox;

   G4Box*             solidPbBrick1;
   G4LogicalVolume*   logicPbBrick1;
   G4VPhysicalVolume* physiPbBrick1;
   G4Box*             solidPbBrick2;
   G4LogicalVolume*   logicPbBrick2;
   G4VPhysicalVolume* physiPbBrick2;

   G4Box*             solidCuBox;
   G4LogicalVolume*   logicCuBox;
   G4VPhysicalVolume* physiCuBox;

   G4Box*             solidDetBox;
   G4LogicalVolume*   logicDetBox;
   G4VPhysicalVolume* physiDetBox;

   G4Tubs*            solidGeDetF;
   G4LogicalVolume*   logicGeDetF;
   G4VPhysicalVolume* physiGeDetF;

   G4Tubs*            solidGeDetHolder;
   G4LogicalVolume*   logicGeDetHolder;
   G4VPhysicalVolume* physiGeDetHolder;


   G4Tubs*            solidGeDetHolderbase;
   G4LogicalVolume*   logicGeDetHolderbase;
   G4VPhysicalVolume* physiGeDetHolderbase;

   G4Tubs*            solidGeDetHolderstem;
   G4LogicalVolume*   logicGeDetHolderstem;
   G4VPhysicalVolume* physiGeDetHolderstem;

   G4Tubs*            solidGeDetTRing;
   G4LogicalVolume*   logicGeDetTRing;
   G4VPhysicalVolume* physiGeDetTRing;

   G4Tubs*            solidGeDetBRing;
   G4LogicalVolume*   logicGeDetBRing;
   G4VPhysicalVolume* physiGeDetBRing;

   G4Tubs*            solidGeDetIR;
   G4LogicalVolume*   logicGeDetIR;
   G4VPhysicalVolume* physiGeDetIR;

   G4Tubs*            solidGeDetD;
   G4LogicalVolume*   logicGeDetD;
   G4VPhysicalVolume* physiGeDetD;

   G4Tubs*            solidGeDetFVac;
   G4LogicalVolume*   logicGeDetFVac;
   G4VPhysicalVolume* physiGeDetFVac;
 
   G4Tubs*            solidGeDetElect;
   G4LogicalVolume*   logicGeDetElect;
   G4VPhysicalVolume* physiGeDetElect;

   G4Tubs*            solidGeDetFtop;
   G4LogicalVolume*   logicGeDetFtop;
   G4VPhysicalVolume* physiGeDetFtop;

   G4Tubs*            solidGeDet;
   G4LogicalVolume*   logicGeDet;
   G4VPhysicalVolume* physiGeDet;

   G4Material*        CoSrcMaterial;//Source Co60 material
   G4Tubs*            solidCoSrc;
   G4LogicalVolume*   logicCoSrc;
   G4VPhysicalVolume* physiCoSrc;
   
   // C-Clamp
   G4LogicalVolume*   logicCClamp;
   G4VPhysicalVolume* physiCClamp;

   GeDetectorMessenger* detectorMessenger; 
   
   G4String fSourceName;
  
   G4double  fPbBoxThickness,   fPbBoxLength,      fPbBoxHeight;
   G4double  fPbBrickThickness1,fPbBrickThickness2,fPbBrickLength,fPbBrickHeight;
   G4double  fCuBoxThickness,   fCuBoxLength,      fCuBoxHeight;
   G4double  fDetBoxThickness,  fDetBoxLength,     fDetBoxHeight;
   G4double  fGeDetHeight,      fGeDetRadius;

   //C-Clamp
 //  G4double fClampWidth, fClampHeight, fClampLength;
 //  G4double fClampHoleRadius, fClampHoleOffset;
 //  G4double fClampGapLength, fClampGapHeight;
 //  G4double fClampGapOffset;
   
  G4Tubs* sampleBowtechLight_p1;
  G4LogicalVolume* logicSampleBowtechLight_p1;
  G4VPhysicalVolume* physiSampleBowtechLigh_p1;

  G4Tubs* sampleBowtechLight_p2;
  G4LogicalVolume* logicSampleBowtechLight_p2;
  G4VPhysicalVolume* physiSampleBowtechLigh_p2;

  
   
};

#endif

