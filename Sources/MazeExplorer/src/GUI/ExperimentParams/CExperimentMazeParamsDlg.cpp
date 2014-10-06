#include <QApplication>
#include "CExperimentMazeParamsDlg.h"

CExperimentMazeParamsDlg::CExperimentMazeParamsDlg(QWidget *parent) : QWidget(parent)
{
    setup_ui();
    retranslate_ui();
    setConnections();
}
void CExperimentMazeParamsDlg::setup_ui()
{
    mainLayout = new QGridLayout;
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    mainLayout->setSpacing(6);
    mainLayout->setMargin(4);
    delete layout();
    setLayout(mainLayout);

    //////////////////////////////////////////////////////////////////////////
    labelSizeX = new QLabel(this);
    labelSizeX->setObjectName(QString::fromUtf8("labelSizeX"));
    labelSizeX->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(labelSizeX,0,0,1,1);

    spinSizeX = new QSpinBox(this);
    spinSizeX->setObjectName(QString::fromUtf8("spinSizeX"));
    spinSizeX->setMaximum(50);
    spinSizeX->setMinimum(5);
    spinSizeX->setValue(10);
    mainLayout->addWidget(spinSizeX,0,1,1,1);
    //////////////////////////////////////////////////////////////////////////
    labelSizeY = new QLabel(this);
    labelSizeY->setObjectName(QString::fromUtf8("labelSizeY"));
    labelSizeY->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(labelSizeY,1,0,1,1);

    spinSizeY = new QSpinBox(this);
    spinSizeY->setObjectName(QString::fromUtf8("spinSizeY"));
    spinSizeY->setMaximum(50);
    spinSizeY->setMinimum(5);
    spinSizeY->setValue(10);
    mainLayout->addWidget(spinSizeY,1,1,1,1);
    //////////////////////////////////////////////////////////////////////////
    labelMazeGenMethod = new QLabel(this);
    labelMazeGenMethod->setObjectName(QString::fromUtf8("label"));
    labelMazeGenMethod->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(labelMazeGenMethod,2,0,1,1);

    comboGenerationMethod = new QComboBox(this);
    comboGenerationMethod->setObjectName(QString::fromUtf8("comboGenerationMethod"));
    mainLayout->addWidget(comboGenerationMethod,2,1,1,1);

    //setupStochasticMazeChanges();


//	button_generate_maze = new QPushButton;
    button_generate_maze=new QPushButton(this);
    button_generate_maze->setObjectName(QString::fromUtf8("buttonBrowseLoadKBPath"));
    mainLayout->addWidget(button_generate_maze,5,0,1,1);

//	QCheckBox	*	checkBoxMazeIsPerfect;
    checkBoxMazeIsPerfect = new QCheckBox(this);
    checkBoxMazeIsPerfect->setChecked(true);
    mainLayout->addWidget(checkBoxMazeIsPerfect,3,0,1,2);

    setupStochasticMazeChanges();
}
void CExperimentMazeParamsDlg::setupStochasticMazeChanges()
{
    groupStochasticMazeChanges = new QGroupBox(this);
    groupStochasticMazeChanges->setObjectName(QString::fromUtf8("groupStochasticMazeChanges"));
    groupStochasticMazeChanges->setCheckable(true);
    groupStochasticMazeChanges->setChecked(false);
    mainLayout->addWidget(groupStochasticMazeChanges,4,0,1,2);

    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, static_cast<QSizePolicy::Policy>(5));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(2);
    sizePolicy.setHeightForWidth(groupStochasticMazeChanges->sizePolicy().hasHeightForWidth());
    groupStochasticMazeChanges->setSizePolicy(sizePolicy);

    delete groupStochasticMazeChanges->layout();
    gboxMazeStochasticLayout = new QGridLayout;
    gboxMazeStochasticLayout->setObjectName(QString::fromUtf8("gboxMazeStochasticLayout"));
    gboxMazeStochasticLayout->setSpacing(6);
    gboxMazeStochasticLayout->setMargin(2);
    groupStochasticMazeChanges->setLayout(gboxMazeStochasticLayout);

    //////////////////////////////////////////////////////////////////////////
    labelRandomnessValue = new QLabel(groupStochasticMazeChanges);
    labelRandomnessValue->setObjectName(QString::fromUtf8("labelRandomnessValue"));
    gboxMazeStochasticLayout->addWidget(labelRandomnessValue,0,0,1,1);

    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, static_cast<QSizePolicy::Policy>(5));
    sizePolicy1.setHorizontalStretch(2);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(labelRandomnessValue->sizePolicy().hasHeightForWidth());
    labelRandomnessValue->setSizePolicy(sizePolicy1);


    spinRandomnessValue = new QSpinBox(groupStochasticMazeChanges);
    spinRandomnessValue->setObjectName(QString::fromUtf8("spinRandomnessValue"));
    spinRandomnessValue->setMaximum(50);
    spinRandomnessValue->setMinimum(1);
    spinRandomnessValue->setValue(1);
    gboxMazeStochasticLayout->addWidget(spinRandomnessValue,0,1,1,1);
    QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(0));
    sizePolicy2.setHorizontalStretch(2);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(spinRandomnessValue->sizePolicy().hasHeightForWidth());
    spinRandomnessValue->setSizePolicy(sizePolicy2);
    //////////////////////////////////////////////////////////////////////////
    checkBoxCumulativeRandomness = new QCheckBox(groupStochasticMazeChanges);
    gboxMazeStochasticLayout->addWidget(checkBoxCumulativeRandomness,1,0,1,2);

}
void CExperimentMazeParamsDlg::retranslate_ui()
{
    labelSizeX->setText(QApplication::translate("Dialog", "Size X", 0));
    labelMazeGenMethod->setText(QApplication::translate("Dialog", "Generation\nmethod", 0));
    labelSizeY->setText(QApplication::translate("Dialog", "Size Y", 0));
    comboGenerationMethod->addItem(tr("Kruskal's"), E_MT_KRUSKAL);
    comboGenerationMethod->addItem(tr("Recursive Backtracker"), E_MT_RECURSIVE);
    comboGenerationMethod->addItem(tr("Prim's"), E_MT_PRIM);
    button_generate_maze->setText("Generate");
    checkBoxMazeIsPerfect->setText("Maze is perfect");
    groupStochasticMazeChanges->setTitle("Maze probability");
    checkBoxCumulativeRandomness->setText("Accumulate\nprobability");
    labelRandomnessValue->setText(QApplication::translate("Dialog", "Probability", 0));
}
void CExperimentMazeParamsDlg::setConnections()
{
    bool bResult=false;
    bResult=connect(button_generate_maze,SIGNAL(clicked(bool)),this,SLOT(on_generate_maze(bool)));
    Q_ASSERT(bResult==true);
}
//////////////////////////////////////////////////////////////////////////
EMazeTypes CExperimentMazeParamsDlg::getMazeGenerationMethod()
{
	if (comboGenerationMethod->currentIndex()>-1)
		return (EMazeTypes)comboGenerationMethod->itemData(comboGenerationMethod->currentIndex()).toInt();
	else
		return E_MT_NONE;
}
void CExperimentMazeParamsDlg::setMazeGenerationMethod(EMazeTypes eType)
{
	comboGenerationMethod->blockSignals(true);
	for(int i=0;i<comboGenerationMethod->count();i++)
	{
		if (eType == (EMazeTypes)comboGenerationMethod->itemData(i).toInt())
		{
			comboGenerationMethod->setCurrentIndex(i);
			comboGenerationMethod->blockSignals(false);
			return;
		}
	}
	comboGenerationMethod->setCurrentIndex(-1);

	comboGenerationMethod->blockSignals(false);
}
//////////////////////////////////////////////////////////////////////////
void CExperimentMazeParamsDlg::set_maze_settings(maze_settings & stMazeSettings)
{
	spinSizeX->setValue(stMazeSettings.size_x);
	spinSizeY->setValue(stMazeSettings.size_y);
	setMazeGenerationMethod(stMazeSettings.mazeType);
	checkBoxMazeIsPerfect->setChecked(stMazeSettings.bMazePerfect);
}
void CExperimentMazeParamsDlg::get_maze_settings(maze_settings & stMazeSettings)
{
	stMazeSettings.size_x = spinSizeX->value();
	stMazeSettings.size_y = spinSizeY->value();
	stMazeSettings.mazeType=getMazeGenerationMethod();
	stMazeSettings.bMazePerfect=checkBoxMazeIsPerfect->isChecked();
}
void CExperimentMazeParamsDlg::on_generate_maze(bool)
{
	qRegisterMetaType<maze_settings>("maze_settings");
	maze_settings mazeSettings;
	get_maze_settings(mazeSettings);
    Q_EMIT generate_maze(mazeSettings);
}
