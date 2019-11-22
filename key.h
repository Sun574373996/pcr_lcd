#ifndef KEY_H
#define KEY_H


#include "button.h"
class Key : public Button
{
    Q_OBJECT
public:
    Key(QString val,QWidget *parent = 0);
    QString key_val;
public slots:
    void send_key(void);
signals:
    void key_clicked(QString key_val);
};

#endif // KEY_H
