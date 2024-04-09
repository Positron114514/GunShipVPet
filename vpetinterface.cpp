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

    // 设置窗体透明
    this->setWindowFlag(Qt::WindowType::MSWindowsOwnDC, false);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::Tool);
    // this->setWindowFlag(Qt::WindowStaysOnTopHint);   // 窗口置顶
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 初始化托盘图标
    InitializeSystemTray();
}

VPetInterface::~VPetInterface()
{
    delete ui;
}

void VPetInterface::InitializeSystemTray()
{
    trayMenu = new QMenu(this);

    // 系统托盘相关设置
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/ico/resources/icons/logo-tmp.ico"));
    trayIcon->setToolTip("虚拟桌宠");

    actionQuit = new QAction("退出", this);
    actionSettings = new QAction("设置", this);

    // action 信号与槽
    connect(actionQuit, &QAction::triggered, this, &QApplication::quit);
    connect(actionSettings, &QAction::triggered, this, &VPetInterface::onSettingsClicked);

    // 菜单设置：添加actions时，从上往下
    trayMenu->addAction(actionSettings);
    trayMenu->addAction(actionQuit);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

void VPetInterface::onSettingsClicked()
{
    // 空实现
    qDebug() << QT_INTERFACE_LOG << "Settings Action triggered";
}
