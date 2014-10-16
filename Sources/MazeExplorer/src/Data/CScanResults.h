#pragma once
#include <vector>
#include <memory>
#include <Maze/location.h>
#include <Data/experiment/EnviromentVariables.h>
#include <Data/robot_postion.h>

//wyniki skanowaia lokacji przez robota
class scan_results
{
public:
	scan_results(void);
	void clear();
	void Rotate(bool bRight);
	void getScanResult(directions dir,bool &bPassage);
	void getFrontScanResult(directions &dir);
	std::vector<directions> getVActions();
	int exitsCount(bool back_scan = false);
	QString translateLocID(const LocationDirs &xLocDirs);

	LocationDirs translateScanResultsToBitArray();
public:
	LocationDirs		locDirs;
	LocationDirs		unrotatedLocDirs;
	directions			robotChosenDir;
	bool				bCrossRoad;

	std::vector<location>		vFrontDir;
	std::vector<location>		vLeftDir;
	std::vector<location>		vRightDir;
	std::vector<location>		vBackDir;
	robot_postion			robotPos;
};
typedef std::shared_ptr<scan_results> scan_results_handle;
