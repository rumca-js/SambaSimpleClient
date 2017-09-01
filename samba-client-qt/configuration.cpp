#include <QProcess>
#include <QDebug>

#include "configuration.h"

Configuration::Configuration(QObject *parent) : QObject(parent)
{
    workgroup = "WORKGROUP";
}

Configuration::~Configuration()
{
}



QString Configuration::mount(SambaShareData * data)
{
    //QString proc_cmd = "gksudo \"sh -c 'mkdir -p "+data->mount_point+";"+"mount "+data->full_share +" "+data->mount_point +" -t cifs -o " + data->getOptions()+"'\"";
    QString share(data->full_share);
    QString proc_cmd = "mkdir -p "+data->mount_point+" & "+"mount "+share.replace("\\","\\\\") +" "+data->mount_point +" -t cifs -o " + data->getOptions();
    QProcess process;
    process.start("bash", QStringList() << "-c" << proc_cmd);

    if (!process.waitForFinished())
    {
        return "";
    }

    QByteArray outb = process.readAllStandardOutput();
    QByteArray errb = process.readAllStandardError();

    QString out(outb);
    QString err(errb);


    return "Mount commandline: "+proc_cmd+"\nProgram output:"+out+"\nProgram error:"+err+"\n";
}

QString Configuration::unmount(SambaShareData * data)
{
    QProcess process;
    QString proc_cmd = "umount "+data->mount_point;
    process.start("bash", QStringList() << "-c" << proc_cmd);

    if (!process.waitForFinished())
    {
        return "";
    }

    QByteArray outb = process.readAllStandardOutput();
    QByteArray errb = process.readAllStandardError();

    QString out(outb);
    QString err(errb);


    return "Mount commandline: "+proc_cmd+"\nProgram output:"+out+"\nProgram error:"+err+"\n";
}

bool Configuration::isShareMounted(SambaShareData * data)
{
    QProcess process;
    process.start("mount");

    if (!process.waitForFinished())
    {
        return false;
    }

    QByteArray ar = process.readAll();
    QString str(ar);

    if (data->full_share.length() == 0)
        return false;

    if (str.count(data->full_share) > 0 )
    {
        return true;
    }

    return false;
}
