#include "pqwertkb.h"

PQwertKb::PQwertKb(QWidget *parent) : Popups(parent)
{

    init_key();
    this->setGeometry(192,150,640,350);
    QPixmap pixmap = QPixmap(":/image/background/qwert_keyboard.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

}
void PQwertKb::init_key(void)
{
    key_cancel = new Key("cancel",this);
    dis_line = new QLineEdit(this);
    key_enter = new Key("enter",this);
    key_del = new Key("del",this);
    key_1 = new Key("1",this);
    key_2 = new Key("2",this);
    key_3 = new Key("3",this);
    key_4 = new Key("4",this);
    key_5 = new Key("5",this);
    key_6 = new Key("6",this);
    key_7 = new Key("7",this);
    key_8 = new Key("8",this);
    key_9 = new Key("9",this);
    key_0 = new Key("0",this);
    key_q = new Key("q",this);
    key_w = new Key("w",this);
    key_e = new Key("e",this);
    key_r = new Key("r",this);
    key_t = new Key("t",this);
    key_y = new Key("y",this);
    key_u = new Key("u",this);
    key_i = new Key("i",this);
    key_o = new Key("o",this);
    key_p = new Key("p",this);
    key_a = new Key("a",this);
    key_s = new Key("s",this);
    key_d = new Key("d",this);
    key_f = new Key("f",this);
    key_g = new Key("g",this);
    key_h = new Key("h",this);
    key_j = new Key("j",this);
    key_k = new Key("k",this);
    key_l = new Key("l",this);
    key_sub = new Key("-",this);
    key_shift = new Key("shift",this);
    key_z = new Key("z",this);
    key_x = new Key("x",this);
    key_c = new Key("c",this);
    key_v = new Key("v",this);
    key_space = new Key(" ",this);
    key_b = new Key("b",this);
    key_n = new Key("n",this);
    key_m = new Key("m",this);
    key_dot = new Key(".",this);
    key_cancel->setGeometry(597,2,40,36);
    dis_line->setGeometry(15,40,400,56);
    key_del->setGeometry(432,45,57,45);
    key_enter->setGeometry(516,45,57,45);
    key_1->setGeometry(12,115,57,45);
    key_2->setGeometry(74,115,57,45);
    key_3->setGeometry(136,115,57,45);
    key_4->setGeometry(198,115,57,45);
    key_5->setGeometry(260,115,57,45);
    key_6->setGeometry(322,115,57,45);
    key_7->setGeometry(384,115,57,45);
    key_8->setGeometry(446,115,57,45);
    key_9->setGeometry(508,115,57,45);
    key_0->setGeometry(569,115,57,45);
    key_q->setGeometry(12,171,57,45);
    key_w->setGeometry(74,171,57,45);
    key_e->setGeometry(136,171,57,45);
    key_r->setGeometry(198,171,57,45);
    key_t->setGeometry(260,171,57,45);
    key_y->setGeometry(322,171,57,45);
    key_u->setGeometry(384,171,57,45);
    key_i->setGeometry(446,171,57,45);
    key_o->setGeometry(508,171,57,45);
    key_p->setGeometry(569,171,57,45);
    key_a->setGeometry(12,229,57,45);
    key_s->setGeometry(74,229,57,45);
    key_d->setGeometry(136,229,57,45);
    key_f->setGeometry(198,229,57,45);
    key_g->setGeometry(260,229,57,45);
    key_h->setGeometry(322,229,57,45);
    key_j->setGeometry(384,229,57,45);
    key_k->setGeometry(446,229,57,45);
    key_l->setGeometry(508,229,57,45);
    key_sub->setGeometry(569,229,57,45);
    key_shift->setGeometry(12,286,57,45);
    key_z->setGeometry(74,286,57,45);
    key_x->setGeometry(136,286,57,45);
    key_c->setGeometry(198,286,57,45);
    key_v->setGeometry(260,286,57,45);
    key_space->setGeometry(322,286,57,45);
    key_b->setGeometry(384,286,57,45);
    key_n->setGeometry(446,286,57,45);
    key_m->setGeometry(508,286,57,45);
    key_dot->setGeometry(569,286,57,45);
    QList<Button*> child_button = this->findChildren<Button *>(QString(), Qt::FindDirectChildrenOnly);
    for(int i=0;i<child_button.size();i++)
    {
        child_button.at(i)->set_press_color(QColor(0,0,0,50),CLICK_BTN);
        child_button.at(i)->setStyleSheet("background-color:transparent");
        connect(child_button.at(i),SIGNAL(key_clicked(QString)),this,SLOT(key_function(QString)));
    }
    dis_line->setStyleSheet("background-color:transparent;border:none");
    QFont font("Microsoft YaHei",18,QFont::Normal);
    dis_line->setFont(font);
    key_shift->set_press_color(QColor(0,0,0,80),TOGGLE_BTN);
    capital_stat=0;
}
void PQwertKb::key_function(QString key_val)
{
    qDebug()<< key_val;
    if(key_val=="cancel")
    {
        emit finish_input(ori_str);
    }
    else if(key_val=="enter")
    {
        emit finish_input(edit_str);
    }
    else if(key_val=="shift")
    {
        if(capital_stat)
        {
            capital_stat=0;
         //   key_shift->set_press_color(QColor(0,0,0,80),CHECK_BTN);
        }
        else
        {
            capital_stat=1;
           // key_shift->set_press_color(QColor(0,0,0,0),CHECK_BTN);
        }
    }
    else if(key_val=="del")
    {
        edit_str.remove(edit_str.size()-1,1);
        dis_line->setText(edit_str);
    }
    else
    {
        if(capital_stat&&(key_val.at(0)<=122)&&(key_val.at(0)>=97))
        {
            char letter=key_val.at(0).toLatin1();
            letter=letter-32;
            key_val.remove(0,1);
            key_val.insert(0,letter);
        }
        edit_str+=key_val;
        dis_line->setText(edit_str);
    }
}
void PQwertKb::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}
