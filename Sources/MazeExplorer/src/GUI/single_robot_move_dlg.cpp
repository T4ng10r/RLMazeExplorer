#include <GUI/single_robot_move_dlg.h>
#include <Data/CScanResults.h>

const int maxFinishPos(5);

single_robot_move_dlg::single_robot_move_dlg(QWidget *parent) : QDockWidget(parent)
{
	show();
	setup_ui();
	retranslate_ui();
	setAllowedAreas(Qt::RightDockWidgetArea);
}
//////////////////////////////////////////////////////////////////////////
void single_robot_move_dlg::setup_ui()
{
	setObjectName(QString::fromUtf8("SingleRobotMoveDlg"));
	QWidget * ptrWidget = new QWidget();
	setWidget(ptrWidget);
	m_ptrVMainlLayout = new QVBoxLayout(ptrWidget);
	m_ptrVMainlLayout->setObjectName(QString::fromUtf8("VMainLayout"));

	//////////////////////////////////////////////////////////////////////////
	QHBoxLayout * m_ptrHRobotPosLayout = new QHBoxLayout();
	m_ptrHRobotPosLayout->setSpacing(6);
	m_ptrHRobotPosLayout->setObjectName(QString::fromUtf8("RobotPosLayout"));

	m_ptrRobotPosLabel = new QLabel(this);
	m_ptrRobotPosLabel->setObjectName(QString::fromUtf8("RobotPosLabel"));
		QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(m_ptrRobotPosLabel->sizePolicy().hasHeightForWidth());
		m_ptrRobotPosLabel->setSizePolicy(sizePolicy);
	m_ptrRobotPosLabel->setMaximumHeight(25);

	m_ptrHRobotPosLayout->addWidget(m_ptrRobotPosLabel);

	m_ptrRobotPoslineEdit = new QLineEdit(this);
	m_ptrRobotPoslineEdit->setObjectName(QString::fromUtf8("m_ptrRobotPoslineEdit"));
		QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(m_ptrRobotPoslineEdit->sizePolicy().hasHeightForWidth());
		m_ptrRobotPoslineEdit->setSizePolicy(sizePolicy1);
	m_ptrRobotPoslineEdit->setMaximumHeight(25);
	m_ptrRobotPoslineEdit->setReadOnly(true);

	m_ptrHRobotPosLayout->addWidget(m_ptrRobotPoslineEdit);


	m_ptrVMainlLayout->addLayout(m_ptrHRobotPosLayout);
	//////////////////////////////////////////////////////////////////////////
	QHBoxLayout * m_ptrRobotScanWidgetsLayout = new QHBoxLayout();
	m_ptrRobotScanWidgetsLayout->setContentsMargins(10, 10, 10, 10);
	m_ptrRobotScanWidgetsLayout->setObjectName(QString::fromUtf8("RobotScanWidgetsLayout"));
	m_ptrRobotScanWidget = new QWidget(this);
	m_ptrRobotScanWidget->setObjectName(QString::fromUtf8("m_ptrRobotScanWidget"));

	m_ptrRobotScanWidgetsLayout->addWidget(m_ptrRobotScanWidget);

	m_ptrRobotRotScanWidget = new QWidget(this);
	m_ptrRobotRotScanWidget->setObjectName(QString::fromUtf8("scanResults_2"));

	m_ptrRobotScanWidgetsLayout->addWidget(m_ptrRobotRotScanWidget);

	m_ptrVMainlLayout->addLayout(m_ptrRobotScanWidgetsLayout);
	//////////////////////////////////////////////////////////////////////////

	QHBoxLayout * m_ptrDownLayout = new QHBoxLayout();
	m_ptrDownLayout->setObjectName(QString::fromUtf8("horizontalLayout_3"));
	m_ptrDownLayout->setContentsMargins(-1, -1, 10, -1);

	m_ptrTimeOutGroupBox = new QGroupBox(this);
	m_ptrTimeOutGroupBox->setObjectName(QString::fromUtf8("m_ptrTimeOutGroupBox"));
	m_ptrTimeOutGroupBox->setMaximumSize(QSize(16777215, 60));
	m_ptrTimeOutGroupBox->setCheckable(true);
		//////////////////////////////////////////////////////////////////////////
		QHBoxLayout * m_ptrHTimeOutGroupBoxLayout = new QHBoxLayout(m_ptrTimeOutGroupBox);
		m_ptrHTimeOutGroupBoxLayout->setObjectName(QString::fromUtf8("m_ptrHTimeOutGroupBoxLayout"));
		m_ptrTimeOutLabel = new QLabel(m_ptrTimeOutGroupBox);
		m_ptrTimeOutLabel->setObjectName(QString::fromUtf8("m_ptrTimeOutLabel"));
		sizePolicy.setHeightForWidth(m_ptrTimeOutLabel->sizePolicy().hasHeightForWidth());
		m_ptrTimeOutLabel->setSizePolicy(sizePolicy);
		m_ptrTimeOutLabel->setMinimumSize(QSize(0, 20));
		m_ptrTimeOutLabel->setMaximumSize(QSize(16777215, 25));

		m_ptrHTimeOutGroupBoxLayout->addWidget(m_ptrTimeOutLabel);

		m_ptrTimeOutValueSpinBox = new QSpinBox(m_ptrTimeOutGroupBox);
		m_ptrTimeOutValueSpinBox->setObjectName(QString::fromUtf8("m_ptrTimeOutValueSpinBox"));
		QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
		sizePolicy2.setHorizontalStretch(0);
		sizePolicy2.setVerticalStretch(0);
		sizePolicy2.setHeightForWidth(m_ptrTimeOutValueSpinBox->sizePolicy().hasHeightForWidth());
		m_ptrTimeOutValueSpinBox->setSizePolicy(sizePolicy2);
		m_ptrTimeOutValueSpinBox->setMinimumSize(QSize(0, 20));
		m_ptrTimeOutValueSpinBox->setMaximumSize(QSize(16777215, 25));

		m_ptrHTimeOutGroupBoxLayout->addWidget(m_ptrTimeOutValueSpinBox);


		m_ptrDownLayout->addWidget(m_ptrTimeOutGroupBox);
		//////////////////////////////////////////////////////////////////////////

	horizontalSpacer = new QSpacerItem(40, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

	m_ptrDownLayout->addItem(horizontalSpacer);

	m_ptrNextMoveButton = new QPushButton(this);
	m_ptrNextMoveButton->setObjectName(QString::fromUtf8("NextMoveButton"));
	sizePolicy.setHeightForWidth(m_ptrNextMoveButton->sizePolicy().hasHeightForWidth());
	m_ptrNextMoveButton->setSizePolicy(sizePolicy);
	m_ptrNextMoveButton->setMinimumSize(QSize(0, 20));
	m_ptrNextMoveButton->setMaximumSize(QSize(50, 25));

	m_ptrDownLayout->addWidget(m_ptrNextMoveButton);


	m_ptrVMainlLayout->addLayout(m_ptrDownLayout);

	retranslate_ui();
	QMetaObject::connectSlotsByName(this);
}
void single_robot_move_dlg::retranslate_ui()
{
	setWindowTitle(QApplication::translate("Form", "Robot move position", 0));
	m_ptrRobotPosLabel->setText(QApplication::translate("Form", "Robot position", 0));
	m_ptrTimeOutGroupBox->setTitle(QApplication::translate("Form", "GroupBox", 0));
	m_ptrTimeOutLabel->setText(QApplication::translate("Form", "TimOut between single moves", 0));
	m_ptrNextMoveButton->setText(QApplication::translate("Form", "Next", 0));
}
//////////////////////////////////////////////////////////////////////////
void single_robot_move_dlg::on_NextMoveButton_clicked(bool checked)
{
    /*	blockSignals(true);

    	int rowCount = modelFinishPos->rowCount();
    	if (rowCount<maxFinishPos)
    	{

    		modelFinishPos->insertRow(rowCount);

    		QModelIndex index = modelFinishPos->index(rowCount, 0, QModelIndex());
    		modelFinishPos->setData(index, QVariant(posX));

    		index = modelFinishPos->index(rowCount, 1, QModelIndex());
    		modelFinishPos->setData(index, QVariant(posY));
    	}
    	blockSignals(false);*/

}
void single_robot_move_dlg::onRobotBeforeMove(scan_results_handle scanResult)
{
	if (!scanResult)	return;
	QString strVal = QString::number(scanResult->robotPos.pos_x)+","+QString::number(scanResult->robotPos.pos_y);
	m_ptrRobotPoslineEdit->setText(strVal);

	//CExperimentSettings expSettings;

	//m_ptrWidgetMazeGenerationParam->getMazeSettings(expSettings.mazeSettings);
	//m_ptrWidgetPositionParams->getExperimentSettings(expSettings);

	//emit experimentSettingsChanged(expSettings);
	//startExperimentButton->setEnabled(true);
}
