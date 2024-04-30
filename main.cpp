#include "vpetinterface.h"

#include <QApplication>
#include "loghandler.h"
#include "qssloader.h"

#define LOG_FILE_ENABLED
// #define HIGH_PRIOIRTY_ENABLED

QMutex mutex;

int main(int argc, char *argv[])
{

#ifdef LOG_FILE_ENABLED
    LogHandler::initLog();
    qInstallMessageHandler(LogHandler::message);
#endif

    QApplication a(argc, argv);

    QSSLoader::setStyle(":/qss/material_dark_teal.qss");

#ifdef HIGH_PRIOIRTY_ENABLED
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS); // 设置进程优先级
#endif

    VPetInterface w;

    w.show();
    return a.exec();
}
