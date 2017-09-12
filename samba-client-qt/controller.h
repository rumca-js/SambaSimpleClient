#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include <QWidget>

#include "configuration.h"
#include "windowmain.h"

class mainwindowcontroller : public QObject
{
    Q_OBJECT

    Configuration * configuration;
    MainWindow * window;

public:
    explicit mainwindowcontroller(QObject *parent = 0);

    QString mount(SambaShareData * data);
    QString unmount(SambaShareData * data);
    bool isShareMounted(SambaShareData * data);

public slots:
    void onMountButton();
    void onChangedServer(QString text);
};

#endif // MAINWINDOWCONTROLLER_H
