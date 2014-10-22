#pragma once
#include <vector>
#include <QObject>

#include <Maze/maze_settings.h>
#include <Maze/maze_interface.h>
#include <memory>
#include <Data/experiment/experiment_settings.h>

class data_thread;
struct data_thread_private;

typedef std::shared_ptr<data_thread> data_thread_type;

class data_thread : public QObject
{
	Q_OBJECT
	data_thread();
	static data_thread_type instance;
public:
	~data_thread();
	static data_thread_type getInstance();
	maze_interface_type get_maze();
public Q_SLOTS:
	//call this to generate new maze according to given maze settings
	void on_maze_generated(maze_settings xMazeSettings);
	void on_start_experiment(experiment_settings& settings);
Q_SIGNALS:
	//emited when maze has been generated 
	void maze_generated();

protected:
	std::unique_ptr<data_thread_private> pimpl;
};

#define gDataThread data_thread::getInstance() 
