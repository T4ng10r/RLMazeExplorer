#include "CExperimentsKBGraph.h"
#include <Data/CMazeKnowlegdeBase.h>

/*
CExperimentsKBGraph::CExperimentsKBGraph(QWidget *parent) : QWidget(parent)
    ,ptRootNode(NULL),bSingleNode(false),font("Arial",8),fontMetric(font)
{
    iSidesTextWidth=fontMetric.width("99%")+3;
    prepareLocationToDraw();
    //fontMetric=QFontMetrics(font);
}

CExperimentsKBGraph::~CExperimentsKBGraph(void)
{
}
void CExperimentsKBGraph::setExplorationNodes(CKBTreeNode	* ptNode)
{
}
void CExperimentsKBGraph::setNode(CKBTreeNode	* ptNode)
{
    ptRootNode = ptNode;
    bSingleNode=true;
    update();
}
void CExperimentsKBGraph::prepareLocationToDraw()
{
    QBrush		brush(Qt::lightGray);
    QPen	    pen;
    QPainter	painter;
    QRect	    rectToDraw;

    painter.begin(&locationBasePicture);           // paint in picture
    //kolor t³a

    rectToDraw.setSize(sizeTreeLocation);
    painter.fillRect(rectToDraw,brush);

    pen.setColor(Qt::gray);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(rectToDraw.topLeft(),rectToDraw.topRight());
    painter.drawLine(rectToDraw.topLeft(),rectToDraw.bottomLeft());

    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawLine(rectToDraw.topRight(),rectToDraw.bottomRight());
    painter.drawLine(rectToDraw.bottomRight(),rectToDraw.bottomLeft());

    painter.end();                     // painting done
    locationBasePicture.save("location.pic");
}
//QPicture & CExperimentsKBGraph::fillLocationWithNodeData(CKBTreeNode * ptNode)
void CExperimentsKBGraph::fillLocationWithNodeData(QPicture &picture, CKBTreeNode * ptNode)
{
    map<directions, float>	mDirsProbs;
    map<directions, float>::iterator IterMDirs;
    vector<LocationDirs>	vDirs;
    vector<double>		vProbabilities;
    vector<LocationDirs>::iterator	iterDirs;
    vector<double>::iterator	iterProb;
    int xMid, yMid;

    //QPicture picture;

    //QBrush		brush(Qt::yellow);
    QBrush		    brush(Qt::lightGray);
    QPainter	    painter;

    QRect   qTopRect,qLeftRect,qRightRect,rectToDraw;
    QString strLeftProb,strRightProb,strTopProb;
    QPen	penWall,penPassage, pen;
    bool bLeft(FALSE),bRight(FALSE),bTop(FALSE);
    qTopRect.setSize(sizeText);

    //////////////////////////////////////////////////////////////////////
    penWall.setColor(Qt::darkYellow);
    //penWall.setWidth(1);

    penPassage.setStyle(Qt::DotLine);

    rectToDraw.setSize(sizeTreeLocation);
    font.setPixelSize(10);
    {
        ptNode->getDirections(mDirsProbs);
        if (mDirsProbs.size()==0) return;
        xMid = (sizeTreeLocation.width()/2)-(sizeText.width()/2);
        yMid = (sizeTreeLocation.height()/2)-(sizeText.height()/2);
        for(IterMDirs=mDirsProbs.begin();
                IterMDirs!=mDirsProbs.end();
                IterMDirs++)
        {
            directions dir = IterMDirs->first;
            QString strProb(QString("%1%").arg((int)IterMDirs->second));
            switch(dir)
            {
            case FRONT_DIR:
                qTopRect.setSize(sizeText);
                qTopRect.moveTo(xMid,3);
                strTopProb = strProb;
                bTop=true;
                break;
            case LEFT_DIR:
                qLeftRect.setSize(sizeText);
                qLeftRect.moveTo(3,yMid);
                strLeftProb = strProb;
                bLeft=true;
                break;
            case RIGHT_DIR:
                qRightRect.setSize(sizeText);
                qRightRect.moveTo(locationBasePicture.width()-sizeText.width()-2,yMid);
                strRightProb = strProb;
                bRight=true;
                break;
            default:
                break;
            }
        }
    }
    //////////////////////////////////////////////////////////////////////
    painter.begin(&picture);
    painter.drawPicture(0,0,locationBasePicture);

    //////////////////////////////////////////////////////////////////////

    //szerokosc elementu do narysowania - dwukrotnosc dlugosci pola na tekst
    rectToDraw.setWidth(sizeTreeLocation.width()-8-iSidesTextWidth*2);
    rectToDraw.setHeight(sizeTreeLocation.height()-fontMetric.height()*2-8);

    int moveX,moveY;

    moveX=3+iSidesTextWidth;
    moveY=3+fontMetric.height();

    rectToDraw.moveTo(moveX,moveY);

    painter.setPen(bLeft?penPassage:penWall);
    painter.drawLine(rectToDraw.bottomLeft(),rectToDraw.topLeft());

    painter.setPen(bRight?penPassage:penWall);
    painter.drawLine(rectToDraw.bottomRight(),rectToDraw.topRight());

    painter.setPen(bTop?penPassage:penWall);
    painter.drawLine(rectToDraw.topLeft(),rectToDraw.topRight());

    if (qTopRect.isValid())
        painter.drawText(qTopRect,Qt::AlignCenter,strTopProb);
    if (qLeftRect.isValid())
        painter.drawText(qLeftRect,Qt::AlignCenter,strLeftProb);
    if (qRightRect.isValid())
        painter.drawText(qRightRect,Qt::AlignCenter,strRightProb);
    painter.end();
}
void CExperimentsKBGraph::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    //pobieramy obszar ktory jest do odmalowania (caly widget)
    QRect qEntireDrawArea	= event->rect();
    //obliczamy srodek na gorze ekranu - stad zaczniem rysowac drzewo
    QPoint ptMiddleTop = qEntireDrawArea.topLeft();
    ptMiddleTop.setX(
        qEntireDrawArea.left()+(qEntireDrawArea.width()/2)-sizeTreeLocation.width()/2);
    ptMiddleTop.ry()+=10;
    painter.begin(this);
    bFirst=false;

    painter.fillRect(event->rect(), QColor(Qt::white));
    if (ptRootNode!=NULL)
    {
        drawKBTreeNode(painter,qEntireDrawArea,ptRootNode,ptMiddleTop);

//	drawVisitedTreeLocation(painter,qEntireDrawArea,rootNode,ptMiddleTop);
//	drawExperimentResults(painter,qEntireDrawArea);
    }
    painter.end();
}
void CExperimentsKBGraph::drawKBTreeNode(QPainter &painter,
        QRect &qEntireDrawArea,
        CKBTreeNode * ptNode,
        QPoint ptMiddleTop)
{
    QPicture			locPicture;
    map<directions, float>	mDirsProbs;
    map<directions, float>::iterator IterMDirs;
    unsigned int iWidth;

    if (NULL == ptNode)
        return;

    fillLocationWithNodeData(locPicture,ptNode);

    painter.drawPicture(ptMiddleTop,locPicture);
    //rysujemy wezly wychodz¹ce z danego
    ptNode->getDirections(mDirsProbs);
    int iCount = mDirsProbs.size();
    //ustalamy jak wiele elementow mamy do dodania
    //czyli jak szeroko trzeba bedzie ustawiac elementy
    iWidth = (iCount*sizeTreeLocation.width())+(iCount-1)*(sizeTreeLocation.width()/2);
    QPoint ptNewMidTop(ptMiddleTop);
    ptNewMidTop.setX(ptNewMidTop.x()-iWidth/2+(sizeTreeLocation.width()/2));
    ptNewMidTop.setY(ptNewMidTop.y()+sizeTreeLocation.height()*1.5);
    //
    for(IterMDirs=mDirsProbs.begin();
            IterMDirs!=mDirsProbs.end();
            IterMDirs++)
    {
        CKBTreeNode * ptChildNode;
        //rysujemy powiazania z nowym elementem

        //rysujemy sam element
        ptChildNode = ptNode->getStateIDByAction(IterMDirs->first);
        if (ptChildNode==NULL)
            continue;
        fillLocationWithNodeData(locPicture,ptChildNode);
        painter.drawPicture(ptNewMidTop,locPicture);
        ptNewMidTop.setX(ptNewMidTop.x()+sizeTreeLocation.width()*1.5);
    }

    //painter.drawPicture(ptMiddleTop,locPicture);
    if (bSingleNode)
        return;
    //tutaj ustalamy polozenie kazdego z dostepnych do narysowania 	wezlow

}
*/