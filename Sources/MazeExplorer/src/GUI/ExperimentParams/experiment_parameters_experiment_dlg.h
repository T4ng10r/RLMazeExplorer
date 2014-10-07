#ifndef CEXPERIMENTPARAMSEXPERIMENTDLG_H
#define CEXPERIMENTPARAMSEXPERIMENTDLG_H
#include <memory>
#include <QWidget>
#include <QApplication>

#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QProgressBar>
#include <Maze/maze_settings.h>
#include <Data/Experiment/CExperimentSettings.h>
/**
	@author Tanglor <tanglor@tanglor-desktop>
*/
const QSize rcLearningParams(211, 141);
const QSize rcDockWidgetSize(451, 328);
const int	dockWidgetYPos(25);

class experiment_parameters_experiment_dlg_private;

class experiment_parameters_experiment_dlg : public QWidget
{
    Q_OBJECT
public:
    experiment_parameters_experiment_dlg(QWidget *parent = 0);
    ~experiment_parameters_experiment_dlg();
    void getExperimentSettings(CExperimentSettings & cExperimentSettings);
protected:
    std::unique_ptr<experiment_parameters_experiment_dlg_private> pimpl;
};

#endif
