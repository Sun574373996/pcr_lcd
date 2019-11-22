#include "page2.h"

Page2::Page2(QWidget *parent) : Widget(parent)
{
    QFont font(this->font());
    font.setPointSize(24);
    back_btn=new Button;
    back_btn->setParent(this);
    back_btn->setGeometry(44,6,50,50);
    back_btn->setStyleSheet("background-color:transparent;color:white");
    back_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(back_btn,SIGNAL(clicked()),this,SLOT(jump_page1()));
    rename_btn=new Button;
    rename_btn->setParent(this);
    rename_btn->setGeometry(345,522,170,78);
    rename_btn->setStyleSheet("background-color:transparent;color:white");
    rename_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(rename_btn,SIGNAL(clicked()),this,SLOT(rename_file_open()));
    copy_btn=new Button;
    copy_btn->setParent(this);
    copy_btn->setGeometry(691,522,173,78);
    copy_btn->setStyleSheet("background-color:transparent;color:white");
    copy_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(copy_btn,SIGNAL(clicked()),this,SLOT(copy_file()));
    open_btn=new Button;
    open_btn->setParent(this);
    open_btn->setGeometry(864,521,160,81);
    open_btn->setStyleSheet("background-color:red;color:white;border-style:none");
    open_btn->setText(tr("打开"));
    open_btn->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    open_btn->setFont(font);
    connect(open_btn,SIGNAL(clicked()),this,SLOT(open_file()));
    font.setPointSize(16);
    dir_num=6;
    dir_page_id=0;
    dir_id=-1;
    dir_btn_g=new QButtonGroup;
    for(int i=0;i<dir_num;i++)
    {
        Button *btn=new Button;
        btn->setParent(this);
        btn->setGeometry(107,179+46*i,251,42);
        btn->setStyleSheet("background-color:transparent;");
        btn->set_press_color(QColor(0,155,255,255),CHECK_BTN);
        btn->setEnabled(false);
        dir_btn_l.append(btn);
        dir_btn_g->addButton(btn,i);
        QLabel *name_label=new QLabel;
        name_label->setParent(btn);
        name_label->setFont(font);
        name_label->setGeometry(55,2,205,36);
        name_label->setStyleSheet("background-color:transparent;color:white;");
        dir_name_l.append(name_label);
        QLabel *ico_label =new QLabel;
        ico_label->setParent(btn);
        ico_label->setGeometry(10,2,36,36);
        ico_label->setPixmap(QPixmap(":/image/btn/dir_ico.png"));
        ico_label->setVisible(false);
        dir_ico_l.append(ico_label);
    }
    file_num=6;
    file_page_id=0;
    file_id=-1;
    file_btn_g=new QButtonGroup;
    for(int i=0;i<file_num;i++)
    {
        Button *btn=new Button;
        btn->setParent(this);
        btn->setGeometry(477,179+46*i,437,42);
        btn->setStyleSheet("background-color:transparent;");
        btn->set_press_color(QColor(0,155,255,255),CHECK_BTN);
        btn->setEnabled(true);
        file_btn_l.append(btn);
        file_btn_g->addButton(btn,i);

        QLabel *name_label=new QLabel;
        name_label->setParent(btn);
        name_label->setFont(font);
        name_label->setGeometry(20,2,240,36);
        name_label->setStyleSheet("background-color:transparent;color:white;");
        file_name_l.append(name_label);

        QLabel *time_label =new QLabel;
        time_label->setParent(btn);
        time_label->setGeometry(280,2,185,36);
        time_label->setStyleSheet("background-color:transparent;color:white;");
        file_time_l.append(time_label);
    }
    connect(dir_btn_g,SIGNAL(buttonPressed(int)),this,SLOT(dir_btn_change(int)));
    connect(file_btn_g,SIGNAL(buttonPressed(int)),this,SLOT(file_btn_change(int)));
    dir_up_btn = new UpArrow;
    dir_up_btn->setParent(this);
    dir_up_btn->setGeometry(380,230,40,40);
    dir_down_btn = new DownArrow;
    dir_down_btn->setParent(this);
    dir_down_btn->setGeometry(380,330,40,40);
    file_up_btn = new UpArrow;
    file_up_btn->setParent(this);
    file_up_btn->setGeometry(940,230,40,40);
    file_down_btn = new DownArrow;
    file_down_btn->setParent(this);
    file_down_btn->setGeometry(940,330,40,40);
    connect(dir_up_btn,SIGNAL(clicked()),this,SLOT(dir_up()));
    connect(dir_down_btn,SIGNAL(clicked()),this,SLOT(dir_down()));
    connect(file_up_btn,SIGNAL(clicked()),this,SLOT(file_up()));
    connect(file_down_btn,SIGNAL(clicked()),this,SLOT(file_down()));
    dir_page_dis=new QLabel;
    dir_page_dis->setParent(this);
    dir_page_dis->setGeometry(380,280,40,40);
    dir_page_dis->setAlignment(Qt::AlignCenter);
    dir_page_dis->setFont(font);
    dir_page_dis->setStyleSheet("background-color:red;color:white");
    file_page_dis=new QLabel;
    file_page_dis->setParent(this);
    file_page_dis->setGeometry(940,280,40,40);
    file_page_dis->setAlignment(Qt::AlignCenter);
    file_page_dis->setFont(font);
    file_page_dis->setStyleSheet("background-color:red;color:white");
    this->resize(1024,600);
    QPixmap pixmap = QPixmap(":/image/background/file_manage.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}
void Page2::display_dir(void)
{
    int start = (dir_page_id)*dir_num;
    qDebug()<< "dir num" <<dev_file->dir_list->size();
    for(int i=start;i<(start+dir_num);i++)
    {
        if(i<dev_file->dir_list->size())
        {
            dir_name_l.at(i%dir_num)->setText(dev_file->dir_list->at(i).fileName());
            dir_btn_l.at(i%dir_num)->setEnabled(true);
            dir_ico_l.at(i%dir_num)->setVisible(true);
            if(i==0)
            {
                if(dev_file->usb_detected())
                {
                }
                else{}
            }
            else{}
        }
        else
        {
            dir_name_l.at(i%dir_num)->setText("");
            dir_btn_l.at(i%dir_num)->setEnabled(false);
            dir_ico_l.at(i%dir_num)->setVisible(false);
        }
    }
    if(dev_file->dir_list->size() > start)
    {
        if((0 < dir_id)&&(dir_id <= 5))
        {
            dir_btn_l[dir_id]->set_state(BTN_RELEASE_STAT);
            dir_btn_l[dir_id]->update();
            dir_id=0;
            dir_btn_l[dir_id]->set_state(BTN_PRESS_STAT);
            dir_btn_l[dir_id]->update();
        }
        else if(0==dir_id)
        {
        }
        else
        {
            dir_id=0;
            dir_btn_l[dir_id]->set_state(BTN_PRESS_STAT);
            dir_btn_l[dir_id]->update();
        }
    }
    else
    {
        if((0 <= dir_id)&&(dir_id <= 5))
        {

            dir_btn_l[dir_id]->set_state(BTN_RELEASE_STAT);
            dir_btn_l[dir_id]->update();
        }
        dir_id=-1;
    }
    QString str("%1/%2");
    int page_totle;
    page_totle=(dev_file->dir_list->size()-1)/6+1;
    dir_page_dis->setText(str.arg(dir_page_id+1).arg(page_totle));
    if(dir_page_id>0)
    {
        dir_up_btn->set_state(ARROW_ACTIVE);
        dir_up_btn->setEnabled(true);
    }
    else
    {
        dir_up_btn->set_state(ARROW_NOTACTIVE);
        dir_up_btn->setEnabled(false);
    }
    if((dir_page_id+1)==page_totle)
    {
        dir_down_btn->set_state(ARROW_NOTACTIVE);
        dir_down_btn->setEnabled(false);
    }
    else
    {
        dir_down_btn->set_state(ARROW_ACTIVE);
        dir_down_btn->setEnabled(true);
    }
    display_dir_file();
}
void Page2::display_dir_file(void)
{
    QFileInfoList files_info;
    if(dir_id>=0)
    {
        files_info = dev_file->file_lists->at(dir_page_id*dir_num+dir_id);
    }
    int start = (file_page_id)*file_num;
    for(int i=start;i<(start+file_num);i++)
    {
        if(i<files_info.size())
        {
            file_btn_l.at(i%file_num)->setEnabled(true);
            QString name = files_info.at(i).fileName();
            name.remove(name.size()-4,4);
            file_name_l.at(i%file_num)->setText(name);
            file_time_l.at(i%file_num)->setText(files_info.at(i).lastModified().toString("yyyy-MM-dd HH:mm"));
        }
        else
        {
            file_name_l.at(i%file_num)->setText("");
            file_btn_l.at(i%file_num)->setEnabled(false);
            file_time_l.at(i%file_num)->setText("");
        }
    }
    if(files_info.size() > start)
    {
        if((0 <= file_id)&&(file_id <= 5))
        {
            file_btn_l[file_id]->set_state(BTN_RELEASE_STAT);
            file_btn_l[file_id]->update();
            file_id=-1;
        }
        else
        {
            file_id=-1;
        }
    }
    else
    {
        if((0 <= file_id)&&(file_id <= 5))
        {

            file_btn_l[file_id]->set_state(BTN_RELEASE_STAT);
            file_btn_l[file_id]->update();
        }
        file_id=-1;
    }
    QString str("%1/%2");
    int page_totle;
    page_totle=(dev_file->file_lists->at(dir_page_id*dir_num+dir_id).size()-1)/6+1;
    file_page_dis->setText(str.arg(dir_page_id+1).arg(page_totle));
    if(file_page_id>0)
    {
        file_up_btn->set_state(ARROW_ACTIVE);
        file_up_btn->setEnabled(true);
    }
    else
    {
        file_up_btn->set_state(ARROW_NOTACTIVE);
        file_up_btn->setEnabled(false);
    }
    if((file_page_id+1)==page_totle)
    {
        file_down_btn->set_state(ARROW_NOTACTIVE);
        file_down_btn->setEnabled(false);
    }
    else
    {
        file_down_btn->set_state(ARROW_ACTIVE);
        file_down_btn->setEnabled(true);
    }
}
void Page2::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void Page2::dir_btn_change(int id)
{
    qDebug()<<"dir_btn_change"<<id;
    if(id!=dir_id)
    {
        if((0 <= dir_id)&&(dir_id <= 5))
        {
            dir_btn_l[dir_id]->set_state(BTN_RELEASE_STAT);
            dir_btn_l[dir_id]->update();
        }
        dir_id=id;
        display_dir_file();
    }
}
void Page2::file_btn_change(int id)
{
    qDebug()<<"file_btn_change"<<id;
    if(id!=file_id)
    {
        if((0 <= file_id)&&(file_id <= 5))
        {
            file_btn_l[file_id]->set_state(BTN_RELEASE_STAT);
            file_btn_l[file_id]->update();
        }
        file_id=id;
    }
}
void Page2::copy_file(void)
{
    qDebug()<<"jump to copy file";
    /*
    pmovefile=new PMoveFile(this);
    pmovefile->setGeometry(300,100,400,400);
    this->setEnabled(false);
    pmovefile->show();
    */
}
void Page2::move_file(void)
{

}
void Page2::rename_file_open(void)
{
    qDebug()<<"jump to copy file";

    this->disable_all_activex(this);
    /*
    prenamefile=new PRenameFile();
    prenamefile->setParent(this);
    connect(prenamefile->rename_btn,SIGNAL(clicked()),this,SLOT(rename_file_confirm()));
    connect(prenamefile->cancel_btn,SIGNAL(clicked()),this,SLOT(rename_file_cancel()));
    connect(prenamefile->name_edit,SIGNAL(send_edit_label(Label*,int)),this,SLOT(open_keyboard(Label*,int)));
    prenamefile->show();
    */
}
void Page2::open_file(void)
{
    qDebug()<<"jump to open file";
    if((dir_id>=0)&&(file_id>=0))
    {
        QString path("/home/pcr_files/run_files/");
        dev_file->cur_dir=dev_file->dir_list->at(dir_page_id*6+dir_id).fileName();
        path += dev_file->cur_dir;
        path +="/";
        dev_file->cur_file=dev_file->file_lists->at(dir_page_id*6+dir_id).at(file_page_id*6+file_id).fileName();
        path += dev_file->cur_file;
        qDebug() << path ;
        dev_file->read_file(path);
        jump_page3();
    }
}
void Page2::rename_file_confirm(void)
{
    qDebug()<<"rename_file_confirm";
}
void Page2::rename_file_cancel(void)
{
    qDebug()<<"rename_file_cancel";
  //  prenamefile->deleteLater();
    this->enable_all_activex(this);
}
void Page2::jump_page1(void)
{
    qDebug()<<"jump_page1";
    emit page_jump(NEXT_PAGE,2,1);
}
void Page2::jump_page3(void)
{
    qDebug()<<"jump_page3";
    emit page_jump(NEXT_PAGE,2,3);
}
void Page2::refresh_page(void)
{
    display_dir();
}

void Page2::dir_up(void)
{
    dir_page_id--;
    display_dir();
}
void Page2::dir_down(void)
{
    dir_page_id++;
    display_dir();
}
void Page2::file_up(void)
{
    file_page_id--;
    display_dir_file();
}
void Page2::file_down(void)
{
    file_page_id++;
    display_dir_file();
}
