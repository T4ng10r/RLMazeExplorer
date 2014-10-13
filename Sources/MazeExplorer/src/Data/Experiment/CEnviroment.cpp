#include "CEnviroment.h"
#include <QFile>
#include <Data/Experiment/robot.h>
#include <KnowledgeBase/CKnowlegdeBase.h>
#include <Tools/loggers.h>

CEnviroment::CEnviroment(void) : m_ptrRobot(NULL), m_ptrKnowledgeBase(NULL),currentScanResults(NULL)
{
    m_ptrRobot = new robot;
    m_iRobotPos=QPoint(0,0);

    Q_CHECK_PTR(m_ptrRobot);
    bool bResult = false;
    bResult = connect(m_ptrRobot,SIGNAL(robotMoved()),SLOT(onRobotMoved()));
	Q_ASSERT(bResult);
    bResult = connect(m_ptrRobot,SIGNAL(robotRotate(bool ,bool )),SLOT(onRobotRotated(bool ,bool )));
	Q_ASSERT(bResult);
    bResult = connect(m_ptrRobot,SIGNAL(robotScans(CScanResults *)),SLOT(onRobotScan(CScanResults *)));
	Q_ASSERT(bResult);
    bResult = connect(m_ptrRobot,SIGNAL(is_in_exit(bool &)),SLOT(onRobotIfInExit(bool &)));
	Q_ASSERT(bResult);
	bResult = connect(m_ptrRobot,SIGNAL(robotBeforeMove(CScanResults *)),SIGNAL(robotBeforeMove(CScanResults *)));
	Q_ASSERT(bResult);
}
CEnviroment::~CEnviroment(void)
{
    m_ptrKnowledgeBase=NULL;
    delete m_ptrRobot;
}
//////////////////////////////////////////////////////////////////////////
void CEnviroment::setRobotToStart()
{
    m_iRobotDir = m_stExperimentSettings.startPosition.dir;
    m_iRobotPos.setX(m_stExperimentSettings.startPosition.posX);
    m_iRobotPos.setY(m_stExperimentSettings.startPosition.posY);
};
void CEnviroment::startSingleExploring()
{
	//void robotBeforeMove(CScanResults *scanResult);

    debugPrintMaze();
    m_ptrKnowledgeBase->ResetRootNode();
	m_stExplorationResult.clear();
    setRobotToStart();
    m_ptrRobot->setKnowledgeBase(m_ptrKnowledgeBase); //pod³¹czamy agenta do KB
    //actual exploration process
    m_ptrRobot->start_exploring();
    afterFinishedExploration();

	Q_EMIT robotFinished(m_stExplorationResult);
    //	//creating robot route info to display it in window
    createRobotRouteInfo();
}
void CEnviroment::afterFinishedExploration()
{
    bool bInExit = false;
	//////////////////////////////////////////////////////////////////////////
    //potrzeba by ustalic ostatnia pozycjie i kierunek
	onRobotScan(currentScanResults);
    currentScanResults->robotPos = m_iRobotPos;
    currentScanResults->robotPos.dir = m_iRobotDir;
    m_stExplorationResult.addRobotPosition(*currentScanResults);
	//////////////////////////////////////////////////////////////////////////
    //zapamietujemy wynik aktualnej eksploracji
	m_ptrKnowledgeBase->setCurrentExplorationResult(&m_stExplorationResult);
    //testujemy czy prawid³owo zosta³a zapisana sciezka
    //learning from explored maze parts and gathered data
    //NewExperiment
    //m_ptrKnowledgeBase->addExplorationResult(m_stExplorationResult);
    onRobotIfInExit(bInExit);
    m_ptrKnowledgeBase->teach((bInExit) ? m_stExperimentSettings.fPriceValue : -m_stExperimentSettings.fPenaltyValue,bInExit);
    currentScanResults=NULL;
}
void CEnviroment::createRobotRouteInfo()
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
void CEnviroment::rotateScanResults(CScanResults & scanResult,eRobotDir dir)
{
    QString strFront,strBack;
    QVector<int>	scan;
    if (scanResult.exitsCount()>1)
	{
		//Log4Qt::Logger::logger("Process")->info(QString("Robot position %1,%2").arg(m_iRobotPos.x()).arg(m_iRobotPos.y()));
		//Log4Qt::Logger::logger("Process")->info(QString("Robot direction %1").arg(ROBOT_DIRECTION_STRING(m_iRobotDir)));
	}

#ifdef DEBUG_INFO
	//if (scanResult.exitsCount() > 1)
	//	//Log4Qt::Logger::logger("Process")->info(" Location exits");
	//	;
    strFront = QString("   %1").arg((int)scanResult.vFrontDir.size());
    strBack  = QString("  %1%2%3").arg((int)scanResult.vLeftDir.size()).
               arg((int)scanResult.vBackDir.size()).arg((int)scanResult.vRightDir.size());
#endif

    if (dir == ROBOT_WEST_DIR)
    {
        scanResult.Rotate(false);
    }
    else if (dir == ROBOT_SOUTH_DIR)
    {
        scanResult.Rotate(false);
        scanResult.Rotate(false);
    }
    else if (dir == ROBOT_EAST_DIR)
    {
        scanResult.Rotate(true);
    }

#ifdef DEBUG_INFO
    strFront += QString("    %1").arg((int)scanResult.vFrontDir.size());
    strBack  += QString("  %1 %3").arg((int)scanResult.vLeftDir.size()).arg((int)scanResult.vRightDir.size());
	//if (scanResult.exitsCount() > 1)
	//	//Log4Qt::Logger::logger("Process")->info(strFront);
	//	;
	//if (scanResult.exitsCount() > 1)
	//	//Log4Qt::Logger::logger("Process")->info(strBack);
	//	;
#endif
}
//////////////////////////////////////////////////////////////////////////
void CEnviroment::onRobotScan(CScanResults *scanResult)
{
	boost::optional<location> loc = m_stMaze.get_location(m_iRobotPos.x()-1, m_iRobotPos.y()-1);
	m_stCurrentLocation = loc.get();

    int size = !m_stCurrentLocation.is_wall(NORTH_DIR);
    scanResult->vFrontDir.resize(size);
	size = !m_stCurrentLocation.is_wall(WEST_DIR);
    scanResult->vLeftDir.resize(size);
	size = !m_stCurrentLocation.is_wall(EAST_DIR);
    scanResult->vRightDir.resize(size);
	size = !m_stCurrentLocation.is_wall(SOUTH_DIR);
    scanResult->vBackDir.resize(size);

    scanResult->unrotatedLocDirs = scanResult->translateScanResultsToBitArray();

    rotateScanResults(*scanResult,m_iRobotDir);

	scanResult->locDirs = scanResult->translateScanResultsToBitArray();
    currentScanResults = scanResult;
}
void CEnviroment::onRobotMoved()
{
#ifdef DEBUG_INFO
    debugPrintDirections();
#endif
    QPoint diff(0,0);
    if(m_iRobotPos.x()<=0)
        Q_ASSERT(m_iRobotPos.x()>0);
    if(m_iRobotPos.y()<=0)
        Q_ASSERT(m_iRobotPos.y()>0);

    currentScanResults->robotPos = m_iRobotPos;
    currentScanResults->robotPos.dir = m_iRobotDir;
    m_stExplorationResult.addRobotPosition(*currentScanResults);

    if (m_iRobotDir==ROBOT_NORTH_DIR)
        diff.setY(-1);
    else if (m_iRobotDir==ROBOT_SOUTH_DIR)
        diff.setY(+1);
    else if (m_iRobotDir==ROBOT_WEST_DIR)
        diff.setX(-1);
    else if (m_iRobotDir==ROBOT_EAST_DIR)
        diff.setX(+1);

    m_iRobotPos+=diff;
	//Log4Qt::Logger::logger("Process")->info("");
}
void CEnviroment::onRobotRotated(bool bRight,bool /*bBack*/)
{
    if (!bRight)	//robot obraca sie w lewo
    {
        switch(m_iRobotDir)
        {
        case ROBOT_NORTH_DIR:
            m_iRobotDir=ROBOT_WEST_DIR;
            break;
        case ROBOT_EAST_DIR:
            m_iRobotDir=ROBOT_NORTH_DIR;
            break;
        case ROBOT_SOUTH_DIR:
            m_iRobotDir=ROBOT_EAST_DIR;
            break;
        case ROBOT_WEST_DIR:
            m_iRobotDir=ROBOT_SOUTH_DIR;
            break;
        default:
            break;
        }
    }
    else
    {
        switch(m_iRobotDir)
        {
        case ROBOT_NORTH_DIR:
            m_iRobotDir=ROBOT_EAST_DIR;
            break;
        case ROBOT_EAST_DIR:
            m_iRobotDir=ROBOT_SOUTH_DIR;
            break;
        case ROBOT_SOUTH_DIR:
            m_iRobotDir=ROBOT_WEST_DIR;
            break;
        case ROBOT_WEST_DIR:
            m_iRobotDir=ROBOT_NORTH_DIR;
            break;
        default:
            break;
        }
    }
}
void CEnviroment::onRobotIfInExit(bool &bIfInExit)
{
	std::list<QPoint>::iterator	iterFinishPos;
    bIfInExit=false;
    for(iterFinishPos=m_stExperimentSettings.lFinishPositions.begin();
            iterFinishPos!=m_stExperimentSettings.lFinishPositions.end();
            iterFinishPos++)
    {
        QPoint pos =*iterFinishPos;
        if ( m_iRobotPos==pos )
        {
            bIfInExit=true;
            return;
        }
    }
}
void CEnviroment::setMaze(const maze &val) 
{ 
	m_stMaze = val; 
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
//    m_stMaze.saveMaze(&pStream);
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
//    m_stMaze.loadMaze(&pStream);
//    emit redrawMaze();
//    m_ptrKnowledgeBase->loadKnowledgeBase(&pStream);
//    pFile.close();
//}
//////////////////////////////////////////////////////////////////////////
void CEnviroment::debugPrintMaze()
{
    location	loc;
    QString mazeLine;
    QString mazeLine1;
    int maxX=m_stMaze.get_size_x();
    int maxY=m_stMaze.get_size_y();
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
			loc = m_stMaze.get_location(indexX, indexY).get();
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
void CEnviroment::debugPrintDirections()
{
	//Log4Qt::Logger::logger("Process")->info(QString("Robot direction %1").arg(ROBOT_DIRECTION_STRING(m_iRobotDir)));
}
//////////////////////////////////////////////////////////////////////////
