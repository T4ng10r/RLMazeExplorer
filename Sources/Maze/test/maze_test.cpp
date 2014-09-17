#include <gtest/gtest.h>
#include <Maze/maze.h>
#include <Maze/maze_generator.h>
//#include <MazeExplorer/Experiment/EnviromentVariables.h>
#include <set>

namespace constants
{
	const unsigned int size_x(10);
	const unsigned int size_y(10);
	const EMazeTypes maze_type(E_MT_KRUSKAL);
	const std::string maze_file_path("");
};

class ut_maze_test : public ::testing::Test
{
public:
	std::shared_ptr<maze_interface> uut;

	ut_maze_test()
	{
		maze_generator mazeGen;
		uut = mazeGen.generate_maze(constants::size_x, constants::size_y, constants::maze_type);

		//std::ifstream data("maze.dat");
		//if (data.open()) {
		//	uut.saveMaze(&out);
		//}
	}

};

TEST_F(ut_maze_test, maze_sizes)
{
	EXPECT_EQ(uut->get_size_x(), constants::size_x);
	EXPECT_EQ(uut->get_size_y(), constants::size_y);
}

TEST_F(ut_maze_test, test_maze_edges)
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

/*
void CMazeTest::testMazeConnections()
{
	unsigned int iNodesCount = m_Maze.getXSize()*m_Maze.getYSize();
	int iX, iY;;
	CLocation loc;

	std::set< std::pair<int, int> > sToBeVisitedCoords;
	std::set< std::pair<int, int> > sVisitedCoords;

	std::pair<int, int> pCoords;
	sToBeVisitedCoords.insert(std::make_pair(0, 0));
	do
	{
		std::set< std::pair<int, int> >::iterator iterCoord = sToBeVisitedCoords.begin();
		pCoords = *iterCoord;
		sToBeVisitedCoords.erase(iterCoord);
		if (sVisitedCoords.count(pCoords))
			continue;

		iX = pCoords.first;
		iY = pCoords.second;
		QVERIFY(m_Maze.getLocation(iX, iY, loc));
		if (false == loc.up)
			sToBeVisitedCoords.insert(std::make_pair(iX, iY - 1));
		if (false == loc.down)
			sToBeVisitedCoords.insert(std::make_pair(iX, iY + 1));
		if (false == loc.left)
			sToBeVisitedCoords.insert(std::make_pair(iX - 1, iY));
		if (false == loc.right)
			sToBeVisitedCoords.insert(std::make_pair(iX + 1, iY));
		sVisitedCoords.insert(pCoords);
	} while (sVisitedCoords.size()<iNodesCount && sToBeVisitedCoords.size()>0);
	QCOMPARE(sVisitedCoords.size(), iNodesCount);
}
*/