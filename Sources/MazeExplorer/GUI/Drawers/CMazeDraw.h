#ifndef C_DRAWMAZE_H
#define C_DRAWMAZE_H
#include <QtGui/QWidget>
#include <QtGui/QPainterPath>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QMouseEvent>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtCore/QPoint>
#include <QtCore/QPair>
#include <QtGui/QTableWidgetItem>
#include <Maze/CMaze.h>
#include <Data/Experiment/CMazeExplorationResult.h>
#include <vector>
#include <map>
const QSize cIconSize(22,22);

using namespace std;

class CMazeDraw : public QWidget
{
    Q_OBJECT

public:
    CMazeDraw(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setMaze(CMaze * maze)
    {
        pMaze=maze;
    }

protected:
    void reset();
    void createContextMenu();
    void prepareLocationVars();
    const QRect targetNormalRect(const QPoint &position);
    const QRect getNormalRect(int posX,int posY);
    const QRect getRouteRect(int posX,int posY);
    const QRect getRobotRect(int posX,int posY);
    QPoint m_ptRobot_startPos;
    QPoint m_ptRobot_finishPos;
    int   iDirection;
    QList<QPoint>	m_lFinishPos;
    void paintEvent(QPaintEvent *event);
    void DrawLocation(const CLocation& location, QRect rect, QPainter *painter);
    void drawRobotLocations(QPainter &painter/*, QRect rectStart, QRect rectFinish*/);
    void drawRobotRoute(QPainter &painter);
    void drawCrossRoad(QPainter & painter,const CScanResults &scanResults);

    QPen pen;
    QBrush brush;
    QMenu *				menuContextMaze;
    QAction *			actionSetStart;
    QAction *			actionSetEnd;
    QAction *			actionSetNextEnd;
    CMaze *				pMaze;
signals:
    void	SelectRoutePos(int index);	//zaznacza wybrane przez uzytkownika pole ze sciezki robota na dialogu z wynikami eksploracji
    void	onNewStartPosition(int posX,int posY);		//wybrano nowa lokacje startowa
    void	onNewFinishPosition(int posX,int posY);		//wybrano nowa lokacje docelowa
    void	setNextFinishPosition(int posX,int posY);	//wybrano nastepna lokacje docelowa
    void	clearRobotRoute();

public slots:
    void	setMazeData(CMaze & mazeData);
    void	setStartPosition(int posX,int posY);		//wybrano nowa lokacje startowa
    void	setFinishPosition(int posX,int posY);		//wybrano nowa lokacje docelowa
    void	setNewFinishPosition(int posX,int posY);
    void	onSetRobotRoute(CMazeExplorationResult &lRoute);
    void	onCellSelected(int , int );
    void	onClearRobotRoute();
    void	onSetFinishPosition(vector< pair<int,int> >);
    void	onSetRobotStartDirection(int iDir);
protected slots:
    void	onMenuSetStartPosition();	//zmiana pozycji startowej robota
    void	onMenuSetFinishPosition();	//zmiana pozycji docelowej robota
    void	onMenuSetNextFinishPosition();	//zmiana pozycji docelowej robota

private:
    QRect	normalLoc;
    QRect	scaledLoc;
    QRect	robotLoc;
    int sizeX,sizeY;
    int scaleSizeX,scaleSizeY;
    int robotScaleSizeX,robotScaleSizeY;
    int m_iSelectedRobotPos_X;
    int m_iSelectedRobotPos_Y;
    CMazeExplorationResult		lRobotRoute;

//	QList<QPair<int,int> > lRoute;
};

#endif
