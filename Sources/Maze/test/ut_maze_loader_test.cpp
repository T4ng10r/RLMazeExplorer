#include <gtest/gtest.h>
#include <Maze/maze.h>
#include <string>

namespace constants
{
	const std::string file_path("maze_data.xml");
	const std::string file_path_json("maze_data.json");
	const unsigned int size_x(5);
	const unsigned int size_y(5);
	const EMazeTypes maze_type(E_MT_PRIM);
};

class ut_maze_loader_test : public ::testing::Test
{
public:
	maze golden_maze;
	maze maze_data;

	ut_maze_loader_test()
	{
	}
	void init_maze()
	{
		golden_maze.size_x = constants::size_x;
		golden_maze.size_y = constants::size_y;
		golden_maze.type = constants::maze_type;
		golden_maze.preset_maze_edges();
	}

};

TEST_F(ut_maze_loader_test, maze_sizes)
{
	maze_data.load_maze(constants::file_path_json);
	EXPECT_EQ(maze_data.get_size_x(), constants::size_x);
	EXPECT_EQ(maze_data.get_size_y(), constants::size_y);
	EXPECT_EQ(maze_data.type, constants::maze_type);
}

TEST_F(ut_maze_loader_test, maze_row_locations)
{
	maze_data.load_maze(constants::file_path_json);
	ASSERT_EQ(maze_data.get_location(0, 0).get(), location(true, false, false, true));
	ASSERT_EQ(maze_data.get_location(1, 0).get(), location(true, false, false, true));
	ASSERT_EQ(maze_data.get_location(2, 0).get(), location(true, true, false, false));
	ASSERT_EQ(maze_data.get_location(3, 0).get(), location(true, false, false, true));
	ASSERT_EQ(maze_data.get_location(4, 0).get(), location(true, true, false, true));
}

TEST_F(ut_maze_loader_test, maze_two_row_locations)
{
	maze_data.load_maze(constants::file_path_json);
	ASSERT_EQ(maze_data.get_location(0, 1).get(), location(true, true, false, true));
	ASSERT_EQ(maze_data.get_location(1, 1).get(), location(false, false, true, true));
	ASSERT_EQ(maze_data.get_location(2, 1).get(), location(true, true, false, false));
	ASSERT_EQ(maze_data.get_location(3, 1).get(), location(true, false, true, false));
	ASSERT_EQ(maze_data.get_location(4, 1).get(), location(false, true, true, false));
}

TEST_F(ut_maze_loader_test, maze_three_row_locations)
{
	maze_data.load_maze(constants::file_path_json);
	ASSERT_EQ(maze_data.get_location(0, 2).get(), location(true, false, true, true));
	ASSERT_EQ(maze_data.get_location(1, 2).get(), location(true, true, true, false));
	ASSERT_EQ(maze_data.get_location(2, 2).get(), location(false, true, true, true));
	ASSERT_EQ(maze_data.get_location(3, 2).get(), location(true, true, true, true));
	ASSERT_EQ(maze_data.get_location(4, 2).get(), location(true, true, false, true));
}
