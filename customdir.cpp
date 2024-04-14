#include "customdir.h"

CustomDir::CustomDir()
{

}

QString CustomDir::customDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
        QDir::separator() + APP_NAME;
}
