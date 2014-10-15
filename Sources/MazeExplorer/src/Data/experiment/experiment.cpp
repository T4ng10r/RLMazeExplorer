#include <Data/experiment/experiment.h>
#include <Data/experiment/enviroment.h>
#include <Maze/maze_generator.h>

class experiment_private
{
public:
	experiment_private();
	~experiment_private();
public:
	time_t  experimentDuration;
	maze  m_stMazeData;
	experiment_settings  m_stExperimentSettings;
	std::shared_ptr<enviroment>  m_ptrEnviroment;
	vector<CMazeExplorationResult>	explorationResults;	//lista pozycji robota dla ka�dego przej�cia w ramach danego eksperymentu
	maze_knowlegde_base_handle			m_cKnowledgeBase;
	//   vector<CKBTree>	            explorationsKBTree;	//lista pozycji robota dla ka�dego przej�cia w ramach danego eksperymentu
	unsigned int exploration_succeses;		//how many time exploration was successful
	unsigned int exploration_fails;		//how many time exploration was failure
};

experiment_private::experiment_private(): exploration_succeses(0), exploration_fails(0),
		m_ptrEnviroment(NULL), m_cKnowledgeBase(new maze_knowlegde_base)
{


}
experiment_private::~experiment_private()
{
}

//////////////////////////////////////////////////////////////////////////
experiment::experiment(void) : pimpl(new experiment_private())
{}
experiment::~experiment(void)
{
}
//////////////////////////////////////////////////////////////////////////
void experiment::increseSuccessCounter()
{
    pimpl->exploration_succeses++;
}
void experiment::increseFailsCounter()
{
	pimpl->exploration_fails++;
}
unsigned int experiment::getSuccessCounter()
{
	return pimpl->exploration_succeses;
}
unsigned int experiment::getFailsCounter()
{
	return pimpl->exploration_fails;
}
int experiment::getExplorationsCount()
{
	return pimpl->explorationResults.size();
}
//////////////////////////////////////////////////////////////////////////
void experiment::on_set_maze_data(const maze & xMazeSource)
{
	pimpl->m_stMazeData = xMazeSource;
}
maze& experiment::getMazeData()
{
	return pimpl->m_stMazeData;
}
void experiment::setExperimentSettings(const experiment_settings & xExperimentSettings)
{
	pimpl->m_stExperimentSettings = xExperimentSettings;
}
//////////////////////////////////////////////////////////////////////////
void experiment::onnext_robot_move()
{
	Q_EMIT robotNextMove();
}
void experiment::startExperiment()
{
	pimpl->m_ptrEnviroment.reset(new enviroment);

	connect(pimpl->m_ptrEnviroment.get(), SIGNAL(robotBeforeMove(scan_results*)), SIGNAL(robotBeforeMove(scan_results*)));
	//connect(m_ptrEnviroment,SIGNAL(robotNextMove()),SLOT(robotNextMove()));

	pimpl->m_ptrEnviroment->setExperimentSettings(pimpl->m_stExperimentSettings);
	pimpl->m_ptrEnviroment->setMaze(pimpl->m_stMazeData);
	pimpl->m_ptrEnviroment->setKnowlegdeBase(pimpl->m_cKnowledgeBase);

	for (int index = 0; index<pimpl->m_stExperimentSettings.repeat_count; index++)
	{
		pimpl->m_ptrEnviroment->startSingleExploring();
		addExplorationResult(pimpl->m_ptrEnviroment->getExplorationResults());
	    //emit nextExplorationInExperiment();
	}
	//emit setExploredKnowlegdeBase(m_ptrKnowledgeBase);	//we're giving control over KB existence to display widget
	//m_ptrKnowledgeBase = NULL;
}
void experiment::addExplorationResult(const CMazeExplorationResult & rExploration)
{
	pimpl->explorationResults.push_back(rExploration);
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
CMazeExplorationResult & experiment::getLastExplorationResult()
{
	return 	pimpl->explorationResults.back();
}
//void experiment::operator=(const experiment & experimentDest)
//{
//	pimpl->exploration_succeses = experimentDest.getSuccessCounter();
//	pimpl->exploration_fails = experimentDest.getFailsCounter();
//	pimpl->m_stMazeData = experimentDest.getMazeData();
//	pimpl->m_stExperimentSettings = experimentDest.m_stExperimentSettings;
//	pimpl->explorationResults = experimentDest.explorationResults;
//}
bool experiment::getExplorationResult(uint nr, CMazeExplorationResult & lastExplorationResult)
{
    QList<scan_results>::iterator	posIter;
	if (nr >= pimpl->explorationResults.size())
        return false;
	lastExplorationResult = pimpl->explorationResults[nr];
    return false;
}
void experiment::saveExperiment(QTextStream *pStream)
{
    vector<CMazeExplorationResult>::iterator	iterExploration;
	std::list<QPoint>::iterator		iterPoints;
    (*pStream)<<"EXPERIMENT_DATA\n";
	(*pStream) << "Quantity   " << pimpl->m_stExperimentSettings.repeat_count << "\n";
	(*pStream) << "StartPos   " << pimpl->m_stExperimentSettings.startPosition.posX << " " << pimpl->m_stExperimentSettings.startPosition.posY << " " << (int)pimpl->m_stExperimentSettings.startPosition.dir << "\n";
	for (iterPoints = pimpl->m_stExperimentSettings.lFinishPositions.begin();
		 iterPoints != pimpl->m_stExperimentSettings.lFinishPositions.end(); iterPoints++)
    {
        (*pStream)<<"FinishPos   "<<iterPoints->x()<<" "<<iterPoints->x()<<"\n";
    }
	(*pStream) << "Penalty    " << pimpl->m_stExperimentSettings.fPenaltyValue << "\n";;
	(*pStream) << "Reward     " << pimpl->m_stExperimentSettings.fPriceValue << "\n";;
	for (iterExploration = pimpl->explorationResults.begin(); iterExploration != pimpl->explorationResults.end(); iterExploration++)
    {
        iterExploration->saveExploration(pStream);
    }
    (*pStream)<<"EXPERIMENT_DATA_END\n";
}
QString experiment::loadExperiment(QTextStream *pStream)
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
        qFatal("Error during file reading");
        return "";
    }

    (*pStream)>>strLine;
    while(strLine!="EXPERIMENT_DATA_END")
    {
        CMazeExplorationResult	expResult;
        expResult.loadExploration(pStream);
		pimpl->explorationResults.push_back(expResult);
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
