#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>
#include <QSemaphore>
#include <QTimer>
#include <QByteArray>
#include <QDebug>

class PortCom : public QObject
{
    Q_OBJECT
public:
    explicit PortCom(QString name,QObject *parent = 0);
    QSerialPort *serial_port;
    QTimer *timer;
    QString port_name;
    QByteArray write_data;
    QByteArray read_datas;
    int retry_times;
signals:
    void dispatch_recv_data(QByteArray &data);
public slots:
    void open_com(void);
    void transmit_data(QByteArray &data);
    void wait_transmit_data(QByteArray &data);
    void retry_transmit_data(void);
    void recv_data(void);
    void analysis_data(QByteArray &data);
};
class PortCtrl : public QObject
{
    Q_OBJECT
public:
    QThread ComThread;
    PortCom *port_com;
    explicit PortCtrl(QObject *parent = 0);

    QByteArray wait_send_msg(QByteArray &msg);
    void send_msg(QByteArray &msg);
signals:
    void transmit_msg(QByteArray &msg);
    void wait_transmit_msg(QByteArray &msg);
public slots:
    void dispatch_recv_msg(QByteArray &msg);

};
#endif // COMMUNICATE_H
