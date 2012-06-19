#ifndef ALIANALYSISETRECONSTRUCTED_H
#define ALIANALYSISETRECONSTRUCTED_H

class TH2F;
class TH2D;

//_________________________________________________________________________
//  Utility Class for transverse energy studies
//  Base class for ESD analysis
//  - reconstruction output
//
//*-- Authors: Oystein Djuvsland (Bergen), David Silvermyr (ORNL)
//_________________________________________________________________________

#include "AliAnalysisEt.h"

class TH2I;
class AliVParticle;
class AliESDEvent;
class AliAnalysisHadEtCorrections;

class AliAnalysisEtReconstructed : public AliAnalysisEt
{

public:

    AliAnalysisEtReconstructed();
    virtual ~AliAnalysisEtReconstructed();

    virtual Int_t AnalyseEvent(AliVEvent* event);

    virtual void Init();

    /** Fill the objects you want to output, classes which add new histograms should overload this. */
    virtual void FillOutputList(TList *list);
    void SetCorrections(AliAnalysisHadEtCorrections *corr) {
        fCorrections = corr;
    }

    /** Create the histograms, must be overloaded if you want to add your own */
    virtual void CreateHistograms();
    
    void SetEMinCorrection(const Double_t factor) { fEMinCorrection = factor; }

protected:

    bool CheckGoodVertex(AliVParticle *track);
    virtual bool TrackHitsCalorimeter(AliVParticle *track, Double_t magField);

    AliAnalysisHadEtCorrections *fCorrections;//corrections needed for hadronic et

    Double_t fPidCut; // cut on the pid probability

    TH2F *fHistChargedPionEnergyDeposit; /** Energy deposited in calorimeter by charged pions */
    TH2F *fHistProtonEnergyDeposit; /** Energy deposited in calorimeter by protons */
    TH2F *fHistAntiProtonEnergyDeposit; /** Energy deposited in calorimeter by anti-protons */
    TH2F *fHistChargedKaonEnergyDeposit; /** Energy deposited in calorimeter by charged kaons */
    TH2F *fHistMuonEnergyDeposit; /** Energy deposited in calorimeter by muons */

    TH1F *fHistRemovedEnergy; // removed energy
    
    Double_t fGeomCorrection; // geometry correction
    Double_t fEMinCorrection; // Emin correction
    
    Double_t fRecEffCorrection; // Eff correction
    Double_t CalcTrackClusterDistance(const Float_t pos[3],Int_t *trkMatchId, const AliESDEvent *event);
    
    TH2D *fClusterPosition; // Position of clusters
    
    TH2D *fHistChargedEnergyRemoved;
    TH2D *fHistNeutralEnergyRemoved;
    TH2D *fHistGammaEnergyAdded;
    

private:

    AliAnalysisEtReconstructed(const AliAnalysisEtReconstructed& g);
    AliAnalysisEtReconstructed & operator=(const AliAnalysisEtReconstructed&);



    ClassDef(AliAnalysisEtReconstructed, 1);
};

#endif // ALIANALYSISETRECONSTRUCTED_H
