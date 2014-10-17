#include "graphics_maze_scene.h"
#include <Tools/loggers.h>
#include <QGraphicsView>
#include <boost/shared_ptr.hpp>
#include <GUI/Drawers/CGraphicsMazeLocation.h>
#include <set>
#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include <QPoint>
#include <map>
#include <boost/format.hpp>

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
	void fit_into_view();
	void add_maze_locations(const maze_interface_type maze_data);
public:
	graphics_maze_scene * public_;
	MapCoords2Location m_mCords2Locations;
	MapCoords2Location::iterator iterCords2LocStart;
	MapCoords2Location::iterator iterCords2LocEnd;

	QGraphicsWidget *		main_item;
	QGraphicsGridLayout	*	main_grid_layout;

	std::pair< int, int> 	empty_point;
	std::pair< int, int> 	start_point;
	PointSet				end_points;
};

graphics_maze_scene_private::graphics_maze_scene_private(graphics_maze_scene * pub) : public_(pub)
{
	main_item = new QGraphicsWidget;
	main_grid_layout = new QGraphicsGridLayout(main_item);
	main_grid_layout->setSpacing(0);
	public_->addItem(main_item);

	iterCords2LocStart = m_mCords2Locations.begin();
	iterCords2LocEnd = m_mCords2Locations.end();

	start_point = std::make_pair(-1, -1);
	empty_point = start_point;
	end_points.clear();;
}

void graphics_maze_scene_private::reset()
{
	while (main_grid_layout->count())
		main_grid_layout->removeAt(0);
	for (MapCoords2Location::iterator iterLocs = iterCords2LocStart; iterLocs != iterCords2LocEnd; iterLocs++)
		public_->removeItem(iterLocs->second);
	m_mCords2Locations.clear();
}

void graphics_maze_scene_private::fit_into_view()
{
	//Log4Qt::Logger::logger("Process")->info("Maze drawned. Fitting into view.");
	QList<QGraphicsView*> lViews = public_->views ();
	QRectF rectF = main_item->geometry ();
	lViews.first ()->fitInView (rectF, Qt::KeepAspectRatio);
}
void graphics_maze_scene_private::add_maze_locations(const maze_interface_type maze_data)
{
	int size_x = maze_data->get_size_x();
	int size_y = maze_data->get_size_y();
	for (int x = 0; x < size_x; ++x)
	{
		for (int y = 0; y < size_y; ++y)
		{
			boost::optional<location> maze_location = maze_data->get_location(x, y);
			if (!maze_location)
			{
				printLog(eDebug, eWarningLogLevel, str(boost::format("Can't get location for ( %1%, %2% )") % x % y));
				continue;
			}
			CGraphicsMazeLocation* draw_location = new CGraphicsMazeLocation;
			draw_location->setLocationData(maze_location.get());
			draw_location->setLocationPos(x, y);
			main_grid_layout->addItem(draw_location, y, x);
			m_mCords2Locations.insert(
				std::make_pair(std::make_pair(x, y), draw_location));
		}
	}
}
//////////////////////////////////////////////////////////////////////////
graphics_maze_scene::graphics_maze_scene() : pimpl(new graphics_maze_scene_private(this)) {}
graphics_maze_scene::~graphics_maze_scene(){}

void graphics_maze_scene::setMaze(maze_interface_type maze_data)
{
	if (!maze_data)
	{
		printLog(eDebug, eErrorLogLevel, "Trying to set Maze with NULL pointer.");
		return;
	}
	pimpl->reset();
	pimpl->add_maze_locations(maze_data);
	pimpl->main_grid_layout->activate();

	pimpl->fit_into_view();
	pimpl->iterCords2LocStart = pimpl->m_mCords2Locations.begin();
	pimpl->iterCords2LocEnd = pimpl->m_mCords2Locations.end();
	pimpl->start_point = pimpl->empty_point;
	pimpl->end_points.clear();
}
void graphics_maze_scene::on_experiment_settings_changed(const experiment_settings & xExperimentSettings)
{
	if (xExperimentSettings.startPosition.pos_x != pimpl->start_point.first ||
		xExperimentSettings.startPosition.pos_y != pimpl->start_point.second)
	{
		if (pimpl->start_point != pimpl->empty_point)
		{
			pimpl->m_mCords2Locations[pimpl->start_point]->setExitStartLocation(true, true);
			pimpl->m_mCords2Locations[pimpl->start_point]->setPathData(ROBOT_NONE_DIR);
			pimpl->m_mCords2Locations[pimpl->start_point]->update();
		}
		pimpl->start_point = std::make_pair(xExperimentSettings.startPosition.pos_x - 1, xExperimentSettings.startPosition.pos_y - 1);
		pimpl->m_mCords2Locations[pimpl->start_point]->setExitStartLocation(true);
		//m_mCords2Locations[m_pStartPoint]->setPathData(xExperimentSettings.startPosition.dir);
	}
	pimpl->m_mCords2Locations[pimpl->start_point]->setPathData(xExperimentSettings.startPosition.dir);
	QString strInfo = QString ("robot start direction selected: %1").arg(ROBOT_DIRECTION_STRING(xExperimentSettings.startPosition.dir));
	//Log4Qt::Logger::logger("Process")->info(strInfo);
	pimpl->m_mCords2Locations[pimpl->start_point]->update();
	PointSet				sEndPoints(xExperimentSettings.lFinishPositions.begin(),xExperimentSettings.lFinishPositions.end());

	if (sEndPoints != pimpl->end_points)
	{
		for (PointSet::iterator iterPos = pimpl->end_points.begin(); iterPos != pimpl->end_points.end(); iterPos++)
		{
			std::pair< int, int> 	pPointPos;
			pPointPos = std::make_pair(iterPos->x()-1,iterPos->y()-1);
			if (pPointPos == pimpl->empty_point) continue;
			pimpl->m_mCords2Locations[pPointPos]->setExitStartLocation(true, true);
			pimpl->m_mCords2Locations[pPointPos]->update();
		}
		pimpl->end_points = sEndPoints;
		for (PointSet::iterator iterPos = pimpl->end_points.begin(); iterPos != pimpl->end_points.end(); iterPos++)
		{
			std::pair< int, int> 	pPointPos;
			pPointPos = std::make_pair(iterPos->x()-1,iterPos->y()-1);
			if (pPointPos == pimpl->empty_point) continue;
			pimpl->m_mCords2Locations[pPointPos]->setExitStartLocation(false);
			pimpl->m_mCords2Locations[pPointPos]->update();
		}
	}
}
