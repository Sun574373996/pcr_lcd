#ifndef ARROW_H
#define ARROW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include "common.h"
class UpArrow : public QPushButton
{
    Q_OBJECT
public:
    UpArrow(QWidget *parent = 0);
    void set_state(int stat);
    int get_state(void);
protected:
    void paintEvent(QPaintEvent *event);
private:
    int state;
};

class DownArrow : public QPushButton
{
    Q_OBJECT
public:
    DownArrow(QWidget *parent = 0);
    void set_state(int stat);
    int get_state(void);
protected:
    void paintEvent(QPaintEvent *event);
private:
    int state;
};

class LeftArrow : public QPushButton
{
    Q_OBJECT
public:
    LeftArrow(QWidget *parent = 0);
    void set_state(int stat);
    int get_state(void);
protected:
    void paintEvent(QPaintEvent *event);
private:
    int state;
};
class RightArrow : public QPushButton
{
    Q_OBJECT
public:
    RightArrow(QWidget *parent = 0);
    void set_state(int stat);
    int get_state(void);
protected:
    void paintEvent(QPaintEvent *event);
private:
    int state;
};
#endif // ARROW_H
