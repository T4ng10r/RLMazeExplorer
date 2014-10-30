#pragma once

#include <Maze/location.h>
#include <memory>
#include <boost/optional.hpp>
#include <string>

class maze_interface
{
public:
	virtual int get_size_x() const = 0;
	virtual int get_size_y() const = 0;
	virtual void save_maze(const std::string& file_path) = 0;
	virtual bool load_maze(const std::string& file_path) = 0;

	virtual boost::optional<location> get_location(unsigned int X, unsigned int Y) const = 0;
};

typedef std::shared_ptr<maze_interface> maze_interface_type;
