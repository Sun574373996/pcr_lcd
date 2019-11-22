#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QButtonGroup>
#include "common.h"
#include "widget.h"
#include "button.h"
#include "arrow.h"
class Page2 : public Widget
{
    Q_OBJECT
public:
    explicit Page2(QWidget *parent = 0);
    Button *back_btn;
    Button *rename_btn;
    Button *copy_btn;
    Button *open_btn;
    QList<Button*> dir_btn_l;
    QButtonGroup *dir_btn_g;
    QList<QLabel*> dir_ico_l;
    QList<QLabel*> dir_name_l;
    QList<Button*> file_btn_l;
    QButtonGroup *file_btn_g;
    QList<QLabel*> file_name_l;
    QList<QLabel*> file_time_l;
    UpArrow *dir_up_btn;
    DownArrow *dir_down_btn;
    QLabel *dir_page_dis;
    UpArrow *file_up_btn;
    DownArrow *file_down_btn;
    QLabel *file_page_dis;
    int dir_num;
    int file_num;
    int dir_page_id;
    int file_page_id;
    int dir_id;
    int file_id;
    void refresh_page(void);
signals:

public slots:
    void display_dir(void);
    void display_dir_file(void);
    void dir_btn_change(int id);
    void file_btn_change(int id);
    void copy_file(void);
    void move_file(void);
    void rename_file_open(void);
    void rename_file_confirm(void);
    void rename_file_cancel(void);
    void open_file(void);
    void jump_page1(void);
    void jump_page3(void);
    void dir_up(void);
    void dir_down(void);
    void file_up(void);
    void file_down(void);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET2_H
