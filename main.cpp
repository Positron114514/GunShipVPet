#include "vpetinterface.h"

#include <QApplication>
#include "loghandler.h"

// #define LOG_FILE_ENABLED

QMutex mutex;

int main(int argc, char *argv[])
{

#ifdef LOG_FILE_ENABLED
    LogHandler::initLog();
    qInstallMessageHandler(LogHandler::message);
#endif

    QApplication a(argc, argv);
    VPetInterface w;
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS); // 设置进程优先级
    w.show();
    return a.exec();
}
