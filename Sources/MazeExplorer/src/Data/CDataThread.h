#pragma once
#include <vector>
#include <QtCore/QThread>

#include <Maze/maze_settings.h>
#include <Maze/maze.h>
#include <boost/shared_ptr.hpp>

class CDataThread : public QThread
{
	Q_OBJECT
public:
    CDataThread(void);
	void run();
	boost::shared_ptr<maze_interface> get_maze();
public Q_SLOTS:
	//call this to generate new maze according to given maze settings
	void onPerformMazeGeneration(maze_settings & xMazeSettings);
Q_SIGNALS:
	//emited when maze has been generated 
	//void mazeHasBeenGenerated(maze *);
	void maze_generated();

protected:
	boost::shared_ptr<maze_interface> maze_data;
};
