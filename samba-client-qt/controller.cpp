#include <QDir>
#include <QProcess>

#include "controller.h"
#include "windowmain.h"

mainwindowcontroller::mainwindowcontroller(QObject *parent) : QObject(parent)
{
    configuration = new Configuration(parent);

    window = new MainWindow();
    window->updateLastItems(configuration->getLastItems() );

    window->setWorkGroup(configuration->workgroup);

    window->show();

    connect(window, SIGNAL(onMountButton()), this, SLOT(onMountButton()));
    connect(window, SIGNAL(changedServer(QString)), this, SLOT(onChangedServer(QString)));
}


void mainwindowcontroller::onMountButton()
{
    SambaShareData data(window->getServer() );
    data.mount_point = window->getMountPoint();
    data.setUid(1000);
    data.workgroup = window->getWorkGroup();
    data.use_login = window->useLogin();
    data.login_name = window->getUserName();
    data.login_password = window->getUserPassword();

    if (window->getAdvancedOptions() != "")
    {
        data.options << window->getAdvancedOptions();
    }

    if (!this->isShareMounted(&data))
    {
        window->debug( this->mount(&data) );
        bool ismounted = this->isShareMounted(&data);
        window->updateMountIndication(ismounted);

        if (ismounted)
        {
            configuration->addItem(data.full_share);
            window->updateLastItems(configuration->getLastItems());
        }
    }
    else
    {
        window->debug( this->unmount(&data) );
        window->updateMountIndication(this->isShareMounted(&data));
    }
}

void mainwindowcontroller::onChangedServer(QString text)
{
    QDir dir(text);
    if (!dir.exists() )
    {
        window->updateMountIndication(false);
        return;
    }
    else
    {
        SambaShareData data(text);
        window->updateMountIndication(this->isShareMounted(&data));
    }
}


QString mainwindowcontroller::mount(SambaShareData * data)
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

QString mainwindowcontroller::unmount(SambaShareData * data)
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

bool mainwindowcontroller::isShareMounted(SambaShareData * data)
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
