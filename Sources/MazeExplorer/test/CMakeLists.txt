cmake_minimum_required(VERSION 2.6)

project(UnitTest)

include_directories (${RL_MazeExplorer_SOURCE_DIR}/include)
include_directories (${RL_MazeExplorer_SOURCE_DIR}/Sources)
include_directories (${RL_MazeExplorer_SOURCE_DIR}/Sources/MazeExplorer )

#dodajemy dane dotyczace QT - sciezki, biblioteki
find_package(Qt4 COMPONENTS QtCore QtGui QtTest REQUIRED )
include(${QT_USE_FILE})

####################
SET ( SOURCES_TEST_DATA
      ${UnitTest_SOURCE_DIR}/CMazeTest.cpp
      ${UnitTest_SOURCE_DIR}/CMazeTest.h
      ${UnitTest_SOURCE_DIR}/CKnowledgeBaseTest.cpp
      ${UnitTest_SOURCE_DIR}/CKnowledgeBaseTest.h
      ${UnitTest_SOURCE_DIR}/CKBLocationDataTest.cpp 
      ${UnitTest_SOURCE_DIR}/CKBLocationDataTest.h
      ${UnitTest_SOURCE_DIR}/CKBStateDataTest.cpp
      ${UnitTest_SOURCE_DIR}/CKBStateDataTest.h
      ${UnitTest_SOURCE_DIR}/CKBTreeDateTest.cpp
      ${UnitTest_SOURCE_DIR}/CKBTreeDateTest.h
	  )

SET ( SOURCES_MAIN
      main.cpp
    )

SET ( SOURCES_TEST_MOC 
      ${UnitTest_SOURCE_DIR}/CMazeTest.h
      ${UnitTest_SOURCE_DIR}/CKnowledgeBaseTest.h
      ${UnitTest_SOURCE_DIR}/CKBStateDataTest.h
      ${UnitTest_SOURCE_DIR}/CKBTreeDateTest.h
      ${UnitTest_SOURCE_DIR}/CKBLocationDataTest.h
    )

qt_wrap_cpp(UnitTest SOURCES_MOC ${SOURCES_TEST_MOC})
SOURCE_GROUP(moc FILES ${SOURCES_MOC})

SOURCE_GROUP(TestCases FILES ${SOURCES_TEST_DATA})
    
add_executable(UnitTest ${SOURCES_MAIN} ${SOURCES_MOC} 
					${SOURCES_TEST_DATA}
)
target_link_libraries(UnitTest ${QT_LIBRARIES} MazeLib KBLib log4qt_lib)

add_test(UnitTest UnitTest)

