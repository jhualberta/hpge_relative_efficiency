#ifndef GeAnalysis_h 
#define GeAnalysis_h 1

#include "globals.hh"
#include <vector>
#include "G4ThreeVector.hh"


class GeAnalysis {
public:
  virtual ~GeAnalysis();
  
public:

  void BeginOfRun();
  void EndOfRun();
  void EndOfEvent();

  void InsertEnergyGe(double en);
  void InsertEnergyGammaRay(double en);

  int GetBinEntriesGe(int bin);
  int GetBinEntriesGammaRay(int bin);

  static GeAnalysis* getInstance();

private:

  GeAnalysis();

private:
  static GeAnalysis* instance;

  int* energyGe;
  int* energyGammaRay;

  int numberOfBins;
  double minimumBinEnergy;
  double maximumBinEnergy;

  int GnumberOfBins;
  double GminimumBinEnergy;
  double GmaximumBinEnergy;
  
  G4String outFileName;
  G4String sourceFileFlag;

};


#endif
