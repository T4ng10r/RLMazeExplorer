#pragma once
#include <vector>
#include <Data/Experiment/CExperimentSettings.h>
#include <Data/Experiment/CMazeExplorationResult.h>
#include <Data/CScanResults.h>
#include <Maze/CMaze.h>
#include <Data/CMazeKnowlegdeBase.h>
#include <QtCore/QObject.h>

using namespace std;
class CEnviroment;

//////////////////////////////////////////////////////////////////////////
class CExperiment : public QObject
{
	Q_OBJECT
public:
    CExperiment(void);
    ~CExperiment(void);
	void setMazeData(const CMaze & xMazeSource);
	CMaze& getMazeData();
	void setExperimentSettings(const CExperimentSettings & xExperimentSettings);
	void startExperiment();
	//////////////////////////////////////////////////////////////////////////
	void operator=(const CExperiment & experimentDest);
	//////////////////////////////////////////////////////////////////////////
    void increseSuccessCounter();
    void increseFailsCounter();
    unsigned int getSuccessCounter();
    unsigned int getFailsCounter();
	//////////////////////////////////////////////////////////////////////////
	void addExplorationResult(CMazeExplorationResult & rExploration);
	int  getExplorationsCount();
    bool getExplorationResult(uint nr, CMazeExplorationResult & lastExplorationResult);
	CMazeExplorationResult &getLastExplorationResult();
	//////////////////////////////////////////////////////////////////////////	
    QString loadExperiment(QTextStream *pStream);
    void saveExperiment(QTextStream *pStream);
    //CKBTree & getArchiveKBTree(int nr);
    //void addKBTree(CKBTree & treeNode);
signals:
	void robotBeforeMove(CScanResults *scanResult);
	void robotNextMove();
public slots:
	void onNextRobotMove();
protected:
    time_t	experimentDuration;
    unsigned int m_iExplorationSucces;		//how many time exploration was successful
    unsigned int m_iExplorationFails;		//how many time exploration was failure
    CMaze						m_stMazeData;
    CExperimentSettings			m_stExperimentSettings;
	CEnviroment * 				m_ptrEnviroment;

    vector<CMazeExplorationResult>	explorationResults;	//lista pozycji robota dla ka¿dego przejœcia w ramach danego eksperymentu
	CMazeKnowlegdeBase			m_cKnowledgeBase;
 //   vector<CKBTree>	            explorationsKBTree;	//lista pozycji robota dla ka¿dego przejœcia w ramach danego eksperymentu

};
