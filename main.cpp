#include "vpetinterface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VPetInterface w;
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    w.show();
    return a.exec();
}
