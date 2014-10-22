#include "enviroment.h"
#include <QFile>
#include <Data/experiment/robot.h>
#include <KnowledgeBase/CKnowlegdeBase.h>
#include <Tools/loggers.h>
#include <Maze/maze_interface.h>

class enviroment_private
{
public:
	enviroment_private(enviroment * pub);
	~enviroment_private();
	void set_connections();
	void	set_robot_to_startup_position();			//ustaw robota w pozycji startowej
	void	rotateScanResults(scan_results_handle scanResult, eRobotDir dir);
	void	afterFinishedExploration();
	void	createRobotRouteInfo();
public:
	enviroment * public_part;
	maze_interface_type maze_;
	//experiment settings - like robot start position, end points and maze params
	experiment_settings		m_stExperimentSettings;
	//robot/agent - he will perform experiment
	std::unique_ptr<robot>  agent;
	//location in which robot is currently
	location				m_stCurrentLocation;
	//current robot directions facing
	eRobotDir				robot_direction;
	//current robot position in maze
	QPoint					robot_position;
	CMazeExplorationResult	m_stExplorationResult;				//result of current exploration process

	//CExperiment				currentExperiment;

	maze_knowlegde_base_handle knowledge_base;		//baza wiedzy
	scan_results_handle currentScanResults;
};

enviroment_private::enviroment_private(enviroment * pub) : public_part(pub)
{
  agent.reset(new robot);
  robot_position=QPoint(0,0);
  set_connections();
}
enviroment_private::~enviroment_private(){}

void enviroment_private::set_connections()
{
	Q_CHECK_PTR(agent);
	bool bResult = false;
	bResult = QObject::connect(agent.get(),SIGNAL(robotMoved()), public_part, SLOT(onRobotMoved()));
	Q_ASSERT(bResult);
	bResult = QObject::connect(agent.get(),SIGNAL(robotRotate(bool ,bool )),public_part, SLOT(onRobotRotated(bool ,bool )));
	Q_ASSERT(bResult);
	bResult = QObject::connect(agent.get(),SIGNAL(robotScans(scan_results *)),public_part, SLOT(onRobotScan(scan_results *)));
	Q_ASSERT(bResult);
	bResult = QObject::connect(agent.get(),SIGNAL(is_in_exit(bool &)),public_part,SLOT(onRobotIfInExit(bool &)));
	Q_ASSERT(bResult);
	bResult = QObject::connect(agent.get(),SIGNAL(robotBeforeMove(scan_results *)),public_part,SIGNAL(robotBeforeMove(scan_results *)));
	Q_ASSERT(bResult);
}
void	enviroment_private::set_robot_to_startup_position()
{
	robot_direction = m_stExperimentSettings.startPosition.dir;
	robot_position = QPoint(m_stExperimentSettings.startPosition.pos_x, m_stExperimentSettings.startPosition.pos_x);
}
void enviroment_private::afterFinishedExploration()
{
	bool bInExit = false;
	//////////////////////////////////////////////////////////////////////////
	//potrzeba by ustalic ostatnia pozycjie i kierunek
	public_part->onRobotScan(currentScanResults);
	currentScanResults->robotPos = robot_position;
	currentScanResults->robotPos.dir = robot_direction;
	m_stExplorationResult.addRobotPosition(currentScanResults);
	//////////////////////////////////////////////////////////////////////////
	//zapamietujemy wynik aktualnej eksploracji
	knowledge_base->setCurrentExplorationResult(&m_stExplorationResult);
	//learning from explored maze parts and gathered data
	//NewExperiment
	//m_ptrKnowledgeBase->addExplorationResult(m_stExplorationResult);
	public_part->onRobotIfInExit(bInExit);
	knowledge_base->teach((bInExit) ? m_stExperimentSettings.fPriceValue : -m_stExperimentSettings.fPenaltyValue,bInExit);
	currentScanResults=NULL;
}
void enviroment_private::createRobotRouteInfo()
{
//    QList<CRobotPostion>::iterator	routeIter;
//    CScanResults		scanResult;
//    //QTableWidgetItem	* newItem;
//    return;
//    explorationResult->clear();
//    unsigned int index=0;
//    QString		str;
//    int count = m_stExplorationResult.getPositionsCount();
//
//    for(int i=0; i<count; i++)
//    {
//        m_stExplorationResult.getRobotPosition(i,scanResult);
//
//        explorationResult->setRowCount(index+1);
//
//        str.setNum(scanResult.robotPos.posX);
//        newItem = new QTableWidgetItem(str);
//        explorationResult->setItem(index, 0, newItem);
//
//        str.setNum(scanResult.robotPos.posY);
//        newItem = new QTableWidgetItem(str);
//        explorationResult->setItem(index, 1, newItem);
//
//        switch(scanResult.robotPos.dir)
//        {
//        case ROBOT_NORTH_DIR:
//            str="NORTH";
//            break;
//        case ROBOT_WEST_DIR:
//            str="WEST";
//            break;
//        case ROBOT_EAST_DIR:
//            str="EAST";
//            break;
//        case ROBOT_SOUTH_DIR:
//            str="SOUTH";
//            break;
//        }
//        newItem = new QTableWidgetItem(str);
//        explorationResult->setItem(index, 2, newItem);
//        index++;
//    }
//    QStringList strList;
//    strList<<"X"<<"Y"<<"Kierunek";
//    //explorationResult->setHorizontalHeaderLabels(strList);
//    m_stExplorationResult.clear();
}
void enviroment_private::rotateScanResults(scan_results_handle scanResult,eRobotDir dir)
{
	QString strFront,strBack;
	QVector<int>	scan;
	if (scanResult->exitsCount()>1)
	{
	//Log4Qt::Logger::logger("Process")->info(QString("Robot position %1,%2").arg(m_iRobotPos.x()).arg(m_iRobotPos.y()));
	//Log4Qt::Logger::logger("Process")->info(QString("Robot direction %1").arg(ROBOT_DIRECTION_STRING(m_iRobotDir)));
	}

#ifdef DEBUG_INFO
	//if (scanResult.exitsCount() > 1)
	//	//Log4Qt::Logger::logger("Process")->info(" Location exits");
	//	;
	strFront = QString("   %1").arg((int)scanResult->vFrontDir.size());
	strBack  = QString("  %1%2%3").arg((int)scanResult->vLeftDir.size()).
	arg((int)scanResult->vBackDir.size()).arg((int)scanResult->vRightDir.size());
#endif

	if (dir == ROBOT_WEST_DIR)
	{
		scanResult->Rotate(false);
	}
	else if (dir == ROBOT_SOUTH_DIR)
	{
		scanResult->Rotate(false);
		scanResult->Rotate(false);
	}
	else if (dir == ROBOT_EAST_DIR)
	{
		scanResult->Rotate(true);
	}

#ifdef DEBUG_INFO
	strFront += QString("    %1").arg((int)scanResult->vFrontDir.size());
	strBack  += QString("  %1 %3").arg((int)scanResult->vLeftDir.size()).arg((int)scanResult->vRightDir.size());
	//if (scanResult.exitsCount() > 1)
	//	//Log4Qt::Logger::logger("Process")->info(strFront);
	//	;
	//if (scanResult.exitsCount() > 1)
	//	//Log4Qt::Logger::logger("Process")->info(strBack);
	//	;
#endif
}
////////////////////////////////////////////////////////////////////////////////
enviroment::enviroment(experiment_settings settings, maze_interface_type maze_,
		maze_knowlegde_base_handle kb) : pimpl(new enviroment_private(this))
{
	pimpl->maze_ = maze_;
}
enviroment::~enviroment(void)
{
}
//////////////////////////////////////////////////////////////////////////
void enviroment::startSingleExploring()
{
	//void robotBeforeMove(CScanResults *scanResult);

	debugPrintMaze();
	pimpl->knowledge_base->ResetRootNode();
	pimpl->m_stExplorationResult.clear();
	pimpl->set_robot_to_startup_position();
	//actual exploration process
	pimpl->agent->start_exploring();
	pimpl->afterFinishedExploration();

	Q_EMIT robotFinished(pimpl->m_stExplorationResult);
	//	//creating robot route info to display it in window
	pimpl->createRobotRouteInfo();
}

//////////////////////////////////////////////////////////////////////////
void enviroment::onRobotScan(scan_results_handle scanResult)
{
	boost::optional<location> loc = pimpl->maze_->get_location(pimpl->robot_position.x()-1, pimpl->robot_position.y()-1);
	pimpl->m_stCurrentLocation = loc.get();

	int size = !pimpl->m_stCurrentLocation.is_wall(NORTH_DIR);
	scanResult->vFrontDir.resize(size);
	size = !pimpl->m_stCurrentLocation.is_wall(WEST_DIR);
	scanResult->vLeftDir.resize(size);
	size = !pimpl->m_stCurrentLocation.is_wall(EAST_DIR);
	scanResult->vRightDir.resize(size);
	size = !pimpl->m_stCurrentLocation.is_wall(SOUTH_DIR);
	scanResult->vBackDir.resize(size);

	scanResult->unrotatedLocDirs = scanResult->translateScanResultsToBitArray();

	pimpl->rotateScanResults(scanResult, pimpl->robot_direction);

	scanResult->locDirs = scanResult->translateScanResultsToBitArray();
	pimpl->currentScanResults = scanResult;
}
void enviroment::onRobotMoved()
{
#ifdef DEBUG_INFO
    debugPrintDirections();
#endif
    QPoint diff(0,0);
    if(pimpl->robot_position.x()<=0)
        Q_ASSERT(pimpl->robot_position.x()>0);
    if(pimpl->robot_position.y()<=0)
        Q_ASSERT(pimpl->robot_position.y()>0);

    pimpl->currentScanResults->robotPos = pimpl->robot_position;
    pimpl->currentScanResults->robotPos.dir = pimpl->robot_direction;
    pimpl->m_stExplorationResult.addRobotPosition(pimpl->currentScanResults);

    if (pimpl->robot_direction==ROBOT_NORTH_DIR)
        diff.setY(-1);
    else if (pimpl->robot_direction==ROBOT_SOUTH_DIR)
        diff.setY(+1);
    else if (pimpl->robot_direction==ROBOT_WEST_DIR)
        diff.setX(-1);
    else if (pimpl->robot_direction==ROBOT_EAST_DIR)
        diff.setX(+1);

    pimpl->robot_position+=diff;
	//Log4Qt::Logger::logger("Process")->info("");
}
void enviroment::onRobotRotated(bool bRight,bool /*bBack*/)
{
    if (!bRight)	//robot obraca sie w lewo
    {
        switch(pimpl->robot_direction)
        {
        case ROBOT_NORTH_DIR:
        	pimpl->robot_direction=ROBOT_WEST_DIR;
            break;
        case ROBOT_EAST_DIR:
        	pimpl->robot_direction=ROBOT_NORTH_DIR;
            break;
        case ROBOT_SOUTH_DIR:
        	pimpl->robot_direction=ROBOT_EAST_DIR;
            break;
        case ROBOT_WEST_DIR:
        	pimpl->robot_direction=ROBOT_SOUTH_DIR;
            break;
        default:
            break;
        }
    }
    else
    {
        switch(pimpl->robot_direction)
        {
        case ROBOT_NORTH_DIR:
        	pimpl->robot_direction=ROBOT_EAST_DIR;
            break;
        case ROBOT_EAST_DIR:
        	pimpl->robot_direction=ROBOT_SOUTH_DIR;
            break;
        case ROBOT_SOUTH_DIR:
        	pimpl->robot_direction=ROBOT_WEST_DIR;
            break;
        case ROBOT_WEST_DIR:
        	pimpl->robot_direction=ROBOT_NORTH_DIR;
            break;
        default:
            break;
        }
    }
}
void enviroment::onRobotIfInExit(bool &is_in_exit)
{
	is_in_exit=false;
	for(std::pair<unsigned int,unsigned int> point : pimpl->m_stExperimentSettings.target_positions)
	{
		if (pimpl->robot_position == QPoint(point.first, point.second))
		{
			is_in_exit=true;
			return;
		}
	}
}
//void CEnviroment::onStartExperiment(CExperimentSettings &m_ExperimentSettings)
//{
    ////TODO kazdy eksperyment moze zaczynac sie utworzeniem nowej bazy wiedzy lub pozostawieniem poprzedniej
    //if (m_ptrKnowledgeBase)
    //    delete m_ptrKnowledgeBase;
    //m_ptrKnowledgeBase = new CKnowlegdeBase;	//baza wiedzy
    ////currentExperiment.setExperimentSettings(&m_ExperimentSettings);
    //m_stExperimentSettings = &m_ExperimentSettings;
    ///*	if (!currentExperimentSettings->sLoadKBPath.isEmpty())
    //	{
    //		load(currentExperimentSettings->sLoadKBPath);
    //	}*/
    //m_ptrKnowledgeBase->NewExperiment(m_ExperimentSettings);

    //for(int index=0; index<m_ExperimentSettings.repeatingQuantity; index++)
    //{
    //    startSingleExploring();

    //    emit nextExplorationInExperiment();
    //}
    //if (!m_stExperimentSettings->sSaveKBPath.isEmpty())
    //{
    //    save(m_stExperimentSettings->sSaveKBPath);
    //}
    //m_ptrKnowledgeBase->FinishCurrentExperiment();
    //emit setExploredKnowlegdeBase(m_ptrKnowledgeBase);	//we're giving control over KB existence to display widget
    //m_ptrKnowledgeBase = NULL;
    //m_stExperimentSettings = NULL;
//}
//////////////////////////////////////////////////////////////////////////
//void CEnviroment::save(QString strPath)
//{
//    QFile		pFile(strPath);
//    pFile.open(QIODevice::WriteOnly|QIODevice::Text);
//
//    QTextStream pStream( &pFile );
//    pStream.setCodec("latin2");
//    maze_.saveMaze(&pStream);
//    m_ptrKnowledgeBase->saveKnowledgeBase(&pStream);
//    pFile.close();
//}
//void CEnviroment::load(QString strPath)
//{
//    QFile		pFile(strPath);
//    pFile.open(QIODevice::ReadOnly|QIODevice::Text);
//
//    QTextStream pStream( &pFile );
//    pStream.setCodec("latin2");
//    maze_.loadMaze(&pStream);
//    emit redrawMaze();
//    m_ptrKnowledgeBase->loadKnowledgeBase(&pStream);
//    pFile.close();
//}
//////////////////////////////////////////////////////////////////////////
void enviroment::debugPrintMaze()
{
	location	loc;
	QString mazeLine;
	QString mazeLine1;
	int maxX=pimpl->maze_->get_size_x();
	int maxY=pimpl->maze_->get_size_y();
	int indexX,indexY;

	mazeLine="-";
	for(indexX=0; indexX<maxX; indexX++)
	mazeLine+="---";
	//Log4Qt::Logger::logger("Process")->info(mazeLine);
	for(indexY=0; indexY<maxY; indexY++)
	{
		mazeLine.clear();
		for(indexX=0; indexX<maxX; indexX++)
		{
			loc.reset();
			loc = pimpl->maze_->get_location(indexX, indexY).get();
			if (loc.is_wall(WEST_DIR))
				mazeLine+="|";
			else
			{
				if (!loc.is_wall(EAST_DIR) && loc.is_wall(NORTH_DIR))
					mazeLine+="_";
				else
					mazeLine+=" ";
			}
			if (loc.is_wall(SOUTH_DIR))
				mazeLine+="__";
			else
				mazeLine+="  ";
			}
		mazeLine+="|";
		//Log4Qt::Logger::logger("Process")->info(mazeLine);
	}
}
void enviroment::debugPrintDirections()
{
	//Log4Qt::Logger::logger("Process")->info(QString("Robot direction %1").arg(ROBOT_DIRECTION_STRING(m_iRobotDir)));
}
CMazeExplorationResult enviroment::getExplorationResults()
{
	return pimpl->m_stExplorationResult;
}
/*void enviroment::setExperimentSettings(experiment_settings val)
{
	pimpl->m_stExperimentSettings = val;
}
void enviroment::setKnowlegdeBase(maze_knowlegde_base_handle knowledge_base_)
{
	pimpl->knowledge_base = knowledge_base_;
}*/
//////////////////////////////////////////////////////////////////////////
