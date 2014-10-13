#ifndef _MAZE_EXPLORATION_RESULTS_INCLUDE
#define _MAZE_EXPLORATION_RESULTS_INCLUDE

#include <KnowledgeBase/CExplorationResult.h>
#include <Data/experiment/EnviromentVariables.h>
#include <Data/CScanResults.h>
#include <QtCore/QTextStream>

//result of single robot exploration - from robot point of view
class CMazeExplorationResult : public CExplorationResult<LocationDirs, directions>
{
public:
    CMazeExplorationResult();
    ~CMazeExplorationResult();
    void	clear();
    void	addRobotPosition(CScanResults );
    int		getPositionsCount();		//how many locations robot had visited in this exploration
    int		getCrossRoadsCount();		//how many crossroad/decision points was in remembered path
    bool	getRobotPosition(unsigned int nr,CScanResults & scanResult);
    void	prepareCrossRoadsList(vector<CScanResults> & listCrossRoads);
    void	loadExploration(QTextStream *pStream);
    void	saveExploration(QTextStream *pStream);

    bool	bExplorationSuccessful;
protected:
    list<CScanResults>			lPositions;
};
#endif //_MAZE_EXPLORATION_RESULTS_INCLUDE
