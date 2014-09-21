#pragma once
#include <vector>
#include <QObject>

#include <Maze/maze_settings.h>
#include <Maze/maze.h>
#include <boost/shared_ptr.hpp>

class data_thread : public QObject
{
	Q_OBJECT
	data_thread(void);
	static boost::shared_ptr<data_thread> instance;
public:
	static boost::shared_ptr<data_thread> getInstance();
	boost::shared_ptr<maze_interface> get_maze();
public Q_SLOTS:
	//call this to generate new maze according to given maze settings
	void onPerformMazeGeneration(maze_settings xMazeSettings);
Q_SIGNALS:
	//emited when maze has been generated 
	//void mazeHasBeenGenerated(maze *);
	void maze_generated();

protected:
	boost::shared_ptr<maze_interface> maze_data;
};

#define gDataThread data_thread::getInstance() 
