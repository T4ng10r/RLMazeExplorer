#pragma once
#include <QGraphicsScene>
#include <Data/Experiment/CExperimentSettings.h>
#include <Maze/maze_interface.h>
#include <boost/scoped_ptr.hpp>

class graphics_maze_scene_private;

class graphics_maze_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    graphics_maze_scene();
	void setMaze(maze_interface_type maze_data);

public Q_SLOTS:
	void onExperimentSettingsChanged(const CExperimentSettings & xExperimentSettings);

protected:
	boost::scoped_ptr<graphics_maze_scene_private>  pimpl;
};
