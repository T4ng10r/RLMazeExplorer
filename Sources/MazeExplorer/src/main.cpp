#include <QApplication>
//#include <QString>
//#include <QtCore/QTextCodec>
#include <Gui/MainWindow.h>

#include <QGraphicsView>
//#include <Maze/CMazeGenerator.h>
//#include "CGraphicsMazeScene.h"
//#include "EnviromentVariables.h"
//////////////////////////////////////////////////////////////////////////
#include <Tools/loggers.h>
#include <boost/scoped_ptr.hpp>

int main(int argc, char **argv)
{
    createLoggers();
    QApplication    app(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName ("System"));
	app.setApplicationName("MazeExplorer");
	app.setOrganizationName("T4ng10r");
	createLoggers();

	boost::scoped_ptr<MainWindow> main_window(new MainWindow);
	main_window->show();
	return app.exec();
}
