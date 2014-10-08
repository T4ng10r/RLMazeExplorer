#include <Data/experiment/CExperiment.h>
#include <Data/experiment/CEnviroment.h>
#include <Maze/maze_generator.h>

CExperiment::CExperiment(void) : m_iExplorationSucces(0), m_iExplorationFails(0),m_ptrEnviroment(NULL){}
CExperiment::~CExperiment(void)
{
	delete m_ptrEnviroment;
}
//////////////////////////////////////////////////////////////////////////
void CExperiment::increseSuccessCounter()
{
    m_iExplorationSucces++;
}
void CExperiment::increseFailsCounter()
{
    m_iExplorationFails++;
}
unsigned int CExperiment::getSuccessCounter()
{
    return m_iExplorationSucces;
}
unsigned int CExperiment::getFailsCounter()
{
    return m_iExplorationFails;
}
int CExperiment::getExplorationsCount()
{
    return explorationResults.size();
}
//////////////////////////////////////////////////////////////////////////
void CExperiment::on_set_maze_data(const maze & xMazeSource)
{
    m_stMazeData = xMazeSource;
}
maze& CExperiment::getMazeData()
{
    return m_stMazeData;
}
void CExperiment::setExperimentSettings(const CExperimentSettings & xExperimentSettings)
{
    m_stExperimentSettings = xExperimentSettings;
}
//////////////////////////////////////////////////////////////////////////
void CExperiment::onnext_robot_move()
{
	Q_EMIT robotNextMove();
}
void CExperiment::startExperiment()
{
	delete m_ptrEnviroment;
	m_ptrEnviroment = new CEnviroment;

	connect(m_ptrEnviroment,SIGNAL(robotBeforeMove(CScanResults*)),SIGNAL(robotBeforeMove(CScanResults*)));
	//connect(m_ptrEnviroment,SIGNAL(robotNextMove()),SLOT(robotNextMove()));

	m_ptrEnviroment->setExperimentSettings(m_stExperimentSettings);
	m_ptrEnviroment->setMaze(m_stMazeData);
	m_ptrEnviroment->setKnowlegdeBase(&m_cKnowledgeBase);

	for(int index=0; index<m_stExperimentSettings.repeatingQuantity; index++)
	{
		m_ptrEnviroment->startSingleExploring();
		addExplorationResult(m_ptrEnviroment->getExplorationResults());
	    //emit nextExplorationInExperiment();
	}
	//emit setExploredKnowlegdeBase(m_ptrKnowledgeBase);	//we're giving control over KB existence to display widget
	//m_ptrKnowledgeBase = NULL;
}
void CExperiment::addExplorationResult(const CMazeExplorationResult & rExploration)
{
    explorationResults.push_back(rExploration);
}
// CExplorationResult *CExperiment::getLastExplorationResult()
// {
// 	if (explorationResults.isEmpty())
// 		return NULL;
// 	return 	&explorationResults.back();
// }
//void CExperiment::addKBTree(CKBTree & treeNode)
//{
//    explorationsKBTree.push_back(treeNode);
//}
CMazeExplorationResult & CExperiment::getLastExplorationResult()
{
    return 	explorationResults.back();
}
void CExperiment::operator=(const CExperiment & experimentDest)
{
    m_iExplorationSucces = experimentDest.m_iExplorationSucces;
    m_iExplorationFails = experimentDest.m_iExplorationFails;
    m_stMazeData = experimentDest.m_stMazeData;
    m_stExperimentSettings = experimentDest.m_stExperimentSettings;
    explorationResults = experimentDest.explorationResults;
}
bool CExperiment::getExplorationResult(uint nr, CMazeExplorationResult & lastExplorationResult)
{
    QList<CScanResults>::iterator	posIter;
    if (nr>=explorationResults.size())
        return false;
    lastExplorationResult=explorationResults[nr];
    return false;
}
void CExperiment::saveExperiment(QTextStream *pStream)
{
    vector<CMazeExplorationResult>::iterator	iterExploration;
	std::list<QPoint>::iterator		iterPoints;
    (*pStream)<<"EXPERIMENT_DATA\n";
    (*pStream)<<"Quantity   "<<m_stExperimentSettings.repeatingQuantity<<"\n";
    (*pStream)<<"StartPos   "<<m_stExperimentSettings.startPosition.posX<<" "<<m_stExperimentSettings.startPosition.posY<<" "<<(int)m_stExperimentSettings.startPosition.dir<<"\n";
    for(iterPoints=m_stExperimentSettings.lFinishPositions.begin();
            iterPoints!=m_stExperimentSettings.lFinishPositions.end(); iterPoints++)
    {
        (*pStream)<<"FinishPos   "<<iterPoints->x()<<" "<<iterPoints->x()<<"\n";
    }
    (*pStream)<<"Penalty    "<<m_stExperimentSettings.fPenaltyValue<<"\n";;
    (*pStream)<<"Reward     "<<m_stExperimentSettings.fPriceValue<<"\n";;
    for(iterExploration=explorationResults.begin(); iterExploration!=explorationResults.end(); iterExploration++)
    {
        iterExploration->saveExploration(pStream);
    }
    (*pStream)<<"EXPERIMENT_DATA_END\n";
}
QString CExperiment::loadExperiment(QTextStream *pStream)
{
    QString strLine;
    while(strLine.isEmpty())
    {
        (*pStream)>>strLine;
    }
    if (strLine=="KB_NODES_DATA_START")
        return strLine;
    else if (strLine!="EXPERIMENT_DATA")
    {
        qFatal("Error durnig file reading");
        return "";
    }

    (*pStream)>>strLine;
    while(strLine!="EXPERIMENT_DATA_END")
    {
        CMazeExplorationResult	expResult;
        expResult.loadExploration(pStream);
        explorationResults.push_back(expResult);
        (*pStream)>>strLine;
    }
    return strLine;
}

//CKBTree & CExperiment::getArchiveKBTree(int nr)
//{
//    if (nr>=explorationsKBTree.size())
//        return explorationsKBTree.back();
//    if (nr<0)
//        return explorationsKBTree.front();
//    return explorationsKBTree[nr];
//}
