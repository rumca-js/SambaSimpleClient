#include "sambasharedata.h"

SambaShareData::SambaShareData(QString share_name)
{
    full_share = share_name;
    mount_point = "/mnt/samba/"+share_name.replace("/", "_");

    use_login = false;
    login_name = "";
    login_password = "";
}

void SambaShareData::setUid(int val)
{
    options << "uid="+QString::number(val);
}

QString SambaShareData::getOptions()
{
    if (!use_login)
    {
        options << "guest";
    }
    if (use_login)
    {
        options << "username="+login_name;
        options << "password="+login_password;
        if (workgroup != "" && workgroup != "WORKGROUP")
        {
            options << "domain="+workgroup;
        }
    }

    return options.join(",");
}
