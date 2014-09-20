#pragma once
#include <Data/Experiment/EnviromentVariables.h>
#include <QPoint>
class CRobotPostion
{
public:
	CRobotPostion::CRobotPostion(void)
	{
		posX=0;
		posY=0;
		dir=ROBOT_NORTH_DIR;
	}
	CRobotPostion::CRobotPostion(QPoint pos)
	{
		posX=pos.x();
		posY=pos.y();
		dir=ROBOT_NORTH_DIR;
	}
	void CRobotPostion::operator=(QPoint pos)
	{
		posX=pos.x();
		posY=pos.y();
	}
    int			posX;
    int			posY;
    eRobotDir	dir;
};
