#include "beep.h"


BEEP::BEEP(QObject *parent): QObject(parent)
{
    beep_cnt=0;
    beep_stat=0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(beep_ctrl()));
}
void BEEP::beep_one(void)
{
    if(0==beep_cnt)
    {
        fd = open("dev/led",O_RDWR|O_NDELAY);
        if(fd<0)
        {
            return;
        }
        timer.start(300);
        ioctl(fd,1);
        beep_stat=BEEP_ON;
    }
    else
    {

    }
    beep_cnt++;
}

void BEEP::beep_ctrl(void)
{
    if(beep_stat==BEEP_IDLE)
    {

    }
    else if(beep_stat==BEEP_ON)
    {
        ioctl(fd,0);
        beep_stat=BEEP_OFF;
        timer.start(200);
    }
    else if(beep_stat==BEEP_OFF)
    {
        if(--beep_cnt>0)
        {
            timer.start(300);
            ioctl(fd,1);
            beep_stat=BEEP_ON;
        }
        else
        {
            close(fd);
            beep_stat=BEEP_IDLE;
        }
    }
    else
    {
    }

}
