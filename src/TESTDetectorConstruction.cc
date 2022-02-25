#include "TESTDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"

TESTDetectorConstruction::TESTDetectorConstruction()
: G4VUserDetectorConstruction()
{
}

TESTDetectorConstruction::~TESTDetectorConstruction()
{
}

struct structInfo{
  G4double xlength, ylength, zlength; //z : thickness
  G4double xplace=0, yplace=0, zplace;
  G4int copyNo;
  G4String mat, name;
  G4Material* mymat;

  structInfo(G4int _copyNo, G4String _mat, G4String _name, G4double x = 0, G4double y = 0, G4double z = 0, G4double xp = 0, G4double yp = 0, G4double zp = 0)
  { G4NistManager* nist = G4NistManager::Instance();
  xlength=x*mm; ylength=y*mm; zlength=z*mm; xplace=xp*mm; yplace=yp*mm, zplace=zp*mm; copyNo=_copyNo; mat=_mat; name=_name;
  mymat = nist -> FindOrBuildMaterial(mat);
  }
  
};

void MakeStructure(G4LogicalVolume *logicWorld, structInfo *mystruct);

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
      
  static G4LogicalVolume* logicWorld =                         
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
  // structInfo detector(1,"G4_Si","Detector",30,15,0,0,0,1400);
  // detector.zlength=100*um;
  // MakeStructure(logicWorld, &detector);

// -----------------------------------------------------
  // Al-shield example
  structInfo Al_6(2,"G4_Al","Al_6",100,100,10,0,0,100);
  MakeStructure(logicWorld, &Al_6);


  // -----------------------------------------------------
  // Target type faraday cup : fCup
  // structInfo fCup(2,"G4_Al","fCup",150,150,5,0,0,700);
  // MakeStructure(logicWorld, &fCup);
  
  // -----------------------------------------------------
  // Collimator type faraday cup : collimator
  // structInfo collimator(3,"G4_Al","Collimator",150,150,5,0,0,400);  

  // G4Box* solidCollimator =    
  //   new G4Box(collimator.name,                       // its name
  //             0.5*collimator.xlength,                // half x
  //             0.5*collimator.ylength,                // half y
  //             0.5*collimator.zlength);               // half z

  // G4Tubs *Al_hole = new G4Tubs("Al_hole", 0,2.5*cm,collimator.zlength,0,2*M_PI);
  // auto collimator_hole = new G4SubtractionSolid("Collimator_hole", solidCollimator, Al_hole, 0, G4ThreeVector(0,0,0));

  //  G4LogicalVolume* logicCollimator =                         
  //   new G4LogicalVolume(collimator_hole,          //its solid
  //                       collimator.mymat,           //its material
  //                       collimator.name);            //its name
                                   
  //   new G4PVPlacement(0,                     //no rotation
  //                     G4ThreeVector(0,0,collimator.zplace),       //at (0,0,0)
  //                     logicCollimator,            //its logical volume
  //                     collimator.name,               //its name
  //                     logicWorld,                     //its mother  volume
  //                     false,                 //no boolean operation
  //                     3,                     //copy number
  //                     true);                 //overlaps checking


  // -----------------------------------------------------
  // Inv_detector
  structInfo Inv(9,"G4_Galactic","Inv",100,100,1,0,0,105);
  MakeStructure(logicWorld, &Inv);

  return physWorld;
}

void MakeStructure(G4LogicalVolume *logicWorld, structInfo *mystruct)
{ 
  G4Box* mysolid =    
    new G4Box(mystruct->name,
              0.5*mystruct->xlength,
              0.5*mystruct->ylength,
              0.5*mystruct->zlength);

   G4LogicalVolume* mylogic =                         
    new G4LogicalVolume(mysolid,
                        mystruct->mymat,
                        mystruct->name);
                                   
    new G4PVPlacement(0,
                      G4ThreeVector(mystruct->xplace,mystruct->yplace,mystruct->zplace),
                      mylogic,
                      mystruct->name,
                      logicWorld,
                      false,
                      mystruct->copyNo,
                      true);

  // G4VisAttributes* myvis = new G4VisAttributes();
  // myvis->SetColor(219,154,51);
  // mylogic->SetVisAttributes(myvis);

}

