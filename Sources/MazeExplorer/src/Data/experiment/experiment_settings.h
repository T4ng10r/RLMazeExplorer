#pragma once

#include <list>
#include <QtCore/QPoint>
#include <QtCore/QString>
#include <Data/robot_postion.h>
#include <Maze/maze_settings.h>

typedef std::pair<unsigned int,unsigned int> point;

//stores list of parameters about experiment - used to initialize 
//CExperiment and CEnviroment class
class experiment_settings
{
public:
	experiment_settings();
	~experiment_settings();
	void reset();
public:
	int					repeat_count;
	maze_settings		mazeSettings;
	robot_postion		startPosition;
	std::list<point>	target_positions;
	std::list<QPoint> lFinishPositions;
	double				fPenaltyValue;
	double				fPriceValue;
	QString				sLoadKBPath;
	QString				sSaveKBPath;
};
