#pragma once

#include <memory>
#include <QWidget>
#include <Maze/maze_settings.h>

class experiment_maze_params_dlg_private;

class experiment_maze_params_dlg : public QWidget
{
    Q_OBJECT
public:
	experiment_maze_params_dlg(QWidget *parent = 0);
	~experiment_maze_params_dlg();
	void set_maze_settings(maze_settings & stMazeSettings);
	void get_maze_settings(maze_settings & stMazeSettings);

Q_SIGNALS:
	void generate_maze(maze_settings);
protected Q_SLOTS:
	//reaction on Generate Maze button click
	void on_generate_maze(bool);
	void on_load_maze(bool);
	void on_save_maze(bool);
	void on_load_maze_browse(bool);
	void on_save_maze_browse(bool);
protected:
	std::unique_ptr<experiment_maze_params_dlg_private> pimpl;
};
