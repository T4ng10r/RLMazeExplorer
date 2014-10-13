#ifndef ENVIROMENT_H
#define ENVIROMENT_H
//#include <QtGui/QStringListModel>
//#include <QtGui/QTableWidget>
#include <QtDebug>
#include <Maze/maze.h>
#include <Data/experiment/experiment_settings.h>
#include <Data/experiment/CMazeExplorationResult.h>
#define DEBUG_INFO

class robot;
class CMazeKnowlegdeBase;

//Class which will monitor agent position and movement in maze
//Only responsibility - inform agent about what he see and where he can move from current position
class CEnviroment : public QObject
{
    Q_OBJECT
public:
	CEnviroment(void);
	~CEnviroment(void);

	CMazeExplorationResult getExplorationResults() { return m_stExplorationResult; }
	void setExperimentSettings(experiment_settings val) { m_stExperimentSettings = val; }
	void setKnowlegdeBase(CMazeKnowlegdeBase * ptrKB)		{ m_ptrKnowledgeBase = ptrKB;	}
	void setMaze(const maze &val);
	//////////////////////////////////////////////////////////////////////////
	// exploration methods
	void startSingleExploring();
	void getRobotPos(unsigned int &X, unsigned int &Y);

	//QTableWidget *		explorationResult;
	void debugPrintDirections();
	void debugPrintMaze();
public Q_SLOTS:
	//void robotNextMove();
Q_SIGNALS:
	void robotFinished(CMazeExplorationResult &lRoute);
	void robotBeforeMove(CScanResults *scanResult);
	//    void nextExplorationInExperiment();
	//    void redrawMaze();
	//    void setMazeLimits(int,int);
	//    will set all experiment values to m_ExperimentSettings and start performing it
	//    void	onStartExperiment(CExperimentSettings &m_ExperimentSettings);
protected Q_SLOTS:
	//for agent - his performing scan of location
	void	onRobotScan(CScanResults *scanResult);
	//for agent - agent moves 
	void	onRobotMoved();
	//for agent - agent rotates
	void	onRobotRotated(bool bRight,bool bBack);
	//for agent - to check if robot has reched target
	void	onRobotIfInExit(bool &bIfInExit);
protected:
	//void	save(QString strPath);
	//void	load(QString strPath);

	void	setRobotToStart();			//ustaw robota w pozycji startowej
	void	rotateScanResults(CScanResults & scanResult,eRobotDir dir);
	void	afterFinishedExploration();
	//
	void	createRobotRouteInfo();
protected:
	maze					m_stMaze;
	//experiment settings - like robot start position, end points and maze params
	experiment_settings		m_stExperimentSettings;
	//robot/agent - he will perform experiment
	robot	*				m_ptrRobot;
	//location in which robot is currently
	location				m_stCurrentLocation;
	//current robot directions facing
	eRobotDir				m_iRobotDir;
	//current robot position in maze
	QPoint					m_iRobotPos;
	CMazeExplorationResult	m_stExplorationResult;				//result of current exploration process

	//CExperiment				currentExperiment;

	CMazeKnowlegdeBase		*	m_ptrKnowledgeBase;		//baza wiedzy
	CScanResults		*	currentScanResults;
};
#endif
