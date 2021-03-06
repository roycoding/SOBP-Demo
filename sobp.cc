#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4ScoringManager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif


int main(int argc,char** argv)
{

  // Run manager
  G4RunManager * runManager = new G4RunManager;

  // Activate UI-command base scorer
  G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
  scManager->SetVerboseLevel(1);

  // Setting up the detector
  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);
  
  // Creating particles and processes
  PhysicsList* phys;
  runManager->SetUserInitialization(phys = new PhysicsList);

   
  // Setting up particle generator
  G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);

  // User Stepping Action
//  SteppingAction* stepping_action = new SteppingAction;
//  runManager->SetUserAction(stepping_action);

      
#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif    
     
  // Get the pointer to the User Interface manager
  G4UImanager * UImanager = G4UImanager::GetUIpointer();  
  if (argc!=1){
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else{
#ifdef G4UI_USE
    G4UIExecutive * ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute vis.mac");     
#endif
//    ui->SessionStart();
    delete ui;
#endif
     
#ifdef G4VIS_USE
    delete visManager;
#endif     
    }

  delete runManager;

  return 0;
}



