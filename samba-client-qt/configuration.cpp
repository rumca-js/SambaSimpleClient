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




