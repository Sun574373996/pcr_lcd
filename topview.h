#ifndef TOPVIEW_H
#define TOPVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include "common.h"
class TopView : public QGraphicsView
{
    Q_OBJECT

public:
    TopView(QWidget *parent = 0);
    ~TopView();
protected:
    void moveEvent(QMoveEvent *event);

};

#endif // TOPVIEW_H
