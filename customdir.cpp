#include "customdir.h"

CustomDir::CustomDir()
{

}

QString CustomDir::customDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
        QDir::separator() + APP_NAME;
}

