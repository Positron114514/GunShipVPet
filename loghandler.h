#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include "qheaders.h"

class LogHandler
{
public:
    LogHandler();

    static void initLog();
    static void message(QtMsgType, const QMessageLogContext &, const QString &);
};

#endif // LOGHANDLER_H
