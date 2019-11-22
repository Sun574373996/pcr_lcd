#include "page6.h"

Page6::Page6(QWidget *parent) : Widget(parent)
{
    QFont font(this->font());
    font.setPointSize(24);
    title_label=new QLabel(tr("高级选项"));
    title_label->setParent(this);
    title_label->setStyleSheet("background-color:transparent;color:white");
    title_label->setGeometry(430,0,180,65);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setFont(font);

    btn_back=new Button;
    btn_back->setParent(this);
    btn_back->setGeometry(44,6,50,50);
    btn_back->setStyleSheet("background-color:transparent");
    btn_back->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(btn_back,SIGNAL(clicked()),this,SLOT(jump_page4()));

    btn_cancel = new Button;
    btn_cancel->setParent(this);
    btn_cancel->setText(tr("取消"));
    btn_cancel->setFont(font);
    btn_cancel->setGeometry(0,521,255,79);
    btn_cancel->setStyleSheet("background-color:blue;color:white");
    btn_cancel->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(jump_page4()));
    btn_confirm = new Button;
    btn_confirm->setParent(this);
    btn_confirm->setText(tr("确定"));
    btn_confirm->setFont(font);
    btn_confirm->setGeometry(770,521,255,79);
    btn_confirm->setStyleSheet("background-color:red;color:white");
    btn_confirm->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(btn_confirm,SIGNAL(clicked()),this,SLOT(confirm_change()));
    font.setPointSize(18);
    times_label=new QLabel(tr("跳转次数"));
    times_label->setParent(this);
    times_label->setStyleSheet("background-color:red;color:white");
    times_label->setGeometry(172,432,120,35);
    times_label->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    times_label->setFont(font);
    times_label->setStyleSheet("background-color:red;color:white");
    font.setPointSize(16);
    page_dis=new QLabel("1/2");
    page_dis->setParent(this);
    page_dis->setGeometry(446,250,40,40);
    page_dis->setAlignment(Qt::AlignCenter);
    page_dis->setFont(font);
    page_dis->setStyleSheet("background-color:red;color:white");
    step_btn_g=new QButtonGroup;
    for(int i=0;i<6;i++)
    {
        Button *btn=new Button;
        btn->setParent(this);
        btn->setGeometry(175,134+46*i,251,42);
        btn->setStyleSheet("background-color:transparent;");
        btn->set_press_color(QColor(0,155,255,255),CHECK_BTN);
        btn->setEnabled(true);
        step_btn_l.append(btn);
        step_btn_g->addButton(btn,i);
        QLabel *name_label=new QLabel;
        name_label->setParent(btn);
        name_label->setFont(font);
        name_label->setGeometry(0,2,250,36);
        name_label->setStyleSheet("background-color:transparent;color:white;");
        name_label->setAlignment(Qt::AlignCenter);
        step_name_l.append(name_label);
    }
    connect(step_btn_g,SIGNAL(buttonPressed(int)),this,SLOT(step_btn_change(int)));
    up_step = new UpArrow;
    down_step = new DownArrow;
    up_step->setParent(this);
    up_step->setGeometry(446,200,40,40);
    down_step->setParent(this);
    down_step->setGeometry(446,300,40,40);
    connect(up_step,SIGNAL(clicked()),this,SLOT(step_up()));
    connect(down_step,SIGNAL(clicked()),this,SLOT(step_down()));
    dis_line = new QLineEdit(this);
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
    dis_line->setStyleSheet("background-color:transparent;border:none;color:white");
    dis_line->setGeometry(300,432,150,35);
    dis_line->setFont(font);
    dis_line->setAlignment(Qt::AlignCenter);
    key_1->setGeometry(524,133,99,80);
    key_2->setGeometry(631,133,99,80);
    key_3->setGeometry(738,133,99,80);
    key_sub->setGeometry(845,133,99,80);
    key_4->setGeometry(524,218,99,80);
    key_5->setGeometry(631,218,99,80);
    key_6->setGeometry(738,218,99,80);
    key_eq->setGeometry(845,218,99,80);
    key_7->setGeometry(524,303,99,80);
    key_8->setGeometry(631,303,99,80);
    key_9->setGeometry(738,303,99,80);
    key_col->setGeometry(845,303,99,80);
    key_dot->setGeometry(524,388,99,80);
    key_0->setGeometry(631,388,99,80);
    key_del->setGeometry(738,388,99,80);
    key_enter->setGeometry(845,388,99,80);

    QList<Key*> child_key = this->findChildren<Key *>(QString(), Qt::FindDirectChildrenOnly);
    for(int i=0;i<child_key.size();i++)
    {
        child_key.at(i)->set_press_color(QColor(0,0,0,50),CLICK_BTN);
        child_key.at(i)->setStyleSheet("background-color:transparent");
        connect(child_key.at(i),SIGNAL(key_clicked(QString)),this,SLOT(key_function(QString)));
    }
    this->resize(1024,600);
    QPixmap pixmap = QPixmap(":/image/background/cycle_set.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);
}
void Page6::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void Page6::refresh_page(void)
{
    int i;
    edit_str.clear();
    dis_line->clear();
    index=dev_file->run_file->check_seg;
    step_num.clear();
    for(i=0;i<dev_file->run_file->cycles.size();i++)
    {
        if(index<(dev_file->run_file->cycles.at(i).begin_seg-1))
        {
            if(index<(dev_file->run_file->cycles.at(i).begin_seg-2))
            {
                for(int j=0;j<(dev_file->run_file->cycles.at(i).begin_seg-index-2);j++)
                {
                    step_num.append(j+index+2);
                }
            }
            if((i+1)<dev_file->run_file->cycles.size())
            {
                if((dev_file->run_file->cycles.at(i+1).begin_seg
                    -dev_file->run_file->cycles.at(i).end_seg)>1)
                {
                    for(int j=0;j<(dev_file->run_file->cycles.at(i+1).begin_seg-
                                   dev_file->run_file->cycles.at(i).end_seg);j++)
                    {
                        step_num.append(dev_file->run_file->cycles.at(i).end_seg+j+1);
                    }
                }
            }
            else
            {
                if(dev_file->run_file->cycles.at(i).end_seg<dev_file->run_file->segs.size())
                {
                    for(int j=0;j<(dev_file->run_file->segs.size()-
                                   dev_file->run_file->cycles.at(i).end_seg);j++)
                    {
                        step_num.append(dev_file->run_file->cycles.at(i).end_seg+j+1);
                    }
                }
            }
            break;
        }
    }
    if(i>=dev_file->run_file->cycles.size())
    {
        if(index<(dev_file->run_file->segs.size()-1))
        {
            for(int j=0;j<(dev_file->run_file->segs.size()-
                           index-1);j++)
            {
                step_num.append(index+j+2);
            }
        }
    }
    for(i=0;i<step_num.size();i++)
    {
        qDebug()<<"step_num"<< step_num.at(i);
    }
    step_page=0;
    dis_step();
}
void Page6::dis_step(void)
{
    step_id=-1;
    QString str(tr("STEP%1"));
    for(int i=step_page*6;i<step_page*6+6;i++)
    {
        if(i<step_num.size())
        {
            step_btn_l.at(i%6)->setEnabled(true);
            step_name_l.at(i%6)->setText(str.arg(step_num.at(step_page*6+i%6)));
        }
        else
        {
            step_btn_l.at(i%6)->setEnabled(false);
            step_name_l.at(i%6)->clear();
        }
        step_btn_l.at(i%6)->set_state(BTN_RELEASE_STAT);
    }
    str="%1/%2";
    int page_totle;
    page_totle=(step_num.size()-1)/6+1;
    page_dis->setText(str.arg(step_page+1).arg(page_totle));
    if(step_page>0)
    {
        up_step->set_state(ARROW_ACTIVE);
        up_step->setEnabled(true);
    }
    else
    {
        up_step->set_state(ARROW_NOTACTIVE);
        up_step->setEnabled(false);
    }
    if((step_page+1)==page_totle)
    {
        down_step->set_state(ARROW_NOTACTIVE);
        down_step->setEnabled(false);
    }
    else
    {
        down_step->set_state(ARROW_ACTIVE);
        down_step->setEnabled(true);
    }
}
void Page6::key_function(QString key_val)
{
    bool ok;
    int dec = key_val.toInt(&ok, 10);
    if(ok==true)
    {
        int edit=edit_str.toInt();
        if(dec==0)
        {
            if(0<edit&&edit<10)
            {
                edit_str+=key_val;
                dis_line->setText(edit_str);
            }
        }
        else
        {
            if(edit<10)
            {
                edit_str+=key_val;
                dis_line->setText(edit_str);
            }
        }
    }
    else if(key_val=="del")
    {
        edit_str.remove(edit_str.size()-1,1);
        dis_line->setText(edit_str);
    }
    else{}
}
void Page6::step_btn_change(int id)
{
    qDebug()<<"step_btn_change"<<id;
    if(id!=step_id)
    {
        if((0 <= step_id)&&(step_id <= 5))
        {
            step_btn_l[step_id]->set_state(BTN_RELEASE_STAT);
            step_btn_l[step_id]->update();
        }
        step_id=id;
    }
}
void Page6::step_up(void)
{
    step_page--;
    dis_step();
}
void Page6::step_down(void)
{
    step_page++;
    dis_step();
}
void Page6::jump_page4(void)
{
    qDebug()<<"jump_page4";

    emit page_jump(NEXT_PAGE,6,4);
}
void Page6::confirm_change(void)
{
    qDebug()<<"jump_page4";
    if(0<=step_id&&step_id<=5)
    {
        if(edit_str.size()!=0)
        {
            int i=0;
            cycle.begin_seg=index+1;
            cycle.end_seg=step_num.at(step_page*6+step_id);
            cycle.num=edit_str.toInt();
            for(i=0;i<dev_file->run_file->cycles.size();i++)
            {
                if(dev_file->run_file->cycles.at(i).begin_seg>cycle.begin_seg)
                {
                    dev_file->run_file->cycles.insert(i,cycle);
                    break;
                }
            }
            if(i>=dev_file->run_file->cycles.size())
            {
                dev_file->run_file->cycles.append(cycle);
            }
        }
    }
    emit page_jump(NEXT_PAGE,6,4);
}
