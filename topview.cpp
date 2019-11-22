#include "topview.h"

TopView::TopView(QWidget *parent)
    : QGraphicsView(parent)
{
    //this->setStyleSheet("padding:0px;border:0px");
    this->setFrameStyle(QFrame::NoFrame);
}

TopView::~TopView()
{

}
void TopView::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);
 //   qDebug()<<"move event";
}
