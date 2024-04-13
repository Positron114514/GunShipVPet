#include "vpetinterface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VPetInterface w;
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS); // 设置进程优先级
    w.show();
    return a.exec();
}
