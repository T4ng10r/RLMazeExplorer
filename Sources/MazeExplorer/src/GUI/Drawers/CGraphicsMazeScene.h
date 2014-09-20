#ifndef C_GRAPHICS_MAZE_SCENE_H
#define C_GRAPHICS_MAZE_SCENE_H
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include <QPoint>
#include <map>
#include <Gui/Drawers/CGraphicsMazeLocation.h>
#include <Data/Experiment/CExperimentSettings.h>
#include <set>
#include <Maze/maze_interface.h>
#include <boost/shared_ptr.hpp>

class CMaze;

typedef std::map< std::pair< int, int>, CGraphicsMazeLocation *>	MapCoords2Location;

//return true if p2 is bigger the p1
struct sort_QPoint_set
{
	bool operator()(const QPoint &p1, const QPoint &p2) const
	//bool operator <(const QPoint &p1, const QPoint &p2)
	{
		if (p1.x()<p2.x())
			return true;
		else if (p1.x()==p2.x() && p1.y()<p2.y())
			return true;
		return false;
	}

};

typedef std::set< QPoint, sort_QPoint_set>		PointSet;

class CGraphicsMazeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CGraphicsMazeScene();
	void setMaze(boost::shared_ptr<maze_interface> maze_data);

public Q_SLOTS:
	void onExperimentSettingsChanged(const CExperimentSettings & xExperimentSettings);

protected:

	void reset();
    MapCoords2Location m_mCords2Locations;
    MapCoords2Location::iterator iterCords2LocStart;
    MapCoords2Location::iterator iterCords2LocEnd;

    QGraphicsWidget *		m_ptrMainItem;
    QGraphicsGridLayout	*	m_ptrMainGridLayout;

	std::pair< int, int> 	m_pEmptyPoint;
	std::pair< int, int> 	m_pStartPoint;
	PointSet				m_sEndPoints;

};

#endif
