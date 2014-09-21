#include <gtest/gtest.h>
#include <Maze/maze.h>
#include <Maze/maze_generator.h>
//#include <MazeExplorer/Experiment/EnviromentVariables.h>
#include <set>

namespace constants
{
	const unsigned int size_x(5);
	const unsigned int size_y(5);
	const EMazeTypes maze_type(E_MT_KRUSKAL);
	const std::string maze_file_path("");
};

class ut_maze_kruskal_test : public ::testing::Test
{
public:
	boost::shared_ptr<maze_interface> uut;

	ut_maze_kruskal_test()
	{
		maze_generator mazeGen;
		uut = mazeGen.generate_maze(constants::size_x, constants::size_y, constants::maze_type);

		//std::ifstream data("maze.dat");
		//if (data.open()) {
		//	uut.saveMaze(&out);
		//}
	}

};

TEST_F(ut_maze_kruskal_test, maze_sizes)
{
	EXPECT_EQ(uut->get_size_x(), constants::size_x);
	EXPECT_EQ(uut->get_size_y(), constants::size_y);
}

TEST_F(ut_maze_kruskal_test, test_maze_edges)
{
	for (int i = 0; i < uut->get_size_x(); i++)
	{
		//location from topest row
		boost::optional<location> loc = uut->get_location(i, 0);
		if (i == 0)
			EXPECT_TRUE(loc->is_wall(WEST_DIR));
		if (i == uut->get_size_y() - 1)
			EXPECT_TRUE(loc->is_wall(EAST_DIR));
		EXPECT_TRUE(loc->is_wall(NORTH_DIR));

		//location from lowest row
		loc = uut->get_location(i, uut->get_size_y() - 1);
		if (i == 0)
			EXPECT_TRUE(loc->is_wall(WEST_DIR));
		if (i == uut->get_size_y() - 1)
			EXPECT_TRUE(loc->is_wall(EAST_DIR));
		EXPECT_TRUE(loc->is_wall(SOUTH_DIR));
	}
}

TEST_F(ut_maze_kruskal_test, test_maze_locations_integrity)
{
	for (int x = 0; x < uut->get_size_x(); x++)
		for (int y = 0; y < uut->get_size_y(); y++)
		{
			boost::optional<location> test_loc = uut->get_location(x, y);
			boost::optional<location> neigh_loc;
			if (x>0)
			{
				neigh_loc = uut->get_location(x-1, y);
				ASSERT_EQ(test_loc->is_wall(WEST_DIR), neigh_loc->is_wall(EAST_DIR));
			}
			if (x<(uut->get_size_x()-1))
			{
				neigh_loc = uut->get_location(x + 1, y);
				ASSERT_EQ(test_loc->is_wall(EAST_DIR), neigh_loc->is_wall(WEST_DIR));
			}
			if (y>0)
			{
				neigh_loc = uut->get_location(x, y-1);
				ASSERT_EQ(test_loc->is_wall(NORTH_DIR), neigh_loc->is_wall(SOUTH_DIR));
			}
			if (y<(uut->get_size_y() - 1))
			{
				neigh_loc = uut->get_location(x, y+1);
				ASSERT_EQ(test_loc->is_wall(SOUTH_DIR), neigh_loc->is_wall(NORTH_DIR));
			}
		}
}

TEST_F(ut_maze_kruskal_test, test_maze_locations_connections)
{
	unsigned int nodes_count = uut->get_size_x()*uut->get_size_y();
	int x, y;
	boost::optional<location> test_loc;

	std::set< std::pair<int, int> > sToBeVisitedCoords;
	std::set< std::pair<int, int> > sVisitedCoords;

	std::pair<int, int> coords;
	sToBeVisitedCoords.insert(std::make_pair(0, 0));
	do
	{
		std::set< std::pair<int, int> >::iterator iterCoord = sToBeVisitedCoords.begin();
		coords = *iterCoord;
		sToBeVisitedCoords.erase(iterCoord);
		if (sVisitedCoords.count(coords))
			continue;

		x = coords.first;
		y = coords.second;
		test_loc = uut->get_location(x, y);
		ASSERT_TRUE(test_loc);
		if (!test_loc->is_wall(NORTH_DIR))
			sToBeVisitedCoords.insert(std::make_pair(x, y - 1));
		if (!test_loc->is_wall(SOUTH_DIR))
			sToBeVisitedCoords.insert(std::make_pair(x, y + 1));
		if (!test_loc->is_wall(WEST_DIR))
			sToBeVisitedCoords.insert(std::make_pair(x - 1, y));
		if (!test_loc->is_wall(EAST_DIR))
			sToBeVisitedCoords.insert(std::make_pair(x + 1, y));
		sVisitedCoords.insert(coords);
	} while (sVisitedCoords.size()<nodes_count && sToBeVisitedCoords.size()>0);
	ASSERT_EQ(sVisitedCoords.size(), nodes_count);
}
