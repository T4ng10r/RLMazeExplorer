#pragma once
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class experiment_result_draft : public QWidget
{
    Q_OBJECT
public:
    experiment_result_draft(QWidget *parent);
    ~experiment_result_draft(void);
public Q_SLOTS:
    void slotDataForDraft(QVector<float> &dataForDraft);
protected:
    void paintEvent(QPaintEvent *event);
    void drawGrid(QPainter &painter,QRect & rect);
    void drawExperimentResults(QPainter &painter,QRect & rect);
    QVector<float> dataForDraft;
};
