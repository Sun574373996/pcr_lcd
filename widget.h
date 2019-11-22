#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QWidget>
#include "common.h"
#include "pqwertkb.h"
#include "pnumkb.h"
#include "label.h"
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    void enable_all_activex(QObject *parent_object);
    void disable_all_activex(QObject *parent_object);
    void set_all_font(QFont &font);
    int page_id;
    int keyboard_type;
    QString input_text;
    QWidget *input_widget;
    PQwertKb *qwert_kb;
    PNumKb   *num_kb;
    Label    *edit_label;
    virtual void refresh_page(void);
public slots:
    void open_keyboard(Label *label,int type);
    void close_keyboard(QString str);
signals:
    void page_jump(int mod,int cur,int dst);
};

#endif // WIDGET_H
