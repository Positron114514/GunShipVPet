#include "qssloader.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDirIterator>

QSSLoader::QSSLoader()
{

}

void QSSLoader::setFontFamily()
{
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-Bold.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-Demibold.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-ExtraLight.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-Heavy.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-Light.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-Medium.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-Normal.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-Regular.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-Semibold.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/font/MiSans-Thin.ttf");
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
