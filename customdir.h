#ifndef CUSTOMDIR_H
#define CUSTOMDIR_H

#include "qheaders.h"

class CustomDir
{
public:
    CustomDir();

    static QString customDir();
    static QString startupDir();
    static QString autoRunLnkDir();
};

#endif // CUSTOMDIR_H
