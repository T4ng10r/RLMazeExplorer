#include "CExperimentSettings.h"

CExperimentSettings::CExperimentSettings(void)
{
    repeatingQuantity=0;
    CRobotPostion robotPos;
    mazeSettings.uiMaxX=10;;
	mazeSettings.uiMaxY=10;;
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

CExperimentSettings::~CExperimentSettings(void)
{
}
