#ifndef WIDGET5_H
#define WIDGET5_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include "button.h"
#include "widget.h"
#include "common.h"
class Page5 : public Widget
{
    Q_OBJECT
public:
    explicit Page5(QWidget *parent = 0);
    int index;
    int max_grad;
    int grad_rang_visiable;
    FileSeg seg;
    Button *btn_back;
    Button *btn_cancel;
    Button *btn_confirm;
    QLabel *title_label;
    QLabel *time;
    QLabel *tmp;
    QLabel *speed;
    QLabel *grad;
    QLabel *grad_rang;
    Label *time_edit;
    Label *tmp_edit;
    Label *speed_edit;
    Label *grad_edit;
    Label *grad_rang_edit;
    QLabel *grads_tmp;
    void refresh_page(void);
signals:

public slots:
    void jump_page4(void);
    void confirm_change(void);
    void value_change(void);
    void change_grad_rang_stat(void);
    void display_grad_rang(void);
protected:
    void paintEvent(QPaintEvent *event);

};


#endif // WIDGET5_H
