#include "main_window.h"
#include <Maze/maze_generator.h>

#include <QMouseEvent>
#include <GUI/Drawers/graphics_maze_scene.h>
#include <GUI/single_robot_move_dlg.h>
#include <QGraphicsView>
#include <QPrinter>
#include <Tools/loggers.h>

#include <Data/data_thread.h>
#include <Data/experiment/CEnviroment.h>
#include <Data/experiment/CExperiment.h>
#include <Data/experiment/COneExplorationResultDlg.h>
#include <GUI/experiment_parameters/experiment_parameters_dlg.h>

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
	QGraphicsView *					maze_draw_view;
	graphics_maze_scene *			maze_scene;

	COneExplorationResultDlg *		cRobotOneExplorationResult;
	//CExperimentManager				m_stExperimentManager;
	CExperiment m_stExperiment;
	//CEnviroment *	pEnviroment;
	QComboBox   * ctrlCombo;
	experiment_parameters_dlg *			m_ptrExperimentParamsDlg;
	single_robot_move_dlg *			single_robot_move;
};

main_window_private::main_window_private(main_window * pub) : public_(pub)
{
	maze_scene = new graphics_maze_scene;
	setup_ui();

	create_actions();
	create_bars();
	setup_dock_widgets();
	set_connections();
	initializing();
}
main_window_private::~main_window_private()
{
	delete maze_scene;
}
void main_window_private::setup_ui()
{
	maze_draw_view = new QGraphicsView(public_);
	maze_draw_view->setScene(maze_scene);
	public_->setCentralWidget(maze_draw_view);

}
void main_window_private::setup_dock_widgets()
{
	public_->setDockNestingEnabled(true);
	//	cRobotOneExplorationResult = new COneExplorationResultDlg(this);
	//	cRobotOneExplorationResult->setAllowedAreas(Qt::RightDockWidgetArea);
	//	addDockWidget(Qt::RightDockWidgetArea, cRobotOneExplorationResult);
	//	cRobotOneExplorationResult->hide();
	//	cRobotOneExplorationResult->setFloating(true);

	m_ptrExperimentParamsDlg = new experiment_parameters_dlg;
	m_ptrExperimentParamsDlg->setAllowedAreas(Qt::BottomDockWidgetArea);
	public_->addDockWidget(Qt::RightDockWidgetArea, m_ptrExperimentParamsDlg);

	actionExperimentSettings = m_ptrExperimentParamsDlg->toggleViewAction();
	actionExperimentSettings->setShortcut(QObject::tr("Ctrl+W"));
	actionExperimentSettings->setStatusTip(QObject::tr("Show window with experiment details"));
	public_->menuBar()->addAction(actionExperimentSettings);

	single_robot_move = new single_robot_move_dlg;
	public_->addDockWidget(Qt::RightDockWidgetArea, single_robot_move);
	//m_ptrSingleRobotMove->setFloating(true);
	//m_ptrSingleRobotMove->show();
}
void main_window_private::set_connections()
{
	bool bResult = false;
	set_connections_for_dlgs();

	bResult = QObject::connect(&m_stExperiment, SIGNAL(robotBeforeMove(CScanResults *)), single_robot_move,
					  SLOT(onRobotBeforeMove(CScanResults *)));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(single_robot_move, SIGNAL(next_robot_move()), &m_stExperiment,
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

	bResult = QObject::connect(m_ptrExperimentParamsDlg, SIGNAL(startExperiment(experiment_settings &)),
					  public_, SLOT(onStartExploring(experiment_settings &)));
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

	bResult = QObject::connect(m_ptrExperimentParamsDlg, SIGNAL(experimentSettingsChanged(const experiment_settings &)),
					  maze_scene, SLOT(on_experiment_settings_changed(const experiment_settings &)));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(m_ptrExperimentParamsDlg, SIGNAL(experimentSettingsChanged(const experiment_settings &)),
					  public_, SLOT(on_experiment_settings_changed(const experiment_settings &)));
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

	experiment_settings stExpSettings;
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
	pimpl->maze_scene->setMaze(gDataThread->get_maze());
	pimpl->m_ptrExperimentParamsDlg->on_experiment_settings_changed();
	////////////////////////////////////////////////////////////////////////
	QPrinter printer(QPrinter::HighResolution);
	printer.setPaperSize(QPrinter::A4);
	printer.setOutputFileName("maze.pdf");
	QPainter painter(&printer);
	pimpl->maze_scene->render(&painter);
	painter.end();
}
void main_window::on_experiment_settings_changed(const experiment_settings & xExpSettings)
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
void	main_window::onStartExploring(experiment_settings & xExpSettings)
{
	pimpl->m_stExperiment.setExperimentSettings(xExpSettings);
	pimpl->m_stExperiment.startExperiment();
	//m_stExperimentManager.getCurrentExperiment().startExperiment();
    //pEnviroment->startExploring();
}
void main_window::mousePressEvent(QMouseEvent * e)
{
	Qt::MouseButtons	Buttons;
	Buttons = e->buttons();

}
