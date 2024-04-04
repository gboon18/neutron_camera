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
  fEdep = new G4double[ndet];
  //Initialize the array
  for(int i = 0 ; i < ndet ; i++){
    fEdep[i] = 0.;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
  delete [] fEdep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* aEvt)
{
  fEvtId = aEvt->GetEventID();
  // G4cout<<"fEvtID = "<<fEvtId<<G4endl;
  // fEdep = 0.;
  for(int i = 0 ; i < ndet ; i++){
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

  /* // fill histograms
  for(int id = 0 ; id < ndet ; id++){
    analysisManager->FillH1(id, fEdep[id]);
  }
   */  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::AddEdep(G4int id, G4double edep){
  fEdep[id] += edep;
  // auto analysisManager = G4AnalysisManager::Instance();
  // analysisManager->FillNtupleDColumn(3, edep);//edep
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void EventAction::SetEdep(G4double edep){
void EventAction::SetEdep(G4int id_detcol, G4double edep){
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(id_detcol, 3, edep);//edep
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void EventAction::FillKine(G4int id, G4double kine){
void EventAction::FillKine(G4int id_detcol, G4int id, G4double kine){
  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  // if(id==0) analysisManager->FillH1(id, kine);//neutron kinetic energy

  // if(id==0) analysisManager->FillNtupleDColumn(2, kine);//kinetic energy
  if(id_detcol==0) {
    if(id==0) analysisManager->FillNtupleDColumn(id_detcol, 2, kine);//kinetic energy
  }
  else if(id_detcol==1) {
    if(id==0) analysisManager->FillNtupleDColumn(id_detcol, 0, kine);//kinetic energy
  }
  // if(id==2) analysisManager->FillNtupleDColumn(8, kine);//temporary for gamma
  // if(id==3) analysisManager->FillNtupleDColumn(4, kine);//temporary for electron
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void EventAction::SetPid(G4String pid){
//   // get analysis manager
//   auto analysisManager = G4AnalysisManager::Instance();
//   analysisManager->FillNtupleSColumn(0, pid);
// }

// void EventAction::SetPid(G4int pid, G4String pid_str){
// void EventAction::SetPidAndPos(G4int pid, G4String pid_str, G4ThreeVector pos){
void EventAction::SetPidPosTime(G4int id_detcol, G4int id_block, G4int pid, G4String pid_str, G4ThreeVector pos, G4double gtime){
  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  // analysisManager->FillNtupleSColumn(0, pid_str);
  // analysisManager->FillNtupleIColumn(1, pid);
  // analysisManager->FillNtupleDColumn(4, pos.getX());
  // analysisManager->FillNtupleDColumn(5, pos.getY());
  // analysisManager->FillNtupleDColumn(6, pos.getZ());

  if(id_detcol==0){
    analysisManager->FillNtupleSColumn(id_detcol, 0, pid_str);
    analysisManager->FillNtupleIColumn(id_detcol, 1, pid);
    analysisManager->FillNtupleDColumn(id_detcol, 4, pos.getX());
    analysisManager->FillNtupleDColumn(id_detcol, 5, pos.getY());
    analysisManager->FillNtupleDColumn(id_detcol, 6, pos.getZ());
    analysisManager->FillNtupleDColumn(id_detcol, 7, gtime);
    analysisManager->FillNtupleIColumn(id_detcol, 8, id_block);
  }
  else if(id_detcol==1){
    analysisManager->FillNtupleDColumn(id_detcol, 1, pos.getX());
    analysisManager->FillNtupleDColumn(id_detcol, 2, pos.getY());
    analysisManager->FillNtupleDColumn(id_detcol, 3, pos.getZ());
    analysisManager->FillNtupleDColumn(id_detcol, 4, gtime);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::SetInOut(G4int inout){
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleIColumn(0, 9, inout);  
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::SetInitalEnergyMom(G4double ene, G4ThreeVector mom){
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(0, 10, ene);
  analysisManager->FillNtupleDColumn(0, 11, mom.getX());
  analysisManager->FillNtupleDColumn(0, 12, mom.getY());
  analysisManager->FillNtupleDColumn(0, 13, mom.getZ());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void EventAction::FillNtuple(){
void EventAction::FillNtuple(G4int id_detcol){
// void EventAction::FillNtuple(G4int trackid, G4int parenid){
  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  // analysisManager->FillNtupleIColumn(5, fEvtId);  
  // analysisManager->FillNtupleIColumn(6, trackid);  
  // analysisManager->FillNtupleIColumn(7, parenid);  

  // analysisManager->AddNtupleRow();
  analysisManager->AddNtupleRow(id_detcol);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
