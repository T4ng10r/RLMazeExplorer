#include "maze.h"
#include <Tools/loggers.h>

maze::maze():size_x(0),size_y(0),maze_type(E_MT_NONE) {}
int maze::get_size_x() const
{
	return size_x;
};
int maze::get_size_y() const
{
	return size_y;
};
boost::optional<location> maze::get_location(int x, int y) const
{
	boost::optional<location> result;
	if (x >= size_x || y >= size_y || x < 0 || y < 0)
		return result;

	return m_vvMapa[x][y];
};
location & maze::get_xlocation(int x, int y)
{
	return m_vvMapa[x][y];
}

void maze::save_maze(std::ofstream stream)
{
	stream << "MAZE_DATA" << std::endl;
	stream << size_x << " " << size_y << "\n";
    for(int Y=0; Y<size_y; Y++)
    {
        for(int X=0; X<size_x; X++)
        {
            int dir=0;
			boost::optional<location>	location_ = get_location(X+1, Y+1);
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
	stream << "END_MAZE_DATA\n";
}
bool maze::load_maze(std::ifstream stream)
{
    int sizeX,sizeY;
    std::string strText;
    location	location;
	stream >> strText;
    if (strText!="MAZE_DATA")
    {
		printLog(eDebug, eErrorLogLevel, "Loading maze data failed (MAZE_DATA tag doesn't exist)");
		return false;
    }
	stream >> sizeX;
	stream >> sizeY;

    //////////////////////////////////////////////////////////////////////////
    //przygotowujemy i alokujemy pamiec na tablice labiryntu
    m_vvMapa.resize(sizeX);
    for(int i=0; i<sizeX; i++)
        m_vvMapa[i].resize(sizeY);


    for(int Y=0; Y<size_y; Y++)
    {
        for(int X=0; X<size_x; X++)
        {
            int dir=0;
			stream >> dir;

            location.reset();

			for (int i = NORTH_DIR; i != COUNT_DIR; i++)
			{
				if (dir & (1 << i))
					location.set_wall(NORTH_DIR);
			}
            m_vvMapa[X][Y]=location;
        }
    }
	stream >> strText;
    if (strText!="END_MAZE_DATA")
    {
		printLog(eDebug, eErrorLogLevel, "Loading maze data failed (END_MAZE_DATA tag doesn't exist)");
		return false;
    }
    preset_maze_edges();
    return true;
}
void maze::operator=(const maze & mazeSource)
{
    m_vvMapa = mazeSource.m_vvMapa;

    size_x = mazeSource.size_x;
    size_y = mazeSource.size_y;
    maze_type = mazeSource.maze_type;
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
