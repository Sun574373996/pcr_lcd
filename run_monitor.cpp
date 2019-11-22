#include "run_monitor.h"

RunMonitor::RunMonitor(QWidget *parent)
    :QLabel(parent)
{

}

void RunMonitor::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    qDebug() << "press RunMonitor";
}


void RunMonitor::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor(255,83,0,255));
    painter.drawPie(QRect(20,20,260,260),330*16,72*16);
    painter.setBrush(QColor(60,60,60,255));
    QPainterPath path;
    path.addEllipse(QPointF(150,150),150,150);
    path.addEllipse(QPointF(150,150),130,130);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.drawPath(path);
    painter.drawEllipse(QPointF(150,150),100,100);

    /*
    QPixmap pixmap = QPixmap(":/image/btn/run_monitor.png").scaled(this->size());
    painter.drawPixmap(this->rect(),pixmap);
    */
}
