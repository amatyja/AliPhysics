
// This file is used to give a list of histograms to be created by the manager.
// the histogram names are automatically generated by the createNames.py script
// the type/binning of the histograms depends on the range.
// DON'T FORGET TO RUN createNames.py AFTER EDITING THIS FILE
// IMPORTANT CONVENTIONS:
// - don't assign numerical value explicitly to the entries (they would be skipped in the authomatic name generation)
// - If you add an histogram set, please respect the order:
//   PionPlus, KaonPlus, ProtonPlus, PionMinus, KaonMinus, ProtonMinus (needed for getters)

namespace AliSpectraNameSpaceBoth
{
   enum BothPtHist_t
   {

      // 6 Pt Generated True Primary
      kHistPtGenTruePrimaryPionPlus,            // Pt histo for pions +, generated tracks, true ID, primary Event
      kHistPtGenTruePrimaryKaonPlus,            // Pt histo for kaons +, generated tracks, true ID, primary Event
      kHistPtGenTruePrimaryProtonPlus,          // Pt histo for protons +, generated tracks, true ID, primary Event
      kHistPtGenTruePrimaryPionMinus,           // Pt histo for pions -, generated tracks, true ID, primary Event
      kHistPtGenTruePrimaryKaonMinus,           // Pt histo for kaons -, generated tracks, true ID, primary Event
      kHistPtGenTruePrimaryProtonMinus,         // Pt histo for protons -, generated tracks, true ID, primary Event
      kNPtGenHist = kHistPtGenTruePrimaryProtonMinus,                    // Number of ptGen-likehistos histos - PID
      kHistPtGen,                               // Pt histo for all particles, generated tracks
      kNPtGenAllChHist = kHistPtGen,                    // Number of ptGen-likehistos histos - AllCh
      
      // 6 Pt Reconstructed Sigma
      kHistPtRecSigmaPionPlus,                  // Pt histo for pions +, reconstructed tracks, sigma ID
      kHistPtRecSigmaKaonPlus,                  // Pt histo for kaons +, reconsructed tracks, sigma ID
      kHistPtRecSigmaProtonPlus,                // Pt histo for protons +, reconstructed tracks, sigma ID
      kHistPtRecSigmaPionMinus,                 // Pt histo for pions -, reconstructed tracks, sigma ID
      kHistPtRecSigmaKaonMinus,                 // Pt histo for kaons -, reconstructed tracks, sigma ID
      kHistPtRecSigmaProtonMinus,               // Pt histo for protons -, reconstructed tracks, sigma ID
      
      // 6 Pt Reconstructed True & identified with nsigma
      kHistPtRecTruePionPlus,                   // Pt histo for pions +, reconstructed tracks, true ID
      kHistPtRecTrueKaonPlus,                   // Pt histo for kaons +, reconsructed tracks, true ID
      kHistPtRecTrueProtonPlus,                 // Pt histo for protons +, reconstructed tracks, true ID
      kHistPtRecTruePionMinus,                  // Pt histo for pions -, reconstructed tracks, true ID
      kHistPtRecTrueKaonMinus,                  // Pt histo for kaons -, reconstructed tracks, true ID
      kHistPtRecTrueProtonMinus,                // Pt histo for protons -, reconstructed tracks, true ID
      kHistPtRecTrueMuonPlus,                   // Pt histo for muons +, reconstructed tracks, true ID,
      kHistPtRecTrueMuonMinus,                  // Pt histo for muons +, reconstructed tracks, true ID,

      // 6 Pt Reconstructed True & (regardless of the offline nsigma identification)
      kHistPtRecPrimaryPionPlus,                   // Pt histo for pions +, reconstructed tracks, true ID
      kHistPtRecPrimaryKaonPlus,                   // Pt histo for kaons +, reconsructed tracks, true ID
      kHistPtRecPrimaryProtonPlus,                 // Pt histo for protons +, reconstructed tracks, true ID
      kHistPtRecPrimaryPionMinus,                  // Pt histo for pions -, reconstructed tracks, true ID
      kHistPtRecPrimaryKaonMinus,                  // Pt histo for kaons -, reconstructed tracks, true ID
      kHistPtRecPrimaryProtonMinus,                // Pt histo for protons -, reconstructed tracks, true ID
      kHistPtRecPrimaryMuonPlus,                   // Pt histo for muons +, reconstructed tracks, true ID,
      kHistPtRecPrimaryMuonMinus,                  // Pt histo for muons +, reconstructed tracks, true ID,
            
      // 6 Pt Reconstructed Sigma Primary
      kHistPtRecSigmaPrimaryPionPlus,           // Pt histo for pions +, reconstructed tracks, sigma ID, primary Event
      kHistPtRecSigmaPrimaryKaonPlus,           // Pt histo for kaons +, reconsructed tracks, sigma ID, primary Event
      kHistPtRecSigmaPrimaryProtonPlus,         // Pt histo for protons +, reconstructed tracks, sigma ID, primary Event
      kHistPtRecSigmaPrimaryPionMinus,          // Pt histo for pions -, reconstructed tracks, sigma ID, primary Event
      kHistPtRecSigmaPrimaryKaonMinus,          // Pt histo for kaons -, reconstructed tracks, sigma ID, primary Event
      kHistPtRecSigmaPrimaryProtonMinus,        // Pt histo for protons -, reconstructed tracks, sigma ID, primary Event
            
      // 6 Pt Reconstructed Sigma Secondary Material
      kHistPtRecSigmaSecondaryMaterialPionPlus,         // Pt histo for pions +, reconstructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryMaterialKaonPlus,         // Pt histo for kaons +, reconsructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryMaterialProtonPlus,       // Pt histo for protons +, reconstructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryMaterialPionMinus,        // Pt histo for pions -, reconstructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryMaterialKaonMinus,        // Pt histo for kaons -, reconstructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryMaterialProtonMinus,      // Pt histo for protons -, reconstructed tracks, sigma ID, secondary Event

      // 6 Pt Reconstructed Sigma Secondary WeakDecay
      kHistPtRecSigmaSecondaryWeakDecayPionPlus,         // Pt histo for pions +, reconstructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryWeakDecayKaonPlus,         // Pt histo for kaons +, reconsructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryWeakDecayProtonPlus,       // Pt histo for protons +, reconstructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryWeakDecayPionMinus,        // Pt histo for pions -, reconstructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryWeakDecayKaonMinus,        // Pt histo for kaons -, reconstructed tracks, sigma ID, secondary Event
      kHistPtRecSigmaSecondaryWeakDecayProtonMinus,      // Pt histo for protons -, reconstructed tracks, sigma ID, secondary Event

      // 6 Pt Reconstructed True Primary
      kHistPtRecTruePrimaryPionPlus,            // Pt histo for pions +, reconstructed tracks, true ID, primary event
      kHistPtRecTruePrimaryKaonPlus,            // Pt histo for kaons +, reconsructed tracks, true ID, primary event
      kHistPtRecTruePrimaryProtonPlus,          // Pt histo for protons +, reconstructed tracks, true ID, primary event
      kHistPtRecTruePrimaryPionMinus,           // Pt histo for pions -, reconstructed tracks, true ID, primary event
      kHistPtRecTruePrimaryKaonMinus,           // Pt histo for kaons -, reconstructed tracks, true ID, primary event
      kHistPtRecTruePrimaryProtonMinus,         // Pt histo for protons -, reconstructed tracks, true ID, primary event
      kHistPtRecTruePrimaryMuonPlus,            // Pt histo for muons +, reconstructed tracks, true ID, primary event
      kHistPtRecTruePrimaryMuonMinus,            // Pt histo for muons +, reconstructed tracks, true ID, primary event
      kNPtRecHist = kHistPtRecTruePrimaryMuonMinus,                    // Number of ptRec-likehistos histos
      
      // Rest
      kHistPtRec,                               // Pt histo for all particles, reconstructed tracks
      kHistPtRecPrimaryAll,                               // Pt histo for all particles, reconstructed tracks
      kNPtRecAllChHist = kHistPtRecPrimaryAll,                    // Number of ptRec-likehistos histos - no PID
      
      kHistPIDTPC,                              // Particle Identification histo
      kHistPIDTOF,                              
      kHistPIDTPCPion,                              
      kHistPIDTPCKaon,                              
      kHistPIDTPCProton,                              
      kHistPIDTPCPionRec,                              
      kHistPIDTPCKaonRec,                              
      kHistPIDTPCProtonRec,                              
      kNHistPID =kHistPIDTPCProtonRec,                           
      
      kHistNSigPionTPC,                              
      kHistNSigKaonTPC,                              
      kHistNSigProtonTPC,                       // NSigma separation plot    
      kHistNSigPionPtTPC,                              
      kHistNSigKaonPtTPC,                              
      kHistNSigProtonPtTPC,                              
      
      kHistNSigPionTOF,                              
      kHistNSigKaonTOF,                              
      kHistNSigProtonTOF,                              
      kHistNSigPionPtTOF,                              
      kHistNSigKaonPtTOF,                              
      kHistNSigProtonPtTOF,                              
     
      kHistNSigPionTPCTOF,                              
      kHistNSigKaonTPCTOF,                              
      kHistNSigProtonTPCTOF,                             
      kHistNSigPionPtTPCTOF,
      kHistNSigKaonPtTPCTOF,                              
      kHistNSigProtonPtTPCTOF,                              
      kNHistNSig=kHistNSigProtonPtTPCTOF,    
      
      kHistGenMulvsRawMul,
                                
      kNHist,                                   // Total number of histos
   };  // Type of events plotted in Pt Histogram

}
