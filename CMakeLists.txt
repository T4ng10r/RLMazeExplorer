cmake_minimum_required(VERSION 2.6)

project(RL_MazeExplorer)

cmake_policy(VERSION 2.8.12)
IF (WIN32)
cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0043 NEW)
ENDIF()

enable_testing()
include(${PROJECT_SOURCE_DIR}/CMake/functions.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/options.cmake)
include_directories(${Boost_INCLUDE_DIR})
set_c11_flags()

add_subdirectory(include)
add_subdirectory(Sources)
