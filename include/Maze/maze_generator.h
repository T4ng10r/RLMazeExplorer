#pragma once 

#include <Maze/maze_interface.h>
#include "maze_settings.h"
#include <memory>

class maze_generator
{
public:
	std::shared_ptr<maze_interface> generate_maze(const maze_settings & xMazeSettings);
	std::shared_ptr<maze_interface> generate_maze(unsigned int size_x, unsigned int size_y, EMazeTypes maze_type);
};
