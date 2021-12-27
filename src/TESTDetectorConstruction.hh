#ifndef TESTDETECTORCONSTRUCTION_HH
#define TESTDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class TESTDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    TESTDetectorConstruction();
    virtual ~TESTDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif
