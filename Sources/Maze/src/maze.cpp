#include <Maze/maze.h>
#include <Tools/loggers.h>
#include "maze_saver.h"
#include "maze_loader.h"

maze::maze():size_x(0),size_y(0),type(E_MT_NONE) {}
int maze::get_size_x() const
{
	return size_x;
};
int maze::get_size_y() const
{
	return size_y;
};
boost::optional<location> maze::get_location(unsigned int x, unsigned  int y) const
{
	boost::optional<location> result;
	if (x >= size_x || y >= size_y)
		return result;

	return m_vvMapa[x][y];
};
location & maze::get_xlocation(unsigned int x, unsigned int y)
{
	return m_vvMapa[x][y];
}

void maze::save_maze(const std::string& file_path)
{
	maze_saver saver(this);
	saver.save(file_path);
	/*stream << "MAZE_DATA" << std::endl;
	stream << size_x << " " << size_y << "\n";
	for(int Y=0; Y<size_y; Y++)
	{
		for(int X=0; X<size_x; X++)
		{
			int dir=0;
			boost::optional<location> location_ = get_location(X+1, Y+1);
			if (!location_)
				continue;;
			for (int i = NORTH_DIR; i != COUNT_DIR; i++)
			{
				if (dir & (1 << i))
					location_->set_wall((EDirections)i);
			}
		}
		stream << "\n";
	}
	stream << "END_MAZE_DATA\n";*/
}
bool maze::load_maze(const std::string& file_path)
{
	maze_loader loader(this);
	loader.load(file_path);
	return true;
}
void maze::operator=(const maze & mazeSource)
{
	m_vvMapa = mazeSource.m_vvMapa;

	size_x = mazeSource.size_x;
	size_y = mazeSource.size_y;
	type = mazeSource.type;
}
//////////////////////////////////////////////////////////////////////////
void maze::preset_maze_edges()
{
	unsigned int X,Y,index;
	X=size_x;
	Y=size_y;

	for(index=0; index<X; index++)
	{
		m_vvMapa[index][0].set_wall(NORTH_DIR);
		m_vvMapa[index][Y - 1].set_wall(SOUTH_DIR);
	}
	for(index=0; index<Y; index++)
	{
		m_vvMapa[0][index].set_wall(WEST_DIR);
		m_vvMapa[X-1][index].set_wall(EAST_DIR);
	}
}

void maze::resize()
{
	m_vvMapa.resize(size_x);
	for (unsigned int index = 0; index < size_x; index++)
		m_vvMapa[index].resize(size_y);
}
void maze::reset_locations()
{
	for (unsigned int index1 = 0; index1 < size_x; index1++)
		for (unsigned int index2 = 0; index2 < size_y; index2++)
			m_vvMapa[index1][index2].reset();
}
