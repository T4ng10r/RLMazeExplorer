cmake_minimum_required(VERSION 2.6)

project(RL_MazeExplorer)

enable_testing()
include(${PROJECT_SOURCE_DIR}/CMake/functions.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/options.cmake)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(include)
add_subdirectory(Sources)
