
include_directories(${gmock_SOURCE_DIR}/include
                    ${gtest_SOURCE_DIR}/include
                    ${Maze_data_SOURCE_DIR} 
                    ${RLME_include_SOURCE_DIR}/Tools)

SET ( SOURCES_TESTS
	maze_test.cpp
	)

SET ( SOURCES_MAIN
      main.cpp
      ${RLME_include_SOURCE_DIR}/Tools/TestRunner.h
    )

add_executable(ut_maze ${SOURCES_MAIN} ${SOURCES_TESTS}
)
target_link_libraries(ut_maze ${QT_LIBRARIES} maze_lib gmock gtest tools_lib)
qt5_use_modules(ut_maze Core Test)

ADD_TEST(ut_maze ut_maze)
