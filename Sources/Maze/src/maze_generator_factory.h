#pragma once

#include "maze_generator_interface.h"
#include <Maze/maze_settings.h>
#include <boost/shared_ptr.hpp>

class maze_generator_factory
{
public:
	static boost::shared_ptr<maze_generator_interface> create_generator(EMazeTypes type);
};