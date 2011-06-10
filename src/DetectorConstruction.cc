//DetectorConstruction.cc

#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
 
DetectorConstruction::DetectorConstruction()
{

}

 
DetectorConstruction::~DetectorConstruction()
{


  delete stepLimit;   

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  //--------- Material definition ---------

  // Use materials predefined by Geant4

  G4NistManager* man = G4NistManager::Instance();

  G4Material* Water  = man->FindOrBuildMaterial("G4_WATER");
//  G4Material* Air  = man->FindOrBuildMaterial("G4_AIR");
  G4Material* Vacuum  = man->FindOrBuildMaterial("G4_Galactic");

  // Print all the materials defined.
  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
  
  //------------------------------ 
  // World
  //------------------------------ 
  WorldXLength = 100*cm;
  WorldYLength = 100*cm;
  WorldZLength = 100*cm;
  WorldMater = Vacuum ;

  G4double HalfWorldXLength = 0.5*WorldXLength;
  G4double HalfWorldYLength = 0.5*WorldYLength;
  G4double HalfWorldZLength = 0.5*WorldZLength;

  solidWorld= new G4Box("world",HalfWorldXLength, HalfWorldYLength,
			HalfWorldZLength);
  logicWorld= new G4LogicalVolume(solidWorld, Vacuum, "World", 0, 0, 0); 
  G4ThreeVector positionWorld = G4ThreeVector(0,0,0);
  physiWorld = new G4PVPlacement(0,               // no rotation
                                 positionWorld,   // at (x,y,z)
                                 logicWorld,      // its logical volume
                				 "World",         // its name
                                 0,               // its mother  volume
                                 false,           // no boolean operations
                                 0);              // copy number

  //------------------------------ 
  // Phantom
  //------------------------------

  PhantomXLength = 20*cm ;         
  PhantomYLength = 20*cm ; 
  PhantomZLength = 20*cm ;

  PhantomMater = Water; 
  
  HalfPhantomXLength = 0.5*PhantomXLength;
  HalfPhantomYLength = 0.5*PhantomYLength;
  HalfPhantomZLength = 0.5*PhantomZLength;

  solidPhantom = new G4Box("Phantom", HalfPhantomXLength, HalfPhantomYLength, 
			    HalfPhantomZLength);
  logicPhantom = new G4LogicalVolume(solidPhantom, PhantomMater, "Phantom",0,0,0);  
  G4ThreeVector positionPhantom = G4ThreeVector(0,0,0);
  physiPhantom = new G4PVPlacement(0,                // no rotation
				    positionPhantom, // at (x,y,z)
				    logicPhantom,    // its logical volume
				    "Phantom",       // its name
				    logicWorld,       // its mother  volume
				    false,            // no boolean operations
				    0);               // copy number

  //--------- Visualization attributes -------------------------------
  G4VisAttributes* WorldVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  logicWorld ->SetVisAttributes(WorldVisAtt);

  G4VisAttributes* PhantomVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  logicPhantom->SetVisAttributes(PhantomVisAtt);

  //--------- User Limits -------------------------------
    
  // Sets a max Step length in the tracker region, with G4StepLimiter
  G4double maxStep = 0.005*PhantomZLength;
  stepLimit = new G4UserLimits(maxStep);
  logicPhantom->SetUserLimits(stepLimit);


  return physiWorld;
}

