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

#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction)
{
  fEdep = new G4double[10];
  //Initialize the array
  for(int i = 0 ; i < 10 ; i++){
    fEdep[i] = 0.;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
  delete [] fEdep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  // fEdep = 0.;
  for(int i = 0 ; i < 10 ; i++){
    fEdep[i] = 0.;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
  // // accumulate statistics in run action
  // fRunAction->AddEdep(fEdep);

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  for(int i = 0 ; i < 10 ; i++){
    analysisManager->FillH1(i, fEdep[i]);
  }
  // analysisManager->FillH1(0, fEdep[0]);
  // analysisManager->FillH1(1, fEdep[1]);
  // analysisManager->FillH1(2, fEdep[2]);
  // analysisManager->FillH1(3, fEdep[3]);
  // analysisManager->FillH1(4, fEdep[4]);
  // analysisManager->FillH1(5, fEdep[5]);
  // analysisManager->FillH1(6, fEdep[6]);
  // analysisManager->FillH1(7, fEdep[7]);
  // analysisManager->FillH1(8, fEdep[8]);
  // analysisManager->FillH1(9, fEdep[9]);

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::AddEdep(G4int id, G4double edep){
  fEdep[id] += edep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
