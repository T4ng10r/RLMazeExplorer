#include "CMazeExplorationResult.h"

CMazeExplorationResult::CMazeExplorationResult()
{
	lPositions.clear();
	bExplorationSuccessful=false;
}
CMazeExplorationResult::~CMazeExplorationResult()
{
}
void CMazeExplorationResult::clear()
{
	CExplorationResult::clear();
	lPositions.clear();
}
void CMazeExplorationResult::addRobotPosition(scan_results_handle scanResult)
{
	if (scanResult->exitsCount(SCAN_BACK_DIR)>1)
	{
		m_vDecisions.push_back(std::make_pair(scanResult->locDirs,scanResult->robotChosenDir));
		scanResult->bCrossRoad=true;
	}
	lPositions.push_back(*scanResult);
}
bool CMazeExplorationResult::getRobotPosition(unsigned int nr,scan_results & scanResult)
{
	std::list<scan_results>::iterator	posIter;
	int index=0;
	if (nr>=lPositions.size())
		return false;
	for(posIter=lPositions.begin(); posIter!=lPositions.end(); posIter++)
	{
		if (nr == index)
		{
			scanResult=(*posIter);
			return true;
		}
		index++;
	}
	return false;
}
int CMazeExplorationResult::getPositionsCount()
{
	return lPositions.size();
}
int CMazeExplorationResult::getCrossRoadsCount()
{
	scan_results	scanResult;
	int count = lPositions.size();
	int crossRoadsCount=0;
	for(int index = 0; index<count-1; index++)
	{
		if (!getRobotPosition(index,scanResult))
		{
			return 0;
		}
		if(scanResult.exitsCount(SCAN_BACK_DIR)==1)
			continue;
		else
			crossRoadsCount++;
	}
	return crossRoadsCount;
}
void CMazeExplorationResult::prepareCrossRoadsList(std::vector<scan_results> & listCrossRoads)
{
	scan_results	scanResult;
	listCrossRoads.clear();
	int count = lPositions.size();
	for(int index = 0; index<count-1; index++)
	{
		if (!getRobotPosition(index,scanResult))
		{
			break;
		}
		if(scanResult.exitsCount(SCAN_BACK_DIR)==1)
			continue;
		else
		{
			listCrossRoads.push_back(scanResult);
		}
	}
}
void CMazeExplorationResult::saveExploration(QTextStream *pStream)
{
	std::list<scan_results>::iterator  iterPos;
	(*pStream)<<"EXPLORATION\n  ";

	for(iterPos=lPositions.begin(); iterPos!=lPositions.end(); iterPos++)
	{
		if (iterPos!=lPositions.begin())
			(*pStream)<<"|";
		scan_results	result = *iterPos;
		(*pStream)<<result.locDirs<<"-"<<result.robotChosenDir<<"-";
		(*pStream)<<result.robotPos.pos_x<<"-"<<result.robotPos.pos_y<<"-"<<result.robotPos.dir;
	}
	(*pStream)<<"\n";
}
void CMazeExplorationResult::loadExploration(QTextStream *pStream)
{
	QString			strLine;
	scan_results	newResult;
	char			letter;
	int				value;
	while(true)
	{
		(*pStream)>>value;
		newResult.locDirs=(eLocationDirs)value;
		(*pStream)>>letter>>value;
		newResult.robotChosenDir=(directions)value;
		(*pStream)>>letter>>newResult.robotPos.pos_x>>letter;
		(*pStream)>>newResult.robotPos.pos_y>>letter>>value;
		newResult.robotPos.dir=(eRobotDir)value;
		(*pStream)>>letter;
		lPositions.push_back(newResult);
		if (letter=='|')
			continue;
		else
			break;
	}
}
