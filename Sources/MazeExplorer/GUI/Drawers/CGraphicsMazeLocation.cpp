#include <QtGui/QPainter>
#include <QtGui/QPen>
#include "CGraphicsMazeLocation.h"

const int ciMinLocationSize=30;

CGraphicsMazeLocation::CGraphicsMazeLocation()
{
    m_iPosX=0;
    m_iPosY=0;

    m_bSelected=false;
	setExitStartLocation(true,true);
	setPathData(ROBOT_NONE_DIR);
    m_vLines.clear();
	setMinimumSize(QSizeF(ciMinLocationSize,ciMinLocationSize));
	setGraphicsItem(this);
}
void CGraphicsMazeLocation::setLocationData(const CLocation & locData)
{
    QRectF rectF = boundingRect();
    m_LocData = locData;

    //////////////////////////////////////////////////////////////////////////
	m_vLines.clear();
    if (m_LocData.up)
    {
        QLineF line;
        line.setP1(rectF.topLeft());
        line.setP2(rectF.topRight());
        m_vLines.push_back(line);
    }
    if (m_LocData.down)
    {
        QLineF line;
        line.setP1(rectF.bottomLeft());
        line.setP2(rectF.bottomRight());
        m_vLines.push_back(line);
    }
    if (m_LocData.right)
    {
        QLineF line;
        line.setP1(rectF.topRight());
        line.setP2(rectF.bottomRight());
        m_vLines.push_back(line);
    }
    if (m_LocData.left)
    {
        QLineF line;
        line.setP1(rectF.topLeft());
        line.setP2(rectF.bottomLeft());
        m_vLines.push_back(line);
    }
}
void CGraphicsMazeLocation::setLocationPos(int iPosX,int iPosY)
{
    m_iPosX = iPosX;
    m_iPosY = iPosY;
}
void CGraphicsMazeLocation::setExitStartLocation(bool bStart,bool bReset)
{
	if (bReset)
		m_eLocType = E_LT_NONE;
	else
		m_eLocType = bStart?E_LT_START_POS:E_LT_END_POS;
}
void CGraphicsMazeLocation::setPathData(eRobotDir ePathRobotDir)
{
	m_ePathRobotDir = ePathRobotDir;
	switch(m_ePathRobotDir)
	{
	case ROBOT_NORTH_DIR:
		stImage = QImage(":/images/north.png");
		break;
	case ROBOT_WEST_DIR:
		stImage = QImage(":/images/west.png");
		break;
	case ROBOT_EAST_DIR:
		stImage = QImage(":/images/east.png");
		break;
	case ROBOT_SOUTH_DIR:
		stImage = QImage(":/images/south.png");
		break;
	default:
		break;
	}
}
void CGraphicsMazeLocation::setSelected(bool bSelected)
{
    m_bSelected = bSelected;
}
void CGraphicsMazeLocation::setGeometry(const QRectF &geom)
{
	prepareGeometryChange();
	QGraphicsLayoutItem::setGeometry(geom);
	setPos(geom.topLeft());
}
QRectF CGraphicsMazeLocation::boundingRect() const
{
    QRectF rectF;
    rectF.setSize(QSizeF(ciMinLocationSize,ciMinLocationSize));
    return rectF;
}
QSizeF CGraphicsMazeLocation::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
	switch (which) {
	case Qt::MinimumSize:
		return QSizeF(ciMinLocationSize,ciMinLocationSize);
	case Qt::MaximumSize:
		return QSizeF(1000,1000);
	default:
		break;
	}
	return constraint;
}
void CGraphicsMazeLocation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QSizeF sizeF = geometry().size();
	QPen pen = painter->pen();
	QRectF rectF(QPoint(0,0),sizeF);

	switch(m_eLocType)
	{
	case E_LT_START_POS:
		{
			pen.setColor(Qt::green);
			painter->setPen(pen);
			rectF.adjust(5,5,-5,-5);
			painter->drawRoundedRect(rectF,3,3);
			//rysujemy strzalke kierunku
			break;
		}
	case E_LT_END_POS:
		{
			pen.setColor(Qt::gray);
			pen.setWidth(1);
			painter->setPen(pen);
			painter->drawRoundedRect(rectF.adjusted(5,5,-5,-5),3,3);
			painter->drawRoundedRect(rectF.adjusted(10,10,-10,-10),3,3);
			break;
		}
	default:
		break;
	}
	if (m_ePathRobotDir !=ROBOT_NONE_DIR)
	{
		rectF.adjust(2,2,-2,-2);
		painter->drawImage(rectF,stImage);
	}
	pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
	painter->drawLines(m_vLines);

}
