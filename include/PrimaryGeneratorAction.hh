//PrimaryGeneratorAction.hh

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 

#include "G4VUserPrimaryGeneratorAction.hh"

class DetectorConstruction;
class G4GeneralParticleSource;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(DetectorConstruction*); 
  ~PrimaryGeneratorAction();

public:
  void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource* particleSource;
  DetectorConstruction* myDetector;
};

#endif


