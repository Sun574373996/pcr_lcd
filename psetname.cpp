#include "psetname.h"

PSetName::PSetName(QWidget *parent) : Popups(parent)
{
    name_edit =new Label;
    name_edit->setParent(this);
    name_edit->setGeometry(110,80,180,30);
    name_edit->edit_mod=QWERT_EDIT;
    name_edit->setText("abcde");
    name_edit->setStyleSheet("background-color:transparent;color:white");

    rename_btn=new Button;
    rename_btn->setParent(this);
    rename_btn->setGeometry(200,160,200,38);
    rename_btn->setStyleSheet("background-color:transparent;color:white");
    rename_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);

    cancel_btn=new Button;
    cancel_btn->setParent(this);
    cancel_btn->setGeometry(0,160,200,38);
    cancel_btn->setStyleSheet("background-color:transparent;color:white");
    cancel_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    this->setGeometry(320,200,400,200);
    QPixmap pixmap = QPixmap(":/image/background/rename_page.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}
void PSetName::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    qDebug()<<"painter PSetName";

}
