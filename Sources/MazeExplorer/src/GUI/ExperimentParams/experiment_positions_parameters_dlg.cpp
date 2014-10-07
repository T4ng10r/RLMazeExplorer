#include "experiment_positions_parameters_dlg.h"

#include <QItemEditorFactory>
#include <QItemEditorCreator>
#include <Tools/loggers.h>
#include <QtCore/QTextCodec>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QApplication>
#include <QSpacerItem>
#include <QComboBox>
#include <QPushButton>
#include <QItemDelegate>
#include <vector>
#include <map>

const int maxFinishPos(5);
const QSize rcExperimentParams(171, 211);

class PositionItemEditor : public QSpinBox
{
public :
	PositionItemEditor(QWidget *widget = 0):QSpinBox(widget)
	{
		setMinimum(1);
		setMaximum(sIntMax);
	};
	static int sIntMax;
};
int PositionItemEditor::sIntMax=10;

class experiment_positions_parameters_dlg_private
{
public:
	experiment_positions_parameters_dlg_private(experiment_positions_parameters_dlg * pub);
	void setup_ui();
	void retranslate_ui();
	void setupRepeatQuant();
	void setupStartingPos();
	void setupFinishPos();
	void setConnections();
public:
	experiment_positions_parameters_dlg * public_;
	int			m_iDirSelected;

	//	QGroupBox*	groupExperimentParam;
	QVBoxLayout *	m_ptrMainLayout;


	QVBoxLayout *	vboxExperimentParamLayout;
	QHBoxLayout *	hboxLayout;
	QLabel *		labelRepeatQuantity;
	QSpinBox *		spinRepeatQuantity;
	QGroupBox *		groupStartingPos;
	QWidget *		groupStartingPosWidget;
	QHBoxLayout *	hStartPosLayout;
	QGridLayout *	gStartPosLayout;

	QLabel *		labelStartX;
	QSpinBox *		spinStartX;
	QLabel *		labelStartY;
	QSpinBox *		spinStartY;
	QLabel *		labelStartDir;
	QComboBox *		comboStartDir;

	QGroupBox *		groupFinishPos;
	QVBoxLayout *	hFinishPosLayout;
	QTableWidget *	tableFinishPos;
	QTableView *	tableViewFinishPos;
	QStandardItemModel * modelFinishPos;
	QWidget *		layoutWidget;
	QHBoxLayout *	hButtonsLayout;
	QSpacerItem *	spacerItem;


	QItemDelegate * ptrDelegate;
	QItemEditorFactory * ptrFactory;

	//CSpinBoxDelegate delegate;

	//
	QHBoxLayout *	hAddRemoveButtonsLayout;

	QPushButton *    addFinishPos;
	QPushButton *    removeFinishPos;

	//	CExperimentParamsMazeDlg * 	widgetExperimentParam;

};
experiment_positions_parameters_dlg_private::experiment_positions_parameters_dlg_private(experiment_positions_parameters_dlg * pub) :
public_(pub)
{
	QTextCodec::codecForName("System");
	setup_ui();
	retranslate_ui();
	setConnections();

	QItemEditorFactory *ptrFactory = new QItemEditorFactory;

	QItemEditorCreatorBase *positionItemCreator =
		new QStandardItemEditorCreator<PositionItemEditor>();

	ptrFactory->registerEditor(QVariant::Int, positionItemCreator);
	//QItemEditorFactory::setDefaultFactory(ptrFactory);
	ptrDelegate = new QItemDelegate;

	ptrDelegate->setItemEditorFactory(ptrFactory);
	tableViewFinishPos->setItemDelegate(ptrDelegate);
}
void experiment_positions_parameters_dlg_private::setup_ui()
{
	m_ptrMainLayout = new QVBoxLayout;
	m_ptrMainLayout->setObjectName(QString::fromUtf8("vboxExperimentParamLayout"));
	m_ptrMainLayout->setSpacing(6);
	m_ptrMainLayout->setMargin(4);
	delete public_->layout();
	public_->setLayout(m_ptrMainLayout);

	setupRepeatQuant();
	setupStartingPos();
	setupFinishPos();
}
void experiment_positions_parameters_dlg_private::setupRepeatQuant()
{
	hboxLayout = new QHBoxLayout;
	hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
	hboxLayout->setSpacing(4);
	hboxLayout->setMargin(0);
	m_ptrMainLayout->addLayout(hboxLayout);
	//////////////////////////////////////////////////////////////////////////
	labelRepeatQuantity = new QLabel(public_);
	labelRepeatQuantity->setObjectName(QString::fromUtf8("labelRepeatQuantity"));

	QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
	sizePolicy.setHorizontalStretch(2);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(labelRepeatQuantity->sizePolicy().hasHeightForWidth());
	labelRepeatQuantity->setSizePolicy(sizePolicy);

	hboxLayout->addWidget(labelRepeatQuantity);

	spinRepeatQuantity = new QSpinBox(public_);
	spinRepeatQuantity->setObjectName(QString::fromUtf8("spinRepeatQuantity"));
	spinRepeatQuantity->setMaximum(1999);
	spinRepeatQuantity->setMinimum(1);
	//TODO ilosc powtorzen jest tymczasowo ustawiona na 2
	spinRepeatQuantity->setValue(2);

	hboxLayout->addWidget(spinRepeatQuantity);
}
void experiment_positions_parameters_dlg_private::setupStartingPos()
{
	groupStartingPos = new QGroupBox(public_);
	groupStartingPos->setObjectName(QString::fromUtf8("groupStartingPos"));
	m_ptrMainLayout->addWidget(groupStartingPos);
	//////////////////////////////////////////////////////////////////////////
	gStartPosLayout = new QGridLayout();
	gStartPosLayout->setSpacing(6);
	gStartPosLayout->setMargin(2);
	gStartPosLayout->setObjectName(QString::fromUtf8("gStartPosLayout"));
	groupStartingPos->setLayout(gStartPosLayout);
	//////////////////////////////////////////////////////////////////////////
	labelStartX = new QLabel(groupStartingPos);
	labelStartX->setObjectName(QString::fromUtf8("labelSTartX"));
	//	QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
	//	sizePolicy.setHorizontalStretch(2);
	//	sizePolicy.setVerticalStretch(0);
	//	sizePolicy.setHeightForWidth(labelRepeatQuantity->sizePolicy().hasHeightForWidth());
	//labelStartX->setSizePolicy(sizePolicy);

	gStartPosLayout->addWidget(labelStartX, 0, 0, 1, 1);
	//////////////////////////////////////////////////////////////////////////
	spinStartX = new QSpinBox(groupStartingPos);
	spinStartX->setObjectName(QString::fromUtf8("spinStartX"));
	spinStartX->setMinimum(1);
	spinStartX->setMinimumSize(QSize(41, 20));

	gStartPosLayout->addWidget(spinStartX, 1, 0, 1, 1);
	//////////////////////////////////////////////////////////////////////////
	labelStartY = new QLabel(groupStartingPos);
	labelStartY->setObjectName(QString::fromUtf8("labelStartY"));
	//QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
	//sizePolicy1.setHorizontalStretch(2);
	//sizePolicy1.setVerticalStretch(0);
	//sizePolicy1.setHeightForWidth(labelRepeatQuantity->sizePolicy().hasHeightForWidth());
	//labelStartY->setSizePolicy(sizePolicy1);

	gStartPosLayout->addWidget(labelStartY, 0, 1, 1, 1);
	//////////////////////////////////////////////////////////////////////////
	spinStartY = new QSpinBox(groupStartingPos);
	spinStartY->setObjectName(QString::fromUtf8("spinStartY"));
	spinStartY->setMinimum(1);
	spinStartY->setMinimumSize(QSize(41, 20));

	gStartPosLayout->addWidget(spinStartY, 1, 1, 1, 1);
	//////////////////////////////////////////////////////////////////////////
	labelStartDir = new QLabel(groupStartingPos);
	labelStartDir->setObjectName(QString::fromUtf8("labelStartDir"));
	QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
	sizePolicy2.setHorizontalStretch(2);
	sizePolicy2.setVerticalStretch(0);
	sizePolicy2.setHeightForWidth(labelStartDir->sizePolicy().hasHeightForWidth());
	labelStartDir->setSizePolicy(sizePolicy2);
	gStartPosLayout->addWidget(labelStartDir, 0, 2, 1, 1);
	//////////////////////////////////////////////////////////////////////////
	comboStartDir = new QComboBox(groupStartingPos);
	comboStartDir->setObjectName(QString::fromUtf8("comboStartDir"));
	comboStartDir->addItem(QIcon(":/images/north.png"), QObject::tr("North"), ROBOT_NORTH_DIR);
	comboStartDir->addItem(QIcon(":/images/west.png"), QObject::tr("West"), ROBOT_WEST_DIR);
	comboStartDir->addItem(QIcon(":/images/east.png"), QObject::tr("East"), ROBOT_EAST_DIR);
	comboStartDir->addItem(QIcon(":/images/south.png"), QObject::tr("South"), ROBOT_SOUTH_DIR);

	comboStartDir->setMinimumSize(QSize(53, 20));
	gStartPosLayout->addWidget(comboStartDir, 1, 2, 1, 1);
}
void experiment_positions_parameters_dlg_private::setupFinishPos()
{
	groupFinishPos = new QGroupBox(public_);
	groupFinishPos->setObjectName(QString::fromUtf8("groupFinishPos"));

	m_ptrMainLayout->addWidget(groupFinishPos);
	//////////////////////////////////////////////////////////////////////////
	hFinishPosLayout = new QVBoxLayout();
	hFinishPosLayout->setSpacing(6);
	hFinishPosLayout->setMargin(4);
	hFinishPosLayout->setObjectName(QString::fromUtf8("hStartPosLayout"));

	delete groupFinishPos->layout();
	groupFinishPos->setLayout(hFinishPosLayout);
	//////////////////////////////////////////////////////////////////////////
	tableViewFinishPos = new QTableView(groupFinishPos);
	tableViewFinishPos->setObjectName(QString::fromUtf8("tableViewFinishPos"));
	//tableViewFinishPos->horizontalHeader()->setResizeMode(QHeaderView::Stretch); //TOFIX
	hFinishPosLayout->addWidget(tableViewFinishPos);

	modelFinishPos = new QStandardItemModel(1, 2);

	tableViewFinishPos->setModel(modelFinishPos);
	tableViewFinishPos->setColumnWidth(0, 50);
	tableViewFinishPos->setColumnWidth(1, 50);
	tableViewFinishPos->resizeRowsToContents();
	//ustawiamy dane w stosownych kom�rkach
	QModelIndex index = modelFinishPos->index(0, 0, QModelIndex());
	modelFinishPos->setData(index, QVariant(10));

	index = modelFinishPos->index(0, 1, QModelIndex());
	modelFinishPos->setData(index, QVariant(10));

	modelFinishPos->setHeaderData(0, Qt::Horizontal, QVariant("X"), Qt::DisplayRole);
	modelFinishPos->setHeaderData(1, Qt::Horizontal, QVariant("Y"), Qt::DisplayRole);
	//********************************************************************//
	hAddRemoveButtonsLayout = new QHBoxLayout();
	hAddRemoveButtonsLayout->setSpacing(6);
	hAddRemoveButtonsLayout->setMargin(4);
	hAddRemoveButtonsLayout->setObjectName(QString::fromUtf8("hAddRemoveButtonsLayout"));
	//
	addFinishPos = new QPushButton();
	addFinishPos->setIcon(QIcon(":/images/plus.png"));

	removeFinishPos = new QPushButton();
	removeFinishPos->setEnabled(false);
	removeFinishPos->setIcon(QIcon(":/images/minus.png"));

	hAddRemoveButtonsLayout->addStretch(2);
	hAddRemoveButtonsLayout->addWidget(addFinishPos);
	hAddRemoveButtonsLayout->addWidget(removeFinishPos);

	hFinishPosLayout->addLayout(hAddRemoveButtonsLayout);
}
void experiment_positions_parameters_dlg_private::retranslate_ui()
{
	labelRepeatQuantity->setText(QApplication::translate("param_eks", "Ilość powtórzeń", 0));
	//labelRepeatQuantity->setText(QApplication::translate("param_eks", "Ilość powtórzeń", 0));
	groupStartingPos->setTitle(QApplication::translate("param_eks", "Pozycja startowa", 0));
	labelStartX->setText(QApplication::translate("param_eks", "X", 0));
	labelStartY->setText(QApplication::translate("param_eks", "Y", 0));
	labelStartDir->setText(QApplication::translate("param_eks", "Kierunek", 0));
	groupFinishPos->setTitle(QApplication::translate("param_eks", "Pozycje końcowe", 0));
}
void experiment_positions_parameters_dlg_private::setConnections()
{
	bool bResult = QObject::connect(spinStartX, SIGNAL(valueChanged(int)), public_, SLOT(onInternalStartPosChange()));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(spinStartY, SIGNAL(valueChanged(int)), public_, SLOT(onInternalStartPosChange()));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(modelFinishPos, SIGNAL(itemChanged(QStandardItem *)), public_, SLOT(onInternalFinishPostionChanged(QStandardItem *)));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(comboStartDir, SIGNAL(highlighted(int)), public_, SLOT(onInternalDirectionChanged(int)));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(comboStartDir, SIGNAL(currentIndexChanged(int)), public_, SLOT(onInternalDirectionChanged(int)));
	Q_ASSERT(bResult == true);

	bResult = QObject::connect(addFinishPos, SIGNAL(clicked(bool)), public_, SLOT(onButtonAddFinishPos()));
	Q_ASSERT(bResult == true);
	bResult = QObject::connect(removeFinishPos, SIGNAL(clicked(bool)), public_, SLOT(onButtonRemFinishPos()));
	Q_ASSERT(bResult == true);
}
//////////////////////////////////////////////////////////////////////////
experiment_positions_parameters_dlg::experiment_positions_parameters_dlg(QWidget *parent) : QWidget(parent), pimpl(new experiment_positions_parameters_dlg_private(this))
{
}
experiment_positions_parameters_dlg::~experiment_positions_parameters_dlg()
{
	delete pimpl->ptrDelegate;
}
//////////////////////////////////////////////////////////////////////////
void experiment_positions_parameters_dlg::setExperimentSettings(CExperimentSettings & cExperimentSettings)
{
	pimpl->spinStartX->blockSignals(true);
	pimpl->spinStartY->blockSignals(true);

	pimpl->spinStartX->setValue(cExperimentSettings.startPosition.posX);
	pimpl->spinStartY->setValue(cExperimentSettings.startPosition.posY);

	std::list<QPoint>::const_iterator iterFinishPos = cExperimentSettings.lFinishPositions.begin();
	pimpl->modelFinishPos->setRowCount(cExperimentSettings.lFinishPositions.size());
	for (int i = 0; i<pimpl->modelFinishPos->rowCount(); i++)
	{
		QModelIndex index = pimpl->modelFinishPos->index(i, 0);
		pimpl->modelFinishPos->setData(index, iterFinishPos->x());
		index = pimpl->modelFinishPos->index(i, 1);
		pimpl->modelFinishPos->setData(index, iterFinishPos->y());
	}

	pimpl->spinStartX->blockSignals(false);
	pimpl->spinStartY->blockSignals(false);
}
void experiment_positions_parameters_dlg::getExperimentSettings(CExperimentSettings & cExperimentSettings)
{
	QModelIndex index;
	QPoint pos;
	int rowCount = pimpl->modelFinishPos->rowCount();
	cExperimentSettings.repeatingQuantity = pimpl->spinRepeatQuantity->value();
	cExperimentSettings.startPosition.posX = pimpl->spinStartX->value();
	cExperimentSettings.startPosition.posY = pimpl->spinStartY->value();
	cExperimentSettings.lFinishPositions.clear();
	for(int i =0; i<rowCount; i++)
	{
		index = pimpl->modelFinishPos->index(i, 0, QModelIndex());
		pos.setX(pimpl->modelFinishPos->data(index).toInt());
		index = pimpl->modelFinishPos->index(i, 1, QModelIndex());
		pos.setY(pimpl->modelFinishPos->data(index).toInt());
		cExperimentSettings.lFinishPositions.push_back(pos);
	}
	QString text = pimpl->comboStartDir->itemText(pimpl->m_iDirSelected);

	cExperimentSettings.startPosition.dir =
		(text == "North") ? ROBOT_NORTH_DIR :
		(text == "West") ? ROBOT_WEST_DIR :
		(text == "South") ? ROBOT_SOUTH_DIR : ROBOT_EAST_DIR;
}
//////////////////////////////////////////////////////////////////////////
void experiment_positions_parameters_dlg::onInternalStartPosChange()
{
	int X = pimpl->spinStartX->value();
	int Y = pimpl->spinStartY->value();
    Q_EMIT on_set_start_position(X,Y);
}
void experiment_positions_parameters_dlg::onInternalFinishPostionChanged(QStandardItem *)
{
	std::vector< std::pair< int, int> > vPositionsList;
	bool bResult;
	bResult=true;
	for (int i = 0; i<pimpl->modelFinishPos->rowCount(); i++)
	{
		std::pair<int, int> pozycja;
		QModelIndex index = pimpl->modelFinishPos->index(i, 0, QModelIndex());
		pozycja.first = pimpl->modelFinishPos->data(index).toInt();

		index = pimpl->modelFinishPos->index(i, 1, QModelIndex());
		pozycja.second = pimpl->modelFinishPos->data(index).toInt();
		vPositionsList.push_back(pozycja);
	}
	Q_EMIT setFinishPositions(vPositionsList);
}
void experiment_positions_parameters_dlg::onInternalDirectionChanged(int iIndex)
{
	pimpl->m_iDirSelected = pimpl->comboStartDir->itemData(iIndex).toInt();
	//QString strInfo = QString ("robot start direction selected: %1").arg(m_iDirSelected);
	//Log4Qt::Logger::logger("Process")->info(strInfo);
	Q_EMIT setStartDirection(pimpl->m_iDirSelected);
}
//////////////////////////////////////////////////////////////////////////
void experiment_positions_parameters_dlg::onNewStartPosition(int posX,int posY)
{
    blockSignals(true);

	pimpl->spinStartX->blockSignals(true);
	if (pimpl->spinStartX->maximum()<posX)
		pimpl->spinStartX->setMaximum(posX);
	pimpl->spinStartX->setValue(posX);
	pimpl->spinStartX->blockSignals(false);

	pimpl->spinStartY->blockSignals(true);
	if (pimpl->spinStartY->maximum()<posY)
		pimpl->spinStartY->setMaximum(posY);
	pimpl->spinStartY->setValue(posY);
	pimpl->spinStartX->blockSignals(false);

    blockSignals(false);
}
void experiment_positions_parameters_dlg::onNewFinishPosition(int posX,int posY)
{
    //to ma prawo zaistniec tylko jesli labirynt ma miec jedno wyjscie
    //czyli czyscimy tablice z wszystkich wpis�w poza tym jednym
    blockSignals(true);

	int rowCount = pimpl->modelFinishPos->rowCount();
	pimpl->modelFinishPos->removeRows(1, rowCount - 1);

	rowCount = pimpl->modelFinishPos->rowCount();

	QModelIndex index = pimpl->modelFinishPos->index(0, 0, QModelIndex());
	pimpl->modelFinishPos->setData(index, QVariant(posX));

	index = pimpl->modelFinishPos->index(0, 1, QModelIndex());
	pimpl->modelFinishPos->setData(index, QVariant(posY));
    blockSignals(false);
	pimpl->tableViewFinishPos->resizeRowsToContents();
}
void experiment_positions_parameters_dlg::onAddFinishPosition(int posX,int posY)
{
	int rowCount = pimpl->modelFinishPos->rowCount();
	if (rowCount>=maxFinishPos)	return;
    blockSignals(true);
	pimpl->modelFinishPos->insertRow(rowCount);

	QModelIndex index = pimpl->modelFinishPos->index(rowCount, 0, QModelIndex());
	pimpl->modelFinishPos->setData(index, QVariant(posX));

	index = pimpl->modelFinishPos->index(rowCount, 1, QModelIndex());
	pimpl->modelFinishPos->setData(index, QVariant(posY));
    blockSignals(false);
	pimpl->tableViewFinishPos->resizeRowsToContents();
}
//////////////////////////////////////////////////////////////////////////
//void CExperimentPositionsParamsDlg::onMazeSizeChange(int iX,int iY)
//{
//    spinStartX->setMaximum(iX);
//    spinStartY->setMaximum(iY);
//    emit on_set_start_position(spinStartX->value(),spinStartY->value());
//
//    //ustawiamy dla wszystkich pol w finish pos maxymalna wartosc
//    for(int i=0; i<modelFinishPos->rowCount(); i++)
//    {
//        QModelIndex index = modelFinishPos->index(i, 0, QModelIndex());
//        QVariant value=modelFinishPos->data(index);
//        if (value.toInt()>iX)
//            modelFinishPos->setData(index, QVariant(iX));
//        index = modelFinishPos->index(i, 1, QModelIndex());
//        value=modelFinishPos->data(index);
//        if (value.toInt()>iY)
//            modelFinishPos->setData(index, QVariant(iY));
//    }
//}
void experiment_positions_parameters_dlg::onButtonAddFinishPos()
{
	int count = pimpl->modelFinishPos->rowCount();
    //QStandardItem * item = new QStandardItem();
    if (count>=maxFinishPos-1)
		pimpl->addFinishPos->setEnabled(false);
    if (count==maxFinishPos)	
	{
		pimpl->addFinishPos->setEnabled(false);
		return;
	}
	pimpl->removeFinishPos->setEnabled(true);

	QList<QStandardItem *> lItems;
	QStandardItem * pItem = new QStandardItem;
	pItem->setData(2, Qt::DisplayRole);
	lItems.push_back(pItem);
	pItem = new QStandardItem;
	pItem->setData(2, Qt::DisplayRole);
	lItems.push_back(pItem);

	pimpl->modelFinishPos->insertRow(count, lItems);
	pimpl->tableViewFinishPos->resizeRowsToContents();
    onInternalFinishPostionChanged(NULL);
}
void experiment_positions_parameters_dlg::onButtonRemFinishPos()
{
	std::vector<int>	vRows;
	int count = pimpl->modelFinishPos->rowCount();
    int iRow;
    if (count==2)
		pimpl->removeFinishPos->setEnabled(false);
    if (count==1)
        return;
	pimpl->addFinishPos->setEnabled(true);
    //sprawdz jaki element jest zaznaczony
	QItemSelectionModel * selectModel = pimpl->tableViewFinishPos->selectionModel();
    for (int i = count-1; i >= 0; --i )
    {
		QModelIndex index = pimpl->modelFinishPos->index(i, 0);
        iRow = index.row();
        if (selectModel->isSelected(index))
        {
            break;
        }
        else iRow = -1;
    }
    if (iRow==-1)
        iRow = count-1;
    //usuwamy element iRow
	pimpl->modelFinishPos->removeRow(iRow);
    onInternalFinishPostionChanged(NULL);
	pimpl->tableViewFinishPos->resizeRowsToContents();
}
void experiment_positions_parameters_dlg::onMazeGeneration(maze_settings xMazeSettings)
{
	if (false == isEnabled())
		setEnabled(true);
	pimpl->spinStartX->setMaximum(xMazeSettings.size_x);
	pimpl->spinStartY->setMaximum(xMazeSettings.size_y);
	PositionItemEditor::sIntMax=xMazeSettings.size_x;
	//emit on_set_start_position(spinStartX->value(),spinStartY->value());
}