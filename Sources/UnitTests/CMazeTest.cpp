#include "CMazeTest.h"
#include <Maze/CMazeGenerator.h>
#include <MazeExplorer/Experiment/EnviromentVariables.h>
#include <set>

void CMazeTest::initTestCase()
{
	CMazeGenerator mazeGen;
	m_iSizeX=10;
	m_iSizeY=10;
	m_Maze = mazeGen.GenerateMaze(m_iSizeX,m_iSizeY,E_MT_KRUSKAL);

	QFile data("maze.dat");
	if (data.open(QFile::WriteOnly | QFile::Truncate)) {
		QTextStream out(&data);
		m_Maze.saveMaze(&out);
	}
}
void CMazeTest::testMazeParams()
{
    QCOMPARE(m_Maze.getXSize(),m_iSizeX);
    QCOMPARE(m_Maze.getYSize(),m_iSizeY);
}
void CMazeTest::testMazeEdges()
{
	for(int iX=0; iX<m_Maze.getXSize(); iX++)
	{
		//location from topest row
		const CLocation & loc1 = m_Maze.getLocation(iX,0);
		if (iX==0)
			QVERIFY(loc1.left);
		if (iX==m_Maze.getXSize()-1)
			QVERIFY(loc1.right);
		QVERIFY(loc1.up);

		//location from lowest row
		const CLocation & loc2 = m_Maze.getLocation(iX,m_Maze.getYSize()-1);
		if (iX==0)
			QVERIFY(loc2.left);
		if (iX==m_Maze.getXSize()-1)
			QVERIFY(loc2.right);
		QVERIFY(loc2.down);
	}
}
void CMazeTest::testMazeConnections()
{
	unsigned int iNodesCount=m_Maze.getXSize()*m_Maze.getYSize();
	int iX,iY;;
	CLocation loc;

	std::set< std::pair<int, int> > sToBeVisitedCoords;
	std::set< std::pair<int, int> > sVisitedCoords;

	std::pair<int,int> pCoords;
	sToBeVisitedCoords.insert(std::make_pair(0,0));
	do
	{
		std::set< std::pair<int, int> >::iterator iterCoord = sToBeVisitedCoords.begin();
		pCoords = *iterCoord;
		sToBeVisitedCoords.erase(iterCoord);
		if (sVisitedCoords.count(pCoords))
			continue;

		iX = pCoords.first;
		iY = pCoords.second;
		QVERIFY(m_Maze.getLocation(iX,iY,loc));
		if (false==loc.up)
			sToBeVisitedCoords.insert(std::make_pair(iX,iY-1));
		if (false==loc.down)
			sToBeVisitedCoords.insert(std::make_pair(iX,iY+1));
		if (false==loc.left)
			sToBeVisitedCoords.insert(std::make_pair(iX-1,iY));
		if (false==loc.right)
			sToBeVisitedCoords.insert(std::make_pair(iX+1,iY));
		sVisitedCoords.insert(pCoords);
	}
	while(sVisitedCoords.size()<iNodesCount && sToBeVisitedCoords.size()>0);
	QCOMPARE(sVisitedCoords.size(),iNodesCount);
}
