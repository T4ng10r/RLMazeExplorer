#pragma once
#include <vector>
#include <Maze/maze_settings.h>
#include <algorithm>

class location	//jesli dany kierunek jest prawda - tam jest sciana
{
public:
	location()
	{
		reset();
	}
	location(bool north_wall, bool east_wall, bool south_wall, bool west_wall)
	{
		reset();
		directions[NORTH_DIR] = north_wall;
		directions[EAST_DIR] = east_wall; 
		directions[SOUTH_DIR] = south_wall;
		directions[WEST_DIR] = west_wall;
	}
	void set_wall(EDirections dir)
	{
		directions[dir] = true;
	}
	void set_passage(EDirections dir)
	{
		directions[dir] = false;
	}
	bool is_wall(EDirections dir) const
	{
		return directions[dir];
	}
	unsigned int get_count(bool wall) const
	{
		return std::count(directions.begin(), directions.end(), wall);
	}
	int get_cell_value()
	{
		int result(0);
		if (directions[NORTH_DIR])
			result |= 1 << NORTH_DIR;
		if (directions[EAST_DIR])
			result |= 1 << EAST_DIR;
		if (directions[SOUTH_DIR])
			result |= 1 << SOUTH_DIR;
		if (directions[WEST_DIR])
			result |= 1 << WEST_DIR;
		return result;
	}
	void reset()
	{
		directions = std::vector<bool>(4, true);
	}
	bool operator==(const location & other) const
	{
		if (directions == other.directions)
			return true;
		return false;
	}
public:
	//bit set if their's wall, otherwise it's false
	std::vector<bool> directions;
};
