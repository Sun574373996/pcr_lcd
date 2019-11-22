#include "psetdir.h"

PSetDir::PSetDir(QWidget *parent) : Popups(parent)
{


}
void PSetDir::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"painter PMoveFile";
    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/image/background/copy_page.jpg"),QRect());
}

