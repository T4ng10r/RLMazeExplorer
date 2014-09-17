#pragma once
#include <vector>
#include <Maze/maze_settings.h>

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
	bool is_wall(EDirections dir)
	{
		return directions[dir];
	}
	void reset()
	{
		directions = std::vector<bool>(4, false);
	}
public:
	//bit set if their's wall, otherwise it's false
	std::vector<bool> directions;
};
