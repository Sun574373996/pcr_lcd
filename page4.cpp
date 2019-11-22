#include "page4.h"

Page4::Page4(QWidget *parent) : Widget(parent)
{
    back_btn=new Button;
    back_btn->setParent(this);
    back_btn->setGeometry(44,6,50,50);
    back_btn->setStyleSheet("background-color:transparent");
    back_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(back_btn,SIGNAL(clicked()),this,SLOT(back_page()));
    QFont font(this->font());
    font.setPixelSize(30);
    option_btn=new Button;
    option_btn->setParent(this);
    option_btn->setText(tr("高级选项"));
    option_btn->setFont(font);
    option_btn->setGeometry(0,521,171,77);
    option_btn->setStyleSheet("background-color:red;color:white");
    option_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(option_btn,SIGNAL(clicked()),this,SLOT(modify_more()));

    jump_btn=new Button;
    jump_btn->setParent(this);
    jump_btn->setText(tr("跳转"));
    jump_btn->setFont(font);
    jump_btn->setGeometry(172,521,171,77);
    jump_btn->setStyleSheet("background-color:green;color:white");
    jump_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(jump_btn,SIGNAL(clicked()),this,SLOT(set_cycle()));

    del_cycle_btn=new Button;
    del_cycle_btn->setParent(this);
    del_cycle_btn->setFont(font);
    del_cycle_btn->setText(tr("删除循环"));
    del_cycle_btn->setGeometry(344,521,173,77);
    del_cycle_btn->setStyleSheet("background-color:blue;color:white");
    del_cycle_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(del_cycle_btn,SIGNAL(clicked()),this,SLOT(del_cycle()));

    add_stage_btn = new Button;
    add_stage_btn->setParent(this);
    add_stage_btn->setFont(font);
    add_stage_btn->setText(tr("新增节"));
    add_stage_btn->setGeometry(517,521,173,77);
    add_stage_btn->setStyleSheet("background-color:green;color:white");
    add_stage_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(add_stage_btn,SIGNAL(clicked()),this,SLOT(add_stage()));

    del_stage_btn = new Button;
    del_stage_btn->setParent(this);
    del_stage_btn->setFont(font);
    del_stage_btn->setText(tr("删除节"));
    del_stage_btn->setGeometry(690,521,173,77);
    del_stage_btn->setStyleSheet("background-color:red;color:white");
    del_stage_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(del_stage_btn,SIGNAL(clicked()),this,SLOT(del_stage()));

    finish_btn=new Button;
    finish_btn->setParent(this);
    finish_btn->setFont(font);
    finish_btn->setText(tr("完成"));
    finish_btn->setGeometry(864,521,158,78);
    finish_btn->setStyleSheet("background-color:orange;color:white");
    finish_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(finish_btn,SIGNAL(clicked()),this,SLOT(finish_manage_step()));

    font.setPixelSize(24);

    turn_left = new LeftArrow;
    turn_right = new RightArrow;
    turn_left->setParent(this);
    turn_left->setGeometry(25,275,50,50);
    turn_right->setParent(this);
    turn_right->setGeometry(950,275,50,50);
    connect(turn_left,SIGNAL(clicked()),this,SLOT(page_up()));
    connect(turn_right,SIGNAL(clicked()),this,SLOT(page_down()));
    font.setPixelSize(20);
    for(int i=0;i<6;i++)
    {
        STAGE *stage = new STAGE(i);
        stage->setParent(this);
        stage->setGeometry(94+i*140,145,136,300);
        stage->tmp->setEnabled(false);
        stage->time->setEnabled(false);
        stages.append(stage);
        connect(stage,SIGNAL(stage_pressed(int)),this,SLOT(update_check_stage(int)));

        QLabel *label = new QLabel;
        label->setParent(this);
        cycles.append(label);
        label->setFont(font);
        label->setVisible(false);
        label->setStyleSheet("background-color:rgba(130,130,130,255);color:white");
    }
    check_stage=-1;
    this->resize(1024,600);
    QPixmap pixmap = QPixmap(":/image/background/step_manage.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}

void Page4::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void Page4::refresh_page(void)
{
    stage_page=0;
    back_up_file();
    refresh_stage();
    refresh_cycle();
    update_check_stage(-1);
}
void Page4::back_up_file(void)
{
    back_segs.clear();
    for(int i=0;i<dev_file->run_file->segs.size();i++)
    {
        back_segs.append(dev_file->run_file->segs.at(i));
    }
    back_cycles.clear();
    for(int i=0;i<dev_file->run_file->cycles.size();i++)
    {
        back_cycles.append(dev_file->run_file->cycles.at(i));
    }
}
void Page4::refresh_stage(void)
{
    for(int i=0;i<6;i++)
    {
        if(dev_file->run_file->segs.size()>(stage_page*6+i))
        {
            stages.at(i)->stage_id=stage_page*6+i;
            stages.at(i)->update_active_value();
            stages.at(i)->update_active_pos();
            stages.at(i)->setVisible(true);
        }
        else
        {
            stages.at(i)->setVisible(false);
        }
    }
}
void Page4::refresh_cycle(void)
{

    int left_pos=0,right_pos=0,top_pos=0;
    int begin=0,end=0;
    int index=0;
    for(int i=0;i<dev_file->run_file->cycles.size();i++)
    {
        left_pos=0;
        right_pos=0;
        begin=dev_file->run_file->cycles.at(i).begin_seg;
        end=dev_file->run_file->cycles.at(i).end_seg;
        if((begin>=(stage_page*6+1))&&(begin<=(stage_page*6+6)))
        {
            left_pos=94+140*((begin-1)%6);
        }
        if((end>=(stage_page*6+1))&&(end<=(stage_page*6+6)))
        {
            right_pos=94+140*((end-1)%6)+136;
        }
        if((begin<(stage_page*6+1))&&(end>(stage_page*6+6)))
        {
            left_pos=94;
            right_pos=94+140*5+136;;
        }
        qDebug()<<"left"<<begin;
        qDebug()<<"right"<<end;
        qDebug()<<"left_pos"<<left_pos;
        qDebug()<<"right_pos"<<right_pos;
        if(0==left_pos&&0==right_pos)
        {
        }
        else
        {
            top_pos=446;
            if((i+1)<dev_file->run_file->cycles.size())
            {
                if(dev_file->run_file->cycles.at(i+1).begin_seg<end)
                {
                    top_pos=471;
                }
            }
            if(0==left_pos)
            {
                left_pos=94;
                cycles.at(index)->setAlignment(Qt::AlignLeft);
            }
            else if(0==right_pos)
            {
                right_pos=94+140*5+136;
                cycles.at(index)->setAlignment(Qt::AlignRight);
            }
            else
            {
                cycles.at(index)->setAlignment(Qt::AlignCenter);
            }
            QString str("X%1");
            cycles.at(index)->setText(str.arg(dev_file->run_file->cycles.at(i).num));
            cycles.at(index)->setVisible(true);
            cycles.at(index)->setGeometry(left_pos,top_pos,right_pos-left_pos,23);
            index++;
            if(index==6)
            {
                break;
            }
        }
    }
    qDebug()<< "index" << index;
    for(int i=index;i<6;i++)
    {
        cycles.at(i)->setVisible(false);
    }
}
void Page4::update_check_stage(int check_id)
{
    int i;
    qDebug() << "update_check_stage" << check_id;

    if((check_id<stage_page*6+6)&&(check_id>=stage_page*6))
    {
        stages.at(check_id%6)->set_check_stat(CHECKED);
        stages.at(check_id%6)->repaint();
    }
    if(check_id!=check_stage)
    {
        if((check_stage<stage_page*6+6)&&(check_stage>=stage_page*6))
        {
            stages.at(check_stage%6)->set_check_stat(NO_CHECK);
            stages.at(check_stage%6)->repaint();
        }
    }
    qDebug() << "finish update_check_stage" << check_id;
    check_stage=check_id;
    jump_btn->setEnabled(false);
    del_cycle_btn->setEnabled(false);
    if((check_stage<stage_page*6+6)&&(check_stage>=stage_page*6))
    {
        option_btn->setEnabled(true);
        add_stage_btn->setEnabled(true);
        if(dev_file->run_file->segs.size()>1)
        {
            del_stage_btn->setEnabled(true);
        }
        else
        {
            del_stage_btn->setEnabled(false);
        }
        for(i=0;i<dev_file->run_file->cycles.size();i++)
        {
            if((check_stage>=(dev_file->run_file->cycles.at(i).begin_seg-1))
                    &&(check_stage<=(dev_file->run_file->cycles.at(i).end_seg-1)))
            {
                del_cycle_btn->setEnabled(true);
                break;
            }
        }
        for(i=0;i<dev_file->run_file->cycles.size();i++)
        {
            if(check_stage<(dev_file->run_file->cycles.at(i).begin_seg-1))
            {
                if(check_stage<(dev_file->run_file->cycles.at(i).begin_seg-2))
                {
                    jump_btn->setEnabled(true);
                }
                else
                {
                    if((i+1)<dev_file->run_file->cycles.size())
                    {
                        if((dev_file->run_file->cycles.at(i+1).begin_seg
                            -dev_file->run_file->cycles.at(i).end_seg)>1)
                        {
                             jump_btn->setEnabled(true);
                        }
                    }
                    else
                    {
                        if(dev_file->run_file->cycles.at(i).end_seg<dev_file->run_file->segs.size())
                        {
                             jump_btn->setEnabled(true);
                        }
                    }
                }
                break;
            }
            else if((check_stage<=(dev_file->run_file->cycles.at(i).end_seg-1)))
            {
                break;
            }
            else
            {

            }
        }
        if(i>=dev_file->run_file->cycles.size())
        {
            if(check_stage<(dev_file->run_file->segs.size()-1))
            {
                jump_btn->setEnabled(true);
            }
        }
    }
    else
    {
        option_btn->setEnabled(false);
        add_stage_btn->setEnabled(false);
        del_stage_btn->setEnabled(false);
    }
}
void Page4::update_btn_enable(void)
{
    int i=0;
    if(stage_page>0)
    {
        turn_left->set_state(ARROW_ACTIVE);
        turn_left->setEnabled(true);
    }
    else
    {
        turn_left->set_state(ARROW_NOTACTIVE);
        turn_left->setEnabled(false);
    }
    if((stage_page+1)*6<dev_file->run_file->segs.size())
    {
        turn_right->set_state(ARROW_ACTIVE);
        turn_right->setEnabled(true);
    }
    else
    {
        turn_right->set_state(ARROW_NOTACTIVE);
        turn_right->setEnabled(false);
    }
    turn_left->repaint();
    turn_right->repaint();

    jump_btn->setEnabled(false);
    del_cycle_btn->setEnabled(false);

    if((check_stage<stage_page*6+6)&&(check_stage>=stage_page*6))
    {
        option_btn->setEnabled(true);
        add_stage_btn->setEnabled(true);
        if(dev_file->run_file->segs.size()>1)
        {
            del_stage_btn->setEnabled(true);
        }
        else
        {
            del_stage_btn->setEnabled(false);
        }
        for(i=0;i<dev_file->run_file->cycles.size();i++)
        {
            if((check_stage>=(dev_file->run_file->cycles.at(i).begin_seg-1))
                    &&(check_stage<=(dev_file->run_file->cycles.at(i).end_seg-1)))
            {
                del_cycle_btn->setEnabled(true);
                break;
            }
        }
        for(i=0;i<dev_file->run_file->cycles.size();i++)
        {
            if(check_stage<(dev_file->run_file->cycles.at(i).begin_seg-1))
            {
                if(check_stage<(dev_file->run_file->cycles.at(i).begin_seg-2))
                {
                    jump_btn->setEnabled(true);
                }
                else
                {
                    if((i+1)<dev_file->run_file->cycles.size())
                    {
                        if((dev_file->run_file->cycles.at(i+1).begin_seg
                            -dev_file->run_file->cycles.at(i).end_seg)>1)
                        {
                             jump_btn->setEnabled(true);
                        }
                    }
                    else
                    {
                        if(dev_file->run_file->cycles.at(i).end_seg<dev_file->run_file->segs.size())
                        {
                             jump_btn->setEnabled(true);
                        }
                    }
                }
                break;
            }
            else if((check_stage<=(dev_file->run_file->cycles.at(i).end_seg-1)))
            {
                break;
            }
            else
            {}
        }
        if(i>=dev_file->run_file->cycles.size())
        {
            if(check_stage<(dev_file->run_file->segs.size()-1))
            {
                jump_btn->setEnabled(true);
            }
        }
    }
    else
    {
        option_btn->setEnabled(false);
        add_stage_btn->setEnabled(false);
        del_stage_btn->setEnabled(false);
    }
}
void Page4::finish_manage_step(void)
{
    jump_page3();
}
void Page4::back_page(void)
{
    dev_file->run_file->segs.clear();
    dev_file->run_file->cycles.clear();
    for(int i=0;i<back_segs.size();i++)
    {
        dev_file->run_file->segs.append(back_segs.at(i));
    }
    for(int i=0;i<back_cycles.size();i++)
    {
        dev_file->run_file->cycles.append(back_cycles.at(i));
    }
    jump_page3();
}
void Page4::modify_more(void)
{
    qDebug() << "modify_more";
    jump_page5();
}
void Page4::set_cycle(void)
{
    qDebug() << "set_cycle";
    jump_page6();
}
void Page4::del_cycle(void)
{
    qDebug() << "del_cycle";
    for(int i=0;i<dev_file->run_file->cycles.size();i++)
    {
        if((check_stage>=(dev_file->run_file->cycles.at(i).begin_seg-1))
                &&(check_stage<=(dev_file->run_file->cycles.at(i).end_seg-1)))
        {
            dev_file->run_file->cycles.removeAt(i);
            break;
        }
    }
    refresh_cycle();
    update_btn_enable();
}
void Page4::add_stage(void)
{
    qDebug() << "add_stage";
    FileCycle cycle;
    dev_file->run_file->segs.insert(check_stage+1,dev_file->run_file->segs.at(check_stage));
    for(int i=0;i<dev_file->run_file->cycles.size();i++)
    {
        cycle=dev_file->run_file->cycles.at(i);
        if((cycle.end_seg-1)<=check_stage)
        {
        }
        else
        {
            if((cycle.begin_seg-1)>check_stage)
            {
                cycle.begin_seg++;
            }
            cycle.end_seg++;
            dev_file->run_file->cycles.replace(i,cycle);
        }
    }
    for(int i=check_stage%6+1;i<6;i++)
    {
        if(dev_file->run_file->segs.size()>(stage_page*6+i))
        {
            stages.at(i)->stage_id=stage_page*6+i;
            stages.at(i)->update_active_value();
            stages.at(i)->update_active_pos();
            stages.at(i)->setVisible(true);
            stages.at(i)->update();
        }
        else
        {
            stages.at(i)->setVisible(false);
        }
    }
    for(int i=0;i<dev_file->run_file->cycles.size();i++)
    {
        qDebug() << "cycles" << i;
        qDebug() << dev_file->run_file->cycles.at(i).begin_seg << dev_file->run_file->cycles.at(i).end_seg;
    }
    refresh_cycle();
    update_btn_enable();
}
void Page4::del_stage(void)
{
    qDebug() << "del_stage";
    FileCycle cycle;
    dev_file->run_file->segs.removeAt(check_stage);
    for(int i=0;i<dev_file->run_file->cycles.size();i++)
    {
        cycle=dev_file->run_file->cycles.at(i);
        if((cycle.end_seg-1)<check_stage)
        {
        }
        else
        {
            if((cycle.begin_seg-1)>check_stage)
            {
                cycle.begin_seg--;
            }
            cycle.end_seg--;

            if(cycle.begin_seg==cycle.end_seg)
            {
                dev_file->run_file->cycles.removeAt(i);
            }
            else
            {
                dev_file->run_file->cycles.replace(i,cycle);
            }
            if((i+1)<dev_file->run_file->cycles.size())
            {
                if((cycle.end_seg==check_stage)&&(cycle.end_seg==dev_file->run_file->cycles.at(i+1).end_seg))
                {
                    dev_file->run_file->cycles.removeAt(i);
                }
            }
        }
    }
    if(check_stage==dev_file->run_file->segs.size())
    {
        stages.at(check_stage%6)->set_check_stat(NO_CHECK);
        check_stage--;
        stages.at(check_stage%6)->set_check_stat(CHECKED);
        if(check_stage%6==5)
        {
            stage_page--;
        }
        for(int i=0;i<6;i++)
        {
            if(dev_file->run_file->segs.size()>(stage_page*6+i))
            {
                stages.at(i)->stage_id=stage_page*6+i;
                stages.at(i)->update_active_value();
                stages.at(i)->update_active_pos();
                stages.at(i)->setVisible(true);
                if(check_stage==(i+stage_page*6))
                {
                    stages.at(i)->set_check_stat(CHECKED);
                }
                else
                {
                    stages.at(i)->set_check_stat(NO_CHECK);
                }
                stages.at(i)->update();
            }
            else
            {
                stages.at(i)->setVisible(false);
            }
        }
    }
    else
    {
        for(int i=check_stage%6;i<6;i++)
        {
            if(dev_file->run_file->segs.size()>(stage_page*6+i))
            {
                stages.at(i)->stage_id=stage_page*6+i;
                stages.at(i)->update_active_value();
                stages.at(i)->update_active_pos();
                stages.at(i)->setVisible(true);
                stages.at(i)->update();
            }
            else
            {
                stages.at(i)->setVisible(false);
            }
        }
    }
    refresh_cycle();
    update_btn_enable();
}
void Page4::page_up(void)
{
    qDebug() << "page_up";
    turn_left->repaint();
    stage_page--;
    for(int i=0;i<6;i++)
    {
        if(dev_file->run_file->segs.size()>(stage_page*6+i))
        {
            stages.at(i)->stage_id=stage_page*6+i;
            stages.at(i)->update_active_value();
            stages.at(i)->update_active_pos();
            stages.at(i)->setVisible(true);
            if(check_stage==(i+stage_page*6))
            {
                stages.at(i)->set_check_stat(CHECKED);
            }
            else
            {
                stages.at(i)->set_check_stat(NO_CHECK);
            }
            stages.at(i)->update();
        }
        else
        {
            stages.at(i)->setVisible(false);
        }
    }
    refresh_cycle();
    update_btn_enable();
}
void Page4::page_down(void)
{
    qDebug() << "page_down";
    turn_right->repaint();
    stage_page++;
    for(int i=0;i<6;i++)
    {
        if(dev_file->run_file->segs.size()>(stage_page*6+i))
        {
            stages.at(i)->stage_id=stage_page*6+i;
            stages.at(i)->update_active_value();
            stages.at(i)->update_active_pos();
            stages.at(i)->setVisible(true);
            if(check_stage==(i+stage_page*6))
            {
                stages.at(i)->set_check_stat(CHECKED);
            }
            else
            {
                stages.at(i)->set_check_stat(NO_CHECK);
            }
            stages.at(i)->update();
        }
        else
        {
            stages.at(i)->setVisible(false);
        }
    }
    refresh_cycle();
    update_btn_enable();
}
void Page4::jump_page3(void)
{
    qDebug()<<"jump_page3";
    emit page_jump(NEXT_PAGE,4,3);
}
void Page4::jump_page5(void)
{
    qDebug() << "jump_page5";
    dev_file->run_file->check_seg=check_stage;
    emit page_jump(NEXT_PAGE,4,5);
}
void Page4::jump_page6(void)
{
    qDebug() << "jump_page6";
    dev_file->run_file->check_seg=check_stage;
    emit page_jump(NEXT_PAGE,4,6);
}
