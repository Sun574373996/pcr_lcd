#include "pnumkb.h"

PNumKb::PNumKb(QWidget *parent) : Popups(parent)
{
    this->resize(QSize(250,250));
    init_key();
    QPixmap pixmap = QPixmap(":/image/background/num_keyboard.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setAutoFillBackground(true);
    this->setPalette(palette);

}
void PNumKb::init_key(void)
{

    dis_line = new QLineEdit(this);
    key_cancel = new Key("cancel",this);

    key_1 = new Key("1",this);
    key_2 = new Key("2",this);
    key_3 = new Key("3",this);
    key_sub = new Key("-",this);
    key_4 = new Key("4",this);
    key_5 = new Key("5",this);
    key_6 = new Key("6",this);
    key_eq = new Key("=",this);
    key_7 = new Key("7",this);
    key_8 = new Key("8",this);
    key_9 = new Key("9",this);
    key_col = new Key(":",this);
    key_dot = new Key(".",this);
    key_0 = new Key("0",this);
    key_del = new Key("del",this);
    key_enter = new Key("enter",this);

    dis_line->setStyleSheet("background-color:transparent;border:none");
    dis_line->setGeometry(10,10,200,36);
    key_cancel->setGeometry(215,10,32,36);
    key_1->setGeometry(8,56,55,45);
    key_2->setGeometry(68,56,55,45);
    key_3->setGeometry(128,56,55,45);
    key_sub->setGeometry(188,56,55,45);
    key_4->setGeometry(8,105,55,45);
    key_5->setGeometry(68,105,55,45);
    key_6->setGeometry(128,105,55,45);
    key_eq->setGeometry(188,105,55,45);
    key_7->setGeometry(8,154,55,45);
    key_8->setGeometry(68,154,55,45);
    key_9->setGeometry(128,154,55,45);
    key_col->setGeometry(188,154,55,45);
    key_dot->setGeometry(8,203,55,45);
    key_0->setGeometry(68,203,55,45);
    key_del->setGeometry(128,203,55,45);
    key_enter->setGeometry(188,203,55,45);

    QList<Button*> child_button = this->findChildren<Button *>(QString(), Qt::FindDirectChildrenOnly);
    for(int i=0;i<child_button.size();i++)
    {
        child_button.at(i)->set_press_color(QColor(0,0,0,50),CLICK_BTN);
        child_button.at(i)->setStyleSheet("background-color:transparent");
        connect(child_button.at(i),SIGNAL(key_clicked(QString)),this,SLOT(key_function(QString)));
    }


}
void PNumKb::key_function(QString key_val)
{
    qDebug() << key_val;
    if(key_val=="cancel")
    {
        emit finish_input(ori_str);
    }
    else if(key_val=="enter")
    {
        emit finish_input(edit_str);
    }
    else if(key_val=="del")
    {
        edit_str.remove(edit_str.size()-1,1);
        dis_line->setText(edit_str);
    }
    else
    {
        edit_str+=key_val;
        dis_line->setText(edit_str);
    }
}

void PNumKb::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}
