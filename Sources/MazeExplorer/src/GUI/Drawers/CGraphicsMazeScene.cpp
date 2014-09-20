#include "CGraphicsMazeScene.h"
#include <Tools/loggers.h>
#include <QGraphicsView>

CGraphicsMazeScene::CGraphicsMazeScene()
{
    m_ptrMainItem = new QGraphicsWidget;
    m_ptrMainGridLayout = new QGraphicsGridLayout(m_ptrMainItem);
	m_ptrMainGridLayout->setSpacing(0);

	addItem(m_ptrMainItem);

    iterCords2LocStart = m_mCords2Locations.begin();
    iterCords2LocEnd = m_mCords2Locations.end();

	m_pStartPoint = std::make_pair(-1,-1);
	m_pEmptyPoint = m_pStartPoint;
	m_sEndPoints.clear();;
}
void CGraphicsMazeScene::reset()
{
	while(m_ptrMainGridLayout->count())
		m_ptrMainGridLayout->removeAt(0);
    for(MapCoords2Location::iterator iterLocs = iterCords2LocStart; iterLocs != iterCords2LocEnd; iterLocs++)
        removeItem(iterLocs->second);
	m_mCords2Locations.clear();
}
void CGraphicsMazeScene::setMaze(const maze & xMaze)
{
	//if (NULL == pMaze)	
	//{
	//	Log4Qt::Logger::logger("Process")->error("Trying to set Maze with NULL pointer.");
	//	return;
	//}
	//Log4Qt::Logger::logger("Process")->info("New Maze to be added.");
	reset();
    int iSizeX = xMaze.get_size_x();
    int iSizeY = xMaze.get_size_y();
	CGraphicsMazeLocation * ptrLocation = NULL;

    for(int iX = 0; iX<iSizeX; iX++)
	{
        for(int iY = 0; iY<iSizeY; iY++)
        {
            boost::optional<location> loc = xMaze.get_location(iX, iY);
			if (!loc)
            {
				QString strError = "Can't get location for (" + QString::number(iX)+","+QString::number(iY)+")";
				//Log4Qt::Logger::logger("Process")->error(strError);
				continue;
            }
            ptrLocation = new CGraphicsMazeLocation;
            ptrLocation->setLocationData(loc.get());
            ptrLocation->setLocationPos(iX,iY);
            m_ptrMainGridLayout->addItem(ptrLocation,iY,iX);
			m_mCords2Locations.insert(std::make_pair(std::make_pair(iX,iY),ptrLocation));
        }
	}
	m_ptrMainGridLayout->activate();
	//Log4Qt::Logger::logger("Process")->info("Maze drawned. Fitting into view.");
	QList<QGraphicsView*> lViews = views();
	QRectF rectF = m_ptrMainItem->geometry();
	lViews.first()->fitInView(rectF,Qt::KeepAspectRatio);
	iterCords2LocStart = m_mCords2Locations.begin();
	iterCords2LocEnd = m_mCords2Locations.end();
	m_pStartPoint = m_pEmptyPoint;
	m_sEndPoints.clear();
	//Log4Qt::Logger::logger("Process")->info("Maze fitted into view.");
}
void CGraphicsMazeScene::onExperimentSettingsChanged(const CExperimentSettings & xExperimentSettings)
{
	if ( xExperimentSettings.startPosition.posX !=m_pStartPoint.first || 
		xExperimentSettings.startPosition.posY !=m_pStartPoint.second )
	{
		if (m_pStartPoint !=m_pEmptyPoint)
		{
			m_mCords2Locations[m_pStartPoint]->setExitStartLocation(true,true);
			m_mCords2Locations[m_pStartPoint]->setPathData(ROBOT_NONE_DIR);
			m_mCords2Locations[m_pStartPoint]->update();
		}
		m_pStartPoint = std::make_pair(xExperimentSettings.startPosition.posX-1 ,xExperimentSettings.startPosition.posY-1);
		m_mCords2Locations[m_pStartPoint]->setExitStartLocation(true);
		//m_mCords2Locations[m_pStartPoint]->setPathData(xExperimentSettings.startPosition.dir);
	}
	m_mCords2Locations[m_pStartPoint]->setPathData(xExperimentSettings.startPosition.dir);
	QString strInfo = QString ("robot start direction selected: %1").arg(ROBOT_DIRECTION_STRING(xExperimentSettings.startPosition.dir));
	//Log4Qt::Logger::logger("Process")->info(strInfo);
	m_mCords2Locations[m_pStartPoint]->update();
	PointSet				sEndPoints(xExperimentSettings.lFinishPositions.begin(),xExperimentSettings.lFinishPositions.end());

	if  (sEndPoints!=m_sEndPoints)
	{
		for(PointSet::iterator iterPos = m_sEndPoints.begin();iterPos != m_sEndPoints.end();iterPos++)
		{
			std::pair< int, int> 	pPointPos;
			pPointPos = std::make_pair(iterPos->x()-1,iterPos->y()-1);
			if (pPointPos==m_pEmptyPoint) continue;
			m_mCords2Locations[pPointPos]->setExitStartLocation(true,true);
			m_mCords2Locations[pPointPos]->update();
		}
		m_sEndPoints = sEndPoints;
		for(PointSet::iterator iterPos = m_sEndPoints.begin();iterPos != m_sEndPoints.end();iterPos++)
		{
			std::pair< int, int> 	pPointPos;
			pPointPos = std::make_pair(iterPos->x()-1,iterPos->y()-1);
			if (pPointPos==m_pEmptyPoint) continue;
			m_mCords2Locations[pPointPos]->setExitStartLocation(false);
			m_mCords2Locations[pPointPos]->update();
		}
	}
}
