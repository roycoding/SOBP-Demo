// StepMaxMessenger.hh

#ifndef StepMaxMessenger_h
#define StepMaxMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class StepMax;
class G4UIcmdWithADoubleAndUnit;


class StepMaxMessenger: public G4UImessenger
{
  public:
    StepMaxMessenger(StepMax*);
   ~StepMaxMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    StepMax* stepMax;
    G4UIcmdWithADoubleAndUnit* StepMaxCmd;
};


#endif
