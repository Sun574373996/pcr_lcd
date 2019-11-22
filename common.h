#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QList>
#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QByteArray>
#include <QDateTime>
#include <QPaintEvent>
#include "communicate.h"
#include "dev_file.h"
#include "beep.h"

#define NEXT_PAGE   0
#define PRE_PAGE    1

#define CHECK_BTN   0
#define CLICK_BTN   1
#define TOGGLE_BTN  2

#define BTN_RELEASE_STAT     0
#define BTN_PRESS_STAT       1

#define NO_EDIT     0
#define NUM_EDIT    1
#define QWERT_EDIT  2

#define NO_CHECK    0
#define CHECKED     1

#define ARROW_ACTIVE    1
#define ARROW_NOTACTIVE  0

extern int top_view_x;
extern int top_view_y;



extern PortCtrl *ctrl_com;
extern DevFile *dev_file;
extern BEEP *beep;
extern QList<FileSeg> back_segs;
extern QList<FileCycle> back_cycles;
#endif // COMMON_H
