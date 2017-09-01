#ifndef SAMBASERVERDATA_H
#define SAMBASERVERDATA_H

#include <QString>
#include <QStringList>

#include "sambatypes.h"

class SambaShareData
{
public:
    /*!
     * \brief share_name is share name, like //192.168.0.71/Volume1
     */
    SambaShareData(QString share_name);

    QStringList options;

    QString getOptions();
    void setUid(int val);

    QString full_share;
    QString mount_point;

    bool use_login;
    QString login_name;
    QString login_password;
    QString workgroup;
};

#endif // SAMBASERVERDATA_H
