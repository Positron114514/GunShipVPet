#ifndef QSSLOADER_H
#define QSSLOADER_H

#include "qheaders.h"

class QSSLoader
{
public:
    QSSLoader();

    static void setFontFamily();
    static bool setStyle(QString qssPath);
};

#endif // QSSLOADER_H
