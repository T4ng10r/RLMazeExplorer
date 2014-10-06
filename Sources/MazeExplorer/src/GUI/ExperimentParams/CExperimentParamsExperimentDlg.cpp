#include "CExperimentParamsExperimentDlg.h"

CExperimentParamsExperimentDlg::CExperimentParamsExperimentDlg(QWidget *parent) : QWidget(parent)
{
    setup_ui();
    retranslate_ui();
    setConnections();
}

void CExperimentParamsExperimentDlg::setup_ui()
{
    mainLayout = new QGridLayout;
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    mainLayout->setSpacing(6);
    mainLayout->setMargin(4);
    delete layout();
    setLayout(mainLayout);

    groupLearningParam = new QGroupBox();
    groupLearningParam->setObjectName(QString::fromUtf8("groupLearningParam"));
    groupLearningParam->setGeometry(QRect(210, dockWidgetYPos, 221, 231));
    groupLearningParam->setMinimumSize(rcLearningParams);

    mainLayout->addWidget(groupLearningParam,0,2,1,1);

    groupLearningParamWidget = new QWidget(groupLearningParam);
    groupLearningParamWidget->setObjectName(QString::fromUtf8("groupLearningParamWidget"));
    groupLearningParamWidget->setGeometry(QRect(10, 20, 191, 27));
    setupLearningMethod();

    gridLayoutWidget = new QWidget(groupLearningParam);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(10, 70, 191, 58));

    gridPenaltyPriceLayout = new QGridLayout(gridLayoutWidget);
    gridPenaltyPriceLayout->setSpacing(6);
    gridPenaltyPriceLayout->setMargin(0);
    gridPenaltyPriceLayout->setObjectName(QString::fromUtf8("gridPenaltyPriceLayout"));

    setupLearningPenaltyValue();
    setupLearningPriceValue();
    retranslate_ui();
}
void CExperimentParamsExperimentDlg::retranslate_ui()
{
    groupLearningParam->setTitle(QApplication::translate("param_eks", "Parametry uczenia", 0));
    labelLearningMethod->setText(QApplication::translate("param_eks", "Metoda", 0));
    pushLearningMethod->setText(QApplication::translate("param_eks", "?", 0));
    labelPenaltyValue->setText(QApplication::translate("param_eks", "Warto\305\233\304\207 kary", 0));
    labelPriceValue->setText(QApplication::translate("param_eks", "Warto\305\233\304\207 nagrody", 0));
    pushPriceValue->setText(QApplication::translate("param_eks", "?", 0));
    pushPenaltyValue->setText(QApplication::translate("param_eks", "?", 0));
}
void CExperimentParamsExperimentDlg::setConnections()
{
}
void CExperimentParamsExperimentDlg::setupLearningParamGroup() {}
void CExperimentParamsExperimentDlg::setupLearningMethod()
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
void CExperimentParamsExperimentDlg::setupLearningPenaltyValue()
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
void CExperimentParamsExperimentDlg::setupLearningPriceValue()
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
void CExperimentParamsExperimentDlg::getExperimentSettings(CExperimentSettings & cExperimentSettings)
{
    cExperimentSettings.fPenaltyValue = spinPenaltyValue->value();
    cExperimentSettings.fPriceValue = spinPriceValue->value();
}
