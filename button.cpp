#include "button.h"

Button::Button(QWidget *parent)
    :QPushButton(parent)
{
    state=0;
    QFont font("Microsoft YaHei",18);
    this->setFont(font);
    this->setFocusPolicy(Qt::NoFocus);
}
void Button::set_press_color(const QColor &color,int model)
{
    press_color=color;
    mod=model;
}
void Button::set_image_path(const QString &path,int model)
{
    image_path=path;
    mod=model;
}
void Button::set_state(int stat)
{
    state=stat;
}
int Button::get_state(void)
{
    return state;
}
void Button::mousePressEvent(QMouseEvent *event)
{

    if(TOGGLE_BTN==mod)
    {
        if(state)
        {
            state=0;
        }
        else
        {
            state=1;
        }
    }
    else
    {
        set_state(BTN_PRESS_STAT);
    }
    QPushButton::mousePressEvent(event);
    beep->beep_one();
    qDebug()<<"press_button";
}
void Button::mouseReleaseEvent(QMouseEvent *event)
{
    if(CHECK_BTN==mod)
    {

    }
    else if(CLICK_BTN==mod)
    {
        set_state(BTN_RELEASE_STAT);
    }
    else{}
    QPushButton::mouseReleaseEvent(event);
}
void Button::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    if(BTN_PRESS_STAT==get_state())
    {
        QPainter painter(this);
        painter.setPen(QColor(0,0,0,0));
        painter.setBrush(press_color);
        QRect rect = this->rect();
        rect.setWidth(rect.width() - 1);
        rect.setHeight(rect.height() - 1);
        painter.drawRoundedRect(rect, 3, 3);
    }

}
