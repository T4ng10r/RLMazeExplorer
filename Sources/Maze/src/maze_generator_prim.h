#pragma once

#include <Maze/maze_interface.h>
#include "maze_settings.h"
#include "maze_generator_interface.h"
#include <memory>

class maze_generator_prim_private;

class maze_generator_prim : public maze_generator_interface
{
public:
	maze_generator_prim();
	~maze_generator_prim();
	std::shared_ptr<maze_interface> generate_maze(const maze_settings & settings);
protected:
	std::unique_ptr<maze_generator_prim_private> pimpl;
};
