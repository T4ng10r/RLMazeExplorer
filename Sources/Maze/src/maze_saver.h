#include <Maze/maze.h>
#include <memory>

struct maze_saver_private;

class maze_saver
{
public:
	maze_saver(const maze * const maze_data);
	~maze_saver();
	void save(const std::string& file_path);
protected:
	std::unique_ptr<maze_saver_private> pimpl;
};
