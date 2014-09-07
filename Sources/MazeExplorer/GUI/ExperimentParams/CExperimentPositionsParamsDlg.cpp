#include "CExperimentPositionsParamsDlg.h"
#include <QtGui/QItemEditorFactory>
#include <QtGui/QItemEditorCreator>
#include <log4qt/logger.h>
#include <QtCore/QTextCodec>

const int maxFinishPos(5);

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

CExperimentPositionsParamsDlg::CExperimentPositionsParamsDlg(QWidget *parent) : QWidget(parent)
{
	QTextCodec::setCodecForTr(QTextCodec::codecForName ("System"));
	setupUI();
	retranslateUI();
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
CExperimentPositionsParamsDlg::~CExperimentPositionsParamsDlg()
{
	delete ptrDelegate;
}
void CExperimentPositionsParamsDlg::setupUI()
{
    m_ptrMainLayout = new QVBoxLayout;
    m_ptrMainLayout->setObjectName(QString::fromUtf8("vboxExperimentParamLayout"));
    m_ptrMainLayout->setSpacing(6);
    m_ptrMainLayout->setMargin(4);
    delete layout();
    setLayout(m_ptrMainLayout);

    setupRepeatQuant();
    setupStartingPos();
    setupFinishPos();
}
void CExperimentPositionsParamsDlg::setupRepeatQuant()
{
    hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout->setSpacing(4);
    hboxLayout->setMargin(0);
    m_ptrMainLayout->addLayout(hboxLayout);
    //////////////////////////////////////////////////////////////////////////
    labelRepeatQuantity = new QLabel(this);
    labelRepeatQuantity->setObjectName(QString::fromUtf8("labelRepeatQuantity"));

    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    sizePolicy.setHorizontalStretch(2);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(labelRepeatQuantity->sizePolicy().hasHeightForWidth());
    labelRepeatQuantity->setSizePolicy(sizePolicy);

    hboxLayout->addWidget(labelRepeatQuantity);

    spinRepeatQuantity = new QSpinBox(this);
    spinRepeatQuantity->setObjectName(QString::fromUtf8("spinRepeatQuantity"));
    spinRepeatQuantity->setMaximum(1999);
    spinRepeatQuantity->setMinimum(1);
    //TODO ilosc powtorzen jest tymczasowo ustawiona na 2
    spinRepeatQuantity->setValue(2);

    hboxLayout->addWidget(spinRepeatQuantity);
}
void CExperimentPositionsParamsDlg::setupStartingPos()
{
    groupStartingPos = new QGroupBox(this);
    groupStartingPos->setObjectName(QString::fromUtf8("groupStartingPos"));
    m_ptrMainLayout->addWidget(groupStartingPos);
    //////////////////////////////////////////////////////////////////////////
    gStartPosLayout = new QGridLayout();
    gStartPosLayout->setSpacing(6);
    gStartPosLayout->setMargin(2);
    gStartPosLayout->setObjectName(QString::fromUtf8("gStartPosLayout"));
    groupStartingPos->setLayout(gStartPosLayout );
    //////////////////////////////////////////////////////////////////////////
    labelStartX = new QLabel(groupStartingPos);
    labelStartX->setObjectName(QString::fromUtf8("labelSTartX"));
    //	QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    //	sizePolicy.setHorizontalStretch(2);
    //	sizePolicy.setVerticalStretch(0);
    //	sizePolicy.setHeightForWidth(labelRepeatQuantity->sizePolicy().hasHeightForWidth());
    //labelStartX->setSizePolicy(sizePolicy);

    gStartPosLayout->addWidget(labelStartX,0,0,1,1);
    //////////////////////////////////////////////////////////////////////////
    spinStartX = new QSpinBox(groupStartingPos);
    spinStartX->setObjectName(QString::fromUtf8("spinStartX"));
    spinStartX->setMinimum(1);
    spinStartX->setMinimumSize(QSize(41,20));

    gStartPosLayout->addWidget(spinStartX,1,0,1,1);
    //////////////////////////////////////////////////////////////////////////
    labelStartY = new QLabel(groupStartingPos);
    labelStartY->setObjectName(QString::fromUtf8("labelStartY"));
    //QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    //sizePolicy1.setHorizontalStretch(2);
    //sizePolicy1.setVerticalStretch(0);
    //sizePolicy1.setHeightForWidth(labelRepeatQuantity->sizePolicy().hasHeightForWidth());
    //labelStartY->setSizePolicy(sizePolicy1);

    gStartPosLayout->addWidget(labelStartY,0,1,1,1);
    //////////////////////////////////////////////////////////////////////////
    spinStartY = new QSpinBox(groupStartingPos);
    spinStartY->setObjectName(QString::fromUtf8("spinStartY"));
    spinStartY->setMinimum(1);
    spinStartY->setMinimumSize(QSize(41,20));

    gStartPosLayout->addWidget(spinStartY,1,1,1,1);
    //////////////////////////////////////////////////////////////////////////
    labelStartDir = new QLabel(groupStartingPos);
    labelStartDir->setObjectName(QString::fromUtf8("labelStartDir"));
    QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    sizePolicy2.setHorizontalStretch(2);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(labelStartDir->sizePolicy().hasHeightForWidth());
    labelStartDir->setSizePolicy(sizePolicy2);
    gStartPosLayout->addWidget(labelStartDir,0,2,1,1);
    //////////////////////////////////////////////////////////////////////////
    comboStartDir = new QComboBox(groupStartingPos);
    comboStartDir->setObjectName(QString::fromUtf8("comboStartDir"));
	comboStartDir->addItem(QIcon(":/images/north.png"),tr("North"), ROBOT_NORTH_DIR);
	comboStartDir->addItem(QIcon(":/images/west.png"),tr("West"), ROBOT_WEST_DIR);
	comboStartDir->addItem(QIcon(":/images/east.png"),tr("East"), ROBOT_EAST_DIR);
	comboStartDir->addItem(QIcon(":/images/south.png"),tr("South"), ROBOT_SOUTH_DIR);

    comboStartDir->setMinimumSize(QSize(53,20));
    gStartPosLayout->addWidget(comboStartDir,1,2,1,1);
}
void CExperimentPositionsParamsDlg::setupFinishPos()
{
    groupFinishPos = new QGroupBox(this);
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
    tableViewFinishPos->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    hFinishPosLayout->addWidget(tableViewFinishPos);

    modelFinishPos = new QStandardItemModel(1,2);

    tableViewFinishPos->setModel(modelFinishPos);
    tableViewFinishPos->setColumnWidth(0,50);
    tableViewFinishPos->setColumnWidth(1,50);
    tableViewFinishPos->resizeRowsToContents();
    //ustawiamy dane w stosownych kom�rkach
    QModelIndex index = modelFinishPos->index(0, 0, QModelIndex());
    modelFinishPos->setData(index, QVariant(10));

    index = modelFinishPos->index(0, 1, QModelIndex());
    modelFinishPos->setData(index, QVariant(10));

    modelFinishPos->setHeaderData(0,Qt::Horizontal,QVariant("X"),Qt::DisplayRole);
    modelFinishPos->setHeaderData(1,Qt::Horizontal,QVariant("Y"),Qt::DisplayRole);
    //********************************************************************//
    hAddRemoveButtonsLayout = new QHBoxLayout ();
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
void CExperimentPositionsParamsDlg::retranslateUI()
{
	labelRepeatQuantity->setText(QApplication::translate("param_eks", "Ilość powtórzeń", 0, QApplication::UnicodeUTF8));
	//labelRepeatQuantity->setText(QApplication::translate("param_eks", "Ilość powtórzeń", 0, QApplication::CodecForTr));
    groupStartingPos->setTitle(QApplication::translate("param_eks", "Pozycja startowa", 0, QApplication::CodecForTr));
    labelStartX->setText(QApplication::translate("param_eks", "X", 0, QApplication::CodecForTr));
    labelStartY->setText(QApplication::translate("param_eks", "Y", 0, QApplication::CodecForTr));
    labelStartDir->setText(QApplication::translate("param_eks", "Kierunek", 0, QApplication::CodecForTr));
    groupFinishPos->setTitle(QApplication::translate("param_eks", "Pozycje końcowe", 0, QApplication::UnicodeUTF8));
}
void CExperimentPositionsParamsDlg::setConnections()
{
    bool bResult=connect(spinStartX,SIGNAL(valueChanged(int)),SLOT(onInternalStartPosChange( )));
    Q_ASSERT(bResult==true);
    bResult=connect(spinStartY,SIGNAL(valueChanged(int)),SLOT(onInternalStartPosChange( )));
    Q_ASSERT(bResult==true);
    bResult=connect(modelFinishPos,SIGNAL(itemChanged(QStandardItem * )),SLOT(onInternalFinishPostionChanged(QStandardItem *)));
    Q_ASSERT(bResult==true);
	bResult=connect(comboStartDir,SIGNAL(highlighted(int)),SLOT(onInternalDirectionChanged(int)));
	Q_ASSERT(bResult==true);
	bResult=connect(comboStartDir,SIGNAL(currentIndexChanged(int)),SLOT(onInternalDirectionChanged(int)));
	Q_ASSERT(bResult==true);

    bResult=connect(addFinishPos,SIGNAL(clicked ( bool)),SLOT(onButtonAddFinishPos()));
    Q_ASSERT(bResult==true);
    bResult=connect(removeFinishPos,SIGNAL(clicked ( bool)),SLOT(onButtonRemFinishPos()));
    Q_ASSERT(bResult==true);
}
//////////////////////////////////////////////////////////////////////////
void CExperimentPositionsParamsDlg::setExperimentSettings(CExperimentSettings & cExperimentSettings)
{
	spinStartX->blockSignals(true);
	spinStartY->blockSignals(true);

	spinStartX->setValue(cExperimentSettings.startPosition.posX);
	spinStartY->setValue(cExperimentSettings.startPosition.posY);

	std::list<QPoint>::const_iterator iterFinishPos = cExperimentSettings.lFinishPositions.begin();
	modelFinishPos->setRowCount(cExperimentSettings.lFinishPositions.size());
	for(int i=0; i<modelFinishPos->rowCount(); i++)
	{
		QModelIndex index = modelFinishPos->index(i, 0);
		modelFinishPos->setData(index, iterFinishPos->x());
		index = modelFinishPos->index(i, 1);
		modelFinishPos->setData(index, iterFinishPos->y());
	}

	spinStartX->blockSignals(false);
	spinStartY->blockSignals(false);
}
void CExperimentPositionsParamsDlg::getExperimentSettings(CExperimentSettings & cExperimentSettings)
{
	QModelIndex index;
	QPoint pos;
	int rowCount = modelFinishPos->rowCount();
	cExperimentSettings.repeatingQuantity = spinRepeatQuantity->value();
	cExperimentSettings.startPosition.posX=spinStartX->value();
	cExperimentSettings.startPosition.posY=spinStartY->value();
	cExperimentSettings.lFinishPositions.clear();
	for(int i =0; i<rowCount; i++)
	{
		index = modelFinishPos->index(i, 0, QModelIndex());
		pos.setX(modelFinishPos->data(index).toInt());
		index = modelFinishPos->index(i, 1, QModelIndex());
		pos.setY(modelFinishPos->data(index).toInt());
		cExperimentSettings.lFinishPositions.push_back(pos);
	}
	QString text = comboStartDir->itemText(m_iDirSelected);

	cExperimentSettings.startPosition.dir =
		(text == "North") ? ROBOT_NORTH_DIR :
		(text == "West") ? ROBOT_WEST_DIR :
		(text == "South") ? ROBOT_SOUTH_DIR : ROBOT_EAST_DIR;
}
//////////////////////////////////////////////////////////////////////////
void CExperimentPositionsParamsDlg::onInternalStartPosChange()
{
    int X = spinStartX->value();
    int Y = spinStartY->value();
    emit setStartPosition(X,Y);
}
void CExperimentPositionsParamsDlg::onInternalFinishPostionChanged(QStandardItem *)
{
	vector< pair< int, int> > vPositionsList;
	bool bResult;
	bResult=true;
	for(int i=0; i<modelFinishPos->rowCount(); i++)
	{
		pair<int, int> pozycja;
		QModelIndex index = modelFinishPos->index(i, 0, QModelIndex());
		pozycja.first=modelFinishPos->data(index).toInt();

		index = modelFinishPos->index(i, 1, QModelIndex());
		pozycja.second=modelFinishPos->data(index).toInt();
		vPositionsList.push_back(pozycja);
	}
	emit setFinishPositions(vPositionsList);
}
void CExperimentPositionsParamsDlg::onInternalDirectionChanged(int iIndex)
{
	m_iDirSelected = comboStartDir->itemData(iIndex).toInt();
	//QString strInfo = QString ("robot start direction selected: %1").arg(m_iDirSelected);
	//Log4Qt::Logger::logger("Process")->info(strInfo);
	emit setStartDirection(m_iDirSelected);
}
//////////////////////////////////////////////////////////////////////////
void CExperimentPositionsParamsDlg::onNewStartPosition(int posX,int posY)
{
    blockSignals(true);

    spinStartX->blockSignals(true);
    if (spinStartX->maximum()<posX)
        spinStartX->setMaximum(posX);
    spinStartX->setValue(posX);
    spinStartX->blockSignals(false);

    spinStartY->blockSignals(true);
    if (spinStartY->maximum()<posY)
        spinStartY->setMaximum(posY);
    spinStartY->setValue(posY);
    spinStartX->blockSignals(false);

    blockSignals(false);
}
void CExperimentPositionsParamsDlg::onNewFinishPosition(int posX,int posY)
{
    //to ma prawo zaistniec tylko jesli labirynt ma miec jedno wyjscie
    //czyli czyscimy tablice z wszystkich wpis�w poza tym jednym
    blockSignals(true);

    int rowCount = modelFinishPos->rowCount();
    modelFinishPos->removeRows(1,rowCount-1);

    rowCount = modelFinishPos->rowCount();

    QModelIndex index = modelFinishPos->index(0, 0, QModelIndex());
    modelFinishPos->setData(index, QVariant(posX));

    index = modelFinishPos->index(0, 1, QModelIndex());
    modelFinishPos->setData(index, QVariant(posY));
    blockSignals(false);
	tableViewFinishPos->resizeRowsToContents();
}
void CExperimentPositionsParamsDlg::onAddFinishPosition(int posX,int posY)
{
	int rowCount = modelFinishPos->rowCount();
	if (rowCount>=maxFinishPos)	return;
    blockSignals(true);
    modelFinishPos->insertRow(rowCount);

    QModelIndex index = modelFinishPos->index(rowCount, 0, QModelIndex());
    modelFinishPos->setData(index, QVariant(posX));

    index = modelFinishPos->index(rowCount, 1, QModelIndex());
    modelFinishPos->setData(index, QVariant(posY));
    blockSignals(false);
	tableViewFinishPos->resizeRowsToContents();
}
//////////////////////////////////////////////////////////////////////////
//void CExperimentPositionsParamsDlg::onMazeSizeChange(int iX,int iY)
//{
//    spinStartX->setMaximum(iX);
//    spinStartY->setMaximum(iY);
//    emit setStartPosition(spinStartX->value(),spinStartY->value());
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
void CExperimentPositionsParamsDlg::onButtonAddFinishPos()
{
    int count = modelFinishPos->rowCount();
    //QStandardItem * item = new QStandardItem();
    if (count>=maxFinishPos-1)
        addFinishPos->setEnabled(false);
    if (count==maxFinishPos)	
	{
		addFinishPos->setEnabled(false);
		return;
	}
    removeFinishPos->setEnabled(true);

	QList<QStandardItem *> lItems;
	QStandardItem * pItem = new QStandardItem;
	pItem->setData(2, Qt::DisplayRole);
	lItems.push_back(pItem);
	pItem = new QStandardItem;
	pItem->setData(2, Qt::DisplayRole);
	lItems.push_back(pItem);

	modelFinishPos->insertRow(count,lItems);
	tableViewFinishPos->resizeRowsToContents();
    onInternalFinishPostionChanged(NULL);
}
void CExperimentPositionsParamsDlg::onButtonRemFinishPos()
{
    vector<int>	vRows;
    int count = modelFinishPos->rowCount();
    int iRow;
    if (count==2)
        removeFinishPos->setEnabled(false);
    if (count==1)
        return;
    addFinishPos->setEnabled(true);
    //sprawdz jaki element jest zaznaczony
    QItemSelectionModel * selectModel = tableViewFinishPos->selectionModel();
    for (int i = count-1; i >= 0; --i )
    {
        QModelIndex index = modelFinishPos->index(i, 0);
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
    modelFinishPos->removeRow(iRow);
    onInternalFinishPostionChanged(NULL);
	tableViewFinishPos->resizeRowsToContents();
}
void CExperimentPositionsParamsDlg::onMazeGeneration(CMazeSettings & xMazeSettings)
{
	if (false == isEnabled())
		setEnabled(true);
	spinStartX->setMaximum(xMazeSettings.uiMaxX);
	spinStartY->setMaximum(xMazeSettings.uiMaxY);
	PositionItemEditor::sIntMax=xMazeSettings.uiMaxX;
	//emit setStartPosition(spinStartX->value(),spinStartY->value());
}