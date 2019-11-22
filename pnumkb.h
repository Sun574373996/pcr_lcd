#ifndef PNumKb_H
#define PNumKb_H

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
class PNumKb : public Popups
{
    Q_OBJECT
public:
    explicit PNumKb(QWidget *parent = 0);
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
    Key *key_sub;
    Key *key_dot;
    Key *key_eq;
    Key *key_col;
signals:
    void finish_input(QString str);
public slots:
    void init_key(void);
    void key_function(QString key_val);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PNumKb_H
