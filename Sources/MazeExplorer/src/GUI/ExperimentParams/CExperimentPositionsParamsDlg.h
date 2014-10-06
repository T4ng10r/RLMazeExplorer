#ifndef CEXPERIMENTPARAMSMAZEDLG_H
#define CEXPERIMENTPARAMSMAZEDLG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QApplication>
#include <QSpacerItem>
#include <QComboBox>
#include <QPushButton>
#include <QItemDelegate>
#include <vector>
#include <map>
//#include "CSpinBoxDelegate.h"
#include <Data/Experiment/CExperimentSettings.h>

const QSize rcExperimentParams(171, 211);
using namespace std;

class CExperimentPositionsParamsDlg : public QWidget
{
    Q_OBJECT
public:
    CExperimentPositionsParamsDlg(QWidget *parent = 0);
    ~CExperimentPositionsParamsDlg();
    void setExperimentSettings(CExperimentSettings & cExperimentSettings);
	void getExperimentSettings(CExperimentSettings & cExperimentSettings);
Q_SIGNALS:
	//send signal about change in start positions
    void on_set_start_position(int ,int);	//wysyla informacja o ustawieniu nowej pozycji startowej
    void setFinishPosition(int ,int);	//wysyla informacja o ustawieniu nowej pozycji koñcowej
	//wysyla informacja o ustawieniu nowej pozycji koñcowej
	void setFinishPositions(std::vector< std::pair<int,int> >);	
	//send info about change of start direction (on argument perform cast into eRobotDir)
    void setStartDirection(int);	
public Q_SLOTS:
	//sets maximum limit values to start and finish positions
	void onMazeGeneration(maze_settings);
	//user selected new start position on Maze Draw
    void onNewStartPosition(int ,int);
	//user selected first of finish position on Maze Draw
    void onNewFinishPosition(int ,int);
	//user add new finish position on Maze Draw
	void onAddFinishPosition(int ,int);
    //void onMazeSizeChange(int,int);	//przyjmuje informacje o rozmiarze labiryntu

    void onButtonAddFinishPos();
    void onButtonRemFinishPos();
protected Q_SLOTS:
	//starting position has been change
	void onInternalStartPosChange();		
	//entry in finish position has been changed - send entire list of positions to update
	void onInternalFinishPostionChanged(QStandardItem *);
	//user changed starting direction of agent by highlighting entry in comboBox
	void onInternalDirectionChanged(int iIndex);
private:
    void setup_ui();
    void retranslate_ui();
    void setupRepeatQuant();
    void setupStartingPos();
    void setupFinishPos();
    void setConnections();


	int			m_iDirSelected;

//	QGroupBox*	groupExperimentParam;
    QVBoxLayout *	m_ptrMainLayout;


    QVBoxLayout *	vboxExperimentParamLayout;
    QHBoxLayout *	hboxLayout;
    QLabel *		labelRepeatQuantity;
    QSpinBox *		spinRepeatQuantity;
    QGroupBox *		groupStartingPos;
    QWidget *		groupStartingPosWidget;
    QHBoxLayout *	hStartPosLayout;
    QGridLayout *	gStartPosLayout;

    QLabel *		labelStartX;
    QSpinBox *		spinStartX;
    QLabel *		labelStartY;
    QSpinBox *		spinStartY;
    QLabel *		labelStartDir;
    QComboBox *		comboStartDir;

    QGroupBox *		groupFinishPos;
    QVBoxLayout *	hFinishPosLayout;
    QTableWidget *	tableFinishPos;
    QTableView *	tableViewFinishPos;
    QStandardItemModel * modelFinishPos;
    QWidget *		layoutWidget;
    QHBoxLayout *	hButtonsLayout;
    QSpacerItem *	spacerItem;


	QItemDelegate * ptrDelegate;
	QItemEditorFactory * ptrFactory;

    //CSpinBoxDelegate delegate;

    //
    QHBoxLayout *	hAddRemoveButtonsLayout;

    QPushButton *    addFinishPos;
    QPushButton *    removeFinishPos;

//	CExperimentParamsMazeDlg * 	widgetExperimentParam;

};

#endif
