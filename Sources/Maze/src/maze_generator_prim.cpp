#include "maze_generator_prim.h"
#include "maze.h"
#include <time.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <Tools/loggers.h>
#include <boost/format.hpp>
#include <time.h>       /* time */

class maze_generator_prim_private
{
public:
	maze_generator_prim_private();
	unsigned int get_bits_size(unsigned int test_value);
	void reset_locations();
	void allocate_locations_table();
	void store_edges(unsigned int cell_id);
	void join_locations(unsigned int start_id, unsigned int end_id);

	unsigned int randomly_select_edge();

	void generate_maze();
    unsigned int make_id(unsigned int X, unsigned int Y);

    void MakeNotPerfect();

	unsigned int                size_x, size_y;
    unsigned int                edge_count;
    unsigned int                nodes_count;
	unsigned int                locations_id_mask;
	boost::shared_ptr<maze>     maze_data;
	std::set<unsigned int>      visited_cells;
	std::vector<unsigned int>   to_be_visited_edges;
};
maze_generator_prim_private::maze_generator_prim_private() :maze_data(new maze){}
unsigned int maze_generator_prim_private::get_bits_size(unsigned int test_value)
{
	unsigned int val(2);
	unsigned int bits_count(1);
	while (val < test_value)
	{
		val <<= 1;
		bits_count++;
	};
	return bits_count;
}
void maze_generator_prim_private::reset_locations()
{
	//int index1,index2;
	for (unsigned int index1 = 0; index1 < size_x; index1++)
		for (unsigned int index2 = 0; index2 < size_y; index2++)
			maze_data->m_vvMapa[index1][index2].reset();
}
void maze_generator_prim_private::allocate_locations_table()
{
	maze_data->size_x = size_x;
	maze_data->size_y = size_y;

	unsigned int edge_count = 2 * size_x*size_y - size_y - size_x;
	locations_id_mask = get_bits_size(edge_count);

	maze_data->m_vvMapa.resize(size_x);
	for (unsigned int index = 0; index < size_x; index++)
		maze_data->m_vvMapa[index].resize(size_y);
	reset_locations();
}
void maze_generator_prim_private::store_edges(unsigned int cell_id)
{
	unsigned int x(cell_id % size_x);
	unsigned int y(cell_id / size_y);
	unsigned int new_id(0);
	location & loc = maze_data->get_xlocation(x, y);
	if (loc.is_wall(NORTH_DIR) && y > 0)
	{
		new_id = make_id(x, y - 1);
		to_be_visited_edges.push_back(make_id(x, y) + (new_id << locations_id_mask));
	}
	if (loc.is_wall(SOUTH_DIR) && y < (size_y -1))
	{
		new_id = make_id(x, y + 1);
		to_be_visited_edges.push_back(make_id(x, y) + (new_id << locations_id_mask));
	}

	if (loc.is_wall(WEST_DIR) && x > 0)
	{
		new_id = make_id(x - 1, y);
		to_be_visited_edges.push_back(make_id(x, y) + (new_id << locations_id_mask));
	}
	if (loc.is_wall(EAST_DIR) && x < (size_x - 1))
	{
		new_id = make_id(x + 1, y);
		to_be_visited_edges.push_back(make_id(x, y) + (new_id << locations_id_mask));
	}

}
unsigned int maze_generator_prim_private::randomly_select_edge()
{
	unsigned int cell_id(0);
	unsigned int edge_id;
	do
	{
		unsigned int random_index = rand() % to_be_visited_edges.size();
		std::vector<unsigned int>::iterator it = to_be_visited_edges.begin();
		std::advance(it, random_index);
		edge_id = *it;
		to_be_visited_edges.erase(it);
		cell_id = edge_id >> locations_id_mask;
	} while (visited_cells.count(cell_id) && to_be_visited_edges.size());
	return edge_id;
}
void maze_generator_prim_private::join_locations(unsigned int start_id, unsigned int end_id)
{
	unsigned int start_x = start_id % size_x;
	unsigned int start_y = start_id / size_y;
	unsigned int dest_x = end_id % size_x;
	unsigned int dest_y = end_id / size_y;

	location& start_loc = maze_data->get_xlocation(start_x, start_y);
	location& end_loc = maze_data->get_xlocation(dest_x, dest_y);
	//jeœlie nie - usuñ scianê z obu lokacji i po³¹cz ich zbiory
	if (start_x == dest_x)
	{
		if (start_y > dest_y)
		{
			start_loc.set_passage(NORTH_DIR);
			end_loc.set_passage(SOUTH_DIR);
		}
		else
		{
			start_loc.set_passage(SOUTH_DIR);
			end_loc.set_passage(NORTH_DIR);
		}
	}
	else {
		if (start_x > dest_x)
		{
			start_loc.set_passage(WEST_DIR);
			end_loc.set_passage(EAST_DIR);
		}
		else
		{
			start_loc.set_passage(EAST_DIR);
			end_loc.set_passage(WEST_DIR);
		}
	}
}
void maze_generator_prim_private::generate_maze()
{
	srand(time(NULL));
	//initial cell
	unsigned int cell_id(make_id(size_x/2, size_y/2));
	do 
	{
		visited_cells.insert(cell_id);
		store_edges(cell_id);
		unsigned int edge_id = randomly_select_edge();
		cell_id = edge_id >> locations_id_mask;
		unsigned int visited_cell_id = edge_id - (cell_id << locations_id_mask);


		if (!visited_cells.count(cell_id))
		{
			join_locations(visited_cell_id, cell_id);
		}

	} while (!to_be_visited_edges.empty());

}
unsigned int maze_generator_prim_private::make_id(unsigned int x, unsigned int y)
{
	return (x + y*size_x);
}
//////////////////////////////////////////////////////////////////////////
maze_generator_prim::maze_generator_prim() : pimpl(new maze_generator_prim_private){}
maze_generator_prim::~maze_generator_prim(){}
boost::shared_ptr<maze_interface> maze_generator_prim::generate_maze(const maze_settings & settings)
{
	pimpl->size_x = settings.size_x;
	pimpl->size_y = settings.size_y;
	pimpl->allocate_locations_table();
	pimpl->maze_data->preset_maze_edges();
	pimpl->generate_maze();
	return pimpl->maze_data;
}
