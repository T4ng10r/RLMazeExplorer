#ifndef _MAZE_GENERATOR_INCLUDE_
#define _MAZE_GENERATOR_INCLUDE_

#include "maze.h"
#include "maze_settings.h"
#include <memory>

class CMazeGeneratorPrivate;

class maze_generator
{
public:
    maze_generator();
    ~maze_generator();
    const maze & GenerateMaze(const maze_settings & xMazeSettings);
    const maze & GenerateMaze(unsigned int size_x, unsigned int size_y, EMazeTypes maze_type);	//generuje labirynt
    //void MakeNotPerfect();
private:
	std::unique_ptr<CMazeGeneratorPrivate> pimpl;
};
#endif
