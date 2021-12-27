#include "TESTRunAction.hh"

TESTRunAction::TESTRunAction()
: G4UserRunAction()
{
  fName = "data";
  SetAnalysis();
}

TESTRunAction::TESTRunAction(const char *name)
: G4UserRunAction()
{
  fName = name;
  SetAnalysis();
}

TESTRunAction::~TESTRunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> Write();
  analysisManager -> CloseFile();

  delete G4AnalysisManager::Instance();
}

void TESTRunAction::BeginOfRunAction(const G4Run*)
{
}

void TESTRunAction::EndOfRunAction(const G4Run*)
{
}

void TESTRunAction::SetAnalysis()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> OpenFile(fName);

  analysisManager -> CreateNtuple("step", "step");

  analysisManager -> CreateNtupleIColumn("eventID");
  analysisManager -> CreateNtupleIColumn("volumeID");
  analysisManager -> CreateNtupleIColumn("particleID");
  analysisManager -> CreateNtupleSColumn("particleName");

  analysisManager -> CreateNtupleDColumn("prePosition.x");
  analysisManager -> CreateNtupleDColumn("prePosition.y");
  analysisManager -> CreateNtupleDColumn("prePosition.z");

  // analysisManager -> CreateNtupleDColumn("edep");

  analysisManager -> FinishNtuple();

  analysisManager -> CreateNtuple("event", "energy deposit per event in volume-1");
  analysisManager -> CreateNtupleDColumn("edep1");
  analysisManager -> CreateNtupleIColumn("eventID");
  analysisManager -> FinishNtuple();
}
