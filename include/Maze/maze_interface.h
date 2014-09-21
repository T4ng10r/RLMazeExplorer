#pragma once

#include <Maze/location.h>
#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>
#include <fstream>

class maze_interface
{
public:
	virtual int get_size_x() const = 0;
	virtual int get_size_y() const = 0;
	virtual void save_maze(std::ofstream stream) = 0;
	virtual bool load_maze(std::ifstream stream) = 0;

	virtual boost::optional<location> get_location(int X, int Y) const = 0;
};

typedef boost::shared_ptr<maze_interface> maze_interface_type;
