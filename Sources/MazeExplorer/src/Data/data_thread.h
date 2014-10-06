#pragma once
#include <vector>
#include <QObject>

#include <Maze/maze_settings.h>
#include <Maze/maze.h>
#include <memory>

class data_thread : public QObject
{
	Q_OBJECT
	data_thread(void);
	static std::shared_ptr<data_thread> instance;
public:
	static std::shared_ptr<data_thread> getInstance();
	maze_interface_type get_maze();
public Q_SLOTS:
	//call this to generate new maze according to given maze settings
	void onPerformMazeGeneration(maze_settings xMazeSettings);
Q_SIGNALS:
	//emited when maze has been generated 
	//void mazeHasBeenGenerated(maze *);
	void maze_generated();

protected:
	maze_interface_type maze_data;
};

#define gDataThread data_thread::getInstance() 
