#pragma once
#include <QGraphicsScene>
#include <Data/experiment/experiment_settings.h>
#include <Maze/maze_interface.h>
#include <memory>

class graphics_maze_scene_private;

class graphics_maze_scene : public QGraphicsScene
{
    Q_OBJECT
public:
	graphics_maze_scene();
	~graphics_maze_scene();
	void setMaze(maze_interface_type maze_data);

public Q_SLOTS:
	void on_experiment_settings_changed(const experiment_settings & xExperimentSettings);

protected:
	std::unique_ptr<graphics_maze_scene_private>  pimpl;
};
