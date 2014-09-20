#pragma once
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class CExperimentResultDraft : public QWidget
{
    Q_OBJECT
public:
    CExperimentResultDraft(QWidget *parent);
    ~CExperimentResultDraft(void);
public Q_SLOTS:
    void slotDataForDraft(QVector<float> &dataForDraft);
protected:
    void paintEvent(QPaintEvent *event);
    void drawGrid(QPainter &painter,QRect & rect);
    void drawExperimentResults(QPainter &painter,QRect & rect);
    QVector<float> dataForDraft;
};
