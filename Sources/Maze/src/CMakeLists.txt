cmake_minimum_required(VERSION 2.8)

project(Maze_data)

cmake_policy(SET CMP0020 NEW)

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Xml)
include_directories($ENV{QTDIR} 
       ${Qt5Widgets_INCLUDE_DIRS} 
			 ${Qt5Core_INCLUDE_DIRS} )

include_directories (${RL_MazeExplorer_SOURCE_DIR}/include/Maze
                     ${MazeExplorer_SOURCE_DIR}
                     ${RL_MazeExplorer_Libs_SOURCE_DIR})

  ####################
  SET ( MAZE_HEADERS
    ${RLME_include_SOURCE_DIR}/Maze/location.h 
    ${RLME_include_SOURCE_DIR}/Maze/maze.h
    ${RLME_include_SOURCE_DIR}/Maze/maze_generator.h
    ${RLME_include_SOURCE_DIR}/Maze/maze_settings.h
    )

  SET ( SOURCES_MAZE
		maze.cpp
		maze_generator.cpp 
	)

add_library(maze_lib ${SOURCES_MAZE} ${MAZE_HEADERS} )
