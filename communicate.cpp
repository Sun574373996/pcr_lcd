#include "communicate.h"

QByteArray g_recv_ask;
QSemaphore g_sem_com;


PortCom::PortCom(QString name,QObject *parent): QObject(parent),port_name(name)
{

    timer = new QTimer;
    qDebug() << "new  serial_port " ;
    connect(timer,SIGNAL(timeout()),this,SLOT(retry_transmit_data()));
    open_com();
}
void PortCom::open_com(void)
{
    serial_port = new QSerialPort(port_name);

    qDebug() << "find device " ;
    serial_port->close();
    if(serial_port->open(QIODevice::ReadWrite))
    {
        serial_port->setBaudRate(QSerialPort::Baud9600);
        serial_port->setDataBits(QSerialPort::Data8);
        serial_port->setFlowControl(QSerialPort::NoFlowControl);
        serial_port->setParity(QSerialPort::NoParity);
        serial_port->setStopBits(QSerialPort::OneStop);
        serial_port->setBreakEnabled(false);
        connect(serial_port,SIGNAL(readyRead()),this,SLOT(recv_data()));
        qDebug()<< "com open successed";
    }
    else
    {
        qDebug()<< "com open fail";
    }
    return;
}

void PortCom::transmit_data(QByteArray &msg)
{
    serial_port->write(msg);
}
void PortCom::wait_transmit_data(QByteArray &msg)
{
    Q_UNUSED(msg);
    serial_port->write(write_data);
    retry_times=2;
    timer->start(200);
}
void PortCom::retry_transmit_data(void)
{

    serial_port->write(write_data);
    if(retry_times>0)
    {
        retry_times--;
        timer->start(200);
    }
    else
    {
        timer->stop();
        g_recv_ask.clear();
        g_sem_com.release();
        qDebug()<< "recv time out";
    }
}
void PortCom::recv_data(void)
{
    static int i;
    read_datas=serial_port->readAll();
    if(serial_port->isWritable())
    {
        qDebug()<< "write_enable";
        qint64 error=serial_port->write(read_datas);
        qDebug()<< "write_error"<<error;
    }
    else
    {
        qDebug()<< "write_disable";
    }

    i++;
    qDebug()<< read_datas << i;
}
void PortCom::analysis_data(QByteArray &msg)
{
    Q_UNUSED(msg);
}
PortCtrl::PortCtrl(QObject *parent) : QObject(parent)
{

    port_com = new PortCom("ttymxc1");
    port_com->moveToThread(&ComThread);
    port_com->serial_port->moveToThread(&ComThread);
    port_com->timer->moveToThread(&ComThread);
    ComThread.start();

    connect(this,SIGNAL(transmit_msg(QByteArray&)),port_com,SLOT(transmit_data(QByteArray&)));
    connect(this,SIGNAL(wait_transmit_msg(QByteArray&)),port_com,SLOT(wait_transmit_data(QByteArray&)));
    connect(port_com,SIGNAL(dispatch_recv_data(QByteArray&)),this,SLOT(dispatch_recv_msg(QByteArray&)));
}

QByteArray PortCtrl::wait_send_msg(QByteArray &msg)
{
    emit wait_transmit_msg(msg);
    g_sem_com.acquire();
    return g_recv_ask;
}

void PortCtrl::send_msg(QByteArray &msg)
{
    emit transmit_msg(msg);
}
void PortCtrl::dispatch_recv_msg(QByteArray &msg)
{
    Q_UNUSED(msg);
}
