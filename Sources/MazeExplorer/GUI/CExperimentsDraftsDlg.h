#pragma once
#include <QApplication>
#include <QDockWidget>
#include <QDialog>
#include <QToolBox>
#include <QToolButton>
#include <QGridLayout>
#include <QTreeView>
#include <QTableView>
#include <QStandardItemModel>
#include <QStringList>
#include <QtDebug>
#include <QLineEdit>
#include <QLabel>
#include <QTreeWidget>
#include <QTabWidget>
#include "CExperimentResultDraft.h"
#include <Data/CMazeKnowlegdeBase.h>
#include  "CExperimentsKBGraph.h"

#define EXPLORATION_TITLE "Eksploracja nr"
#define PATH_TEXT "Sciezka"
#define CROSS_TEXT "Skrzyzowania"
class CExperiment;

/*
class CExperimentsDraftsDlg : public QWidget
{
    Q_OBJECT
public:
    CExperimentsDraftsDlg(void);
    ~CExperimentsDraftsDlg(void);

    QGridLayout *		gridWindowLayout;

    QToolBox	*	toolBox;
    QWidget		*	widgetPage1;
    QTreeWidget	*	treeExplorationResults;

    QToolButton	*	button;

    QGridLayout *	gridStatLayout;
    QLabel		*	labelFails;
    QLineEdit	*	lineEditFails;
    QLabel		*	labelSucces;
    QLineEdit	*	lineEditSucces;
    QTreeModel	*	treeModel;
    QTabWidget  *   tabDialog;



    //CExperimentsKBGraph		*	widgetKBDraw;
    QScrollArea             *   widgetScrollKBDraw;
    CExperimentResultDraft	*	widgetResultDraft;
    QStandardItemModel		*	ptModel;
signals:
    void emitDataForDraft(QVector<float> &dataForDraft);
    void emitShowRobotRoute(CMazeExplorationResult &dataForDraft);
    void emitLocationSelected(int , int );
    void emitLocationNrSelected(int );

public slots:
    void setKnowlegdeBase(CMazeKnowlegdeBase * pKB);
    void setLocationSelected(int , int );

protected slots:
    void slotTreeItemClicked(QTreeWidgetItem *, int);
    void slotTreeItemChanged(QTreeWidgetItem *, QTreeWidgetItem *);
protected:
    QVector<float>	dataForDraft;
    CMazeKnowlegdeBase	*	pKB;
    CExperiment		*	pExperiment;
    void showKBData(int expNr,int posX, int posY);
    void prepareExplorationRouteToSend(int expNr);
    void connecting();
    void calculateDraftValues(CExperiment &exp);
    void fillTableWithExperimentData(CExperiment &exp);
    void fillItemExplorationData(QTreeWidgetItem * parentItem,CMazeExplorationResult &expResult);
    void fillItemExplorationPath(QTreeWidgetItem * parentItemPath,QTreeWidgetItem * parentItemCrossroadPath,CMazeExplorationResult &expResult);
    void setupUI();
    void setupUIToolBoxPages();
    void setupUIFillKnowlegdeBaseData();
};
*/