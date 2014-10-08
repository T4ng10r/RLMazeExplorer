#ifndef C_DRAWMAZE_H
#define C_DRAWMAZE_H
#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>
#include <QPoint>
#include <QPair>
#include <QTableWidgetItem>
#include <Maze/maze_interface.h>
#include <Data/experiment/CMazeExplorationResult.h>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <memory>
const QSize cIconSize(22,22);

using namespace std;
class maze_draw_private;

class maze_draw : public QWidget
{
    Q_OBJECT

public:
	maze_draw(QWidget *parent = 0);
	~maze_draw();

protected:
	void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

protected:
	boost::scoped_ptr<maze_draw_private> pimpl;

Q_SIGNALS:
    void	SelectRoutePos(int index);	//zaznacza wybrane przez uzytkownika pole ze sciezki robota na dialogu z wynikami eksploracji
    void	onNewStartPosition(int posX,int posY);		//wybrano nowa lokacje startowa
    void	onNewFinishPosition(int posX,int posY);		//wybrano nowa lokacje docelowa
    void	setNextFinishPosition(int posX,int posY);	//wybrano nastepna lokacje docelowa
    void	clearRobotRoute();

public Q_SLOTS:
    void	on_set_maze_data(maze_interface_type mazeData);
    void	on_set_start_position(int posX,int posY);		//wybrano nowa lokacje startowa
    void	setFinishPosition(int posX,int posY);		//wybrano nowa lokacje docelowa
    void	setNewFinishPosition(int posX,int posY);
    void	onSetRobotRoute(CMazeExplorationResult &lRoute);
    void	onCellSelected(int , int );
    void	onClearRobotRoute();
    void	onSetFinishPosition(vector< pair<int,int> >);
    void	onSetRobotStartDirection(int iDir);
protected Q_SLOTS:
    void	onMenuon_set_start_position();	//zmiana pozycji startowej robota
    void	onMenuSetFinishPosition();	//zmiana pozycji docelowej robota
    void	onMenuSetNextFinishPosition();	//zmiana pozycji docelowej robota
};

#endif
