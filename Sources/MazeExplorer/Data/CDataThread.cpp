#include <Data/CDataThread.h>
#include <Maze/CMazeGenerator.h>
#include <QString>
#include <log4qt/logger.h>

CDataThread::CDataThread(void){}
void CDataThread::run()
{
	exec();
}

void CDataThread::onPerformMazeGeneration(CMazeSettings & xMazeSettings)
{

	CMazeGenerator mazeGen;
	mMaze = mazeGen.GenerateMaze(xMazeSettings);

	QString strInfo;
	strInfo ="Maze generated ("+QString::number(xMazeSettings.uiMaxX)+","+QString::number(xMazeSettings.uiMaxY)+")";
	Log4Qt::Logger::logger("Process")->info(strInfo);

	emit mazeHasBeenGenerated(&mMaze);

	////m_stExperimentManager.getCurrentExperiment().setMazeData(maze);
	//m_stExperiment.setMazeData(maze);
	//m_ptrMazeScene->setMaze(maze);
	//m_ptrExperimentParamsDlg->onExperimentSettingsChanged();
	//bMazeUpdated=true;
	////m_stExperimentManager.getCurrentExperiment().setMazeData(maze);
	//m_stExperiment.setMazeData(maze);
}
