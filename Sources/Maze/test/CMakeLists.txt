
project(ut_maze)
SetWindowsPolicies()

include_directories(${gmock_SOURCE_DIR}/include
                    ${gtest_SOURCE_DIR}/include
                    ${Maze_data_SOURCE_DIR} 
                    ${RLME_include_SOURCE_DIR}/Tools)

SET ( SOURCES_TESTS
	ut_maze_kruskal_test.cpp
	ut_maze_prim_test.cpp 
	ut_maze_recursive_test.cpp 
	ut_maze_loader_test.cpp
	)

SET ( SOURCES_MAIN
      main.cpp
      ${RLME_include_SOURCE_DIR}/Tools/TestRunner.h
    )

add_executable(ut_maze ${SOURCES_MAIN} ${SOURCES_TESTS}
	maze_data.xml maze_data.json	
)
target_link_libraries(ut_maze ${QT_LIBRARIES} maze_lib gmock gtest tools_lib
	)
qt5_use_modules(ut_maze Core Test)

ADD_TEST(ut_maze ut_maze)
	add_custom_command(TARGET ut_maze POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E make_directory ${ut_maze_BINARY_DIR}/logs
		COMMAND ${CMAKE_COMMAND} -E copy ${MazeExplorer_SOURCE_DIR}/log4cpp.properties ${ut_maze_BINARY_DIR}/logs/log4cpp.properties
		COMMAND ${CMAKE_COMMAND} -E copy ${ut_maze_SOURCE_DIR}/maze_data.xml ${ut_maze_BINARY_DIR}/maze_data.xml
		COMMAND ${CMAKE_COMMAND} -E copy ${ut_maze_SOURCE_DIR}/maze_data.json ${ut_maze_BINARY_DIR}/maze_data.json
		)

