#include <gtest/gtest.h>
#include <Maze/maze.h>
#include <string>

namespace constants
{
	const std::string file_path("maze_data.xml");
	const std::string file_path_json("maze_data_save.json");
	const unsigned int size_x(5);
	const unsigned int size_y(5);
	const EMazeTypes maze_type(E_MT_PRIM);
};

class ut_maze_saver_test : public ::testing::Test
{
public:
	maze golden_maze;
	maze maze_data;

	ut_maze_saver_test()
	{
		init_maze();
	}
	void init_maze()
	{
		golden_maze.size_x = constants::size_x;
		golden_maze.size_y = constants::size_y;
		golden_maze.type = constants::maze_type;
		golden_maze.resize();
		golden_maze.preset_maze_edges();

		golden_maze.get_xlocation(0, 0) = location(true, false, true, true);
		golden_maze.get_xlocation(1, 0) = location(true, true, true, false);
		golden_maze.get_xlocation(2, 0) = location(false, true, true, true);
		golden_maze.get_xlocation(3, 0) = location(true, true, true, true);
		golden_maze.get_xlocation(4, 0) = location(true, true, false, true);
	}
};

TEST_F(ut_maze_saver_test, maze_sizes)
{
	golden_maze.save_maze(constants::file_path_json);
	maze_data.load_maze(constants::file_path_json);
	ASSERT_EQ(maze_data.get_size_x(), constants::size_x);
	ASSERT_EQ(maze_data.get_size_y(), constants::size_y);
	ASSERT_EQ(maze_data.type, constants::maze_type);
}

TEST_F(ut_maze_saver_test, maze_first_row)
{
	golden_maze.save_maze(constants::file_path_json);
	maze_data.load_maze(constants::file_path_json);
	EXPECT_EQ(golden_maze.get_location(0, 0).get(), location(true, false, true, true));
	EXPECT_EQ(golden_maze.get_location(1, 0).get(), location(true, true, true, false));
	EXPECT_EQ(golden_maze.get_location(2, 0).get(), location(false, true, true, true));
	EXPECT_EQ(golden_maze.get_location(3, 0).get(), location(true, true, true, true));
	EXPECT_EQ(golden_maze.get_location(4, 0).get(), location(true, true, false, true));
}
