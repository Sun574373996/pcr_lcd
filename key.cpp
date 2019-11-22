#include "key.h"

Key::Key(QString val,QWidget *parent)
    :Button(parent),key_val(val)
{
    connect(this,SIGNAL(clicked()),this,SLOT(send_key()));
    this->setFocusPolicy(Qt::NoFocus);
}

void Key::send_key(void)
{
    emit key_clicked(key_val);
}
