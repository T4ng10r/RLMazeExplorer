#include "robot.h"
#include <Tools/loggers.h>

class robot_private
{
public:
	robot_private(robot * pub);
	void	scanLocation();
	void	onOneExit();			//robot mo¿e iœc tylko w jedn¹ stronê
	void	onChooseExit();			//robot mo¿e dokonaæ wyboru
	int		howManyExits();			//ile wyjœæ z danej lokacji
public:
	robot * public_;

	bool	bOneStep;
	//	QList<int >				sectorExits;			//wynik skanowania lokacji
	CMazeKnowlegdeBase			* pKB;				//baza wiedzy
	CScanResults			currentScanResult;
};

robot_private::robot_private(robot * pub) : public_(pub)
{
	bOneStep = false;
	pKB = NULL;
}
int robot_private::howManyExits()
{
	int result = 0;
	/*	if (sectorScan[0].size())	result++;
	if (sectorScan[1].size())	result++;
	if (sectorScan[2].size())	result++;
	if (sectorScan[3].size())	result++;*/
	return result;
}
void robot_private::onOneExit()
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
		Q_EMIT public_->robotRotate(false, false);
	}
	else if (dir == RIGHT_DIR)
	{
		Q_EMIT public_->robotRotate(true, false);
	}
	else if (dir == BACK_DIR)
		//to mamy wyjscie za pleceami - czyli klasyczny slepy zaulek
		return;
	currentScanResult.robotChosenDir = dir;
	Q_EMIT public_->robotBeforeMove(&currentScanResult);
	Q_EMIT public_->robotMoved();
}
void robot_private::onChooseExit()
{
	directions dir = ERROR_DIR;
	dir = pKB->chooseExit(currentScanResult.locDirs);
	if (dir == LEFT_DIR)
	{
		Q_EMIT public_->robotRotate(false, false);
	}
	else if (dir == RIGHT_DIR)
	{
		Q_EMIT public_->robotRotate(true, false);
	}
	currentScanResult.robotChosenDir = dir;
	Q_EMIT public_->robotBeforeMove(&currentScanResult);
	Q_EMIT public_->robotMoved();
}
void robot_private::scanLocation()
{
	currentScanResult.clear();
	Q_EMIT public_->robotScans(&currentScanResult);
}

//////////////////////////////////////////////////////////////////////////
robot::robot(void) : pimpl(new robot_private(this)) {}
robot::~robot(void) {}
void robot::setOneStep(bool bOne)	
{ 
	pimpl->bOneStep = bOne; 
}
void robot::setKnowledgeBase(CMazeKnowlegdeBase * KnowlegdeBase)
{ 
	pimpl->pKB = KnowlegdeBase;
}
void robot::start_exploring()
{
    directions dir;
    int		nExits=0;
	bool	in_exit = false;
	if (pimpl->pKB == NULL)
		return;
    do
    {
        //sprawdzamy czy dotarliœmy ju¿ do wyjœcia
        Q_EMIT is_in_exit(in_exit);
		if (in_exit)
        {
			//Log4Qt::Logger::logger("")->info();
            break;
        }
		pimpl->scanLocation();
		nExits = pimpl->currentScanResult.getExitsCount(SCAN_BACK_DIR);
        if (nExits == 1)
        {
            //sprawdzamy czy to nie jest œlepy zau³ek
			pimpl->currentScanResult.getFrontScanResult(dir);
            if (dir != BACK_DIR && dir != ERROR_DIR)
				pimpl->onOneExit();
            else
            {
                break;
            }
        }
        else if (nExits>1)
        {
			pimpl->onChooseExit();
        }
        else
        {
            break;
        }

    }
    while(1);
};
