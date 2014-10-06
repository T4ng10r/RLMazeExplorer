#ifndef  MAINWINDOW_H
#define  MAINWINDOW_H

#include <memory>
#include <QMainWindow>

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QDockWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <Data/Experiment/CExperimentSettings.h>

class main_window_private;

class main_window : public QMainWindow
{
    Q_OBJECT
public:
    main_window();
	~main_window();

protected:
	std::unique_ptr<main_window_private>  pimpl;
	void mouseMoveEvent(QMouseEvent * event);

public Q_SLOTS:
	//generate maze according to params from dock window and send this maze to environment
	void on_maze_generated();

	//there were some changes in start or end position - udpate maze drawer
    void on_experiment_settings_changed(const CExperimentSettings & xExperimentSettings);

    void onRobotPosChanged();
    void onStartExploring(CExperimentSettings &);
    void onRobotDirChange(const QString text);
Q_SIGNALS:
	void generate_maze(maze_settings);

};
#endif
