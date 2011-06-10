// PhysicsList.cc

#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"

#include "G4DecayPhysics.hh"

#include "G4HadronElasticPhysics.hh"
#include "G4HadronDElasticPhysics.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4HadronQElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonBinaryCascadePhysics.hh"

#include "G4RadioactiveDecayPhysics.hh"

#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"

#include "G4ProcessManager.hh"
#include "G4Decay.hh"

#include "StepMax.hh"

#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"

//------

PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
  G4LossTableManager::Instance();
  defaultCutValue = 0.01*mm;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;

  helIsRegisted  = false;
  bicIsRegisted  = false;
  biciIsRegisted = false;

  stepMaxProcess  = 0;

  pMessenger = new PhysicsListMessenger(this);

  SetVerboseLevel(1);

  //......Default physics........
  // EM physics
  emName = G4String("emstandard_opt3");  
  emPhysicsList = new G4EmStandardPhysics_option3(1);

  // Deacy physics and all particles
  decPhysicsList = new G4DecayPhysics();

}

//------

PhysicsList::~PhysicsList()
{
  delete pMessenger;
  delete emPhysicsList;
  delete decPhysicsList;
  for(size_t i=0; i<hadronPhys.size(); i++) {delete hadronPhys[i];}
}

//------

void PhysicsList::ConstructParticle()
{
  decPhysicsList->ConstructParticle();
}

//------

void PhysicsList::ConstructProcess()
{
  // transportation
  //
  AddTransportation();
  
  // electromagnetic physics list
  //
  emPhysicsList->ConstructProcess();

  // decay physics list
  //
  decPhysicsList->ConstructProcess();
  
  // hadronic physics lists
  for(size_t i=0; i<hadronPhys.size(); i++) {
    hadronPhys[i]->ConstructProcess();
  }
  
  // step limitation (as a full process)
  //  
  AddStepMax();  
}

//------

void PhysicsList::AddPhysicsList(const G4String& name)
{
  if (verboseLevel>1) {
    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
  }

  if (name == emName) return;

  else if (name == "emstandard_opt0") {

    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics(1);

  } else if (name == "emstandard_opt1") {

    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option1();

  } else if (name == "emstandard_opt2") {

    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option2();
    
  } else if (name == "emstandard_opt3") {

    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option3();    

  } else if (name == "emlivermore") {
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmLivermorePhysics();

  } else if (name == "empenelope") {
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmPenelopePhysics();

  } else if (name == "elastic" && !helIsRegisted) {
    hadronPhys.push_back( new G4HadronElasticPhysics());
    helIsRegisted = true;

  } else if (name == "DElastic" && !helIsRegisted) {
    hadronPhys.push_back( new G4HadronDElasticPhysics());
    helIsRegisted = true;

  } else if (name == "HElastic" && !helIsRegisted) {
    hadronPhys.push_back( new G4HadronHElasticPhysics());
    helIsRegisted = true;

  } else if (name == "QElastic" && !helIsRegisted) {
    hadronPhys.push_back( new G4HadronQElasticPhysics());
    helIsRegisted = true;

  } else if (name == "binary" && !bicIsRegisted) {
    hadronPhys.push_back(new G4HadronInelasticQBBC());
    bicIsRegisted = true;

  } else if (name == "binary_ion" && !biciIsRegisted) {
    hadronPhys.push_back(new G4IonBinaryCascadePhysics());
    biciIsRegisted = true;

  } else if (name == "radioactive") { // && !biciIsRegisted) {
    hadronPhys.push_back(new G4RadioactiveDecayPhysics());

  } else {

    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
           << " is not defined"
           << G4endl;
  }
}

//------

void PhysicsList::AddStepMax()
{
  // Step limitation seen as a process
  stepMaxProcess = new StepMax();
  stepMaxProcess->SetMaxStep(0.1*mm) ; // This *should* be done in the macro

  theParticleIterator->reset();
  while ((*theParticleIterator)()){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (stepMaxProcess->IsApplicable(*particle) && pmanager)
      {
	pmanager ->AddDiscreteProcess(stepMaxProcess);
      }
  }
}

//------

void PhysicsList::SetCuts()
{

  if (verboseLevel >0){
    G4cout << "PhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }

  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");

  if (verboseLevel>0) DumpCutValuesTable();
}

//------

void PhysicsList::SetCutForGamma(G4double cut)
{
  cutForGamma = cut;
  SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

//------

void PhysicsList::SetCutForElectron(G4double cut)
{
  cutForElectron = cut;
  SetParticleCuts(cutForElectron, G4Electron::Electron());
}

//------

void PhysicsList::SetCutForPositron(G4double cut)
{
  cutForPositron = cut;
  SetParticleCuts(cutForPositron, G4Positron::Positron());
}

//------

