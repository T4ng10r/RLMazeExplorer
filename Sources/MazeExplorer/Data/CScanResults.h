#pragma once
#include <vector>
#include <Maze/CLocation.h>
#include <Data/Experiment/EnviromentVariables.h>
#include <Data/CRobotPostion.h>
using namespace std;
//wyniki skanowaia lokacji przez robota
class CScanResults
{
public:
    CScanResults(void);
    void clear();
    void Rotate(bool bRight);
    void getScanResult(directions dir,bool &bPassage);
    void getFrontScanResult(directions &dir);
    vector<directions> getVActions();
    int exitsCount();
    int getExitsCount(bool bBackScan);
    QString translateLocID(const LocationDirs &xLocDirs);

	LocationDirs translateScanResultsToBitArray();


    LocationDirs		locDirs;
    LocationDirs		unrotatedLocDirs;
    directions			robotChosenDir;
    bool				bCrossRoad;

    vector<CLocation>		vFrontDir;
    vector<CLocation>		vLeftDir;
    vector<CLocation>		vRightDir;
    vector<CLocation>		vBackDir;
    CRobotPostion			robotPos;
};
