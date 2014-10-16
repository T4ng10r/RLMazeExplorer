#include "CScanResults.h"
#include <QString>

scan_results::scan_results(void):locDirs(LOCATION_EMPTY),robotChosenDir(FRONT_DIR),bCrossRoad(false)
{
    clear();
}
void scan_results::clear()
{
    vFrontDir.clear();
    vLeftDir.clear();
    vRightDir.clear();
    vBackDir.clear();
}
int scan_results::exitsCount(bool back_scan)
{
    int count(0);
    if (vFrontDir.size())
        count++;
    if (vLeftDir.size())
        count++;
    if (vRightDir.size())
        count++;
    if (back_scan && vBackDir.size())
        count++;

    return count;
}

void scan_results::Rotate(bool bRight)
{
    std::vector<location>		vTemporary;

    if (bRight)
    {
        vTemporary = vFrontDir;
        vFrontDir = vRightDir;
        vRightDir = vBackDir;
        vBackDir = vLeftDir;
        vLeftDir = vTemporary;
    }
    else
    {
        vTemporary = vFrontDir;
        vFrontDir = vLeftDir;
        vLeftDir = vBackDir;
        vBackDir = vRightDir;
        vRightDir = vTemporary;
    }
}

void scan_results::getScanResult(directions dir,bool &bPassage)
{
    bPassage=false;
    switch(dir)
    {
    case FRONT_DIR:
        if (vFrontDir.size())
            bPassage=true;
        break;
    case RIGHT_DIR:
        if (vRightDir.size())
            bPassage=true;
        break;
    case LEFT_DIR:
        if (vLeftDir.size())
            bPassage=true;
        break;
    case BACK_DIR:
        if (vBackDir.size())
            bPassage=true;
        break;
    default:
        break;
    }
}
void scan_results::getFrontScanResult(directions &dir)
{
	std::vector<directions>	exitsDir;

    if (vFrontDir.size())
        exitsDir.push_back(FRONT_DIR);
    if (vRightDir.size())
        exitsDir.push_back(RIGHT_DIR);
    if (vLeftDir.size())
        exitsDir.push_back(LEFT_DIR);

    if (exitsDir.size()>1)
        dir=ERROR_DIR;
    else
        dir = exitsDir.back();
}
QString scan_results::translateLocID(const LocationDirs &xLocDirs)
{
    QString name;
    switch(xLocDirs)
    {
    case LOCATION_EMPTY:
        return "EMPTY";
    case LOCATION_FRONT:
        return "FRONT";
    case LOCATION_LEFT:
        return "LEFT";
    case LOCATION_RIGHT:
        return "RIGHT";
    case LOCATION_BACK:
        return "BACK";
    case LOCATION_LR:
        return "LEFT_RIGHT";
    case LOCATION_FL:
        return "FRONT_LEFT";
    case LOCATION_FR:
        return "FRONT_RIGHT";
    case LOCATION_FLR:
        return "FRONT_LEFT_RIGHT";
	case LOCATION_LB:
		return "LEFT_BACK";
	case LOCATION_FB:
		return "FRONT_BACK";
	case LOCATION_RB:
		return "RIGHT_BACK";
	case LOCATION_FLB:
		return "FRONT_LEFT_BACK";
	case LOCATION_FRB:
		return "FRONT_RIGHT_BACK";
	case LOCATION_LRB:
		return "LEFT_RIGHT_BACK";
    }
    return "";
}
std::vector<directions> scan_results::getVActions()
{
    bool bPassage;
    std::vector<directions> vActions;

    getScanResult(FRONT_DIR,bPassage);
    if (bPassage)	vActions.push_back(FRONT_DIR);
    getScanResult(LEFT_DIR,bPassage);
    if (bPassage)	vActions.push_back(LEFT_DIR);
    getScanResult(RIGHT_DIR,bPassage);
    if (bPassage)	vActions.push_back(RIGHT_DIR);

    return vActions;
}

LocationDirs scan_results::translateScanResultsToBitArray()
{
	int				result=0;
	bool			bPassage=false;

	getScanResult(FRONT_DIR,bPassage);
	if (bPassage)	result |=LOCATION_FRONT;
	getScanResult(LEFT_DIR,bPassage);
	if (bPassage)	result |=LOCATION_LEFT;
	getScanResult(RIGHT_DIR,bPassage);
	if (bPassage)	result |=LOCATION_RIGHT;
	getScanResult(BACK_DIR,bPassage);
	if (bPassage)	result |=LOCATION_BACK;
	return (eLocationDirs)result;
}

