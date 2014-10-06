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
	void reset()
	{
		directions = std::vector<bool>(4, true);
	}
public:
	//bit set if their's wall, otherwise it's false
	std::vector<bool> directions;
};
