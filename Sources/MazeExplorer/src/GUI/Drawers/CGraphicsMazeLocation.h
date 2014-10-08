#ifndef C_GRAPHICS_MAZE_LOCATION_H
#define C_GRAPHICS_MAZE_LOCATION_H
#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QVector>
#include <QLineF>
#include <Data/experiment/EnviromentVariables.h>
#include <Maze/location.h>

enum eLocationType
{
    E_LT_NONE,
    E_LT_START_POS,
    E_LT_END_POS
};

class CGraphicsMazeLocation : public QGraphicsItem, public QGraphicsLayoutItem
{
public:
    CGraphicsMazeLocation();
    //sets location data - like walls location
    void setLocationData(const location & locData);
    //
    void setLocationPos(int iPosX,int iPosY);
    //sets flag - is this location a Start or End point (do not change if none of them)
    void setExitStartLocation(bool bStart,bool bReset=false);
    //sets data about path in which location is
    void setPathData(eRobotDir ePathRobotDir);
    //
    void setSelected(bool bSelected);

    QRectF boundingRect() const;
	void setGeometry(const QRectF &geom);
	QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	location	m_LocData;
    int		m_iPosX;
    int		m_iPosY;
    //is this location a Start or End point or empty
    eLocationType	m_eLocType;
    //is this location a selected one
    bool			m_bSelected;
    //is this location a part of exploration path and robot direction in this location
    eRobotDir		m_ePathRobotDir;

	QImage stImage;

    QVector<QLineF>	m_vLines;

};
#endif
