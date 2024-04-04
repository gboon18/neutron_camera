#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <TLeaf.h>

void convert_root2csv(const char* rootFileName, const char* ntupleName, const char* csvFileName) {
  TFile *file = TFile::Open(rootFileName);
  if (!file || file->IsZombie()) {
    std::cerr << "Error opening file: " << rootFileName << std::endl;
    return;
  }

  TTree *tree = (TTree*)file->Get(ntupleName);
  if (!tree) {
    std::cerr << "Ntuple/Tree " << ntupleName << " not found!" << std::endl;
    file->Close();
    return;
  }

  std::ofstream csvFile(csvFileName);
  const TObjArray *branches = tree->GetListOfBranches();
  int nBranches = branches->GetEntriesFast();

  // Write CSV headers
  for (int i = 0; i < nBranches; ++i) {
    TBranch *branch = (TBranch*)branches->At(i);
    csvFile << branch->GetName();
    if (i < nBranches - 1) csvFile << ",";
  }
  csvFile << "\n";

  // Dynamic data storage
  std::vector<void*> branchBuffers(nBranches);
  std::vector<std::string> branchTypes(nBranches);

  for (int i = 0; i < nBranches; ++i) {
    TBranch *branch = (TBranch*)branches->At(i);
    TLeaf *leaf = branch->GetLeaf(branch->GetName());
    if (!leaf) continue; // Skip branches without a leaf

    std::string typeName = leaf->GetTypeName();

    // Allocate buffer and set branch address
    if (typeName == "Int_t") {
      branchBuffers[i] = new Int_t;
      tree->SetBranchAddress(branch->GetName(), branchBuffers[i]);
    } else if (typeName == "Float_t") {
      branchBuffers[i] = new Float_t;
      tree->SetBranchAddress(branch->GetName(), branchBuffers[i]);
    } else if (typeName == "Double_t") {
      branchBuffers[i] = new Double_t;
      tree->SetBranchAddress(branch->GetName(), branchBuffers[i]);
    } else if (typeName == "Char_t") {
      branchBuffers[i] = new Char_t[256]; // Adjust size as needed
      tree->SetBranchAddress(branch->GetName(), branchBuffers[i]);
    }
    branchTypes[i] = typeName;
  }

  // Read entries and write to CSV
  Long64_t nEntries = tree->GetEntries();
  for (Long64_t entry = 0; entry < nEntries; ++entry) {
    tree->GetEntry(entry);
    for (int i = 0; i < nBranches; ++i) {
      if (branchTypes[i] == "Int_t") {
        csvFile << *(static_cast<Int_t*>(branchBuffers[i]));
      } else if (branchTypes[i] == "Float_t") {
        csvFile << *(static_cast<Float_t*>(branchBuffers[i]));
      } else if (branchTypes[i] == "Double_t") {
        csvFile << *(static_cast<Double_t*>(branchBuffers[i]));
      } else if (branchTypes[i] == "Char_t") {
        csvFile << static_cast<Char_t*>(branchBuffers[i]);
      }
      if (i < nBranches - 1) csvFile << ",";
    }
    csvFile << "\n";
  }

  // Cleanup
    for (int i = 0; i < nBranches; ++i) {
        if (branchBuffers[i] != nullptr) {
            if (branchTypes[i] == "Int_t") {
                delete static_cast<Int_t*>(branchBuffers[i]);
            } else if (branchTypes[i] == "Float_t") {
                delete static_cast<Float_t*>(branchBuffers[i]);
            } else if (branchTypes[i] == "Double_t") {
                delete static_cast<Double_t*>(branchBuffers[i]);
            } else if (branchTypes[i] == "Char_t") {
                delete[] static_cast<Char_t*>(branchBuffers[i]); // Use delete[] for arrays
            }
            branchBuffers[i] = nullptr;
        }
    }

  csvFile.close();
  file->Close();
  std::cout << "Conversion complete. CSV file created: " << csvFileName << std::endl;
}
