#pragma once 

#include <Maze/maze_interface.h>
#include "maze_settings.h"
#include <boost/shared_ptr.hpp>

class maze_generator 
{
public:
	boost::shared_ptr<maze_interface> generate_maze(const maze_settings & xMazeSettings);
	boost::shared_ptr<maze_interface> generate_maze(unsigned int size_x, unsigned int size_y, EMazeTypes maze_type);
};
