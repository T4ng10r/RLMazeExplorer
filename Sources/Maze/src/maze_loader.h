#include <Maze/maze.h>
#include <memory>

struct maze_loader_private;

class maze_loader
{
public:
	maze_loader(maze * maze_);
	~maze_loader();
	void load(const std::string& file_path);
protected:
	std::unique_ptr<maze_loader_private> pimpl;
};
