#include "TangleRunAction.hh"
#include "TangleAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"
#include <cassert>
#include <fstream>

//TangleRunAction* TangleRunAction::fpMasterRunAction = 0;
std::vector<std::vector<TangleRunAction::Data>*> TangleRunAction::fPointers;

namespace {
    G4Mutex runActionMutex = G4MUTEX_INITIALIZER;
}

TangleRunAction::TangleRunAction()
        :G4UserRunAction()
{
    /*if (G4Threading::IsMasterThread()) {
      fpMasterRunAction = this;
    }
    fData.reserve(10000000);
    G4AutoLock lock(&runActionMutex);
    fpMasterRunAction->fPointers.push_back(&fData);*/

    //I believe this reserves the specified amount of space for the vector of structs
    fData.reserve(10000000);


    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(10);

    // Create analysis manager
    // The choice of analysis technology is done via selection of a namespace
    // in TangleAnalysis.hh
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;

    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(1);

    // Book histograms, ntuple

    // Creating histograms
    analysisManager->CreateH1("1", "Crystal DelPhi (North relative)", 4, 0., 360.*degree);


    // Creating ntuple
    analysisManager->CreateNtuple("LysoScatter", "Angles");
    analysisManager->CreateNtupleDColumn("CrystDeltaPhi");
    analysisManager->FinishNtuple();
}

TangleRunAction::~TangleRunAction()
{}

void TangleRunAction::BeginOfRunAction(const G4Run*)
{
    //removes all data from the vector so it's ready for the next run to record
    fData.clear();


    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    G4String fileName = "TangleScatterTest";
    analysisManager->OpenFile(fileName);
}

/*namespace {
  std::ofstream outFile("outFile.csv");
}*/

void TangleRunAction::EndOfRunAction(const G4Run* run)
{
   /* G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;

    G4String runType;
    if (G4Threading::IsMasterThread()) {
        runType = "Global Run";
        // Workers finished...
        // outFile << "#,theta1,phi1,theta2,phi2";
        *//*for (const auto& pointer: fPointers) {
          for (const auto& data: *pointer) {
            outFile
            << "\n," << data.fTheta1 << ',' << data.fPhi1
            << ',' << data.fTheta2 << ',' << data.fPhi2;
          }
        }*//*
        //outFile << std::endl;
    } else {
        runType = "Local Run-";
    }

    G4cout
            << "\n----------------------End of " << runType << "------------------------"
            << "\n The run consists of " << nofEvents << " events."
            << "\n------------------------------------------------------------"
            << G4endl;*/

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // save histograms & ntuple
    analysisManager->Write();
    analysisManager->CloseFile();
}
