
#include "GeRunAction.hh"

#include <fstream>
#include "G4RunManager.hh"
#include "GeAnalysis.hh"

// Includes for writing to text file
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
#include <stdlib.h>

#include <math.h>

GeAnalysis* GeAnalysis::instance = 0;

GeAnalysis* GeAnalysis::getInstance()
{
  if (instance == 0) instance = new GeAnalysis();
  return instance;
}

GeAnalysis::GeAnalysis()
{

  // Set the energy histogram parameters
  numberOfBins = 5000;
  minimumBinEnergy = 0.5;
  maximumBinEnergy = 5000.5;

  GnumberOfBins = 5000;
  GminimumBinEnergy = 0.5;
  GmaximumBinEnergy = 5000.5;

  // Point to nothing
  energyGe = NULL;
  energyGammaRay = NULL;

  // Allocate the memory for n number of points
  energyGe = new int[numberOfBins];
  energyGammaRay = new int[GnumberOfBins];
  
  int i(0);
  for (i=0;i<numberOfBins;i++) {
    energyGe[i] = 0;
  }
  for (i=0;i<GnumberOfBins;i++) {
    energyGammaRay[i] = 0;
  }

}


GeAnalysis::~GeAnalysis() {
  // Delete the dynamic arrays
  delete [] energyGe;
  delete [] energyGammaRay;
  energyGe = NULL;
  energyGammaRay = NULL;
}

// To convet energy received to bin number:

// Calculate the interval
// interval = (maximumBinEnergy-minimumBinEnergy)/numberOfBins;

// Take the modulus of the energy with the interval and subtract it from the energy recieved
// energy -= energy%interval

// Divide by the interval to get bin number
// bin = energy/interval

// Increment the bin number by one

// Functions that fill the respective histograms
void GeAnalysis::InsertEnergyGe(double en)
{
  double interval = (maximumBinEnergy-minimumBinEnergy)/numberOfBins;

  en -= fmod(en,interval);
  G4int bin = en/interval;

  energyGe[bin]++;
}

void GeAnalysis::InsertEnergyGammaRay(double en)
{
  double Ginterval = (GmaximumBinEnergy-GminimumBinEnergy)/GnumberOfBins;

  en -= fmod(en,Ginterval);
  G4int bin = en/Ginterval;

  energyGammaRay[bin]++;
}

int GeAnalysis::GetBinEntriesGe(int bin) {
  return energyGe[bin];
}

int GeAnalysis::GetBinEntriesGammaRay(int bin) {
  return energyGammaRay[bin];
}

void GeAnalysis::BeginOfRun() 
{ 

  int i(0);
  for (i=0;i<numberOfBins;i++) {
    energyGe[i] = 0;
  }
  for (i=0;i<GnumberOfBins;i++) {
    energyGammaRay[i] = 0;
  }

}


void GeAnalysis::EndOfRun()
{

  // Get the file name parameters to determine where to print data
  GeRunAction* run = (GeRunAction*)
  G4RunManager::GetRunManager()->GetUserRunAction();  
  outFileName = run->GetFileName();
  sourceFileFlag = run->GetSourceFileFlag();
  
    // Forced into the new output directory
  outFileName = "output/" + outFileName;
  
  outFileName += ".txt";
  
  // Store the file name and source file generator flags to the necessary variables
  outFileName;
  sourceFileFlag;

  if (sourceFileFlag == "true") {
    // Generate the reference file for a point source geometry
  
    int i(0);
    int maximumCounts = 0;
  
    double interval = (maximumBinEnergy-minimumBinEnergy)/numberOfBins;  
    double energy = 0.;
  
    for (i=0;i<numberOfBins;i++) {
//    G4cout<<"\n"<<GetBinEntriesGe(i);
      if (GetBinEntriesGe(i) > maximumCounts) {
        maximumCounts = GetBinEntriesGe(i); 
      } 
    }
  
    // Set the threshold for the efficicency calculations
    double thresholdPercentage = 0.2;
    int threshold = 0;
    threshold = maximumCounts * (thresholdPercentage/100);  
  
    // Loop again through the array
    for (i=0;i<numberOfBins;i++) {
      if (GetBinEntriesGe(i) >= threshold && GetBinEntriesGammaRay(i) != 0) {
  
        energy = i*interval+interval/2.+minimumBinEnergy;
        // Perform the calculation using this count value
        G4cout<<"\n\nCounts at "<<energy<<" (keV): "<<GetBinEntriesGe(i)<<"\t"<<"Produced:\t"<<GetBinEntriesGammaRay(i)<<"\n"<<G4endl;
	
	// Print this data to the source reference text file
        ofstream fout;	
	fout.open(outFileName, ios::app);
        if(!fout.fail()) {

          fout<<energy<<" "<<GetBinEntriesGammaRay(i)<<" "<<GetBinEntriesGe(i)<<endl;

          fout.close();

        }
  
     }
    }

  }
  else {
  
  // Code to run to print text file for regular sources
  double effArray[100][3];
  
    const int MAX_CHARS_PER_LINE = 512;
    const int MAX_TOKENS_PER_LINE = 20;
    const char* const DELIMITER = " ";
    int line = 0;

    // create a file-reading object
    ifstream fin;
    fin.open("output/PointSource_Reference.txt"); // open a file
    if (!fin.fail()) {
  
      // read each line of the file
      while (!fin.eof())
      {
        // read an entire line into memory
        char buf[MAX_CHARS_PER_LINE];
        fin.getline(buf, MAX_CHARS_PER_LINE);
    
        // parse the line into blank-delimited tokens
        int n = 0; // a for-loop index
     
        // array to store memory addresses of the tokens in buf
        const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
        // parse the line
        token[0] = strtok(buf, DELIMITER); // first token
        if (token[0]) // zero if line is blank
        {
          for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
          {
            token[n] = strtok(0, DELIMITER); // subsequent tokens
            if (!token[n]) break; // no more tokens
          }
        }

        // process (print) the tokens
	// skip the first line of headers
	if (line != 0) {
          for (int i = 0; i < n; i++) {// n = #of tokens
            
	    effArray[line-1][i] = atof(token[i]);	    
//	    cout << "Token[" << i << "] = " << effArray[line-1][i] << endl;
	      
	  }
         // cout << endl;
	
	}
	
	line++;
      } // End loop over lines

      fin.close();
    } // End file input open
    
    // Now have a 3 col array (energy, produced, counts) that can be used to determine efficiencies
    
    int i(0);
    int maximumCounts = 0;
  
    double interval = (maximumBinEnergy-minimumBinEnergy)/numberOfBins;  
    double energy = 0.;
  
    for (i=0;i<numberOfBins;i++) {
//    G4cout<<"\n"<<GetBinEntriesGe(i);
      if (GetBinEntriesGe(i) > maximumCounts) {
        maximumCounts = GetBinEntriesGe(i); 
      } 
    }
  
    // Set the threshold for the efficicency calculations
    double thresholdPercentage = 0.2;
    int threshold = 0;
    threshold = maximumCounts * (thresholdPercentage/100);  
  
    // Loop again through the array
    for (i=0;i<numberOfBins;i++) {
      if (GetBinEntriesGe(i) >= threshold && GetBinEntriesGammaRay(i) != 0) {
  
        energy = i*interval+interval/2.+minimumBinEnergy;
        // Perform the calculation using this count value
        G4cout<<"\n\nSample counts at "<<energy<<" (keV): "<<GetBinEntriesGe(i)<<"\t"<<"Produced: "<<GetBinEntriesGammaRay(i)<<G4endl;
	
	// Search the point source array to look for an energy match
	// If a match exists, calculate the relative efficiency and display it
	// Goes to (line-2) since an extra empty line is being put into the array, potentially buggy if file is modifed
	int j(0);
	for (j=0;j<line-2;j++) {
	
	  // Check for an energy match
	  if (energy == effArray[j][0]) {
	    // Calculate the effiency and display the data
	    cout<<"Point source ref "<<effArray[j][0]<<" (keV): "<<effArray[j][2]<<"\t"<<"Produced: "<<effArray[j][1]<<"\n"<<endl;
	    
	    // Calculate the relative efficiency, takes into account the simulation event numbers
	    double relEff = (double(GetBinEntriesGe(i))/double(GetBinEntriesGammaRay(i)))/(effArray[j][2]/effArray[j][1]);
	    
	    cout<<"Relative Efficiency at "<<effArray[j][0]<<" (keV): "<<relEff<<"\n"<<endl;
	    
	    // Print this data to the relative efficiency curve text file
	    ofstream fout;	
	    fout.open(outFileName, ios::app);
            if(!fout.fail()) {

              fout<<effArray[j][0]<<" "<<relEff<<endl;

              fout.close();

            }
	    else {
	      G4cout<<"Error opening file!"<<G4endl;
	    }// Close file
	  
	  
	  } // End energy match
	  
	} // End loop over point source reference
	


     } // End exceed threshold of depostion statement
    } // End loop over deposition histogram
    
    
  } // End of general case code 
  // Testing
//  G4cout<<outFileName<<G4endl;
//  G4cout<<sourceFileFlag<<G4endl;
  
}


void GeAnalysis::EndOfEvent() 
{
}

