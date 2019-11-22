#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include "common.h"
class Button : public QPushButton
{
    Q_OBJECT
public:
    Button(QWidget *parent = 0);
    QString image_path;
    QColor press_color;
    void set_press_color(const QColor &color,int model);
    void set_image_path(const QString &path,int model);
    void set_state(int stat);
    int get_state(void);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    int state;
    int mod;
};

#endif // BUTTON_H
