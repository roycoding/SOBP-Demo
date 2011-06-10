//DetectorConstruction.hh

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:  
  DetectorConstruction();
  ~DetectorConstruction();

public:
  G4VPhysicalVolume* Construct();

private:
  G4Box*             solidWorld;    // pointer to the solid world 
  G4LogicalVolume*   logicWorld;    // pointer to the logical world
  G4VPhysicalVolume* physiWorld;    // pointer to the physical world
     
  G4Box*             solidPhantom;  // pointer to the solid Phantom
  G4LogicalVolume*   logicPhantom;  // pointer to the logical Phantom
  G4VPhysicalVolume* physiPhantom;  // pointer to the physical detectpr

  G4Material*        WorldMater;    // pointer to the world material
  G4Material*        PhantomMater; // pointer to the Phantom material

  G4UserLimits* stepLimit;            // pointer to user step limits
            
  G4double WorldXLength;
  G4double WorldYLength;
  G4double WorldZLength;            

  G4int NumPhantoms ;
  G4int DimX ;
  G4int DimY ;
  G4int DimZ ;

  G4double PhantomXLength;         
  G4double PhantomYLength; 
  G4double PhantomZLength;
  G4double HalfPhantomXLength ;
  G4double HalfPhantomYLength ;
  G4double HalfPhantomZLength ;

};

#endif
