#ifndef WIDGET3_H
#define WIDGET3_H

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
class Page3 : public Widget
{
    Q_OBJECT
public:
    explicit Page3(QWidget *parent = 0);
    Button *back_btn;
    Button *step_manage_btn;
    Button *save_btn;
    Button *save_as_btn;
    Button *run_btn;
    QLabel *hotlid_dis;
    QLabel *volume_dis;
    Label *hotlid_edit;
    Label *volume_edit;
    Button *tube;
    Button *block;
    int stage_page;
    QList<STAGE*> stages;
    QList<QLabel*> cycles;
    LeftArrow *turn_left;
    RightArrow *turn_right;
    void refresh_page(void);
    void refresh_stage(void);
    void refresh_cycle(void);
signals:

public slots:
    void jump_page2(void);
    void jump_page4(void);
    void tube_set(void);
    void block_set(void);
    void value_change(void);
    void page_up(void);
    void page_down(void);
    void save_file(void);
    void save_as_file(void);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET3_H
