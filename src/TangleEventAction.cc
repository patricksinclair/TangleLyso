#include "TangleEventAction.hh"

#include "TangleRunAction.hh"
#include "TangleVSteppingAction.hh"
//This next include was added by psinclair
#include "TangleAnalysis.hh"

/*TangleEventAction::TangleEventAction
(TangleVSteppingAction* onePhotonSteppingAction)
: fTangleVSteppingAction(onePhotonSteppingAction)
{}*/

//This was edited to the annihilation photon stepping action by psinclair
TangleEventAction::TangleEventAction
        (TangleVSteppingAction* onePhotonSteppingAction)
        : fTangleVSteppingAction(onePhotonSteppingAction),
          crystScatAng(0.)
{}


TangleEventAction::~TangleEventAction()
{}

void TangleEventAction::BeginOfEventAction(const G4Event*)
{
    fTangleVSteppingAction->BeginOfEventAction();
    //psinclair
    crystScatAng = 0.;
}

void TangleEventAction::EndOfEventAction(const G4Event*)
{
    fTangleVSteppingAction->EndOfEventAction();

    //psinclair
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(1, crystScatAng);
    analysisManager->FillNtupleDColumn(0, crystScatAng);
    analysisManager->AddNtupleRow();
}
