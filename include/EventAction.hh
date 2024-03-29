//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file /include/EventAction.hh
/// \brief Definition of the ::EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;

/// Event action class

class EventAction : public G4UserEventAction
{
public:
  EventAction(RunAction* runAction);
  // ~EventAction() override = default;
  ~EventAction();

  void BeginOfEventAction(const G4Event* event) override;
  void EndOfEventAction(const G4Event* event) override;

  void AddEdep(G4int, G4double); //{
  // // fColEdep += edep[0];
  // // fDetEdep1 += edep[1];
  // // fDetEdep2 += edep[2];
  // // fDetEdep3 += edep[3];
  // // fDetEdep4 += edep[4];
  // // fDetEdep5 += edep[5];
  // // fDetEdep6 += edep[6];
  // // fDetEdep7 += edep[7];
  // // fDetEdep8 += edep[8];
  // // fDetEdep9 += edep[9];
  // for(int i = 0 ; i < 10 ; i++){
  //   fEdep[i] += edep[i];
  // }
  // } // get called from SteppingAction: adding edep for each step to one event.
  void FillKine(G4int, G4double);
  // void SetPid(G4String);
  void SetPid(G4int, G4String);
  // void FillNtuple();
  void FillNtuple(G4int, G4int);

private:
  RunAction* fRunAction = nullptr;
  G4int fEvtId;
  G4double   *fEdep;
  // G4double   fColEdep = 0.;
  // G4double   fDetEdep1 = 0.;
  // G4double   fDetEdep2 = 0.;
  // G4double   fDetEdep3 = 0.;
  // G4double   fDetEdep4 = 0.;
  // G4double   fDetEdep5 = 0.;
  // G4double   fDetEdep6 = 0.;
  // G4double   fDetEdep7 = 0.;
  // G4double   fDetEdep8 = 0.;
  // G4double   fDetEdep9 = 0.;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


