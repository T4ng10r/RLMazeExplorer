#include "experiment_parameters_dlg.h"
#include "experiment_positions_parameters_dlg.h"
#include "CExperimentMazeParamsDlg.h"
#include "experiment_parameters_experiment_dlg.h"
#include <QLineEdit>
#include <QFileDialog>
#include <QProgressBar>
#include <map>
#include <Maze/maze_settings.h>

const int maxFinishPos(5);

class experiment_parameters_dlg_private
{
public:
	experiment_parameters_dlg_private(experiment_parameters_dlg * pub);
	void setup_ui();
	void setup_progress();
	void retranslate_ui();
	void set_connections();
	void setup_ok_button();
	void setup_load_save_kb_paths();
public:
	experiment_parameters_dlg * public_;
	experiment_positions_parameters_dlg *  	m_ptrWidgetPositionParams;
	CExperimentMazeParamsDlg *			m_ptrWidgetMazeGenerationParam;
	experiment_parameters_experiment_dlg *	m_ptrWidgetExperimentDetails;

	QWidget *			main_widget;
	QVBoxLayout *		main_layout;
	QHBoxLayout *		progres_layout;
	QTabWidget *		tab_dialog;
	QProgressBar *		progress_bar;
	QPushButton *		start_experiment_button;
	QPushButton *		cancel_button;
	QGroupBox	*		groupLoadSaveKB;
	QGridLayout *		gboxLoadSaveKB;

	QLabel		*		labelLoadKBPath;
	QLineEdit	*		lineEditLoadKBPath;
	QPushButton *		buttonBrowseLoadKBPath;

	QLabel		*		labelSaveKBPath;
	QLineEdit	*		lineEditSaveKBPath;
	QPushButton *		buttonBrowseSaveKBPath;
	QFileDialog *		fileDialog;
};

experiment_parameters_dlg_private::experiment_parameters_dlg_private(experiment_parameters_dlg * pub) : public_(pub)
{
	setup_ui();
	retranslate_ui();
}
void experiment_parameters_dlg_private::setup_ui()
{
	public_->setObjectName(QString::fromUtf8("ExperimentParamsDlg"));
	//setMinimumSize(QSize(250, 350));//.expandedTo(minimumSizeHint()));
	//resize(QSize(350, 380));//.expandedTo(minimumSizeHint()));

	main_widget = new QWidget(public_);
	main_widget->setObjectName(QString::fromUtf8("main_widget_dockWidget"));

	main_layout = new QVBoxLayout;
	main_layout->setObjectName(QString::fromUtf8("mainWindowLayout"));
	main_widget->setLayout(main_layout);

	tab_dialog = new QTabWidget;

	m_ptrWidgetMazeGenerationParam = new CExperimentMazeParamsDlg;
	tab_dialog->addTab(m_ptrWidgetMazeGenerationParam, "Maze");

	m_ptrWidgetPositionParams = new experiment_positions_parameters_dlg;
	tab_dialog->addTab(m_ptrWidgetPositionParams, "Positions");
	m_ptrWidgetPositionParams->setEnabled(false);


	m_ptrWidgetExperimentDetails = new experiment_parameters_experiment_dlg;
	tab_dialog->addTab(m_ptrWidgetExperimentDetails, "Details");

	main_layout->addWidget(tab_dialog);

	setup_progress();
	main_layout->addLayout(progres_layout);

	//	setupLoadSaveKBPaths();
	public_->setWidget(main_widget);

	set_connections();
}
void experiment_parameters_dlg_private::setup_progress()
{
	progres_layout = new QHBoxLayout();
	progres_layout->setObjectName(QString::fromUtf8("progresLayout"));
	progres_layout->setSpacing(6);
	progres_layout->setMargin(0);


	progress_bar = new QProgressBar();
	progress_bar->reset();
	progress_bar->setAlignment(Qt::AlignHCenter);
	progress_bar->setMaximum(1);
	progress_bar->setMinimum(0);
	progres_layout->addWidget(progress_bar);

	QSizePolicy sizePolicy(QSizePolicy::Expanding, static_cast<QSizePolicy::Policy>(1));
	sizePolicy.setHorizontalStretch(2);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(progress_bar->sizePolicy().hasHeightForWidth());
	progress_bar->setSizePolicy(sizePolicy);


	start_experiment_button = new QPushButton();
	start_experiment_button->setObjectName(QString::fromUtf8("startExperimentButton"));
	progres_layout->addWidget(start_experiment_button);
	start_experiment_button->setEnabled(false);

	start_experiment_button->setText(QObject::tr("param_eks", "Start", 0));
	//cancelButton->setText(QApplication::translate("param_eks", "Anuluj", 0));
}
void experiment_parameters_dlg_private::setup_ok_button()
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

	startExperimentButton->setText(QApplication::translate("param_eks", "Rozpocznij", 0));
	cancelButton->setText(QApplication::translate("param_eks", "Anuluj", 0));*/
}
void experiment_parameters_dlg_private::setup_load_save_kb_paths()
{
/*	groupLoadSaveKB = new QGroupBox(public_);
	groupLoadSaveKB->setObjectName(QString::fromUtf8("groupLoadSaveKB"));
	groupLoadSaveKB->setTitle("Baza wiedzy");
	main_layout->addWidget(groupLoadSaveKB);

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
void experiment_parameters_dlg_private::set_connections()
{
	bool bResult = false;
	//////////////////////////////////////////////////////////////////////////
	bResult = QObject::connect(m_ptrWidgetMazeGenerationParam, SIGNAL(generate_maze(maze_settings)),
					  m_ptrWidgetPositionParams, SLOT(onMazeGeneration(maze_settings)));
	Q_ASSERT(bResult == true);

	bResult = QObject::connect(m_ptrWidgetMazeGenerationParam, SIGNAL(generate_maze(maze_settings)), public_,
					  SIGNAL(generate_maze(maze_settings)));
	Q_ASSERT(bResult == true);

	bResult = QObject::connect(start_experiment_button, SIGNAL(clicked(bool)), public_, SLOT(processExperiment()));
	Q_ASSERT(bResult == true);
	//////////////////////////////////////////////////////////////////////////
	//send signal about change in start positions
	bResult = QObject::connect(m_ptrWidgetPositionParams, SIGNAL(on_set_start_position(int, int)), public_, SLOT(on_experiment_settings_changed()));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(m_ptrWidgetPositionParams, SIGNAL(setFinishPosition(int, int)), public_, SLOT(on_experiment_settings_changed()));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(m_ptrWidgetPositionParams, SIGNAL(setFinishPositions(std::vector< std::pair<int, int> >)), public_, SLOT(on_experiment_settings_changed()));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(m_ptrWidgetPositionParams, SIGNAL(setStartDirection(int)), public_, SLOT(on_experiment_settings_changed()));
	Q_ASSERT(bResult == true);
	//////////////////////////////////////////////////////////////////////////

	qDebug("Sygnaly polaczone");
}
void experiment_parameters_dlg_private::retranslate_ui()
{
	public_->setWindowTitle("Experiment parameters");
	tab_dialog->setTabText(0, QObject::tr("experiment_parameters_dlg", "Maze", 0));
	tab_dialog->setTabText(1, QObject::tr("experiment_parameters_dlg", "Localizing", 0));
	tab_dialog->setTabText(2, QObject::tr("experiment_parameters_dlg", "Details", 0));
}
//////////////////////////////////////////////////////////////////////////
experiment_parameters_dlg::experiment_parameters_dlg(QWidget *parent) :
#ifdef TREAT_WINDOW_AS_DOCKWIDGET
    QDockWidget(parent)
#else
    QDialog(parent)
#endif
	, pimpl(new experiment_parameters_dlg_private(this))
{
    sizeXUpdated = 10;
    sizeYUpdated = 10;
    //setMinimumSize(rcDockWidgetSize);
}
experiment_parameters_dlg::~experiment_parameters_dlg(){}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void experiment_parameters_dlg::onSetExperimentSettings(CExperimentSettings & cExperimentSettings)
{
    pimpl->m_ptrWidgetPositionParams->setExperimentSettings(cExperimentSettings);
	pimpl->m_ptrWidgetMazeGenerationParam->set_maze_settings(cExperimentSettings.mazeSettings);
}
void experiment_parameters_dlg::processExperiment()
{
    CExperimentSettings cExperimentSettings;

	pimpl->m_ptrWidgetMazeGenerationParam->get_maze_settings(cExperimentSettings.mazeSettings);
	pimpl->m_ptrWidgetPositionParams->getExperimentSettings(cExperimentSettings);
    //m_ptrWidgetExperimentDetails->getExperimentSettings(cExperimentSettings);

	//////////////////////////////////////////////////////////////////////////
	pimpl->progress_bar->setMinimum(1);
	pimpl->progress_bar->setMaximum(cExperimentSettings.repeatingQuantity);
	pimpl->progress_bar->reset();

	cExperimentSettings.sLoadKBPath = pimpl->lineEditLoadKBPath->text();
	cExperimentSettings.sSaveKBPath = pimpl->lineEditSaveKBPath->text();

	//////////////////////////////////////////////////////////////////////////
    Q_EMIT startExperiment(cExperimentSettings);
}
//////////////////////////////////////////////////////////////////////////
void experiment_parameters_dlg::onSpinBoxStartSignals() {}
void experiment_parameters_dlg::onNewStartPosition(int posX,int posY)
{
	pimpl->m_ptrWidgetPositionParams->onNewStartPosition(posX, posY);
}
void experiment_parameters_dlg::onNewFinishPosition(int posX,int posY)
{
	pimpl->m_ptrWidgetPositionParams->onNewFinishPosition(posX, posY);
}
void experiment_parameters_dlg::onAddFinishPosition(int posX,int posY)
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
void experiment_parameters_dlg::on_experiment_settings_changed()
{
	CExperimentSettings expSettings;

	pimpl->m_ptrWidgetMazeGenerationParam->get_maze_settings(expSettings.mazeSettings);
	pimpl->m_ptrWidgetPositionParams->getExperimentSettings(expSettings);

	Q_EMIT experimentSettingsChanged(expSettings);
	pimpl->start_experiment_button->setEnabled(true);
}
void experiment_parameters_dlg::onon_set_start_positionWrap(int iPosX,int iPosY)
{
	Q_EMIT on_set_start_position(iPosX, iPosY);
}
void experiment_parameters_dlg::onSetFinishPositionWrap(std::vector< std::pair<int, int> > vPostionsList)
{
	Q_EMIT setFinishPosition(vPostionsList);
}

void experiment_parameters_dlg::resetExperimentStatus()
{
	pimpl->progress_bar->reset();
}
void experiment_parameters_dlg::nextStepInExperiment()
{
	pimpl->progress_bar->setValue(pimpl->progress_bar->value() + 1);
}
void experiment_parameters_dlg::openDialogLoadFile()
{
    QString s = QFileDialog::getOpenFileName(
                    this,
                    "Choose a file",
                    "",
                    "Date (*.dat);;Any files (*.*)");
	pimpl->lineEditLoadKBPath->setText(s);
}
void experiment_parameters_dlg::openDialogSaveFile()
{
    QString s = QFileDialog::getOpenFileName(
                    this,
                    "Choose a file",
                    "",
                    "Date (*.dat);;Any files (*.*)");
	pimpl->lineEditSaveKBPath->setText(s);
}
