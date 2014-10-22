#include <Data/experiment/experiment.h>
#include <Data/experiment/enviroment.h>
#include <Maze/maze_generator.h>

class experiment_private
{
public:
	experiment_private();
	void reset_enviroment();
public:
	time_t  duration_in_msec;
	maze_interface_type maze_data;
	experiment_settings  settings;
	std::shared_ptr<enviroment>  enviroment_;
	std::vector<CMazeExplorationResult>	explorationResults;	//lista pozycji robota dla ka�dego przej�cia w ramach danego eksperymentu
	maze_knowlegde_base_handle			knowledge_base;
	//   vector<CKBTree>	            explorationsKBTree;	//lista pozycji robota dla ka�dego przej�cia w ramach danego eksperymentu
	unsigned int exploration_succeses;		//how many time exploration was successful
	unsigned int exploration_fails;		//how many time exploration was failure
};

experiment_private::experiment_private(): duration_in_msec(0), knowledge_base(new maze_knowlegde_base),
    exploration_succeses(0), exploration_fails(0)
{
}
void experiment_private::reset_enviroment()
{
	enviroment_.reset(new enviroment(settings, maze_data, knowledge_base));
	//enviroment_->setExperimentSettings(settings);
	//enviroment_->setMaze(maze_data);
	//enviroment_->setKnowlegdeBase(knowledge_base);
}

//////////////////////////////////////////////////////////////////////////
experiment::experiment() : pimpl(new experiment_private())
{	}
experiment::experiment(experiment_settings & settings_, maze_interface_type maze_) :
    pimpl(new experiment_private())
{
	pimpl->maze_data = maze_;
	pimpl->settings = settings_;
}
experiment::~experiment()
{ }
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
void experiment::on_set_maze_data(maze_interface_type maze_source)
{
	pimpl->maze_data = maze_source;
}
/*maze_interface_type experiment::getMazeData()
{
	return pimpl->maze_data;
}*/
void experiment::setExperimentSettings(const experiment_settings & xExperimentSettings)
{
	pimpl->settings = xExperimentSettings;
}
//////////////////////////////////////////////////////////////////////////
void experiment::on_next_robot_move()
{
	Q_EMIT robotNextMove();
}
void experiment::start()
{
	pimpl->reset_enviroment();

	connect(pimpl->enviroment_.get(), SIGNAL(robotBeforeMove(scan_results*)), SIGNAL(robotBeforeMove(scan_results*)));
	//connect(enviroment_,SIGNAL(robotNextMove()),SLOT(robotNextMove()));


	for (int index = 0; index<pimpl->settings.repeat_count; index++)
	{
		pimpl->enviroment_->startSingleExploring();
		addExplorationResult(pimpl->enviroment_->getExplorationResults());
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
//	pimpl->maze_data = experimentDest.getMazeData();
//	pimpl->settings = experimentDest.settings;
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
	(*pStream) << "Quantity   " << pimpl->settings.repeat_count << "\n";
	(*pStream) << "StartPos   " << pimpl->settings.startPosition.pos_x << " " << pimpl->settings.startPosition.pos_y << " " << (int)pimpl->settings.startPosition.dir << "\n";
	for(std::pair<unsigned int,unsigned int> point : pimpl->settings.target_positions)
	//	for (iterPoints = pimpl->settings.lFinishPositions.begin();
	//		 iterPoints != pimpl->settings.lFinishPositions.end(); iterPoints++)
	{
		(*pStream)<<"FinishPos   "<<point.first<<" "<<point.second<<"\n";
	}
	(*pStream) << "Penalty    " << pimpl->settings.fPenaltyValue << "\n";;
	(*pStream) << "Reward     " << pimpl->settings.fPriceValue << "\n";;
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
