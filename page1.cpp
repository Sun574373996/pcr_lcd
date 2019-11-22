#include "page1.h"

Page1::Page1(QWidget *parent) : Widget(parent)
{
    QFont font(this->font());
    font.setPointSize(30);
    title_label=new QLabel(tr("我的设备"));
    title_label->setParent(this);
    title_label->setStyleSheet("background-color:transparent;color:white");
    title_label->setGeometry(430,0,180,65);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setFont(font);
    btn_new=new Button;
    btn_new->setParent(this);
    btn_new->setGeometry(257,462,253,94);
    btn_new->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    btn_new->setStyleSheet("background-color:transparent;color:white");
    font.setPointSize(22);
    btn_new->setFont(font);
    btn_new->setText(QString(tr("        新建文件")));
    btn_manage=new Button;
    btn_manage->setParent(this);
    btn_manage->setText(QString(tr("        文件管理")));
    btn_manage->setGeometry(512,462,256,94);
    btn_manage->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    btn_manage->setStyleSheet("background-color:transparent;color:white");
    btn_manage->setFont(font);
    btn_set=new Button;
    btn_set->setParent(this);
    btn_set->setText(QString(tr("        系统设置")));
    btn_set->setGeometry(770,477,254,80);
    btn_set->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    btn_set->setStyleSheet("background-color:transparent;color:white");
    btn_set->setFont(font);
    module_A =new RunMonitor;
    module_A->setParent(this);
    module_A->setGeometry(362,120,300,300);
    connect(btn_new,SIGNAL(clicked()),this,SLOT(jump_page7()));
    connect(btn_manage,SIGNAL(clicked()),this,SLOT(jump_page2()));
    this->resize(1024,600);
    QPixmap pixmap = QPixmap(":/image/background/main_page.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}
void Page1::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void Page1::jump_page2(void)
{
    qDebug()<<"jump_page2";
    emit page_jump(NEXT_PAGE,1,2);
}
void Page1::jump_page7(void)
{
    qDebug()<<"jump_page7";
    emit page_jump(NEXT_PAGE,1,7);
}
