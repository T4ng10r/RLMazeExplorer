#include <QApplication>
#include <QString>
#include <QPushButton>
#include <QtCore/QTextCodec>
#include <Gui/MainWindow.h>

#include <QtGui/QGraphicsView>
//#include <Maze/CMazeGenerator.h>
//#include "CGraphicsMazeScene.h"
//#include "EnviromentVariables.h"
//////////////////////////////////////////////////////////////////////////
#include <log4qt/consoleappender.h>
#include <log4qt/fileappender.h>
#include <log4qt/logger.h>
#include <log4qt/ttcclayout.h>


void createLoggers()
{
    // Create a layout
    Log4Qt::Logger::logger("Process");
    Log4Qt::TTCCLayout *p_layout = new Log4Qt::TTCCLayout();
	p_layout->setDateFormat("ISO8601");
    p_layout->setName(QLatin1String("My Layout"));
    p_layout->activateOptions();
    // Create an appender
    Log4Qt::FileAppender * pFileAppender = new Log4Qt::FileAppender(p_layout, "process.log");
    pFileAppender->setName(QLatin1String("Process FileAppender"));
    pFileAppender->activateOptions();
    Log4Qt::Logger::logger("Process")->addAppender(pFileAppender);
	//////////////////////////////////////////////////////////////////////////
	Log4Qt::Logger::logger("MazeKB");
	Log4Qt::TTCCLayout *p_MazeKBlayout = new Log4Qt::TTCCLayout();
	p_MazeKBlayout->setDateFormat("ISO8601");
	p_MazeKBlayout->setName(QLatin1String("Maze KB Layout"));
	p_MazeKBlayout->activateOptions();
	// Create an appender
	Log4Qt::FileAppender * pFileKBAppender = new Log4Qt::FileAppender(p_MazeKBlayout, "maze_kb.log");
	pFileKBAppender->setName(QLatin1String("Maze KB FileAppender"));
	pFileKBAppender->activateOptions();
	// Set appender on root logger
	Log4Qt::Logger::logger("MazeKB")->addAppender(pFileKBAppender);
};
int main(int argc, char **argv)
{
    createLoggers();
    Log4Qt::Logger::logger("Process")->info("Program start");
    QApplication    app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName ("System"));
    //
    MainWindow * Maze=new MainWindow;

	Maze->show();

    return app.exec();
}
