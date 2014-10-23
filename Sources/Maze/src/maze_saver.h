#include <Maze/maze.h>

class maze_saver
{
public:
	maze_saver(maze * maze_data);
	void save(const std::string& file_path);
protected:
	maze *	maze_data;
};
