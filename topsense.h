#ifndef TOPSENSE_H
#define TOPSENSE_H

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page4.h"
#include "page5.h"
#include "page6.h"
#include "page7.h"
#include "common.h"
class TopSense : public QGraphicsScene
{
     Q_OBJECT
public:
    TopSense(QObject *parent = Q_NULLPTR);
    ~TopSense();
    Page1 *page1;
    Page2 *page2;
    Page3 *page3;
    Page4 *page4;
    Page5 *page5;
    Page6 *page6;
    Page7 *page7;
    QList<QGraphicsProxyWidget*> pages;
    int cur_page;
    int pre_page;
public slots:
    void change_page(int mod,int cur=0,int dst=0);
};

#endif // TOPSENSE_H
