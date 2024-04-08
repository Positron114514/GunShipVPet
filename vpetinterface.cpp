#include "vpetinterface.h"
#include "ui_vpetinterface.h"

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

VPetInterface::VPetInterface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VPetInterface)
{
    ui->setupUi(this);

    //设置窗体透明
    // this->setWindowFlag(Qt::WindowType::MSWindowsOwnDC, false);
    // this->setWindowFlag(Qt::FramelessWindowHint);
    // this->setWindowFlag(Qt::Tool);
    // this->setWindowFlag(Qt::WindowStaysOnTopHint);
    // this->setAttribute(Qt::WA_TranslucentBackground);

}

VPetInterface::~VPetInterface()
{
    delete ui;
}
