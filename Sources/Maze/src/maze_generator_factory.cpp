#include "maze_generator_factory.h"
#include "maze_generator_kruskal.h"
#include "maze_generator_prim.h"
#include "maze_generator_recursive.h"

std::shared_ptr<maze_generator_interface> maze_generator_factory::create_generator(EMazeTypes type)
{
	std::shared_ptr<maze_generator_interface> maze_generator_;

	switch (type)
	{
		case E_MT_KRUSKAL:
			maze_generator_.reset(new maze_generator_kruskal); break;
		case E_MT_PRIM:
			maze_generator_.reset(new maze_generator_prim); break;
		case E_MT_RECURSIVE:
			maze_generator_.reset(new maze_generator_recursive); break;
		default:
			break;
	}

	return maze_generator_;
}
