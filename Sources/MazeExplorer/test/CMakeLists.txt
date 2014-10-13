cmake_minimum_required(VERSION 2.6)

project(UnitTest)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
ADD_DEFINITIONS( "-DQT_NO_KEYWORDS" )
SetWindowsPolicies()

include_directories (${RLME_include_SOURCE_DIR}
                     ${RL_MazeExplorer_SOURCE_DIR}/Sources
                     ${MazeExplorer_SOURCE_DIR}
                     $ENV{QTDIR}
                     ${Qt5Widgets_INCLUDE_DIRS}
                     ${Qt5Core_INCLUDE_DIRS}
                     ${Qt5Test_INCLUDE_DIRS})

####################
SET ( SOURCES_TEST_DATA
      ${UnitTest_SOURCE_DIR}/TestRunner.h
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
      main.cpp )

SOURCE_GROUP(TestCases FILES ${SOURCES_TEST_DATA})
    
add_executable(ut_maze_explorer ${SOURCES_MAIN} ${SOURCES_MOC} 
					${SOURCES_TEST_DATA}
)
target_link_libraries(ut_maze_explorer ${QT_LIBRARIES} maze_lib  KBLib log4cpp)
qt5_use_modules(ut_maze_explorer Widgets Core Test)

add_test(UnitTest UnitTest)
