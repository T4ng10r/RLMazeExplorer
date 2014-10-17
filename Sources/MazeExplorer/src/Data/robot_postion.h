#pragma once
#include <Data/experiment/EnviromentVariables.h>
#include <QPoint>
class robot_postion
{
public:
	robot_postion(void)
	{
		pos_x=0;
		pos_y=0;
		dir=ROBOT_NORTH_DIR;
	}
	robot_postion(QPoint pos)
	{
		pos_x=pos.x();
		pos_y=pos.y();
		dir=ROBOT_NORTH_DIR;
	}
	robot_postion(std::pair<unsigned int,unsigned int> pos, eRobotDir dir_ = ROBOT_NORTH_DIR)
	{
		pos_x=pos.first;
		pos_y=pos.second;
		dir=dir_;
	}
	void operator=(QPoint pos)
	{
		pos_x=pos.x();
		pos_y=pos.y();
	}
	void operator=(std::pair<unsigned int,unsigned int> pos)
	{
		pos_x=pos.first;
		pos_y=pos.second;
	}
public:	
	int			pos_x;
	int			pos_y;
	eRobotDir	dir;
};
