#include "dev_file.h"


RunFile::RunFile(QObject *parent): QObject(parent)
{

}

void RunFile::reset_def(void)
{
    this->hotlid_tmp=999;
    this->volume=80;
    this->run_type=1;
    FileSeg seg;
    seg.tmp=999;
    seg.minite=2;
    seg.second=30;
    seg.speed=4;
    seg.grad=0;
    seg.ext_tmp=0;
    seg.ext_minite=0;
    seg.ext_second=0;
    seg.ext_grad[0]=0;
    seg.ext_grad[1]=0;
    seg.ext_grad[2]=0;
    seg.ext_grad[3]=0;
    seg.ext_grad[4]=0;
    this->segs.append(seg);
    this->segs.append(seg);
    this->segs.append(seg);
    this->segs.append(seg);
    this->segs.append(seg);
    FileCycle cycle;
    cycle.num=20;
    cycle.begin_seg=2;
    cycle.end_seg=4;
    this->cycles.append(cycle);
}
DevFile::DevFile(QObject *parent): QObject(parent)
{
    usb_stat=0;
    dir = new QDir;
    file = new QFile;  
    process = new QProcess;
    run_file = new RunFile;
    dir_list = new QFileInfoList;
    file_lists = new QList<QFileInfoList>;
    watcher = new QFileSystemWatcher;
    init_files();
    umount_udisk();
    check_udisk("/dev");
    watcher->addPath("/dev");
    connect(watcher,SIGNAL(directoryChanged(const QString&)),this,SLOT(check_udisk(const QString&)));
    read_list();
}
void DevFile::init_files(void)
{
    dir->setPath("/home/pcr_files");
    if(dir->exists())
    {

    }
    else
    {
        qDebug()<< "mkpath pcr_files";
        dir->mkpath("/home/pcr_files");
        dir->mkdir("run_files");
        dir->cd("run_files");
        dir->mkdir("factory");
        dir->cd("factory");
        QString def_file(dir->path());
        def_file = def_file+"/bf_def.ebr";
        run_file->reset_def();
        qDebug()<< "write def file";
        this->write_file(def_file);
    }
//    file->setFileName("/home/pcr");
  //  qDebug() << "remove pcr " << file->remove();
}
void DevFile::read_list(void)
{
    dir->setPath("/home/pcr_files/run_files");
    dir->setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
    dir->setSorting(QDir::Time);
    *dir_list=dir->entryInfoList();
    if(true==usb_stat)
    {
        for(int i=0;i<dir_list->size();i++)
        {
            if("USB"==dir_list->at(i).fileName())
            {
                if(i!=0)
                {
                    dir_list->move(i,0);
                }
                break;
            }
        }
    }
    QStringList name_filter;
    name_filter << "*.ebr";
    for(int i=0;i<dir_list->size();i++)
    {
        dir->cd(dir_list->at(i).fileName());
        dir->setNameFilters(name_filter);
        dir->setFilter(QDir::Files);
        dir->setSorting(QDir::Time);
        file_lists->insert(i,dir->entryInfoList());
        dir->cd("..");
    }

    for(int i=0;i<dir_list->size();i++)
    {
        qDebug()<< dir_list->at(i).fileName();
        for(int j=0;j<file_lists->at(i).size();j++)
        {
            qDebug()<< file_lists->at(i).at(j).fileName();
            qDebug()<< file_lists->at(i).at(j).lastModified().toString("yyyy-MM-dd HH:mm");
        }
    }
}
int DevFile::add_dir(QString &dir_name)
{
    Q_UNUSED(dir_name);
    return 0;
}
int DevFile::del_dir(int index)
{
    Q_UNUSED(index);
    return 0;
}

int DevFile::write_file(QString &file_path)
{
    QFile file(file_path);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate))
    {
        qDebug()<< "open fail";
        return -1;
    }
    int name_start=file_path.lastIndexOf('/')+1;
    QString filename(file_path.right(file_path.size()-name_start));
    qDebug()<< "file name" << filename;
    QByteArray write_info;
    int index=0;
    write_info.insert(index++,1);
    for(int i=0;i<12;i++)
    {
        write_info.insert(index++,0xFF);
    }
    for(int i=0;i<12;i++)
    {
        if(i<(filename.size()-4))
        {
            write_info.insert(index++,filename.at(i).cell());
        }
        else
        {
            write_info.insert(index++,0xFF);
        }
    }
    QDateTime filetime(QDateTime::currentDateTime());
    write_info.insert(index++,(char)(filetime.date().year()%100));
    write_info.insert(index++,(char)(filetime.date().month()));
    write_info.insert(index++,(char)(filetime.date().daysInMonth()));
    write_info.insert(index++,(char)(filetime.time().hour()));
    write_info.insert(index++,(char)(filetime.time().minute()));
    write_info.insert(index++,(char)(run_file->segs.size()));

    for(int i=0;i< run_file->segs.size();i++)
    {
        qDebug()<<"write segs"<<i;
        write_info.insert(index++,(char)(run_file->segs.at(i).tmp/100));
        write_info.insert(index++,(char)(run_file->segs.at(i).tmp%100));
        write_info.insert(index++,(char)(run_file->segs.at(i).minite));
        write_info.insert(index++,(char)(run_file->segs.at(i).second));
        write_info.insert(index++,(char)(run_file->segs.at(i).speed));
        if(run_file->segs.at(i).ext_tmp>0)
        {
            write_info.insert(index++,'+');
            write_info.insert(index++,(char)(run_file->segs.at(i).ext_tmp));
        }
        else
        {
            write_info.insert(index++,'-');
            int ext_tmp = -run_file->segs.at(i).ext_tmp;
            write_info.insert(index++,(char)(ext_tmp));
        }
        if(run_file->segs.at(i).ext_minite>0)
        {
            write_info.insert(index++,'+');
            write_info.insert(index++,(char)(run_file->segs.at(i).ext_minite));
        }
        else
        {
            write_info.insert(index++,'-');
            int ext_minite = -run_file->segs.at(i).ext_minite;
            write_info.insert(index++,(char)(ext_minite));
        }
        if(run_file->segs.at(i).ext_second>0)
        {
            write_info.insert(index++,'+');
            write_info.insert(index++,(char)(run_file->segs.at(i).ext_second));
        }
        else
        {
            write_info.insert(index++,'-');
            int ext_second = -run_file->segs.at(i).ext_second;
            write_info.insert(index++,(char)(ext_second));
        }
        write_info.insert(index++,(char)(run_file->segs.at(i).grad));
        qDebug()<<"write ext_grad"<<i;
        for(int j=0;j<5;j++)
        {
            if(run_file->segs.at(i).ext_grad[j]>0)
            {
                write_info.insert(index++,'+');
                write_info.insert(index++,(char)(run_file->segs.at(i).ext_grad[j]/100));
                write_info.insert(index++,(char)(run_file->segs.at(i).ext_grad[j]%100));
            }
            else
            {
                write_info.insert(index++,'-');
                int ext_grad = -run_file->segs.at(i).ext_grad[j];
                write_info.insert(index++,(char)(ext_grad/100));
                write_info.insert(index++,(char)(ext_grad%100));
            }
        }
    }
    qDebug()<<"write cycles";
    write_info.insert(index++,(char)(run_file->cycles.size()));
    for(int i=0 ;i<run_file->cycles.size();i++)
    {
        write_info.insert(index++,(char)(run_file->cycles.at(i).num));
        write_info.insert(index++,(char)(run_file->cycles.at(i).end_seg));
        write_info.insert(index++,(char)(run_file->cycles.at(i).begin_seg));
    }
    write_info.insert(index++,(char)(run_file->hotlid_tmp/100));
    write_info.insert(index++,(char)(run_file->hotlid_tmp%100));
    write_info.insert(index++,(char)(run_file->volume/100));
    write_info.insert(index++,(char)(run_file->volume%100));
    write_info.insert(index++,(char)(run_file->run_type));
    qDebug()<<  file.write(write_info);
    file.close();
    return 0;
}
int DevFile::read_file(QString &file_path)
{
    QFile file(file_path);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        qDebug()<< "open fail";
        return -1;
    }
    int index=0;
    const QByteArray &read_info=file.read(file.size());
    qDebug()<< "read_info" << read_info.size();
    index += 13;
    QString name;
    for(int i=index;i<index+12;i++)
    {
        if(!read_info.at(i))
        {
            break;
        }
        name+=read_info.at(i);
    }
    index += 12;
    name += ".ebr";
    qDebug() << name;
    index +=5;
    int seg_num = read_info.at(index++);
    run_file->segs.clear();
    for(int i=0;i<seg_num;i++)
    {
        FileSeg seg;
        seg.tmp=read_info.at(index++)*100;
        seg.tmp+=read_info.at(index++);
        seg.minite=read_info.at(index++);
        seg.second=read_info.at(index++);
        seg.speed=read_info.at(index++);
        if(read_info.at(index)=='+')
        {
            index++;
            seg.ext_tmp=read_info.at(index++);
        }
        else if(read_info.at(index)=='-')
        {
            index++;
            seg.ext_tmp= 0-read_info.at(index++);
        }
        else{}
        if(read_info.at(index)=='+')
        {
            index++;
            seg.ext_minite=read_info.at(index++);
        }
        else if(read_info.at(index)=='-')
        {
            index++;
            seg.ext_minite= 0-read_info.at(index++);
        }
        else{}
        if(read_info.at(index)=='+')
        {
            index++;
            seg.ext_second=read_info.at(index++);
        }
        else if(read_info.at(index)=='-')
        {
            index++;
            seg.ext_second= 0-read_info.at(index++);
        }
        else{}
        if(read_info.at(index)=='+')
        {
            index++;
            seg.ext_second=read_info.at(index++);
        }
        else if(read_info.at(index)=='-')
        {
            index++;
            seg.ext_second= 0-read_info.at(index++);
        }
        else{}

        seg.grad=read_info.at(index++);
        for(int j=0;j<5;j++)
        {
            if(read_info.at(index)=='+')
            {
                index++;
                seg.ext_grad[j]=read_info.at(index++)*100;
                seg.ext_grad[j]+=read_info.at(index++);
            }
            else if(read_info.at(index)=='-')
            {
                index++;
                seg.ext_grad[j]=0-read_info.at(index++)*100;
                seg.ext_grad[j]-=read_info.at(index++);
            }
            else{}
        }
        run_file->segs.append(seg);
    }
    int cycle_num = read_info.at(index++);
    run_file->cycles.clear();
    for(int i=0;i<cycle_num;i++)
    {
        int j=0;
        FileCycle cycle;
        cycle.num=read_info.at(index++);
        cycle.end_seg=read_info.at(index++);
        cycle.begin_seg=read_info.at(index++);
        for(j=0;j<run_file->cycles.size();j++)
        {
            if(cycle.begin_seg<run_file->cycles.at(j).begin_seg)
            {
                break;
            }
        }
        run_file->cycles.insert(j,cycle);
    }
    run_file->hotlid_tmp=read_info.at(index++)*100;
    run_file->hotlid_tmp+=read_info.at(index++);
    run_file->volume=read_info.at(index++)*100;
    run_file->volume+=read_info.at(index++);
    run_file->run_type=read_info.at(index);
    file.close();
    QString dis("%1");
    qDebug() << "seg size"<< dis.arg(run_file->segs.size());
    for(int i=0;i<run_file->segs.size();i++)
    {
        qDebug() << "tmp" << i << dis.arg(run_file->segs.at(i).tmp);
        qDebug() << "minite" << i << dis.arg(run_file->segs.at(i).minite);
        qDebug() << "second" << i << dis.arg(run_file->segs.at(i).second);
        qDebug() << "speed" << i << dis.arg(run_file->segs.at(i).speed);
        qDebug() << "ext_tmp" << i << dis.arg(run_file->segs.at(i).ext_tmp);
        qDebug() << "ext_minite" << i << dis.arg(run_file->segs.at(i).ext_minite);
        qDebug() << "ext_second" << i << dis.arg(run_file->segs.at(i).ext_second);
        qDebug() << "grad" << i << dis.arg(run_file->segs.at(i).grad);
        for(int j=0;j<5;j++)
        {
            qDebug() << "ext_grad" << i << j << dis.arg(run_file->segs.at(i).ext_grad[j]);
        }

    }
    qDebug() << "cycles size " <<  dis.arg(run_file->cycles.size());
    for(int i=0;i<run_file->cycles.size();i++)
    {
        qDebug() << "num" << i << dis.arg(run_file->cycles.at(i).num);
        qDebug() << "end" << i << dis.arg(run_file->cycles.at(i).end_seg);
        qDebug() << "begin" << i << dis.arg(run_file->cycles.at(i).begin_seg);
    }
    return 0;
}
int DevFile::usb_detected(void)
{
    return usb_stat;
}
void DevFile::check_udisk(const QString &dir)
{
    QDir dev_dir(dir);
    dev_dir.setFilter(QDir::System);
    QStringList str_list;
    str_list << "sd*1";
    dev_dir.setNameFilters(str_list);
    QStringList entry = dev_dir.entryList();
    qDebug() << entry.size() ;
    for(int i=0;i<entry.size();i++)
    {
        qDebug() << entry.at(i) ;
    }
    if((0<entry.size())&&usb_stat==0)
    {
        usb_stat=1;
        qDebug() << "detect usb in" ;
        mount_udisk(entry.at(0));
    }
    else if((0==entry.size())&&usb_stat==1)
    {
        usb_stat=0;
        qDebug() << "detect usb out";
        umount_udisk();
    }
    else
    {}
}
void DevFile::mount_udisk(const QString &sdx)
{
    dir->setPath("/home/pcr_files/run_files");
    dir->mkdir("USB");
    QStringList arg;
    QString str("/dev/");
    str+=sdx;
    arg << str << "/home/pcr_files/run_files/USB";
    process->start("mount",arg);
    if(true==process->waitForFinished())
    {
        qDebug()<< "return true";
        QByteArray result=process->readAll();
        qDebug()<< result;
    }
    else
    {
        QByteArray result=process->readAll();
        qDebug()<< result;
    }
}
void DevFile::umount_udisk(void)
{
    QStringList arg;
    arg << "/home/pcr_files/run_files/USB";
    process->start("umount",arg);
    if(true==process->waitForFinished())
    {
        qDebug()<< "return true";
        QByteArray result=process->readAll();
        qDebug()<< result;
    }
    else
    {
        QByteArray result=process->readAll();
        qDebug()<< result;
    }
    dir->setPath("/home/pcr_files/run_files");
    if(true==dir->rmdir("USB/"))
    {
        qDebug() << "remove udisk success";
    }
    else
    {
        qDebug() << "remove udisk fail";
    }
}
