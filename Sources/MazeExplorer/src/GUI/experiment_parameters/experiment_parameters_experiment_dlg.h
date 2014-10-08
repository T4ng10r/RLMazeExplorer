#pragma once

#include <memory>
#include <QWidget>
#include <Data/experiment/CExperimentSettings.h>

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
