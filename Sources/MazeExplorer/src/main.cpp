#include <QApplication>
#include <QString>
#include <QPushButton>
#include <QtCore/QTextCodec>
#include <Gui/MainWindow.h>

#include <QGraphicsView>
//#include <Maze/CMazeGenerator.h>
//#include "CGraphicsMazeScene.h"
//#include "EnviromentVariables.h"
//////////////////////////////////////////////////////////////////////////
#include <Tools/loggers.h>

int main(int argc, char **argv)
{
    createLoggers();
    //Log4Qt::Logger::logger("Process")->info("Program start");
    QApplication    app(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName ("System"));
    //
    MainWindow * Maze=new MainWindow;

	Maze->show();

    return app.exec();
}
