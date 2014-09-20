#include "maze_generator.h"
#include "maze_generator_factory.h"

//////////////////////////////////////////////////////////////////////////
boost::shared_ptr<maze_interface> maze_generator::generate_maze(unsigned int size_x, unsigned int size_y, EMazeTypes eMazeType)
{
    maze_settings xMazeSettings;
	xMazeSettings.size_x = size_x;
	xMazeSettings.size_y = size_y;
    xMazeSettings.mazeType = eMazeType;
    xMazeSettings.bMazePerfect = true;
	return generate_maze(xMazeSettings);
}
boost::shared_ptr<maze_interface> maze_generator::generate_maze(const maze_settings & xMazeSettings)
{
	boost::shared_ptr<maze_generator_interface> generator = maze_generator_factory::create_generator(xMazeSettings.mazeType);
	return generator->generate_maze(xMazeSettings);
}
