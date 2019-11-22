#include "label.h"

Label::Label(QWidget *parent)
    :QLabel(parent)
{
    edit_mod=NO_EDIT;
}
int Label::set_value(const QString &str)
{
    value=str;
    this->setText(QString(value+unit));
    return 0;
}
void Label::set_unit(const QString &str)
{
    unit=str;
}
void Label::set_edit_mod(int mod)
{
    edit_mod=mod;
}
QString Label::get_value(void)
{
    return value;
}
void Label::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit send_edit_label(this,edit_mod);
}

int Label::input_str(QString &str)
{
    if(0==str.count())
    {
    }
    else
    {
        value=str;
        emit value_change(value);
        this->setText(value+unit);
    }
    return 0;
}
