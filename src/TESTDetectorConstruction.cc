#include "TESTDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

TESTDetectorConstruction::TESTDetectorConstruction()
: G4VUserDetectorConstruction()
{
}

TESTDetectorConstruction::~TESTDetectorConstruction()
{
}

G4VPhysicalVolume* TESTDetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();


  // -----------------------------------------------------
  // World

  G4Material* world_mat = nist -> FindOrBuildMaterial("G4_AIR");
  G4double world_size = 10*m;

  G4Box* solidWorld =    
    new G4Box("World",                       // its name
              0.5*world_size,                // half x
              0.5*world_size,                // half y
              0.5*world_size);               // half z
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      true);                 //overlaps checking

  // -----------------------------------------------------
  // Detector

  G4Material* detector_mat = nist -> FindOrBuildMaterial("G4_Si");
  G4double detector_xlength = 30*mm; 
  G4double detector_ylength = 15*mm; 
  G4double detector_zlength = 100*um; //thickess
  
  G4double detector_place_x = 140*cm;

  G4Box* solidDetector =    
    new G4Box("Detector",
              0.5*detector_xlength,
              0.5*detector_ylength,
              0.5*detector_zlength);

  G4LogicalVolume* logicDetector =                         
    new G4LogicalVolume(solidDetector,
                        detector_mat,
                        "Detector");
                                   
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,detector_place_x),
                      logicDetector,
                      "Detector",
                      logicWorld,
                      false,
                      1,
                      true);
  G4VisAttributes* visDetector = new G4VisAttributes();
  visDetector->SetColor(219,154,51);
  logicDetector->SetVisAttributes(visDetector);

  return physWorld;
}