#pragma once

#include "maze_generator_interface.h"
#include <Maze/maze_settings.h>
#include <memory>

class maze_generator_factory
{
public:
	static std::shared_ptr<maze_generator_interface> create_generator(EMazeTypes type);
};