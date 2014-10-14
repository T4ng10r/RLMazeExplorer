#include "experiment_settings.h"

namespace constants
{
	const int repeat_count(0);
	const int maze_size_x(10);
	const int maze_size_y(10);
	const bool maze_perfect(true);
	const EMazeTypes maze_type(E_MT_KRUSKAL);

	const int robot_pos_x(1);
	const int robot_pos_y(1);
	const int end_pos_x(10);
	const int end_pos_y(10);
	const double penalty_value(0.25);
	const double price_value(0.25);
};

experiment_settings::experiment_settings(void)
{
	reset();
}

experiment_settings::~experiment_settings(void)
{
}

void experiment_settings::reset()
{
	repeat_count = constants::repeat_count;
	CRobotPostion robotPos;
	mazeSettings.size_x = constants::maze_size_x;
	mazeSettings.size_y = constants::maze_size_y;
	mazeSettings.bMazePerfect = constants::maze_perfect;
	mazeSettings.mazeType = constants::maze_type;

	robotPos.posX = constants::robot_pos_x;
	robotPos.posY = constants::robot_pos_y;
	startPosition = robotPos;

	QPoint pos;

	pos.setX(constants::end_pos_x);
	pos.setY(constants::end_pos_y);
	lFinishPositions.clear();
	lFinishPositions.push_back(pos);
	fPenaltyValue = constants::penalty_value;
	fPriceValue = constants::price_value;
}
