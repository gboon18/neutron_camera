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

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

// #include "SensitiveDetector.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{

  // if (!fScoringVolume) {
  //   const auto detConstruction = static_cast<const DetectorConstruction*>(
  //     G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  //   fScoringVolume = detConstruction->GetScoringVolume();
  // }

  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
    ->GetVolume()->GetLogicalVolume();

  G4Track* track = step->GetTrack();
  G4ParticleDefinition* particle = track->GetDefinition();
  G4String particleName = particle->GetParticleName();
  
  G4int pid = track->GetDynamicParticle()->GetParticleDefinition()->GetPDGEncoding();
  G4double edep = step->GetTotalEnergyDeposit()/CLHEP::keV;//For _HP library
  G4double kine = track->GetKineticEnergy()/CLHEP::keV;
  // G4double tote = track->GetTotalEnergy()/CLHEP::keV;

  G4ThreeVector pos = track->GetPosition();
  G4double gtime   = track->GetGlobalTime();

  // // check if we are in scoring volume
  // if (volume != fScoringVolume) return;

  // const G4StepPoint* endPoint = step->GetPostStepPoint();
  // // collect energy deposited in this step
  // // G4double edepStep = step->GetTotalEnergyDeposit();
  // G4double edepStep = endPoint->GetKineticEnergy();
  // // fEventAction->AddEdep(edepStep);
  // // G4cout<<"jey"<<G4endl;
  // // if(edepStep!=0)G4cout<<volume->GetName()<<", "<<edepStep<<" MeV"<<G4endl;
  // // G4cout<<"yej"<<G4endl;

  // Moved from SensitiveDetector.cc
  // get the status of the pre step point
  G4StepStatus PreStepStatus = step->GetPreStepPoint()->GetStepStatus();
  // get the status of the post step point
  G4StepStatus PostStepStatus = step->GetPostStepPoint()->GetStepStatus();
  // // get the volume of the pre step point
  // G4LogicalVolume* PreStepPoint = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  // // get the volume of the post step point
  // G4LogicalVolume* PostStepPoint = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  auto prevol   = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  auto postvol = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
  G4LogicalVolume* PreStepPoint = NULL;
  G4LogicalVolume* PostStepPoint = NULL;
  if(prevol) PreStepPoint = prevol->GetLogicalVolume();
  if(postvol) PostStepPoint = postvol->GetLogicalVolume();
  G4String preName = "";
  G4String postName = "";
  if(PreStepPoint) preName = PreStepPoint->GetName();
  if(PostStepPoint) postName = PostStepPoint->GetName();
    
  // G4cout<<PostStepPoint->GetName()<<G4endl;

  // G4cout<<PreStepPoint->GetName()<<G4endl;
  // auto postStepPoint = step->GetPostStepPoint();
  // if (!postStepPoint) {
  //   G4cout<<"No postStepoint"<<G4endl;
  // }
  // auto touchableHandle = postStepPoint->GetTouchableHandle();
  // if (!touchableHandle) {
  //   G4cout<<"No touchableHandle"<<G4endl;
  // }
  // auto vvolume = touchableHandle->GetVolume();
  // if (!vvolume) {
  //   G4cout<<"No volume"<<G4endl;
  // }
  // auto logicalVolume = vvolume ? vvolume->GetLogicalVolume() : nullptr;
  // if (!logicalVolume) {
  //   G4cout<<vvolume<<"... No logicalVolume"<<G4endl;
  // }

  
  int inout = -999;// -1: particle coming in. 0: inside the detector. 1: particle going out. // 

  // // if((PreStepStatus == fGeomBoundary) && (postName.substr(0,4) == "LV_L")) {inout = -1; } // 
  // // else if((PostStepStatus == fGeomBoundary) && (preName.substr(0,4) == "LV_L")) {inout = 1;} // 
  // // else {inout=0;} // 
  // if((PostStepStatus == fGeomBoundary) && (postName.substr(0,4) == "LV_L")) {inout = -1;}
  // else if((PostStepStatus == fGeomBoundary) && (postName == "worldVOL")) {inout = 1;}
  // else {inout=0;}
  // // G4cout<<preName<<", "<<postName<<": "<<inout<<G4endl;
  // // G4cout<<PreStepPoint->GetName()<<", "<<PostStepPoint->GetName()<<": "<<inout<<G4endl;
  // // auto sd = new SensitiveDetector();

  // int level = -999;
  // int detNo = -999;
  // if(postName.substr(0,4) == "LV_L") level = std::stoi(postName.substr(4,1));
  // if(postName.substr(0,4) == "LV_L") detNo = std::stoi(postName.substr(6,1));

  // if((postName.substr(0,4) == "LV_L") || (postName == "worldVOL")) {
  //   fEventAction->SetEdep(0, edep); // 
  //   fEventAction->FillKine(0, 0, kine);
  //   fEventAction->SetPidPosTime(0, 5*level+detNo, pid, particleName, pos, gtime);
  //   // fEventAction->SetInOut(inout); // moved to SteppingAction.cc
  //   fEventAction->FillNtuple(0);
  //   // fEventAction->FillNtuple(trackid, parenid);
  // }

  if(preName == "worldVOL" && postName.substr(0,4) == "LV_L") inout = -1;
  else if(preName.substr(0,4) == "LV_L" && postName == "worldVOL") inout = 1;
  else if(preName.substr(0,4) == "LV_L" && postName.substr(0,4) == "LV_L") inout = 0;
  else{inout = -999;}

  if(inout !=  -999){
    int level = -999;
    int detNo = -999;
    if(inout == -1) {
      level = std::stoi(postName.substr(4,1));
      detNo = std::stoi(postName.substr(6,1));
    }
    else if(inout == 1 || inout == 0){
      level = std::stoi(preName.substr(4,1));
      detNo = std::stoi(preName.substr(6,1));
    }
    // G4cout<<preName<<", "<<postName<<": "<<inout<<G4endl;
    fEventAction->SetEdep(0, edep); // 
    fEventAction->FillKine(0, 0, kine);
    fEventAction->SetPidPosTime(0, 5*level+detNo, pid, particleName, pos, gtime);
    fEventAction->SetInOut(inout);
    fEventAction->FillNtuple(0);
    // fEventAction->FillNtuple(trackid, parenid);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
