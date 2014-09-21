#include <Data/data_thread.h>
#include <Maze/maze_generator.h>
#include <QString>
#include <Tools/loggers.h>
#include <QtCore/QThread>

boost::shared_ptr<data_thread> data_thread::instance;

data_thread::data_thread(void) 
//: privPart(new CDataThreadPrivate(this))
{
	QThread* thread = new QThread;
	this->moveToThread(thread);
	thread->start();
}

boost::shared_ptr<data_thread> data_thread::getInstance()
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

void data_thread::onPerformMazeGeneration(maze_settings xMazeSettings)
{
	maze_generator mazeGen;
	maze_data = mazeGen.generate_maze(xMazeSettings);

	QString strInfo;
	strInfo = "Maze generated (" + QString::number(xMazeSettings.size_x) + "," + QString::number(xMazeSettings.size_y) + ")";
	//Log4Qt::Logger::logger("Process")->info(strInfo);

	Q_EMIT maze_generated();

	////m_stExperimentManager.getCurrentExperiment().setMazeData(maze);
	//m_stExperiment.setMazeData(maze);
	//m_ptrMazeScene->setMaze(maze);
	//m_ptrExperimentParamsDlg->onExperimentSettingsChanged();
	//bMazeUpdated=true;
	////m_stExperimentManager.getCurrentExperiment().setMazeData(maze);
	//m_stExperiment.setMazeData(maze);
}
boost::shared_ptr<maze_interface> data_thread::get_maze()
{
	return maze_data;
}
