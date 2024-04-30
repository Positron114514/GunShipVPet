#include "qssloader.h"
#include <QApplication>

QSSLoader::QSSLoader()
{

}

bool QSSLoader::setStyle(QString qssPath)
{
    QFile qss(qssPath);
    if(qss.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
        return true;
    }
    else
        return false;
}
