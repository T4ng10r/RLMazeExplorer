#include "experiment_test.h"
#include <Data/robot_postion.h>

namespace constants
{
	const int repeat_count(0);
	const int maze_size_x(10);
	const int maze_size_y(10);
	const bool maze_perfect(true);

	const int robot_pos_x(1);
	const int robot_pos_y(1);
	const eRobotDir	dir(ROBOT_EAST_DIR);

	const int end_pos_x(10);
	const int end_pos_y(10);
	const double penalty_value(0.25);
	const double price_value(0.25);
};

experiment_test::experiment_test()
{
	init_settings();
	init_maze();
}

void experiment_test::init_settings()
{
	settings.repeat_count=1;

	maze_settings maze_sett;
	maze_sett.size_x = constants::maze_size_x;
	maze_sett.size_y = constants::maze_size_y;
	settings.mazeSettings = maze_sett;
	robot_postion rob_pos;
	robot_pos.pos_x = constants::robot_pos_x;
	robot_pos.pos_y = constants::robot_pos_y;
	robot_pos.dir = constants::dir

	settings.startPosition = robot_pos;
	settings.target_positions.push_back(std::make_pair(constants::end_pos_x, constants::end_pos_y));
}

void experiment_test::init_maze()
{
	maze maze_data;
	maze_data.load_maze();
}

