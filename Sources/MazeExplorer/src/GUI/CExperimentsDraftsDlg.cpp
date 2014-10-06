#include "CExperimentsDraftsDlg.h"
#include <math.h>
/*
CExperimentsDraftsDlg::CExperimentsDraftsDlg(void) : QWidget(NULL)
{
    setup_ui();
    connect(this,SIGNAL(emitDataForDraft(QVector<float> &)),widgetResultDraft,SLOT(slotDataForDraft(QVector<float> &)));
    pExperiment=NULL;
}
CExperimentsDraftsDlg::~CExperimentsDraftsDlg(void)
{
}
void CExperimentsDraftsDlg::connecting()
{
    bool bResult=false;
//	bResult=connect(treeExplorationResults,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(slotTreeItemClicked(QTreeWidgetItem *, int)));
//	Q_ASSERT(bResult==TRUE);
    bResult=connect(treeExplorationResults,SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *) ),this,SLOT(slotTreeItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));
    Q_ASSERT(bResult==TRUE);
}
void CExperimentsDraftsDlg::setup_ui()
{
    setObjectName(QString::fromUtf8("ExperimentResultDraftDialog"));
    resize(QSize(651, 378).expandedTo(minimumSizeHint()));
    setWindowTitle(QApplication::translate("ExperimentResultDraftDialog", "Efekty eksploracji", 0, QApplication::UnicodeUTF8));

    gridWindowLayout = new QGridLayout;
    gridWindowLayout->setObjectName(QString::fromUtf8("gridWindowLayout"));
    setLayout(gridWindowLayout);

    setup_uiToolBoxPages();
    //tutaj musimy skorzystać z TabWidgeta
    tabDialog = new QTabWidget;
    gridWindowLayout->addWidget(tabDialog,0,1,1,1);
    QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, static_cast<QSizePolicy::Policy>(5));
    sizePolicy2.setHorizontalStretch(4);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(tabDialog->sizePolicy().hasHeightForWidth());
    tabDialog->setSizePolicy(sizePolicy2);

    widgetResultDraft = new CExperimentResultDraft(this);
    widgetResultDraft->setObjectName(QString::fromUtf8("widgetResultDraft"));
    tabDialog->addTab(widgetResultDraft,"Wykres");

    ///
    widgetScrollKBDraw = new QScrollArea(this);
    tabDialog->addTab(widgetScrollKBDraw,"Baza wiedzy");

    //widgetKBDraw = new CExperimentsKBGraph();
    //widgetKBDraw->setObjectName(QString::fromUtf8("widgetKBDraw"));
    //widgetScrollKBDraw->setWidget(widgetKBDraw);
    //widgetScrollKBDraw->setWidgetResizable(true);

    connecting();
}
void CExperimentsDraftsDlg::setKnowlegdeBase(CMazeKnowlegdeBase * ptKB)
{
    pKB = ptKB;
    setup_uiFillKnowlegdeBaseData();
    QTreeWidgetItem			*	parentItem;

    parentItem = treeExplorationResults->itemAt(2,2);
    if (parentItem==NULL)
        return;

    slotTreeItemClicked(parentItem, 0);
}
void CExperimentsDraftsDlg::setup_uiToolBoxPages()
{
    toolBox = new QToolBox(this);
    toolBox->setObjectName(QString::fromUtf8("toolBoox"));
    gridWindowLayout->addWidget(toolBox,0,0,1,1);
    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, static_cast<QSizePolicy::Policy>(5));
    sizePolicy1.setHorizontalStretch(1);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(toolBox->sizePolicy().hasHeightForWidth());
    toolBox->setSizePolicy(sizePolicy1);

    treeExplorationResults = new QTreeWidget();
    treeExplorationResults->setObjectName(QString::fromUtf8("treeExplorationResults"));
    toolBox->addItem(treeExplorationResults, QApplication::translate("ExperimentResultDraftDialog", "Lista eksploracji", 0, QApplication::UnicodeUTF8));
    treeExplorationResults->setColumnCount(2);
    treeExplorationResults->setRootIsDecorated(true);


    widgetPage1=new QWidget();
    widgetPage1->setObjectName(QString::fromUtf8("widgetPage1"));
    toolBox->addItem(widgetPage1, QApplication::translate("ExperimentResultDraftDialog", "Statystyki", 0, QApplication::UnicodeUTF8));

    gridStatLayout = new QGridLayout;
    gridStatLayout->setObjectName(QString::fromUtf8("gridStatLayout"));
    widgetPage1->setLayout(gridStatLayout);

    //////////////////////////////////////////////////////////////////////////
    labelFails = new QLabel(widgetPage1);
    labelFails->setObjectName(QString::fromUtf8("labelFails"));
    labelFails->setText(QApplication::translate("ExperimentResultDraftDialog", "Porazki", 0, QApplication::UnicodeUTF8));
    //	QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    //	sizePolicy.setHorizontalStretch(2);
    //	sizePolicy.setVerticalStretch(0);
    //	sizePolicy.setHeightForWidth(labelRepeatQuantity->sizePolicy().hasHeightForWidth());
    //labelStartX->setSizePolicy(sizePolicy);
    gridStatLayout->addWidget(labelFails,0,0,1,1);

    lineEditFails = new QLineEdit(widgetPage1);
    lineEditFails->setObjectName(QString::fromUtf8("lineEditFails"));
    lineEditFails->setReadOnly(true);
    gridStatLayout->addWidget(lineEditFails,0,1,1,1);
    //////////////////////////////////////////////////////////////////////////
    labelSucces = new QLabel(widgetPage1);
    labelSucces->setObjectName(QString::fromUtf8("labelSucces"));
    labelSucces->setText(QApplication::translate("ExperimentResultDraftDialog", "Sukcesy", 0, QApplication::UnicodeUTF8));
    //	QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    //	sizePolicy.setHorizontalStretch(2);
    //	sizePolicy.setVerticalStretch(0);
    //	sizePolicy.setHeightForWidth(labelRepeatQuantity->sizePolicy().hasHeightForWidth());
    //labelStartX->setSizePolicy(sizePolicy);
    gridStatLayout->addWidget(labelSucces,1,0,1,1);

    lineEditSucces = new QLineEdit(widgetPage1);
    lineEditSucces->setObjectName(QString::fromUtf8("lineEditFails"));
    lineEditSucces->setReadOnly(true);
    gridStatLayout->addWidget(lineEditSucces,1,1,1,1);
}
void CExperimentsDraftsDlg::calculateDraftValues(CExperiment &exp)
{
    QVector<bool>				dataForAvarge;
    CMazeExplorationResult			expResult;

    int count = exp.getExplorationsCount();
    double loga = floor(log((double)count));
    unsigned int statisticRange=0;
    if (count<1)
        statisticRange=1;
    else
    {
        statisticRange=floor((double)count/loga)/2;
    }
    qDebug()<<"Locations count "<<count<<" / "<<statisticRange<<"\nLog(count) count "<<loga;

    dataForDraft.clear();
    dataForAvarge.clear();
    float fAvarge;

    int counterForAvarge=0;
    if (statisticRange==0)
        return;
    qDebug()<<"Explorations Successes\n";

    for(int index=0; index<count; index++)
    {
        exp.getExplorationResult(index,expResult);
        if (expResult.bExplorationSuccessful)
            dataForAvarge.push_back(true);
        else
            dataForAvarge.push_back(false);
        counterForAvarge++;
        if (counterForAvarge>statisticRange)
            dataForAvarge.pop_front();
        //obliczamy teraz srednia na podstawie dataForAvarge
        {
            unsigned int sucess=0,fails=0;
            QVector<bool>::iterator iter;

            for(iter=dataForAvarge.begin(); iter!=dataForAvarge.end(); iter++)
            {
                if (*iter==true)
                    sucess++;
                else
                    fails++;
            }
            //			if (counterForAvarge>statisticRange)
            fAvarge=(float)sucess/(float)statisticRange;
            //			else
            //				fAvarge=(float)sucess/(float)counterForAvarge;
        }
        if (expResult.bExplorationSuccessful)
            qDebug()<<"Exploration nr "<<index<<"SUCCESS   "<<fAvarge;
        else
            qDebug()<<"Exploration nr "<<index<<"FAILED    "<<fAvarge;
        dataForDraft.push_back(fAvarge);
    }
    qDebug()<<"\n";
    emit emitDataForDraft(dataForDraft);
}

void CExperimentsDraftsDlg::fillItemExplorationPath(QTreeWidgetItem * parentItemPath,QTreeWidgetItem * parentItemCrossroadPath,CExplorationResult &expResult)
{
    QTreeWidgetItem			*	item;
    QStringList					strList;
    CScanResults				scanResult;
    int count=expResult.getPositionsCount();

    for(int i=0; i<count; i++)
    {
        expResult.getRobotPosition(i,scanResult);

        strList.clear();
        strList<<QString("(%1,%2)").arg(scanResult.robotPos.posX).arg(scanResult.robotPos.posY);
        switch(scanResult.robotPos.dir)
        {
        case ROBOT_NORTH_DIR:
            strList<<"NORTH";
            break;
        case ROBOT_WEST_DIR:
            strList<<"WEST";
            break;
        case ROBOT_EAST_DIR:
            strList<<"EAST";
            break;
        case ROBOT_SOUTH_DIR:
            strList<<"SOUTH";
            break;
        }
        item = new QTreeWidgetItem(parentItemPath,strList);
        if(scanResult.getExitsCount(SCAN_BACK_DIR)>1)
        {
            item = new QTreeWidgetItem(parentItemCrossroadPath,strList);
        }
    }
}
void CExperimentsDraftsDlg::fillItemExplorationData(QTreeWidgetItem * parentItem,CExplorationResult &expResult)
{
    QTreeWidgetItem			*	item;
    QTreeWidgetItem			*	item1;
    QStringList	strList;

    //////////////////////////////////////////////////////////////////////////
    //dodajemy informacje o danej eksploracji

    //ilosc lokacji
    strList<<"Ilosc lokacji";
    strList<<QString("%1").arg(expResult.getPositionsCount());
    item = new QTreeWidgetItem(parentItem,strList);

    strList.clear();
    strList<<"Ilosc skrzy�owa�";
    strList<<QString("%1").arg(expResult.getCrossRoadsCount());
    item = new QTreeWidgetItem(parentItem,strList);

    strList.clear();
    strList<<PATH_TEXT;
    strList<<QString("");
    item = new QTreeWidgetItem(parentItem,strList);

    strList.clear();
    strList<<CROSS_TEXT;
    strList<<QString("");
    item1 = new QTreeWidgetItem(parentItem,strList);
    fillItemExplorationPath(item,item1,expResult);

    
    //DialogNode *pNode1 = NULL;
    //bool		bFirst=false;
    //QString			strToolTip;
    //vector<DialogNode>::iterator PhasIter;
    //QString			strToolTip;
    //vector<DialogNode>::iterator PhasIter;
    //for(PhasIter=Dialog.vPhases.begin();PhasIter!=Dialog.vPhases.end();PhasIter++)
    //{
    //pNode1 = &*PhasIter;
    //item = new QTreeWidgetItem(PhasesList);
    //item->setText(0, QString("%1").arg(pNode1->nodeID));
    //item->setText(1, pNode1->MobText);
    //strToolTip = prepareNodeToolTip(pNode1);
    //item->setToolTip(0,strToolTip);
    //item->setToolTip(1,strToolTip);
    //if (!bFirst)
    //{
    //PhasesList->setCurrentItem(item);
    //iPhaseNr=0;
    //bFirst=true;
    //}
    //}
    //PhasesList->resizeColumnToContents(0);
    //PhasesList->resizeColumnToContents(1);
    //editDialogName->setText(Dialog.name); 
}
void CExperimentsDraftsDlg::fillTableWithExperimentData(CExperiment &exp)
{
    QTreeWidgetItem			*	item;
    CExplorationResult			expResult;
    QString						strText;
    QStringList					strList;
    int count = exp.getExplorationsCount();
    treeExplorationResults->clear();

    for(int index=0; index<count; index++)
    {
        strList.clear();
        exp.getExplorationResult(index,expResult);
        strList<<QString("%1 %2").arg(EXPLORATION_TITLE ).arg(index+1);
        if (expResult.bExplorationSuccessful)
            strList<<"SUKCES";
        else
            strList<<"PORAZKA";
        item = new QTreeWidgetItem(treeExplorationResults,strList);

        item->setText(0, QString("%1 %2").arg(EXPLORATION_TITLE).arg(index+1));
        fillItemExplorationData(item,expResult);

        //////////////////////////////////////////////////////////////////////////

    }
    treeExplorationResults->resizeColumnToContents(0);
    treeExplorationResults->resizeColumnToContents(1);
}
void CExperimentsDraftsDlg::setup_uiFillKnowlegdeBaseData()
{
    QString test;

    pExperiment=pKB->getCurrentExperiment();

    calculateDraftValues(*pExperiment);
    fillTableWithExperimentData(*pExperiment);

    //////////////////////////////////////////////////////////////////////////
    lineEditFails->setText(QString("%1").arg(pExperiment->getFailsCounter()));
    lineEditSucces->setText(QString("%1").arg(pExperiment->getSuccessCounter()));
    test = lineEditFails->text();
    test = 	lineEditSucces->text();
}
void CExperimentsDraftsDlg::prepareExplorationRouteToSend(int expNr)
{
    CExperiment				exp;
    CExplorationResult		expResult;
    pKB->getCurrentExperiment(exp);
    exp.getExplorationResult(expNr,expResult);
    emit emitShowRobotRoute(expResult);
}
//
void CExperimentsDraftsDlg::showKBData( int expNr,int posX, int posY )
{
    vector<CScanResults> crossRoadsList;
    vector<CScanResults>::iterator iterCross;
    CExplorationResult expResult;
    pExperiment->getExplorationResult(expNr,expResult);
    expResult.prepareCrossRoadsList(crossRoadsList);
    //przechodzimy cala sprawdzamy kt�re skrzy�owanie wybrano
    int count = crossRoadsList.size();
    for(iterCross=crossRoadsList.begin(); iterCross!=crossRoadsList.end(); iterCross++)
    {
        CScanResults scanResult;
        if (iterCross->robotPos.posX==posX && iterCross->robotPos.posY==posY)
        {
            CKBTreeNode	* ptNode=NULL;
            crossRoadsList.erase(++iterCross,crossRoadsList.end());
            count = crossRoadsList.size();
            ptNode=pKB->getKBTreeData(expNr,crossRoadsList);
            if (ptNode==NULL)
                return;
            //mamy potwierdzenie ze ta lokacja wystepuje
            //widgetKBDraw->setNode(ptNode);
            break;
        }
    }
}
//////////////////////////////////////////////////////////////////////////
void CExperimentsDraftsDlg::setLocationSelected(int , int )
{ }
void CExperimentsDraftsDlg::slotTreeItemClicked(QTreeWidgetItem *itemClicked, int )
{
    QTreeWidgetItem			*	parentItem;
    QTreeWidgetItem			*	childItem,*	processItem;
    QString	strParentText, strText;
    int posX, posY,expNr ;
//	std::string strTT;

    //sprawdzamy kto jest rodzicem tego elementu
    if (itemClicked==NULL) return;

    // ******************************************
    parentItem = itemClicked->parent();
    processItem = itemClicked;
    //szukamy numeru z tekstu 'Eksploracja nr'
    if (parentItem!=NULL)
    {
        strParentText = parentItem->text(0);
        processItem = parentItem;
        while(processItem->parent()!=NULL)
        {
            processItem = processItem->parent();
        }
    }
    strText = processItem->text(0); //pobieramy tekst 'Eksploracja nr xx'
    QStringList strList = strText.split(" "); //dzielimy na czastki
    expNr = strList.back().toInt(); //ostatnia czastka to numer ekspl
    //TODO potrzeba nam wybrać właściwe drzewo KB

    // ******************************************
    // potrzebujemy numeru kolejnego kroku/skrzyzowania - szukamy
    processItem = itemClicked;
    //skoro nie kliknelismy nigdzie w galezi sciezka lub skrzyzowania
    if (strParentText!=PATH_TEXT && strParentText!=CROSS_TEXT)
    {
        bool bFound = false;
        do
        {
            //przejrzyj galezie w poszukiwaniu 'Skrzyzowania'
            for(int i =0; i<processItem->childCount(); i++)
            {
                childItem = processItem->child(i);
                Q_ASSERT(childItem!=NULL);
                strText=childItem->text(0);
                if (strText==CROSS_TEXT)
                {
                    bFound=true;
                    processItem = childItem;
                    break;
                }
            }
            if (bFound==false)
            {
                //jeśli nie znalazl - wyjdz na wyzszy poziom
                processItem = processItem->parent();
            }
        }
        while(bFound ==false);
        //tutaj processItem ma wskazywac na pierwszy element CROSS_TEXT
        processItem = processItem->child(0);
    }
    if (processItem==NULL)
        return;
    strText=processItem->text(0); // pobieramy wspolrzedne
    strText.remove(QChar('(')).remove(QChar(')'));
    strList = strText.split(",");
    posX = strList.front().toInt();
    posY = strList.back().toInt();

    if (strParentText==PATH_TEXT || strParentText==CROSS_TEXT)
        emit emitLocationSelected(posX,posY);

    prepareExplorationRouteToSend(expNr-1);
    showKBData(expNr-1,posX,posY);
}
void CExperimentsDraftsDlg::slotTreeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem * previous)
{
    slotTreeItemClicked(current, 1);
}
*/