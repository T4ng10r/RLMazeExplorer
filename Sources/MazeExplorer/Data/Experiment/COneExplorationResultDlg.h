#pragma once
#include <QtGui/QApplication>
#include <QtGui/QDockWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

class COneExplorationResultDlg : public QDockWidget
{
public:
    COneExplorationResultDlg(QWidget *parent);
    ~COneExplorationResultDlg();

    QTableWidget *	explorationResult;
    QVBoxLayout *	centralLayout;

};
