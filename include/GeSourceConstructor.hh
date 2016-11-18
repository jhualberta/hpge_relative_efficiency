#ifndef GeSourceConstructor_h 
#define GeSourceConstructor_h 1

#include "globals.hh"

class GeSourceConstructor {
public:
  virtual ~GeSourceConstructor();
  
public:

  void ConstructSource(G4String sourceName);

  static GeSourceConstructor* getInstance();
  
private:

  GeSourceConstructor();
  
private:
  static GeSourceConstructor* instance;
  
  };

#endif
