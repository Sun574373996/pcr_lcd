#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
}
void Widget::enable_all_activex(QObject *parent_object)
{
    QList<QWidget *> child_widget = parent_object->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
    for (int i=0;i<child_widget.size();i++)
    {
        child_widget.at(i)->setEnabled(true);
    }
}
void Widget::disable_all_activex(QObject *parent_object)
{
    QList<QWidget *> child_widget = parent_object->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
    for (int i=0;i<child_widget.size();i++)
    {
        child_widget.at(i)->setEnabled(false);
    }
}
void Widget::set_all_font(QFont &font)
{
    QList<QWidget *> child_widget = this->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
    for (int i=0;i<child_widget.size();i++)
    {
        child_widget.at(i)->setFont(font);
    }
}
void Widget::open_keyboard(Label *label,int type)
{
    qDebug()<< "keyboard type" << type;
    int left=0,top=0;
    edit_label=label;
    keyboard_type=type;
    this->disable_all_activex(this);
    if(keyboard_type==NUM_EDIT)
    {
        QRect label_pos(edit_label->geometry());
        QRect parent_pos(edit_label->parentWidget()->geometry());
        qDebug()<< "parent_pos.left()"<<parent_pos.left();
        qDebug()<<"parent_pos.top()"<<parent_pos.top();
        if(parent_pos.left()!=0||parent_pos.top()!=0)
        {
            left=label_pos.left()+parent_pos.left();
            top=label_pos.top()+parent_pos.top();
        }
        else
        {
            left=label_pos.left();
            top=label_pos.top();
        }
        if((left+label_pos.width())<750)
        {
            left=left+label_pos.width();
        }
        else
        {
            left=left-250;
        }
        if((top+label_pos.height())<350)
        {
            top=top+label_pos.height();
        }
        else
        {
            top=top-250;
        }

        num_kb = new PNumKb();
        num_kb->setGeometry(left,top,250,250);
        qDebug()<< "new  PNumKb";
        num_kb->setParent(this);
        num_kb->setVisible(true);
        num_kb->show();
        num_kb->dis_line->setEnabled(true);
        num_kb->dis_line->setFocus();
        num_kb->dis_line->setPlaceholderText(edit_label->get_value());

        connect(num_kb,SIGNAL(finish_input(QString)),this,SLOT(close_keyboard(QString)));
    }
    else if(keyboard_type==QWERT_EDIT)
    {

        qwert_kb=new PQwertKb();
        qwert_kb->setParent(this);
        qwert_kb->show();
        qwert_kb->dis_line->setEnabled(true);
        qwert_kb->dis_line->setFocus();
        connect(qwert_kb,SIGNAL(finish_input(QString)),this,SLOT(close_keyboard(QString)));
    }
    else{}
}
void Widget::close_keyboard(QString str)
{
    if(keyboard_type==NUM_EDIT)
    {
        if(0==edit_label->input_str(str))
        {
            this->enable_all_activex(this);
            num_kb->deleteLater();
        }
        else
        {

            num_kb->edit_str.clear();
        }
    }
    else if(keyboard_type==QWERT_EDIT)
    {
        qDebug() << str;
        this->enable_all_activex(this);
        edit_label->setText(str);
        qwert_kb->deleteLater();
    }
    else{}
}
void Widget::refresh_page(void)
{
    qDebug() << "refresh_page";
}
