cmake_minimum_required(VERSION 2.8)

project(RL_MazeExplorer_Libs)

include_directories (${RL_MazeExplorer_SOURCE_DIR}/include)

add_subdirectory(gmock)
add_subdirectory(log4cpp)
add_subdirectory(KnowledgeBase)
add_subdirectory(Maze)
add_subdirectory(Tools)
#add_subdirectory(UnitTests)
#add_subdirectory(MazeExplorer)
