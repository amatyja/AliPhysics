# **************************************************************************
# * Copyright(c) 1998-2014, ALICE Experiment at CERN, All rights reserved. *
# *                                                                        *
# * Author: The ALICE Off-line Project.                                    *
# * Contributors are mentioned in the code where appropriate.              *
# *                                                                        *
# * Permission to use, copy, modify and distribute this software and its   *
# * documentation strictly for non-commercial purposes is hereby granted   *
# * without fee, provided that the above copyright notice appears in all   *
# * copies and that both the copyright notice and this permission notice   *
# * appear in the supporting documentation. The authors make no claims     *
# * about the suitability of this software for any purpose. It is          *
# * provided "as is" without express or implied warranty.                  *
# **************************************************************************/

#Module
set(MODULE PWGCaloTrackCorrBase)
add_definitions(-D_MODULE_="${MODULE}")

# Module include folder
include_directories(${AliPhysics_SOURCE_DIR}/PWG/CaloTrackCorrBase)

# Additional includes - alphabetical order except ROOT
include_directories(${ROOT_INCLUDE_DIRS}
                    ${AliPhysics_SOURCE_DIR}/OADB
                    ${AliPhysics_SOURCE_DIR}/OADB/COMMON/MULTIPLICITY
                    ${AliPhysics_SOURCE_DIR}/PWG/EMCAL/EMCALbase
		    ${AliPhysics_SOURCE_DIR}/PWG/Tools
		    ${AliPhysics_SOURCE_DIR}/PWG/Tools/yaml-cpp
                   )

# Sources - alphabetical order
set(SRCS
  AliNeutralMesonSelection.cxx 
  AliFiducialCut.cxx 
  AliCaloPID.cxx 
  AliMCAnalysisUtils.cxx 
  AliIsolationCut.cxx 
  AliAnaScale.cxx 
  AliCaloTrackParticle.cxx 
  AliCaloTrackParticleCorrelation.cxx 
  AliCaloTrackReader.cxx 
  AliCaloTrackESDReader.cxx 
  AliCaloTrackAODReader.cxx 
  AliCaloTrackMCReader.cxx 
  AliCalorimeterUtils.cxx 
  AliAnalysisTaskCounter.cxx 
  AliAnaCaloTrackCorrMaker.cxx
  AliAnaCaloTrackCorrBaseClass.cxx
  AliAnalysisTaskCaloTrackCorrelation.cxx
  AliAnalysisTaskCaloTrackCorrelationM.cxx
  AliHistogramRanges.cxx
  AliAnaWeights.cxx
  )

# Headers from sources
string(REPLACE ".cxx" ".h" HDRS "${SRCS}")

# Generate the dictionary
# It will create G_ARG1.cxx and G_ARG1.h / ARG1 = function first argument
get_directory_property(incdirs INCLUDE_DIRECTORIES)
generate_dictionary("${MODULE}" "${MODULE}LinkDef.h" "${HDRS}" "${incdirs}")

# Add a shared library
add_library_tested(${MODULE} SHARED  ${SRCS} G__${MODULE}.cxx)

# Generate the ROOT map
# Dependencies
set(LIBDEPS ANALYSISalice EMCALUtils PWGEMCALbase PHOSUtils)
generate_rootmap("${MODULE}" "${LIBDEPS}" "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}LinkDef.h")

# Generate a PARfile target for this library
add_target_parfile(${MODULE} "${SRCS}" "${HDRS}" "${MODULE}LinkDef.h" "${LIBDEPS}")

# Linking the library
target_link_libraries(${MODULE} ${LIBDEPS})

# Public include folders that will be propagated to the dependencies
target_include_directories(${MODULE} PUBLIC ${incdirs})

# System dependent: Modify the way the library is build
if(${CMAKE_SYSTEM} MATCHES Darwin)
    set_target_properties(${MODULE} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
endif(${CMAKE_SYSTEM} MATCHES Darwin)

# Installation
install(TARGETS ${MODULE} 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
install(FILES ${HDRS} DESTINATION include)
