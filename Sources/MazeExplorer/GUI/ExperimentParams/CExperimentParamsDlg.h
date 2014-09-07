#pragma once
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QDialog>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QProgressBar>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QHeaderView>
#include <QTabWidget>
#include <vector>
#include <map>
#include <Maze/CMazeSettings.h>
#include <Data/Experiment/CExperimentSettings.h>
//#include "CSpinBoxDelegate.h"
//#include "CExperimentParamsExperimentDlg.h"

class CExperimentPositionsParamsDlg;
class CExperimentMazeParamsDlg;
class CExperimentParamsExperimentDlg;

#define TREAT_WINDOW_AS_DOCKWIDGET
class CMaze;
using namespace std;
#ifdef TREAT_WINDOW_AS_DOCKWIDGET
class CExperimentParamsDlg : public QDockWidget
//#else
//class CExperimentParamsDlg : public QDialog
#endif
{
    Q_OBJECT
public:
    CExperimentParamsDlg(QWidget *parent=NULL);
//	~CExperimentParamsDlg(void);
signals:
    void setStartPosition(int ,int);
    void setFinishPosition(int ,int);
    void setFinishPosition(vector< pair<int,int> >);
	void generateMaze(CMazeSettings &);
    void experimentSettingsChanged(const CExperimentSettings &);
    //xMazeSettings
    void startExperiment(CExperimentSettings & cExperimentSettings);
    void getMazeData(CMaze & cMaze);
    void setStartDirection(int);
public slots:
	void onSetExperimentSettings(CExperimentSettings & cExperimentSettings);
    void onNewStartPosition(int ,int);
    void onNewFinishPosition(int ,int);
    void onAddFinishPosition(int ,int);
    void resetExperimentStatus();
    void nextStepInExperiment();
	void onExperimentSettingsChanged();
protected slots:
    void onSpinBoxStartSignals();
    void processExperiment();
    void openDialogLoadFile();
    void openDialogSaveFile();
    void onSetStartPositionWrap(int ,int );
    void onSetFinishPositionWrap(vector< pair<int,int> >);
    //void onSetStartDirectionWrap(int);
protected:
    void setConnections();
    //metody u�ywane przy tworzeniu GUI
    void setupUI();
    void setupProgress();
    void setupLoadSaveKBPaths();
    void setupOkButton();
	void retranslateUI();

protected:
    unsigned int sizeXUpdated,sizeYUpdated;
    int progressBarStepValue;
	CExperimentPositionsParamsDlg *  	m_ptrWidgetPositionParams;
    CExperimentMazeParamsDlg *			m_ptrWidgetMazeGenerationParam;
    CExperimentParamsExperimentDlg *	m_ptrWidgetExperimentDetails;
	//////////////////////////////////////////////////////////////////////////
	QWidget *			m_ptrMainWidget;
	QVBoxLayout *		m_ptrMainLayout;
	QTabWidget *		m_ptrTabDialog;

	//////////////////////////////////////////////////////////////////////////
	QGroupBox	*		groupLoadSaveKB;
	QGridLayout *		gboxLoadSaveKB;

	QLabel		*		labelLoadKBPath;
	QLineEdit	*		lineEditLoadKBPath;
	QPushButton *		buttonBrowseLoadKBPath;

	QLabel		*		labelSaveKBPath;
	QLineEdit	*		lineEditSaveKBPath;
	QPushButton *		buttonBrowseSaveKBPath;

	//////////////////////////////////////////////////////////////////////////
	QProgressBar *		progressBar;
	QPushButton *		startExperimentButton;
	QPushButton *		cancelButton;

	QFileDialog *		fileDialog;

	QHBoxLayout *		progresLayout;

};
