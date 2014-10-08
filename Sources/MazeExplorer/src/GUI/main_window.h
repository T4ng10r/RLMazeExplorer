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
#include <Data/experiment/CExperimentSettings.h>

class main_window_private;

class main_window : public QMainWindow
{
    Q_OBJECT
public:
    main_window();
	~main_window();

protected:
	std::unique_ptr<main_window_private>  pimpl;
	void mousePressEvent(QMouseEvent * e);;

public Q_SLOTS:
	//generate maze according to params from dock window and send this maze to environment
	void on_maze_generated();

	//there were some changes in start or end position - udpate maze drawer
    void on_experiment_settings_changed(const experiment_settings & xExperimentSettings);

    void onRobotPosChanged();
    void onStartExploring(experiment_settings &);
    void onRobotDirChange(const QString text);
Q_SIGNALS:
	void generate_maze(maze_settings);

};
#endif
