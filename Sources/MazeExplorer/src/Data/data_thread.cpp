#include <Data/data_thread.h>
#include <Maze/maze_generator.h>
#include <QString>
#include <Tools/loggers.h>
#include <QThread>
#include <boost/format.hpp>
#include <Data/experiment/experiment.h>

std::shared_ptr<data_thread> data_thread::instance;

struct data_thread_private
{
public:	
	maze_interface_type maze_data;
	experiment_type experiment_;
};


data_thread::data_thread() : pimpl(new data_thread_private())
{
	QThread* thread = new QThread;
	this->moveToThread(thread);
	thread->start();
}
data_thread::~data_thread()
{}

data_thread_type data_thread::getInstance()
{
	if (!instance)
	{
		if (!instance)
		{
			instance.reset(new data_thread());
		}
	}
	return instance;
}
maze_interface_type data_thread::get_maze()
{
	return pimpl->maze_data;
}
void data_thread::on_maze_generated(maze_settings xMazeSettings)
{
	maze_generator mazeGen;
	pimpl->maze_data = mazeGen.generate_maze(xMazeSettings);

	printLog(eDebug, eDebugLogLevel, str(boost::format("Maze generated (%1%, %2%) ") 
	                                     % xMazeSettings.size_x % xMazeSettings.size_y));

	Q_EMIT maze_generated();
}
void data_thread::on_start_experiment(experiment_settings& settings)
{
	pimpl->experiment_.reset(new experiment(settings, pimpl->maze_data));
	pimpl->experiment_->start();
	//m_stExperimentManager.getCurrentExperiment().startExperiment();
}
