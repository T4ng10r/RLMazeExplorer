#pragma once

#include <Maze/maze_interface.h>
#include "maze_settings.h"
#include "maze_generator_interface.h"
#include <memory>

class maze_generator_recursive_private;

class maze_generator_recursive : public maze_generator_interface
{
public:
	maze_generator_recursive();
	~maze_generator_recursive();
	maze_interface_type generate_maze(const maze_settings & settings);
protected:
	std::unique_ptr<maze_generator_recursive_private> pimpl;
};
