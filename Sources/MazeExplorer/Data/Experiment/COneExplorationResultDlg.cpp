#include "COneExplorationResultDlg.h"

COneExplorationResultDlg::COneExplorationResultDlg(QWidget *parent) : QDockWidget(parent)
{
    QStringList strList;
    setMinimumSize( 130,200 );
    resize(150,200 );
    setAllowedAreas(Qt::RightDockWidgetArea);
    topLevelChanged ( false );
    setWindowTitle(QApplication::translate("Dialog", "Wyniki exploracji", 0, QApplication::DefaultCodec));
    setFeatures(QDockWidget::AllDockWidgetFeatures);

    strList<<"X"<<"Y"<<"Kierunek";
    explorationResult = new QTableWidget(this);
    explorationResult->setColumnCount(3);
    explorationResult->setObjectName(QString::fromUtf8("explorationResult"));
    explorationResult->setGeometry(QRect(5, 25, 190, 190));
    explorationResult->setHorizontalHeaderLabels(strList);
    explorationResult->resizeColumnsToContents();
    explorationResult->setSelectionBehavior( QAbstractItemView::SelectRows );
    explorationResult->setSelectionMode(QAbstractItemView::SingleSelection);
    setWidget(explorationResult);
}
COneExplorationResultDlg::~COneExplorationResultDlg()
{

}
