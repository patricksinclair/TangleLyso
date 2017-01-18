#ifndef TangleEventAction_hh
#define TangleEventAction_hh

#include "G4UserEventAction.hh"
#include "globals.hh"

class TangleRunAction;
class TangleVSteppingAction;

class TangleEventAction : public G4UserEventAction
{
public:

    TangleEventAction(TangleVSteppingAction*);

    virtual ~TangleEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    //added by psinclair
    //Added to record difference in crystals that are scattered to
    void addCrystalDelPhi(G4double crystDPhi);

    //booleans to check if the photon has been recorded yet
    void ScatBool(G4bool scatYN);
    void RecordedBool(G4bool recordYN);

private:

    TangleVSteppingAction* fTangleVSteppingAction;
    //added by psinclair
    G4double crystScatAng;
    G4bool scattered;
    G4bool recorded;
};


inline void TangleEventAction::addCrystalDelPhi(G4double crystDPhi) {
    crystScatAng = crystDPhi;
}
inline void TangleEventAction::ScatBool(G4bool isScattered){
    scattered = isScattered;
}
inline void TangleEventAction::RecordedBool(G4bool isRecorded) {
    recorded = isRecorded;
}

#endif
