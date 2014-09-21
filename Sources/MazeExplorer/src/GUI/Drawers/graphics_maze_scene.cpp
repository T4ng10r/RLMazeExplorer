#include "graphics_maze_scene.h"
#include <Tools/loggers.h>
#include <QGraphicsView>
#include <boost/shared_ptr.hpp>
#include <Gui/Drawers/CGraphicsMazeLocation.h>
#include <set>
#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include <QPoint>
#include <map>

class CMaze;

typedef std::map< std::pair< int, int>, CGraphicsMazeLocation *>	MapCoords2Location;

//return true if p2 is bigger the p1
struct sort_QPoint_set
{
	bool operator()(const QPoint &p1, const QPoint &p2) const
	//bool operator <(const QPoint &p1, const QPoint &p2)
	{
		if (p1.x() < p2.x())
			return true;
		else if (p1.x() == p2.x() && p1.y() < p2.y())
			return true;
		return false;
	}

};

typedef std::set< QPoint, sort_QPoint_set>		PointSet;

class graphics_maze_scene_private
{
public:
	graphics_maze_scene_private(graphics_maze_scene * pub);

	void reset();
	graphics_maze_scene * public_;
	MapCoords2Location m_mCords2Locations;
	MapCoords2Location::iterator iterCords2LocStart;
	MapCoords2Location::iterator iterCords2LocEnd;

	QGraphicsWidget *		m_ptrMainItem;
	QGraphicsGridLayout	*	m_ptrMainGridLayout;

	std::pair< int, int> 	m_pEmptyPoint;
	std::pair< int, int> 	m_pStartPoint;
	PointSet				m_sEndPoints;
};

graphics_maze_scene_private::graphics_maze_scene_private(graphics_maze_scene * pub) : public_(pub)
{
	m_ptrMainItem = new QGraphicsWidget;
	m_ptrMainGridLayout = new QGraphicsGridLayout(m_ptrMainItem);
	m_ptrMainGridLayout->setSpacing(0);
	public_->addItem(m_ptrMainItem);

	iterCords2LocStart = m_mCords2Locations.begin();
	iterCords2LocEnd = m_mCords2Locations.end();

	m_pStartPoint = std::make_pair(-1, -1);
	m_pEmptyPoint = m_pStartPoint;
	m_sEndPoints.clear();;

}

void graphics_maze_scene_private::reset()
{
	while (m_ptrMainGridLayout->count())
		m_ptrMainGridLayout->removeAt(0);
	for (MapCoords2Location::iterator iterLocs = iterCords2LocStart; iterLocs != iterCords2LocEnd; iterLocs++)
		public_->removeItem(iterLocs->second);
	m_mCords2Locations.clear();
}


graphics_maze_scene::graphics_maze_scene() : pimpl(new graphics_maze_scene_private(this)) {}
void graphics_maze_scene::setMaze(maze_interface_type maze_data)
{
	//if (NULL == pMaze)	
	//{
	//	Log4Qt::Logger::logger("Process")->error("Trying to set Maze with NULL pointer.");
	//	return;
	//}
	//Log4Qt::Logger::logger("Process")->info("New Maze to be added.");
	pimpl->reset();
	int iSizeX = maze_data->get_size_x();
	int iSizeY = maze_data->get_size_y();
	CGraphicsMazeLocation * ptrLocation = NULL;

    for(int iX = 0; iX<iSizeX; iX++)
	{
        for(int iY = 0; iY<iSizeY; iY++)
        {
			boost::optional<location> loc = maze_data->get_location(iX, iY);
			if (!loc)
            {
				QString strError = "Can't get location for (" + QString::number(iX)+","+QString::number(iY)+")";
				//Log4Qt::Logger::logger("Process")->error(strError);
				continue;
            }
            ptrLocation = new CGraphicsMazeLocation;
            ptrLocation->setLocationData(loc.get());
            ptrLocation->setLocationPos(iX,iY);
			pimpl->m_ptrMainGridLayout->addItem(ptrLocation, iY, iX);
			pimpl->m_mCords2Locations.insert(std::make_pair(std::make_pair(iX, iY), ptrLocation));
        }
	}
	pimpl->m_ptrMainGridLayout->activate();
	//Log4Qt::Logger::logger("Process")->info("Maze drawned. Fitting into view.");
	QList<QGraphicsView*> lViews = views();
	QRectF rectF = pimpl->m_ptrMainItem->geometry();
	lViews.first()->fitInView(rectF,Qt::KeepAspectRatio);
	pimpl->iterCords2LocStart = pimpl->m_mCords2Locations.begin();
	pimpl->iterCords2LocEnd = pimpl->m_mCords2Locations.end();
	pimpl->m_pStartPoint = pimpl->m_pEmptyPoint;
	pimpl->m_sEndPoints.clear();
	//Log4Qt::Logger::logger("Process")->info("Maze fitted into view.");
}
void graphics_maze_scene::onExperimentSettingsChanged(const CExperimentSettings & xExperimentSettings)
{
	if (xExperimentSettings.startPosition.posX != pimpl->m_pStartPoint.first ||
		xExperimentSettings.startPosition.posY != pimpl->m_pStartPoint.second)
	{
		if (pimpl->m_pStartPoint != pimpl->m_pEmptyPoint)
		{
			pimpl->m_mCords2Locations[pimpl->m_pStartPoint]->setExitStartLocation(true, true);
			pimpl->m_mCords2Locations[pimpl->m_pStartPoint]->setPathData(ROBOT_NONE_DIR);
			pimpl->m_mCords2Locations[pimpl->m_pStartPoint]->update();
		}
		pimpl->m_pStartPoint = std::make_pair(xExperimentSettings.startPosition.posX - 1, xExperimentSettings.startPosition.posY - 1);
		pimpl->m_mCords2Locations[pimpl->m_pStartPoint]->setExitStartLocation(true);
		//m_mCords2Locations[m_pStartPoint]->setPathData(xExperimentSettings.startPosition.dir);
	}
	pimpl->m_mCords2Locations[pimpl->m_pStartPoint]->setPathData(xExperimentSettings.startPosition.dir);
	QString strInfo = QString ("robot start direction selected: %1").arg(ROBOT_DIRECTION_STRING(xExperimentSettings.startPosition.dir));
	//Log4Qt::Logger::logger("Process")->info(strInfo);
	pimpl->m_mCords2Locations[pimpl->m_pStartPoint]->update();
	PointSet				sEndPoints(xExperimentSettings.lFinishPositions.begin(),xExperimentSettings.lFinishPositions.end());

	if (sEndPoints != pimpl->m_sEndPoints)
	{
		for (PointSet::iterator iterPos = pimpl->m_sEndPoints.begin(); iterPos != pimpl->m_sEndPoints.end(); iterPos++)
		{
			std::pair< int, int> 	pPointPos;
			pPointPos = std::make_pair(iterPos->x()-1,iterPos->y()-1);
			if (pPointPos == pimpl->m_pEmptyPoint) continue;
			pimpl->m_mCords2Locations[pPointPos]->setExitStartLocation(true, true);
			pimpl->m_mCords2Locations[pPointPos]->update();
		}
		pimpl->m_sEndPoints = sEndPoints;
		for (PointSet::iterator iterPos = pimpl->m_sEndPoints.begin(); iterPos != pimpl->m_sEndPoints.end(); iterPos++)
		{
			std::pair< int, int> 	pPointPos;
			pPointPos = std::make_pair(iterPos->x()-1,iterPos->y()-1);
			if (pPointPos == pimpl->m_pEmptyPoint) continue;
			pimpl->m_mCords2Locations[pPointPos]->setExitStartLocation(false);
			pimpl->m_mCords2Locations[pPointPos]->update();
		}
	}
}
