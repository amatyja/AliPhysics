/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* $Id$ */

#ifndef AliAnalysisTaskAO2Dconverter_H
#define AliAnalysisTaskAO2Dconverter_H

#include "AliAnalysisFilter.h"
#include "AliAnalysisTaskSE.h"
#include "AliEventCuts.h"

#include <TString.h>

#include "TClass.h"

#include <Rtypes.h>

class AliESDEvent;

class AliAnalysisTaskAO2Dconverter : public AliAnalysisTaskSE
{
public:
  AliAnalysisTaskAO2Dconverter() = default;
  AliAnalysisTaskAO2Dconverter(const char *name);
  virtual ~AliAnalysisTaskAO2Dconverter();

  AliAnalysisTaskAO2Dconverter(const AliAnalysisTaskAO2Dconverter &) = default;
  AliAnalysisTaskAO2Dconverter &operator=(const AliAnalysisTaskAO2Dconverter &) = delete;

  void SetUseEventCuts(Bool_t useEventCuts=kTRUE) { fUseEventCuts = useEventCuts;}
  Bool_t GetUseEventCuts() const {return fUseEventCuts;}

  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t *option);
  virtual void Terminate(Option_t *option);

  void SetNumberOfEventsPerCluster(int n) { fNumberOfEventsPerCluster = n; }

  virtual void SetTruncation(Bool_t trunc=kTRUE) {fTruncate = trunc;}

  static AliAnalysisTaskAO2Dconverter* AddTask(TString suffix = "");
  enum TreeIndex { // Index of the output trees
    kEvents = 0,
    kEventsExtra,
    kTracks,
    kCalo,
    kCaloTrigger,
    kMuon,
    kMuonCls,
    kZdc,
    kRun2V0,
    kFDD,
    kV0s,
    kCascades,
    kTOF,
    kMcParticle,
    kMcCollision,
    kMcTrackLabel,
    kMcCaloLabel,
    kMcCollisionLabel,
    kBC,
    kTrees
  };
  enum TaskModes { // Flag for the task operation mode
    kStandard = 0,
    kMC
  };
  enum MCGeneratorID { // Generator type
    kAliGenEventHeader = 0,
    kAliGenCocktailEventHeader,
    kAliGenDPMjetEventHeader,
    kAliGenEpos3EventHeader,
    kAliGenEposEventHeader,
    kAliGenEventHeaderTunedPbPb,
    kAliGenGeVSimEventHeader,
    kAliGenHepMCEventHeader,
    kAliGenHerwigEventHeader,
    kAliGenHijingEventHeader,
    kAliGenPythiaEventHeader,
    kAliGenToyEventHeader,
    kGenerators
  };
  enum TrackTypeEnum : uint8_t {
    GlobalTrack = 0,
    ITSStandalone,
    MFTStandalone,
    Run2Tracklet
  }; // corresponds to O2/Core/Framework/include/Framework/DataTypes.h
  enum MCParticleFlags : uint8_t {
    ProducedInTransport = 1 // Bit 0: 0 = from generator; 1 = from transport
  };
  static const TClass* Generator[kGenerators]; // Generators

  TTree* CreateTree(TreeIndex t);
  void PostTree(TreeIndex t);
  void EnableTree(TreeIndex t) { fTreeStatus[t] = kTRUE; };
  void DisableTree(TreeIndex t) { fTreeStatus[t] = kFALSE; };
  static const TString TreeName[kTrees];  //! Names of the TTree containers
  static const TString TreeTitle[kTrees]; //! Titles of the TTree containers

  void Prune(TString p) { fPruneList = p; }; // Setter of the pruning list
  void SetMCMode() { fTaskMode = kMC; };     // Setter of the MC running mode
  AliEventCuts& GetEventCuts() { return fEventCuts; }

  AliAnalysisFilter fTrackFilter; // Standard track filter object
private:
  Bool_t fUseEventCuts = kFALSE;         //! Use or not event cuts
  AliEventCuts fEventCuts;      //! Standard event cuts
  AliESDEvent *fESD = nullptr;  //! input event
  TList *fOutputList = nullptr; //! output list
  
  Int_t fEventCount = 0; //! event count

  // Output TTree
  TTree* fTree[kTrees] = { nullptr }; //! Array with all the output trees
  void Prune();                       // Function to perform tree pruning
  void FillTree(TreeIndex t);         // Function to fill the trees (only the active ones)

  // Task configuration variables
  TString fPruneList = "";                // Names of the branches that will not be saved to output file
  Bool_t fTreeStatus[kTrees] = { kTRUE }; // Status of the trees i.e. kTRUE (enabled) or kFALSE (disabled)
  int fNumberOfEventsPerCluster = 1000;   // Maximum basket size of the trees

  TaskModes fTaskMode = kStandard; // Running mode of the task. Useful to set for e.g. MC mode

  // Data structures

  struct {
    // Event data
    Int_t fBCsID = 0u;       /// Index to BC table
    // Primary vertex position
    Float_t  fPosX = -999.f;       /// Primary vertex x coordinate
    Float_t  fPosY = -999.f;       /// Primary vertex y coordinate
    Float_t  fPosZ = -999.f;       /// Primary vertex z coordinate
    // Primary vertex covariance matrix
    Float_t  fCovXX = 999.f;    /// cov[0]
    Float_t  fCovXY = 0.f;      /// cov[1]
    Float_t  fCovXZ = 0.f;      /// cov[2]
    Float_t  fCovYY = 999.f;    /// cov[3]
    Float_t  fCovYZ = 0.f;      /// cov[4]
    Float_t  fCovZZ = 999.f;    /// cov[5]
    // Quality parameters
    Float_t  fChi2 = 999.f;             /// Chi2 of the vertex
    UInt_t   fN = 0u;                /// Number of contributors

    // The calculation of event time certainly will be modified in Run3
    // The prototype below can be switched on request
    Float_t fCollisionTime = -999.f;    /// Event time (t0) obtained with different methods (best, T0, T0-TOF, ...)
    Float_t fCollisionTimeRes = -999.f; /// Resolution on the event time (t0) obtained with different methods (best, T0, T0-TOF, ...)
    UChar_t fCollisionTimeMask = 0u;    /// Mask with the method used to compute the event time (0x1=T0-TOF,0x2=T0A,0x3=TOC) for each momentum bins

  } collision; //! structure to keep the primary vertex (avoid name conflicts)
  
  struct {
    // Start indices and numbers of elements for data in the other trees matching this vertex.
    // Needed for random access of collision-related data, allowing skipping data discarded by the user
    Int_t     fStart[kTrees]    = {0}; /// Start entry indices for data in the other trees matching this vertex
    Int_t     fNentries[kTrees] = {0}; /// Numbers of entries for data in the other trees matching this vertex
  } eventextra; //! structure for benchmarking information

  struct {
    int fRunNumber = -1;         /// Run number
    ULong64_t fGlobalBC = 0u;    /// Unique bunch crossing id. Contains period, orbit and bunch crossing numbers
    ULong64_t fTriggerMask = 0u; /// Trigger class mask
  } bc; //! structure to keep trigger-related info
  
  struct {
    // Track data

    Int_t   fCollisionsID = -1;    /// The index of the collision vertex in the TF, to which the track is attached
    
    uint8_t fTrackType = 0;       // Type of track: global, ITS standalone, tracklet, ...
    
    // In case we need connection to TOF clusters, activate next lines
    // Int_t   fTOFclsIndex;     /// The index of the associated TOF cluster
    // Int_t   fNTOFcls;         /// The number of TOF clusters
    
    

    // Coordinate system parameters
    Float_t fX = -999.f;     /// X coordinate for the point of parametrisation
    Float_t fAlpha = -999.f; /// Local <--> global coor.system rotation angle

    // Track parameters
    Float_t fY = -999.f;          /// fP[0] local Y-coordinate of a track (cm)
    Float_t fZ = -999.f;          /// fP[1] local Z-coordinate of a track (cm)
    Float_t fSnp = -999.f;        /// fP[2] local sine of the track momentum azimuthal angle
    Float_t fTgl = -999.f;        /// fP[3] tangent of the track momentum dip angle
    Float_t fSigned1Pt = -999.f;  /// fP[4] 1/pt (1/(GeV/c))

    // "Covariance matrix"
    // The diagonal elements represent the errors = Sqrt(C[i,i])
    // The off-diagonal elements are the correlations = C[i,j]/Sqrt(C[i,i])/Sqrt(C[j,j])
    // The off-diagonal elements are multiplied by 128 (7bits) and packed in Char_t
    Float_t fSigmaY      = -999.f; /// Sqrt(fC[0])
    Float_t fSigmaZ      = -999.f; /// Sqrt(fC[2])
    Float_t fSigmaSnp    = -999.f; /// Sqrt(fC[5])
    Float_t fSigmaTgl    = -999.f; /// Sqrt(fC[9])
    Float_t fSigma1Pt    = -999.f; /// Sqrt(fC[14])
    Char_t fRhoZY        = 0;      /// 128*fC[1]/SigmaZ/SigmaY
    Char_t fRhoSnpY      = 0;      /// 128*fC[3]/SigmaSnp/SigmaY
    Char_t fRhoSnpZ      = 0;      /// 128*fC[4]/SigmaSnp/SigmaZ
    Char_t fRhoTglY      = 0;      /// 128*fC[6]/SigmaTgl/SigmaY
    Char_t fRhoTglZ      = 0;      /// 128*fC[7]/SigmaTgl/SigmaZ
    Char_t fRhoTglSnp    = 0;      /// 128*fC[8]/SigmaTgl/SigmaSnp
    Char_t fRho1PtY      = 0;      /// 128*fC[10]/Sigma1Pt/SigmaY
    Char_t fRho1PtZ      = 0;      /// 128*fC[11]/Sigma1Pt/SigmaZ
    Char_t fRho1PtSnp    = 0;      /// 128*fC[12]/Sigma1Pt/SigmaSnp
    Char_t fRho1PtTgl    = 0;      /// 128*fC[13]/Sigma1Pt/SigmaTgl

    // Additional track parameters
    Float_t fTPCinnerP = -999.f; /// Full momentum at the inner wall of TPC for dE/dx PID

    // Track quality parameters
    ULong64_t fFlags = 0u;       /// Reconstruction status flags

    // Clusters and tracklets
    UChar_t fITSClusterMap = 0u;   /// ITS map of clusters, one bit per a layer
    UChar_t fTPCNClsFindable = 0u; /// number of clusters that could be assigned in the TPC
    Char_t fTPCNClsFindableMinusFound = 0;       /// difference between foundable and found clusters
    Char_t fTPCNClsFindableMinusCrossedRows = 0; ///  difference between foundable clsuters and crossed rows
    UChar_t fTPCNClsShared = 0u;   /// Number of shared clusters
    UChar_t fTRDPattern = 0u;   /// Bit 0-5 if tracklet from TRD layer used for this track

    // Chi2
    Float_t fITSChi2NCl = -999.f; /// chi2/Ncl ITS
    Float_t fTPCChi2NCl = -999.f; /// chi2/Ncl TPC
    Float_t fTRDChi2 = -999.f;    /// chi2 TRD match (?)
    Float_t fTOFChi2 = -999.f;    /// chi2 TOF match (?)

    // PID
    Float_t fTPCSignal = -999.f; /// dE/dX TPC
    Float_t fTRDSignal = -999.f; /// dE/dX TRD
    Float_t fTOFSignal = -999.f; /// TOFsignal
    Float_t fLength = -999.f;    /// Int.Lenght @ TOF
    Float_t fTOFExpMom = -999.f; /// TOF Expected momentum based on the expected time of pions
  } tracks;                      //! structure to keep track information

  struct {
    // MC collision
    Int_t fBCsID = 0u;       /// Index to BC table
    Short_t fGeneratorsID = 0u; /// Generator ID used for the MC
    Float_t fPosX = -999.f;  /// Primary vertex x coordinate from MC
    Float_t fPosY = -999.f;  /// Primary vertex y coordinate from MC
    Float_t fPosZ = -999.f;  /// Primary vertex z coordinate from MC
    Float_t fT = -999.f;  /// Time of the collision from MC
    Float_t fWeight = -999.f;  /// Weight from MC
  } mccollision;  //! MC collisions = vertices

  struct {
    // Track label to find the corresponding MC particle
    UInt_t fLabel = 0;       /// Track label
    UShort_t fLabelMask = 0; /// Bit mask to indicate detector mismatches (bit ON means mismatch)
                           /// Bit 0-6: mismatch at ITS layer
                           /// Bit 7-9: # of TPC mismatches in the ranges 0, 1, 2-3, 4-7, 8-15, 16-31, 32-63, >64
                           /// Bit 10: TRD, bit 11: TOF, bit 15: negative label sign
  } mctracklabel; //! Track labels
  
  struct {
    // Calo cluster label to find the corresponding MC particle
    UInt_t fLabel = 0;       /// Calo label
    UShort_t fLabelMask = 0; /// Bit mask to indicate detector mismatches (bit ON means mismatch)
                             /// bit 15: negative label sign
  } mccalolabel; //! Calo labels
  
  struct {
    // MC collision label
    UInt_t fLabel = 0;       /// Collision label
    UShort_t fLabelMask = 0; /// Bit mask to indicate collision mismatches (bit ON means mismatch)
                             /// bit 15: negative label sign
  } mccollisionlabel; //! Collision labels
  
  struct {
    // MC particle

    Int_t   fMcCollisionsID = -1;    /// The index of the MC collision vertex

    // MC information (modified version of TParticle
    Int_t fPdgCode    = -99999; /// PDG code of the particle
    Int_t fStatusCode = -99999; /// generation status code
    uint8_t fFlags     = 0;     /// See enum MCParticleFlags
    Int_t fMother[2]   = { 0 }; /// Indices of the mother particles
    Int_t fDaughter[2] = { 0 }; /// Indices of the daughter particles
    Float_t fWeight    = 1;     /// particle weight from the generator or ML

    Float_t fPx = -999.f; /// x component of momentum
    Float_t fPy = -999.f; /// y component of momentum
    Float_t fPz = -999.f; /// z component of momentum
    Float_t fE  = -999.f; /// Energy (covers the case of resonances, no need for calculated mass)

    Float_t fVx = -999.f; /// x of production vertex
    Float_t fVy = -999.f; /// y of production vertex
    Float_t fVz = -999.f; /// z of production vertex
    Float_t fVt = -999.f; /// t of production vertex
    // We do not use the polarisation so far
  } mcparticle;  //! MC particles from the kinematics tree

  // To test the compilation uncoment the line below
  // #define USE_TOF_CLUST 1
#ifdef USE_TOF_CLUST
  struct {
    // TOF clusters
    // PH: Do we store the TOF information per track?
    Int_t fTOFChannel = -1;        /// Index of the matched channel
    Short_t fTOFncls = -1;         /// Number of matchable clusters of the track
    Float_t fDx = -999.f;          /// Residual along x
    Float_t fDz = -999.f;          /// Residual along z
    Float_t fToT = -999.f;         /// ToT
    Float_t fLengthRatio = -999.f; /// Ratio of the integrated track length @ TOF to the cluster with respect to the matched cluster
  } tofClusters;                   //! structure to keep TOF clusters
#endif

  struct {
    // Calorimeter data (EMCAL & PHOS)

    Int_t fBCsID = 0u;       /// Index to BC table

    Short_t fCellNumber = -1;     /// Cell absolute Id. number
    Float_t fAmplitude = -999.f;  /// Cell amplitude (= energy!)
    Float_t fTime = -999.f;       /// Cell time
    Char_t fCellType = -1;        /// EMCAL: High Gain: 0 / Low Gain: 1 / TRU: 2 / LEDmon 3 (see DataFromatsEMCAL/Constants.h)
    Char_t fCaloType = -1;        /// Cell type (-1 is undefined, 0 is PHOS, 1 is EMCAL)
  } calo;                         //! structure to keep EMCAL info
  
  struct {
    // Calorimeter trigger data (EMCAL & PHOS)
    Int_t fBCsID = 0u;        /// Index to BC table
    Short_t fFastOrAbsID = - 1;   /// FastOR absolute ID
    Float_t fL0Amplitude = -1.f;  /// L0 amplitude (ADC) := Peak Amplitude
    Float_t fL0Time = -1.f;       /// L0 time
    Int_t fL1TimeSum = -1;        /// L1 amplitude (ADC) := Integral over L0 time samples
    Char_t fNL0Times = -1;        /// Number of L0 times
    Int_t fTriggerBits = 0;       /// Online trigger bits
    Char_t fCaloType = -1;            /// Calorimeter type (-1 is undefined, 0 is PHOS, 1 is EMCAL)
  } calotrigger;                  //! structure to keep calo trigger info

  struct {
    // MUON track data

    Int_t fBCsID = 0u;            /// Index to BC table
    // In case we need connection to muon clusters, activate next lines
    // Int_t   fClusterIndex;        /// The index of the associated MUON clusters
    // Int_t   fNclusters;           /// The number of MUON clusters

    /// Parameters at vertex
    Float_t fInverseBendingMomentum = 0.f; ///< Inverse bending momentum (GeV/c ** -1) times the charge 
    Float_t fThetaX = -999.f;              ///< Angle of track at vertex in X direction (rad)
    Float_t fThetaY = -999.f;              ///< Angle of track at vertex in Y direction (rad)
    Float_t fZMu = -999.f;                 ///< Z coordinate (cm)
    Float_t fBendingCoor = -999.f;         ///< bending coordinate (cm)
    Float_t fNonBendingCoor = -999.f;      ///< non bending coordinate (cm)

    /// Reduced covariance matrix of UNCORRECTED track parameters, ordered as follow:      <pre>
    /// [0] =  <X,X>
    /// [1] =<X,ThetaX>  [2] =<ThetaX,ThetaX>
    /// [3] =  <X,Y>     [4] =  <Y,ThetaX>     [5] =  <Y,Y>
    /// [6] =<X,ThetaY>  [7] =<ThetaX,ThetaY>  [8] =<Y,ThetaY>  [9] =<ThetaY,ThetaY>
    /// [10]=<X,InvP_yz> [11]=<ThetaX,InvP_yz> [12]=<Y,InvP_yz> [13]=<ThetaY,InvP_yz> [14]=<InvP_yz,InvP_yz>  </pre>
    Float_t fCovariances[15] = {-999.}; ///< \brief reduced covariance matrix of parameters AT FIRST CHAMBER

    /// Global tracking info
    Float_t fChi2 = 999.f;                ///< chi2 in the MUON track fit
    Float_t fChi2MatchTrigger = 999.f;    ///< chi2 of trigger/track matching
  } muons;                        //! structure to keep muons information

  struct {
    // Muon cluster data
    
    Int_t   fMuonsID = -1; /// The index of the muon track to which the clusters are attached
    Float_t fX = -999.f;         ///< cluster X position
    Float_t fY = -999.f;         ///< cluster Y position
    Float_t fZ = -999.f;         ///< cluster Z position
    Float_t fErrX = -999.f;      ///< transverse position errors
    Float_t fErrY = -999.f;      ///< transverse position errors
    Float_t fCharge = -999.f;    ///< cluster charge
    Float_t fChi2 = -999.f;      ///< cluster chi2
  } mucls;              //! structure to keep muon clusters information

  struct {
    Int_t   fBCsID = 0u;                 /// Index to BC table
    Float_t fEnergyZEM1 = 0.f;           ///< E in ZEM1
    Float_t fEnergyZEM2 = 0.f;           ///< E in ZEM2
    Float_t fEnergyCommonZNA = 0.f;      ///< E in common ZNA PMT - high gain chain
    Float_t fEnergyCommonZNC = 0.f;      ///< E in common ZNC PMT - high gain chain
    Float_t fEnergyCommonZPA = 0.f;      ///< E in common ZPA PMT - high gain chain
    Float_t fEnergyCommonZPC = 0.f;      ///< E in common ZPC PMT - high gain chain
    Float_t fEnergySectorZNA[4] = {0.f}; ///< E in 4 ZNA sectors - high gain chain
    Float_t fEnergySectorZNC[4] = {0.f}; ///< E in 4 ZNC sectors - high gain chain
    Float_t fEnergySectorZPA[4] = {0.f}; ///< E in 4 ZPA sectors - high gain chain
    Float_t fEnergySectorZPC[4] = {0.f}; ///< E in 4 ZPC sectors - high gain chain
    Float_t fTimeZEM1 = 0.f;             ///< Corrected time in ZEM1      
    Float_t fTimeZEM2 = 0.f;             ///< Corrected time in ZEM2
    Float_t fTimeZNA = 0.f;              ///< Corrected time in ZNA
    Float_t fTimeZNC = 0.f;              ///< Corrected time in ZNC     
    Float_t fTimeZPA = 0.f;              ///< Corrected time in ZPA     
    Float_t fTimeZPC = 0.f;              ///< Corrected time in ZPC     
  } zdc;                                 //! structure to keep ZDC information

  struct {
    /// Run 2 VZERO Legacy table 

    Int_t fBCsID = 0u;       /// Index to BC table

    Float_t fAdc[64] = {0.f};          ///  adc for each channel
    Float_t fTime[64] = {0.f};         ///  time for each channel
    Float_t fWidth[64] = {0.f};        ///  time width for each channel
    Float_t fMultA = 0.f;            ///  calibrated A-side multiplicity
    Float_t fMultC = 0.f;            ///  calibrated C-side multiplicity
    Float_t fTimeA = 0.f;            ///  average A-side time
    Float_t fTimeC = 0.f;            ///  average C-side time
    ULong64_t fBBFlag = 0ul;         ///  BB Flags from Online V0 Electronics
    ULong64_t fBGFlag = 0ul;         ///  BG Flags from Online V0 Electronics
  } vzero;                     //! structure to keep VZERO information

  struct {
    /// FDD (AD)  

    Int_t fBCsID = 0u;              /// Index to BC table

    Float_t fAmplitude[8] = {0.f};  ///  adc for each channel (not filled)
    Float_t fTimeA = 0.f;           ///  average A-side time
    Float_t fTimeC = 0.f;           ///  average C-side time
    uint8_t fBCSignal = 0;          ///  trigger info (not filled)
  } fdd;                            //! structure to keep FDD (AD) information

  struct {
    /// V0s (Ks, Lambda)

    Int_t fPosTrackID = -1; // Positive track ID
    Int_t fNegTrackID = -1; // Negative track ID
  } v0s;               //! structure to keep v0sinformation

  struct {
    /// Cascades

    Int_t fV0sID = -1; // V0 ID
    Int_t fTracksID = -1; // Bachelor track ID
  } cascs;             //! structure to keep cascades information

  /// Offsets to convert the IDs within one collision to global IDs
  Int_t fOffsetMuTrackID = 0; ///! Offset of MUON track IDs (used in the clusters)
  Int_t fOffsetTrackID = 0;   ///! Offset of track IDs (used in V0s)
  Int_t fOffsetV0ID = 0;      ///! Offset of track IDs (used in cascades)
  Int_t fOffsetLabel = 0;      ///! Offset of track IDs (used in cascades)

  /// Set truncation
  Bool_t fTruncate = kFALSE;
  
  ClassDef(AliAnalysisTaskAO2Dconverter, 9);
};

#endif
