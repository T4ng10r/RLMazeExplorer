#include "CRobot.h"
#include <Tools/loggers.h>

CRobot::CRobot(void)
{
    bOneStep = false;
    pKB=NULL;
}
CRobot::~CRobot(void)
{
}
int CRobot::howManyExits()
{
    int result=0;
    /*	if (sectorScan[0].size())	result++;
    	if (sectorScan[1].size())	result++;
    	if (sectorScan[2].size())	result++;
    	if (sectorScan[3].size())	result++;*/
    return result;
}
void CRobot::onOneExit()
{
    directions dir;
    currentScanResult.getFrontScanResult(dir);
    if (dir == ERROR_DIR)
    {
        Q_ASSERT(0);
        return;
    }
    else if (dir == LEFT_DIR)
    {
		Q_EMIT robotRotate(false, false);
    }
    else if (dir == RIGHT_DIR)
    {
		Q_EMIT robotRotate(true, false);
    }
    else if (dir == BACK_DIR)
        //to mamy wyjscie za pleceami - czyli klasyczny slepy zaulek
        return;
    currentScanResult.robotChosenDir=dir;
	Q_EMIT robotBeforeMove(&currentScanResult);
	Q_EMIT robotMoved();
}
void CRobot::onChooseExit()
{
    directions dir=ERROR_DIR;
	dir = pKB->chooseExit(currentScanResult.locDirs);
    if (dir==LEFT_DIR)
    {
		Q_EMIT robotRotate(false, false);
    }
    else if (dir==RIGHT_DIR)
    {
		Q_EMIT robotRotate(true, false);
    }
    currentScanResult.robotChosenDir=dir;
	Q_EMIT robotBeforeMove(&currentScanResult);
	Q_EMIT robotMoved();
}
void CRobot::scanLocation()
{
    currentScanResult.clear();
	Q_EMIT robotScans(&currentScanResult);
}
void CRobot::robotStartExploring()
{
    directions dir;
    int		nExits=0;
    bool	bIsInExit=false;
	if (pKB==NULL)
		return;
    do
    {
        //sprawdzamy czy dotarliœmy ju¿ do wyjœcia
        Q_EMIT checkIfInExit(bIsInExit);
        if (bIsInExit)
        {
			//Log4Qt::Logger::logger("")->info();
            break;
        }
        scanLocation();
        nExits = currentScanResult.getExitsCount(SCAN_BACK_DIR);
        if (nExits == 1)
        {
            //sprawdzamy czy to nie jest œlepy zau³ek
            currentScanResult.getFrontScanResult(dir);
            if (dir != BACK_DIR && dir != ERROR_DIR)
                onOneExit();
            else
            {
                break;
            }
        }
        else if (nExits>1)
        {
            onChooseExit();
        }
        else
        {
            break;
        }

    }
    while(1);
};
