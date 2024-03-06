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

  // G4cout<<"SensitiveDetector::ProcessHits volName: "<<volName<<", matName: "<<matName<<G4endl;
  // PrintMaterialElements(material);

  // //av_1_impr_1_LV_det5_pv_5
  // if(volName == "av_1_impr_1_LV_det1_pv_1"){
  //   G4cout<<"SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  // else if(volName == "av_1_impr_1_LV_det2_pv_2"){
  //   G4cout<<"SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  // else if(volName == "av_1_impr_1_LV_det3_pv_3"){
  //   G4cout<<"SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  // else if(volName == "av_1_impr_1_LV_det4_pv_4"){
  //   G4cout<<"SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  // else if(volName == "av_1_impr_1_LV_det5_pv_5"){
  //   G4cout<<"SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  // else if(volName == "av_1_impr_1_LV_det6_pv_6"){
  //   G4cout<<"SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  // else if(volName == "av_1_impr_1_LV_det7_pv_7"){
  //   G4cout<<"SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  // else if(volName == "av_1_impr_1_LV_det8_pv_8"){
  //   G4cout<<"SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  // else if(volName == "av_1_impr_1_LV_det9_pv_9"){
  //   G4cout<<"SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  // else{
  //   G4cout<<"ARG... SensitiveDetector::ProcessHits You are in "<<volName<<G4endl;
  // }
  
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
