#include <Maze/maze.h>

class maze_saver
{
public:
	maze_saver(const maze * const maze_data);
	void save(const std::string& file_path);
protected:
	const maze * const	maze_data;
};
