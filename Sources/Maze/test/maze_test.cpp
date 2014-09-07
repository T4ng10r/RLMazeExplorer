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
	maze uut;

	ut_maze_test()
	{
		maze_generator mazeGen;
		uut = mazeGen.GenerateMaze(constants::size_x, constants::size_y, constants::maze_type);

		//std::ifstream data("maze.dat");
		//if (data.open()) {
		//	uut.saveMaze(&out);
		//}
	}

};

TEST_F(ut_maze_test, maze_sizes)
{
	EXPECT_EQ(uut.getXSize(), constants::size_x);
	EXPECT_EQ(uut.getYSize(), constants::size_y);
}

TEST_F(ut_maze_test, test_maze_edges)
{
	for (int i = 0; i < uut.getXSize(); i++)
	{
		//location from topest row
		const location & loc1 = uut.get_location(i, 0);
		if (i == 0)
			EXPECT_TRUE(loc1.left);
		if (i == uut.getXSize() - 1)
			EXPECT_TRUE(loc1.right);
		EXPECT_TRUE(loc1.up);

		//location from lowest row
		const location & loc2 = uut.get_location(i, uut.getYSize() - 1);
		if (i == 0)
			EXPECT_TRUE(loc2.left);
		if (i == uut.getXSize() - 1)
			EXPECT_TRUE(loc2.right);
		EXPECT_TRUE(loc2.down);
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