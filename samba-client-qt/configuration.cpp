#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "configuration.h"

Configuration::Configuration(QObject *parent) : QObject(parent)
{
    workgroup = "WORKGROUP";

    QFile file(configLocation);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        lastItems.append(line);
    }

    file.close();
}

Configuration::~Configuration()
{
    save();
}

void Configuration::addItem(QString newitem)
{
    while(lastItems.size() > 9)
    {
        lastItems.removeFirst();
    }

    if (lastItems.contains(newitem))
        return;

    lastItems.append(newitem);

    save();
}

QStringList Configuration::getLastItems()
{
    return lastItems;
}
bool Configuration::save()
{
    QFile file(configLocation);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    for(int i=0;i<lastItems.size();i++)
        out << lastItems[i] << "\n";

    file.close();

    return true;
}
