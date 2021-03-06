#ifndef _SINGLE_ROBOT_MOVE_DLG_INCLUDE_
#define _SINGLE_ROBOT_MOVE_DLG_INCLUDE_

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>
#include <QDockWidget>
#include <Data/CScanResults.h>

class single_robot_move_dlg : public QDockWidget
{
    Q_OBJECT
public:
    single_robot_move_dlg(QWidget *parent=NULL);
//	~CSingleRobotMoveDlg(void);
Q_SIGNALS:
	//signal that next robot move can be performed
    void next_robot_move();
public Q_SLOTS:
	//robot is ready to perform next move - it show what he sees
	void onRobotBeforeMove(scan_results_handle scanResult);
	void on_NextMoveButton_clicked(bool checked);
protected:
    void setup_ui();
	void retranslate_ui();
protected:
	QVBoxLayout *		m_ptrVMainlLayout;
	QLabel *			m_ptrRobotPosLabel;
	QLineEdit *			m_ptrRobotPoslineEdit;
	QHBoxLayout *		horizontalLayout;
	//widget with unrotated scan result, as it's delivered from maze
	QWidget *			m_ptrRobotScanWidget;
	//widget with rotated according to his POV scan result
	QWidget *			m_ptrRobotRotScanWidget;
	QHBoxLayout *		horizontalLayout_3;
	QGroupBox *			m_ptrTimeOutGroupBox;
	QHBoxLayout *		horizontalLayout_4;
	QLabel *			m_ptrTimeOutLabel;
	QSpinBox *			m_ptrTimeOutValueSpinBox;
	QSpacerItem *		horizontalSpacer;
	QPushButton *		m_ptrNextMoveButton;


};
#endif  /*_SINGLE_ROBOT_MOVE_DLG_INCLUDE_*/
