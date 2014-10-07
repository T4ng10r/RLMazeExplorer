#pragma once
#include <QDockWidget>
#include <QObject>
#include <Data/Experiment/CExperimentSettings.h>
#include <vector>
#include <utility>
#include <memory>

class experiment_parameters_dlg_private;
#define TREAT_WINDOW_AS_DOCKWIDGET

class experiment_parameters_dlg : 
#ifdef TREAT_WINDOW_AS_DOCKWIDGET
	public QDockWidget
#else
	public QDialog
#endif
{
    Q_OBJECT
public:
	experiment_parameters_dlg(QWidget *parent = NULL);
	~experiment_parameters_dlg();
Q_SIGNALS:
    void on_set_start_position(int ,int);
    void setFinishPosition(int ,int);
	void setFinishPosition(std::vector< std::pair<int, int> >);
	void generate_maze(maze_settings);
    void experimentSettingsChanged(const CExperimentSettings &);
    //xMazeSettings
    void startExperiment(CExperimentSettings & cExperimentSettings);
    void setStartDirection(int);
public Q_SLOTS:
	void onSetExperimentSettings(CExperimentSettings & cExperimentSettings);
    void onNewStartPosition(int ,int);
    void onNewFinishPosition(int ,int);
    void onAddFinishPosition(int ,int);
    void resetExperimentStatus();
    void nextStepInExperiment();
	void on_experiment_settings_changed();
protected Q_SLOTS:
    void onSpinBoxStartSignals();
    void processExperiment();
    void openDialogLoadFile();
    void openDialogSaveFile();
    void onon_set_start_positionWrap(int ,int );
	void onSetFinishPositionWrap(std::vector< std::pair<int, int> >);
    //void onSetStartDirectionWrap(int);
protected:
	std::unique_ptr<experiment_parameters_dlg_private> pimpl;
protected:
    unsigned int sizeXUpdated,sizeYUpdated;
    int progressBarStepValue;
	//////////////////////////////////////////////////////////////////////////
};
