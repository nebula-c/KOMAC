#include "TESTEventAction.hh"

TESTEventAction::TESTEventAction()
: G4UserEventAction()
{
}

TESTEventAction::~TESTEventAction()
{
}

void TESTEventAction::BeginOfEventAction(const G4Event*)
{
  edep1 = 0.;
}

void TESTEventAction::EndOfEventAction(const G4Event* event)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager -> FillNtupleDColumn(1, 0, edep1);
  analysisManager -> FillNtupleIColumn(1, 1, event->GetEventID());
  analysisManager -> AddNtupleRow(1);
}
