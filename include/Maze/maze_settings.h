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

