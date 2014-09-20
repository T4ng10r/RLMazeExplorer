cmake_minimum_required(VERSION 2.8)

project(MazeExplorer)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

  #to get log4qt folder
include_directories (${RLME_include_SOURCE_DIR}
                     ${RL_MazeExplorer_Libs_SOURCE_DIR}
                     ${MazeExplorer_SOURCE_DIR}
                     ${Boost_INCLUDE_DIR})

#dodajemy dane dotyczace QT - sciezki, biblioteki
include_directories($ENV{QTDIR} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS})
ADD_DEFINITIONS( "-DQT_NO_KEYWORDS" )
GatheringFiles(${CMAKE_CURRENT_SOURCE_DIR} "cpp;h;;c;cc")

SET(TMP_FILES ${TMP_FILES} log4cpp.properties 
		${SOURCES_TOOLS} )

add_executable(MazeExplorer ${TMP_FILES} main.cpp  )
target_link_libraries(MazeExplorer ${Boost_LIBRARIES} tools_lib log4cpp maze_lib KBLib)
qt5_use_modules(MazeExplorer Widgets Core)

