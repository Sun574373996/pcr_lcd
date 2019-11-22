#ifndef DEV_FILE_H
#define DEV_FILE_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileSystemWatcher>
#include <QProcess>
#include <QDateTime>
class FileSeg
{
public:
    int tmp;
    int minite;
    int second;
    int speed;
    int ext_tmp;
    int ext_minite;
    int ext_second;
    int grad;
    int ext_grad[5];
};
class FileCycle
{
public:
    int begin_seg;
    int end_seg;
    int num;
};

class RunFile : public QObject
{
    Q_OBJECT
public:
    explicit RunFile(QObject *parent = 0);
    int hotlid_tmp;
    int volume;
    int run_type;
    QList<FileSeg> segs;
    QList<FileCycle> cycles;
    int check_seg;
    void reset_def(void);
signals:

public slots:

};

class DevFile : public QObject
{
    Q_OBJECT
public:
    explicit DevFile(QObject *parent = 0);
    QDir *dir;
    QFile *file;
    QFileSystemWatcher *watcher;
    QProcess *process;
    RunFile *run_file;
    QFileInfoList *dir_list;
    QList<QFileInfoList> *file_lists;
    QString cur_dir;
    QString cur_file;
    void init_files(void);
    void read_list(void);
    int read_file(QString &file_path);
    int write_file(QString &file_path);
    void mount_udisk(const QString &dir);
    void umount_udisk(void);
    int add_dir(QString &dir_name);
    int del_dir(int index);
    int usb_detected(void);
signals:

public slots:
    void check_udisk(const QString &dir);
private:
    int usb_stat;
};

#endif // DEV_FILE_H
