#ifndef CEXPERIMENTPARAMSMAZEDLG_H
#define CEXPERIMENTPARAMSMAZEDLG_H

#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QTableWidget>
#include <QtGui/QTableView>
#include <QtGui/QHeaderView>
#include <QtGui/QStandardItemModel>
#include <QtGui/QApplication>
#include <QtGui/QSpacerItem>
#include <QtGui/QComboBox>
#include <QtGui/QPushButton>
#include <QtGui/QItemDelegate>
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
signals:
	//send signal about change in start positions
    void setStartPosition(int ,int);	//wysyla informacja o ustawieniu nowej pozycji startowej
    void setFinishPosition(int ,int);	//wysyla informacja o ustawieniu nowej pozycji koñcowej
	//wysyla informacja o ustawieniu nowej pozycji koñcowej
	void setFinishPositions(std::vector< std::pair<int,int> >);	
	//send info about change of start direction (on argument perform cast into eRobotDir)
    void setStartDirection(int);	
public slots:
	//sets maximum limit values to start and finish positions
	void onMazeGeneration(CMazeSettings &);
	//user selected new start position on Maze Draw
    void onNewStartPosition(int ,int);
	//user selected first of finish position on Maze Draw
    void onNewFinishPosition(int ,int);
	//user add new finish position on Maze Draw
	void onAddFinishPosition(int ,int);
    //void onMazeSizeChange(int,int);	//przyjmuje informacje o rozmiarze labiryntu

    void onButtonAddFinishPos();
    void onButtonRemFinishPos();
protected slots:
	//starting position has been change
	void onInternalStartPosChange();		
	//entry in finish position has been changed - send entire list of positions to update
	void onInternalFinishPostionChanged(QStandardItem *);
	//user changed starting direction of agent by highlighting entry in comboBox
	void onInternalDirectionChanged(int iIndex);
private:
    void setupUI();
    void retranslateUI();
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
