//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// -------------------------------------------------------------------
//
// GEANT4 Class header file
//
//
// File name:     G4VSubCutoffProcessor
//
// Author:        Vladimir Ivanchenko
// 
// Creation date: 03.01.2002
//
// Modifications: 
//
// Class Description: 
//
// Abstract class for interface to simualtion of subCutoff

// -------------------------------------------------------------------
//

#ifndef G4VSubCutoffProcessor_h
#define G4VSubCutoffProcessor_h 1


#include "globals.hh"
#include "g4std/vector"

class G4Step;
class G4Track;
class G4ParticleDefinition;
class G4DynamicParticle;
class G4EmModelManager;
class G4PhysicsTable;

class G4VSubCutoffProcessor 
{

public:

  G4VSubCutoffProcessor() {};

  virtual ~G4VSubCutoffProcessor() {};

  virtual G4std::vector<G4Track*>* SampleSecondary(const G4Step& step,
                                                   const G4DynamicParticle*,
                                                         G4double meanLoss) {return 0;};

  virtual void Initialise(const G4ParticleDefinition*, 
                          const G4ParticleDefinition*, 
                                G4EmModelManager* ) {};

  virtual void SetLambdaSubTable(G4PhysicsTable*) {};

  virtual G4PhysicsTable* LambdaSubTable() {return 0;};

protected:

private:

  // hide assignment operator 
  G4VSubCutoffProcessor & operator=(const  G4VSubCutoffProcessor &right);
  G4VSubCutoffProcessor(const  G4VSubCutoffProcessor&);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif
