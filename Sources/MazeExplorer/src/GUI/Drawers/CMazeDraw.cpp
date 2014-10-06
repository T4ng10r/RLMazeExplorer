#include "CMazeDraw.h"
#include <GUI/main_window.h>


class maze_draw_private
{
public:
	maze_draw_private(maze_draw * pub);
	void reset();
	void createContextMenu();
	void prepareLocationVars();
	const QRect get_normal_rect(const QPoint &position);
	const QRect get_normal_rect(int posX, int posY);
	const QRect getRouteRect(int posX, int posY);
	const QRect getRobotRect(int posX, int posY);
	QPoint m_ptRobot_startPos;
	QPoint m_ptRobot_finishPos;
	int   iDirection;
	QList<QPoint>	m_lFinishPos;
	void draw_location(const location& location, QRect rect, QPainter *painter);
	void drawRobotLocations(QPainter &painter/*, QRect rectStart, QRect rectFinish*/);
	void drawRobotRoute(QPainter &painter);
	void drawCrossRoad(QPainter & painter, const CScanResults &scanResults);
public:
	maze_draw *         public_;
	QPen pen;
	QBrush brush;
	QMenu *				menuContextMaze;
	QAction *			actionSetStart;
	QAction *			actionSetEnd;
	QAction *			actionSetNextEnd;
	maze_interface_type maze_data;
	QRect	normalLoc;
	QRect	scaledLoc;
	QRect	robotLoc;
	int size_x, size_y;
	int scale_size_x, scale_size_y;
	int robot_scale_size_x, robot_scale_size_y;
	int m_iSelectedRobotPos_X;
	int m_iSelectedRobotPos_Y;
	CMazeExplorationResult		lRobotRoute;
};

maze_draw_private::maze_draw_private(maze_draw * pub) : public_(pub), iDirection(ROBOT_NORTH_DIR)
{}

void maze_draw_private::reset()
{
	lRobotRoute.clear();
	size_x = 0;
	size_y = 0;
	scale_size_x = 0;
	scale_size_y = 0;
	m_iSelectedRobotPos_X = -1;
	m_iSelectedRobotPos_Y = -1;
}
void maze_draw_private::createContextMenu()
{
	actionSetStart = new QAction(QObject::tr("&Start position"), public_);
	actionSetStart->setStatusTip(QObject::tr("From here agent will start his exploration"));
	QObject::connect(actionSetStart, SIGNAL(triggered()), public_, SLOT(onMenuon_set_start_position()));

	actionSetEnd = new QAction(QObject::tr("&Maze exit"), public_);
	actionSetEnd->setStatusTip(QObject::tr("This is target of agent exploration"));
	QObject::connect(actionSetEnd, SIGNAL(triggered()), public_, SLOT(onMenuSetFinishPosition()));

	actionSetNextEnd = new QAction(QObject::tr("&Another exit..."), public_);
	actionSetNextEnd->setStatusTip(QObject::tr("This is target of agent exploration"));
	QObject::connect(actionSetNextEnd, SIGNAL(triggered()), public_, SLOT(onMenuSetNextFinishPosition()));

	menuContextMaze = new QMenu(NULL);
	menuContextMaze->addAction(actionSetStart);
	menuContextMaze->addAction(actionSetEnd);
	menuContextMaze->addAction(actionSetNextEnd);
	//	menuContextMaze->addSeparator();
}
const QRect maze_draw_private::get_normal_rect(const QPoint &position)
{
	return QRect(position.x() / size_x * size_x, position.y() / size_y * size_y, size_x, size_y);
}
const QRect maze_draw_private::get_normal_rect(int pos_x, int pos_y)
{
	return QRect(pos_x * size_x, pos_y * size_y, size_x, size_y);
}
const QRect maze_draw_private::getRouteRect(int pos_x, int size_y)
{
	QRect rect = get_normal_rect(pos_x, size_y);
	return rect.adjusted(scale_size_x, scale_size_y, -scale_size_x, -scale_size_y);
}
const QRect maze_draw_private::getRobotRect(int pos_x, int pos_y)
{
	QRect rect = getRouteRect(pos_x, pos_y);
	return rect.adjusted(robot_scale_size_x, robot_scale_size_y, -robot_scale_size_x, -robot_scale_size_y);
}
void maze_draw_private::prepareLocationVars()
{
	unsigned int X = 0, Y = 0;
	unsigned int heig = 0, wid = 0;

	X = maze_data->get_size_x();
	Y = maze_data->get_size_y();
	heig = public_->height() - 2;
	wid = public_->width() - 2;

	size_x = wid / X;
	size_y = heig / Y;

	scale_size_x = size_y*0.15;
	scale_size_y = size_y*0.15;

	robot_scale_size_x = scale_size_x*0.5;
	robot_scale_size_y = scale_size_y*0.5;
}
void maze_draw_private::drawRobotRoute(QPainter &painter)
{
	//	unsigned int	m_iRobotPos_X=m_ptRobot_startPos.x();
	//	unsigned int	m_iRobotPos_Y=m_ptRobot_startPos.y();
	QRect rect(0, 0, 10, 10);
	CScanResults		scanResults;
	pen.setColor(Qt::red);
	pen.setWidth(2);
	painter.setPen(pen);

	int count = lRobotRoute.getPositionsCount();

	for (int i = 0; i<count; i++)
	{
		lRobotRoute.getRobotPosition(i, scanResults);
		rect = getRouteRect(scanResults.robotPos.posX - 1, scanResults.robotPos.posY - 1);
		if (scanResults.getExitsCount(false)>1)
			drawCrossRoad(painter, scanResults);
		else
			painter.drawRect(rect);
	}
	if (m_iSelectedRobotPos_X >= 0)
	{
		pen.setColor(Qt::blue);
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(1);

		painter.setPen(pen);
		rect = getRobotRect(m_iSelectedRobotPos_X - 1, m_iSelectedRobotPos_Y - 1);
		painter.drawRect(rect);
	}
}
void maze_draw_private::draw_location(const location& location, QRect rect, QPainter *painter)
{
	if (location.is_wall(NORTH_DIR))
		painter->drawLine(rect.topLeft(), rect.topRight());
	if (location.is_wall(EAST_DIR))
		painter->drawLine(rect.topRight(), rect.bottomRight());
	if (location.is_wall(SOUTH_DIR))
		painter->drawLine(rect.bottomRight(), rect.bottomLeft());
	if (location.is_wall(WEST_DIR))
		painter->drawLine(rect.bottomLeft(), rect.topLeft());
	//---//
	if (location.is_wall(SOUTH_DIR) && location.is_wall(WEST_DIR))
		painter->drawPoint(rect.bottomLeft().x(), rect.bottomLeft().y() - 1);
	if (location.is_wall(SOUTH_DIR) && location.is_wall(EAST_DIR))
		painter->drawPoint(rect.bottomRight().x(), rect.bottomRight().y() + 1);
	if (location.is_wall(NORTH_DIR) && location.is_wall(EAST_DIR))
		painter->drawPoint(rect.topRight().x(), rect.topRight().y() - 1);
	if (location.is_wall(NORTH_DIR) && location.is_wall(WEST_DIR))
		painter->drawPoint(rect.topLeft().x(), rect.topLeft().y() + 1);
}
void maze_draw_private::drawRobotLocations(QPainter &painter)
{
	QList<QPoint>::iterator	iterFinishPos;
	QRect rect;
	//starting position
	rect = getRobotRect(m_ptRobot_startPos.x(), m_ptRobot_startPos.y());
	pen.setColor(Qt::red);
	pen.setWidth(2);
	painter.setPen(pen);

	painter.drawRect(rect);
	//dorzucamy tez ikone
	if (rect.height() > 12 && rect.width() > 12)
	{
		QIcon icon;
		switch (iDirection)
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
		pos += QPoint(rect.width() / 2, rect.height() / 2);
		pos -= QPoint(cIconSize.width() / 2, cIconSize.height() / 2);
		QPixmap pixmap = icon.pixmap(cIconSize);
		painter.drawPixmap(pos, pixmap);
	}

	//draw all finish positions
	for (iterFinishPos = m_lFinishPos.begin(); iterFinishPos != m_lFinishPos.end(); iterFinishPos++)
	{
		rect = getRobotRect(iterFinishPos->x(), iterFinishPos->y());
		pen.setColor(Qt::darkRed);
		pen.setWidth(2);
		pen.setStyle((Qt::PenStyle)2);
		painter.setPen(pen);

		painter.drawRect(rect);
	}
}
void maze_draw_private::drawCrossRoad(QPainter & painter, const CScanResults &scanResults)
{
	QRect rect;
	//starting position
	rect = getRobotRect(scanResults.robotPos.posX - 1, scanResults.robotPos.posY - 1);
	pen.setColor(Qt::red);
	pen.setWidth(2);
	painter.setPen(pen);

	painter.drawRect(rect);
	//dorzucamy tez ikone
	if (rect.height() > 12 && rect.width() > 12)
	{
		QIcon icon;
		switch (scanResults.robotPos.dir)
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
		pos += QPoint(rect.width() / 2, rect.height() / 2);
		pos -= QPoint(cIconSize.width() / 2, cIconSize.height() / 2);
		QPixmap pixmap = icon.pixmap(cIconSize);
		painter.drawPixmap(pos, pixmap);
	}
}
//////////////////////////////////////////////////////////////////////////
maze_draw::maze_draw(QWidget *parent) : QWidget(parent), pimpl(new maze_draw_private(this))
{
    pimpl->reset();
    setMinimumSize(200, 200);
    setBackgroundRole(QPalette::Base);
	pimpl->pen.setColor(Qt::blue);
	pimpl->pen.setStyle((Qt::PenStyle)1);
	pimpl->pen.setCapStyle((Qt::PenCapStyle)0);
    setMouseTracking(true);
	pimpl->createContextMenu();
}
maze_draw::~maze_draw(){}
//----------------------------------------------------------------//
void maze_draw::paintEvent(QPaintEvent *)
{
	QRect rect(0, 0, 10, 10);
	QPainter painter(this);
	unsigned int maze_size_x=0,maze_size_y=0;
	maze_size_x = pimpl->maze_data->get_size_x();
	maze_size_y = pimpl->maze_data->get_size_y();
	pimpl->prepareLocationVars();

	pimpl->pen.setColor(Qt::blue);
	pimpl->pen.setStyle((Qt::PenStyle)1);
	pimpl->pen.setWidth(1);

	painter.setPen(pimpl->pen);
	painter.setBrush(pimpl->brush);

	for (unsigned int x = 0; x < maze_size_x; x++)
		for (unsigned int y = 0; y < maze_size_y; y++)
		{
			rect = pimpl->get_normal_rect(x, y);
			boost::optional<location> location_ = pimpl->maze_data->get_location(x + 1, y + 1);
			pimpl->draw_location(location_.get(), rect, &painter);
		}

	pimpl->drawRobotLocations(painter);
	pimpl->drawRobotRoute(painter);
}
//----------------------------------------------------------------//
void maze_draw::mouseMoveEvent(QMouseEvent * event)
{
    CScanResults		scanResult;
    //	CRobotPostion		robotPos;
    int x,y;
	int count = pimpl->lRobotRoute.getPositionsCount();
	pimpl->m_iSelectedRobotPos_X = -1;
	pimpl->m_iSelectedRobotPos_Y = -1;
    if (count)
    {
		x = event->x() / pimpl->size_x + 1;
		y = event->y() / pimpl->size_y + 1;
        //szukamy pozycji z trasy robota
        for(int index=0; index<count; index++)
        {
			pimpl->lRobotRoute.getRobotPosition(index, scanResult);
            if (scanResult.robotPos.posX==x && scanResult.robotPos.posY == y)
            {
                Q_EMIT SelectRoutePos(index);
				pimpl->m_iSelectedRobotPos_X = scanResult.robotPos.posX;
				pimpl->m_iSelectedRobotPos_Y = scanResult.robotPos.posY;
                break;
            }
        }
    }
    update();
}
void maze_draw::mousePressEvent(QMouseEvent *event)
{
    Qt::MouseButtons	Buttons = event->buttons();
    QPoint pos = event->pos();
    pos = QWidget::mapToGlobal ( pos  );
    if (Buttons & Qt::RightButton)
    {
        pimpl->menuContextMaze->popup(pos);
    }
}
void maze_draw::mouseReleaseEvent(QMouseEvent* /*event*/)
{
}
//----------------------------------------------------------------//
void maze_draw::on_set_start_position(int posX,int posY)
{
	pimpl->m_ptRobot_startPos.setX(posX - 1);
	pimpl->m_ptRobot_startPos.setY(posY - 1);
	Q_EMIT clearRobotRoute();
	pimpl->lRobotRoute.clear();
    update();
}
void maze_draw::setFinishPosition(int posX,int posY)
{
    QPoint	finishPos;
    finishPos.setX(posX-1);
    finishPos.setY(posY-1);
	pimpl->m_lFinishPos.clear();
	pimpl->m_lFinishPos.push_back(finishPos);
	Q_EMIT clearRobotRoute();
	pimpl->lRobotRoute.clear();
    update();
}
void maze_draw::setNewFinishPosition(int posX,int posY)
{
    QPoint	finishPos;
    finishPos.setX(posX-1);
    finishPos.setY(posY-1);
	pimpl->m_lFinishPos.push_back(finishPos);
	Q_EMIT clearRobotRoute();
	pimpl->lRobotRoute.clear();
    update();
}
void maze_draw::onMenuon_set_start_position()
{
    unsigned int X=0,Y=0;

	QPoint pos = pimpl->menuContextMaze->pos();
    pos = mapFromGlobal(pos);
	QRect rect = pimpl->get_normal_rect(pos);
    Y = rect.top()/rect.height()+1;
    X = rect.left()/rect.width()+1;
	Q_EMIT onNewStartPosition(X, Y);
    on_set_start_position(X,Y);
}
void maze_draw::onMenuSetFinishPosition()
{
    unsigned int X=0,Y=0;

	QPoint pos = pimpl->menuContextMaze->pos();
    pos = mapFromGlobal(pos);
	QRect rect = pimpl->get_normal_rect(pos);
    Y = rect.top()/rect.height()+1;
    X = rect.left()/rect.width()+1;
	Q_EMIT onNewFinishPosition(X, Y);
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
void maze_draw::onMenuSetNextFinishPosition()
{
    unsigned int X=0,Y=0;
    QList<QPoint>::iterator	iterFinishPos;
    bool	bFound=false;
	QPoint pos = pimpl->menuContextMaze->pos();
    pos = mapFromGlobal(pos);
	QRect rect = pimpl->get_normal_rect(pos);
    Y = rect.top()/rect.height()+1;
    X = rect.left()/rect.width()+1;

    //checking if there is already location with this cords
	for (iterFinishPos = pimpl->m_lFinishPos.begin(); iterFinishPos != pimpl->m_lFinishPos.end(); iterFinishPos++)
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
		Q_EMIT setNextFinishPosition(X, Y);
        setNewFinishPosition(X,Y);
    }
}
void maze_draw::onSetRobotRoute(CMazeExplorationResult &lRoute)
{
	pimpl->lRobotRoute = lRoute;
    update();
}
void maze_draw::onCellSelected(int row, int column )
{
//	CScanResults		scanResults;
    //	int count = lRobotRoute.getPositionsCount();
    //	lRobotRoute.getRobotPosition(row,scanResults);
	pimpl->m_iSelectedRobotPos_X = row;
	pimpl->m_iSelectedRobotPos_Y = column;
    update();
}
void maze_draw::onClearRobotRoute()
{
	pimpl->lRobotRoute.clear();
    update();
}
void maze_draw::on_set_maze_data(maze_interface_type maze)
{
	pimpl->maze_data = maze;
}
void	maze_draw::onSetFinishPosition(vector< pair<int,int> > vPositionsList)
{
//	unsigned int X=0,Y=0;
    vector< pair<int,int> >::iterator iterFinish;
    QList<QPoint>::iterator	iterFinishPos;
//	bool	bFound=false;

	pimpl->m_lFinishPos.clear();
    for(iterFinish=vPositionsList.begin(); iterFinish!=vPositionsList.end(); iterFinish++)
    {
        QPoint pos;
        pos.setX(iterFinish->first-1);
        pos.setY(iterFinish->second-1);
		pimpl->m_lFinishPos.push_back(pos);
    }
    update();
}
void	maze_draw::onSetRobotStartDirection(int iDir)
{
	pimpl->iDirection = iDir;
    update();
}
