#pragma once

#include "maze_interface.h"
#include "maze_settings.h"
#include <boost/shared_ptr.hpp>

class maze_generator_interface
{
public:
	virtual boost::shared_ptr<maze_interface> generate_maze(const maze_settings & xMazeSettings) = 0;
};
