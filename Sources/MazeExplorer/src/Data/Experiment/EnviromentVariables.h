#ifndef ENVIROMENT_VARS_H
#define ENVIROMENT_VARS_H
#include <vector>

//directions in which agent is pointing according to global compas
enum eRobotDir
{
    ROBOT_NORTH_DIR,	//robot is facing NORTH
    ROBOT_WEST_DIR,		//robot is facing WEST
    ROBOT_EAST_DIR,		//robot is facing EAST
    ROBOT_SOUTH_DIR,	//robot is facing SOUTH
    ROBOT_NONE_DIR		//there were no robot
};

//directions from agent point of view ...
enum directions
{
	ERROR_DIR=-1,	//-1 - there were error in calculations or nothing to return
    FRONT_DIR=0,	//0 - FRONT direction from ROBOT point of view
    RIGHT_DIR,	//1 - RIGHT direction from ROBOT point of view
    LEFT_DIR,	//2 - LEFT direction from ROBOT point of view
    BACK_DIR	//3 - BACK direction from ROBOT point of view
};
//
enum eLocationDirs
{
    LOCATION_EMPTY=0,	//location with none WALL
    LOCATION_FRONT=1,	//location with WALL on FRONT - usally from robot POV
    LOCATION_LEFT=2,	//location with WALL on LEFT  - usally from robot POV
    LOCATION_RIGHT=4,	//location with WALL on RIGHT - usally from robot POV
    LOCATION_BACK=8,	//location with WALL on BACK - usally from robot POV
	LOCATION_LB=LOCATION_LEFT|LOCATION_BACK,	//location with WALL on LEFT and RIGHT - usally from robot POV
    LOCATION_LR=LOCATION_LEFT|LOCATION_RIGHT,	//location with WALL on LEFT and RIGHT - usally from robot POV
	LOCATION_FL=LOCATION_FRONT|LOCATION_LEFT,	//location with WALL on LEFT and FRONT - usally from robot POV
	LOCATION_FR=LOCATION_FRONT|LOCATION_RIGHT,	//location with WALL on FRONT and RIGHT - usally from robot POV
	LOCATION_FB=LOCATION_FRONT|LOCATION_BACK,	//location with WALL on LEFT and FRONT - usally from robot POV
    LOCATION_RB=LOCATION_RIGHT|LOCATION_BACK,	//location with WALL on LEFT and FRONT - usally from robot POV
	LOCATION_FLR=LOCATION_FRONT|LOCATION_LEFT|LOCATION_RIGHT,	//location with WALL on FRONT, LEFT and RIGHT - usally from robot POV
	LOCATION_FLB=LOCATION_FRONT|LOCATION_LEFT|LOCATION_BACK,	//location with WALL on FRONT, LEFT and BACK - usally from robot POV
	LOCATION_FRB=LOCATION_FRONT|LOCATION_RIGHT|LOCATION_BACK,	//location with WALL on FRONT, RIGHT and BACK - usally from robot POV
	LOCATION_LRB=LOCATION_LEFT|LOCATION_RIGHT|LOCATION_BACK		//location with WALL on LEFTY, RIGHT and BACK - usally from robot POV
};

struct LocationDirs
{
    eLocationDirs locDir;
	LocationDirs():locDir(LOCATION_EMPTY) {}
    LocationDirs(eLocationDirs xlocDir):locDir(xlocDir) {}
    LocationDirs(directions xDir)
    {
        if (xDir = FRONT_DIR) locDir = LOCATION_FRONT;
        else if (xDir = LEFT_DIR) locDir = LOCATION_LEFT;
        else if (xDir = RIGHT_DIR) locDir = LOCATION_RIGHT;
        else if (xDir = BACK_DIR) locDir = LOCATION_BACK;
        else locDir = LOCATION_EMPTY;
    }
	std::vector<directions> Directions()
	{
		std::vector<directions> vActions;

		if (locDir&LOCATION_FRONT)
			vActions.push_back(FRONT_DIR);
		if (locDir&LOCATION_LEFT)
			vActions.push_back(LEFT_DIR);
		if (locDir&LOCATION_RIGHT)
			vActions.push_back(RIGHT_DIR);
		if (locDir&LOCATION_BACK)
			vActions.push_back(BACK_DIR);
		return vActions;
	}
    //operator eLocationDirs(){ return locDir; }
    operator eLocationDirs() const
    {
        return locDir;
    }
};


#define DIR_TO_LOCATION(x)	((x)==FRONT_DIR) ? LOCATION_FRONT : \
	((x)==LEFT_DIR) ? LOCATION_LEFT : \
	((x)==RIGHT_DIR) ? LOCATION_RIGHT : \
	((x)==BACK_DIR) ? LOCATION_BACK : LOCATION_EMPTY

#define LOCATION_TO_DIR(x)	((x)==LOCATION_FRONT) ? FRONT_DIR : \
	((x)==LOCATION_LEFT) ? LEFT_DIR : \
	((x)==LOCATION_RIGHT) ? RIGHT_DIR : \
	((x)==LOCATION_BACK) ? BACK_DIR : ERROR_DIR

#define ROBOT_DIRECTION_STRING(x)	((x)==ROBOT_EAST_DIR) ? "EAST" : \
	((x)==ROBOT_WEST_DIR) ? "WEST" : \
	((x)==ROBOT_NORTH_DIR) ? "NORTH" : "SOUTH"

typedef unsigned long LocationID;
#define SCAN_BACK_DIR false

#endif
