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

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
// #include "Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4AnalysisManager.hh" 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{

  //RunAction copied from B1. Usage of G4AnalysisManager copied from B4b

  // // set printing event number per each event
  // G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  // Declaring the analysisManager in RunAction ensures multi-threading

  // Create directories
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  // analysisManager->SetVerboseLevel(1);
  analysisManager->SetVerboseLevel(0);
  // analysisManager->SetNtupleMerging(true);
  //   // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple
  //

  // Creating histograms
  analysisManager->CreateH1("col" ,"Edep in collimator", 100, 0., 15*keV);
  analysisManager->CreateH1("det1" ,"Edep in detector 1", 100, 0., 15*keV);
  analysisManager->CreateH1("det2" ,"Edep in detector 2", 100, 0., 15*keV);
  analysisManager->CreateH1("det3" ,"Edep in detector 3", 100, 0., 15*keV);
  analysisManager->CreateH1("det4" ,"Edep in detector 4", 100, 0., 15*keV);
  analysisManager->CreateH1("det5" ,"Edep in detector 5", 100, 0., 15*keV);
  analysisManager->CreateH1("det6" ,"Edep in detector 6", 100, 0., 15*keV);
  analysisManager->CreateH1("det7" ,"Edep in detector 7", 100, 0., 15*keV);
  analysisManager->CreateH1("det8" ,"Edep in detector 8", 100, 0., 15*keV);
  analysisManager->CreateH1("det9" ,"Edep in detector 9", 100, 0., 15*keV);
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{

  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "col_det.csv";
  // Other supported output types:
  G4String fileName2 = "col_det.root";
  // G4String fileName = "col_det.hdf5";
  // G4String fileName = "col_det.xml";
  // analysisManager->OpenFile(fileName);
  analysisManager->OpenFile(fileName2);
  G4cout << "Using " << analysisManager->GetType() << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl;
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl;
    }

    // G4cout << " Coll Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(0)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(0)->rms(),  "keV") << G4endl;

    // G4cout << " Detector1 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(1)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(1)->rms(),  "keV") << G4endl;

    // G4cout << " Detector2 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(2)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(2)->rms(),  "keV") << G4endl;

    // G4cout << " Detector3 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(3)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(3)->rms(),  "keV") << G4endl;

    // G4cout << " Detector4 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(4)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(4)->rms(),  "keV") << G4endl;

    // G4cout << " Detector5 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(5)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(5)->rms(),  "keV") << G4endl;

    // G4cout << " Detector6 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(6)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(6)->rms(),  "keV") << G4endl;

    // G4cout << " Detector7 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(7)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(7)->rms(),  "keV") << G4endl;

    // G4cout << " Detector8 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(8)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(8)->rms(),  "keV") << G4endl;

    // G4cout << " Detector9 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(9)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(9)->rms(),  "keV") << G4endl;

    // save histograms & ntuple
    //
    analysisManager->Write();
    analysisManager->CloseFile();
    
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void RunAction::AddEdep(G4double edep)
// {
//   fEdep  += edep;
//   fEdep2 += edep*edep;
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

