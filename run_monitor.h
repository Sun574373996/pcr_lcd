#ifndef RUNMONITOR_H
#define RUNMONITOR_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "common.h"
#include <QPainter>
#include <QPainterPath>
class RunMonitor : public QLabel
{
    Q_OBJECT
public:
    RunMonitor(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *event);
private:

signals:

};

#endif // RUNMONITOR_H
