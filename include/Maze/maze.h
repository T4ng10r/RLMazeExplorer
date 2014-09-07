#include <QtCore/QPoint>
#include <QtCore/QTextStream>
#include <vector>
#include <Maze/location.h>
#include <Maze/maze_settings.h>
#include <fstream>
#include <memory>

#ifndef C_MAZE_H
#define C_MAZE_H

enum EMazeTypes;
class CMazeGeneratorPrivate;

class maze
{
	friend  class CMazeGeneratorPrivate;
public:
    maze();
    int getXSize() const;
    int getYSize() const;
	void save_maze(std::ofstream stream);
	bool load_maze(std::ifstream stream);
    void operator=(const maze & mazeSource);

    bool				get_location(QPoint pos,location & location) const;
    bool				get_location(QPoint pos, bool &up, bool &down, bool &right, bool &left) const;
    const location &	get_location(int X,int Y) const;
    bool				get_location(int X,int Y,location & location) const;
    bool				get_location(int X,int Y, bool &up, bool &down, bool &right, bool &left) const;
    void				SetMazeEdges();
protected:
	//first index is column
	//second index is row
    std::vector< std::vector <location> >	m_vvMapa;
    int	size_x;
    int	size_y;
    //type of maze generation algorithm used to generate
    EMazeTypes		maze_type;
    location		empty_location;
};
#endif
