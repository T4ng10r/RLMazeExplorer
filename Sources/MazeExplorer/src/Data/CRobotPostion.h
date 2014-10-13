#pragma once
#include <Data/experiment/EnviromentVariables.h>
#include <QPoint>
class CRobotPostion
{
public:
	CRobotPostion(void)
	{
		posX=0;
		posY=0;
		dir=ROBOT_NORTH_DIR;
	}
	CRobotPostion(QPoint pos)
	{
		posX=pos.x();
		posY=pos.y();
		dir=ROBOT_NORTH_DIR;
	}
	void operator=(QPoint pos)
	{
		posX=pos.x();
		posY=pos.y();
	}
public:	
	int			posX;
	int			posY;
	eRobotDir	dir;
};
