#ifndef BEEP_H
#define BEEP_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BEEP_IDLE 0
#define BEEP_ON   1
#define BEEP_OFF  2

class BEEP : public QObject
{
    Q_OBJECT
public:
    explicit BEEP(QObject *parent = 0);
    QTimer timer;
    void beep_one(void);
signals:

public slots:
    void beep_ctrl(void);
private:
    int beep_cnt;
    int beep_stat;
    int fd;
};


#endif // BEEP_H
