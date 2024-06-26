#include "pythonhandler.h"
// #undef slots
// #define slots Q_SLOTS
#include "vpetinterface.h"

#include <QSharedMemory>

#include <QApplication>
#include "loghandler.h"
#include "qssloader.h"

// #define HIGH_PRIOIRTY_ENABLED

QMutex mutex;

int main(int argc, char *argv[])
{
    PythonHandler::initPython();
    PythonHandler::importNecessaryPyMoudle();
    LogHandler::initLog();
    qInstallMessageHandler(LogHandler::message);

    QApplication a(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false); // 设置平行顶层窗口逻辑：文心一言我爱你xD

    QSharedMemory singleMem(a.applicationName());
    if(!singleMem.create(1))
    {
        qDebug() << QT_BACKGROUND_LOG << "App started more than once";
        return -1;
    }
    // 用共享内存方法检测软件是否运行多次

    QSSLoader::setFontFamily();
    QSSLoader::setStyle(":/qss/material_dark_teal.qss");

#ifdef HIGH_PRIOIRTY_ENABLED
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS); // 设置进程优先级
#endif

    VPetInterface w;

    w.show();
    return a.exec();
}
