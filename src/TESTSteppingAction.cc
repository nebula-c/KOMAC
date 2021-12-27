#include "TESTSteppingAction.hh"
#include "TESTEventAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4EventManager.hh"

TESTSteppingAction::TESTSteppingAction()
: G4UserSteppingAction()
{
}

TESTSteppingAction::~TESTSteppingAction()
{
}

void TESTSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4int eventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
  G4int volumeID = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetCopyNo();
  G4double totalEdep = step -> GetTotalEnergyDeposit();
  G4int particleID = step-> GetTrack()->GetParticleDefinition()->GetParticleDefinitionID();
  G4String particleName = step-> GetTrack()->GetParticleDefinition()->GetParticleName();
    
    
  G4StepPoint* prePoint = step -> GetPreStepPoint();
  G4ThreeVector prePosition = prePoint -> GetPosition();
  G4ThreeVector preMomentum = prePoint->GetMomentum();
    
  // G4StepPoint* postPoint = step -> GetPostStepPoint();
  // G4ThreeVector postPosition = postPoint->GetPosition();
  // G4ThreeVector postMomentum = postPoint ->GetMomentum();


  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> FillNtupleIColumn(0, eventID);
  analysisManager -> FillNtupleIColumn(1, volumeID);
  analysisManager -> FillNtupleIColumn(2, particleID);
  analysisManager -> FillNtupleSColumn(3, particleName);

  analysisManager -> FillNtupleDColumn(4, prePosition.x());
  analysisManager -> FillNtupleDColumn(5, prePosition.y());
  analysisManager -> FillNtupleDColumn(6, prePosition.z());

  analysisManager -> AddNtupleRow();

  TESTEventAction *eventAction = (TESTEventAction *) G4EventManager::GetEventManager() -> GetUserEventAction();
  if (volumeID == 1)
  {
    eventAction -> AddEnergyDeposit1(totalEdep);
    analysisManager -> FillNtupleIColumn(1, 1, eventID);
    analysisManager -> AddNtupleRow(1);

  }   
}