#include "CMazeDraw.h"
#include <Gui/MainWindow.h>

CMazeDraw::CMazeDraw(QWidget *parent) : QWidget(parent), iDirection(ROBOT_NORTH_DIR)
{
    reset();
    setMinimumSize(200, 200);
    setBackgroundRole(QPalette::Base);
    pen.setColor(Qt::blue);
    pen.setStyle((Qt::PenStyle)1);
    pen.setCapStyle((Qt::PenCapStyle)0);
    setMouseTracking(true);
    createContextMenu();
}
void CMazeDraw::reset()
{
    lRobotRoute.clear();
    sizeX=0;
    sizeY=0;
    scaleSizeX=0;
    scaleSizeY=0;
    m_iSelectedRobotPos_X=-1;
    m_iSelectedRobotPos_Y=-1;
}
void CMazeDraw::createContextMenu()
{
    actionSetStart = new QAction(tr("&Pozycja startowa"), this);
    actionSetStart->setStatusTip(tr("St�d agent rozpocznie swoj� w�dr�wk�"));
    connect(actionSetStart,SIGNAL(triggered()), this,SLOT(onMenuSetStartPosition( )));

    actionSetEnd = new QAction(tr("&Wyjscie z labiryntu"), this);
    actionSetEnd->setStatusTip(tr("Ustaw te pozycj�, jako wyj�cie z labiryntu"));
    connect(actionSetEnd,SIGNAL(triggered()), this,SLOT(onMenuSetFinishPosition( )));

    actionSetNextEnd = new QAction(tr("&Kolejne wyjscie ..."), this);
    actionSetNextEnd->setStatusTip(tr("Ustaw te pozycj�, jako wyj�cie z labiryntu"));
    connect(actionSetNextEnd,SIGNAL(triggered()), this,SLOT(onMenuSetNextFinishPosition( )));


    menuContextMaze = new QMenu(NULL);
    menuContextMaze->addAction(actionSetStart);
    menuContextMaze->addAction(actionSetEnd);
    menuContextMaze->addAction(actionSetNextEnd);
    //	menuContextMaze->addSeparator();
}
const QRect CMazeDraw::targetNormalRect(const QPoint &position)
{
    return QRect(position.x()/sizeX * sizeX, position.y()/sizeY * sizeY, sizeX, sizeY);
}
const QRect CMazeDraw::getNormalRect(int posX,int posY)
{
    return QRect(posX * sizeX, posY * sizeY, sizeX, sizeY);
}
const QRect CMazeDraw::getRouteRect(int posX,int posY)
{
    QRect rect = getNormalRect(posX,posY);
    return rect.adjusted(scaleSizeX,scaleSizeY,-scaleSizeX,-scaleSizeY);
}
const QRect CMazeDraw::getRobotRect(int posX,int posY)
{
    QRect rect = getRouteRect(posX,posY);
    return rect.adjusted(robotScaleSizeX,robotScaleSizeY,-robotScaleSizeX,-robotScaleSizeY);
}
void CMazeDraw::prepareLocationVars()
{
    unsigned int X=0,Y=0;
    unsigned int heig=0,wid=0;

    X =	pMaze->getXSize();
    Y =	pMaze->getYSize();
    heig = height()-2;
    wid = width()-2;

    sizeX = wid/X;
    sizeY = heig/Y;

    scaleSizeX = sizeY*0.15;
    scaleSizeY = sizeY*0.15;

    robotScaleSizeX = scaleSizeX*0.5;
    robotScaleSizeY = scaleSizeY*0.5;
}
//----------------------------------------------------------------//
void CMazeDraw::paintEvent(QPaintEvent *)
{
    QRect rect(0, 0, 10, 10);
    QPainter painter(this);
    unsigned int /*index=0,*/index1=0,index2=0;
    unsigned int X=0,Y=0;
    X =	pMaze->getXSize();
    Y =	pMaze->getYSize();
    prepareLocationVars();

    pen.setColor(Qt::blue);
    pen.setStyle((Qt::PenStyle)1);
    pen.setWidth(1);

    painter.setPen(pen);
    painter.setBrush(brush);

    for (index1 = 0; index1 < X; index1++)
        for (index2 = 0; index2 < Y; index2++)
        {
            rect = getNormalRect(index1,index2);
            CLocation location;
            pMaze->getLocation(QPoint(index1+1,index2+1),location);
            //DrawLocation(pMaze->getLocation(index1+1,index2+1), rect, &painter);
            DrawLocation(location, rect, &painter);
        }

    drawRobotLocations(painter);
    drawRobotRoute(painter);
}
void CMazeDraw::drawRobotRoute(QPainter &painter)
{
    //	unsigned int	m_iRobotPos_X=m_ptRobot_startPos.x();
    //	unsigned int	m_iRobotPos_Y=m_ptRobot_startPos.y();
    QRect rect(0, 0, 10, 10);
    CScanResults		scanResults;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    int count = lRobotRoute.getPositionsCount();

    for(int i=0; i<count; i++)
    {
        lRobotRoute.getRobotPosition(i,scanResults);
        rect = getRouteRect(scanResults.robotPos.posX-1,scanResults.robotPos.posY-1);
        if (scanResults.getExitsCount(false)>1)
            drawCrossRoad(painter,scanResults);
        else
            painter.drawRect(rect);
    }
    if (m_iSelectedRobotPos_X >=0)
    {
        pen.setColor(Qt::blue);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);

        painter.setPen(pen);
        rect = getRobotRect(m_iSelectedRobotPos_X-1,m_iSelectedRobotPos_Y-1);
        painter.drawRect(rect);
    }
}
void CMazeDraw::DrawLocation(const CLocation& location, QRect rect, QPainter *painter)
{
    if (location.up)
        painter->drawLine(rect.topLeft(),rect.topRight());
    if (location.right)
        painter->drawLine(rect.topRight(),rect.bottomRight());
    if (location.down)
        painter->drawLine(rect.bottomRight(),rect.bottomLeft());
    if (location.left)
        painter->drawLine(rect.bottomLeft(),rect.topLeft());
    //---//
    if (location.down && location.left)
        painter->drawPoint(rect.bottomLeft().x() ,rect.bottomLeft().y()-1);
    if (location.down && location.right)
        painter->drawPoint(rect.bottomRight().x() ,rect.bottomRight().y()+1);
    if (location.up && location.right)
        painter->drawPoint(rect.topRight().x(),rect.topRight().y()-1);
    if (location.up && location.left)
        painter->drawPoint(rect.topLeft().x(),rect.topLeft().y()+1);
}
void CMazeDraw::drawRobotLocations(QPainter &painter)
{
    QList<QPoint>::iterator	iterFinishPos;
    QRect rect;
    //starting position
    rect = getRobotRect(m_ptRobot_startPos.x(),m_ptRobot_startPos.y());
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawRect(rect);
    //dorzucamy tez ikone
    if (rect.height() >12 && rect.width()>12)
    {
        QIcon icon;
        switch(iDirection)
        {
        case ROBOT_NORTH_DIR:
            icon = QIcon(":/images/north.png");
            break;
        case ROBOT_SOUTH_DIR:
            icon = QIcon(":/images/south.png");
            break;
        case ROBOT_WEST_DIR:
            icon = QIcon(":/images/west.png");
            break;
        case ROBOT_EAST_DIR:
            icon = QIcon(":/images/east.png");
            break;
        default:
            break;
        }
        QPoint pos = rect.topLeft();
        pos+=QPoint(rect.width()/2,rect.height()/2);
        pos-=QPoint(cIconSize.width()/2,cIconSize.height()/2);
        QPixmap pixmap = icon.pixmap(cIconSize);
        painter.drawPixmap(pos, pixmap);
    }

    //draw all finish positions
    for(iterFinishPos=m_lFinishPos.begin(); iterFinishPos!=m_lFinishPos.end(); iterFinishPos++)
    {
        rect = getRobotRect(iterFinishPos->x(),iterFinishPos->y());
        pen.setColor(Qt::darkRed);
        pen.setWidth(2);
        pen.setStyle((Qt::PenStyle)2);
        painter.setPen(pen);

        painter.drawRect(rect);
    }
}
void CMazeDraw::drawCrossRoad(QPainter & painter,const CScanResults &scanResults)
{
    QRect rect;
    //starting position
    rect = getRobotRect(scanResults.robotPos.posX-1,scanResults.robotPos.posY-1);
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawRect(rect);
    //dorzucamy tez ikone
    if (rect.height() >12 && rect.width()>12)
    {
        QIcon icon;
        switch(scanResults.robotPos.dir)
        {
        case ROBOT_NORTH_DIR:
            icon = QIcon(":/images/north.png");
            break;
        case ROBOT_SOUTH_DIR:
            icon = QIcon(":/images/south.png");
            break;
        case ROBOT_WEST_DIR:
            icon = QIcon(":/images/west.png");
            break;
        case ROBOT_EAST_DIR:
            icon = QIcon(":/images/east.png");
            break;
        default:
            break;
        }
        QPoint pos = rect.topLeft();
        pos+=QPoint(rect.width()/2,rect.height()/2);
        pos-=QPoint(cIconSize.width()/2,cIconSize.height()/2);
        QPixmap pixmap = icon.pixmap(cIconSize);
        painter.drawPixmap(pos, pixmap);
    }
}
//----------------------------------------------------------------//
void CMazeDraw::mouseMoveEvent(QMouseEvent * event)
{
    CScanResults		scanResult;
    //	CRobotPostion		robotPos;
    int x,y;
    int count = lRobotRoute.getPositionsCount();
    m_iSelectedRobotPos_X=-1;
    m_iSelectedRobotPos_Y=-1;
    if (count)
    {
        x=event->x()/sizeX+1;
        y=event->y()/sizeY+1;
        //szukamy pozycji z trasy robota
        for(int index=0; index<count; index++)
        {
            lRobotRoute.getRobotPosition(index,scanResult);
            if (scanResult.robotPos.posX==x && scanResult.robotPos.posY == y)
            {
                emit SelectRoutePos(index);
                m_iSelectedRobotPos_X=scanResult.robotPos.posX;
                m_iSelectedRobotPos_Y=scanResult.robotPos.posY;
                break;
            }
        }
    }
    update();
}
void CMazeDraw::mousePressEvent(QMouseEvent *event)
{
    Qt::MouseButtons	Buttons = event->buttons();
    QPoint pos = event->pos();
    pos = QWidget::mapToGlobal ( pos  );
    if (Buttons & Qt::RightButton)
    {
        menuContextMaze->popup(pos);
    }
}
void CMazeDraw::mouseReleaseEvent(QMouseEvent* /*event*/)
{
}
//----------------------------------------------------------------//
void CMazeDraw::setStartPosition(int posX,int posY)
{
    m_ptRobot_startPos.setX(posX-1);
    m_ptRobot_startPos.setY(posY-1);
    emit clearRobotRoute();
    lRobotRoute.clear();
    update();
}
void CMazeDraw::setFinishPosition(int posX,int posY)
{
    QPoint	finishPos;
    finishPos.setX(posX-1);
    finishPos.setY(posY-1);
    m_lFinishPos.clear();
    m_lFinishPos.push_back(finishPos);
    emit clearRobotRoute();
    lRobotRoute.clear();
    update();
}
void CMazeDraw::setNewFinishPosition(int posX,int posY)
{
    QPoint	finishPos;
    finishPos.setX(posX-1);
    finishPos.setY(posY-1);
    m_lFinishPos.push_back(finishPos);
    emit clearRobotRoute();
    lRobotRoute.clear();
    update();
}
void CMazeDraw::onMenuSetStartPosition()
{
    unsigned int X=0,Y=0;

    QPoint pos = menuContextMaze->pos();
    pos = mapFromGlobal(pos);
    QRect rect = targetNormalRect(pos);
    Y = rect.top()/rect.height()+1;
    X = rect.left()/rect.width()+1;
    emit onNewStartPosition(X,Y);
    setStartPosition(X,Y);
}
void CMazeDraw::onMenuSetFinishPosition()
{
    unsigned int X=0,Y=0;

    QPoint pos = menuContextMaze->pos();
    pos = mapFromGlobal(pos);
    QRect rect = targetNormalRect(pos);
    Y = rect.top()/rect.height()+1;
    X = rect.left()/rect.width()+1;
    emit onNewFinishPosition(X,Y);
    setFinishPosition(X,Y);
    /*
    	m_lFinishPos.clear();
    	for(iterFinish=vPositionsList.begin();iterFinish!=vPositionsList.end();iterFinish++)
    	{
    		QPoint pos;
    		pos.setX(iterFinish->first-1);
    		pos.setY(iterFinish->second-1);
    		m_lFinishPos.push_back(pos);
    	}
    	update();	*/

}
void CMazeDraw::onMenuSetNextFinishPosition()
{
    unsigned int X=0,Y=0;
    QList<QPoint>::iterator	iterFinishPos;
    bool	bFound=false;
    QPoint pos = menuContextMaze->pos();
    pos = mapFromGlobal(pos);
    QRect rect = targetNormalRect(pos);
    Y = rect.top()/rect.height()+1;
    X = rect.left()/rect.width()+1;

    //checking if there is already location with this cords
    for(iterFinishPos=m_lFinishPos.begin(); iterFinishPos!=m_lFinishPos.end(); iterFinishPos++)
    {
        QPoint pos = *iterFinishPos;
        if (pos.x() == X-1 && pos.y() == Y-1)
        {
            bFound=true;
            break;
        }
    }
    if (!bFound)
    {
        emit setNextFinishPosition(X,Y);
        setNewFinishPosition(X,Y);
    }
}
void CMazeDraw::onSetRobotRoute(CMazeExplorationResult &lRoute)
{
    lRobotRoute = lRoute;
    update();
}
void CMazeDraw::onCellSelected(int row, int column )
{
//	CScanResults		scanResults;
    //	int count = lRobotRoute.getPositionsCount();
    //	lRobotRoute.getRobotPosition(row,scanResults);
    m_iSelectedRobotPos_X=row;
    m_iSelectedRobotPos_Y=column;
    update();
}
void CMazeDraw::onClearRobotRoute()
{
    lRobotRoute.clear();
    update();
}
void CMazeDraw::setMazeData(CMaze & mazeData)
{
    mazeData = *pMaze;
}
void	CMazeDraw::onSetFinishPosition(vector< pair<int,int> > vPositionsList)
{
//	unsigned int X=0,Y=0;
    vector< pair<int,int> >::iterator iterFinish;
    QList<QPoint>::iterator	iterFinishPos;
//	bool	bFound=false;

    m_lFinishPos.clear();
    for(iterFinish=vPositionsList.begin(); iterFinish!=vPositionsList.end(); iterFinish++)
    {
        QPoint pos;
        pos.setX(iterFinish->first-1);
        pos.setY(iterFinish->second-1);
        m_lFinishPos.push_back(pos);
    }
    update();
}
void	CMazeDraw::onSetRobotStartDirection(int iDir)
{
    iDirection = iDir;
    update();
}
