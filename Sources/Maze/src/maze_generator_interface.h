#pragma once

#include "maze_interface.h"
#include "maze_settings.h"
#include <memory>

class maze_generator_interface
{
public:
	virtual std::shared_ptr<maze_interface> generate_maze(const maze_settings & xMazeSettings) = 0;
};
