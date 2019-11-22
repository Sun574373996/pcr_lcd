#include "topsense.h"
#include <QDebug>
TopSense::TopSense(QObject *parent)
    :QGraphicsScene(parent)
{
    page1=new Page1;
    page2=new Page2;
    page3=new Page3;
    page4=new Page4;
    page5=new Page5;
    page6=new Page6;
    page7=new Page7;
    connect(page1,SIGNAL(page_jump(int,int,int)),this,SLOT(change_page(int,int,int)));
    connect(page2,SIGNAL(page_jump(int,int,int)),this,SLOT(change_page(int,int,int)));
    connect(page3,SIGNAL(page_jump(int,int,int)),this,SLOT(change_page(int,int,int)));
    connect(page4,SIGNAL(page_jump(int,int,int)),this,SLOT(change_page(int,int,int)));
    connect(page5,SIGNAL(page_jump(int,int,int)),this,SLOT(change_page(int,int,int)));
    connect(page6,SIGNAL(page_jump(int,int,int)),this,SLOT(change_page(int,int,int)));
    connect(page7,SIGNAL(page_jump(int,int,int)),this,SLOT(change_page(int,int,int)));
    pages.append(this->addWidget(page1));
    pages.append(this->addWidget(page2));
    pages.append(this->addWidget(page3));
    pages.append(this->addWidget(page4));
    pages.append(this->addWidget(page5));
    pages.append(this->addWidget(page6));
    pages.append(this->addWidget(page7));
    for(int i=0;i<pages.size();i++)
    {
        pages.at(i)->setRotation(90);
    }
    pages[0]->setVisible(true);
    pages[1]->setVisible(false);
    pages[2]->setVisible(false);
    pages[3]->setVisible(false);
    pages[4]->setVisible(false);
    pages[5]->setVisible(false);
    pages[6]->setVisible(false);
    cur_page=1;

}
TopSense::~TopSense()
{

}
void TopSense::change_page(int mod,int cur,int dst)
{
    qDebug()<<"change_page";
    QDateTime datetime(QDateTime::currentDateTime());
    QTime cur_time=datetime.time();
    qDebug()<< cur_time.hour() << cur_time.minute() << cur_time.second() << cur_time.msec();
    if(NEXT_PAGE==mod)
    {
        pages[dst-1]->setVisible(true);
        pages[cur_page-1]->setVisible(false);
        Widget *p =dynamic_cast<Widget*>(pages[dst-1]->widget());
        p->refresh_page();
        pre_page=cur_page;
        cur_page=dst;
    }
    else if(PRE_PAGE==mod)
    {
        pages[pre_page-1]->setVisible(true);
        pages[cur-1]->setVisible(false);
        Widget *p =dynamic_cast<Widget*>(pages[pre_page-1]->widget());
        p->refresh_page();
        cur_page=pre_page;
        pre_page=cur;
    }
    else{}
    datetime=QDateTime::currentDateTime();
    cur_time=datetime.time();
    qDebug()<< cur_time.hour() << cur_time.minute() << cur_time.second() << cur_time.msec();

}
