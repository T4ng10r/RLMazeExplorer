#pragma once
#include <QtTest/QtTest>
#include "TestRunner.h"
#include <GUI/experiment_parameters/experiment_maze_params_dlg.h>

class experiment_maze_params_dlg_test : public QObject
{
	Q_OBJECT
public:
	experiment_maze_params_dlg_test();
	virtual ~experiment_maze_params_dlg_test();
public Q_SLOTS:
	void set_maze_settings_1();
	void get_maze_settings_1();
	void generate_maze();
//void set_maze_settings(maze_settings & stMazeSettings);
//void get_maze_settings(maze_settings & stMazeSettings);
//void generate_maze(maze_settings);

};
