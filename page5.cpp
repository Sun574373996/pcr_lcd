#include "page5.h"

Page5::Page5(QWidget *parent) : Widget(parent)
{
    QFont font(this->font());
    font.setPointSize(24);
    title_label=new QLabel(tr("高级选项"));
    title_label->setParent(this);
    title_label->setStyleSheet("background-color:transparent;color:white");
    title_label->setGeometry(430,0,180,65);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setFont(font);
    btn_back = new Button;
    btn_back=new Button;
    btn_back->setParent(this);
    btn_back->setGeometry(44,6,50,50);
    btn_back->setStyleSheet("background-color:green;color:white");
    btn_back->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(btn_back,SIGNAL(clicked()),this,SLOT(jump_page4()));
    btn_cancel = new Button;
    btn_cancel->setParent(this);
    btn_cancel->setText(tr("取消"));
    btn_cancel->setGeometry(0,521,255,79);
    btn_cancel->setStyleSheet("background-color:blue;color:white");
    btn_cancel->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(jump_page4()));
    btn_confirm = new Button;
    btn_confirm->setParent(this);
    btn_confirm->setText(tr("确定"));
    btn_confirm->setGeometry(770,521,255,79);
    btn_confirm->setStyleSheet("background-color:red;color:white");
    btn_confirm->set_press_color(QColor(0,0,0,20),CLICK_BTN);
    connect(btn_confirm,SIGNAL(clicked()),this,SLOT(confirm_change()));
    font.setPointSize(20);

    time = new QLabel;
    time->setParent(this);
    time->setFont(font);
    time->setText(tr("拓展时间"));
    time->setGeometry(300,127,200,34);
    time->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    time->setStyleSheet("background-color:red;color:white");
    tmp = new QLabel;
    tmp->setParent(this);
    tmp->setFont(font);
    tmp->setText(tr("拓展温度"));
    tmp->setGeometry(300,203,200,34);
    tmp->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    tmp->setStyleSheet("background-color:red;color:white");
    speed = new QLabel;
    speed->setParent(this);
    speed->setFont(font);
    speed->setText(tr("速度"));
    speed->setGeometry(300,278,200,34);
    speed->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    speed->setStyleSheet("background-color:red;color:white");
    grad = new QLabel;
    grad->setParent(this);
    grad->setFont(font);
    grad->setText(tr("梯度"));
    grad->setGeometry(300,355,200,34);
    grad->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    grad->setStyleSheet("background-color:red;color:white");
    grad_rang = new QLabel;
    grad_rang->setParent(this);
    grad_rang->setFont(font);
    grad_rang->setText(tr("梯度范围"));
    grad_rang->setGeometry(300,433,200,34);
    grad_rang->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    grad_rang->setStyleSheet("background-color:red;color:white");
    time_edit = new Label;
    time_edit->setGeometry(565,127,158,34);
    time_edit->set_edit_mod(NUM_EDIT);
    time_edit->setFont(font);
    time_edit->set_unit("s");
    time_edit->setParent(this);
    time_edit->setAlignment(Qt::AlignCenter);
    time_edit->setStyleSheet("background-color:green;color:white;");
    connect(time_edit,SIGNAL(send_edit_label(Label*,int)),this,SLOT(open_keyboard(Label*,int)));
    connect(time_edit,SIGNAL(value_change(QString)),this,SLOT(value_change()));
    tmp_edit = new Label;
    tmp_edit->setGeometry(565,203,158,34);
    tmp_edit->set_edit_mod(NUM_EDIT);
    tmp_edit->setFont(font);
    tmp_edit->set_unit("℃");
    tmp_edit->setParent(this);
    tmp_edit->setAlignment(Qt::AlignCenter);
    tmp_edit->setStyleSheet("background-color:green;color:white;");
    connect(tmp_edit,SIGNAL(send_edit_label(Label*,int)),this,SLOT(open_keyboard(Label*,int)));
    connect(tmp_edit,SIGNAL(value_change(QString)),this,SLOT(value_change()));
    speed_edit = new Label;
    speed_edit->setGeometry(565,278,158,34);
    speed_edit->set_edit_mod(NUM_EDIT);
    speed_edit->setFont(font);
    speed_edit->set_unit("℃/s");
    speed_edit->setParent(this);
    speed_edit->setAlignment(Qt::AlignCenter);
    speed_edit->setStyleSheet("background-color:green;color:white;");
    connect(speed_edit,SIGNAL(send_edit_label(Label*,int)),this,SLOT(open_keyboard(Label*,int)));
    connect(speed_edit,SIGNAL(value_change(QString)),this,SLOT(value_change()));
    grad_edit = new Label;
    grad_edit->setGeometry(565,355,158,34);
    grad_edit->set_edit_mod(NUM_EDIT);
    grad_edit->setFont(font);
    grad_edit->set_unit("℃");
    grad_edit->setParent(this);
    grad_edit->setAlignment(Qt::AlignCenter);
    grad_edit->setStyleSheet("background-color:green;color:white;");
    connect(grad_edit,SIGNAL(send_edit_label(Label*,int)),this,SLOT(open_keyboard(Label*,int)));
    connect(grad_edit,SIGNAL(value_change(QString)),this,SLOT(value_change()));
    font.setPointSize(18);
    grad_rang_edit = new Label;
    grad_rang_edit->setGeometry(565,433,158,34);
    grad_rang_edit->set_edit_mod(NUM_EDIT);
    grad_rang_edit->setFont(font);
    grad_rang_edit->set_unit("℃");
    grad_rang_edit->setParent(this);
    grad_rang_edit->setAlignment(Qt::AlignCenter);
    grad_rang_edit->setStyleSheet("background-color:green;color:white;");
    connect(grad_rang_edit,SIGNAL(send_edit_label(Label*,int)),this,SLOT(change_grad_rang_stat()));
    font.setPointSize(12);
    grads_tmp = new QLabel;
    grads_tmp->setGeometry(80,480,840,30);
    grads_tmp->setFont(font);
    grads_tmp->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    grads_tmp->setStyleSheet("background-color:green;color:white;");
    grads_tmp->setParent(this);

    this->resize(1024,600);
    QPixmap pixmap = QPixmap(":/image/background/method_more.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);
}
void Page5::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void Page5::jump_page4(void)
{
    qDebug()<<"jump_page4";

    emit page_jump(NEXT_PAGE,5,4);
}
void Page5::confirm_change(void)
{
    qDebug()<<"jump_page4";
    dev_file->run_file->segs.replace(index,seg);
    emit page_jump(NEXT_PAGE,5,4);
}
void Page5::value_change(void)
{
    qDebug()<<"value_change";
    int time = this->time_edit->value.toInt();
    seg.ext_minite=time/60;
    seg.ext_second=time%60;
    seg.ext_tmp=this->tmp_edit->value.toFloat();
    seg.speed=this->speed_edit->value.toFloat();
    seg.grad=this->grad_edit->value.toInt();
    QString str("%1.%2~%3.%4");
    max_grad = seg.tmp+seg.grad*10;
    if(max_grad>999)
    {
        max_grad=999;
    }
    grad_rang_edit->set_value(str.arg(seg.tmp/10)
                              .arg(seg.tmp%10)
                                   .arg(max_grad/10)
                                        .arg(max_grad%10));
    dev_file->run_file->segs.replace(index,seg);

}
void Page5::change_grad_rang_stat(void)
{
    if(0==grad_rang_visiable)
    {
        grad_rang_visiable=1;
    }
    else
    {
        grad_rang_visiable=0;
    }
    display_grad_rang();
}
void Page5::display_grad_rang(void)
{
    if(0==grad_rang_visiable)
    {
        grads_tmp->setVisible(false);
    }
    else
    {
        QString dis;
        QString str("%1.%2");
        for(int i=0;i<12;i++)
        {
            dis+=str.arg(seg.tmp/10).arg(seg.tmp%10);
            dis+="℃";
            dis+="    ";
        }
        grads_tmp->setText(dis);
        grads_tmp->setVisible(true);
    }
}
void Page5::refresh_page(void)
{
    index=dev_file->run_file->check_seg;
    seg = dev_file->run_file->segs.at(index);
    QString str("%1");
    time_edit->set_value(str.arg(seg.ext_minite*60+seg.ext_second));
    grad_edit->set_value(str.arg(seg.grad));
    str="%1.%2";
    tmp_edit->set_value(str.arg(seg.ext_tmp/10).arg(seg.ext_tmp%10));
    speed_edit->set_value(str.arg(seg.speed/10).arg(seg.speed%10));

    max_grad = seg.tmp+seg.grad*10;
    if(max_grad>999)
    {
        max_grad=999;
    }
    str="%1.%2~%3.%4";
    grad_rang_edit->set_value(str.arg(seg.tmp/10)
                              .arg(seg.tmp%10)
                                   .arg(max_grad/10)
                                        .arg(max_grad%10));
    grad_rang_visiable=0;
    grads_tmp->setVisible(false);
}
