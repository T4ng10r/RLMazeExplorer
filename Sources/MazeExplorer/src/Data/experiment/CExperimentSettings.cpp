#include "CExperimentSettings.h"

experiment_settings::experiment_settings(void)
{
	reset();
}

experiment_settings::~experiment_settings(void)
{
}

void experiment_settings::reset()
{
	repeat_count=0;
	CRobotPostion robotPos;
	mazeSettings.size_x = 10;;
	mazeSettings.size_y = 10;;
	mazeSettings.bMazePerfect=true;;
	mazeSettings.mazeType=E_MT_KRUSKAL;;

	robotPos.posX=1;
	robotPos.posY=1;
	startPosition=robotPos;

	QPoint pos;

	pos.setX(10);
	pos.setY(10);
	lFinishPositions.clear();
	lFinishPositions.push_back(pos);
	fPenaltyValue=0.25;
	fPriceValue=0.25;

}
