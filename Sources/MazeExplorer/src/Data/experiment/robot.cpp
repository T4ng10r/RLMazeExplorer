#include "robot.h"
#include <Tools/loggers.h>

class robot_private
{
public:
	robot_private(robot * pub);
	void	scanLocation();
	void	onOneExit();			//robot mo�e i�c tylko w jedn� stron�
	void	onChooseExit();			//robot mo�e dokona� wyboru
	int		howManyExits();			//ile wyj�� z danej lokacji
public:
	robot * public_;

	bool	bOneStep;
	//	QList<int >				sectorExits;			//wynik skanowania lokacji
	maze_knowlegde_base			* pKB;				//baza wiedzy
	scan_results_handle  currentScanResult;
};

robot_private::robot_private(robot * pub) : public_(pub)
{
	currentScanResult.reset(new scan_results);
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
	currentScanResult->getFrontScanResult(dir);
	if (dir == ERROR_DIR)
	{
		Q_ASSERT(0);
		return;
	}
	else if (dir == LEFT_DIR)
	{
		Q_EMIT public_->rotate(false, false);
	}
	else if (dir == RIGHT_DIR)
	{
		Q_EMIT public_->rotate(true, false);
	}
	else if (dir == BACK_DIR)
		//to mamy wyjscie za pleceami - czyli klasyczny slepy zaulek
		return;
	currentScanResult->robotChosenDir = dir;
	Q_EMIT public_->robotBeforeMove(currentScanResult);
	Q_EMIT public_->move_forward();
}
void robot_private::onChooseExit()
{
	directions dir = ERROR_DIR;
	dir = pKB->chooseExit(currentScanResult->locDirs);
	if (dir == LEFT_DIR)
	{
		Q_EMIT public_->rotate(false, false);
	}
	else if (dir == RIGHT_DIR)
	{
		Q_EMIT public_->rotate(true, false);
	}
	currentScanResult->robotChosenDir = dir;
	Q_EMIT public_->robotBeforeMove(currentScanResult);
	Q_EMIT public_->move_forward();
}
void robot_private::scanLocation()
{
	currentScanResult->clear();
	Q_EMIT public_->robotScans(currentScanResult);
}

//////////////////////////////////////////////////////////////////////////
robot::robot(void) : pimpl(new robot_private(this)) {}
robot::~robot(void) {}
void robot::setOneStep(bool bOne)	
{ 
	pimpl->bOneStep = bOne; 
}
void robot::setKnowledgeBase(maze_knowlegde_base * KnowlegdeBase)
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
		//sprawdzamy czy dotarli�my ju� do wyj�cia
		Q_EMIT is_in_exit(in_exit);
		if (in_exit)
		{
			//Log4Qt::Logger::logger("")->info();
			break;
		}
		pimpl->scanLocation();
		nExits = pimpl->currentScanResult->exitsCount(SCAN_BACK_DIR);
		if (nExits == 1)
		{
			//sprawdzamy czy to nie jest �lepy zau�ek
			pimpl->currentScanResult->getFrontScanResult(dir);
			if (dir != BACK_DIR && dir != ERROR_DIR)
				pimpl->onOneExit();
			else
				break;
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
