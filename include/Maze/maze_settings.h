#pragma once

enum EMazeTypes
{
	E_MT_NONE,
	E_MT_PRIM,
	E_MT_RECURSIVE,
	E_MT_KRUSKAL
};

struct maze_settings
{
	unsigned int    size_x;
	unsigned int    size_y;
	EMazeTypes      mazeType;
	bool            bMazePerfect;
};

enum EDirections
{
	NORTH_DIR = 0,
	WEST_DIR,
	EAST_DIR,
	SOUTH_DIR,
	NONE_DIR,
	COUNT_DIR = NONE_DIR
};

//enum ELocationDirs
//{
//	LOCATION_EMPTY = 0,	//location with none WALL
//	LOCATION_FRONT = 1,	//location with WALL on FRONT - usally from robot POV
//	LOCATION_LEFT = 2,	//location with WALL on LEFT  - usally from robot POV
//	LOCATION_RIGHT = 4,	//location with WALL on RIGHT - usally from robot POV
//	LOCATION_BACK = 8,	//location with WALL on BACK - usally from robot POV
//	LOCATION_LB = LOCATION_LEFT | LOCATION_BACK,	//location with WALL on LEFT and RIGHT - usally from robot POV
//	LOCATION_LR = LOCATION_LEFT | LOCATION_RIGHT,	//location with WALL on LEFT and RIGHT - usally from robot POV
//	LOCATION_FL = LOCATION_FRONT | LOCATION_LEFT,	//location with WALL on LEFT and FRONT - usally from robot POV
//	LOCATION_FR = LOCATION_FRONT | LOCATION_RIGHT,	//location with WALL on FRONT and RIGHT - usally from robot POV
//	LOCATION_FB = LOCATION_FRONT | LOCATION_BACK,	//location with WALL on LEFT and FRONT - usally from robot POV
//	LOCATION_RB = LOCATION_RIGHT | LOCATION_BACK,	//location with WALL on LEFT and FRONT - usally from robot POV
//	LOCATION_FLR = LOCATION_FRONT | LOCATION_LEFT | LOCATION_RIGHT,	//location with WALL on FRONT, LEFT and RIGHT - usally from robot POV
//	LOCATION_FLB = LOCATION_FRONT | LOCATION_LEFT | LOCATION_BACK,	//location with WALL on FRONT, LEFT and BACK - usally from robot POV
//	LOCATION_FRB = LOCATION_FRONT | LOCATION_RIGHT | LOCATION_BACK,	//location with WALL on FRONT, RIGHT and BACK - usally from robot POV
//	LOCATION_LRB = LOCATION_LEFT | LOCATION_RIGHT | LOCATION_BACK		//location with WALL on LEFTY, RIGHT and BACK - usally from robot POV
//};

