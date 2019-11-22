#include "stage.h"

STAGE::STAGE(int id,QFrame *parent) : QFrame(parent),stage_id(id)
{
    this->check_stat=NO_CHECK;
    QFont font(this->font());
    font.setPixelSize(22);
    stage_name = new QLabel();
    stage_name->setFont(font);
    stage_name->setParent(this);
    QString name("STEP%1");
    stage_name->setAlignment(Qt::AlignCenter);
    stage_name->setText(name.arg(stage_id+1));
    stage_name->setGeometry(0,0,136,40);
    stage_name->setStyleSheet("background-color:rgba(45,45,45,255);color:white; \
                               border-top-left-radius:5px;border-top-right-radius:5px");
    tmp = new Label;
    tmp->set_edit_mod(NUM_EDIT);
    tmp->setFont(font);
    tmp->set_unit("℃");
    tmp->setParent(this);
    tmp->setAlignment(Qt::AlignCenter);
    time = new Label;
    time->set_edit_mod(NUM_EDIT);
    time->setFont(font);
    time->setParent(this);
    time->setAlignment(Qt::AlignCenter);
    tmp->setStyleSheet("background-color:transparent;color:white;");
    time->setStyleSheet("background-color:transparent;color:white;");
}
void STAGE::update_active_value(void)
{
    QString name("STEP%1");
    stage_name->setText(name.arg(stage_id+1));
    QString tmp_str("%1.%2");
    if(dev_file->run_file->segs.size() > stage_id)
    {
        tmp->value=tmp_str.arg(dev_file->run_file->segs.at(stage_id).tmp/10).arg(\
                                dev_file->run_file->segs.at(stage_id).tmp%10);
        tmp_str=tmp->value+tmp->unit;
        tmp->setText(tmp_str);
        tmp_str=("%1:%2");
        time->value=tmp_str.arg(dev_file->run_file->segs.at(stage_id).minite,2,10,QLatin1Char('0')).arg(\
                    dev_file->run_file->segs.at(stage_id).second,2,10,QLatin1Char('0'));
        time->setText(time->value);
    }
}
void STAGE::update_active_value(const QList<FileSeg> &segs)
{
    QString name("STEP%1");
    stage_name->setText(name.arg(stage_id+1));
    QString tmp_str("%1.%2");
    if(segs.size() > stage_id)
    {
        tmp->value=tmp_str.arg(segs.at(stage_id).tmp/10).arg(\
                                segs.at(stage_id).tmp%10);
        tmp_str=tmp->value+tmp->unit;
        tmp->setText(tmp_str);
        tmp_str=("%1:%2");
        time->value=tmp_str.arg(segs.at(stage_id).minite,2,10,QLatin1Char('0')).arg(\
                    segs.at(stage_id).second,2,10,QLatin1Char('0'));
        time->setText(time->value);
    }
}
void STAGE::update_active_pos(void)
{
    int hold_pos;
    if(dev_file->run_file->segs.size() > stage_id)
    {
        hold_pos=dev_file->run_file->segs.at(stage_id).tmp*16/100;
        hold_pos=250-hold_pos;
        tmp->setGeometry(46,hold_pos-40,80,40);
        time->setGeometry(46,hold_pos+5,80,40);
    }
}
void STAGE::update_active_pos(const QList<FileSeg> &segs)
{
    int hold_pos;
    if(segs.size() > stage_id)
    {
        hold_pos=segs.at(stage_id).tmp*16/100;
        hold_pos=250-hold_pos;
        tmp->setGeometry(46,hold_pos-40,80,40);
        time->setGeometry(46,hold_pos+5,80,40);
    }
}
void STAGE::enable_all_activex(QObject *parent_object)
{
    QList<QWidget *> child_widget = parent_object->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
    for (int i=0;i<child_widget.size();i++)
    {
        child_widget.at(i)->setEnabled(true);
    }
}
void STAGE::disable_all_activex(QObject *parent_object)
{
    QList<QWidget *> child_widget = parent_object->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
    for (int i=0;i<child_widget.size();i++)
    {
        child_widget.at(i)->setEnabled(false);
    }
}
void STAGE::set_all_font(QFont &font)
{
    QList<QWidget *> child_widget = this->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
    for (int i=0;i<child_widget.size();i++)
    {
        child_widget.at(i)->setFont(font);
    }
}
void STAGE::set_check_stat(int stat)
{
    if(stat==this->check_stat)
    {

    }
    else
    {
        this->check_stat=stat;
    }
}
void STAGE::paintEvent(QPaintEvent *event)
{
    //qDebug()<< "paint"<<stage_id;
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QColor(0,0,0,0));
    painter.setBrush(QColor(39,113,248,100));
    QRect rect = this->rect();
    rect.setTop(42);
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 5, 5);
    if(dev_file->run_file->segs.size() > stage_id)
    {
        int start_pos,hold_pos;
        painter.setRenderHint(QPainter::Antialiasing,true);
        rect.setTop(260);
        painter.setBrush(QColor(20,108,228,255));
        painter.drawRoundedRect(rect, 5, 5);
        if(stage_id==0)
        {
            start_pos=250;
        }
        else
        {
            start_pos=dev_file->run_file->segs.at(stage_id-1).tmp*16/100;
            start_pos=250-start_pos;
        }
        hold_pos=dev_file->run_file->segs.at(stage_id).tmp*16/100;
        hold_pos=250-hold_pos;
        QPoint points[5]={QPoint(0,290),QPoint(0,start_pos),QPoint(36,hold_pos),QPoint(135,hold_pos),QPoint(135,290)};
        painter.drawPolygon(points,5);
        if(check_stat==CHECKED)
        {
            painter.setPen(QColor(0,0,0,0));
            painter.setBrush(QColor(113,196,227,100));
            rect = this->rect();
            rect.setTop(42);
            rect.setWidth(rect.width() - 1);
            rect.setHeight(rect.height() - 1);
            painter.drawRoundedRect(rect, 5, 5);
        }
    }
}

void STAGE::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit stage_pressed(stage_id);
}
