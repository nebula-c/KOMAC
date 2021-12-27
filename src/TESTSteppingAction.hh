#ifndef TESTSTEPPINGACTION_HH
#define TESTSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"
#include "g4root.hh"

class TESTSteppingAction : public G4UserSteppingAction
{
  public:
    TESTSteppingAction();
    virtual ~TESTSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);
};

#endif
