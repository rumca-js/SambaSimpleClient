#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QWidget>
#include <QList>

#include "sambatypes.h"
#include "sambasharedata.h"

class Configuration : public QObject
{
    Q_OBJECT
public:
    explicit Configuration(QObject *parent = 0);
    ~Configuration();

    QString workgroup;
    QStringList lastItems;
    QString configLocation = "/usr/local/etc/samba-simple.conf";

    void addItem(QString);
    QStringList getLastItems();
    bool save();

signals:

public slots:
};

#endif // CONFIGURATION_H
