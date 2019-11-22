#include "arrow.h"

UpArrow::UpArrow(QWidget *parent)
    :QPushButton(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    state=0;
}
void UpArrow::set_state(int stat)
{
    state=stat;
    this->update();
}
int UpArrow::get_state(void)
{
    return state;
}
void UpArrow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor(80,80,80,255));
    QRect rect = this->rect();
    painter.drawRoundedRect(rect, 5, 5);
    if(ARROW_ACTIVE==get_state())
    {
        painter.setBrush(QColor(0,100,200,255));
    }
    else
    {
        painter.setBrush(QColor(160,160,160,255));
    }
    static const QPointF points[6] = {
          QPointF(8.0, 32.0),
          QPointF(8.0, 20.0),
          QPointF(20.0, 8.0),
          QPointF(32.0, 20.0),
          QPointF(32.0, 32.0),
          QPointF(20.0, 20.0)
      };
    painter.drawPolygon(points, 6);
}

DownArrow::DownArrow(QWidget *parent)
    :QPushButton(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    state=0;
}
void DownArrow::set_state(int stat)
{
    state=stat;
    this->update();
}
int DownArrow::get_state(void)
{
    return state;
}
void DownArrow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor(80,80,80,255));
    QRect rect = this->rect();
    painter.drawRoundedRect(rect, 5, 5);
    if(ARROW_ACTIVE==get_state())
    {
        painter.setBrush(QColor(0,100,200,255));
    }
    else
    {
        painter.setBrush(QColor(160,160,160,255));
    }
    static const QPointF points[6] = {
          QPointF(8.0, 8.0),
          QPointF(8.0, 20.0),
          QPointF(20.0, 32.0),
          QPointF(32.0, 20.0),
          QPointF(32.0, 8.0),
          QPointF(20.0, 20.0)
      };
    painter.drawPolygon(points, 6);
}

LeftArrow::LeftArrow(QWidget *parent)
    :QPushButton(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    state=0;
}
void LeftArrow::set_state(int stat)
{
    state=stat;
}
int LeftArrow::get_state(void)
{
    return state;
}
void LeftArrow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor(80,80,80,255));
    QRect rect = this->rect();
    painter.drawRoundedRect(rect, 5, 5);
    if(ARROW_ACTIVE==get_state())
    {
        painter.setBrush(QColor(0,100,200,255));
    }
    else
    {
        painter.setBrush(QColor(160,160,160,255));
    }
    static const QPointF points[6] = {
        QPointF(5.0, 25.0),
        QPointF(25.0, 5.0),
        QPointF(40.0, 5.0),
        QPointF(25.0, 25.0),
        QPointF(40.0, 45.0),
        QPointF(25.0, 45.0)
      };
    painter.drawPolygon(points, 6);
}

RightArrow::RightArrow(QWidget *parent)
    :QPushButton(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    state=0;
}
void RightArrow::set_state(int stat)
{
    state=stat;
}
int RightArrow::get_state(void)
{
    return state;
}
void RightArrow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor(80,80,80,255));
    QRect rect = this->rect();
    painter.drawRoundedRect(rect, 5, 5);
    if(ARROW_ACTIVE==get_state())
    {
        painter.setBrush(QColor(0,100,200,255));
    }
    else
    {
        painter.setBrush(QColor(160,160,160,255));
    }
    static const QPointF points[6] = {
        QPointF(10.0, 5.0),
        QPointF(25.0, 5.0),
        QPointF(45.0, 25.0),
        QPointF(25.0, 45.0),
        QPointF(10.0, 45.0),
        QPointF(25.0, 25.0)
      };
    painter.drawPolygon(points, 6);
}
