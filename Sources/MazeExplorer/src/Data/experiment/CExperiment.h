#pragma once
#include <vector>
#include <Data/experiment/CExperimentSettings.h>
#include <Data/experiment/CMazeExplorationResult.h>
#include <Data/CScanResults.h>
#include <Maze/maze.h>
#include <Data/CMazeKnowlegdeBase.h>
#include <QObject>

using namespace std;
class CEnviroment;

//////////////////////////////////////////////////////////////////////////
class CExperiment : public QObject
{
	Q_OBJECT
public:
	CExperiment(void);
	~CExperiment(void);
	void on_set_maze_data(const maze & xMazeSource);
	maze& getMazeData();
	void setExperimentSettings(const experiment_settings & xExperimentSettings);
	void startExperiment();
	//////////////////////////////////////////////////////////////////////////
	void operator=(const CExperiment & experimentDest);
	//////////////////////////////////////////////////////////////////////////
	void increseSuccessCounter();
	void increseFailsCounter();
	unsigned int getSuccessCounter();
	unsigned int getFailsCounter();
	//////////////////////////////////////////////////////////////////////////
	void addExplorationResult(const CMazeExplorationResult & rExploration);
	int  getExplorationsCount();
	bool getExplorationResult(uint nr, CMazeExplorationResult & lastExplorationResult);
	CMazeExplorationResult &getLastExplorationResult();
	//////////////////////////////////////////////////////////////////////////	
	QString loadExperiment(QTextStream *pStream);
	void saveExperiment(QTextStream *pStream);
	//CKBTree & getArchiveKBTree(int nr);
	//void addKBTree(CKBTree & treeNode);
Q_SIGNALS:
	void robotBeforeMove(CScanResults *scanResult);
	void robotNextMove();
public Q_SLOTS:
	void onnext_robot_move();
protected:
	time_t	experimentDuration;
	unsigned int m_iExplorationSucces;		//how many time exploration was successful
	unsigned int m_iExplorationFails;		//how many time exploration was failure
	maze						m_stMazeData;
	experiment_settings			m_stExperimentSettings;
	CEnviroment * 				m_ptrEnviroment;
	vector<CMazeExplorationResult>	explorationResults;	//lista pozycji robota dla ka�dego przej�cia w ramach danego eksperymentu
	CMazeKnowlegdeBase			m_cKnowledgeBase;
	//   vector<CKBTree>	            explorationsKBTree;	//lista pozycji robota dla ka�dego przej�cia w ramach danego eksperymentu
};
