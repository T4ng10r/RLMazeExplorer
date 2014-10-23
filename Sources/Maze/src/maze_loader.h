#include <Maze/maze.h>

class maze_loader
{
public:
	maze_loader(maze * maze_);
	void load(const std::string& file_path);
protected:
	maze * maze_data;
};
