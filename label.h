#ifndef LABEL_H
#define LABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "common.h"

class Label : public QLabel
{
    Q_OBJECT
public:
    Label(QWidget *parent = 0);
    int max_val;
    int min_val;
    int edit_mod;
    QString unit;
    QString value;
    void set_edit_mod(int mod);
    void set_unit(const QString &str);
    int set_value(const QString &str);
    QString get_value(void);
    int input_str(QString &str);
protected:
    void mousePressEvent(QMouseEvent *ev);
private:

signals:
    void send_edit_label(Label *label,int type);
    void value_change(QString str);
};

#endif // LABEL_H
