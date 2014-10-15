#include <QApplication>
#include <GUI/main_window.h>

#include <Tools/loggers.h>
#include <memory>
//#include <boost/scoped_ptr.hpp>

#include <GUI/experiment_parameters/experiment_maze_params_dlg.h>

int main(int argc, char **argv)
{
	QApplication    app(argc, argv);
	app.setApplicationName("MazeExplorer");
	app.setOrganizationName("T4ng10r");
	createLoggers();

	std::unique_ptr<experiment_maze_params_dlg> experiment_maze_params_dlg_(new experiment_maze_params_dlg);
	experiment_maze_params_dlg_->show();

	std::unique_ptr<main_window> main_window_(new main_window);
	main_window_->show();
	return app.exec();
}
