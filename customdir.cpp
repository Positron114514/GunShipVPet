#include "customdir.h"

CustomDir::CustomDir()
{

}

QString CustomDir::customDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
        QDir::separator() + APP_NAME;
}

QString CustomDir::startupDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
           QDir::separator() + "Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";
}

QString CustomDir::autoRunLnkDir()
{
    return startupDir() + QDir::separator() + "\\GunshipVPet.lnk";
}

QString CustomDir::resourcesDir()
{
    return CustomDir::customDir() + QDir::separator() + "resources/";
}
