#ifndef  MAINWINDOW_H
#define  MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QDockWidget>
#include <QMenuBar>
#include <QStatusBar>

#include <Data/Experiment/CEnviroment.h>
#include <Data/Experiment/CExperiment.h>
#include <Data/Experiment/COneExplorationResultDlg.h>
#include <GUI/ExperimentParams/CExperimentParamsDlg.h>

class graphics_maze_scene;
class QGraphicsView;
class CSingleRobotMoveDlg;
class CDataThread;

const int ciStartingMazeWidth=10;
const int ciStartingMazeHeight=10;

class MainWindow : public QMainWindow
{
    //friend class CMazeDraw;
    Q_OBJECT
public:
    MainWindow();
	~MainWindow();

	//CExperimentManager				m_stExperimentManager;
	CExperiment m_stExperiment;
    //CEnviroment *	pEnviroment;
    QComboBox   * ctrlCombo;
    CExperimentParamsDlg *			m_ptrExperimentParamsDlg;
	graphics_maze_scene *			m_ptrMazeScene;
	QGraphicsView *					m_ptrMazeDraw;
    COneExplorationResultDlg *		cRobotOneExplorationResult;
	CSingleRobotMoveDlg *			m_ptrSingleRobotMove;

protected:
	void	setupUI();
	void	createActions();
	void	setupUIDockWidgets();
	void	createBars();
	void	setConnections();
	void	setConnectionsForDlgs();

	void	initializing();
	void	mouseMoveEvent(QMouseEvent * event);

protected:
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

public Q_SLOTS:
	//generate maze according to params from dock window and send this maze to environment
	void	on_maze_generated();

	//there were some changes in start or end position - udpate maze drawer
    void	onExperimentSettingsChanged(const CExperimentSettings & xExperimentSettings);

    void	onRobotPosChanged();
    void	onStartExploring(CExperimentSettings &);
    void	onRobotDirChange(const QString text);
Q_SIGNALS:
	void	generateMaze(maze_settings);

};
#endif
