#include <gtest/gtest.h>
#include <Maze/maze.h>
#include <string>

namespace constants
{
	const std::string file_path("maze_data.xml");
	const unsigned int size_x(10);
	const unsigned int size_y(10);
	const EMazeTypes maze_type(E_MT_PRIM);
};

class ut_maze_loader_test : public ::testing::Test
{
public:
	maze maze_data;

	ut_maze_loader_test()
	{
	}

};

TEST_F(ut_maze_loader_test, maze_sizes)
{
	maze_data.load_maze(constants::file_path);
	EXPECT_EQ(maze_data.get_size_x(), constants::size_x);
	EXPECT_EQ(maze_data.get_size_y(), constants::size_y);
}

