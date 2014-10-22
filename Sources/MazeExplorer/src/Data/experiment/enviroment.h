#ifndef ENVIROMENT_H
#define ENVIROMENT_H
//#include <QtGui/QStringListModel>
//#include <QtGui/QTableWidget>
#include <memory>
#include <QtDebug>
#include <Maze/maze_interface.h>
#include <Data/experiment/experiment_settings.h>
#include <Data/experiment/CMazeExplorationResult.h>
#include <Data/CMazeKnowlegdeBase.h>

#define DEBUG_INFO

class robot;
class enviroment_private;

//Class which will monitor agent position and movement in maze
//Only responsibility - inform agent about what he see and where he can move from current position
class enviroment : public QObject
{
    Q_OBJECT
public:
	enviroment(experiment_settings settings, maze_interface_type maze, maze_knowlegde_base_handle kb);
	~enviroment(void);

	CMazeExplorationResult getExplorationResults();
	//void setExperimentSettings(experiment_settings val);
	//void setKnowlegdeBase(maze_knowlegde_base_handle ptrKB);
	//void setMaze(const maze &val);
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
	void robotBeforeMove(scan_results_handle scanResult);
	//    void nextExplorationInExperiment();
	//    void redrawMaze();
	//    void setMazeLimits(int,int);
	//    will set all experiment values to m_ExperimentSettings and start performing it
	//    void	onStartExperiment(CExperimentSettings &m_ExperimentSettings);
protected Q_SLOTS:
	//for agent - his performing scan of location
	void	onRobotScan(scan_results_handle scanResult);
	//for agent - agent moves 
	void	onRobotMoved();
	//for agent - agent rotates
	void	onRobotRotated(bool bRight,bool bBack);
	//for agent - to check if robot has reched target
	void	onRobotIfInExit(bool &bIfInExit);
protected:
	friend class enviroment_private;
	std::unique_ptr<enviroment_private> pimpl;
};
#endif
