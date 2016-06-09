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
// $Id: G4EmStandardPhysics71.cc,v 1.5 2007/02/13 16:29:16 vnivanch Exp $
// GEANT4 tag $Name: geant4-08-02-patch-01 $
//
//---------------------------------------------------------------------------
//
// ClassName:   G4EmStandardPhysics71
//
// Author:      V.Ivanchenko 09.11.2005
//
// Modified:
// 19.12.2005 V.Ivanchenko StepFunction for electrons (1.0, 1.0*mm)
// 21.06.2006 V.Ivanchenko use recent msc with step limitation off
// 23.06.2006 V.Ivanchenko set dRoverRange = 0.8 for e- and e+
// 13.11.2006 V.Ivanchenko use G4hMultipleScattering
// 23.11.2006 V.Ivanchenko remove mscStepLimit option and improve cout
// 13.02.2007 V.Ivanchenko set skin=0.0
//
//----------------------------------------------------------------------------
//

#include "G4EmStandardPhysics71.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4LossTableManager.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4hMultipleScattering.hh"
#include "G4MultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4KaonPlus.hh"
#include "G4KaonMinus.hh"
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4EmStandardPhysics71::G4EmStandardPhysics71(const G4String& name, G4int ver)
  : G4VPhysicsConstructor(name), verbose(ver)
{
  G4LossTableManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4EmStandardPhysics71::~G4EmStandardPhysics71()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4EmStandardPhysics71::ConstructParticle()
{
// gamma
  G4Gamma::Gamma();

// leptons
  G4Electron::Electron();
  G4Positron::Positron();
  G4MuonPlus::MuonPlus();
  G4MuonMinus::MuonMinus();

// mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();

// barions
  G4Proton::Proton();
  G4AntiProton::AntiProton();

// ions
  G4Deuteron::Deuteron();
  G4Triton::Triton();
  G4He3::He3();
  G4Alpha::Alpha();
  G4GenericIon::GenericIonDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4EmStandardPhysics71::ConstructProcess()
{
  // Add standard EM Processes

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {

      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);

    } else if (particleName == "e-") {

      if(verbose > 1)
        G4cout << "### G4standard_fast instantiates eIoni " 
               << particleName << G4endl;
      G4eIonisation* eioni = new G4eIonisation();
      eioni->SetStepFunction(0.8, 1.0*mm);
      G4MultipleScattering* msc = new G4MultipleScattering;
      pmanager->AddProcess(msc,                   -1, 1, 1);
      pmanager->AddProcess(eioni,                 -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung, -1, 3, 3);

    } else if (particleName == "e+") {

      if(verbose > 1)
        G4cout << "### G4standard_fast instantiates eIoni " 
               << particleName << G4endl;
      G4eIonisation* eioni = new G4eIonisation();
      eioni->SetStepFunction(0.8, 1.0*mm);
      G4MultipleScattering* msc = new G4MultipleScattering;
      pmanager->AddProcess(msc,                     -1, 1, 1);
      pmanager->AddProcess(eioni,                   -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1, 4);

    } else if (particleName == "mu+" ||
               particleName == "mu-"    ) {

      if(verbose > 1)
        G4cout << "### G4standard_fast instantiates muIoni " 
               << particleName << G4endl;
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation,        -1, 2, 2);
      pmanager->AddProcess(new G4MuBremsstrahlung,    -1, 3, 3);
      pmanager->AddProcess(new G4MuPairProduction,    -1, 4, 4);

    } else if (particleName == "alpha" ||
               particleName == "He3" ||
               particleName == "GenericIon") {

      if(verbose > 1)
        G4cout << "### G4standard_fast instantiates ionIoni " 
               << particleName << G4endl;
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);

    } else if (particleName == "anti_omega-" ||
               particleName == "anti_proton" ||
               particleName == "anti_sigma+" ||
               particleName == "anti_sigma-" ||
               particleName == "anti_xi-" ||
               particleName == "deuteron" ||
               particleName == "kaon+" ||
               particleName == "kaon-" ||
               particleName == "omega-" ||
               particleName == "pi+" ||
               particleName == "pi-" ||
               particleName == "proton" ||
               particleName == "sigma+" ||
               particleName == "sigma-" ||
               particleName == "tau+" ||
               particleName == "tau-" ||
               particleName == "triton" ||
               particleName == "xi-" ) {
      if(verbose > 1)
        G4cout << "### G4Standard_fast instantiates hIoni " 
               << particleName << G4endl;
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
    }
  }
  G4EmProcessOptions opt;
  opt.SetVerbose(verbose);
  opt.SetMscStepLimitation(false);
  //  opt.SetSkin(0.0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......