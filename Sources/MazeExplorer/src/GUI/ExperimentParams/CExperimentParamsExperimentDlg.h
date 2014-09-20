#ifndef CEXPERIMENTPARAMSEXPERIMENTDLG_H
#define CEXPERIMENTPARAMSEXPERIMENTDLG_H
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

class CExperimentParamsExperimentDlg : public QWidget
{
    Q_OBJECT
public:
    CExperimentParamsExperimentDlg(QWidget *parent = 0);
    void getExperimentSettings(CExperimentSettings & cExperimentSettings);
protected:
    void setupUI();
    void retranslateUI();
    void setConnections();
    void setupLearningParamGroup();
    void setupLearningMethod();
    void setupLearningPenaltyValue();
    void setupLearningPriceValue();

    QGridLayout *		mainLayout;
    QGroupBox *		groupLearningParam;
    QWidget *		groupLearningParamWidget;
    QHBoxLayout *		hLearningMethodLayout;
    QLabel *		labelLearningMethod;
    QComboBox *		comboLearningMethod;
    QPushButton *		pushLearningMethod;
    QWidget *		gridLayoutWidget;
    QGridLayout *		gridPenaltyPriceLayout;
    QLabel *		labelPenaltyValue;
    QDoubleSpinBox *	spinPriceValue;
    QDoubleSpinBox *	spinPenaltyValue;
    QLabel *		labelPriceValue;
    QPushButton *		pushPriceValue;
    QPushButton *		pushPenaltyValue;
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    QGroupBox	*	groupLoadSaveKB;
    QGridLayout *		gboxLoadSaveKB;

    QLabel		*	labelLoadKBPath;
    QLineEdit	*	lineEditLoadKBPath;
    QPushButton *		buttonBrowseLoadKBPath;

    QLabel		*	labelSaveKBPath;
    QLineEdit	*	lineEditSaveKBPath;
    QPushButton *		buttonBrowseSaveKBPath;

    //////////////////////////////////////////////////////////////////////////
    QPushButton *	cancelButton;

//	QFileDialog *	fileDialog;
    QTabWidget *	tabDialog;


};

#endif
