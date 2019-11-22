#ifndef WIDGET4_H
#define WIDGET4_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QButtonGroup>
#include "common.h"
#include "widget.h"
#include "popups.h"
#include "button.h"
#include "label.h"
#include "stage.h"
#include "arrow.h"
class Page4 : public Widget
{
    Q_OBJECT
public:
    explicit Page4(QWidget *parent = 0);
    Button *back_btn;
    Button *option_btn;
    Button *jump_btn;
    Button *del_cycle_btn;
    Button *add_stage_btn;
    Button *del_stage_btn;
    Button *finish_btn;
    int stage_page;
    int check_stage;
    QList<STAGE*> stages;
    QList<QLabel*> cycles;
    LeftArrow *turn_left;
    RightArrow *turn_right;
    void refresh_page(void);
    void back_up_file(void);
    void refresh_stage(void);
    void refresh_cycle(void);
signals:

public slots:
    void jump_page3(void);
    void jump_page5(void);
    void jump_page6(void);
    void update_check_stage(int check_id);
    void update_btn_enable(void);
    void back_page(void);
    void modify_more(void);
    void set_cycle(void);
    void del_cycle(void);
    void add_stage(void);
    void del_stage(void);
    void page_up(void);
    void page_down(void);
    void finish_manage_step(void);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET4_H
