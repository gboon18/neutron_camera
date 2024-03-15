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
/// \file persistency/gdml//src/SensitiveDetector.cc
/// \brief Implementation of the SensitiveDetector class
//
//
//

#include "SensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include <CLHEP/Units/SystemOfUnits.h>

#include "G4RunManager.hh"
#include "EventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensitiveDetector::SensitiveDetector(const G4String& name)
  : G4VSensitiveDetector(name)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensitiveDetector::~SensitiveDetector()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SensitiveDetector::Initialize(G4HCofThisEvent*)
{
}

//....Ooooo0ooooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  // G4cout << "SensitiveDetector::ProcessHits Processing hits ...." << G4endl;
  // G4String volName = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
  G4LogicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  G4String volName = volume->GetName();
  G4Material* material = volume->GetMaterial();
  G4String matName = material->GetName();
  G4Track* track = aStep->GetTrack();
  G4ParticleDefinition* particle = track->GetDefinition();
  G4String particleName = particle->GetParticleName();

  // Access the EventAction
  auto eventAction = const_cast<EventAction*>(static_cast<const EventAction*>(G4RunManager::GetRunManager()->GetUserEventAction()));

  G4int pid = track->GetDynamicParticle()->GetParticleDefinition()->GetPDGEncoding();
  G4double edep = aStep->GetTotalEnergyDeposit()/CLHEP::keV;//For _HP library
  G4double kine = track->GetKineticEnergy()/CLHEP::keV;

  G4double trackid = track->GetTrackID();
  G4double parenid = track->GetParentID();

  // const G4StepPoint* endPoint = aStep->GetPostStepPoint();
  // G4double edep = endPoint->GetKineticEnergy();// For NeutronPhysics Hadr04 example. No physics at all except Neutron. No secondary particle.
  // G4cout<<volName<<G4endl;

  // if(volName != "worldVOL") G4cout<<volName<<" heeeeeey "<<edep<<" MeV"<<G4endl;
  // Call a method on EventAction to update some data based on this hit
  // if(particleName == "neutron" && edep != 0) G4cout<<"The volume is "<<volName<<". The particle is "<<particleName<<". Edep = "<<edep<<" MeV"<<G4endl;
  // if(particleName == "neutron" && kine!=0) G4cout<<"The volume is "<<volName<<". The particle is "<<particleName<<". Kinetic Energy = "<<kine<<" MeV"<<G4endl;
  if (eventAction) {
    if(
       // volName == "LV_000_1136__001"
       // ||
       // volName == "LV_000_1136__002"
       // ||
       // volName == "LV_000_1136__003"
       // ||
       // volName == "LV_000_1136__004"
       volName == "LV_Box"
       ) {
      if(edep!=0){
	if(particleName == "proton") eventAction->AddEdep(1, edep);
	else if(particleName == "gamma") eventAction->AddEdep(2, edep);
	else if(particleName == "e-") {eventAction->AddEdep(3, edep);eventAction->FillKine(3, kine);}
	else if(particleName == "e+") eventAction->AddEdep(4, edep);
	else if(particleName == "deuteron") eventAction->AddEdep(5, edep);
	else if(particleName == "C12") eventAction->AddEdep(6, edep);
	else if(particleName == "C13") eventAction->AddEdep(7, edep);
	else if(particleName == "C14") eventAction->AddEdep(8, edep);
	else eventAction->AddEdep(9, edep);
	eventAction->AddEdep(10, edep);
	// if(edep>0.01) G4cout<<"The particle is "<<particleName<<". Edep = "<<edep<<" MeV"<<G4endl;
	// if(particleName == "neutron") G4cout<<"The particle is "<<particleName<<". Edep = "<<edep<<" MeV"<<G4endl;
	// else {G4cout<<"The particle is "<<particleName<<". Edep = "<<edep<<" MeV"<<G4endl;}
      }//if(edep!=0)
      if(kine!=0){
	if(particleName == "neutron") eventAction->FillKine(0, kine);
      }//if(kine!=0)
      if(edep!=0 || kine!=0) {/*eventAction->SetPid(particleName);*/ eventAction->SetPid(pid, particleName); eventAction->FillNtuple(trackid, parenid);}
    }//sensitive volume check
    else{G4cout<<"SensitiveDetector::ProcessHits. I don't know what this volume "<<volName<<" is~~ You better stop this play~~"<<G4endl;}
  }//if (eventAction)
  else{G4cout<<"SensitiveDetector::ProcessHits. No event? Somethings wrong.. You better stop this"<<G4endl;}
  // PrintMaterialElements(material);
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SensitiveDetector::PrintMaterialElements(const G4Material* material) {
    if (!material) {
        G4cout << "Material is null" << G4endl;
        return;
    }

    G4cout << "Material " << material->GetName() << " has the following composition: " << G4endl;

    // Get the number of elements in the material
    const G4int numberOfElements = material->GetNumberOfElements();

    // Iterate over the elements and their fraction
    for (G4int i = 0; i < numberOfElements; ++i) {
        const G4Element* element = material->GetElement(i);
        const G4double fraction = material->GetFractionVector()[i]; // Get the fraction of the element

        // Access properties of the element
        G4String elementName = element->GetName();
        G4int atomicNumber = element->GetZ();
        G4double atomicMass = element->GetA();

        // Determine if the ratio is by number (nAtoms) or by weight (mass fraction)
        if(material->GetFractionVector()[i] > 1.) { // Typically, nAtoms ratios are large numbers
            G4cout << "Element: " << elementName
                   << ", Atomic Number: " << atomicNumber
                   << ", Atomic Mass: " << atomicMass / (CLHEP::g/CLHEP::mole) << " g/mole"
                   << ", Number of Atoms (per molecule): " << fraction << G4endl;
        } else { // Mass fractions are typically <= 1
            G4cout << "Element: " << elementName
                   << ", Atomic Number: " << atomicNumber
                   << ", Atomic Mass: " << atomicMass / (CLHEP::g/CLHEP::mole) << " g/mole"
                   << ", Mass Fraction: " << fraction*100 << "%" << G4endl;
        }
    }
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
}
