#include <Data/CDataThread.h>
#include <Maze/maze_generator.h>
#include <QString>
#include <Tools/loggers.h>

CDataThread::CDataThread(void){}
void CDataThread::run()
{
	exec();
}

void CDataThread::onPerformMazeGeneration(maze_settings & xMazeSettings)
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
boost::shared_ptr<maze_interface> CDataThread::get_maze()
{
	return maze_data;
}
