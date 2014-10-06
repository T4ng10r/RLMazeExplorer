#include <QApplication>
#include <GUI/main_window.h>

#include <Tools/loggers.h>
#include <boost/scoped_ptr.hpp>

int main(int argc, char **argv)
{
    QApplication    app(argc, argv);
	app.setApplicationName("MazeExplorer");
	app.setOrganizationName("T4ng10r");
	createLoggers();

	boost::scoped_ptr<main_window> main_window(new main_window);
	main_window->show();
	return app.exec();
}
