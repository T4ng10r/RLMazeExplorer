#pragma once
#include <KnowledgeBase/CKnowlegdeBase.h>
#include <Data/experiment/CMazeExplorationResult.h>
#include <Data/experiment/EnviromentVariables.h>

#include <vector>
#include <map>
#include <string>

class maze_knowlegde_base : public CKnowlegdeBase<LocationDirs, directions>
{
public:
    maze_knowlegde_base(void);
    ~maze_knowlegde_base(void);
	//resets entire KB (quantities and KBRoot)
    void ResetKB();
	//sets current node to RootNode 
	void ResetRootNode();
	CKBTreeNode * getCurrentNode();

	CMazeExplorationResult * getCurrentExplorationResult() const { return m_ptrCurrentExplorationResult; }
	void addExplorationResult(CMazeExplorationResult * val)
	{

	}
	void setCurrentExplorationResult(CMazeExplorationResult * val) { m_ptrCurrentExplorationResult = val; }

    void teach(double value,bool bReward);
//	//
    directions chooseExit(LocationDirs stateID);
//    /********************************************/
//    void NewExperiment(CExperimentSettings & expSeting);	//run this method evetime before processing new experiment
//    void FinishCurrentExperiment();							//translate
//    void loadKnowledgeBase(QTextStream * pStream);
//    void saveKnowledgeBase(QTextStream * pStream);
//    /********************************************/	//processing data stored inside experiment archive
//    /********************************************/	//processing data stored inside experiment archive
//
//	CKBTreeNode * getCurrentNode();
//
//
//    int  getExplorationsCount();	//get how many explorations is stored inside current experiment
//    void  getCurrentExperiment(CExperiment & rExperiment);	//get how many explorations is stored inside current experiment
//    CExperiment * getCurrentExperiment();
//    void addExplorationResult(CExplorationResult & rExploration);	//add this exploration result to current experiment
//    void addKBTree();
//    CKBTreeNode * getKBTreeData(vector<CScanResults> & listCrossRoads);
//    CKBTreeNode * getKBTreeData(int nr, vector<CScanResults> & listCrossRoads);
//    void CollapseExperiments();
//    int getExperimentsCount();
//    void CreateKnowledgeTree();
//    //
protected:
//    void storeKBTreeData();
//    void printDebugCrossRoadsList(vector<CScanResults> &listCrossRoads);
//    directions chooseFromOneLocationProbability(int probability);
//    int chooseFromLocationsList(int probability);
//    void staticLearningPolicy(CExplorationResult *lastExplorationResult, double value, bool bReward);
	directions chooseExitFromTree(LocationDirs stateID,double probability );
	//void treeLearningPolicy(CMazeExplorationResult *lastExplorationResult, double value, bool bReward);
	void treeLearningPolicy(CExplorationResult<LocationDirs,directions> *lastExplorationResult, double value, bool bReward);
	//void treeLearningPolicy( CExplorationResult & explorationResult, double value, bool bReward);

	std::vector<CMazeExplorationResult>		vectorOfExplorations;		//list of all experiment which were used to teach this Knowledge Base
	//vector<CExperiment>			vectorOfExperiments;		//list of all experiment which were used to teach this Knowledge Base
    //vector<CKBTree>			    vectorOfKBTrees;		//list of all experiment which were used to teach this Knowledge Base
	//pointer to currently  which is currently being proccessed
    CMazeExplorationResult	*		m_ptrCurrentExplorationResult;
	choosingExitsMethod			currentMethodOfChoosingExits;

    //parametry wyboru tylko jednej lokacji
    //klucz - ID lokacji skanowanej
    //dane - prawdopobobienstwa wyboru kt�rego� z dost�pnych wyj��
//	map<LocationID,CKBLocationData>	m_mOneLocation;

	//vector<CKBTreeNode>			archiveKBList;		//list of all experiment which were used to teach this Knowledge Base
    //CKBTreeNode *				currentNode;
    //CKBTree 				KBTree;
    //CKBTreeNode				KBRoot;
    //CKBTreeNode *			currentNode;

    unsigned int m_iExplorationQuantity;	//ilosc przejsc robota
    unsigned int m_iExplorationSucces;		//ilosc przejsc robota
    unsigned int m_iExplorationFails;		//ilosc przejsc robota
};

typedef std::shared_ptr<maze_knowlegde_base> maze_knowlegde_base_handle;
