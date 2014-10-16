#pragma once
#include <Data/experiment/EnviromentVariables.h>
#include <QPoint>
class robot_postion
{
public:
	robot_postion(void)
	{
		posX=0;
		posY=0;
		dir=ROBOT_NORTH_DIR;
	}
	robot_postion(QPoint pos)
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
