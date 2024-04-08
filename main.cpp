#include "vpetinterface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VPetInterface w;
    w.show();
    return a.exec();
}
