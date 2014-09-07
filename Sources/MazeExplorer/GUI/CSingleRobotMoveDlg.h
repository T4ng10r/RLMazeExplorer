#ifndef _SINGLE_ROBOT_MOVE_DLG_INCLUDE_
#define _SINGLE_ROBOT_MOVE_DLG_INCLUDE_

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QDockWidget>

class CScanResults;

class CSingleRobotMoveDlg : public QDockWidget
{
    Q_OBJECT
public:
    CSingleRobotMoveDlg(QWidget *parent=NULL);
//	~CSingleRobotMoveDlg(void);
signals:
	//signal that next robot move can be performed
    void nextRobotMove();
public slots:
	//robot is ready to perform next move - it show what he sees
	void onRobotBeforeMove(CScanResults *scanResult);
	void on_NextMoveButton_clicked(bool checked);
protected:
    void setupUI();
	void retranslateUI();
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
