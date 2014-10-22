#pragma once
#include <vector>
#include <Data/experiment/experiment_settings.h>
#include <Data/experiment/CMazeExplorationResult.h>
#include <Data/CScanResults.h>
#include <Maze/maze.h>
#include <Data/CMazeKnowlegdeBase.h>
#include <QObject>

using namespace std;
class enviroment;

class experiment_private;

//////////////////////////////////////////////////////////////////////////
class experiment : public QObject
{
	Q_OBJECT
public:
	experiment();
	experiment(experiment_settings & settings, maze_interface_type maze_);
	~experiment();
	void on_set_maze_data(maze_interface_type maze_source);

	//maze_interface_type getMazeData();
	void setExperimentSettings(const experiment_settings & xExperimentSettings);
	void start();
	//////////////////////////////////////////////////////////////////////////
	//void operator=(const experiment & experimentDest);
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
	void robotBeforeMove(scan_results_handle scanResult);
	void robotNextMove();
public Q_SLOTS:
	void on_next_robot_move();
protected:
	std::unique_ptr<experiment_private> pimpl;
};

typedef std::shared_ptr<experiment> experiment_type;

