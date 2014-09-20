#include <Data/CMazeKnowlegdeBase.h>
#include <time.h>
#define DEBUG_INFO
#include <Tools/loggers.h>

CMazeKnowlegdeBase::CMazeKnowlegdeBase(void)
{
#ifdef DEBUG_INFO
	//Log4Qt::Logger::logger("MazeKB")->setLevel(Log4Qt::Level::ALL_INT);
#else
	//Log4Qt::Logger::logger("MazeKB")->setLevel(Log4Qt::Level::WARN_INT);
#endif

    currentMethodOfChoosingExits=treeOfLastDecisionPoints;
    ResetKB();
}
CMazeKnowlegdeBase::~CMazeKnowlegdeBase(void) {}
void CMazeKnowlegdeBase::ResetKB()
{
    m_iExplorationQuantity=0;
    m_iExplorationSucces=0;
    m_iExplorationFails=0;

    m_ptrCurrentNode = &m_stKBRoot;
    m_stKBRoot.setStateID(LOCATION_EMPTY);
}
void CMazeKnowlegdeBase::ResetRootNode()
{
    m_ptrCurrentNode=&m_stKBRoot;
}
CMazeKnowlegdeBase::CKBTreeNode * CMazeKnowlegdeBase::getCurrentNode()
{
	return m_ptrCurrentNode;
}
//LocationDirs CKnowlegdeBase::translateScanResultsToBitArray(CScanResults &scanResult)
//{
//    int				result=0;
//    bool			bPassage=false;
//
//    scanResult.getScanResult(FRONT_DIR,bPassage);
//    if (bPassage)	result |=LOCATION_FRONT;
//    scanResult.getScanResult(LEFT_DIR,bPassage);
//    if (bPassage)	result |=LOCATION_LEFT;
//    scanResult.getScanResult(RIGHT_DIR,bPassage);
//    if (bPassage)	result |=LOCATION_RIGHT;
//    return (eLocationDirs)result;
//}
//void CKnowlegdeBase::NewExperiment(CExperimentSettings & expSeting)
//{
//    //jeœli mamy ju¿ jakieœ wczeœniejsze eksploracje - zapamietaj KB
//    CExperiment experiment;
//    experiment.setExperimentSettings(&expSeting);
//    vectorOfExperiments.push_back(experiment);
//    currentExperiment = &vectorOfExperiments.back();
//    currentNode=&KBTree;
//}
//void CKnowlegdeBase::FinishCurrentExperiment()
//{
//
//}
////*******************************************************************//
void CMazeKnowlegdeBase::teach(double value,bool bReward)
{
    Q_CHECK_PTR(m_ptrCurrentExplorationResult);
    Q_ASSERT(m_ptrCurrentExplorationResult!=NULL);
//	currentExperiment->increseSuccessCounter();

    m_ptrCurrentExplorationResult->bExplorationSuccessful=bReward;

//	staticLearningPolicy(lastExplorationResult,value,true);
    treeLearningPolicy(m_ptrCurrentExplorationResult,value,bReward);
}
//void CKnowlegdeBase::staticLearningPolicy(CExplorationResult */*lastExplorationResult*/, double /*value*/, bool /*bReward*/)
//{
//    /*	CScanResults	scanResult;
//    	LocationID locationID;
//    	int direction,count = lastExplorationResult->getCrossRoadsCount();
//    	if (count<1)
//    	{
//    		qWarning("Lack of crossroads in exploration path");
//    		return;
//    	}
//    	double delta = 1/count;
//    	double discountedValue = 1;
//    	double finalValue;
//    	if (bReward)	direction=1;
//    	else			direction=-1;
//    	// rewarding only policy - choosing one location (STATIC LEARNING)
//    	for(int index = count-1; index>=0; index--)
//    	{
//    		finalValue = value*discountedValue*direction;
//
//    		if (!lastExplorationResult->getRobotPosition(index,scanResult))
//    		{
//    			qWarning("problem");
//    		}
//    		//working only with crossroads locations
//    		if(scanResult.getExitsCount(SCAN_BACK_DIR)==1)
//    			continue;
//    		locationID = translateScanResultsToBitArray(scanResult);
//
//    		//getting appropriate location from KB
//    		if (!m_mOneLocation.contains(locationID))
//    		{
//    			qFatal("There was try to get non-existing value from KB internal map");
//    			exit(0);
//    		}
//    		CKBLocationData & data=m_mOneLocation[locationID];
//    		data.modifyChoicingProbabiliies(scanResult.robotChosenDir,finalValue);
//    		//rewarding or punishing
//    		discountedValue-=delta;
//    	}*/
//}
//void CMazeKnowlegdeBase::treeLearningPolicy(CExplorationResult<LocationDirs,directions> *lastExplorationResult, double value, bool bReward)
//{
//
//}
void CMazeKnowlegdeBase::treeLearningPolicy(CExplorationResult<LocationDirs,directions> *lastExplorationResult, double value, bool bReward)
{
    CKBTreeNode	*	ptNode, * ptCurrentNode;

    //first we need to check if this path exist in KB tree
    vector<CScanResults> listCrossRoads; //lista skrzyzowan - punktow decyzyjnych
    CScanResults	scanResult,nextScanResult;

	
	CMazeExplorationResult * ptrExplorationResult = dynamic_cast<CMazeExplorationResult *>(lastExplorationResult);
    ptrExplorationResult->prepareCrossRoadsList(listCrossRoads);
    double crossRoadCounts = listCrossRoads.size();

	CKBTreeNode::Action2Probabilities mDirsProbs;
	CKBTreeNode::Action2Probabilities::iterator IterMDirs;
    QString strDirs;

    ptCurrentNode = &m_stKBRoot;
	ptCurrentNode->getDirections(mDirsProbs,false);
    strDirs="Values ";
    for(IterMDirs=mDirsProbs.begin();
            IterMDirs!=mDirsProbs.end();
            IterMDirs++)
    {
        strDirs += QString("(%1)").arg(scanResult.translateLocID(DIR_TO_LOCATION(IterMDirs->first)));
        strDirs += QString(": %1, ").arg((double)IterMDirs->second);
    }
	//Log4Qt::Logger::logger("MazeKB")->info(strDirs);
    strDirs="Percents ";
    ptCurrentNode->getDirections(mDirsProbs);
    for(IterMDirs=mDirsProbs.begin(); IterMDirs!=mDirsProbs.end(); IterMDirs++)
    {
        strDirs += QString("(%1)").arg(scanResult.translateLocID(DIR_TO_LOCATION(IterMDirs->first)));
        strDirs += QString(": %1, ").arg((double)IterMDirs->second);
    }
	//Log4Qt::Logger::logger("MazeKB")->info(strDirs);

    //printDebugCrossRoadsList(listCrossRoads);
    //Log4Qt::Logger::logger("MazeKB")->info("BEGIN tree learning policy\n");
	strDirs=QString("  Crossroads count   %1").arg(crossRoadCounts);
    //Log4Qt::Logger::logger("MazeKB")->info(strDirs);
    if (crossRoadCounts<1)
    {
		//Log4Qt::Logger::logger("MazeKB")->warn("Lack of crossroads in exploration path");
        return;
    }
    double delta = 1.0/crossRoadCounts;
    double finalValue,discount = delta;//,discountedValue = delta;

    //crossRoadCounts=0;
    vector<CScanResults>::iterator iterCross;

    ptCurrentNode = &m_stKBRoot;
    m_ptrCurrentNode = &m_stKBRoot;
    for(iterCross=listCrossRoads.begin(); iterCross!=listCrossRoads.end(); iterCross++)
    {
        finalValue = value*discount;
        scanResult=*iterCross;
		strDirs=QString(" Discounted Value %1").arg(finalValue);
		//Log4Qt::Logger::logger("MazeKB")->info(strDirs);
        //first walkthorugh KB
        //ustawiamy dane dotyczace korzenia
        if (ptCurrentNode->getStateID() == LOCATION_EMPTY)
        {
            bool bPassage;
            //scanResult.locDirs;
            m_ptrCurrentNode->setStateID(scanResult.locDirs);
            vector<directions> vActions;
            //ustalamy liste dostepnych akcji
            scanResult.getScanResult(FRONT_DIR,bPassage);
            if (bPassage)	vActions.push_back(FRONT_DIR);
            scanResult.getScanResult(LEFT_DIR,bPassage);
            if (bPassage)	vActions.push_back(LEFT_DIR);
            scanResult.getScanResult(RIGHT_DIR,bPassage);
            if (bPassage)	vActions.push_back(RIGHT_DIR);
            m_ptrCurrentNode->setAllAction(vActions);
			//Log4Qt::Logger::logger("MazeKB")->warn(" Root Node wasn't initialized");
//			return;
        }
        else if(ptCurrentNode==NULL)
        {
            ptCurrentNode=&m_stKBRoot;
        }
        else if (crossRoadCounts==1 && m_stKBRoot.getStateID()!=scanResult.locDirs)
        {
            //to zupelnie inne drzewo do eksploracji
			//Log4Qt::Logger::logger("MazeKB")->warn("This KB tree start with different root - leaving teaching");
            return;
        }

        if ((ptNode = ptCurrentNode->getStateIDByAction(scanResult.robotChosenDir))!=NULL)
        {
			//Log4Qt::Logger::logger("MazeKB")->info(" Found node leading from this node");
            //znalezlismy taki wezel
        }
        else
        {
			//Log4Qt::Logger::logger("MazeKB")->info(" Didn't found node leading from this node");
//			return;
//			ptCurrentNode->addNodeToDir(scanResult.robotChosenDir,&ptNode);
        }
        ptCurrentNode->teach(scanResult.robotChosenDir,finalValue);
        if (ptNode)		ptCurrentNode=ptNode;
        else
        {
			//Log4Qt::Logger::logger("MazeKB")->fatal("ptNode is NULL - traversing through tree incorrect");
            exit(1);
        }
        ptNode=NULL;

        discount+= delta;
    }
#ifdef DEBUG_INFO
	ptCurrentNode = &m_stKBRoot;
	ptCurrentNode->getDirections(mDirsProbs,true);
	strDirs="Values ";
	for(IterMDirs=mDirsProbs.begin();
		IterMDirs!=mDirsProbs.end();
		IterMDirs++)
	{
		strDirs += QString("(%1)").arg(scanResult.translateLocID(DIR_TO_LOCATION(IterMDirs->first)));
		strDirs += QString(": %1, ").arg((double)IterMDirs->second);
	}
	//Log4Qt::Logger::logger("MazeKB")->info(strDirs);
	strDirs="Percents ";
	ptCurrentNode->getDirections(mDirsProbs);
	for(IterMDirs=mDirsProbs.begin(); IterMDirs!=mDirsProbs.end(); IterMDirs++)
	{
		strDirs += QString("(%1)").arg(scanResult.translateLocID(DIR_TO_LOCATION(IterMDirs->first)));
		strDirs += QString(": %1, ").arg((double)IterMDirs->second);
	}
	//Log4Qt::Logger::logger("MazeKB")->info(strDirs);

	//printDebugCrossRoadsList(listCrossRoads);
	//Log4Qt::Logger::logger("MazeKB")->info("BEGIN tree learning policy\n");
	strDirs=QString("  Crossroads count   %1").arg(crossRoadCounts);
	//Log4Qt::Logger::logger("MazeKB")->info(strDirs);
	//////////////////////////////////////////////////////////////////////////
    //ptCurrentNode = &KBTree;
    //ptCurrentNode->getDirections(mDirsProbs,false);
    //strDirs="Values ";
    //for(IterMDirs=mDirsProbs.begin();
    //        IterMDirs!=mDirsProbs.end();
    //        IterMDirs++)
    //{
    //    strDirs += QString("(%1)").arg(scanResult.translateLocID(DIR_TO_LOCATION(IterMDirs->first)));
    //    strDirs += QString(": %1, ").arg(IterMDirs->second);
    //}
    //qDebug()<<strDirs;
    //ptCurrentNode = &KBTree;
    //ptCurrentNode->getDirections(mDirsProbs);
    //strDirs="Percents ";
    //for(IterMDirs=mDirsProbs.begin();
    //        IterMDirs!=mDirsProbs.end();
    //        IterMDirs++)
    //{
    //    strDirs += QString("(%1)").arg(scanResult.translateLocID(DIR_TO_LOCATION(IterMDirs->first)));
    //    strDirs += QString(": %1, ").arg(IterMDirs->second);
    //}
    //qDebug()<<strDirs;
#endif
#ifdef DEBUG_INFO
	//Log4Qt::Logger::logger("MazeKB")->info("END tree learning policy\n");
#endif
//	ptCurrentNode=NULL;
    //storeKBTreeData();
};
//////////////////////////////////////////////////////////////////////////
directions CMazeKnowlegdeBase::chooseExit(LocationDirs stateID)
{
    static unsigned int before=1;
    double			probability;
    directions		result;

    unsigned int seed = (unsigned)time( NULL );
    seed =seed+seed%before++;
    srand(seed);
	probability=rand()%100;
    probability/=100.0;

    //LocationDirs locationID = scanResult.translateScanResultsToBitArray();
    //scanResult.locDirs=locationID;

    switch(currentMethodOfChoosingExits)
    {
    case staticOneLocationLearning:
//		result = m_mOneLocation[locationID].getLocation(probability);
        break;
    case treeOfLastDecisionPoints:
        result = chooseExitFromTree(stateID,probability);
        break;
    }

#ifdef DEBUG_INFO
	//Log4Qt::Logger::logger("MazeKB")->info("Choosing exit ");
	QString strInfo = "Probability	"+QString::number(probability);
	//Log4Qt::Logger::logger("MazeKB")->info(strInfo);
	strInfo = "Result		"+QString::number(result);
	//Log4Qt::Logger::logger("MazeKB")->info(strInfo);
#endif

    return result;
}
directions CMazeKnowlegdeBase::chooseExitFromTree(LocationDirs stateID,double probability )
{
    directions		choosenDir;
    CKBTreeNode * ptNewNode;
    Q_ASSERT(m_ptrCurrentNode!=NULL);
    QString strlocID;
	CScanResults scan;
	if (m_ptrCurrentNode->getStateID() == LOCATION_EMPTY)
    {
        //bool bPassage;
        m_ptrCurrentNode->setStateID(stateID);
        //vector<directions> vActions;
        //ustalamy liste dostepnych akcji
        //scanResult.getScanResult(FRONT_DIR,bPassage);
        //if (bPassage)	vActions.push_back(FRONT_DIR);
        //scanResult.getScanResult(LEFT_DIR,bPassage);
        //if (bPassage)	vActions.push_back(LEFT_DIR);
        //scanResult.getScanResult(RIGHT_DIR,bPassage);
        //if (bPassage)	vActions.push_back(RIGHT_DIR);
        m_ptrCurrentNode->setAllAction(stateID.Directions());

        strlocID = " Ustawiamy parametry aktualnego wezla na ";
        strlocID += scan.translateLocID(stateID);
		//Log4Qt::Logger::logger("MazeKB")->info(strlocID);
	}
    choosenDir = m_ptrCurrentNode->getActiondID(probability);
    strlocID = "Lokacja ma ";
    strlocID += scan.translateLocID(stateID);
    strlocID += " a wybrano ";
    strlocID += scan.translateLocID(DIR_TO_LOCATION(choosenDir));
	//Log4Qt::Logger::logger("MazeKB")->info(strlocID);
    //Q_ASSERT_X(scanResult.locDirs & DIR_TO_LOCATION(choosenDir) > 0,strlocID.toStdString().c_str(),"");

    ptNewNode = m_ptrCurrentNode->getStateIDByAction(choosenDir);
    Q_ASSERT(ptNewNode!=NULL);

    m_ptrCurrentNode = ptNewNode;
	//Log4Qt::Logger::logger("MazeKB")->info("Wybrano nowy wezel");

    return choosenDir;
}
//directions CKnowlegdeBase::chooseFromOneLocationProbability(int /*locationID*/)
//{
//    //QVector<double>	vExits;
//    //int				probability;
//    //int				result;
//
//    //srand( (unsigned)time( NULL ) );
//    //probability=rand()%100;
//
//    //vExits = m_mOneLocation[locationID];
//
//    //result = vExits[FRONT_DIR];
//    //if (probability<=result)
//    //{
//    //	return FRONT_DIR;
//    //}
//    //else
//    //{
//    //	result+=vExits[LEFT_DIR];
//    //	if (probability<=result)
//    //	{
//    //		return LEFT_DIR;
//    //	}
//    //	else
//    //	{
//    //		return RIGHT_DIR;
//    //	}
//    //}
//    return FRONT_DIR;
//}
//
////*******************************************************************//
//void CKnowlegdeBase::storeKBTreeData()
//{
////	archiveKBList.push_back(KBTree);
//}
//int  CKnowlegdeBase::getExplorationsCount()
//{
//    Q_CHECK_PTR(currentExperiment);
//    return currentExperiment->getExplorationsCount();
//}
//void CKnowlegdeBase::addExplorationResult(CExplorationResult & rExploration)
//{
//    Q_CHECK_PTR(currentExperiment);
//    currentExperiment->addExplorationResult(rExploration);
//    currentNode=&KBTree;
//}
//void CKnowlegdeBase::addKBTree()
//{
//    Q_CHECK_PTR(currentExperiment);
//    //currentExperiment->addKBTree(KBTree);
//}
//void  CKnowlegdeBase::getCurrentExperiment(CExperiment & rExperiment)
//{
//    rExperiment=*currentExperiment;
//}
//CExperiment * CKnowlegdeBase::getCurrentExperiment()
//{
//    return currentExperiment;
//}
//CKBTreeNode * CKnowlegdeBase::getKBTreeData(vector<CScanResults> & listCrossRoads)
//{
//    CScanResults scanResult;
//    vector<CScanResults>::const_iterator iterCross;
//    CKBTreeNode *	ptNode=&KBTree;
//    if (listCrossRoads.size()==0)
//        return NULL;
////	LocationDirs locationID;
//
//    iterCross=listCrossRoads.begin();
//    while(ptNode!=NULL && iterCross!=listCrossRoads.end())
//    {
//        CKBTreeNode *	ptNode1=NULL;
//        scanResult = *iterCross;
////		locationID = translateScanResultsToBitArray(scanResult);
//        if (ptNode->getStateID()!=scanResult.locDirs)
//            return NULL;
//        if (!(ptNode1 = ptNode->getStateIDByAction(scanResult.robotChosenDir)))
//        {
//            return NULL;
//        }
//        else
//        {
//            iterCross++;
//            if (iterCross==listCrossRoads.end())
//            {
//                return ptNode;
//            }
//            ptNode=ptNode1;
//        }
//    }
//    return ptNode;
//}
//CKBTreeNode * CKnowlegdeBase::getKBTreeData(int nr, vector<CScanResults> & listCrossRoads)
//{
//    CScanResults scanResult;
//    vector<CScanResults>::const_iterator iterCross;
//    CKBTreeNode *	ptNode=NULL;//&archiveKBList[nr];
//    if (listCrossRoads.size()==0)
//        return NULL;
//
//    iterCross=listCrossRoads.begin();
//
//    //ptNode=&KBTree;
//    ptNode= &currentExperiment->getArchiveKBTree(nr);
//    while(ptNode!=NULL && iterCross!=listCrossRoads.end())
//    {
//        CKBTreeNode *	ptNode1=NULL;
//        scanResult = *iterCross;
//        if (ptNode->getStateID()!=scanResult.locDirs)
//            return NULL;
//        if (!(ptNode1 = ptNode->getStateIDByAction(scanResult.robotChosenDir)))
//        {
//            return NULL;
//        }
//        else
//        {
//            iterCross++;
//            if (iterCross==listCrossRoads.end())
//            {
//                return ptNode;
//            }
//            ptNode=ptNode1;
//        }
//    }
//    return ptNode;
//}
//QString LocationDirs2String(LocationDirs lDir)
//{
//    switch(lDir)
//    {
//    case LOCATION_EMPTY:
//        return "EMPTY";
//    case LOCATION_FRONT:
//        return "FRONT";
//    case LOCATION_LEFT:
//        return "LEFT";
//    case LOCATION_RIGHT:
//        return "RIGHT";
//    case LOCATION_BACK:
//        return "BACK";
//    case LOCATION_LR:
//        return "LEFT, RIGTH";
//    case LOCATION_FL:
//        return "LEFT, FRONT";
//    case LOCATION_FR:
//        return "RIGHT, FRONT";
//    case LOCATION_FLR:
//        return "LEFT, RIGHT, FRONT";
//    }
//    return "";
//}
//
//void CKnowlegdeBase::printDebugCrossRoadsList(vector<CScanResults> &listCrossRoads)
//{
//    vector<CScanResults>::iterator iterCross;
//    CScanResults scanResult;
//    int count=0;
//    QString strDir;
//
//    for(iterCross=listCrossRoads.begin(); iterCross!=listCrossRoads.end(); iterCross++)
//    {
//        scanResult=*iterCross;
//        qDebug()<<count<<": Pos X:"<<scanResult.robotPos.posX<<"  Y:"<<scanResult.robotPos.posY;
//        qDebug()<<"    Location Dirs "<<LocationDirs2String(scanResult.locDirs);
//        strDir=ROBOT_DIRECTION_STRING(scanResult.robotChosenDir);
//        qDebug()<<"    Choosen Dir "<<strDir;
//        count++;
//    }
//}
//void CKnowlegdeBase::saveKnowledgeBase(QTextStream * )
//{
//    /*	QList<CExperiment>::iterator	iterExperiment;
//    	vector<CKBTreeNode>::iterator	iterKB;		//list of all experiment which were used to teach this Knowledge Base
//
//    	(*pStream)<<"KB_DATA_START\n";
//    	for(iterExperiment=vectorOfExperiments.begin();iterExperiment!=vectorOfExperiments.end();iterExperiment++)
//    	{
//    		iterExperiment->saveExperiment(pStream);
//    	}
//    	(*pStream)<<"KB_NODES_DATA_START\n";
//    	for(iterKB=archiveKBList.begin();iterKB!=archiveKBList.end();iterKB++)
//    	{
//    		(*pStream)<<"ROOT_NODE\n";
//    		iterKB->saveNodesChildren(pStream);
//    		(*pStream)<<"\n";
//    	}
//    	(*pStream)<<"KB_DATA_END\n";*/
//}
//void CKnowlegdeBase::loadKnowledgeBase(QTextStream * )
//{
//    return;
//    /*	QString strLine;
//    	QList<CExperiment>::iterator	iterExperiment;
//    	vector<CKBTreeNode>::iterator	iterKB;		//list of all experiment which were used to teach this Knowledge Base
//
//    	while(strLine.isEmpty())
//    		strLine=pStream->readLine();
//    	if (strLine!="KB_DATA_START")
//    		qFatal("Error during file reading");
//    	while(strLine!="EXPERIMENT_DATA_END")
//    	{
//    		CExperiment experiment;
//    		strLine=experiment.loadExperiment(pStream);
//    		vectorOfExperiments.push_back(experiment);
//    	}
//    	while(strLine!="ROOT_NODE")
//    		strLine=pStream->readLine();
//    	if (strLine!="ROOT_NODE")
//    		qFatal("Error during file reading");
//    	do
//    	{
//    		CKBTreeNode node;
//    		node.loadNodesChildren(pStream);
//    		archiveKBList.push_back(node);
//    		strLine="";
//    		do
//    		{
//    			strLine=pStream->readLine();
//    		} while(strLine.isEmpty());
//    	}
//    	while(strLine!="KB_DATA_END");
//    	KBTree = archiveKBList.back();*/
//}
//void CKnowlegdeBase::CollapseExperiments()
//{
//
//}
