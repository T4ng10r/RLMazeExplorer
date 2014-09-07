#pragma once
#include <vector>
#include <QtCore/QThread>

#include <Maze/CMazeSettings.h>
#include <Maze/CMaze.h>

class CDataThread : public QThread
{
	Q_OBJECT
public:
    CDataThread(void);
	void run();
public slots:
	//call this to generate new maze according to given maze settings
	void onPerformMazeGeneration(CMazeSettings & xMazeSettings);
signals:
	//emited when maze has been generated 
	void mazeHasBeenGenerated(CMaze *);

protected:
	CMaze mMaze;

};
