#ifndef STAGE_H
#define STAGE_H

#include <QObject>
#include <QWidget>
#include "common.h"
#include "label.h"
#include <QFrame>
#include <QPainter>
class STAGE : public QFrame
{
    Q_OBJECT
public:
    explicit STAGE(int id,QFrame *parent = 0);
    void enable_all_activex(QObject *parent_object);
    void disable_all_activex(QObject *parent_object);
    void set_all_font(QFont &font);
    int stage_id;
    QLabel *stage_name;
    Label *tmp;
    Label *time;
    int check_stat;
    void init_active(void);
    void set_check_stat(int stat);
public slots:
    void update_active_value(void);
    void update_active_pos(void);
    void update_active_value(const QList<FileSeg> &segs);
    void update_active_pos(const QList<FileSeg> &segs);
signals:
    void stage_pressed(int id);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

};

#endif // STAGE_H
