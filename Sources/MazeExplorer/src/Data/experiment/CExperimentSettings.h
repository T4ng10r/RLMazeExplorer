#ifndef EXPERIMENTSETTINGS_HPP
#define EXPERIMENTSETTINGS_HPP

#include <list>
#include <QtCore/QPoint>
#include <QtCore/QString>
#include <Data/CRobotPostion.h>
#include <Maze/maze_settings.h>

//stores list of parameters about experiment - used to initialize 
//CExperiment and CEnviroment class
class experiment_settings
{
public:
	experiment_settings(void);
	~experiment_settings(void);
	void reset();
public:
	int					repeat_count;
	maze_settings		mazeSettings;
	CRobotPostion		startPosition;
	std::list<QPoint>	lFinishPositions;
	double				fPenaltyValue;
	double				fPriceValue;
	QString				sLoadKBPath;
	QString				sSaveKBPath;
};
#endif
