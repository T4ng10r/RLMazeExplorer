#include <QtTest/QtTest>
#include <Maze/CMaze.h>

class CMazeTest : public QObject
{
    Q_OBJECT
public:
    CMaze m_Maze;
	int m_iSizeX;
	int m_iSizeY;
private slots:
	void initTestCase();
    void testMazeParams();
    void testMazeEdges();
	void testMazeConnections();
};

