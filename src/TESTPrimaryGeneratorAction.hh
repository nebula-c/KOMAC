#ifndef TESTPRIMARYGENERATORACTION_HH
#define TESTPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
#include "globals.hh"

class TESTPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    TESTPrimaryGeneratorAction();    
    virtual ~TESTPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         

  private:
    G4GeneralParticleSource* fParticleGun;
};

#endif
