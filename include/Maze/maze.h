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
	void save_maze(const std::string& file_path);
	bool load_maze(const std::string& file_path);
	void reset_locations();
	void resize();

	boost::optional<location> get_location(int x, int y) const;
	location & get_xlocation(int x, int y);
	//////////////////////////////////////////////////////////////////////////
	void preset_maze_edges();
public:
	//first index is column
	//second index is row
	std::vector< std::vector<location> > m_vvMapa;
	int size_x;
	int size_y;
	//type of maze generation algorithm used to generate
	EMazeTypes type;
	location empty_location;
};
