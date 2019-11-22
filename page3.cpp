#include "page3.h"

Page3::Page3(QWidget *parent) : Widget(parent)
{
    back_btn=new Button;
    back_btn->setParent(this);
    back_btn->setGeometry(44,6,50,50);
    back_btn->setStyleSheet("background-color:transparent");
    back_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(back_btn,SIGNAL(clicked()),this,SLOT(jump_page2()));
    QFont font(this->font());
    font.setPixelSize(30);
    step_manage_btn=new Button;
    step_manage_btn->setParent(this);
    step_manage_btn->setText("步骤管理");
    step_manage_btn->setFont(font);
    step_manage_btn->setGeometry(0,521,171,76);
    step_manage_btn->setStyleSheet("background-color:transparent;color:white");
    step_manage_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(step_manage_btn,SIGNAL(clicked(bool)),this,SLOT(jump_page4()));

    save_btn=new Button;
    save_btn->setParent(this);
    save_btn->setText("保存");
    save_btn->setFont(font);
    save_btn->setGeometry(172,521,171,76);
    save_btn->setStyleSheet("background-color:transparent;color:white");
    save_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(save_btn,SIGNAL(clicked(bool)),this,SLOT(save_file()));
    save_as_btn=new Button;
    save_as_btn->setParent(this);
    save_as_btn->setFont(font);
    save_as_btn->setText("另存为");
    save_as_btn->setGeometry(344,521,173,76);
    save_as_btn->setStyleSheet("background-color:transparent;color:white");
    connect(save_as_btn,SIGNAL(clicked(bool)),this,SLOT(save_as_file()));
    save_as_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);

    run_btn=new Button;
    run_btn->setParent(this);
    run_btn->setFont(font);
    run_btn->setText("直接运行");
    run_btn->setGeometry(865,521,158,76);
    run_btn->setStyleSheet("background-color:transparent;color:white");
    run_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);

    font.setPixelSize(24);
    hotlid_dis  =new QLabel("hotlid");
    hotlid_dis->setParent(this);
    hotlid_dis->setAlignment(Qt::AlignCenter);
    hotlid_dis->setFont(font);
    hotlid_dis->setStyleSheet("background-color:rgba(45,45,45,255);color:white");
    hotlid_dis->setGeometry(94,75,136,40);
    volume_dis  =new QLabel("volume");
    volume_dis->setParent(this);
    volume_dis->setAlignment(Qt::AlignCenter);
    volume_dis->setFont(font);
    volume_dis->setStyleSheet("background-color:rgba(45,45,45,255);color:white");
    volume_dis->setGeometry(234,75,136,40);

    hotlid_edit =new Label;
    hotlid_edit->setParent(this);
    hotlid_edit->setGeometry(94,115,136,50);
    hotlid_edit->setFont(font);
    hotlid_edit->edit_mod=NUM_EDIT;
    hotlid_edit->set_unit("℃");
    hotlid_edit->setAlignment(Qt::AlignCenter);
    hotlid_edit->setStyleSheet("background-color:black;color:white");
    connect(hotlid_edit,SIGNAL(send_edit_label(Label*,int)),this,SLOT(open_keyboard(Label*,int)));
    connect(hotlid_edit,SIGNAL(value_change(QString)),this,SLOT(value_change()));
    volume_edit =new Label;
    volume_edit->setParent(this);
    volume_edit->setGeometry(234,115,136,50);
    volume_edit->setFont(font);
    volume_edit->edit_mod=NUM_EDIT;
    volume_edit->set_unit("uL");
    volume_edit->setAlignment(Qt::AlignCenter);
    volume_edit->setStyleSheet("background-color:black;color:white");
    connect(volume_edit,SIGNAL(send_edit_label(Label*,int)),this,SLOT(open_keyboard(Label*,int)));
    connect(volume_edit,SIGNAL(value_change(QString)),this,SLOT(value_change()));

    tube =new Button;
    tube->setParent(this);
    tube->setGeometry(600,85,120,60);
    tube->setText("Tube");
    tube->setFont(font);
    tube->setStyleSheet("background-color:black;color:white");
    tube->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(tube,SIGNAL(clicked(bool)),this,SLOT(tube_set()));
    block =new Button;
    block->setParent(this);
    block->setGeometry(800,85,120,60);
    block->setText("Block");
    block->setFont(font);
    block->setStyleSheet("background-color:black;color:white");
    block->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(block,SIGNAL(clicked(bool)),this,SLOT(block_set()));
    turn_left = new LeftArrow;
    turn_right = new RightArrow;
    turn_left->setParent(this);
    turn_left->setGeometry(25,300,50,50);
    turn_right->setParent(this);
    turn_right->setGeometry(950,300,50,50);
    connect(turn_left,SIGNAL(clicked()),this,SLOT(page_up()));
    connect(turn_right,SIGNAL(clicked()),this,SLOT(page_down()));
    font.setPixelSize(20);
    for(int i=0;i<6;i++)
    {
        STAGE *stage = new STAGE(i);
        stage->setParent(this);
       // stage->setStyleSheet("background-color:blue;color:white");
        stage->setGeometry(94+i*140,170,136,300);
        stages.append(stage);
        connect(stage->tmp,SIGNAL(send_edit_label(Label*,int)),this,SLOT(open_keyboard(Label*,int)));
        connect(stage->time,SIGNAL(send_edit_label(Label*,int)),this,SLOT(open_keyboard(Label*,int)));
        connect(stage->tmp,SIGNAL(value_change(QString)),this,SLOT(value_change()));
        connect(stage->time,SIGNAL(value_change(QString)),this,SLOT(value_change()));
        QLabel *label = new QLabel;
        label->setParent(this);
        cycles.append(label);
        label->setFont(font);
        label->setVisible(false);
        label->setStyleSheet("background-color:rgba(130,130,130,255);color:white");
    }

    this->resize(1024,600);
    QPixmap pixmap = QPixmap(":/image/background/file_dis.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}

void Page3::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void Page3::jump_page2(void)
{
    qDebug()<<"jump_page2";
    emit page_jump(NEXT_PAGE,3,2);
}
void Page3::jump_page4(void)
{
    qDebug()<<"jump_page4";
    emit page_jump(NEXT_PAGE,3,4);
}
void Page3::refresh_page(void)
{
    stage_page=0;
    QString str("%1.%2");
    hotlid_edit->set_value(str.arg(dev_file->run_file->hotlid_tmp/10).arg(dev_file->run_file->hotlid_tmp%10));
    str="%1";
    volume_edit->set_value(str.arg(dev_file->run_file->volume));
    if(dev_file->run_file->run_type)
    {
        block->setStyleSheet("background-color:rgba(20,108,228,255);color:white;border-radius:5px");
        block->update();
        tube->setStyleSheet("background-color:black;color:white;border-radius:5px");
        tube->update();
    }
    else
    {
        tube->setStyleSheet("background-color:rgba(20,108,228,255);color:white;border-radius:5px");
        tube->update();
        block->setStyleSheet("background-color:black;color:white;border-radius:5px");
        block->update();
    }
    turn_left->setEnabled(false);
    turn_left->set_state(ARROW_NOTACTIVE);
    if(dev_file->run_file->segs.size()>6)
    {
        turn_right->setEnabled(true);
        turn_right->set_state(ARROW_ACTIVE);
    }
    else
    {
        turn_right->setEnabled(false);
        turn_right->set_state(ARROW_NOTACTIVE);
    }
    refresh_stage();
    refresh_cycle();
}
void Page3::refresh_stage(void)
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
void Page3::refresh_cycle(void)
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
        if(0==left_pos&&0==right_pos)
        {}
        else
        {
            top_pos=471;
            if((i+1)<dev_file->run_file->cycles.size())
            {
                if(dev_file->run_file->cycles.at(i+1).begin_seg<end)
                {
                    top_pos=496;
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
    for(int i=index;i<6;i++)
    {
        cycles.at(i)->setVisible(false);
    }
}
void Page3::tube_set(void)
{
    if(dev_file->run_file->run_type)
    {
        tube->setStyleSheet("background-color:rgba(20,108,228,255);color:white;border-radius:5px");
        tube->update();
        block->setStyleSheet("background-color:black;color:white;border-radius:5px");
        block->update();
        dev_file->run_file->run_type=0;
    }
}
void Page3::block_set(void)
{
    if(0==dev_file->run_file->run_type)
    {
        block->setStyleSheet("background-color:rgba(20,108,228,255);color:white;border-radius:5px");
        block->update();
        tube->setStyleSheet("background-color:black;color:white;border-radius:5px");
        tube->update();
        dev_file->run_file->run_type=1;
    }
}
void Page3::value_change(void)
{
    qDebug() << "value change";
    int hotlid=0;
    int volume=0;
    int tmp=0;
    int minite=0;
    int second=0;
    FileSeg seg;

    hotlid=this->hotlid_edit->value.toFloat()*10;
    if(hotlid!=dev_file->run_file->hotlid_tmp)
    {
        dev_file->run_file->hotlid_tmp=hotlid;
        return;
    }
    volume=this->volume_edit->value.toInt();
    if(volume!=dev_file->run_file->volume)
    {
        dev_file->run_file->volume=volume;
        return;
    }
    for(int i=0;i<6;i++)
    {
        if(dev_file->run_file->segs.size()>(stage_page*6+i))
        {
            seg = dev_file->run_file->segs.at(stage_page*6+i);
            tmp=(int)(this->stages.at(i)->tmp->value.toFloat()*10);
            if(tmp != seg.tmp)
            {
                seg.tmp=tmp;
                dev_file->run_file->segs.replace(stage_page*6+i,seg);
                if(i<5)
                {
                    this->stages.at(i)->update_active_pos();
                    this->stages.at(i)->update();
                    this->stages.at(i+1)->update();
                }
                else
                {
                    this->stages.at(i)->update_active_pos();
                    this->stages.at(i)->update();
                }
                break;
            }
            const QStringList& time=this->stages.at(i)->time->value.split(':');
            minite=time.at(0).toInt();
            second=time.at(1).toInt();
            if(minite!=seg.minite||second!=seg.second)
            {
                seg.minite=minite;
                seg.second=second;
                dev_file->run_file->segs.replace(stage_page*6+i,seg);
                break;
            }
        }
        else
        {
        }
    }
}
void Page3::page_up(void)
{
    stage_page--;
    if(stage_page>0)
    {
        turn_left->setEnabled(true);
        turn_left->set_state(ARROW_ACTIVE);
    }
    else
    {
        turn_left->setEnabled(false);
        turn_left->set_state(ARROW_NOTACTIVE);
    }
    if(dev_file->run_file->segs.size()>6*(stage_page+1))
    {
        turn_right->setEnabled(true);
        turn_right->set_state(ARROW_ACTIVE);
    }
    else
    {
        turn_right->setEnabled(false);
        turn_right->set_state(ARROW_NOTACTIVE);
    }
    refresh_stage();
    refresh_cycle();
    qDebug() << "Page3::page_up";
}
void Page3::page_down(void)
{
    stage_page++;
    if(stage_page>0)
    {
        turn_left->setEnabled(true);
        turn_left->set_state(ARROW_ACTIVE);
    }
    else
    {
        turn_left->setEnabled(false);
        turn_left->set_state(ARROW_NOTACTIVE);
    }
    if(dev_file->run_file->segs.size()>6*(stage_page+1))
    {
        turn_right->setEnabled(true);
        turn_right->set_state(ARROW_ACTIVE);
    }
    else
    {
        turn_right->setEnabled(false);
        turn_right->set_state(ARROW_NOTACTIVE);
    }
    refresh_stage();
    refresh_cycle();
    qDebug() << "Page3::page_down";
}
void Page3::save_file(void)
{
    qDebug()<< "save_file";
    QString path("/home/pcr_files/run_files/");
    path += dev_file->cur_dir;
    path +="/";
    path += dev_file->cur_file;
    qDebug() << path ;
    dev_file->write_file(path);
}
void Page3::save_as_file(void)
{
    qDebug()<< "save_as_file";
}
