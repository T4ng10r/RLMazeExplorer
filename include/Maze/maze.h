#pragma once

#include <Maze/maze_interface.h>
#include <fstream>

enum EMazeTypes;
class CMazeGeneratorPrivate;

class maze : public maze_interface
{
	friend  class CMazeGeneratorPrivate;
public:
	maze();

	void operator=(const maze & maze_source);
	int get_size_x() const;
	int get_size_y() const;
	void save_maze(std::ofstream stream);
	bool load_maze(std::ifstream stream);

	boost::optional<location> get_location(int X, int Y) const;
	//////////////////////////////////////////////////////////////////////////
    void				SetMazeEdges();
public:
	//first index is column
	//second index is row
    std::vector< std::vector <location> >	m_vvMapa;
    int	size_x;
    int	size_y;
    //type of maze generation algorithm used to generate
    EMazeTypes		maze_type;
    location		empty_location;
};
