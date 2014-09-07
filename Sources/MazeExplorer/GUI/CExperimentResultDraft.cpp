#include "CExperimentResultDraft.h"
const QColor backgroundColor(Qt::white);
const QColor gridColor = QColor("#A4c2DB");

CExperimentResultDraft::CExperimentResultDraft(QWidget *parent) : QWidget(parent)
{
}

CExperimentResultDraft::~CExperimentResultDraft(void)
{
}
void CExperimentResultDraft::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    QRect qRect	= event->rect();
    //emit showDrawRect(qRect);
    painter.begin(this);
    painter.fillRect(event->rect(), QColor(Qt::white));
    drawGrid(painter,qRect);
    drawExperimentResults(painter,qRect);
//	drawExperimentResults();
    //if (highlightedRect.isValid())
    //{
    //	painter.setBrush(QColor("#ffcccc"));
    //	painter.setPen(Qt::NoPen);
    //	painter.drawRect(highlightedRect.adjusted(1, 1, -1, -1));
    //}
    //drawGrid(painter,qRect);
    //drawRooms(painter,qRect);
    painter.end();
}
void CExperimentResultDraft::drawGrid(QPainter &painter,QRect & rect)
{
    unsigned int delta;
    QSize qSize = rect.size();
    QPen qPen = painter.pen();
    qPen.setColor(gridColor);
    qPen.setStyle(Qt::SolidLine);
    qPen.setWidth(3);
    painter.setPen(qPen);

    painter.drawRect(rect);
    //drawing horizontal lines

    qPen.setStyle(Qt::DashLine);
    qPen.setWidth(1);
    painter.setPen(qPen);

    delta = qSize.height()/5;
    for(unsigned int index=delta; index<qSize.height(); index+=delta)
    {
        painter.drawLine(QPoint(0,index),QPoint(qSize.width(),index));
    }
}
void CExperimentResultDraft::drawExperimentResults(QPainter &painter,QRect & rect)
{
    QPoint startPoint,endPoint;

    QPen qPen = painter.pen();
    QPen qNewPen = painter.pen();
    qNewPen.setColor(Qt::black);
    qNewPen.setStyle(Qt::SolidLine);
    qNewPen.setWidth(2);
    painter.setPen(qNewPen);

    int count = dataForDraft.size();
    if (count==0)	return;
    int horDelta=rect.width()/(count);
    int verDelta=rect.height()-2;
    int horStart=rect.left();
    int verStart=rect.bottom();
    int horAdd=0,verAdd=0;

    startPoint=rect.bottomLeft();
    for(int index=0; index<count-1; index++)
    {
        horAdd=(1+index)*(horDelta);
        endPoint.setX(horStart+horAdd);

        verAdd=dataForDraft[index]*verDelta;
        endPoint.setY(verStart-verAdd);
        painter.drawLine(startPoint,endPoint);
        startPoint=endPoint;
    }
    painter.setPen(qPen);
}
void CExperimentResultDraft::slotDataForDraft(QVector<float> &data)
{
    dataForDraft = data;
    update();
}
