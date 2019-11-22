#ifndef PQwertKb_H
#define PQwertKb_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QLineEdit>
#include "common.h"
#include "popups.h"
#include "button.h"
#include "label.h"
#include "key.h"
class PQwertKb : public Popups
{
    Q_OBJECT
public:
    explicit PQwertKb(QWidget *parent = 0);
    QString ori_str;
    QString edit_str;
    QLineEdit *dis_line;
    Key *key_cancel;
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
    Key *key_q;
    Key *key_w;
    Key *key_e;
    Key *key_r;
    Key *key_t;
    Key *key_y;
    Key *key_u;
    Key *key_i;
    Key *key_o;
    Key *key_p;
    Key *key_a;
    Key *key_s;
    Key *key_d;
    Key *key_f;
    Key *key_g;
    Key *key_h;
    Key *key_j;
    Key *key_k;
    Key *key_l;
    Key *key_sub;
    Key *key_shift;
    Key *key_z;
    Key *key_x;
    Key *key_c;
    Key *key_v;
    Key *key_space;
    Key *key_b;
    Key *key_n;
    Key *key_m;
    Key *key_dot;
    int capital_stat;
signals:
    void finish_input(QString str);
public slots:
    void init_key(void);
    void key_function(QString key_val);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PQwertKb_H
