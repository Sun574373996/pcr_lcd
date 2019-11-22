#ifndef WIDGET6_H
#define WIDGET6_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QButtonGroup>
#include "button.h"
#include "widget.h"
#include "common.h"
#include "arrow.h"
class Page6 : public Widget
{
    Q_OBJECT
public:
    explicit Page6(QWidget *parent = 0);
    int index;
    int step_page;
    int step_id;
    int check_id;
    QList<int> step_num;
    FileCycle cycle;
    Button *btn_back;
    Button *btn_cancel;
    Button *btn_confirm;
    QLabel *title_label;
    QLabel *times_label;
    QLabel *page_dis;
    QList<Button*> step_btn_l;
    QButtonGroup *step_btn_g;
    QList<QLabel*> step_name_l;
    UpArrow *up_step;
    DownArrow *down_step;
    QString edit_str;
    QLineEdit *dis_line;
    Key *key_enter;
    Key *key_del;
    Key *key_1;
    Key *key_2;
    Key *key_3;
    Key *key_4;
    Key *key_5;
    Key *key_6;
    Key *key_7;
    Key *key_8;
    Key *key_9;
    Key *key_0;
    Key *key_sub;
    Key *key_dot;
    Key *key_eq;
    Key *key_col;
    void refresh_page(void);
signals:

public slots:
    void jump_page4(void);
    void confirm_change(void);
    void key_function(QString key_val);
    void step_btn_change(int id);
    void dis_step(void);
    void step_up(void);
    void step_down(void);
protected:
    void paintEvent(QPaintEvent *event);

};


#endif // WIDGET6_H
