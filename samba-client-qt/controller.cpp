#include <QDir>
#include "controller.h"
#include "windowmain.h"

mainwindowcontroller::mainwindowcontroller(QObject *parent) : QObject(parent)
{
    configuration = new Configuration(parent);

    window = new MainWindow();

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

    if (!configuration->isShareMounted(&data))
    {
        window->debug( configuration->mount(&data) );
        window->updateMountIndication(configuration->isShareMounted(&data));
    }
    else
    {
        window->debug( configuration->unmount(&data) );
        window->updateMountIndication(configuration->isShareMounted(&data));
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
        window->updateMountIndication(configuration->isShareMounted(&data));
    }
}
