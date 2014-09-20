/********************************************************************************
** Form generated from reading UI file 'SingleRobotMoveDlg.ui'
**
** Created: Wed 14. Apr 15:08:11 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SINGLEROBOTMOVEDLG_H
#define SINGLEROBOTMOVEDLG_H

#include <QtCore/QVariant>
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

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_ptrRobotPosLabel;
    QLineEdit *m_ptrRobotPoslineEdit;
    QHBoxLayout *horizontalLayout;
    QWidget *scanResult_1;
    QWidget *scanResults_2;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *m_ptrTimeOutGroupBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_ptrTimeOutLabel;
    QSpinBox *m_ptrTimeOutValueSpinBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_ptrNextMoveButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(418, 438);
        Form->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_ptrRobotPosLabel = new QLabel(Form);
        m_ptrRobotPosLabel->setObjectName(QString::fromUtf8("m_ptrRobotPosLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_ptrRobotPosLabel->sizePolicy().hasHeightForWidth());
        m_ptrRobotPosLabel->setSizePolicy(sizePolicy);
        m_ptrRobotPosLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(m_ptrRobotPosLabel);

        m_ptrRobotPoslineEdit = new QLineEdit(Form);
        m_ptrRobotPoslineEdit->setObjectName(QString::fromUtf8("m_ptrRobotPoslineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_ptrRobotPoslineEdit->sizePolicy().hasHeightForWidth());
        m_ptrRobotPoslineEdit->setSizePolicy(sizePolicy1);
        m_ptrRobotPoslineEdit->setMaximumSize(QSize(16777215, 25));
        m_ptrRobotPoslineEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(m_ptrRobotPoslineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setContentsMargins(10, 10, 10, 10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scanResult_1 = new QWidget(Form);
        scanResult_1->setObjectName(QString::fromUtf8("scanResult_1"));

        horizontalLayout->addWidget(scanResult_1);

        scanResults_2 = new QWidget(Form);
        scanResults_2->setObjectName(QString::fromUtf8("scanResults_2"));

        horizontalLayout->addWidget(scanResults_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, 10, -1);
        m_ptrTimeOutGroupBox = new QGroupBox(Form);
        m_ptrTimeOutGroupBox->setObjectName(QString::fromUtf8("m_ptrTimeOutGroupBox"));
        m_ptrTimeOutGroupBox->setMaximumSize(QSize(16777215, 60));
        m_ptrTimeOutGroupBox->setCheckable(true);
        horizontalLayout_4 = new QHBoxLayout(m_ptrTimeOutGroupBox);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_ptrTimeOutLabel = new QLabel(m_ptrTimeOutGroupBox);
        m_ptrTimeOutLabel->setObjectName(QString::fromUtf8("m_ptrTimeOutLabel"));
        sizePolicy.setHeightForWidth(m_ptrTimeOutLabel->sizePolicy().hasHeightForWidth());
        m_ptrTimeOutLabel->setSizePolicy(sizePolicy);
        m_ptrTimeOutLabel->setMinimumSize(QSize(0, 20));
        m_ptrTimeOutLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(m_ptrTimeOutLabel);

        m_ptrTimeOutValueSpinBox = new QSpinBox(m_ptrTimeOutGroupBox);
        m_ptrTimeOutValueSpinBox->setObjectName(QString::fromUtf8("m_ptrTimeOutValueSpinBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_ptrTimeOutValueSpinBox->sizePolicy().hasHeightForWidth());
        m_ptrTimeOutValueSpinBox->setSizePolicy(sizePolicy2);
        m_ptrTimeOutValueSpinBox->setMinimumSize(QSize(0, 20));
        m_ptrTimeOutValueSpinBox->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(m_ptrTimeOutValueSpinBox);


        horizontalLayout_3->addWidget(m_ptrTimeOutGroupBox);

        horizontalSpacer = new QSpacerItem(40, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        m_ptrNextMoveButton = new QPushButton(Form);
        m_ptrNextMoveButton->setObjectName(QString::fromUtf8("m_ptrNextMoveButton"));
        sizePolicy.setHeightForWidth(m_ptrNextMoveButton->sizePolicy().hasHeightForWidth());
        m_ptrNextMoveButton->setSizePolicy(sizePolicy);
        m_ptrNextMoveButton->setMinimumSize(QSize(0, 20));
        m_ptrNextMoveButton->setMaximumSize(QSize(50, 25));

        horizontalLayout_3->addWidget(m_ptrNextMoveButton);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        m_ptrRobotPosLabel->setText(QApplication::translate("Form", "Robot position", 0));
        m_ptrTimeOutGroupBox->setTitle(QApplication::translate("Form", "GroupBox", 0));
        m_ptrTimeOutLabel->setText(QApplication::translate("Form", "TimOut between single moves", 0));
        m_ptrNextMoveButton->setText(QApplication::translate("Form", "Next", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SINGLEROBOTMOVEDLG_H
