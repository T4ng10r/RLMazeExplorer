#include "CExperimentParamsDlg.h"
#include "CExperimentPositionsParamsDlg.h"
#include "CExperimentMazeParamsDlg.h"
#include "CExperimentParamsExperimentDlg.h"

const int maxFinishPos(5);

CExperimentParamsDlg::CExperimentParamsDlg(QWidget *parent) :
#ifdef TREAT_WINDOW_AS_DOCKWIDGET
    QDockWidget(parent)
#else
    QDialog(parent)
#endif
{
    sizeXUpdated = 10;
    sizeYUpdated = 10;
    //setMinimumSize(rcDockWidgetSize);
    setupUI();
	retranslateUI();
}
//////////////////////////////////////////////////////////////////////////
void CExperimentParamsDlg::setupUI()
{
    setObjectName(QString::fromUtf8("ExperimentParamsDlg"));
    //setMinimumSize(QSize(250, 350));//.expandedTo(minimumSizeHint()));
    //resize(QSize(350, 380));//.expandedTo(minimumSizeHint()));

    m_ptrMainWidget = new QWidget(this);
    m_ptrMainWidget->setObjectName(QString::fromUtf8("main_widget_dockWidget"));

    m_ptrMainLayout = new QVBoxLayout ;
    m_ptrMainLayout->setObjectName(QString::fromUtf8("mainWindowLayout"));
    m_ptrMainWidget->setLayout(m_ptrMainLayout);

    m_ptrTabDialog = new QTabWidget;

	m_ptrWidgetMazeGenerationParam = new CExperimentMazeParamsDlg;
	m_ptrTabDialog->addTab(m_ptrWidgetMazeGenerationParam,"Labirynt");

    m_ptrWidgetPositionParams = new CExperimentPositionsParamsDlg;
    m_ptrTabDialog->addTab(m_ptrWidgetPositionParams,"Pozycjonowanie");
	m_ptrWidgetPositionParams->setEnabled(false);


    m_ptrWidgetExperimentDetails = new CExperimentParamsExperimentDlg;
    m_ptrTabDialog->addTab(m_ptrWidgetExperimentDetails,"Szczegó³y");

    m_ptrMainLayout->addWidget(m_ptrTabDialog);

    setupProgress();
    m_ptrMainLayout->addLayout(progresLayout);

//	setupLoadSaveKBPaths();
    setWidget(m_ptrMainWidget);

    setConnections();
}
void CExperimentParamsDlg::setupProgress()
{
    progresLayout = new QHBoxLayout();
    progresLayout->setObjectName(QString::fromUtf8("progresLayout"));
    progresLayout->setSpacing(6);
    progresLayout->setMargin(0);


    progressBar = new QProgressBar();
    progressBar->reset();
    progressBar->setAlignment(Qt::AlignHCenter);
    progressBar->setMaximum(1);
    progressBar->setMinimum(0);
    progresLayout->addWidget(progressBar);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, static_cast<QSizePolicy::Policy>(1));
    sizePolicy.setHorizontalStretch(2);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
    progressBar->setSizePolicy(sizePolicy);


    startExperimentButton = new QPushButton();
    startExperimentButton->setObjectName(QString::fromUtf8("startExperimentButton"));
    progresLayout->addWidget(startExperimentButton);
	startExperimentButton->setEnabled(false);

    startExperimentButton->setText(QApplication::translate("param_eks", "Rozpocznij", 0, QApplication::UnicodeUTF8));
//	cancelButton->setText(QApplication::translate("param_eks", "Anuluj", 0, QApplication::UnicodeUTF8));
}
void CExperimentParamsDlg::setupOkButton()
{
    /*
    	layoutWidget = new QWidget(dockWindowWidget);
    	layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    	mainWindowLayout->addWidget(layoutWidget,2,0,1,3);

    	progresLayout = new QHBoxLayout(layoutWidget);
    	progresLayout->setObjectName(QString::fromUtf8("progresLayout"));
    	progresLayout->setSpacing(6);
    	progresLayout->setMargin(0);

    	progressBar = new QProgressBar(layoutWidget);
    	progressBar->reset();
    	progressBar->setAlignment(Qt::AlignHCenter);
    	progressBar->setMaximum(1);
    	progressBar->setMinimum(0);
    	progresLayout->addWidget(progressBar);

    	QSizePolicy sizePolicy(QSizePolicy::Expanding, static_cast<QSizePolicy::Policy>(1));
    	sizePolicy.setHorizontalStretch(2);
    	sizePolicy.setVerticalStretch(0);
    	sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
    	progressBar->setSizePolicy(sizePolicy);


    	startExperimentButton = new QPushButton(layoutWidget);
    	startExperimentButton->setObjectName(QString::fromUtf8("startExperimentButton"));
    	progresLayout->addWidget(startExperimentButton);
    	cancelButton = new QPushButton(layoutWidget);
    	cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
    	progresLayout->addWidget(cancelButton);

    	startExperimentButton->setText(QApplication::translate("param_eks", "Rozpocznij", 0, QApplication::UnicodeUTF8));
    	cancelButton->setText(QApplication::translate("param_eks", "Anuluj", 0, QApplication::UnicodeUTF8));*/
}
void CExperimentParamsDlg::setupLoadSaveKBPaths()
{
    /*	groupLoadSaveKB = new QGroupBox(dockWindowWidget);
    	groupLoadSaveKB->setObjectName(QString::fromUtf8("groupLoadSaveKB"));
    	groupLoadSaveKB->setTitle("Baza wiedzy");
    	mainWindowLayout->addWidget(groupLoadSaveKB,1,0,1,3);

    	QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, static_cast<QSizePolicy::Policy>(5));
    	sizePolicy.setHorizontalStretch(0);
    	sizePolicy.setVerticalStretch(2);
    	sizePolicy.setHeightForWidth(groupLoadSaveKB->sizePolicy().hasHeightForWidth());
    	groupLoadSaveKB->setSizePolicy(sizePolicy);

    	delete groupLoadSaveKB->layout();
    	gboxLoadSaveKB = new QGridLayout;
    	gboxLoadSaveKB->setObjectName(QString::fromUtf8("gboxMazeStochasticLayout"));
    	gboxLoadSaveKB->setSpacing(6);
    	gboxLoadSaveKB->setMargin(2);
    	groupLoadSaveKB->setLayout(gboxLoadSaveKB);

    	//////////////////////////////////////////////////////////////////////////
    	labelLoadKBPath = new QLabel(groupLoadSaveKB);
    	labelLoadKBPath->setObjectName(QString::fromUtf8("labelLoadKBPath"));
    	labelLoadKBPath->setAlignment(Qt::AlignCenter);
    	labelLoadKBPath->setText(QApplication::translate("Dialog", "Odczytaj", 0, QApplication::DefaultCodec));
    	gboxLoadSaveKB->addWidget(labelLoadKBPath,0,0,1,1);


    	lineEditLoadKBPath = new QLineEdit(groupLoadSaveKB);
    	lineEditLoadKBPath->setObjectName(QString::fromUtf8("lineEditLoadKBPath"));
    	gboxLoadSaveKB->addWidget(lineEditLoadKBPath,0,1,1,1);
    		QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, static_cast<QSizePolicy::Policy>(5));
    		sizePolicy1.setHorizontalStretch(2);
    		sizePolicy1.setVerticalStretch(0);
    		sizePolicy1.setHeightForWidth(lineEditLoadKBPath->sizePolicy().hasHeightForWidth());
    		lineEditLoadKBPath->setSizePolicy(sizePolicy1);

    	buttonBrowseLoadKBPath=new QPushButton(groupLoadSaveKB);
    	buttonBrowseLoadKBPath->setObjectName(QString::fromUtf8("buttonBrowseLoadKBPath"));
    	buttonBrowseLoadKBPath->setText("Browse");
    	gboxLoadSaveKB->addWidget(buttonBrowseLoadKBPath,0,2,1,1);
    	//////////////////////////////////////////////////////////////////////////
    	labelSaveKBPath = new QLabel(groupLoadSaveKB);
    	labelSaveKBPath->setObjectName(QString::fromUtf8("labelSaveKBPath"));
    	labelSaveKBPath->setAlignment(Qt::AlignCenter);
    	labelSaveKBPath->setText(QApplication::translate("Dialog", "Zapisz", 0, QApplication::DefaultCodec));
    	gboxLoadSaveKB->addWidget(labelSaveKBPath,1,0,1,1);


    	lineEditSaveKBPath = new QLineEdit(groupLoadSaveKB);
    	lineEditSaveKBPath->setObjectName(QString::fromUtf8("lineEditSaveKBPath"));
    	gboxLoadSaveKB->addWidget(lineEditSaveKBPath,1,1,1,1);
    		QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, static_cast<QSizePolicy::Policy>(5));
    		sizePolicy2.setHorizontalStretch(2);
    		sizePolicy2.setVerticalStretch(0);
    		sizePolicy2.setHeightForWidth(lineEditSaveKBPath->sizePolicy().hasHeightForWidth());
    		lineEditSaveKBPath->setSizePolicy(sizePolicy2);

    	buttonBrowseSaveKBPath=new QPushButton(groupLoadSaveKB);
    	buttonBrowseSaveKBPath->setObjectName(QString::fromUtf8("buttonBrowseSaveKBPath"));
    	buttonBrowseSaveKBPath->setText("Browse");
    	gboxLoadSaveKB->addWidget(buttonBrowseSaveKBPath,1,2,1,1);*/
    //////////////////////////////////////////////////////////////////////////
}
void CExperimentParamsDlg::retranslateUI()
{
	setWindowTitle("Parametry eksperymentu");
	m_ptrTabDialog->setTabText(0,QApplication::translate("Form", "Labirynt", 0, QApplication::CodecForTr));
	m_ptrTabDialog->setTabText(1,QApplication::translate("Form", "Pozycjonowanie", 0, QApplication::CodecForTr));
	m_ptrTabDialog->setTabText(2,QApplication::translate("Form", "Szczegó³y", 0, QApplication::CodecForTr));
}
void CExperimentParamsDlg::setConnections()
{
	bool bResult=false;
	//////////////////////////////////////////////////////////////////////////
	bResult=connect(m_ptrWidgetMazeGenerationParam,SIGNAL(generateMaze(CMazeSettings &)),
		m_ptrWidgetPositionParams,SLOT(onMazeGeneration(CMazeSettings &)));
	Q_ASSERT(bResult==true);

	bResult=connect(m_ptrWidgetMazeGenerationParam,SIGNAL(generateMaze(CMazeSettings &)),
		SIGNAL(generateMaze(CMazeSettings &)));
	Q_ASSERT(bResult==true);
	
	bResult=connect(startExperimentButton,SIGNAL(clicked( bool )),SLOT(processExperiment( )));
	Q_ASSERT(bResult==true);
	//////////////////////////////////////////////////////////////////////////
	//send signal about change in start positions
	bResult=connect(m_ptrWidgetPositionParams,SIGNAL(setStartPosition( int, int )),SLOT(onExperimentSettingsChanged()));
	Q_ASSERT(bResult==true);
	bResult=connect(m_ptrWidgetPositionParams,SIGNAL(setFinishPosition( int, int )),SLOT(onExperimentSettingsChanged()));
	Q_ASSERT(bResult==true);
	bResult=connect(m_ptrWidgetPositionParams,SIGNAL(setFinishPositions( std::vector< std::pair<int,int> > )),SLOT(onExperimentSettingsChanged()));
	Q_ASSERT(bResult==true);
	bResult=connect(m_ptrWidgetPositionParams,SIGNAL(setStartDirection( int )),SLOT(onExperimentSettingsChanged()));
	Q_ASSERT(bResult==true);
	//////////////////////////////////////////////////////////////////////////

	qDebug("Sygnaly polaczone");
}
//////////////////////////////////////////////////////////////////////////
void CExperimentParamsDlg::onSetExperimentSettings(CExperimentSettings & cExperimentSettings)
{
    m_ptrWidgetPositionParams->setExperimentSettings(cExperimentSettings);
	m_ptrWidgetMazeGenerationParam->setMazeSettings(cExperimentSettings.mazeSettings);
}
void CExperimentParamsDlg::processExperiment()
{
    CExperimentSettings cExperimentSettings;

    m_ptrWidgetMazeGenerationParam->getMazeSettings(cExperimentSettings.mazeSettings);
    m_ptrWidgetPositionParams->getExperimentSettings(cExperimentSettings);
    //m_ptrWidgetExperimentDetails->getExperimentSettings(cExperimentSettings);

	//////////////////////////////////////////////////////////////////////////
    progressBar->setMinimum(1);
    progressBar->setMaximum(cExperimentSettings.repeatingQuantity);
    progressBar->reset();

//	cExperimentSettings.sLoadKBPath = lineEditLoadKBPath->text();
//	cExperimentSettings.sSaveKBPath = lineEditSaveKBPath->text();

	//////////////////////////////////////////////////////////////////////////
    emit startExperiment(cExperimentSettings);
}
//////////////////////////////////////////////////////////////////////////
void CExperimentParamsDlg::onSpinBoxStartSignals() {}
void CExperimentParamsDlg::onNewStartPosition(int posX,int posY)
{
    m_ptrWidgetPositionParams->onNewStartPosition(posX, posY);
}
void CExperimentParamsDlg::onNewFinishPosition(int posX,int posY)
{
    m_ptrWidgetPositionParams->onNewFinishPosition(posX, posY);
}
void CExperimentParamsDlg::onAddFinishPosition(int posX,int posY)
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
void CExperimentParamsDlg::onExperimentSettingsChanged()
{
	CExperimentSettings expSettings;

	m_ptrWidgetMazeGenerationParam->getMazeSettings(expSettings.mazeSettings);
	m_ptrWidgetPositionParams->getExperimentSettings(expSettings);

	emit experimentSettingsChanged(expSettings);
	startExperimentButton->setEnabled(true);
}
void CExperimentParamsDlg::onSetStartPositionWrap(int iPosX,int iPosY)
{
	emit setStartPosition(iPosX,iPosY);
}
void CExperimentParamsDlg::onSetFinishPositionWrap(vector< pair<int,int> > vPostionsList)
{
	emit setFinishPosition(vPostionsList);
}

void CExperimentParamsDlg::resetExperimentStatus()
{
    progressBar->reset();
}
void CExperimentParamsDlg::nextStepInExperiment()
{
    progressBar->setValue(progressBar->value()+1);
}
void CExperimentParamsDlg::openDialogLoadFile()
{
    QString s = QFileDialog::getOpenFileName(
                    this,
                    "Choose a file",
                    "",
                    "Date (*.dat);;Any files (*.*)");
    lineEditLoadKBPath->setText(s);
}
void CExperimentParamsDlg::openDialogSaveFile()
{
    QString s = QFileDialog::getOpenFileName(
                    this,
                    "Choose a file",
                    "",
                    "Date (*.dat);;Any files (*.*)");
    lineEditSaveKBPath->setText(s);
}
