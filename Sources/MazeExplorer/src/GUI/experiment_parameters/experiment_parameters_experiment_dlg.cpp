#include "experiment_parameters_experiment_dlg.h"

#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <Maze/maze_settings.h>

const QSize rcLearningParams(211, 141);
const QSize rcDockWidgetSize(451, 328);
const int	dockWidgetYPos(25);

class experiment_parameters_experiment_dlg_private
{
public:
	experiment_parameters_experiment_dlg_private(experiment_parameters_experiment_dlg * pub);

	void setup_ui();
    void retranslate_ui();
    void set_connections();
    void setup_learning_param_group();
    void setup_learning_method();
    void setup_learning_penalty_value();
    void setup_learning_price_value();
public:
	experiment_parameters_experiment_dlg * public_;

    QWidget *  gridLayoutWidget;
    QWidget *  groupLearningParamWidget;
    QLabel * labelLearningMethod;
    QLabel * labelPenaltyValue;
    QLabel * labelPriceValue;
    QComboBox * comboLearningMethod;
    QGroupBox * groupLearningParam;
    QPushButton * pushLearningMethod;
    QDoubleSpinBox * spinPriceValue;
    QDoubleSpinBox * spinPenaltyValue;
    QPushButton * pushPriceValue;
    QPushButton * pushPenaltyValue;
    QGridLayout * gridPenaltyPriceLayout;
    QHBoxLayout * hLearningMethodLayout;
    //////////////////////////////////////////////////////////////////////////
};

experiment_parameters_experiment_dlg_private::experiment_parameters_experiment_dlg_private(experiment_parameters_experiment_dlg * pub) : public_(pub)
{
    setup_ui();
    retranslate_ui();
    set_connections();
}
void experiment_parameters_experiment_dlg_private::setup_ui()
{
    QGridLayout *  main_layout = new QGridLayout;
    main_layout->setObjectName(QString::fromUtf8("mainLayout"));
    main_layout->setSpacing(6);
    main_layout->setMargin(4);
    delete public_->layout();
    public_->setLayout(main_layout);

    groupLearningParam = new QGroupBox();
    groupLearningParam->setObjectName(QString::fromUtf8("groupLearningParam"));
    groupLearningParam->setGeometry(QRect(210, dockWidgetYPos, 221, 231));
    groupLearningParam->setMinimumSize(rcLearningParams);

    main_layout->addWidget(groupLearningParam,0,2,1,1);

    groupLearningParamWidget = new QWidget(groupLearningParam);
    groupLearningParamWidget->setObjectName(QString::fromUtf8("groupLearningParamWidget"));
    groupLearningParamWidget->setGeometry(QRect(10, 20, 191, 27));
    setup_learning_method();

    gridLayoutWidget = new QWidget(groupLearningParam);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(10, 70, 191, 58));

    gridPenaltyPriceLayout = new QGridLayout(gridLayoutWidget);
    gridPenaltyPriceLayout->setSpacing(6);
    gridPenaltyPriceLayout->setMargin(0);
    gridPenaltyPriceLayout->setObjectName(QString::fromUtf8("gridPenaltyPriceLayout"));

    setup_learning_penalty_value();
    setup_learning_price_value();
    retranslate_ui();
}
void experiment_parameters_experiment_dlg_private::retranslate_ui()
{
    groupLearningParam->setTitle(QObject::tr("param_eks", "Learning parameters", 0));
    labelLearningMethod->setText(QObject::tr("param_eks", "Learning method", 0));
    pushLearningMethod->setText(QObject::tr("param_eks", "?", 0));
    labelPenaltyValue->setText(QObject::tr("param_eks", "Penalty value", 0));
    labelPriceValue->setText(QObject::tr("param_eks", "Reward value", 0));
    pushPriceValue->setText(QObject::tr("param_eks", "?", 0));
    pushPenaltyValue->setText(QObject::tr("param_eks", "?", 0));
}
void experiment_parameters_experiment_dlg_private::set_connections(){}
void experiment_parameters_experiment_dlg_private::setup_learning_param_group() {}
void experiment_parameters_experiment_dlg_private::setup_learning_method()
{
    hLearningMethodLayout = new QHBoxLayout(groupLearningParamWidget);
    hLearningMethodLayout->setSpacing(6);
    hLearningMethodLayout->setMargin(0);
    hLearningMethodLayout->setObjectName(QString::fromUtf8("hLearningMethodLayout"));

    labelLearningMethod = new QLabel(groupLearningParamWidget);
    labelLearningMethod->setObjectName(QString::fromUtf8("labelLearningMethod"));
    QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(1));
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(labelLearningMethod->sizePolicy().hasHeightForWidth());
    labelLearningMethod->setSizePolicy(sizePolicy1);
    hLearningMethodLayout->addWidget(labelLearningMethod);

    comboLearningMethod = new QComboBox(groupLearningParamWidget);
    comboLearningMethod->setObjectName(QString::fromUtf8("comboLearningMethod"));
    QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(3), static_cast<QSizePolicy::Policy>(0));
    sizePolicy2.setHorizontalStretch(3);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(comboLearningMethod->sizePolicy().hasHeightForWidth());
    comboLearningMethod->setSizePolicy(sizePolicy2);
    comboLearningMethod->addItem("Metoda 1");
    comboLearningMethod->addItem("Metoda 2");

    hLearningMethodLayout->addWidget(comboLearningMethod);

    pushLearningMethod = new QPushButton(groupLearningParamWidget);
    pushLearningMethod->setObjectName(QString::fromUtf8("pushLearningMethod"));
    QSizePolicy sizePolicy3(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(pushLearningMethod->sizePolicy().hasHeightForWidth());
    pushLearningMethod->setSizePolicy(sizePolicy3);
    pushLearningMethod->setMaximumSize(QSize(25, 16777215));

    hLearningMethodLayout->addWidget(pushLearningMethod);
}
void experiment_parameters_experiment_dlg_private::setup_learning_penalty_value()
{
    labelPenaltyValue = new QLabel(gridLayoutWidget);
    labelPenaltyValue->setObjectName(QString::fromUtf8("labelPenaltyValue"));
    gridPenaltyPriceLayout->addWidget(labelPenaltyValue, 1, 0, 1, 1);

    spinPenaltyValue = new QDoubleSpinBox(gridLayoutWidget);
    spinPenaltyValue->setObjectName(QString::fromUtf8("spinPenaltyValue"));
    QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(0));
    sizePolicy1.setHorizontalStretch(2);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(spinPenaltyValue->sizePolicy().hasHeightForWidth());
    spinPenaltyValue->setSizePolicy(sizePolicy1);
    spinPenaltyValue->setMaximum(100);
    spinPenaltyValue->setMinimum(0);
    spinPenaltyValue->setSingleStep(0.01);
    spinPenaltyValue->setValue(0.5);

    gridPenaltyPriceLayout->addWidget(spinPenaltyValue, 1, 1, 1, 1);

    pushPenaltyValue = new QPushButton(gridLayoutWidget);
    pushPenaltyValue->setObjectName(QString::fromUtf8("pushPenaltyValue"));
    QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(pushPenaltyValue->sizePolicy().hasHeightForWidth());
    pushPenaltyValue->setSizePolicy(sizePolicy2);
    pushPenaltyValue->setMaximumSize(QSize(25, 16777215));

    gridPenaltyPriceLayout->addWidget(pushPenaltyValue, 1, 2, 1, 1);

}
void experiment_parameters_experiment_dlg_private::setup_learning_price_value()
{
    labelPriceValue = new QLabel(gridLayoutWidget);
    labelPriceValue->setObjectName(QString::fromUtf8("labelPriceValue"));
    gridPenaltyPriceLayout->addWidget(labelPriceValue, 0, 0, 1, 1);

    spinPriceValue = new QDoubleSpinBox(gridLayoutWidget);
    spinPriceValue->setObjectName(QString::fromUtf8("spinPriceValue"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(2);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(spinPriceValue->sizePolicy().hasHeightForWidth());
    spinPriceValue->setSizePolicy(sizePolicy);
    spinPriceValue->setMaximum(100);
    spinPriceValue->setMinimum(0);
    spinPriceValue->setSingleStep(0.01);
    spinPriceValue->setValue(0.5);
    gridPenaltyPriceLayout->addWidget(spinPriceValue, 0, 1, 1, 1);

    pushPriceValue = new QPushButton(gridLayoutWidget);
    pushPriceValue->setObjectName(QString::fromUtf8("pushPriceValue"));
    QSizePolicy sizePolicy6(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy6.setHorizontalStretch(0);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(pushPriceValue->sizePolicy().hasHeightForWidth());
    pushPriceValue->setSizePolicy(sizePolicy6);
    pushPriceValue->setMaximumSize(QSize(25, 16777215));

    gridPenaltyPriceLayout->addWidget(pushPriceValue, 0, 2, 1, 1);
}
////////////////////////////////////////////////////////////////////////////////
experiment_parameters_experiment_dlg::experiment_parameters_experiment_dlg(QWidget *parent) : QWidget(parent), pimpl(new experiment_parameters_experiment_dlg_private(this))
{}
experiment_parameters_experiment_dlg::~experiment_parameters_experiment_dlg(){};
void experiment_parameters_experiment_dlg::getExperimentSettings(experiment_settings & cExperimentSettings)
{
    cExperimentSettings.fPenaltyValue = pimpl->spinPenaltyValue->value();
    cExperimentSettings.fPriceValue = pimpl->spinPriceValue->value();
}
