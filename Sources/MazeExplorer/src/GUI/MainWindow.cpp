#include "MainWindow.h"
#include <Maze/maze_generator.h>

#include <QMouseEvent>
#include <Gui/Drawers/graphics_maze_scene.h>
#include <Gui/CSingleRobotMoveDlg.h>
#include <QGraphicsView>
#include <QPrinter>
#include <Tools/loggers.h>

#include <Data/data_thread.h>

MainWindow::MainWindow()
{
	gDataThread;

    setMinimumSize( 800,650 );

	m_ptrMazeScene = new graphics_maze_scene;
	setupUI();

    createActions();
    createBars();
    setupUIDockWidgets();
    statusBar()->showMessage(tr("Ready"));
	setConnections();
	initializing();

    setMouseTracking(true);
}
MainWindow::~MainWindow()
{
	delete m_ptrMazeScene;
}
void	MainWindow::setupUI()
{
	setWindowTitle(tr("Eksperyment"));

	m_ptrMazeDraw = new QGraphicsView(this);
	m_ptrMazeDraw->setScene(m_ptrMazeScene);
	setCentralWidget(m_ptrMazeDraw);

	m_ptrSingleRobotMove = new CSingleRobotMoveDlg;
	addDockWidget(Qt::AllDockWidgetAreas,m_ptrSingleRobotMove);
	m_ptrSingleRobotMove->setFloating(true);
	m_ptrSingleRobotMove->show();
}
void	MainWindow::setupUIDockWidgets()
{
	//	cRobotOneExplorationResult = new COneExplorationResultDlg(this);
	//	cRobotOneExplorationResult->setAllowedAreas(Qt::RightDockWidgetArea);
	//	addDockWidget(Qt::RightDockWidgetArea, cRobotOneExplorationResult);
	//	cRobotOneExplorationResult->hide();
	//	cRobotOneExplorationResult->setFloating(true);

	m_ptrExperimentParamsDlg = new CExperimentParamsDlg;
	m_ptrExperimentParamsDlg->setAllowedAreas(Qt::BottomDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, m_ptrExperimentParamsDlg);

	actionExperimentSettings = m_ptrExperimentParamsDlg->toggleViewAction();
	actionExperimentSettings->setShortcut(tr("Ctrl+W"));
	actionExperimentSettings->setStatusTip(tr("Poka� okno ze szczeg�lami przygotowanego eksperymentu"));
	menuBar()->addAction(actionExperimentSettings);
}
void	MainWindow::setConnections()
{
    bool bResult=false;
    setConnectionsForDlgs();

	bResult=connect(&m_stExperiment,SIGNAL(robotBeforeMove(CScanResults *)),m_ptrSingleRobotMove,
		SLOT(onRobotBeforeMove(CScanResults *)));
	Q_ASSERT(bResult==true);
	bResult=connect(m_ptrSingleRobotMove,SIGNAL(nextRobotMove()),&m_stExperiment,
		SLOT(onNextRobotMove()));
	Q_ASSERT(bResult==true);

	//////////////////////////////////////////////////////////////////////////
//    bResult=connect(pEnviroment,SIGNAL(robotFinished(CExplorationResult &)),
//                    cMazeDraw,SLOT(onSetRobotRoute(CExplorationResult & )));
//    Q_ASSERT(bResult==true);

//	bResult=connect(cMazeDraw,SIGNAL(SelectRoutePos(int)),cRobotOneExplorationResult->explorationResult,SLOT(selectRow(int)));
//	Q_ASSERT(bResult==true);

//	bResult=connect(cRobotOneExplorationResult->explorationResult,
//		SIGNAL(currentItemChanged ( QTableWidgetItem * , QTableWidgetItem *  )),
//		cMazeDraw, SLOT(onSetRobotRouteLocation( QTableWidgetItem * , QTableWidgetItem *  )));
//	Q_ASSERT(bResult==true);

//	bResult=connect(cRobotOneExplorationResult->explorationResult,SIGNAL(cellClicked ( int , int )),
//		cMazeDraw,SLOT(onCellSelected( int , int )));
//	Q_ASSERT(bResult==true);

//	bResult=connect(cRobotOneExplorationResult->explorationResult,SIGNAL(cellClicked ( int , int )),
//		cMazeDraw,SLOT(onCellSelected( int , int )));
//	Q_ASSERT(bResult==true);

    bResult=connect(m_ptrExperimentParamsDlg,SIGNAL(startExperiment(CExperimentSettings & )),
                    SLOT(onStartExploring(CExperimentSettings &)));
    Q_ASSERT(bResult==true);

    //bResult=connect(pEnviroment,SIGNAL(nextExplorationInExperiment()),
    //                m_ptrExperimentParamsDlg,SLOT(nextStepInExperiment()));
    //Q_ASSERT(bResult==true);
}
void	MainWindow::setConnectionsForDlgs()
{
    bool bResult=false;

//	bResult=connect(cExperimentParamsDlg,SIGNAL(getMazeData(CMaze &)),cMazeDraw,SLOT(on_set_maze_data(CMaze &)));
//	Q_ASSERT(bResult==true);
	//perform generation
	bResult = connect(m_ptrExperimentParamsDlg, SIGNAL(generateMaze(maze_settings)), gDataThread.get(), SLOT(onPerformMazeGeneration(maze_settings)));
    Q_ASSERT(bResult==true);
	bResult = connect(gDataThread.get(), SIGNAL(maze_generated()), SLOT(on_maze_generated()));
	Q_ASSERT(bResult==true);

	bResult=connect(m_ptrExperimentParamsDlg,SIGNAL(experimentSettingsChanged(const CExperimentSettings &)),
		m_ptrMazeScene,SLOT(onExperimentSettingsChanged(const CExperimentSettings &)));
	Q_ASSERT(bResult==true);
	bResult=connect(m_ptrExperimentParamsDlg,SIGNAL(experimentSettingsChanged(const CExperimentSettings &)),
		SLOT(onExperimentSettingsChanged(const CExperimentSettings &)));
	Q_ASSERT(bResult==true);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //bResult=connect(cMazeDraw,SIGNAL(onNewStartPosition(int ,int )),
    //                cExperimentParamsDlg,SLOT(onNewStartPosition(int ,int)));
    //Q_ASSERT(bResult==true);
    //bResult=connect(cMazeDraw,SIGNAL(onNewFinishPosition(int ,int )),
    //                cExperimentParamsDlg,SLOT(onNewFinishPosition(int ,int)));
    //Q_ASSERT(bResult==true);
//	bResult=connect(cMazeDraw,SIGNAL(setNextFinishPosition(int ,int )),
//			cExperimentParamsDlg->widgetExperimentParam,SLOT(onAddFinishPosition(int ,int)));
//	Q_ASSERT(bResult==true);
//	bResult=connect(pEnviroment,SIGNAL(redrawMaze()),cMazeDraw,SLOT(update()));
//	Q_ASSERT(bResult==true);


//	connect(cMazeDraw,SIGNAL(setFinishPosition(int ,int )),cExperimentParamsDlg,SLOT(onRobotPosChanged()));
//	connect(cExperimentParamsDlg->spinStartY,SIGNAL(setFinishPosition(int ,int )),this,SLOT(onRobotPosChanged()));
//	connect(cMazeDraw,SIGNAL(setNextFinishPosition(int ,int )),this,SLOT(onRobotPosChanged()));
}
//////////////////////////////////////////////////////////////////////////
void MainWindow::initializing()
{
	bAutoGenerate=false;
	bMazeUpdated=false;

	CExperimentSettings stExpSettings;
	m_ptrExperimentParamsDlg->onSetExperimentSettings(stExpSettings);

	//pEnviroment = new CEnviroment;
}
//////////////////////////////////////////////////////////////////////////
void	MainWindow::onRobotDirChange(const QString text)
{
	eRobotDir dir;
	if (text == "North")
		dir = ROBOT_NORTH_DIR;
	else if (text == "West")
		dir = ROBOT_WEST_DIR;
	else if (text == "South")
		dir = ROBOT_SOUTH_DIR;
	else if (text == "East")
		dir = ROBOT_EAST_DIR;

	//	pEnviroment->setRobotDir(dir);
}
void	MainWindow::on_maze_generated()
{
	m_ptrMazeScene->setMaze(gDataThread->get_maze());
	m_ptrExperimentParamsDlg->onExperimentSettingsChanged();
	////////////////////////////////////////////////////////////////////////
	QPrinter printer(QPrinter::HighResolution);
	printer.setPaperSize(QPrinter::A4);
	printer.setOutputFileName("maze.pdf");
	QPainter painter(&printer);
	m_ptrMazeScene->render(&painter);
	painter.end();
}
void MainWindow::onExperimentSettingsChanged(const CExperimentSettings & xExpSettings)
{
	m_stExperiment.setExperimentSettings(xExpSettings);
	//m_stExperimentManager.getCurrentExperiment().setExperimentSettings(xExpSettings);
}
//////////////////////////////////////////////////////////////////////////
void	MainWindow::onRobotPosChanged()
{
//	int X=cRobotConfigurationDlg->startXSpin->value();
//	int Y=cRobotConfigurationDlg->startYSpin->value();
//	cMazeDraw->setStartPos(X,Y);
//	pEnviroment->setRobotStartPos(X,Y);
//	X=cRobotConfigurationDlg->endXSpin->value();
//	Y=cRobotConfigurationDlg->endYSpin->value();
//	cMazeDraw->setFinishPos(X,Y);
//	pEnviroment->setRobotFinishPos(X,Y);
//	cMazeDraw->update();
}
void	MainWindow::onStartExploring(CExperimentSettings & xExpSettings)
{
	m_stExperiment.setExperimentSettings(xExpSettings);
	m_stExperiment.startExperiment();
	//m_stExperimentManager.getCurrentExperiment().startExperiment();
    //pEnviroment->startExploring();
}
void	MainWindow::createActions()
{
    actionGeneruj = new QAction(tr("&Generuj"), this);
    actionGeneruj->setShortcut(tr("Ctrl+G"));
    actionGeneruj->setStatusTip(tr("Generuj labirynt"));
//	connect(actionGeneruj,SIGNAL(triggered()), this,SLOT(onGenerateMaze( )));

    actionMazeSettings = new QAction(tr("&Ustawienia"), this);
    actionMazeSettings->setStatusTip(tr("Ustawienia labiryntu"));

    actionKBStatistics = new QAction(tr("&Statystyki"), this);
    actionKBStatistics->setStatusTip(tr("Statystyki"));
//	QAction *			actionExperimentResult;
}
void	MainWindow::createBars()
{
    menuLabirynt = menuBar()->addMenu(tr("&Labirynt"));
    menuLabirynt->addAction(actionGeneruj);
    menuLabirynt->addAction(actionMazeSettings);
//	menuOkna = menuBar()->addMenu(tr("&Okno"));
//	menuBazaWiedzy  = menuBar()->addMenu(tr("&Baza wiedzy"));
//	menuBazaWiedzy->addAction(actionKBStatistics);
}
void	MainWindow::mouseMoveEvent(QMouseEvent * event)
{
    Qt::MouseButtons	Buttons;
    int x =0;
    Buttons = event->buttons();
    if (Buttons & Qt::LeftButton)
    {
        x =1;
    }
}
