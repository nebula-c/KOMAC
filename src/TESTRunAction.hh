#ifndef TESTRUNACTION_HH
#define TESTRUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "globals.hh"
#include "g4root.hh"

class TESTRunAction : public G4UserRunAction
{
  public:
    TESTRunAction();
    TESTRunAction(const char *);
    virtual ~TESTRunAction();

    // method from the base class
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void SetAnalysis();

  private:
    G4String fName;
};

#endif
