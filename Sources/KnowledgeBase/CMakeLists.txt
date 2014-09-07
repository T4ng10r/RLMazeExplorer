cmake_minimum_required(VERSION 2.6)

include_directories (${RL_MazeExplorer_SOURCE_DIR}/include/KnowledgeBase)
include_directories (${MazeExplorer_SOURCE_DIR})

  ####################
  SET ( KB_HEADERS
    ${RLME_include_SOURCE_DIR}/KnowledgeBase/CKBTree.h
    ${RLME_include_SOURCE_DIR}/KnowledgeBase/CKBLocationData.h 
    ${RLME_include_SOURCE_DIR}/KnowledgeBase/CKnowlegdeBase.h
    ${RLME_include_SOURCE_DIR}/KnowledgeBase/CExplorationResult.h 
    )

  SET ( KB_SOURCES
      CKBTree.cpp
	)

  add_library(KBLib ${KB_SOURCES} ${KB_HEADERS} )

