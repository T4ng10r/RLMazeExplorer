#include "main_window.h"
#include <Maze/maze_generator.h>

#include <QMouseEvent>
#include <GUI/Drawers/graphics_maze_scene.h>
#include <GUI/single_robot_move_dlg.h>
#include <QGraphicsView>
#include <QPrinter>
#include <Tools/loggers.h>

#include <Data/data_thread.h>
#include <Data/Experiment/CEnviroment.h>
#include <Data/Experiment/CExperiment.h>
#include <Data/Experiment/COneExplorationResultDlg.h>
#include <GUI/ExperimentParams/CExperimentParamsDlg.h>

const int ciStartingMazeWidth = 10;
const int ciStartingMazeHeight = 10;

class main_window_private
{
public:
	main_window_private(main_window * pub);
	~main_window_private();
	void	setup_ui();
	void	create_actions();
	void	setup_dock_widgets();
	void	create_bars();
	void	set_connections();
	void	set_connections_for_dlgs();

	void	initializing();
	void	mouseMoveEvent(QMouseEvent * event);
public:
	main_window * public_;
	QMenuBar *						menubar;
	QMenu *				menuLabirynt;
	QMenu *				menuOkna;
	QMenu *				menuBazaWiedzy;
	QAction *			actionGeneruj;
	QAction *			actionTestuj;
	QAction *			actionMazeConfiguration;
	QAction *			actionRobotConfiguration;
	QAction *			actionExplorationResult;
	QAction *			actionMazeSettings;
	QAction *			actionKBStatistics;
	QAction *			actionExperimentSettings;
	QAction *			actionExperimentResult;
	bool				bAutoGenerate;
	bool				bMazeUpdated;		//labirynt wymaga odrysowania
	QGraphicsView *					m_ptrMazeDraw;
	graphics_maze_scene *			m_ptrMazeScene;

	COneExplorationResultDlg *		cRobotOneExplorationResult;
	//CExperimentManager				m_stExperimentManager;
	CExperiment m_stExperiment;
	//CEnviroment *	pEnviroment;
	QComboBox   * ctrlCombo;
	CExperimentParamsDlg *			m_ptrExperimentParamsDlg;
	single_robot_move_dlg *			m_ptrSingleRobotMove;
};

main_window_private::main_window_private(main_window * pub) : public_(pub)
{
	m_ptrMazeScene = new graphics_maze_scene;
	setup_ui();

	create_actions();
	create_bars();
	setup_dock_widgets();
	set_connections();
	initializing();
}
main_window_private::~main_window_private()
{
	delete m_ptrMazeScene;
}
void main_window_private::setup_ui()
{
	public_->setWindowTitle(QObject::tr("Experiment"));

	m_ptrMazeDraw = new QGraphicsView(public_);
	m_ptrMazeDraw->setScene(m_ptrMazeScene);
	public_->setCentralWidget(m_ptrMazeDraw);

	m_ptrSingleRobotMove = new single_robot_move_dlg;
	public_->addDockWidget(Qt::AllDockWidgetAreas, m_ptrSingleRobotMove);
	m_ptrSingleRobotMove->setFloating(true);
	m_ptrSingleRobotMove->show();
}
void main_window_private::setup_dock_widgets()
{
	//	cRobotOneExplorationResult = new COneExplorationResultDlg(this);
	//	cRobotOneExplorationResult->setAllowedAreas(Qt::RightDockWidgetArea);
	//	addDockWidget(Qt::RightDockWidgetArea, cRobotOneExplorationResult);
	//	cRobotOneExplorationResult->hide();
	//	cRobotOneExplorationResult->setFloating(true);

	m_ptrExperimentParamsDlg = new CExperimentParamsDlg;
	m_ptrExperimentParamsDlg->setAllowedAreas(Qt::BottomDockWidgetArea);
	public_->addDockWidget(Qt::RightDockWidgetArea, m_ptrExperimentParamsDlg);

	actionExperimentSettings = m_ptrExperimentParamsDlg->toggleViewAction();
	actionExperimentSettings->setShortcut(QObject::tr("Ctrl+W"));
	actionExperimentSettings->setStatusTip(QObject::tr("Show window with experiment details"));
	public_->menuBar()->addAction(actionExperimentSettings);
}
void main_window_private::set_connections()
{
	bool bResult = false;
	set_connections_for_dlgs();

	bResult = QObject::connect(&m_stExperiment, SIGNAL(robotBeforeMove(CScanResults *)), m_ptrSingleRobotMove,
					  SLOT(onRobotBeforeMove(CScanResults *)));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(m_ptrSingleRobotMove, SIGNAL(next_robot_move()), &m_stExperiment,
					  SLOT(onnext_robot_move()));
	Q_ASSERT(bResult == true);

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

	bResult = QObject::connect(m_ptrExperimentParamsDlg, SIGNAL(startExperiment(CExperimentSettings &)),
					  public_, SLOT(onStartExploring(CExperimentSettings &)));
	Q_ASSERT(bResult == true);

	//bResult=connect(pEnviroment,SIGNAL(nextExplorationInExperiment()),
	//                m_ptrExperimentParamsDlg,SLOT(nextStepInExperiment()));
	//Q_ASSERT(bResult==true);
}
void main_window_private::set_connections_for_dlgs()
{
	bool bResult = false;

	//	bResult=connect(cExperimentParamsDlg,SIGNAL(getMazeData(CMaze &)),cMazeDraw,SLOT(on_set_maze_data(CMaze &)));
	//	Q_ASSERT(bResult==true);
	//perform generation
	bResult = QObject::connect(m_ptrExperimentParamsDlg, SIGNAL(generate_maze(maze_settings)), gDataThread.get(), SLOT(onPerformMazeGeneration(maze_settings)));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(gDataThread.get(), SIGNAL(maze_generated()), public_, SLOT(on_maze_generated()));
	Q_ASSERT(bResult == true);

	bResult = QObject::connect(m_ptrExperimentParamsDlg, SIGNAL(experimentSettingsChanged(const CExperimentSettings &)),
					  m_ptrMazeScene, SLOT(on_experiment_settings_changed(const CExperimentSettings &)));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(m_ptrExperimentParamsDlg, SIGNAL(experimentSettingsChanged(const CExperimentSettings &)),
					  public_, SLOT(on_experiment_settings_changed(const CExperimentSettings &)));
	Q_ASSERT(bResult == true);
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
void main_window_private::initializing()
{
	bAutoGenerate = false;
	bMazeUpdated = false;

	CExperimentSettings stExpSettings;
	m_ptrExperimentParamsDlg->onSetExperimentSettings(stExpSettings);

	//pEnviroment = new CEnviroment;
}
void main_window_private::create_actions()
{
	actionGeneruj = new QAction(QObject::tr("&Generate"), public_);
	actionGeneruj->setShortcut(QObject::tr("Ctrl+G"));
	actionGeneruj->setStatusTip(QObject::tr("Generate maze"));
	//	connect(actionGeneruj,SIGNAL(triggered()), this,SLOT(on_generate_maze( )));

	actionMazeSettings = new QAction(QObject::tr("&Settings"), public_);
	actionMazeSettings->setStatusTip(QObject::tr("Maze settings"));

	actionKBStatistics = new QAction(QObject::tr("&Statistics"), public_);
	actionKBStatistics->setStatusTip(QObject::tr("Statistics"));
	//	QAction *			actionExperimentResult;
}
void main_window_private::create_bars()
{
	menuLabirynt = public_->menuBar()->addMenu(QObject::tr("&Maze"));
	menuLabirynt->addAction(actionGeneruj);
	menuLabirynt->addAction(actionMazeSettings);
	//	menuOkna = menuBar()->addMenu(tr("&Okno"));
	//	menuBazaWiedzy  = menuBar()->addMenu(tr("&Baza wiedzy"));
	//	menuBazaWiedzy->addAction(actionKBStatistics);
}

//////////////////////////////////////////////////////////////////////////
main_window::main_window() : pimpl(new main_window_private(this))
{
	gDataThread;

    setMinimumSize( 800,650 );
	statusBar()->showMessage(tr("Ready"));
    setMouseTracking(true);
}
main_window::~main_window(){}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void main_window::onRobotDirChange(const QString text)
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
void main_window::on_maze_generated()
{
	pimpl->m_ptrMazeScene->setMaze(gDataThread->get_maze());
	pimpl->m_ptrExperimentParamsDlg->on_experiment_settings_changed();
	////////////////////////////////////////////////////////////////////////
	QPrinter printer(QPrinter::HighResolution);
	printer.setPaperSize(QPrinter::A4);
	printer.setOutputFileName("maze.pdf");
	QPainter painter(&printer);
	pimpl->m_ptrMazeScene->render(&painter);
	painter.end();
}
void main_window::on_experiment_settings_changed(const CExperimentSettings & xExpSettings)
{
	pimpl->m_stExperiment.setExperimentSettings(xExpSettings);
	//m_stExperimentManager.getCurrentExperiment().setExperimentSettings(xExpSettings);
}

//////////////////////////////////////////////////////////////////////////
void main_window::onRobotPosChanged()
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
void	main_window::onStartExploring(CExperimentSettings & xExpSettings)
{
	pimpl->m_stExperiment.setExperimentSettings(xExpSettings);
	pimpl->m_stExperiment.startExperiment();
	//m_stExperimentManager.getCurrentExperiment().startExperiment();
    //pEnviroment->startExploring();
}
void	main_window::mouseMoveEvent(QMouseEvent * event)
{
    Qt::MouseButtons	Buttons;
    int x =0;
    Buttons = event->buttons();
    if (Buttons & Qt::LeftButton)
    {
        x =1;
    }
}