#include "topview.h"
#include "topsense.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Microsoft YaHei");
    a.setFont(font);
    qDebug() << a.font().family();

    ctrl_com=new PortCtrl;
    dev_file=new DevFile;
    beep=new BEEP;
    qDebug()<< "create pages";
    TopSense sense;
    qDebug()<< "end pages";
    TopView view;
    view.setScene(&sense);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.resize(600,1024);

    qDebug() << "show view start";
    view.show();
    qDebug() << "show view end";
    top_view_x=view.x();
    top_view_y=view.y();

    return a.exec();
}
