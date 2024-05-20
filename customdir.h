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
    static QString resourcesDir();
};

#endif // CUSTOMDIR_H
