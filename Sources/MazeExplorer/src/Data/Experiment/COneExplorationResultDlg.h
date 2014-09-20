#pragma once
#include <QApplication>
#include <QDockWidget>
#include <QTableWidget>
#include <QVBoxLayout>

class COneExplorationResultDlg : public QDockWidget
{
public:
    COneExplorationResultDlg(QWidget *parent);
    ~COneExplorationResultDlg();

    QTableWidget *	explorationResult;
    QVBoxLayout *	centralLayout;

};
