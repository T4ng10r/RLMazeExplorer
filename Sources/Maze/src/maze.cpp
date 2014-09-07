#include "maze.h"
#include "maze_settings.h"
//#include <Experiment/EnviromentVariables.h>
#include <Tools/loggers.h>

maze::maze():size_x(0),size_y(0),maze_type(E_MT_NONE) {}
bool maze::get_location(int X,int Y, bool &up, bool &down, bool &right, bool &left) const
{
    if (X >= size_x  || Y >= size_y )
        return false;

    const location & location = get_location(X,Y);
    up = location.up;
    down = location.down;
    right = location.right;
    left = location.left;
    return true;
}
const location & maze::get_location(int X,int Y) const
{
    if (X >= size_x || Y >= size_x )
        return empty_location;
    return m_vvMapa[X][Y];
}
bool maze::get_location(int X,int Y,location & location) const
{
    if (X >= size_x || Y >= size_x )
        return false;

    location = get_location(X,Y);
    //location = m_vvMapa[X][Y];
    return true;
}
bool maze::get_location(QPoint pos,location & location) const
{
    if (pos.x() >= size_x || pos.y() >= size_x )
        return false;

    location = get_location(pos.x(),pos.y());
    //location = m_vvMapa[X][Y];
    return true;
}
bool maze::get_location(QPoint pos, bool &up, bool &down, bool &right, bool &left) const
{
    if (pos.x() >= size_x || pos.y() >= size_x )
        return false;

    return get_location(pos.x(),pos.y(),up,down,right,left);
    //CLocation location = m_vvMapa[X][Y];
    //up = location.up;
    //down = location.down;
    //right = location.right;
    //left = location.left;
    return true;
};
int maze::getXSize() const
{
    return size_x;
}
int maze::getYSize() const
{
    return size_y;
}
void maze::save_maze(std::ofstream stream)
{
    bool bUp, bDown, bRight, bLeft;
	stream << "MAZE_DATA" << std::endl;
	stream << size_x << " " << size_y << "\n";
    for(int Y=0; Y<size_y; Y++)
    {
        for(int X=0; X<size_x; X++)
        {
            int dir=0;
            if (get_location(X+1, Y+1, bUp, bDown, bRight, bLeft))
            {
                if (bUp)
                    dir|=LOCATION_FRONT;
                if (bDown)
                    dir|=LOCATION_BACK;
                if (bRight)
                    dir|=LOCATION_RIGHT;
                if (bLeft)
                    dir|=LOCATION_LEFT;
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
            QChar cChar;
			stream >> dir;

            location.reset();

            if (dir&LOCATION_FRONT)
                location.up=true;
            if (dir&LOCATION_BACK)
                location.down=true;
            if (dir&LOCATION_RIGHT)
                location.right=true;
            if (dir&LOCATION_LEFT)
                location.left=true;
            m_vvMapa[X][Y]=location;
        }
    }
	stream >> strText;
    if (strText!="END_MAZE_DATA")
    {
		printLog(eDebug, eErrorLogLevel, "Loading maze data failed (END_MAZE_DATA tag doesn't exist)");
		return false;
    }
    SetMazeEdges();
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
void maze::SetMazeEdges()
{
    unsigned int X,Y,index;
    X=size_x;
    Y=size_y;

    for(index=0; index<X; index++)
    {
        m_vvMapa[index][0].up=true;
        m_vvMapa[index][Y-1].down=true;
    }

    for(index=0; index<Y; index++)
    {
        m_vvMapa[0][index].left=true;
        m_vvMapa[X-1][index].right=true;
    }
}
